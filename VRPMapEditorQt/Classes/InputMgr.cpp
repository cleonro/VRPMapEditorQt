#include "InputMgr.h"

#include "AppBaseState.h"

OInputMgr::OInputMgr()
{
	//state_ = NULL;
	state_ = new OInputBaseState;

	//auxiliary information, default values;
	drag_ = false;
}

OInputMgr::~OInputMgr()
{
	if(state_) {
		delete state_;
	}
}

OInputMgr* OInputMgr::GetInstance()
{
	static OInputMgr instance;
	return &instance;
}

void OInputMgr::ChangeState(eInputStates new_type)
{
	if(state_) {
		delete state_;
	}
	state_type_ = new_type;
	
	switch(state_type_) {
		case INPUT_BASE:
				state_ = new OInputBaseState;
			break;
		case INPUT_MAP_EDIT:
				state_ = new OInputMapEdit;
			break;
		default:

			break;
	}
}

//extern float power_control;

void OInputMgr::OnLButtonDown(QPoint point)
{
	drag_ = true;
	pnt_ = point;
	state_->OnLeftDown(point, APPMNGR.GetDataForInput());
// 	if( (
// 		(pnt_.x < 100 && pnt_.y > (392 - 100)) || 
// 		(pnt_.x > 174 + power_control - 10 && pnt_.x < 174 + power_control + 10 && pnt_.y > 392 - 32) 
// 		)
// 		&& state_type_ != INPUT_WHEEL) {
// 		ChangeState(INPUT_WHEEL);
// 	}

}

void OInputMgr::OnLButtonUp(QPoint point)
{
	drag_ = false;
	state_->OnLeftClick(point);
	//if(/*(pnt_.x >=100 || pnt_.y <= (392 - 100) ) && */state_type_ != INPUT_BASE) {
	//	ChangeState(INPUT_BASE);
	//	angle_control = 0.0f;
	//}
}

void OInputMgr::OnMouseMove(QPoint point)
{
	if(drag_) {
		state_->OnMouseDrag(point, pnt_, APPMNGR.GetDataForInput());
	} else {
		state_->OnMouseMove(point, APPMNGR.GetDataForInput());
	}
}

void OInputMgr::OnMouseWheel(short zDelta, QPoint pt)
{
	state_->OnMouseWheel(zDelta, APPMNGR.GetDataForInput());
}

// void OInputMgr::OnRButtonUp(UINT nFlags, CPoint point)
// {
// 	state_->OnRightClick(point, APPMNGR.GetDataForInput());
// }
// 
// void OInputMgr::OnRButtonDown(UINT nFlags, CPoint point)
// {
// 	state_->OnRightDown(point, APPMNGR.GetDataForInput());
// }