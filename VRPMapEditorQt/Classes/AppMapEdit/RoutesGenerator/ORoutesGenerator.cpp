#include "ORoutesGenerator.h"
#include "../GraphAlgorithms/GraphAlgorithm.h"

#include <fstream>
#include <iostream>
#include <strstream>
#include <sstream>


#include <map>
#include <string>

#include "../../xml/rapidxml.hpp"
#include "../../xml/rapidxml_print.hpp"

ORoutesGenerator::ORoutesGenerator()
{
	max_time_ = 8.0;
	temp_day_ = 0;
	initialized_ = false;
	start_node_ = -1;
	//
	SetModel(routesUiModel_);

	for(int i = 0; i < 5; i++) {
		nodes_[i] = 0; cnodes_[i] = 0;
		distance_[i] = 0.0; cdistance_[i] = 0.0;
		time_[i] = 0.0; ctime_[i] = 0.0;
		cost_[i] = 0.0; ncost_[i] = 0.0;
	}

	//
	SetModel(customRoutesUiModel_);
	unidentifiedNodesUiModel_ = new QStandardItemModel();
}

void ORoutesGenerator::Clear()
{
	routesUiModel_->clear();
	customRoutesUiModel_->clear();
	unidentifiedNodesUiModel_->clear();

	max_time_ = 8.0;
	temp_day_ = 0;
	initialized_ = false;
	start_node_ = -1;
	//
	SetModel(routesUiModel_);

	for(int i = 0; i < 5; i++) {
		nodes_[i] = 0; cnodes_[i] = 0;
		distance_[i] = 0.0; cdistance_[i] = 0.0;
		time_[i] = 0.0; ctime_[i] = 0.0;
		cost_[i] = 0.0; ncost_[i] = 0.0;
	}

	SetModel(customRoutesUiModel_);
}

void ORoutesGenerator::ClearCustomRoutes()
{
	for(int i = 0; i < 5; i++) {
		cnodes_[i] = 0;
		cdistance_[i] = 0.0;
		ctime_[i] = 0.0;
		ncost_[i] = 0.0;
	}

	int nvh = vehicles_.size();
	//init custom_routes
	custom_routes_->clear();
	for(int i = 0; i < NDAYS; i++) {
		custom_routes_[i].reserve(nvh + 2);
	}

	customRoutesUiModel_->clear();
	SetModel(customRoutesUiModel_);
}

void ORoutesGenerator::SetModel(QStandardItemModel*& model_)
{
	model_ = new QStandardItemModel();
	model_->setColumnCount(5);
	model_->setHorizontalHeaderItem(0, new QStandardItem("Nume / Tip Veh."));
	model_->setHorizontalHeaderItem(1, new QStandardItem("Noduri"));
	model_->setHorizontalHeaderItem(2, new QStandardItem("Distanta"));
	model_->setHorizontalHeaderItem(3, new QStandardItem("Timp"));
	model_->setHorizontalHeaderItem(4, new QStandardItem("Cost"));

	QStandardItem* day1 = new QStandardItem("Luni");
	QList<QStandardItem*> day1List;
	day1List.append(day1);
	QStandardItem* day1Nodes = new QStandardItem();
	QStandardItem* day1Distance = new QStandardItem();
	QStandardItem* day1Time = new QStandardItem();
	QStandardItem* day1Cost = new QStandardItem();
	day1List.append(day1Nodes);
	day1List.append(day1Distance);
	day1List.append(day1Time);
	day1List.append(day1Cost);
	model_->appendRow(day1List);

	QStandardItem* day2 = new QStandardItem("Marti");
	QList<QStandardItem*> day2List;
	day2List.append(day2);
	QStandardItem* day2Nodes = new QStandardItem();
	QStandardItem* day2Distance = new QStandardItem();
	QStandardItem* day2Time = new QStandardItem();
	QStandardItem* day2Cost = new QStandardItem();
	day2List.append(day2Nodes);
	day2List.append(day2Distance);
	day2List.append(day2Time);
	day2List.append(day2Cost);
	model_->appendRow(day2List);
	QStandardItem* day3 = new QStandardItem("Miercuri");
	QList<QStandardItem*> day3List;
	day3List.append(day3);
	QStandardItem* day3Nodes = new QStandardItem();
	QStandardItem* day3Distance = new QStandardItem();
	QStandardItem* day3Time = new QStandardItem();
	QStandardItem* day3Cost = new QStandardItem();
	day3List.append(day3Nodes);
	day3List.append(day3Distance);
	day3List.append(day3Time);
	day3List.append(day3Cost);
	model_->appendRow(day3List);
	QStandardItem* day4 = new QStandardItem("Joi");
	QList<QStandardItem*> day4List;
	day4List.append(day4);
	QStandardItem* day4Nodes = new QStandardItem();
	QStandardItem* day4Distance = new QStandardItem();
	QStandardItem* day4Time = new QStandardItem();
	QStandardItem* day4Cost = new QStandardItem();
	day4List.append(day4Nodes);
	day4List.append(day4Distance);
	day4List.append(day4Time);
	day4List.append(day4Cost);
	model_->appendRow(day4List);
	QStandardItem* day5 = new QStandardItem("Vineri");
	QList<QStandardItem*> day5List;
	day5List.append(day5);
	QStandardItem* day5Nodes = new QStandardItem();
	QStandardItem* day5Distance = new QStandardItem();
	QStandardItem* day5Time = new QStandardItem();
	QStandardItem* day5Cost = new QStandardItem();
	day5List.append(day5Nodes);
	day5List.append(day5Distance);
	day5List.append(day5Time);
	day5List.append(day5Cost);
	model_->appendRow(day5List);

	QStandardItem* total = new QStandardItem("Total");
	QList<QStandardItem*> totalList;
	totalList.append(total);
	QStandardItem* totalNodes = new QStandardItem();
	QStandardItem* totalDistance = new QStandardItem();
	QStandardItem* totalTime = new QStandardItem();
	QStandardItem* totalCost = new QStandardItem();
	totalList.append(totalNodes);
	totalList.append(totalDistance);
	totalList.append(totalTime);
	totalList.append(totalCost);
	model_->appendRow(totalList);
}

