#pragma once

#include "Vector4.h"

class OQuaternion : public OVector4
{
public:
//constructors
	OQuaternion();
	OQuaternion(const OVector3& v, float f) : OVector4(v, f) {};
	OQuaternion(float x, float y, float z, float w) : OVector4(x, y, z, w) {};
	OQuaternion(const OVector4& v) : OVector4(v) {}; 
	OQuaternion(const OQuaternion& q) : OVector4(q) {};
	~OQuaternion();
//access functions
	OQuaternion& operator=(const OQuaternion&);
//math functions
	OQuaternion operator*(const OQuaternion&) const;
	OQuaternion Invert();
	OQuaternion Transpose();
//conversion functions
	OMatrix4x4 ToMatrix();
	void FromMatrix(const OMatrix4x4&, bool fast = false);
protected:
};
