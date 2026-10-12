#include "MapOperationsIAccess.h"
#include "../xml/rapidxml.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>
#include <QUrlQuery>

OMapOperationsIAccess::OMapOperationsIAccess()
{
    path_ = nullptr;
    route_ = nullptr;
}

OMapOperationsIAccess::~OMapOperationsIAccess()
{
}

QByteArray OMapOperationsIAccess::FetchUrl(const char* address)
{
    // The manager and reply belong to the calling thread, including worker jobs.
    QNetworkAccessManager manager;
    QUrl url(QString::fromUtf8(address));
    if (url.host() == "maps.googleapis.com") {
        const QString key = qEnvironmentVariable("GOOGLE_MAPS_API_KEY");
        if (key.isEmpty()) { return {}; }
        QUrlQuery query(url);
        query.addQueryItem("key", key);
        url.setQuery(query);
    }
    if (QThread::currentThread()->isInterruptionRequested()) { return {}; }
    QNetworkRequest request{url};
    request.setTransferTimeout(30000);
    QNetworkReply* reply = manager.get(request);
    reply->setReadBufferSize(SIZEBUFF);
    QEventLoop loop;
    QTimer deadline;
    deadline.setSingleShot(true);
    QObject::connect(&deadline, &QTimer::timeout, reply, &QNetworkReply::abort);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QByteArray response;
    bool tooLarge = false;
    const auto read = [&] {
        const QByteArray chunk = reply->readAll();
        if (chunk.size() > SIZEBUFF - 1 - response.size()) {
            tooLarge = true;
            reply->abort();
            return;
        }
        response.append(chunk);
    };
    QObject::connect(reply, &QIODevice::readyRead, &loop, read);
    QTimer cancellation;
    QObject::connect(&cancellation, &QTimer::timeout, reply, [reply] {
        if (QThread::currentThread()->isInterruptionRequested()) { reply->abort(); }
    });
    cancellation.start(100);
    deadline.start(30000);
    loop.exec();
    read();
    const bool ok = !tooLarge && reply->error() == QNetworkReply::NoError;
    if (!ok) { qWarning() << "Map request failed with network error" << reply->error(); }
    delete reply;
    return ok ? response : QByteArray{};
}

bool OMapOperationsIAccess::FindRoute(double latitude0, double longitude0, double latitude1, double longitude1)
{
    const QByteArray address = QString("https://maps.googleapis.com/maps/api/directions/xml?origin=%1,%2&destination=%3,%4&sensor=false")
        .arg(latitude0, 0, 'f', 6).arg(longitude0, 0, 'f', 6)
        .arg(latitude1, 0, 'f', 6).arg(longitude1, 0, 'f', 6).toUtf8();
    const QByteArray response = FetchUrl(address.constData());
    if (response.isEmpty()) { return false; }
    return ParseDirectionsResponseXML(response);
}

bool OMapOperationsIAccess::FindRoute(int i, int j)
{
	int N = graph_.GetSize();
	if(i < 0 || i >= N) {
		return false;
	}
	if(j < 0 || j >= N) {
		return false;
	}

	double lat0, longit0;
	double lat1, longit1;
	graph_.GetNode(i)->GetCoordinates(lat0, longit0);
	graph_.GetNode(j)->GetCoordinates(lat1, longit1);

	return FindRoute(lat0, longit0, lat1, longit1);
}

