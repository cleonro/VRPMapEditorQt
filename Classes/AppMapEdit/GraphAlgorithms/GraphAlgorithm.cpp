#include "GraphAlgorithm.h"
#include "../GraphMap/GraphRoute.h"

OGraphAlgorithm::OGraphAlgorithm()
{
	p_graph_ = NULL;
}


OGraphAlgorithm::~OGraphAlgorithm()
{

}

OGraphAlgorithm& OGraphAlgorithm::GetInstance()
{
	static OGraphAlgorithm instance;
	return instance;
}

void OGraphAlgorithm::InitDjikstra()
{
	djk_node_inf_.clear();
	djk_node_inf_.reserve(p_graph_->nodes_.size());
	tDjikstraNodeInf djknd;
	djknd.previous_ = -1;//previous node undefined
	djknd.distance_ = DISTINF;
	djknd.visited_ = false;
	for(int i = 0; i < p_graph_->nodes_.size(); i++) {
		djk_node_inf_.push_back(djknd);
	}
}

void OGraphAlgorithm::Djikstra(OGraphMap& graph, int start_index, int end_index, std::vector<int>& sequence)
{
	//init
	p_graph_ = &graph;
	InitDjikstra();
	djk_node_inf_[start_index].distance_ = 0;
	int shortest_dist_ind = start_index;
	//
	int removed = 0; //number of visited nodes
	tDjikstraNodeInf* djknode;
	while(removed < djk_node_inf_.size()) {
		djknode = &djk_node_inf_[shortest_dist_ind];
		if(djknode->distance_ == DISTINF) {
			break;
		}
		//this node is removed from the set of the nodes to be visited
		removed++;
		djknode->visited_ = true;
		//shortest path from start_index to end_index found
		if(shortest_dist_ind == end_index) {
			int indx = shortest_dist_ind;
			sequence.insert(sequence.begin(), indx);
			while(djknode->previous_ >= 0) {
				indx = djknode->previous_;
				sequence.insert(sequence.begin(), indx);
				djknode = &djk_node_inf_[indx];
			}
			break;
		}
		OGraphRoute* route;
		tRouteInf route_inf;
		//visit each neighbour of djknode in graph
		for(int i = 0; i < p_graph_->nodes_.size(); i++) {

			if(i == shortest_dist_ind) {
				continue;
			}

			route = p_graph_->GetRoute(i, shortest_dist_ind);
			
			if(route != NULL) {
				route_inf = route->GetRouteInf();
				float alt = djknode->distance_ + route_inf.distance_;
				tDjikstraNodeInf* djknode2 = &djk_node_inf_[i];
				if(alt < djknode2->distance_) {
					djknode2->distance_ = alt;
					djknode2->previous_ = shortest_dist_ind;
				}
			}
		}

		//find the shortest distance in the set of the nodes to be visited;
		float dist = DISTINF;
		int indx = 0;
		tDjikstraNodeInf djknode2;
		while(indx < djk_node_inf_.size()) {
			djknode2 = djk_node_inf_[indx];
			if(!djknode2.visited_ && dist > djknode2.distance_) {
				shortest_dist_ind = indx;
				dist = djknode2.distance_;
			}
			indx++;
		}
	}
}