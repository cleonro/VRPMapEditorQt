#include "MapOperationsIAccess.h"
#include "../xml/rapidxml.hpp"
//#include "../Network/curl/curl.h"

int OMapOperationsIAccess::size_b_ = 0;

//http://code.google.com/apis/maps/documentation/utilities/polylinealgorithm.html

OMapOperationsIAccess::OMapOperationsIAccess()
{
	buffer_ = new char[SIZEBUFF];
	path_ = NULL;
	route_ = NULL;

// 	CURL *curl;
// 	CURLcode res;
	curl = curl_easy_init();
	if(!curl) {
		printf("\nCurl not initialized...\n");
	}
}

OMapOperationsIAccess::~OMapOperationsIAccess()
{
	if(buffer_) {
		delete [] buffer_;
	}
	if(curl) {
		curl_easy_cleanup(curl);
	}
}

unsigned int OMapOperationsIAccess::write_tc(char *in, unsigned int size, unsigned int nmemb, char *out)
{
	unsigned int r;
	r = size * nmemb;

	memcpy(out + size_b_, in, r);

	size_b_ += r;
	return r;
}

bool OMapOperationsIAccess::CallCurl(char addr[])
{
// 	CURL *curl;
// 	CURLcode res;
// 	curl = curl_easy_init();
// 	if(!curl) {
// 		printf("\nCurl not initialized...\n");
// 		return false;
// 	}

	CURLcode res;

	char curl_errbuf[CURL_ERROR_SIZE] = "";
	curl_easy_setopt(curl, CURLOPT_URL, addr);
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_errbuf);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OMapOperationsIAccess::write_tc); 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer_); 
	size_b_ = 0;
	res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		printf("\n Error calling Curl...\n%s\n", curl_errbuf);
		//curl_easy_cleanup(curl);
		return false;
	}

	//curl_easy_cleanup(curl);
	return true;
}

bool OMapOperationsIAccess::FindRoute(double latitude0, double longitude0, double latitude1, double longitude1)
{
	//http://maps.googleapis.com/maps/api/directions/json?origin=Boston,MA&destination=Concord,MA&waypoints=Charlestown,MA|Lexington,MA&sensor=false
	char tstr[100];
	char addr[2000] = "http://maps.googleapis.com/maps/api/directions/xml?origin=";
	sprintf_s(tstr, "%.6lf,%.6lf&destination=", latitude0, longitude0);
	strcat_s(addr, tstr);
	sprintf_s(tstr, "%.6lf,%.6lf&sensor=false", latitude1, longitude1);
	strcat_s(addr, tstr);

	if(!CallCurl(addr)) {
		return false;
	}

	buffer_[size_b_] = 0;
	return ParseDirectionsResponseXML();
	//printf("\n%s\n", buffer_);

	return true;
}

bool OMapOperationsIAccess::FindRoute(int i, int j)
{
	int N = graph_.GetSize();
	if(i < 0 && i >= N) {
		return false;
	}
	if(j < 0 && j >= N) {
		return false;
	}

	double lat0, longit0;
	double lat1, longit1;
	graph_.GetNode(i)->GetCoordinates(lat0, longit0);
	graph_.GetNode(j)->GetCoordinates(lat1, longit1);

	return FindRoute(lat0, longit0, lat1, longit1);
}

bool OMapOperationsIAccess::ParseDirectionsResponseXML()
{
	rapidxml::xml_document<> doc;
	doc.parse<0>(buffer_);
	rapidxml::xml_node<> *direction_response = doc.first_node();

	rapidxml::xml_node<> *status = direction_response->first_node("status");
	//rapidxml::xml_attribute<> *status = direction_response->first_attribute();
	if(strcmp(status->value(), "OK") != 0) {
		if(strcmp(status->value(), "OVER_QUERY_LIMIT") == 0) {
			printf("\nOVER_QUERY_LIMIT reached...\n");
		}
		return false;
	}
	//printf("\n%s %s\n", status->name(), status->value());

	rapidxml::xml_node<> *route = direction_response->first_node("route");
	rapidxml::xml_node<> *overview_polyline = route->first_node("overview_polyline");
	rapidxml::xml_node<> *points = overview_polyline->first_node("points");
	//printf("\n%s\n%s\n", points->name(), points->value());

	PolylineDecoder(points->value(), path_);

	rapidxml::xml_node<> *leg = route->first_node("leg");
	rapidxml::xml_node<> *duration = leg->first_node("duration")->first_node("value");
	rapidxml::xml_node<> *distance = leg->first_node("distance")->first_node("value");
	rapidxml::xml_node<> *start_address = leg->first_node("start_address");
	rapidxml::xml_node<> *end_address = leg->first_node("end_address");

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
	strncpy_s(route_addr.start_address_, start_address->value(), 48);
	strncpy_s(route_addr.end_address_, end_address->value(), 48);
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
