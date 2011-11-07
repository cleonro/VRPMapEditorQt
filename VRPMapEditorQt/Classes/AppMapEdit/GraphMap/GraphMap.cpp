#include "GraphMap.h"


QDataStream& operator<<(QDataStream& ar, const OGraphMap& graphm)
{
	ar<<graphm.nodes_.size();
	//save nodes
	for(int i = 0; i < graphm.nodes_.size(); i++) {
		ar<<*(graphm.nodes_[i]);
	}
	
	//save routes
	OGraphRoute* p_route;
	for(int i = 0; i < graphm.routes_.size(); i++) {
		p_route = graphm.routes_[i];
		if(p_route == NULL) {
			ar<<0;
		} else {
			ar<<1;
			ar<<(*p_route);
		}
	}

	return ar;
}

QDataStream& operator>>(QDataStream& ar, OGraphMap& graphm)
{
	int k;
	ar>>k;
	graphm.nodes_.erase(graphm.nodes_.begin(), graphm.nodes_.end());
	graphm.routes_.erase(graphm.routes_.begin(), graphm.routes_.end());

	//load nodes
	OGraphNode* node;
	for(int i = 0; i < k; i++) {
		node = new OGraphNode;
		ar>>*node;
		graphm.nodes_.push_back(node);
	}

	//load routes
	OGraphRoute* p_route;
	int r, i, j;
	for(i = 1; i < graphm.nodes_.size(); i++) {
		for(j = 0; j < i; j++) {
			ar>>r;
			if(r == 0) {
				p_route = NULL;
				
			} else {
				p_route = new OGraphRoute;
				ar>>(*p_route);

				//
				//p_route->Select(true);
				//

			}
			graphm.routes_.push_back(p_route);
		}
	}

	return ar;
}

OGraphMap::OGraphMap()
{
	nodes_.reserve(104);
	routes_.reserve(104);

	block_arc_draw_ = false;
}


OGraphMap::~OGraphMap()
{
// 	for(int i = 0; i < nodes_.size(); i++) {
// 		if(nodes_[i] != NULL) {
// 			delete nodes_[i];
// 			nodes_[i] = NULL;
// 		}
// 	}
// 	nodes_.clear();
// 
// 	for(int i = 0; i < routes_.size(); i++) {
// 		if(routes_[i] != NULL) {
// 			delete routes_[i];
// 			routes_[i] = NULL;
// 		}
// 	}
// 	routes_.clear();
	Clear();
}

void OGraphMap::Clear()
{
	for(int i = 0; i < nodes_.size(); i++) {
		if(nodes_[i] != NULL) {
			delete nodes_[i];
			nodes_[i] = NULL;
		}
	}
	nodes_.clear();

	for(int i = 0; i < routes_.size(); i++) {
		if(routes_[i] != NULL) {
			delete routes_[i];
			routes_[i] = NULL;
		}
	}
	routes_.clear();
}

void OGraphMap::AddNode(OGraphNode* node)
{
	//add last node at position n-1
	nodes_.push_back(node);
	OGraphRoute* route = NULL;
	//for i=0,...,n-2 link nodes (n-1, i) with a "null" (no)route 
	for(int i = 0; i < (nodes_.size() - 1); i++) {
		routes_.push_back(route);
	}
}

OGraphNode* OGraphMap::GetNode(int i)
{
	if(i >= nodes_.size()) {
		return NULL;
	} else {
		return nodes_[i];
	}
}

void OGraphMap::AddRoute(int i, int j, OGraphRoute* route, bool erase)
{
	if(i == j) {
		return;
	}

	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;

	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);

	if(erase && routes_[k] != NULL) {
		delete routes_[k];
		routes_[k] = NULL;
	}

	if(route != NULL) {

		tRouteNodes route_nodes;
		route_nodes.start_node_ = nodes_[i];
		route_nodes.end_node_ = nodes_[j];
		route->SetRouteNodes(route_nodes);

	}

	routes_[k] = route;
}

OGraphRoute* OGraphMap::GetRoute(int i, int j)
{
	if(i == j) {
		return NULL;
	}

	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;
	//ig > jg
	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);

	return routes_[k];
}

OGraphRoute* OGraphMap::GetRoute(int i)
{
	if(i < routes_.size() && i >= 0) {
		return routes_[i];
	} else {
		return NULL;
	}
}

void OGraphMap::DeleteRoute(int i)
{
	if(i >= routes_.size() || i < 0) {
		return;
	}
	if(routes_[i] != NULL) {
		delete routes_[i];
		routes_[i] = NULL;
	}
}

void OGraphMap::DeleteRoute(int i, int j)
{
	if(i == j) {
		return;
	}

	int ig = (i > j) ? i : j;
	int jg = (i < j) ? i : j;
	//ig > jg
	int k = ig * (ig - 1) / 2 + (ig - 1 - jg);
	DeleteRoute(k);
}

void OGraphMap::DeleteNode(int i)
{
	if(i >= nodes_.size() || i < 0) {
		return;
	}

	int N = nodes_.size();
	//delete node
	std::vector<OGraphNode*>::iterator itn = nodes_.begin() + i;
	delete nodes_[i];
	nodes_[i] = NULL;
	nodes_.erase(itn);

	//delete node connections
	for(int j = i * (i - 1) / 2; j <= i * (i - 1) / 2 + (i - 1); j++) {
		delete routes_[j];
		routes_[j] = NULL;
	}
	std::vector<OGraphRoute*>::iterator it_start = routes_.begin() + i * (i - 1) / 2;
	std::vector<OGraphRoute*>::iterator it_end = routes_.begin() + i * (i - 1) / 2 + i;
	routes_.erase(it_start, it_end);
	int d = i;
	int k;
	for(int j = i + 1; j < N; j++) {
		k = j * (j - 1) / 2 + (j - 1 - i) - d;
		it_start = routes_.begin() + k;
		delete routes_[k];
		routes_[k] = NULL;
		routes_.erase(it_start);
		d++;
	}
}

void OGraphMap::UnSelectAll()
{
	for(int i = 0; i < nodes_.size(); i++) {
		nodes_[i]->Select(false);
	}

	for(int i = 0; i < routes_.size(); i++) {
		if(routes_[i] != NULL) {
			routes_[i]->Select(false);
		}
	}
}

void OGraphMap::Draw(float transparency, float line_width)
{
	for(int i = 0; i < nodes_.size(); i++) {
		nodes_[i]->Draw(transparency);
	}

// 	if(block_arc_draw_) {
// 		return;
// 	}

	if(!block_arc_draw_) {

		for(int i = 0; i < routes_.size(); i++) {
			if(routes_[i] != NULL && !routes_[i]->IsSelected()) {
				routes_[i]->Draw(transparency, line_width);
			}
		}

	}

	for(int i = 0; i < routes_.size(); i++) {
		if(routes_[i] != NULL && routes_[i]->IsSelected()) {
			routes_[i]->Draw(transparency, line_width);
		}
	}
}
