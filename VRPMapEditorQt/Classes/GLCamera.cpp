#include "GLCamera.h"

#include <windows.h>
//#include <afxwin.h>
#include <GL/GL.h>
#include <GL/GLU.h>

OGL3DCamera::OGL3DCamera()
{
	position_ = OVector3(0.0f, 0.0f, 0.0f);
	orientation_ = OVector4(0.0f, 0.0f, 0.0f, 1.0f);
	modelview_matrix_.MakeIdentity();

	computed_ = true;
	type_ = LOOK_AT_CAMERA;

	//in my app z axis is "up" axis
	//use q_implicit to transform camera "up" (y camera) in z
	q_implicit = OQuaternion(OVector3(1.0f, 0.0f, 0.0f) * cosf((float)M_PI / 4.0f), sinf((float)M_PI / 4.0f));

	is2d_ = false;
	camera3d_saved_ = false;
}

OGL3DCamera::~OGL3DCamera()
{
	
}

void OGL3DCamera::SwitchToOrthoProjection(OVector4 planes_2d)
{
	camera2d_planes_ = planes_2d;

	glMatrixMode(GL_PROJECTION);
	if(!is2d_) {
		glPushMatrix();
	}
	//?
	glLoadIdentity();
	//glRotatef( -90.f, 0.f, 0.f, 1.f );
	//
	glOrtho(camera2d_planes_[0], camera2d_planes_[1], 
			camera2d_planes_[2], camera2d_planes_[3], -1, 1);
	
	glMatrixMode(GL_MODELVIEW);
	if(!is2d_) {
		glPushMatrix();
	}
	glLoadIdentity();

	if(!is2d_) {
		camera3d_saved_ = true;
		is2d_ = true;
	} else {
		camera3d_saved_ = false;
	}

}

void OGL3DCamera::SwitchToPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	if(camera3d_saved_) {
		glPopMatrix();
	} else {
		glLoadIdentity();
		gluPerspective(fovy_, aspect_, zNear_, zFar_);
	}
	
	glMatrixMode(GL_MODELVIEW);
	if(camera3d_saved_) {
		glPopMatrix();
	} else {
		computed_ = false;
	}

	is2d_ = false;
}

void OGL3DCamera::SetGLModelViewMatrix()
{
	if(!computed_) {
		ComputeModelView();
	}
	glLoadMatrixf(modelview_matrix_.GetSafeM());
}

void OGL3DCamera::ComputeModelView()
{
	OMatrix4x4 translate;
	OMatrix4x4 rotate;
	//Matrix4x4 m_implicit;
	OQuaternion iq = /*q_implicit.Transpose() */ orientation_.Transpose();
	
	translate.TranslationMatrix((-1.0f) * position_);
	rotate = iq.ToMatrix();
	//m_implicit = q_implicit.Transpose().ToMatrix();

	modelview_matrix_ =  rotate * translate;
	computed_ = true;
}

float OGL3DCamera::GetRoll()
{
	const OVector3 up(0.0f, 0.0f, 1.0f);
	float roll;
	OVector3 _k = GetAxesK();
	OVector3 _in = GetAxesI();
	OVector3 _jn = GetAxesJ();

	OVector3 _i = up * _k;
	float inorm = _i.Norm();

	float x;
	float y;

	if(inorm > 0.0001) {
		_i = _i * (1.0f / _i.Norm());

		x = _in.Dot(_i);
		y = _jn.Dot(_i);
		
	} else {
		x = _in.Dot(OVector3(1.0, 0.0, 0.0));
		y = _jn.Dot(OVector3(1.0, 0.0, 0.0));
	}

	roll = -atan2f(y, x);
	roll = rad2deg(roll);

	return roll;
}

void OGL3DCamera::PlaceAt(const OVector3& p)
{
	position_ = p;
	computed_ = false;
}

