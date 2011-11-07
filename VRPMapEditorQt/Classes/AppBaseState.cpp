
#include "AppBaseState.h"
#include "AppMapEdit\AppMapEdit.h"
#include "Utils/draw_utils.h"

//AppBaseState

OAppBaseState::OAppBaseState()
{
	
}

OAppBaseState::~OAppBaseState()
{

}

OAppBaseState& OAppBaseState::GetInstance()
{
	static OAppBaseState base_state; 
	return base_state;
}

void* OAppBaseState::GetDataForInput()
{
	return (void*)(&camera_);
}

void OAppBaseState::Init(void *data) 
{
	float aspect = *(float*)data;
	camera_.SetPerspective(OVector4(1, 2048, 75, aspect));
	camera_.PlaceAt(OVector3(- 3 * 39, 1 * 50, 5 * 30 + 20));
	camera_.LookAt(OVector3(0, 0, 0));
		
}


void OAppBaseState::Update(void *data)
{
	camera_.SetGLModelViewMatrix();
}

void OAppBaseState::Update2(void* data)
{

}

void OAppBaseState::Draw()
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	VDraws->DrawHorizontalQuad(50, 50);
		
	char str[30];
	sprintf_s(str, 30, "Camera Roll %.2f", camera_.GetRoll());
	show_fps(1, 15, 150, 150, str);

	VDraws->DrawAxes(30.0f, 1.0f);
	
}

//AppManager
OAppManager::OAppManager()
{
	app_state_id_ = -1;
	app_state_ = NULL;
}

OAppManager::~OAppManager()
{
	app_state_id_ = -1;
	app_state_ = NULL;
}

void OAppManager::ChangeState(eAppStates state_id)
{
	switch(state_id){
		
		case APP_BASE_STATE :
			app_state_ = &(OAppBaseState::GetInstance());
			break;
		case APP_MAP_EDIT:
			app_state_ = &(OAppMapEdit::GetInstance());
		default:

			break;
	}

	app_state_id_ = state_id;
}

OAppBaseState* OAppManager::GetState()
{
	return app_state_;
}

OAppManager& OAppManager::GetInstance()
{
	static OAppManager instance;
	return instance;
}