ORoutesGenerator::~ORoutesGenerator()
{

}

void ORoutesGenerator::DecodeVehicleTypesText(char vehicle_types[])
{
	int nc;
	int nb;
	sscanf(vehicle_types, "%d %n", &nb, &nc);//read number of vehicle types in nb
	                                      //nc is number of characters read from vehicle_types
	int tc = nc;//position in the char* vehicle_types
	tVehicleType tp;
	vehicles_.clear();
	vehicles_.reserve(nb);
	for(int i = 0; i < nb; i++) {
		sscanf(&vehicle_types[tc], "%s %f %d %n", &tp.name_, &tp.capacity_, &tp.number_, &nc);
		tc += nc;

		tp.cost_gas_idle_ = 4.0;
		tp.cost_gas_ = 4.0;
		tp.cost_maint_ = 2.0;
		tp.cost_equip_ = 2.0;
		tp.cost_sal_ = 20.0;

		vehicles_.push_back(tp);
	}
}

void ORoutesGenerator::InitDaysQuantities()
{
	const int N = p_graph_map_->GetSize();
	quantities_.clear();
	quantities_.reserve(N);
	days_.clear();
	days_.reserve(N);
	tNodeInf inf;
	for(int i = 0; i < N; i++) {
		inf = p_graph_map_->GetNode(i)->GetNodeInf();
		quantities_.push_back(inf.quantity_);
		days_.push_back(-1);
	}
}

void ORoutesGenerator::InitTempData()
{
	//temp_day_ = 0;
	temp_vehicles_.clear();
	temp_vehicles_.reserve(vehicles_.size());
	for(int i = 0; i < vehicles_.size(); i++)
	{
		temp_vehicles_.push_back(vehicles_[i].number_);
	}
}

int ORoutesGenerator::FindAvVehType()
{
	int r = -1;
	for(int i = 0; i < temp_vehicles_.size(); i++)
	{
		if(temp_vehicles_[i] > 0) 
		{
			r = i;
			break;
		}
	}
	return r;
}

