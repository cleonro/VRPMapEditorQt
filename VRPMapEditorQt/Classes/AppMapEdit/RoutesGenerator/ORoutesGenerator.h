#pragma once

#include "OVehicleRoute.h"
//#include "../MapOperations.h"
#include "../GraphMap/GraphMap.h"

#include <QStandardItemModel>

struct tVehicleType
{
	char name_[10];
	float capacity_;//capacity in cube meters
	int number_;//number of vehicles of this type

	//vehicle cost
	float cost_gas_idle_; //gas cos for idle time / (hour)
	float cost_gas_;//gas cost / kilometer
	float cost_maint_;//maintenance cost / (hour)
	float cost_equip_;//equipment cost / (hour)
	float cost_sal_;//personnel sallaries cost / (hour)

};

//number of days in the plan
#define NDAYS 5

class ORoutesGenerator
{
	friend class CGenerateRoutesUi;
	friend class CVehicleCostUi;
	friend class CUiCustomRoutes;
public:
	ORoutesGenerator();
	~ORoutesGenerator();

	void Init(OGraphMap& graph_map);
	void InitDaysQuantities();
	void InitTempData();//init temp_vehicles_ and temp_day_
	int FindAvVehType();//find available vehicle type (a type with not all veh. used)
	void Clear();

public:
	void FindRouteForOneVehicle(int vtype, int day, OVehicleRoute& route, float MAXTIME = 8.0, int first_node = -1);
	void FindLRouteForOneVehicle(int vtype, int day, OVehicleRoute& route);
	//
	void FindRoutes();
	void PrintRoutes(int sel = 0);
	void PrintRoutesXml(char* filepath, int sel = 0);

	void ParseCustomRoutesFile(char *filename);
	inline QStandardItemModel* GetUiModel() {return routesUiModel_;}
	inline bool& Initialized() {return initialized_;}
	void ClearCustomRoutes();

protected:
	void DecodeVehicleTypesText(char vehicle_types[]);
	void DecodeVehicleCostsText(char vehicle_costs[]);
	void EncodeVehicleCosts(char* vehicles_costs);

	OGraphMap* p_graph_map_;//?
	bool initialized_;
	int start_node_;
	std::vector<int> depots_;//depots and transfer stations
//public:
	std::vector<tVehicleType> vehicles_;
	std::vector<int>	temp_vehicles_;//temporary  informations about veh. numbers (modified when routes are generated)
	int					temp_day_;//day for which one route is generated (one route gen. operation)
	float				max_time_;
protected:
	std::vector<OVehicleRoute> all_routes_[NDAYS];//all routes for 5 days schedule
	std::vector<OVehicleRoute> custom_routes_[NDAYS];

	//qt interface model
	QStandardItemModel* routesUiModel_;
	QStandardItemModel* customRoutesUiModel_;
	QStandardItemModel* unidentifiedNodesUiModel_;
	void SetModel(QStandardItemModel*&);

	//informations and functions necessary to find routes
	std::vector<float> quantities_;//quantities remained to be collected in each node
	std::vector<int> days_;//mark the nodes in the graph with the day for which they have a route
	std::vector<OVehicleRoute> shortest_routes_;//shortest routes (Djikstra algorithm) between each pair of points from graph map
// 	std::vector<float> shortest_routes_length_;
// 	std::vector<float> shortest_routes_time_;

	std::vector<float> depot_startnode_time_;
	std::vector<float> depot_startnode_dist_;

	float GetShortestRouteLength(int i, int j); //get the length for the shortest route between nodes (i, j)
	                                            //found with Djikstra algorithm and memorised in shortest_routes_
	float GetShortestRouteTime(int i, int j);
	float GetRouteTime(OVehicleRoute route);
	float GetRouteIdleTime(OVehicleRoute route);
	float GetRouteDistance(OVehicleRoute route);
	float GetRouteCost(OVehicleRoute route);
	void MarkShortestRoute(int i, int j);
	void MarkRoute(OVehicleRoute route);
	void AddRouteToQtModel(OVehicleRoute& vroute, int day, int sel = 0);

	//routes and custom routes information
	int nodes_[5], cnodes_[5];
	float distance_[5], cdistance_[5];
	float time_[5], ctime_[5];
	float cost_[5], ncost_[5];
};

