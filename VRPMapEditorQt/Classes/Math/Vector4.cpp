//#include "StdAfx.h"
#include "Vector4.h"

#include "Matrix4x4.h"
#include <stdio.h>

OVector4::OVector4()
{
	for(int i = 0; i < 4; i++) {
		vec_[i] = 0;
	}
}

OVector4::OVector4(float x, float y, float z, float w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}

OVector4::OVector4(const OVector3& v, float w)
{
	vec3_ = v;
	w_ = w;
}

OVector4::OVector4(const OVector4& v) 
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	w_ = v.w_;
}

OVector4::~OVector4()
{

}

OVector4& OVector4::operator=(const OVector4& v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	w_ = v.w_;
	return *this;
}

float& OVector4::operator[](int i)
{
	i = (i < 0) ? 0 : (i > 3 ? 3 : i);
	return vec_[i];
}

void OVector4::Print()
{
	printf("\n[%.2f, %.2f, %.2f, %.2f] \n", x_, y_, z_, w_);
}

OVector4 OVector4::operator+(const OVector4& v) const
{
	OVector4 r;
	r.x_ = x_ + v.x_;
	r.y_ = y_ + v.y_;
	r.z_ = z_ + v.z_;
	r.w_ = w_ + v.w_;
	return r;
}

OVector4 OVector4::operator-(const OVector4& v) const
{
	OVector4 r;
	r.x_ = x_ - v.x_;
	r.y_ = y_ - v.y_;
	r.z_ = z_ - v.z_;
	r.w_ = w_ - v.w_;
	return r;
}

OVector4 OVector4::operator*(const float& f) const
{
	OVector4 r;
	r.x_ = x_ * f;
	r.y_ = y_ * f;
	r.z_ = z_ * f;
	r.w_ = w_ * f;
	return r;
}
float OVector4::Dot(const OVector4& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_ + w_ * v.w_;
}

OVector4 operator*(const float& f, const OVector4& v)
{
	OVector4 r;
	r = v * f;
	return r;
}

OVector4 OVector4::operator*(const OMatrix4x4& m) const
{
	OVector4 r;
	r.vec_[0] = vec_[0] * m.m00_ + vec_[1] * m.m10_ + vec_[2] * m.m20_ + vec_[3] * m.m30_;
	r.vec_[1] = vec_[0] * m.m01_ + vec_[1] * m.m11_ + vec_[2] * m.m21_ + vec_[3] * m.m31_;
	r.vec_[2] = vec_[0] * m.m02_ + vec_[1] * m.m12_ + vec_[2] * m.m22_ + vec_[3] * m.m32_;
	r.vec_[3] = vec_[0] * m.m03_ + vec_[1] * m.m13_ + vec_[2] * m.m23_ + vec_[3] * m.m33_;
	return r;
}