void ORoutesGenerator::Init(OGraphMap& graph_map)
{
	if(initialized_) {
		return;
	}
	p_graph_map_ = &graph_map;

	OGraphNode::eNodeType tp;
	const int N = graph_map.GetSize();

	//find start node and depots
	depots_.clear();
	for(int i = 0; i < N; i++) {
		tp = graph_map.GetNode(i)->GetType();
		if(tp == OGraphNode::N_DEPOT || tp == OGraphNode::N_TRANSIT) {
			depots_.push_back(i);
		}
		if(tp == OGraphNode::N_START) {
			start_node_ = i;
		}
	}

	if(start_node_ >= 0) {
		char* vh = graph_map.GetNode(start_node_)->Vehicles();
		DecodeVehicleTypesText(vh);
	}

	//init all_routes_
	all_routes_->clear();
	int nvh = vehicles_.size();
	for(int i = 0; i < NDAYS; i++) {
		all_routes_[i].reserve(nvh + 2);
	}

	//init custom_routes
	custom_routes_->clear();
	for(int i = 0; i < NDAYS; i++) {
		custom_routes_[i].reserve(nvh + 2);
	}

	//init quantities_ and days_
	InitDaysQuantities();

	//populate shortest_routes_
	shortest_routes_.clear();
	shortest_routes_.reserve((N - 1) * (N - 2) / 2 + 1);
	for(int i = 1; i < N; i++) {
		for(int j = i - 1; j >= 0; j--) {
			OVehicleRoute route;
			GRAPHALG.Djikstra(*p_graph_map_, i, j, route.Sequence());
			shortest_routes_.push_back(route);
		}
	}

	//test GetShortestRouteLength and GetShortestRouteTime
// 	float tm = GetShortestRouteTime(start_node_, depots_[0]);
// 	float dst = GetShortestRouteLength(start_node_, depots_[0]);
// 	printf("\nStart Node - Depot time and distance (%.2f, %.2f)\n", tm, dst);

	//populate depot_startnode_time_ and depot_startnode_dist_
	for(int i = 0; i < depots_.size(); i++) {
		float tm = GetShortestRouteTime(start_node_, depots_[i]);
		float dst = GetShortestRouteLength(start_node_, depots_[i]);
		depot_startnode_time_.push_back(tm);
		depot_startnode_dist_.push_back(dst);
	}

	//init temp data (vehicles and day)
	temp_day_ = 0;
	InitTempData();
	initialized_ = true;
}

float ORoutesGenerator::GetShortestRouteLength(int i, int j)
{
	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;
	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);

	std::vector<int>* seq = &shortest_routes_[k].Sequence();

	float res = 0.0f;
	for(int u = 1; u < seq->size(); u++) {
		tRouteInf inf;
		inf = p_graph_map_->GetRoute((*seq)[u], (*seq)[u - 1])->GetRouteInf();
		res += inf.distance_;
	}
	return res;
}

float ORoutesGenerator::GetShortestRouteTime(int i, int j)
{
	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;
	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);

	std::vector<int>* seq = &shortest_routes_[k].Sequence();

	float res = 0.0f;
	for(int u = 1; u < seq->size(); u++) {
		tRouteInf inf;
		inf = p_graph_map_->GetRoute((*seq)[u], (*seq)[u - 1])->GetRouteInf();
		res += inf.time_;
	}
	return res;
}

void ORoutesGenerator::MarkShortestRoute(int i, int j)
{
	if(i == j) {
		return;
	}
	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;
	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);

	std::vector<int>* seq = &shortest_routes_[k].Sequence();
	p_graph_map_->GetNode((*seq)[0])->Select(true);
	for(int u = 1; u < seq->size(); u++) {
		p_graph_map_->GetRoute((*seq)[u], (*seq)[u - 1])->Select(true);
	}

}

//#define MAXTIME 7.0

