//#include <afxdialogex.h>
//#include "../../Resource.h"

#include "MapOperations.h"
#include "../Utils/OTextures.h"
#include "../Network/curl/curl.h"
#include <math.h>
#include "../VariousObjects.h"
#include "../xml/rapidxml.hpp"
#include "../Draw2D.h"
#include "../Utils/draw_utils.h"

#include "../AppBaseState.h"
//#include "../../NodeDialogView.h"

#include "GraphAlgorithms/GraphAlgorithm.h"
#include "../Xml/rapidxml_print.hpp"
#include <fstream>

#include <windows.h>
#include <process.h>
#include <QApplication>
#include "..\..\ccentralwidget.h"
#include "OMapEvent.h"

QDataStream& operator<<(QDataStream& ar, const OMapOperations& map_op)
{
	ar<<map_op.graph_;
	return ar;
}

QDataStream& operator>>(QDataStream& ar, OMapOperations& map_op)
{
	ar>>map_op.graph_;
	return ar;
}


OMapOperations::OMapOperations()
{
	
	center_latitude_ = 45.852908;
	center_longitude_ = 25.794983;
	zoom_ = 10;//8;//5;

	FromLatLongToWorldCoord(center_latitude_, center_longitude_, center_xworld_, center_yworld_);
	
	node_[0] = NULL;
	node_[1] = NULL;
	selected_ = 0;
	strncpy(maptype_, "terrain", 10);

	view_ = NULL;
}

OMapOperations::~OMapOperations()
{
	::TerminateThread((HANDLE)thread_importxml_, -1000);
}

void OMapOperations::SetView(CGLWidget* glview) 
{
	view_ = glview;
}

void OMapOperations::FromScreenCoordToWorldCoord(double xscreen, double yscreen, double& xworld, double& yworld)
{
	const double SC = M_PI / pow(2.0, zoom_ + 7.0);
	xworld = center_xworld_ + xscreen * SC;
	yworld = center_yworld_ + yscreen * SC;
}

void OMapOperations::FromWorldCoordToScreenCoord(double xworld, double yworld, double& xscreen, double& yscreen)
{
	const double SC = M_PI / pow(2.0, zoom_ + 7.0);
	xscreen = (xworld - center_xworld_) / SC;
	yscreen = (yworld - center_yworld_) / SC;
}

//Mercator projection
void OMapOperations::FromWorldCoordToLatLong(double xworld, double yworld, double& latitude, double& longitude)
{
	//center_longitude_ and center_latitude_ given in degrees
	
	//compute longitude and latitude in radians
	longitude = xworld + center_longitude_ * (M_PI / 180.0);
	latitude = 2.0 * atan(exp(yworld)) - M_PI_2;

	//transform longitude and latitude in degrees
	latitude *= (180.0 / M_PI);
	longitude *= (180.0 / M_PI);
}

void OMapOperations::FromLatLongToWorldCoord(double latitude, double longitude, double &xworld, double &yworld)
{
	//center_longitude_ and center_latitude_ given in degrees
	//input parameters latitude, longitude given in degrees; must be transformed in radians

	xworld = (longitude - center_longitude_) * (M_PI / 180.0);
	yworld = log(tan(M_PI / 4.0 + (latitude * (M_PI / 180.0)) / 2.0f));
}
//

//return the index of a graph node, close to the point (xworld, yworld) 
int OMapOperations::SearchScreenCoordinatesInGraphNodes(double xscreen, double yscreen)
{
	const double error = 7.2;

	double lxw, lyw;
	double lat, longit;
	double xs, ys;
	double dx, dy;

	int i = 0;
	bool found = false;
	while(i < graph_.GetSize() && !found) {
		node_[0] = graph_.GetNode(i);
		node_[0]->GetCoordinates(lat, longit);
		FromLatLongToWorldCoord(lat, longit, lxw, lyw);
		FromWorldCoordToScreenCoord(lxw, lyw, xs, ys);
		dx = xscreen - xs;
		dy = yscreen - ys;
		if(sqrt(dx * dx + dy * dy) < error) {
			found = true;
		} else {
			i++;
		}
	} 

	if(found) {
		return i;
	} else {
		return -1;
	}
}

