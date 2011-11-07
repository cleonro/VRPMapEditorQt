#pragma once

#include "..\InputBaseState.h"
#include <QPoint>

class OInputMapEdit : public OInputBaseState
{
public:
	friend class OInputMgr;
	virtual void OnLeftClick(QPoint, void* data = NULL);
	virtual void OnMouseDrag(QPoint, QPoint, void* data = NULL);
	virtual void OnMouseMove(QPoint, void* data = NULL);
	//virtual void OnRightClick(QPoint, void* data = NULL);
	virtual void OnMouseWheel(short, void* data = NULL);

	virtual void OnLeftDown(QPoint, void* data = NULL);
	//virtual void OnRightDown(QPoint, void* data = NULL);

protected:
	OInputMapEdit(void);
	~OInputMapEdit(void);
};