void ORoutesGenerator::FindRouteForOneVehicle(int vtype, int day, OVehicleRoute& route, float MAXTIME, int first_node)
{
	const float capacityvh = vehicles_[vtype].capacity_;
	float timevh = 0.0f;
	float loadvh = 0.0f;
	int node;
	if(first_node == -1) {
		node = start_node_;
	} else {
		node = first_node;
	}
	route.Sequence().push_back(node);
	std::vector<float> qdiffsv;
	std::vector<int> v_nodes_removed;//nodes added to the route in a first step, than removed (time constraints)
	const int N = p_graph_map_->GetSize();

	bool route_closed = false;

	while(loadvh < capacityvh && timevh < MAXTIME * 60.0) {
		//find closest node to the current node,..., that could be added to the route
		int indx = -1;
		float mindist;
		bool st = false;
		for(int i = 0; i < N; i++) {
			
			bool not_on_route = true;
			for(int j = 0; j < route.Sequence().size(); j++) {
				if(i == route.Sequence()[j]) {
					not_on_route = false;
					break;
				}
			}
			
			bool not_in_removed = true;
			for(int j = 0; j < v_nodes_removed.size(); j++) {
				if(i == v_nodes_removed[j]) {
					not_in_removed = false;
					break;
				}
			}

			bool not_depot = true;
			for(int j = 0; j < depots_.size(); j++) {
				if(i == depots_[j]) {
					not_depot = false;
					break;
				}
			}

			if(not_on_route && not_in_removed && not_depot && days_[i] < day && quantities_[i] > 0) {
				if(!st) {
					indx = i;
					mindist = GetShortestRouteLength(node, i);
					st = true;
				} else {
					float dist = GetShortestRouteLength(node, i);
					if(mindist > dist) {
						mindist = dist;
						indx = i;
					}
				}
			}
		}
		
		if(indx < 0) {
			break;
		} else {
			//put indx to route
			float tm1 = GetShortestRouteTime(/*node*/route.Sequence()[route.Sequence().size() - 1], indx);//time from current node to indx
			float tm2 = p_graph_map_->GetNode(indx)->GetNodeInf().waiting_time_ * 60.0;//time to wait in node indx;
			timevh += (tm1 + tm2);
			float qdff = (capacityvh - loadvh) - quantities_[indx];
			if(qdff > 0) {
				qdiffsv.push_back(quantities_[indx]);
				loadvh += quantities_[indx];
				quantities_[indx] = 0.0;	
			} else {
				qdiffsv.push_back(capacityvh - loadvh);
				quantities_[indx] -= (capacityvh - loadvh);
				loadvh = capacityvh;			
			}
			
			route.Sequence().push_back(indx);

			//find closest depot and check if can get from there to start node in time
			bool nodes_removed = false;
			do {
				float mdst = GetShortestRouteLength(indx, depots_[0]);
				int indx2 = 0;
				for(int i = 0; i < depots_.size(); i++) {
					float dst =  GetShortestRouteLength(indx, depots_[i]);
					if(mdst > dst) {
						indx2 = i;
						mdst = dst;
					}
				}
				float mtme1 = GetShortestRouteTime(indx, depots_[indx2]);//time to get to depot
				float mtme2 = p_graph_map_->GetNode(depots_[indx2])->GetNodeInf().waiting_time_ * 60.0;//time to wait at depot
				float mtme3 = depot_startnode_time_[indx2];//time from depot to start node
				//timevh += (mtme1 + mtme2 + mtme3);
				if(timevh + mtme1 + mtme2 + mtme3 > MAXTIME * 60.0){
				//if not in time back to depot, remove last added node
					//timevh -= (mtme1 + mtme2 + mtme3);
					nodes_removed = true;
					int li = route.Sequence().size() - 1;
					float rmt1 = GetShortestRouteTime(route.Sequence()[li], route.Sequence()[li - 1]);
					float rmt2 = p_graph_map_->GetNode(route.Sequence()[li])->GetNodeInf().waiting_time_ * 60.0;
					timevh -= (rmt1 + rmt2);
					float qdiff = qdiffsv[li - 1];
					loadvh -= qdiff;
					quantities_[route.Sequence()[li]] += qdiff;

					v_nodes_removed.push_back(route.Sequence()[li]);
					route.Sequence().erase(route.Sequence().begin() + li);
					qdiffsv.erase(qdiffsv.begin() + li -1);
				}
			} while(timevh > MAXTIME * 60.0);

			if(nodes_removed && route.Sequence().size() > 1) {
				//find closest depot and close the route
				int li = route.Sequence().size() - 1;
				float mdst = GetShortestRouteLength(route.Sequence()[li], depots_[0]);
				int indx2 = 0;
				for(int i = 0; i < depots_.size(); i++) {
					float dst =  GetShortestRouteLength(route.Sequence()[li], depots_[i]);
					if(mdst > dst) {
						indx2 = i;
						mdst = dst;
					}
				}
				route.Sequence().push_back(depots_[indx2]);
				route_closed = true;
				break;
			}

		}
	}

	if(route.Sequence().size() > 1) {

		if(!route_closed) {
			//find closest depot and close the route
				int li = route.Sequence().size() - 1;
				float mdst = GetShortestRouteLength(route.Sequence()[li], depots_[0]);
				int indx2 = 0;
				for(int i = 0; i < depots_.size(); i++) {
					float dst =  GetShortestRouteLength(route.Sequence()[li], depots_[i]);
					if(mdst > dst) {
						indx2 = i;
						mdst = dst;
					}
				}
				route.Sequence().push_back(depots_[indx2]);
				route_closed = true;
		}

		route.Sequence().push_back(start_node_);
		for(int i = 1; i < route.Sequence().size() - 1; i++) {
			days_[route.Sequence()[i]] = day;
		}
		route.VehicleType() = vtype;
	}
}

float ORoutesGenerator::GetRouteTime(OVehicleRoute route)
{
	float r = 0;
	for(int i = 1; i < route.Sequence().size(); i++) {
		int i1 = route.Sequence()[i - 1];
		int i2 = route.Sequence()[i];
		float t1 = GetShortestRouteTime(i1, i2);
		float t2 = p_graph_map_->GetNode(i2)->GetNodeInf().waiting_time_ * 60.0;
		r += (t1 + t2);
	}
	return r;
}

float ORoutesGenerator::GetRouteIdleTime(OVehicleRoute route)
{
	float r = 0;
	for(int i = 1; i < route.Sequence().size(); i++) {
		int i1 = route.Sequence()[i - 1];
		int i2 = route.Sequence()[i];
		float t2 = p_graph_map_->GetNode(i2)->GetNodeInf().waiting_time_ * 60.0;
		r += (t2);
	}
	return r;
}

