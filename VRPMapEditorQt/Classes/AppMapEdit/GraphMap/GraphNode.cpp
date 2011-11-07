#include "GraphNode.h"

#include "../MapOperationsInput.h"
#include "../../Draw2D.h"

#include <math.h>
#include <QString>

QDataStream& operator<<(QDataStream& ar, const OGraphNode& node)
{
	QString str_name = QString(node.name_);
	ar<<node.type_<<node.latitude_<<node.longitude_<<str_name;
	if(node.type_ == OGraphNode::N_START) {
		QString str_vehicles(node.vehicles_);
		ar<<str_vehicles;
	} else {
		ar<<node.waiting_time_<<node.quantity_;
	}
	ar<<node.Accesibility();
	if(node.type_ == OGraphNode::N_CLIENT) {
		ar<<node.Locals()<<node.Contracts()<<node.Price();
	}
	return ar;
}

QDataStream& operator>>(QDataStream& ar, OGraphNode& node)
{
	int r;
	QString str_name;
	ar>>r>>node.latitude_>>node.longitude_>>str_name;
	strncpy(node.name_, str_name.toAscii().data(), 20);
	switch(r) {
		case 0:
			node.type_ = OGraphNode::N_START;
			break;
		case 1:
			node.type_ = OGraphNode::N_CLIENT;
			break;
		case 2:
			node.type_ = OGraphNode::N_DEPOT;
			break;
		case 3:
			node.type_ = OGraphNode::N_TRANSIT;
			break;
		default:
			node.type_ = OGraphNode::N_START;
			break;
	}
	if(node.type_ == OGraphNode::N_START) {
		QString str_vehicles;
		ar>>str_vehicles;
		strncpy(node.vehicles_, str_vehicles.toAscii().data(), 200);
	} else {
		ar>>node.waiting_time_>>node.quantity_;
	}
	ar>>node.Accesibility();
	if(node.type_ == OGraphNode::N_CLIENT) {
		ar>>node.Locals()>>node.Contracts()>>node.Price();
	}
	return ar;
}

OGraphNode::OGraphNode()
{
	selected_ = false;

	strcpy_s(name_, "");
	waiting_time_ = 0.0;
	quantity_ = 0.0;

	//vehicles_.reserve(10);
	strcpy_s(vehicles_, "");

	accesib_index_ = 1.0;
	locals_ = 100;
	contracts_ = 100;
	price_ = 10.0;
}


OGraphNode::~OGraphNode()
{

}

void OGraphNode::GetCoordinates(double& lat, double& longit)
{
	lat = latitude_;
	longit = longitude_;
}

void OGraphNode::SetCoordinates(double lat, double longit)
{
	latitude_ = lat;
	longitude_ = longit;
}

void OGraphNode::SetNodeInf(tNodeInf node_info)
{
	//strcpy_s(name_, node_info.name_);
	waiting_time_ = node_info.waiting_time_;
	quantity_ = node_info.quantity_;
}

tNodeInf OGraphNode::GetNodeInf()
{
	tNodeInf node_info;
	//strcpy_s(node_info.name_, name_);
	node_info.waiting_time_ = waiting_time_;
	node_info.quantity_ = quantity_;
	return node_info;
}

void OGraphNode::Draw(float transparency)
{
	double xw, yw;
	double xs, ys;

	MAPOPP.FromLatLongToWorldCoord(latitude_, longitude_, xw, yw);
	MAPOPP.FromWorldCoordToScreenCoord(xw, yw, xs, ys);
		
	ePolyType ptype;
	float angle;
	float r, g, b;

	switch(type_) {
		case N_START:
			//ptype = SQUARE;
			ptype = TRIANGLE;
			angle = 0.0f;
			r = 0.82;
			g = 0.91;
			b = 0.56;
			break;
		case N_CLIENT:
			//ptype = HEXAGON;
			ptype = CIRCLE;
			angle = 0.0f;
			r = 0.69;
			g = 0.84;
			b = 0.23;
			break;
		case N_DEPOT:
			//ptype = TRIANGLE;
			ptype = SQUARE;
			angle = 0.0f;
			r = 1.0;
			g = 0.77;
			b = 0.44;
			break;
		case N_TRANSIT:
			//ptype = TRIANGLE;
			//angle = 180.0f;
			ptype = HEXAGON;
			angle = 0.0f;
			r = 0.44;
			g = 0.72;
			b = 0.72;
			break;
	}

	if(selected_) {
		DRAW2D.SetColor(0.8f, 0.3f, 0.3f, transparency);
	} else {
		DRAW2D.SetColor(r, g, b, transparency);
	}

	DRAW2D.FillPoly(xs, ys, 8, angle, ptype);
	DRAW2D.SetColor(0.0f, 0.0f, 0.0f, transparency);
	DRAW2D.DrawPoly(xs, ys, 8, angle, ptype);
}

void OGraphNode::ToXml(rapidxml::xml_document<>& doc, rapidxml::xml_node<>*& node)
{
	node = doc.allocate_node(rapidxml::node_element, "GRAPH_NODE");

	char* str;
	char buff[20];
	//type
	sprintf(buff,"%d", type_);
	str = doc.allocate_string(buff, 20);
	rapidxml::xml_node<>* nxtype = doc.allocate_node(rapidxml::node_element, "TYPE", str);
	//coordinates
	sprintf(buff, "%.4lf %.4lf", latitude_, longitude_);
	str = doc.allocate_string(buff, 20);
	rapidxml::xml_node<>* nxcoord = doc.allocate_node(rapidxml::node_element, "COORD", str);
	//name
	str = doc.allocate_string(name_, 20);
	rapidxml::xml_node<>* nxname = doc.allocate_node(rapidxml::node_element, "NAME", str);
	//waiting time & quantity
	sprintf(buff, "%.2f %.2f", waiting_time_, quantity_);
	str = doc.allocate_string(buff, 20);
	rapidxml::xml_node<>* nxtimequant = doc.allocate_node(rapidxml::node_element, "TIME_QUANT", str);
	//vehicles
	str = doc.allocate_string(vehicles_, 200);
	rapidxml::xml_node<>* nxveh = doc.allocate_node(rapidxml::node_element, "VEHICLES", str);
	//special informations
	char nbuff[30];
	sprintf(nbuff, "%.2f %d %d %.2f", accesib_index_, locals_, contracts_, price_);
	str = doc.allocate_string(nbuff, 30);
	rapidxml::xml_node<>* nxinf = doc.allocate_node(rapidxml::node_element, "SPECIAL_INF", str);

	node->append_node(nxtype);
	node->append_node(nxcoord);
	node->append_node(nxname);
	node->append_node(nxtimequant);
	node->append_node(nxveh);
	node->append_node(nxinf);
}

void OGraphNode::FromXml(rapidxml::xml_node<>* node)
{
	int r;
	//type
	int tp = atoi(node->first_node("TYPE")->value());
	type_ = static_cast<eNodeType>(tp);
	//coordinates
	char *s = node->first_node("COORD")->value();
	r = sscanf(s, "%lf %lf", &latitude_, &longitude_);
	//name
	strcpy(name_, node->first_node("NAME")->value());
	//waiting time & quantity
	r = sscanf(node->first_node("TIME_QUANT")->value(), "%f %f", &waiting_time_, &quantity_);
	//vehicles
	strcpy(vehicles_, node->first_node("VEHICLES")->value());
	//special informations
	r = sscanf(node->first_node("SPECIAL_INF")->value(), "%f %d %d %f", &accesib_index_, &locals_, &contracts_, &price_);
}