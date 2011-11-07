#pragma once

#include "../GraphMap/GraphMap.h"
#include <vector>

//distance infinity
#define DISTINF 1000000.0

struct tDjikstraNodeInf 
{
	float distance_;//node distance
	bool visited_;
	int previous_;//previous node index
};

#define GRAPHALG (OGraphAlgorithm::GetInstance())

class OGraphAlgorithm
{
public:
	static OGraphAlgorithm& GetInstance();

	//Djikstra algorithm; sequence - shortest path from start_index to end_index
	void Djikstra(OGraphMap& graph, int start_index, int end_index, std::vector<int>& sequence);
	
protected:
	OGraphAlgorithm();
	~OGraphAlgorithm();

	//Djikstra algorithm, auxiliary functions 
	void InitDjikstra();

	OGraphMap* p_graph_;
	std::vector<tDjikstraNodeInf> djk_node_inf_;

};