float ORoutesGenerator::GetRouteCost(OVehicleRoute route)
{
	float r = 0.0;
	float l = GetRouteDistance(route);
	float t = GetRouteTime(route);
	float t_idle = GetRouteIdleTime(route);
	int i = route.VehicleType();
	float cost_idle = vehicles_[i].cost_gas_idle_;
	float cost_gas = vehicles_[i].cost_gas_;
	float cost_maint = vehicles_[i].cost_maint_;
	float cost_equip = vehicles_[i].cost_equip_;
	float cost_sal = vehicles_[i].cost_sal_;
	r = cost_gas * l + (t /*/ 8.0*/ / 60.0) * (cost_maint + cost_equip + cost_sal) + 
						(t_idle / 60.0) * cost_idle;
	return r;
}

float ORoutesGenerator::GetRouteDistance(OVehicleRoute route)
{
	float r = 0;
	for(int i = 1; i < route.Sequence().size(); i++) {
		int i1 = route.Sequence()[i - 1];
		int i2 = route.Sequence()[i];
		float t1 = GetShortestRouteLength(i1, i2);
		
		r += t1;
	}
	return r;
}

void ORoutesGenerator::MarkRoute(OVehicleRoute route) 
{
	
	if(route.Sequence().size() == 0) {
		return;
	}
	p_graph_map_->GetNode(route.Sequence()[0])->Select(true);
	for(int i = 1; i < route.Sequence().size(); i++) {
		int i1 = route.Sequence()[i - 1];
		int i2 = route.Sequence()[i];
		MarkShortestRoute(i1, i2);
		p_graph_map_->GetNode(i2)->Select(true);
	}
}

void ORoutesGenerator::FindLRouteForOneVehicle(int vtype, int day, OVehicleRoute& route)
{
	//MAXTIME = 7
	FindRouteForOneVehicle(vtype, day, route);
	float dt = GetRouteTime(route);
	//too short time, try to find more clients after depot visit
	if(route.Sequence().size() > 1 && dt < /*5.0*/6.0 * 60.0) {
		OVehicleRoute nroute;
		int li = route.Sequence().size() - 1;
		int first_node = route.Sequence()[li - 1];
		FindRouteForOneVehicle(vtype, day, nroute, max_time_ - dt / 60.0, first_node);
		if(nroute.Sequence().size() > 1) {
			route.Sequence().erase(route.Sequence().begin() + li);
			for(int i = 1; i < nroute.Sequence().size(); i++) {
				route.Sequence().push_back(nroute.Sequence()[i]);
			}
		}
	}
}

void ORoutesGenerator::FindRoutes()
{
	for(int i = temp_day_; i < NDAYS; i++) {
// 		std::vector<int> nveh;//numbers from each vehicle type
// 		for(int j = 0; j < vehicles_.size(); j++) {
// 			nveh.push_back(vehicles_[j].number_);
// 		}

		//find routes for day "i" for each vehicle from each type
		printf("\nFind routes for day %d\n", i);
		for(int j = 0; j < temp_vehicles_.size(); j++) {
			while(temp_vehicles_[j] > 0) {
				OVehicleRoute route;
				FindLRouteForOneVehicle(j, i, route);
				if(route.Sequence().size() > 1) {
					all_routes_[i].push_back(route);
					temp_vehicles_[j] -= 1;

					MarkRoute(route);
					AddRouteToQtModel(route, i);
				} else {
					break;
				}
			}
		}
		//
		InitTempData();
		temp_day_++;
	}
}

void ORoutesGenerator::PrintRoutes(int sel)
{
	float total_dist = 0.0;
	
	std::vector<OVehicleRoute>* p_routes;
	char flname[256];
	if(sel == 0) {
		p_routes = all_routes_;
		strcpy(flname, "RuteVehicule(1).txt");
	}
	
	if(sel == 1){
		p_routes = custom_routes_;
		strcpy(flname, "RuteVehicule(2).txt");
	}
	char* daynames[5] = {
		"LUNI",
		"MARTI",
		"MIERCURI",
		"JOI",
		"VINERI"
	};
	std::fstream fl(flname, std::ios::out);
	for(int i = 0; i < NDAYS; i++) {
		fl<<daynames[i]<<std::endl;
		for(int j = 0; j < p_routes[i].size(); j++) {
			fl<<vehicles_[p_routes[i][j].VehicleType()].name_<<": ";
			for(int k = 0; k < p_routes[i][j].Sequence().size(); k++) {
				OGraphNode* nd = p_graph_map_->GetNode(p_routes[i][j].Sequence()[k]);
				fl<<nd->GetName();
				if(k < p_routes[i][j].Sequence().size() - 1) {
					fl<<" -> ";
				}
			}
			float dist = GetRouteDistance(p_routes[i][j]);
			fl<<"; Distanta "<<dist;
			total_dist += dist;
			fl<<"; Timp "<<(GetRouteTime(p_routes[i][j]) / 60.0);
			fl<<"; Cost "<<(GetRouteCost(p_routes[i][j]))<<" | "<<std::endl;
		}
	}
	fl<<"\nCantitati ramase"<<std::endl;
	for(int i = 0; i < p_graph_map_->GetSize(); i++) {
		bool not_depot = true;
		for(int j = 0; j < depots_.size(); j++) {
			if(i == depots_[j]) {
				not_depot = false;
				break;
			}
		}
		if(not_depot && i != start_node_) {
			fl<<i<<". "<<p_graph_map_->GetNode(i)->GetName()<<"   "<<quantities_[i];
			fl<<"  ("<<p_graph_map_->GetNode(i)->GetNodeInf().quantity_<<")";
			fl<<"  ("<<days_[i]<<")"<<std::endl;
		}
	}
	fl<<"\n Distanta totala "<<total_dist<<std::endl;
	fl.close();
}