bool OMapOperationsIAccess::ParseDirectionsResponseXML(QByteArray response)
{
	rapidxml::xml_document<> doc;
    try { doc.parse<0>(response.data()); }
    catch (const rapidxml::parse_error&) { return false; }
	rapidxml::xml_node<> *direction_response = doc.first_node("DirectionsResponse");
    if (!direction_response) { return false; }

	rapidxml::xml_node<> *status = direction_response->first_node("status");
	//rapidxml::xml_attribute<> *status = direction_response->first_attribute();
	if (!status) { return false; }
	if(strcmp(status->value(), "OK") != 0) {
		if(strcmp(status->value(), "OVER_QUERY_LIMIT") == 0) {
			printf("\nOVER_QUERY_LIMIT reached...\n");
		}
		return false;
	}
	//printf("\n%s %s\n", status->name(), status->value());

	rapidxml::xml_node<> *route = direction_response->first_node("route");
	if (!route) { return false; }
	rapidxml::xml_node<> *overview_polyline = route->first_node("overview_polyline");
    if (!overview_polyline) { return false; }
	rapidxml::xml_node<> *points = overview_polyline->first_node("points");
	//printf("\n%s\n%s\n", points->name(), points->value());

	if (!points || !path_ || !route_) { return false; }
    PolylineDecoder(points->value(), path_);

	rapidxml::xml_node<> *leg = route->first_node("leg");
	if (!leg || !leg->first_node("duration") || !leg->first_node("distance")) { return false; }
    rapidxml::xml_node<> *duration = leg->first_node("duration")->first_node("value");
    rapidxml::xml_node<> *distance = leg->first_node("distance")->first_node("value");
	rapidxml::xml_node<> *start_address = leg->first_node("start_address");
	rapidxml::xml_node<> *end_address = leg->first_node("end_address");

    if (!duration || !distance || !start_address || !end_address) { return false; }
	printf("\nRoute\nDuration %s\nDistance %s\nStart Address %s\nEnd Address %s\n", duration->value(),
		distance->value(), start_address->value(), end_address->value());

	int secondes;
	int meters;
	sscanf(duration->value(), "%d", &secondes);
	sscanf(distance->value(), "%d", &meters);
	tRouteInf route_inf;
	route_inf.time_ = (secondes + 0.0) / 60.0;
	route_inf.distance_ = (meters + 0.0) / 1000.0;
	route_->SetRouteInf(route_inf);

	tRouteAddr route_addr;
	qstrncpy(route_addr.start_address_, start_address->value(), sizeof(route_addr.start_address_));
	qstrncpy(route_addr.end_address_, end_address->value(), sizeof(route_addr.end_address_));
	route_->SetRouteAddr(route_addr);

	return true;
}

//http://www.geekyblogger.com/2010/12/decoding-polylines-from-google-maps.html
bool OMapOperationsIAccess::PolylineDecoder(char* encoded, std::vector<double>* polyline)
{
	int index = 0; 
	int	len = strlen(encoded);
	int lat = 0, lng = 0;
	while (index < len) {
		int b;
		int shift = 0;
		int result = 0;

		do {
			b = encoded[index++] - 63;
			result |= (b & 0x1f) << shift;
			shift += 5;
		} while (b >= 0x20);

		int dlat = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
		lat += dlat;
		shift = 0;
		result = 0;

		do {
			b = encoded[index++] - 63;
			result |= (b & 0x1f) << shift;
			shift += 5;
		} while (b >= 0x20);

		int dlng = ((result & 1) != 0 ? ~(result >> 1) : (result >> 1));
		lng += dlng;

		polyline->push_back((double) lat / 1E5);
		polyline->push_back((double) lng / 1E5);
		//printf("\n(%.6lf, %.6lf)\n", (double) lat / 1E5, (double) lng / 1E5);
	}

	return true;
}

//http://groups.google.com/group/google-maps-api/browse_thread/thread/c85319eb7fd930dc
void OMapOperationsIAccess::EncodeSignedNumber(int num, std::string& str)
{
	int sgn_num = num << 1;

	if (num < 0) {
		sgn_num = ~(sgn_num);
	}

	EncodeNumber(sgn_num, str);
}

void OMapOperationsIAccess::EncodeNumber(int num, std::string& str)
{
	str.clear();
	str = "";
	int nextValue;

	while (num >= 0x20) {
		nextValue = (0x20 | (num & 0x1f)) + 63;
		str += ((char)nextValue);
		num >>= 5;
	}

	int finalValue = num + 63;
	str += ((char)finalValue);

}

void OMapOperationsIAccess::PolylineEncoder(std::string& str, std::vector<double>* polyline)
{
	str.clear();
	str = "";
	int lat;
	int longit;
	int dlat;
	int dlongit;
	for(int i = 0; i < polyline->size(); i +=2 ) {
		std::string auxstr_lat = "";
		std::string auxstr_longit = "";
		lat = (*polyline)[i] * 1e5;
		longit = (*polyline)[i + 1] * 1e5;
		if(i == 0) {
			dlat = lat;
			dlongit = longit;
		} else {
			dlat = lat - (*polyline)[i - 2] * 1e5;
			dlongit = longit - (*polyline)[i - 1] * 1e5;
		}
		EncodeSignedNumber(dlat, auxstr_lat);
		EncodeSignedNumber(dlongit, auxstr_longit);
		str += auxstr_lat;
		str += auxstr_longit;
	}
}