//return the index of a graph route, close to the point(xworld, yworld)
int OMapOperations::SearchScreenCoordinatesInGraphRoutes(double xscreen, double yscreen)
{
	const double error = 2.0;
	const int N = graph_.GetSize();
	if(N <= 1) {
		return -1;
	}
	const int R = N * (N - 1) / 2;
	int i = 0;
	bool found = false;
	//while(i < R && !found) {
	for(i = 0; i < R && !found; i++) {
		if(graph_.GetRoute(i) == NULL) {
			continue;
		}
		std::vector<double>* path = graph_.GetRoute(i)->GetPathAddr();
		int k = 1;
		bool sfnd = false;
		double lat1, longit1, lat2, longit2;
		double xw1, yw1, xw2, yw2;
		double x1, y1, x2, y2;
		float dist;
		lat1 = (*path)[0];
		longit1 = (*path)[1];
		FromLatLongToWorldCoord(lat1, longit1, xw1, yw1);
		FromWorldCoordToScreenCoord(xw1, yw1, x1, y1);
		while(k < path->size() / 2 && !sfnd) {
			lat2 = (*path)[2 * k];
			longit2 = (*path)[2 * k + 1];
			FromLatLongToWorldCoord(lat2, longit2, xw2, yw2);
			FromWorldCoordToScreenCoord(xw2, yw2, x2, y2);
			dist = DRAW2D.DistanceFromPointToSegment(xscreen, yscreen, x1, y1, x2, y2);
			if(dist <= error) {
				sfnd = true;
			}
			k++;
			x1 = x2;
			y1 = y2;
		}
		if(sfnd) {
			found = true;
			i = i - 1;
		} //else {
			//i++;
		//}
	}
	
	if(found) {
		return i;
	} else {
		return -1;
	}
}


void OMapOperations::ExportGraphToXml(char* filename)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* doc_node = doc.allocate_node(rapidxml::node_element, "GRAPH_NODES");
	rapidxml::xml_node<>* doc_route = doc.allocate_node(rapidxml::node_element, "GRAPH_ROUTES");

	//nodes
	int sz = graph_.GetSize();
	for(int i = 0; i < sz; i++) {
		rapidxml::xml_node<>* node;
		graph_.GetNode(i)->ToXml(doc, node);
		doc_node->append_node(node);
		//doc.append_node(node);
	}

	//routes
	for(int i = 0; i < sz * (sz - 1) / 2; i++) {
		rapidxml::xml_node<>* node;
		node = doc.allocate_node(rapidxml::node_element, "GRAPH_ROUTE");
		OGraphRoute* route = graph_.GetRoute(i);
		if(route != NULL) {
			route->ToXml(doc, node);
		}
		doc_route->append_node(node);
	}

	//write to file
	doc.append_node(doc_node);
	doc.append_node(doc_route);
	std::fstream fl(filename, std::ios::out);
	fl<<doc;
	fl.close();
}

struct tLoadXml {
	OMapOperations* obj_;
	char* filename_;
};

void OMapOperations::ImportGraphFromXml(char* filename)
{
	tLoadXml* data = new tLoadXml;
	data->obj_ = this;
	int r = strlen(filename);
	data->filename_ = new char[r + 1];
	strcpy(data->filename_, filename);
	thread_importxml_ = _beginthread(OMapOperations::ImportGraphFromXmlThread, 0, (void*)data);
	//ImportGraphFromXmlThread((void*)data);
}

void OMapOperations::ImportGraphFromXmlThread(void* data)
{
	tLoadXml* dt = (tLoadXml*)data;
	rapidxml::xml_document<> doc;
	char* filename = dt->filename_;
	OMapOperations* obj = dt->obj_;

	OMapEvent* event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_START_TIMER;
	QApplication::postEvent(obj->view_, event);

	std::fstream fl(filename, std::ios::in);
	fl.seekg(0, std::ios::end);
	int size = fl.tellg();
	fl.seekg(0);
	char* buffer = new char[size + 1];
	buffer[0] = '\0';
	char lbuff[10000];
	while(!fl.eof()) {
		fl.getline(lbuff, 10000);
		strcat(buffer, lbuff);
	}
	fl.close();

	doc.parse<0>(buffer);

	obj->graph_.Clear();
	OGraphNode* graph_node;

	rapidxml::xml_node<>* xnode = doc.first_node("GRAPH_NODES");
	for(rapidxml::xml_node<>* xnode_child = xnode->first_node("GRAPH_NODE"); xnode_child; xnode_child = xnode_child->next_sibling()) {
		graph_node = new OGraphNode;
		graph_node->FromXml(xnode_child);
		obj->graph_.AddNode(graph_node);
	}

	rapidxml::xml_node<>* xroute = doc.first_node("GRAPH_ROUTES");
	rapidxml::xml_node<>* xroute_child = xroute->first_node("GRAPH_ROUTE");
	for(int i = 1; i < obj->graph_.GetSize(); i++) {
		for(int j = i - 1; j >= 0; j--) {
			printf("\nImport Graph From Xml (%d, %d)", i, j);
			OGraphRoute* route = new OGraphRoute;
			bool r = route->FromXml(xroute_child);
			if(r) {
				obj->graph_.AddRoute(i, j, route);
			} else {
				delete route;
			}
			xroute_child = xroute_child->next_sibling();
		}
	}

	event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_STOP_TIMER;
	QApplication::postEvent(obj->view_, event);

	delete [] buffer;
	delete [] dt->filename_;
	delete dt;
}