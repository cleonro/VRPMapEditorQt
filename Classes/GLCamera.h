#pragma once

#include "Math/Matrix4x4.h"
#include "Math/Quaternion.h"

class OGL3DCamera
{
	enum eCameraType {
		LOOK_AT_CAMERA,
		FREE_CAMERA,
	};
public:
	OGL3DCamera();
	~OGL3DCamera();

//access functions
	inline OVector3& GetPosition(){return position_;}
	inline OQuaternion& GetOrientation(){return orientation_;}
	inline OMatrix4x4& GetModelView(){return modelview_matrix_;}
	inline eCameraType GetType(){return type_;}

	inline void SetPosition(const OVector3& v){position_ = v; computed_ = false;}
	inline void SetOrientation(const OQuaternion& q){orientation_ = q; computed_ = false;}
	inline void SetType(eCameraType type) {type_ = type;}

	void SetPerspective(OVector4);//the argument is Vector4(zNear, zFar, fovy, aspect)
	OVector4 GetPerspective();
	void SetGLModelViewMatrix();
	
	OVector3 GetAxesK();
	OVector3 GetAxesI();
	OVector3 GetAxesJ();

	float GetRoll();

//place and orient camera
	
	void PlaceAt(const OVector3&);
	void LookAt(const OVector3&, const float& roll = 0.0f);
	
	void Roll(const float&);
	void Pitch(const float&);
	void Yaw(const float&);
	void Translate(const float&);

//visibility

//perspective
	void SwitchToOrthoProjection(OVector4 planes_2d);//(left, right, bottom, top)
	void SwitchToPerspectiveProjection();

protected:
	void ComputeModelView();
	
protected:
//data
	OVector3 position_;
	OVector3 look_at_point_;
	OQuaternion orientation_;
	OQuaternion q_implicit;//in my app z axis is "up" axis
						  //use q_implicit to transform camera "up" (y camera) in z

	bool computed_;//shows if modelview_matrix was computed
	OMatrix4x4 modelview_matrix_;

	float zNear_;
	float zFar_;
	float fovy_;
	float aspect_;

	eCameraType type_;

	OVector4 camera2d_planes_;//(left, right, bottom, top)
	bool is2d_;
	bool camera3d_saved_;//used when changes from 2d to 3d camera, to restore 3d perspective
};
