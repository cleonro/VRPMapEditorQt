#pragma once
#include <vector>

// struct tRouteNode 
// {
// 	int i;//order of the node in graphmap
// 	bool wait_;//shows vehicle is serving(waiting) in the node,
// 	           //or is just passing by (not waiting)
// };

class OVehicleRoute
{
public:
	OVehicleRoute();
	~OVehicleRoute();
	inline std::vector</*tRouteNode*/int>& Sequence(){return sequence_;}
	inline int& VehicleType(){return vehicle_type_;}

	//void Select(bool sel = true);

protected:
	std::vector</*tRouteNode*/int> sequence_;//sequences of the graph nodes forming the route
	int vehicle_type_;//type of the vehicle assigned on the route;
					  //index in the vector of vehicle types
};

