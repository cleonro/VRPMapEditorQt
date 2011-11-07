#include "MapOperationsInput.h"

#include "../../NodeViewDialog.h"

#include "GraphAlgorithms/GraphAlgorithm.h"
#include <math.h>
#include "../AppBaseState.h"

#include <fstream>
#include <iostream>


OMapOperationsInput& OMapOperationsInput::GetInstance()
{
	static OMapOperationsInput instance;
	return instance;
}

OMapOperationsInput::OMapOperationsInput()
{
	//
	action_state_ = MAP_MOVE;

	//test
	// 	char strt[10];
	// 	int u = 0, nr = 0, k = 0;
	// 	sscanf("5 13T 45 abcdef", "%d %s %d %n", &u, strt, &nr, &k);

	Ig_ = 1;
	Jg_ = 0;
	intrrt_ = false;

	std::fstream tmpfile("temp_genroutes.txt", std::ios::in);
	int ig, jg;
	tmpfile>>ig>>jg;
	if( ig > 1 && jg > 0) {
		Ig_ = ig;
		Jg_ = jg;
		intrrt_ = true;
		//graph_.BlockArcDraw() = true;
	}
	tmpfile.close();
}

OMapOperationsInput::~OMapOperationsInput()
{
	
}

void OMapOperationsInput::Clear()
{
	//?
	Ig_ = 1;
	Jg_ = 0;
	intrrt_ = false;

	std::fstream tmpfile("temp_genroutes.txt", std::ios::in);
	int ig, jg;
	tmpfile>>ig>>jg;
	if( ig > 1 && jg > 0) {
		Ig_ = ig;
		Jg_ = jg;
		intrrt_ = true;
		//graph_.BlockArcDraw() = true;
	}
	tmpfile.close();
	//

	graph_.Clear();
	generator_.Clear();
}

void OMapOperationsInput::OnMove(int x, int y)
{
	if(selected_ == 1 && (action_state_ == MAP_ADD_ROUTE || action_state_ == MAP_NODE_CINF)) {

		//
		drawline_ = true;
		//

		double lat, longit;
		double xw, yw;
		double x0, y0;
		graph_.GetNode(index_[0])->GetCoordinates(lat, longit);
		FromLatLongToWorldCoord(lat, longit, xw, yw);
		FromWorldCoordToScreenCoord(xw, yw, x0, y0);
		line_[0] = x0;
		line_[1] = y0;
		line_[2] = x;
		line_[3] = y;
	}
}

void OMapOperationsInput::OnDrag(int nx, int ny, int ox, int oy)
{
	if(action_state_ != MAP_MOVE) {
		return;
	}

	static int rx, ry;
	if(abs(nx - ox) <= 5 && abs(ny - oy) <= 5) {
		rx = nx;
		ry = ny;
		return;
	}

	OVector4 limits = APPMNGR.GetState()->GetCamera().GetPerspective();

	float limit_x = (limits[1] - limits[0]) / 2.0;
	float limit_y = (limits[3] - limits[2]) / 2.0;

	int dx = (nx - rx);
	int dy = (ny - ry);

	translate_x_ += dx;
	translate_y_ += dy;

	rx = nx;
	ry = ny;

	if(translate_x_ >= limit_x || translate_x_ <= -limit_x) {
		translate_x_ -= dx;
		dx = 0;
	}
	if(translate_y_ >= limit_y || translate_y_ <= -limit_y) {
		translate_y_ -= dy;
		dy = 0;
	}

	double xw, yw;
	double lat, longit;
	FromScreenCoordToWorldCoord(-dx, -dy, xw, yw);
	FromWorldCoordToLatLong(xw, yw, lat, longit);
	center_latitude_ = lat;
	center_longitude_ = longit;
	FromLatLongToWorldCoord(center_latitude_, center_longitude_, center_xworld_, center_yworld_);
	//printf("\n New Center Coordinates (%.5lf, %.5lf)", center_latitude_, center_longitude_);
}