using namespace rapidxml;

xml_node<>* AllocateCellNode(xml_document<>& doc, const char* str_data, int index = 0)
{
	int str_size = strlen(str_data) + 1;
	char* alloc_str_data = doc.allocate_string(str_data, str_size);
	xml_node<>* cell_node = doc.allocate_node(node_element, "Cell");
	xml_node<>* cell_data = doc.allocate_node(node_element, "Data", alloc_str_data);
	xml_attribute<char>* cell_attr = doc.allocate_attribute("ss:Type", "String", 7, 6);
	cell_data->append_attribute(cell_attr);
	if(index > 0) {
		char str_idx[4];
		sprintf(str_idx, "%d", index);
		char* alloc_str_idx = doc.allocate_string(str_idx, strlen(str_idx));
		xml_attribute<>* cell_indx_attr = doc.allocate_attribute("ss:Index", alloc_str_idx, 8, strlen(str_idx));
		cell_node->append_attribute(cell_indx_attr);
	}
	cell_node->append_node(cell_data);

	return cell_node;
}

char xml_file_header[] = "<?xml version=\"1.0\"?> \n\
						<?mso-application progid=\"Excel.Sheet\"?> \n\
						<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" \n\
						xmlns:o=\"urn:schemas-microsoft-com:office:office\" \n\
						xmlns:x=\"urn:schemas-microsoft-com:office:excel\" \n\
						xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" \n\
						xmlns:html=\"http://www.w3.org/TR/REC-html40\"> \n\
						<Worksheet ss:Name=\"Sheet1\"> \n\
						<Table >\n\
							<Column ss:AutoFitWidth=\"0\" ss:Width=\"89.25\"/>\n\
							<Column ss:AutoFitWidth=\"0\" ss:Width=\"65.25\"/>\n\
							<Column ss:AutoFitWidth=\"0\" ss:Width=\"72\"/>\n";

char xml_file_end[] = "\n</Table> \
						</Worksheet> \
						</Workbook>";
