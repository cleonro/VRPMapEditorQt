#ifndef _MAP_OP_INPUT_H_
#define _MAP_OP_INPUT_H_

#include "MapOperationsGraphics.h"

#include "RoutesGenerator/ORoutesGenerator.h"

#define MAPOPP (OMapOperationsInput::GetInstance())
class OMapOperationsInput : public OMapOperationsGraphics
{
	Q_OBJECT

	friend class OGraphMap;
	friend class OGraphNode;
	friend class OGraphRoute;

public:

	enum eActionState {
		MAP_MOVE,
		MAP_ADD_NODE_CL,
		MAP_ADD_NODE_ST,
		MAP_ADD_NODE_DP,
		MAP_ADD_NODE_TR,
		MAP_ADD_ROUTE,
		MAP_DEL,
		MAP_NODE_INF,
		MAP_NODE_CINF
	};

	static OMapOperationsInput& GetInstance();

	//operations
	void Zoom(int nzoom);
	void ScrollX(bool left = true);
	void ScrollY(bool down = true);

	void OnClick(int x, int y);
	void OnMove(int x, int y);
	void OnDrag(int nx, int ny, int ox, int oy);
	inline void ChangeActionState(eActionState state) {action_state_ = state;}

	void GenerateRoutes();
	void SetMapType(char mtp[]);

	//test routes generator
	//void TestGenerator();
	inline ORoutesGenerator& GetGenerator() {return generator_;}

	//find nodes with name
	void FindNode(const char* name, int indx);

	inline void MappChanged() {emit mapChanged();}

	//clear graph map and routes generator
	void Clear();

protected:
	OMapOperationsInput();
	~OMapOperationsInput();

	//operations on graphmap;
	int Ig_;
	int Jg_; //conexions geneterated until the pair (Ig, Jg)
	bool intrrt_;//shows if conectionns generations was stoped abnormally
	eActionState action_state_;

	void EditNodeInf();
	
	//Routes Generator
	ORoutesGenerator generator_;
};

#endif