void OMapOperationsInput::OnClick(int x, int y)
{
	//
	drawline_ = false;
	//

	if(selected_ == 0 && action_state_ != MAP_MOVE) {
		graph_.UnSelectAll();
	}

	bool opf = false;//shows if an operations was done

	int i = SearchScreenCoordinatesInGraphNodes(x, y);
	//add route operation
	if(i >= 0 && (action_state_ == MAP_ADD_ROUTE || action_state_ == MAP_NODE_CINF)) {

		//node_[selected_] = graph.GetNode(i);
		//node_[selected_]->Select(true);
		graph_.GetNode(i)->Select(true);
		index_[selected_] = i;
		selected_++;
		if(selected_ == 1) {
			line_[0] = x;
			line_[1] = y;
			line_[2] = x;
			line_[3] = y;
		}
		if(selected_ == 2) {
			selected_ = 0;
			if(action_state_ == MAP_ADD_ROUTE) {
				double lat0, longit0;
				double lat, longit;
				graph_.GetNode(index_[0])->GetCoordinates(lat0, longit0);
				graph_.GetNode(index_[0])->Select(false);
				graph_.GetNode(index_[1])->GetCoordinates(lat, longit);
				graph_.GetNode(index_[1])->Select(false);

				route_ = new OGraphRoute;
				path_ = route_->GetPathAddr();

				if((index_[0] != index_[1]) && (graph_.GetRoute(index_[0], index_[1]) == NULL) 
					&& FindRoute(lat0, longit0, lat, longit)) {
						graph_.AddRoute(index_[0], index_[1], route_);
						emit mapChanged();
				}
			} else {
				std::vector<int> sequence;
				sequence.reserve(20);
				GRAPHALG.Djikstra(graph_, index_[0], index_[1], sequence);
				for(int i = 1; i < sequence.size(); i++) {
					int i1 = sequence[i - 1];
					int i2 = sequence[i];
					if(i == 1) {
						graph_.GetNode(i1)->Select(true);
					}
					graph_.GetNode(i2)->Select(true);
					graph_.GetRoute(i1, i2)->Select(true);
				}
			}

		}
	} else if((action_state_ == MAP_ADD_ROUTE || action_state_ == MAP_NODE_CINF) && selected_ == 1) {
		selected_ = 0;
		drawline_ = false;
		graph_.GetNode(index_[0])->Select(false);
	}

	//delete node operation
	if(i >= 0 && action_state_ == MAP_DEL) {

		//delete a node
		graph_.DeleteNode(i);
		emit mapChanged();
	}

	//edit node information
	if(i >=0 && action_state_ == MAP_NODE_INF) {
		node_[0] = graph_.GetNode(i);
		EditNodeInf();
	}

	//delete a connection
	if(i == -1 && action_state_ == MAP_DEL) {
		int N = graph_.GetSize();
		int j = SearchScreenCoordinatesInGraphRoutes(x, y);
		if(j != -1) {
			graph_.DeleteRoute(j);
			emit mapChanged();
			return;
		}
	}


	//add node operation

	if(i != -1) {
		return;
	}
	double xw, yw;
	double lat, longit;
	FromScreenCoordToWorldCoord(x, y, xw, yw);
	FromWorldCoordToLatLong(xw, yw, lat, longit);
	node_[0] = new OGraphNode;
	node_[0]->SetCoordinates(lat, longit);
	switch(action_state_) {
	case MAP_ADD_NODE_CL:
		node_[0]->SetType(OGraphNode::N_CLIENT);
		opf = true;
		break;
	case MAP_ADD_NODE_ST:
		node_[0]->SetType(OGraphNode::N_START);
		opf = true;
		break;
	case MAP_ADD_NODE_DP:
		node_[0]->SetType(OGraphNode::N_DEPOT);
		opf = true;
		break;
	case MAP_ADD_NODE_TR:
		node_[0]->SetType(OGraphNode::N_TRANSIT);
		opf = true;
		break;
	default:
		break;
	}
	if(opf) {
		graph_.AddNode(node_[0]);
		emit mapChanged();
		return;
	}
}