void OGL3DCamera::LookAt(const OVector3 &lt, const float& roll)
{
	const OVector3 up(0.0f, 0.0f, 1.0f);
	const float rl = deg2rad(roll);

	look_at_point_ = lt;

	OVector3 _i, _j, _k;

	_k = position_ - lt;
	_k = _k * (1.0f / _k.Norm());
	
	_i = /*_k * up;/*/up * _k;
	float inorm = _i.Norm();
	
	if(inorm > 0.0001){
		_j = _k * _i;
		_i = _i * (1.0f / inorm);
		_j = _j * (1.0f / _j.Norm());
	} else {
		_i = OVector3(1, 0, 0);
		_j = OVector3(0, 1, 0) * _k[2];
	}

	if(fabs(roll) > 0.0001f) {

		OVector3 _in;
		OVector3 _jn;

		_in = _i * cosf(rl) + _j * sinf(rl);
		_jn = _i * sinf(-rl) + _j * cosf(rl);
		_i = _in;
		_j = _jn;
	} 

	//orientation matrix
	OMatrix4x4 m_orient(OVector4(_i, 0.0f), OVector4(_j, 0.0f), OVector4(_k, 0.0f), OVector4(0.0f, 0.0f, 0.0f, 1.0f));

	//printf("\nOrientation Matrix Det %.2f\n", m_orient.Det());

	orientation_.FromMatrix(m_orient);
	computed_ = false;

// 	look_at_point_ = lt;
// 	Vector3 dir = position_ - look_at_point_;
// 	dir = dir * (1.0f / dir.Norm());
// 
// 	float yaw = M_PI_2 + atan2f(dir.Y(), dir.X());
// 	float pitch = M_PI_2 - asinf(dir.Z());
// 	float sy = sinf(0.5f * yaw);
// 	float cy = cosf(0.5f * yaw);
// 	float sp = sinf(0.5f * pitch);
// 	float cp = cosf(0.5f * pitch);
// 
// 	Quaternion q_yaw(0, 0, sy, cy);
// 	Quaternion q_pitch(sp, 0, 0, cp);
// 	//Quaternion q_roll(0, sr, 0, cr);//?
// 
// 	orientation_ = q_yaw * q_pitch /* q_roll*/;
// 	computed_ = false;

}

OVector3 OGL3DCamera::GetAxesI()
{
	OVector4 _i(1.0f, 0.0f, 0.0f, 1.0f);
	_i = orientation_ * _i * orientation_.Transpose();
	return _i.V3();
}

OVector3 OGL3DCamera::GetAxesJ()
{
	OVector4 _j(0.0f, 1.0f, 0.0f, 1.0f);
	_j = orientation_ * _j * orientation_.Transpose();
	return _j.V3();
}

OVector3 OGL3DCamera::GetAxesK()
{
	OVector4 _k(0.0f, 0.0f, 1.0f, 1.0f);
	_k = orientation_ * _k * orientation_.Transpose();
	return _k.V3();
}

void OGL3DCamera::Roll(const float& roll)
{
	const float hcos = cosf(deg2rad(roll / 2.0f));
	const float hsin = sinf(deg2rad(roll / 2.0f));

	OQuaternion qroll(hsin * OVector3(0.0f, 0.0f, 1.0f), hcos);

	orientation_ = orientation_ * qroll;
	computed_ = false;
}

void OGL3DCamera::Pitch(const float& pitch)
{
	const float hcos = cosf(deg2rad(pitch / 2.0f));
	const float hsin = sinf(deg2rad(pitch / 2.0f));

	if(type_ == LOOK_AT_CAMERA) {
		OQuaternion qp_pitch(hsin * GetAxesI(), hcos);
		OQuaternion pos(position_ + (-1.0f) * look_at_point_, 1.0f);
		pos = qp_pitch * pos * qp_pitch.Transpose();
		position_ = pos.V3() + look_at_point_;
		orientation_ = qp_pitch * orientation_;
	}

	if(type_ == FREE_CAMERA) {
		OQuaternion qpitch(hsin * OVector3(1.0f, 0.0f, 0.0f), hcos);
		orientation_ = orientation_ * qpitch;
	}

	computed_ = false;
}

void OGL3DCamera::Yaw(const float& yaw)
{
	const float hcos = cosf(deg2rad(yaw / 2.0f));
	const float hsin = sinf(deg2rad(yaw / 2.0f));

	if(type_ == LOOK_AT_CAMERA) {
		OQuaternion qp_yaw(hsin * OVector3(0, 0, 1), hcos);
		OQuaternion pos(position_ + (-1.0f) * look_at_point_, 1.0f);
		pos = qp_yaw * pos * qp_yaw.Transpose();
		position_ = pos.V3() + look_at_point_;
		orientation_ = qp_yaw * orientation_;
	}

	if(type_ == FREE_CAMERA) {
		OQuaternion qyaw(hsin * OVector3(0.0f, 1.0f, 0.0f), hcos);
		orientation_ = orientation_ * qyaw;
	}

	computed_ = false;
}


void OGL3DCamera::Translate(const float& dist)
{
	OVector4 _k(0.0f, 0.0f, 1.0f, 1.0f);
	_k = orientation_ * _k * orientation_.Transpose();
	position_ = position_ + _k.V3() * (-dist);
	computed_ = false;
}

//the argument is Vector4(zNear, zFar, fovy, aspect)
void OGL3DCamera::SetPerspective(OVector4 s)
{
	zNear_ = s[0]; 
	zFar_ = s[1]; 
	fovy_ = s[2];
	aspect_ = s[3];

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy_, aspect_, zNear_, zFar_);
	glMatrixMode(GL_MODELVIEW);
}

OVector4 OGL3DCamera::GetPerspective()
{
	if(!is2d_) {
		return OVector4(zNear_, zFar_, fovy_, aspect_);
	} else {
		return camera2d_planes_;
	}
}