void ORoutesGenerator::PrintRoutesXml(char* filepath, int sel)
{
	char *str;
	char *str2;
	QStandardItemModel* model;
	if(sel == 0) {
		model = routesUiModel_;
	}
	if(sel == 1) {
		model = customRoutesUiModel_;
	}
	
	xml_document<> doc;
	
	//header
	xml_node<>* header = doc.allocate_node(node_element, "Row");
	header->append_node(AllocateCellNode(doc, "ZI"));
	header->append_node(AllocateCellNode(doc, "TIP VEHICUL"));
	header->append_node(AllocateCellNode(doc, "CLIENTI"));
	header->append_node(AllocateCellNode(doc, "DISTANTA"));
	header->append_node(AllocateCellNode(doc, "TIMP"));
	header->append_node(AllocateCellNode(doc, "COST"));
	doc.append_node(header);
	
	for(int i = 0; i < 6; i++) {
		doc.append_node(doc.allocate_node(node_element, "Row"));
		QStandardItem* item_day = model->itemFromIndex(model->index(i, 0));
		QStandardItem* item_day_nodes = model->itemFromIndex(model->index(i, 1));
		QStandardItem* item_day_dist = model->itemFromIndex(model->index(i, 2));
		QStandardItem* item_day_time = model->itemFromIndex(model->index(i, 3));
		QStandardItem* item_day_cost = model->itemFromIndex(model->index(i, 4));
		xml_node<>* row_day = doc.allocate_node(node_element, "Row");
		row_day->append_node(AllocateCellNode(doc, item_day->text().toAscii().data()));
		row_day->append_node(AllocateCellNode(doc, item_day_nodes->text().toAscii().data(), 3));
		row_day->append_node(AllocateCellNode(doc, item_day_dist->text().toAscii().data(), 4));
		row_day->append_node(AllocateCellNode(doc, item_day_time->text().toAscii().data(), 5));
		row_day->append_node(AllocateCellNode(doc, item_day_cost->text().toAscii().data(), 6));
		doc.append_node(row_day);

		for(int j = 0; j < item_day->rowCount(); j++) {
			QStandardItem* item_veh = item_day->child(j, 0);
			QStandardItem* item_nodes = item_day->child(j, 1);
			QStandardItem* item_dist = item_day->child(j, 2);
			QStandardItem* item_time = item_day->child(j, 3);
			QStandardItem* item_cost = item_day->child(j, 4);

			xml_node<>* row_veh = doc.allocate_node(rapidxml::node_element, "Row");
			row_veh->append_node(AllocateCellNode(doc, item_veh->text().toAscii().data(), 2));
			row_veh->append_node(AllocateCellNode(doc, item_nodes->text().toAscii().data(), 3));
			row_veh->append_node(AllocateCellNode(doc, item_dist->text().toAscii().data(), 4));
			row_veh->append_node(AllocateCellNode(doc, item_time->text().toAscii().data(), 5));
			row_veh->append_node(AllocateCellNode(doc, item_cost->text().toAscii().data(), 6));
			doc.append_node(row_veh);

			for(int k = 0; k < item_veh->rowCount(); k++) {
				QStandardItem* item_node = item_veh->child(k, 0);
				xml_node<>* row_node = doc.allocate_node(rapidxml::node_element, "Row");
				row_node->append_node(AllocateCellNode(doc, item_node->text().toUtf8().data(), 3));
				doc.append_node(row_node);
			}
		}
	}

	std::fstream fl(filepath, std::ios::out);
	fl << xml_file_header;
	fl << doc;
	fl << xml_file_end;
	fl.close();
}

void Trim(std::string& str)
{
	if(str.size() == 0) {
		return;
	}

	int i = 0;
	while(str[i] == ' ') {
		str.erase(str.begin() + i);
	}
	i = 1;
	while(str[str.size() - i] == ' ') {
		str.erase(str.end() - i);
	}
}

std::string ToLower(std::string str)
{
	std::string rstr;
	for(int i = 0; i < str.size(); i++) {
		rstr.push_back(tolower(str[i]));
	}
	return rstr;
}

void ORoutesGenerator::ParseCustomRoutesFile(char *filename)
{
	if(!initialized_) {
		return;
	}
	std::fstream fl(filename, std::ios::in);
	if(!fl.is_open()) {
		return;
	}
	std::fstream fln("Nodes.txt", std::ios::out);
	std::map<std::string, int> days;
	days["luni"] = 1;
	days["marti"] = 2;
	days["miercuri"] = 3;
	days["joi"] = 4;
	days["vineri"] = 5;

	std::map<std::string, int> nodes;
	int i = 1;
	for(int j = 0; j < p_graph_map_->GetSize(); j++) {
		nodes[ToLower(p_graph_map_->GetNode(j)->GetName())] = i;
		fln<<i<<"."<<ToLower(p_graph_map_->GetNode(j)->GetName())<<std::endl;
		i++;
	}

	while(!fl.eof()) {
		char c;
		char buffer[512];
		
		fl.getline(buffer, 512);

		//std::istrstream lbuffer(buffer, 512);
		std::istringstream lbuffer(buffer, std::istringstream::in);

		std::string wrd = "";

		OVehicleRoute route;
		int day;
		int veh_idx = -1;
		int capacity = 0;
		char s[10] = "";

		while(/*lbuffer>>c*/lbuffer.get(c)) {
			if(c != ':' && c != '-' && c != '(' && c != ')') {
				wrd.push_back(c);
			} else {
				//wrd.push_back('\0');
				Trim(wrd);
				
				if(c == ')') {
					//sscanf_s(wrd.data(), "%d%s", capacity, s);
					std::istringstream(wrd)>>capacity>>s;
					for(int i = 0; i < vehicles_.size(); i++) {
						if(capacity == vehicles_[i].capacity_) {
							veh_idx = i;
							break;;
						}
					}
					if(veh_idx >= 0) {
						route.VehicleType() = veh_idx;
					} else {
						std::cout<<"warning, unidentified vehicle type!\n";
					}
				}

				if(c == ':') {
					std::cout<<wrd<<"("<<days[ToLower(wrd)]<<")";
					day = days[ToLower(wrd)];
				}
				if(c == '-') {
					int idx = nodes[ToLower(wrd)];
					std::cout<<wrd<<"("<<idx<<")";
					if(idx <= 0) {
						std::cout<<"(warning)";
						//add inf in qt model
						QStandardItem* item = new QStandardItem(wrd.c_str());
						unidentifiedNodesUiModel_->appendRow(item);
						//
					} else {
						route.Sequence().push_back(idx - 1);
						quantities_[idx - 1] -= capacity;
						days_[idx - 1] = day;
					}
				}
				wrd.clear();
			}
		}

		if(route.Sequence().size() > 0 && route.VehicleType() >= 0) {
			custom_routes_[day - 1].push_back(route);
			AddRouteToQtModel(route, day - 1, 1);
			MarkRoute(route);
		}
		std::cout<<std::endl;
	}
	fl.close();
	fln.close();
	//PrintRoutes(1);
}