void OMapOperationsInput::EditNodeInf()
{
	CNodeViewDialog node_dialog;
	char nvtype[20];

	OGraphNode::eNodeType ntype = node_[0]->GetType();
	switch(ntype) {
	case OGraphNode::N_CLIENT:
		strcpy_s(nvtype, "Client");
		break;
	case OGraphNode::N_START:
		strcpy_s(nvtype, "Punct Pornire");
		break;
	case OGraphNode::N_DEPOT:
		strcpy_s(nvtype, "Depozit");
		break;
	case OGraphNode::N_TRANSIT:
		strcpy_s(nvtype, "ST Transfer");
		break;
	}

	node_dialog.mType = nvtype;

	tNodeInf node_info = node_[0]->GetNodeInf();

	node_dialog.mName = node_[0]->GetName();
	node_dialog.mTime =  node_info.waiting_time_;
	node_dialog.mQuantity = node_info.quantity_;
	node_dialog.mVehicles = node_[0]->Vehicles();

	node_dialog.mAccessibility = node_[0]->Accesibility();
	node_dialog.mHabitants = node_[0]->Locals();
	node_dialog.mContracts = node_[0]->Contracts();
	node_dialog.mPrice = node_[0]->Price();

	node_dialog.DataExchange(true);

	if(node_dialog.exec() == QDialog::Accepted) {
		node_dialog.DataExchange(false);
		strncpy(node_[0]->GetName(), node_dialog.mName.toAscii().data(), 19);

		node_info.quantity_ = node_dialog.mQuantity;
		node_info.waiting_time_ = node_dialog.mTime;

		node_[0]->SetNodeInf(node_info);

		strncpy(node_[0]->Vehicles(), node_dialog.mVehicles.toAscii().data(), 200);

		node_[0]->Accesibility() = node_dialog.mAccessibility;
		node_[0]->Locals() = node_dialog.mHabitants;
		node_[0]->Contracts() = node_dialog.mContracts;
		node_[0]->Price() = node_dialog.mPrice;
		emit mapChanged();
	}
}

void OMapOperationsInput::Zoom(int nzoom) {
	zoom_ = nzoom;
	GetImageFromGoogle();
}

#define FRAC 2.0

void OMapOperationsInput::ScrollX(bool left)
{
	double dxworld = 2.0 * M_PI / pow(2.0, zoom_ - 1.0);
	double dep = dxworld / FRAC;
	if(left) {
		center_xworld_ -= dep;
	} else {
		center_xworld_ += dep;
	}
	FromWorldCoordToLatLong(center_xworld_, center_yworld_, center_latitude_, center_longitude_);
	FromLatLongToWorldCoord(center_latitude_, center_longitude_, center_xworld_, center_yworld_);

	GetImageFromGoogle();
}

void OMapOperationsInput::ScrollY(bool down)
{
	double dyworld = 2.0 * M_PI / pow(2.0, zoom_ - 1.0);
	double dep = dyworld / FRAC;
	if(down) {
		center_yworld_ -= dep;
	} else {
		center_yworld_ += dep;
	}
	FromWorldCoordToLatLong(center_xworld_, center_yworld_, center_latitude_, center_longitude_);
	FromLatLongToWorldCoord(center_latitude_, center_longitude_, center_xworld_, center_yworld_);

	GetImageFromGoogle();
}

