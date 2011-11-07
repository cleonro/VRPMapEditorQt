#include "GraphRoute.h"

#include "../../Draw2D.h"
#include "../MapOperationsInput.h"

QDataStream& operator<<(QDataStream& ar, const OGraphRoute& route)
{
	ar<<route.path_.size();
	for(int i = 0; i < route.path_.size(); i++) {
		ar<<route.path_[i];
	}
	ar<<route.distance_<<route.time_;
	QString start_adr(route.start_address_);
	QString end_addr(route.end_address_);
	ar<<start_adr<<end_addr;

	return ar;
}

QDataStream& operator>>(QDataStream& ar, OGraphRoute& route)
{
	int k;
	double val;
	ar>>k;
	for(int i = 0; i < k; i++) {
		ar>>val;
		route.path_.push_back(val);
	}
	ar>>route.distance_>>route.time_;
	QString start_adr;
	QString end_addr;
	ar>>start_adr>>end_addr;
	strncpy(route.start_address_, start_adr.toAscii().data(), 50);
	strncpy(route.end_address_, end_addr.toAscii().data(), 50);

	return ar;
}

OGraphRoute::OGraphRoute()
{
	selected_ = false;
}


OGraphRoute::~OGraphRoute()
{

}

// set/get distance and time
void OGraphRoute::SetRouteInf(tRouteInf route_inf)
{
	distance_ = route_inf.distance_;
	time_ = route_inf.time_;
}

tRouteInf OGraphRoute::GetRouteInf()
{
	tRouteInf route_inf;
	route_inf.distance_ = distance_;
	route_inf.time_ = time_;
	return route_inf;
}

// set/get route nodes
void OGraphRoute::SetRouteNodes(tRouteNodes route_nodes)
{
	start_node_ = route_nodes.start_node_;
	end_node_ = route_nodes.end_node_;
}

tRouteNodes OGraphRoute::GetRouteNodes()
{
	tRouteNodes route_nodes;
	route_nodes.start_node_ = start_node_;
	route_nodes.end_node_ = end_node_;
	return route_nodes;
}

// set/get start and end route adresses
void OGraphRoute::SetRouteAddr(tRouteAddr route_addr)
{
	strcpy_s(start_address_, route_addr.start_address_);
	strcpy_s(end_address_, route_addr.end_address_);
}

tRouteAddr OGraphRoute::GetRouteAddr()
{
	tRouteAddr route_addr;
	strcpy_s(route_addr.start_address_, start_address_);
	strcpy_s(route_addr.end_address_, end_address_);
	return route_addr;
}

#define DRAW_STEP 4

void OGraphRoute::Draw(float transparency, float line_width)
{
	if(selected_) {
		DRAW2D.SetColor(0.8f, 0.3f, 0.3f, transparency);
	} else {
		DRAW2D.SetColor(0.0f, 0.0f, 0.99f, transparency);
	}
	double x, xs, xs0;
	double y, ys, ys0;
	int iv = 0;
	for(int i = 0; i < path_.size(); i += 2 * DRAW_STEP) {
		MAPOPP.FromLatLongToWorldCoord(path_[i], path_[i + 1], x, y);
		MAPOPP.FromWorldCoordToScreenCoord(x, y, xs, ys);
		if(i > 0) {
			DRAW2D.DrawLine(xs0, ys0, xs, ys, line_width);
		}
		xs0 = xs;
		ys0 = ys;
		iv = i;
	}
	//connect with the last point in path
	if(iv != path_.size() - 2) {
		MAPOPP.FromLatLongToWorldCoord(path_[iv], path_[iv + 1], x, y);
		MAPOPP.FromWorldCoordToScreenCoord(x, y, xs, ys);
		DRAW2D.DrawLine(xs0, ys0, xs, ys, line_width);
	}
}

void OGraphRoute::ToXml(rapidxml::xml_document<>& doc, rapidxml::xml_node<>*& node)
{
	//node = doc.allocate_node(rapidxml::node_element, "GRAPH_ROUTE");

	char* str;
	char buff[20];
	//distance & time
	sprintf(buff, "%.2f %.2f", distance_, time_);
	str = doc.allocate_string(buff, 20);
	rapidxml::xml_node<>* nxdisttime = doc.allocate_node(rapidxml::node_element, "DISTANCE_TIME", str);
	//start address
	str = doc.allocate_string(start_address_, 50);
	rapidxml::xml_node<>* nxstartaddr = doc.allocate_node(rapidxml::node_element, "START_ADDRESS", str);
	//end address
	str = doc.allocate_string(end_address_, 50);
	rapidxml::xml_node<>* nxendaddr = doc.allocate_node(rapidxml::node_element, "END_ADDRESS", str);
	//path
	std::string encoded;
	MAPOPP.PolylineEncoder(encoded, &path_);
	const char* str_encod = encoded.c_str();
	int l = strlen(str_encod);
	str = doc.allocate_string(str_encod, l + 1);
	rapidxml::xml_node<>* nxpath = doc.allocate_node(rapidxml::node_element, "PATH", str);

	node->append_node(nxdisttime);
	node->append_node(nxstartaddr);
	node->append_node(nxendaddr);
	node->append_node(nxpath);
}

bool OGraphRoute::FromXml(rapidxml::xml_node<>* node)
{
	int r;
	//path
	rapidxml::xml_node<>* nxpath = node->first_node("PATH");
	if(nxpath == NULL) {
		return false;
	}
	char* encoded = nxpath->value();
	MAPOPP.PolylineDecoder(encoded, &path_);
	//distance & time
	rapidxml::xml_node<>* nxdisttime = node->first_node("DISTANCE_TIME");
	if(nxdisttime == NULL) {
		return false;
	}
	char* s = nxdisttime->value();
	r = sscanf(s, "%f %f", &distance_, &time_);
	return true;
	//start address
	rapidxml::xml_node<>* nxstartaddr = node->first_node("START_ADDRESS");
	strcpy(start_address_, nxstartaddr->value());
	//end address
	rapidxml::xml_node<>* nxendaddr = node->first_node("END_ADDRESS");
	strcpy(end_address_, nxendaddr->value());
}