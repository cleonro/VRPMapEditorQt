//#include "StdAfx.h"
#include "Vector3.h"
#include <stdio.h>

OVector3::OVector3()
{
	x_ = 0.0f;
	y_ = 0.0f;
	z_ = 0.0f;
}

OVector3::OVector3(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

OVector3::OVector3(const OVector3& v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
}

OVector3::~OVector3()
{

}

OVector3& OVector3::operator=(const OVector3& v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	return *this;
}

float& OVector3::operator[](int i)
{
	i = (i < 0) ? 0 : (i > 2 ? 2 : i);
	return vec_[i];
}

void OVector3::Print()
{
	printf("\n[%.2f, %.2f, %.2f] \n", x_, y_, z_);
}

OVector3 OVector3::operator+(const OVector3&v) const
{
	OVector3 r;
	for(int i = 0; i < 3; i++) {
		r.vec_[i] = vec_[i] + v.vec_[i];
	}
	return r;
}

OVector3 OVector3::operator-(const OVector3&v) const
{
	OVector3 r;
	for(int i = 0; i < 3; i++) {
		r.vec_[i] = vec_[i] - v.vec_[i];
	}
	return r;
}

OVector3 OVector3::operator*(const float& f) const
{
	OVector3 r;
	for(int i = 0; i < 3; i++) {
		r.vec_[i] = vec_[i] * f;
	}
	return r;
}

OVector3 operator*(const float& f, const OVector3& v)
{
	OVector3 r;
	r = v * f;
	return r;
}

OVector3 OVector3::operator*(const OVector3& v) const
{
	OVector3 r;
	r.x_ = y_ * v.z_ - z_ * v.y_;
	r.y_ = z_ * v.x_ - x_ * v.z_;
	r.z_ = x_ * v.y_ - y_ * v.x_;
	return r;
}

float OVector3::Dot(const OVector3& v) const
{
	float r;
	r = x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
	return r;
}
