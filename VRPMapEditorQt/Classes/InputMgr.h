#pragma once

#include "InputBaseState.h"
#include "AppMapEdit\InputMapEdit.h"
#include <QPoint>

enum eInputStates 
{
	INPUT_BASE = 0,
	INPUT_MAP_EDIT
};

//Input Manager is a singleton, so its constructor and destructor are protected

#define INPUTMGR (OInputMgr::GetInstance())

class OInputMgr
{
protected:
	OInputMgr(void);
	~OInputMgr(void);
	
	OInputBaseState *state_;
	eInputStates state_type_;

	//auxiliary informations
	bool drag_;
	QPoint pnt_;

public:
	static OInputMgr* GetInstance();
	virtual void ChangeState(eInputStates);

	virtual void OnLButtonDown(QPoint point);
	virtual void OnLButtonUp(QPoint point);
	virtual void OnMouseMove(QPoint point);
	virtual void OnMouseWheel(short zDelta, QPoint pt);
// 	virtual void OnRButtonUp(UINT nFlags, CPoint point);
// 	virtual void OnRButtonDown(UINT nFlags, CPoint point);
};