void OMapOperationsInput::GenerateRoutes()
{
	graph_.BlockArcDraw() = true;

	int N = graph_.GetSize();

	//first, delete all exist routes
	access_blocked_ = true;//block access to resources for other functions
	for(int i = 0; i < N * (N - 1) / 2; i++) {
		if(intrrt_) {
			break;
		}
		graph_.DeleteRoute(i);
	}
	access_blocked_ = false;

	//generate all posible routes
	printf("\nGENERATE ROUTES -> all possible routes (%d)\n", N);
	int ist;
	if(intrrt_) {
		ist = Ig_;
	} else {
		ist = 1;
	}
	bool ft = true;
	for(int i = ist; i < N; i++) {
		int jst = i - 1;
		if(ft) {
			ft = false;
			if(intrrt_) {
				jst = Jg_;
			}
		}

		for(int j = jst; j >=0; j--) {
			printf("\n add route (%d, %d)", i, j);
			route_ = new OGraphRoute;
			path_ = route_->GetPathAddr();
			graph_.GetNode(i)->Select(true);
			graph_.GetNode(j)->Select(true);
			if(FindRoute(i, j)) {
				graph_.AddRoute(i, j, route_);
			} else {
				intrrt_ = true;
				Ig_ = i;
				Jg_ = j;
				printf("\nGenerateRoutes() interrupted at (%d, %d). Try again later...\n", Ig_, Jg_);

				std::fstream tmpfile("temp_genroutes.txt", std::ios::out);
				tmpfile<<Ig_<<" "<<Jg_;
				tmpfile.close();

				//graph_.BlockArcDraw() = false;

				return;
			}
			Sleep(250);
			graph_.GetNode(i)->Select(false);
			graph_.GetNode(j)->Select(false);
		}
	}

	//delete "unnecessary routes"
	access_blocked_ = true;
	printf("\nGENERATE ROUTES -> delete unnecessary routes (%d)\n", N);
	const double err = 0.05;// 5/100 relative error
	for(int i = 1; i < N; i++) {
		for(int j = i - 1; j >= 0; j--) {

			printf("\n check route (%d, %d)", i, j);
			graph_.GetNode(i)->Select(true);
			graph_.GetNode(j)->Select(true);

			route_ = graph_.GetRoute(i, j);

			if(route_ == NULL) {
				continue;
			}

			graph_.AddRoute(i, j, NULL, false);
			
			std::vector<int> sequence;
			sequence.reserve(20);
			GRAPHALG.Djikstra(graph_, i, j, sequence);
			double d1 = route_->GetRouteInf().distance_;
			double d2 = 0.0;
			for(int k = 1; k < sequence.size(); k++) {
				int i1 = sequence[k - 1];
				int i2 = sequence[k];
				d2 += graph_.GetRoute(i1, i2)->GetRouteInf().distance_;
			}
			if(fabs((d1 - d2) / d1) < err) {
				//graph_.DeleteRoute(i, j);
				printf("  delete directe route...");
				delete route_;
				graph_.GetNode(i)->Select(false);
				graph_.GetNode(j)->Select(false);
			} else {
				printf("  keep directe route...");
				if(route_ != NULL) {
					route_->Select(true);
				}
				graph_.AddRoute(i, j, route_, false);
			}

// 			graph_.GetNode(i)->Select(false);
// 			graph_.GetNode(j)->Select(false);
		}
	}
	access_blocked_ = false;

	graph_.BlockArcDraw() = false;
}

void OMapOperationsInput::SetMapType(char mtp[])
{
	strncpy(maptype_, mtp, 10);
	GetImageFromGoogle();
}

void OMapOperationsInput::TestGenerator()
{
	printf("\nTest Custom Routes...\n");
	generator_.Init(graph_);
	generator_.ParseCustomRoutesFile("Rute_existente.txt");
	//return;
	generator_.InitDaysQuantities();
	generator_.FindRoutes();
	generator_.PrintRoutes();
}

void OMapOperationsInput::FindNode(const char* name, int index)
{
	OGraphNode* node;
	for(int i = 0; i < graph_.GetSize(); i++) {
		node = graph_.GetNode(i);
		
		if(index >= 0 && index == i) {
			node->Select(true);
		} else {
			if(strcmp(name, node->GetName()) == 0) {
				node->Select(true);
			}
		}
	}
}