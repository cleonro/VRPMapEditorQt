#pragma once

//#include <afxwin.h>

#include "GraphNode.h"
#include "GraphRoute.h"
#include <vector>
#include <QDataStream>

class OGraphMap
{
	friend class OGraphAlgorithm;

public:

	friend QDataStream& operator<<(QDataStream& ar, const OGraphMap& graphm);
	friend QDataStream& operator>>(QDataStream& ar, OGraphMap& graphm);

	OGraphMap();
	~OGraphMap();

	void AddNode(OGraphNode* node);
	OGraphNode* GetNode(int i);
	void AddRoute(int i, int j, OGraphRoute* route, bool erase = true);
	OGraphRoute* GetRoute(int i, int j);
	OGraphRoute* GetRoute(int i);
	inline int GetSize() {return nodes_.size();}
	void DeleteNode(int i);
	void DeleteRoute(int i);
	void DeleteRoute(int i, int j);
	void Clear();

	void UnSelectAll();
	
	void Draw(float transparency = 0.7, float line_width = 1.0);

	inline bool& BlockArcDraw() {return block_arc_draw_;}

protected:
	std::vector<OGraphNode*> nodes_;
	std::vector<OGraphRoute*> routes_;
	bool block_arc_draw_;

};

