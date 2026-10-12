#include "InputBaseState.h"

#include "GLCamera.h"
#include "Math/Quaternion.h"

float angle_control = 0.0f;
float power_control = 0.0f;

OInputBaseState::OInputBaseState(void)
{

}

OInputBaseState::~OInputBaseState(void)
{

}

void OInputBaseState::OnLeftClick(QPoint p, void* data)
{
	if(!data) {
		return;
	}
}

void OInputBaseState::OnMouseDrag(QPoint p, QPoint p_start, void* data)
{

	if(!data) {
		return;
	}
	
	OGL3DCamera* camera = (OGL3DCamera*)data;
	
	static QPoint point = p_start;
	if(abs(p.x() - p_start.x()) < 2 && abs(p.y() - p_start.y()) < 2) {
		point = p_start;
	}

	camera->Pitch(-(p.y() - point.y() - 0.0f));
	camera->Yaw(-(p.x() - point.x() - 0.0f));

// 	Quaternion camera_orientation = camera->GetOrientation();
// 	float pitch_val = deg2rad(p.y - point.y - 0.0f);
// 	float yaw_val = -deg2rad(p.x - point.x - 0.0f);
// 
// 	Quaternion qpitch(Vector3(1, 0, 0) * sinf(pitch_val * 0.5f), cosf(pitch_val * 0.5f));
// 	Quaternion qyaw(Vector3(0.0f, 0.0f, 1.0f) * sinf(yaw_val * 0.5f), cosf(yaw_val * 0.5f));
// 
// 	camera_orientation = camera_orientation * qyaw * qpitch;
// 	camera->SetOrientation(camera_orientation);
// 
// 	// 		DrawGLScene();

	point = p;
}

void OInputBaseState::OnMouseMove(QPoint p, void* data)
{
	if(!data) {
		return;
	}
}

// void OInputBaseState::OnRightClick(CPoint, void* data)
// {
// 	if(!data) {
// 		return;
// 	}
// }

void OInputBaseState::OnMouseWheel(short zDelta, void* data)
{
	if(!data) {
		return;
	}

	OGL3DCamera* camera = (OGL3DCamera*)data;

	const float dist = 2.0f;

// 	Vector4 persp;
// 	persp = camera->GetPerspective();

	if(zDelta > 0) {
		camera->Translate(dist);
		//camera->Roll(dist - 1);
// 		persp[2] += (dist - 1);
// 		camera->SetPerspective(persp);
	} else {
		camera->Translate(-dist);
		//camera->Roll(-dist + 1);
// 		persp[2] += (-dist + 1);
// 		camera->SetPerspective(persp);
	}
}


void OInputBaseState::OnLeftDown(QPoint, void* data)
{

}

// void OInputBaseState::OnRightDown(QPoint, void* data)
// {
// 
// }