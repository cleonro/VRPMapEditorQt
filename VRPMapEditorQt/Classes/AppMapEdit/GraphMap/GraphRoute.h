#pragma once

#include "GraphNode.h"
#include <vector>
#include <QDataStream>

struct tRouteInf
{
	float distance_;
	float time_;
};

struct tRouteNodes 
{
	OGraphNode* start_node_;
	OGraphNode* end_node_;
};

struct tRouteAddr
{
	char start_address_[50];
	char end_address_[50];
};

class OGraphRoute
{
public:

	friend QDataStream& operator<<(QDataStream& ar, const OGraphRoute& route);
	friend QDataStream& operator>>(QDataStream& ar, OGraphRoute& route);

	OGraphRoute();
	~OGraphRoute();

	inline std::vector<double>* GetPathAddr() {return &path_;}

	// set/get distance and time
	void SetRouteInf(tRouteInf route_inf);
	tRouteInf GetRouteInf();

	//set/get route nodes
	void SetRouteNodes(tRouteNodes route_nodes);
	tRouteNodes GetRouteNodes();

	// set/get start and end route adresses
	void SetRouteAddr(tRouteAddr route_addr);
	tRouteAddr GetRouteAddr();

	inline void Select(bool slct) {selected_ = slct;}
	inline bool IsSelected() {return selected_;}

	void Draw(float transparency = 0.7, float line_width = 1.0);

	//export to xml
	void ToXml(rapidxml::xml_document<>& doc, rapidxml::xml_node<>*& node);
	//import from xml
	bool FromXml(rapidxml::xml_node<>* node);

protected:

	bool selected_;

	OGraphNode* start_node_;
	OGraphNode* end_node_;
	std::vector<double> path_;

	float distance_;//total distance in kilometers
	float time_;//aproximate traveling time in minutes

	char start_address_[50];
	char end_address_[50];
};

