#include "OVehicleRoute.h"
//#include "..\MapOperationsInput.h"
//#include "..\GraphMap\GraphRoute.h"

OVehicleRoute::OVehicleRoute()
{
	vehicle_type_ = -1;//no vehicle associated to the route
}


OVehicleRoute::~OVehicleRoute()
{

}

// void OVehicleRoute::Select(bool sel)
// {
// 	for(int i = 1; i < sequence_.size(); i++) {
// 		OGraphRoute *route = MAPOPP.graph_.GetRoute(i, i-1);
// 		if(route != NULL) {
// 			route->Select(sel);
// 		}
// 	}
// }