void ORoutesGenerator::AddRouteToQtModel(OVehicleRoute& vroute, int day, int sel)
{
	QStandardItemModel* model;
	if(sel == 0) {
		model = routesUiModel_;
	}
	if(sel == 1) {
		model = customRoutesUiModel_;
	}
	QList<QStandardItem*> itemList;
	int vehtype = vroute.VehicleType();
	int nodes = vroute.Sequence().size();

	float distance = GetRouteDistance(vroute);
	float vtime = GetRouteTime(vroute);

	QStandardItem* item_vehtype;
	if(vehtype >= 0) {
		item_vehtype = new QStandardItem(vehicles_[vehtype].name_);
	} else {
		item_vehtype = new QStandardItem("unidentified");
	}
	for(int i = 0; i < vroute.Sequence().size(); i++)
	{
		QStandardItem* item_node = new QStandardItem();
		int idx = vroute.Sequence()[i];
		item_node->setText(p_graph_map_->GetNode(idx)->GetName());
		item_vehtype->appendRow(item_node);
	}
	itemList.append(item_vehtype);

	QStandardItem* item_nodes = new QStandardItem(QString("%1").arg(nodes));
	itemList.append(item_nodes);
	
	itemList.append(new QStandardItem(QString("%1").arg(distance)));
	itemList.append(new QStandardItem(QString("%1").arg(vtime / 60.0)));

	float cost = 0.0;
	if(vehtype >= 0) {
		cost = GetRouteCost(vroute);
	}
	itemList.append(new QStandardItem(QString("%1").arg(cost)));

	QModelIndex index = model->index(day, 0);
	QStandardItem* item = model->itemFromIndex(index);
	item->appendRow(itemList);

	if(sel == 0) {
		nodes_[day] += nodes;
		distance_[day] += distance;
		time_[day] += vtime / 60.0;
		cost_[day] += cost;
	} else {
		cnodes_[day] += nodes;
		cdistance_[day] += distance;
		ctime_[day] += vtime / 60.0;
		ncost_[day] += cost;
	}

	index = model->index(day, 1);
	item = model->itemFromIndex(index);
	if(sel == 0) {
		item->setText(QString("%1").arg(nodes_[day]));
	} else {
		item->setText(QString("%1").arg(cnodes_[day]));
	}
	
	index = model->index(day, 2);
	item = model->itemFromIndex(index);
	if(sel == 0) {
		item->setText(QString("%1").arg(distance_[day]));
	} else {
		item->setText(QString("%1").arg(cdistance_[day]));
	}
	index = model->index(day, 3);
	item = model->itemFromIndex(index);
	if(sel == 0) {
		item->setText(QString("%1").arg(time_[day]));
	} else {
		item->setText(QString("%1").arg(ctime_[day]));
	}
	index = model->index(day, 4);
	item = model->itemFromIndex(index);
	if(sel == 0) {
		item->setText(QString("%1").arg(cost_[day]));
	} else {
		item->setText(QString("%1").arg(ncost_[day]));
	}

	int tnodes = 0;
	float tdist = 0.0;
	float ttime = 0.0;
	float tcost = 0.0;
	if(sel == 0) {
		for(int i = 0; i < 5; i++) {
			tnodes += nodes_[i];
			tdist += distance_[i];
			ttime += time_[i];
			tcost += cost_[i];
		}
	} else {
		for(int i = 0; i < 5; i++) {
			tnodes += cnodes_[i];
			tdist += cdistance_[i];
			ttime += ctime_[i];
			tcost += ncost_[i];
		}
	}
	index = model->index(5, 1);
	item = model->itemFromIndex(index);
	item->setText(QString("%1").arg(tnodes));
	index = model->index(5, 2);
	item = model->itemFromIndex(index);
	item->setText(QString("%1").arg(tdist));
	index = model->index(5, 3);
	item = model->itemFromIndex(index);
	item->setText(QString("%1").arg(ttime));
	index = model->index(5, 4);
	item = model->itemFromIndex(index);
	item->setText(QString("%1").arg(tcost));
}