#include "InputMapEdit.h"
#include "MapOperationsInput.h"
#include "AppMapEdit.h"

OInputMapEdit::OInputMapEdit()
{

}

OInputMapEdit::~OInputMapEdit()
{

}

void OInputMapEdit::OnLeftClick(QPoint point, void* data)
{

	MAPOPP.OnClick(point.x(), point.y());

	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

void OInputMapEdit::OnMouseDrag(QPoint point, QPoint pnt, void* data)
{
	MAPOPP.OnDrag(point.x(), point.y(), pnt.x(), pnt.y());

	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

void OInputMapEdit::OnMouseMove(QPoint point, void* data)
{
	MAPOPP.OnMove(point.x(), point.y());

	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

// void OInputMapEdit::OnRightClick(CPoint, void* data)
// {
// 	//MAPOPP.TestGenerator();
// }

void OInputMapEdit::OnMouseWheel(short, void* data)
{

}

void OInputMapEdit::OnLeftDown(QPoint, void* data)
{

}

// void OInputMapEdit::OnRightDown(CPoint, void* data)
// {
// 
// }