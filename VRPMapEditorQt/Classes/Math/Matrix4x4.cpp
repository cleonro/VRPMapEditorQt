//#include "StdAfx.h"
#include "Matrix4x4.h"

#include "Vector3.h"
#include "Vector4.h"
#include <stdio.h>

OMatrix4x4::OMatrix4x4()
{
	for(int i = 0; i < 16; i++) {
		m_[i] = 0.0f;
	}
}

OMatrix4x4::OMatrix4x4(float m[4][4])
{
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
#ifdef COLUMN_MAJOR
			matrix_[i][j] = m[j][i];
#else
			matrix_[i][j] = m[i][j];
#endif
		}
	}
}

OMatrix4x4::OMatrix4x4(const OMatrix4x4& m)
{
	for(int i = 0; i < 16; i++) {
		m_[i] = m.m_[i];
	}
}

//construct matrix from 4 columns
OMatrix4x4::OMatrix4x4(const OVector4& v0, const OVector4& v1, const OVector4& v2, const OVector4& v3)
{
	for(int i = 0; i < 4; i++) {
#ifdef COLUMN_MAJOR
		matrix_[0][i] = v0.vec_[i];
		matrix_[1][i] = v1.vec_[i];
		matrix_[2][i] = v2.vec_[i];
		matrix_[3][i] = v3.vec_[i];
#else
		matrix_[i][0] = v0.vec_[i];
		matrix_[i][1] = v1.vec_[i];
		matrix_[i][2] = v2.vec_[i];
		matrix_[i][3] = v3.vec_[i];
#endif
	}
}

OMatrix4x4::~OMatrix4x4()
{

}

float& OMatrix4x4::operator()(int i, int j)
{
	i = (i < 0) ? 0 : (i > 3 ? 3 : i);
	j = (j < 0) ? 0 : (j > 3 ? 3 : j);
#ifdef COLUMN_MAJOR
	return m_[i + j * 4];
#else
	return m_[i * 4 + j];
#endif
}

OMatrix4x4& OMatrix4x4::operator=(const OMatrix4x4& m)
{
	for(int i = 0; i < 16; i++) {
		m_[i] = m.m_[i];
	}
	return *this;
}

OMatrix4x4 OMatrix4x4::operator*(const OMatrix4x4& m) const
{
	OMatrix4x4 r;
	r.m00_ = m00_ * m.m00_ + m01_ * m.m10_ + m02_ * m.m20_ + m03_ * m.m30_;
	r.m01_ = m00_ * m.m01_ + m01_ * m.m11_ + m02_ * m.m21_ + m03_ * m.m31_;
	r.m02_ = m00_ * m.m02_ + m01_ * m.m12_ + m02_ * m.m22_ + m03_ * m.m32_;
	r.m03_ = m00_ * m.m03_ + m01_ * m.m13_ + m02_ * m.m23_ + m03_ * m.m33_;

	r.m10_ = m10_ * m.m00_ + m11_ * m.m10_ + m12_ * m.m20_ + m13_ * m.m30_;
	r.m11_ = m10_ * m.m01_ + m11_ * m.m11_ + m12_ * m.m21_ + m13_ * m.m31_;
	r.m12_ = m10_ * m.m02_ + m11_ * m.m12_ + m12_ * m.m22_ + m13_ * m.m32_;
	r.m13_ = m10_ * m.m03_ + m11_ * m.m13_ + m12_ * m.m23_ + m13_ * m.m33_;

	r.m20_ = m20_ * m.m00_ + m21_ * m.m10_ + m22_ * m.m20_ + m23_ * m.m30_;
	r.m21_ = m20_ * m.m01_ + m21_ * m.m11_ + m22_ * m.m21_ + m23_ * m.m31_;
	r.m22_ = m20_ * m.m02_ + m21_ * m.m12_ + m22_ * m.m22_ + m23_ * m.m32_;
	r.m23_ = m20_ * m.m03_ + m21_ * m.m13_ + m22_ * m.m23_ + m23_ * m.m33_;

	r.m30_ = m30_ * m.m00_ + m31_ * m.m10_ + m32_ * m.m20_ + m33_ * m.m30_;
	r.m31_ = m30_ * m.m01_ + m31_ * m.m11_ + m32_ * m.m21_ + m33_ * m.m31_;
	r.m32_ = m30_ * m.m02_ + m31_ * m.m12_ + m32_ * m.m22_ + m33_ * m.m32_;
	r.m33_ = m30_ * m.m03_ + m31_ * m.m13_ + m32_ * m.m23_ + m33_ * m.m33_;

	return r;
}

OVector4 OMatrix4x4::operator*(const OVector4& v) const
{
	OVector4 r;
	r.vec_[0] = m00_ * v.vec_[0] + m01_ * v.vec_[1] + m02_ * v.vec_[2] + m03_ * v.vec_[3];
	r.vec_[1] = m10_ * v.vec_[0] + m11_ * v.vec_[1] + m12_ * v.vec_[2] + m13_ * v.vec_[3];
	r.vec_[2] = m20_ * v.vec_[0] + m21_ * v.vec_[1] + m22_ * v.vec_[2] + m23_ * v.vec_[3];
	r.vec_[3] = m30_ * v.vec_[0] + m31_ * v.vec_[1] + m32_ * v.vec_[2] + m33_ * v.vec_[3];
	return r;
}

OMatrix4x4 OMatrix4x4::operator*(const float&m) const
{
	OMatrix4x4 r;
	for(int i = 0; i < 16; i++) {
		r.m_[i] = m * m_[i];
	}
	return r;
}

OMatrix4x4 operator*(const float& f, const OMatrix4x4& m)
{
	OMatrix4x4 r;
	r = m * f;
	return r;
}

float OMatrix4x4::Det()
{
	float det;
	det = m03_ * m12_ * m21_ * m30_ - m02_ * m13_ * m21_ * m30_ - m03_ * m11_ * m22_ * m30_ + m01_ * m13_ * m22_ * m30_ +
		  m02_ * m11_ * m23_ * m30_ - m01_ * m12_ * m23_ * m30_ - m03_ * m12_ * m20_ * m31_ + m02_ * m13_ * m20_ * m31_ +
		  m03_ * m10_ * m22_ * m31_ - m00_ * m13_ * m22_ * m31_ - m02_ * m10_ * m23_ * m31_ + m00_ * m12_ * m23_ * m31_ +
		  m03_ * m11_ * m20_ * m32_ - m01_ * m13_ * m20_ * m32_ - m03_ * m10_ * m21_ * m32_ + m00_ * m13_ * m21_ * m32_ +
		  m01_ * m10_ * m23_ * m32_ - m00_ * m11_ * m23_ * m32_ - m02_ * m11_ * m20_ * m33_ + m01_ * m12_ * m20_ * m33_ +
		  m02_ * m10_ * m21_ * m33_ - m00_ * m12_ * m21_ * m33_ - m01_ * m10_ * m22_ * m33_ + m00_ * m11_ * m22_ * m33_;
	return det;
}

OMatrix4x4 OMatrix4x4::Invert()
{
	OMatrix4x4 r;
	r.m00_ = m12_ * m23_ * m31_ - m13_ * m22_ * m31_ + m13_ * m21_ * m32_ - m11_ * m23_ * m32_ - m12_ * m21_ * m33_ + m11_ * m22_ * m33_;
	r.m01_ = m03_ * m22_ * m31_ - m02_ * m23_ * m31_ - m03_ * m21_ * m32_ + m01_ * m23_ * m32_ + m02_ * m21_ * m33_ - m01_ * m22_ * m33_;
	r.m02_ = m02_ * m13_ * m31_ - m03_ * m12_ * m31_ + m03_ * m11_ * m32_ - m01_ * m13_ * m32_ - m02_ * m11_ * m33_ + m01_ * m12_ * m33_;
	r.m03_ = m03_ * m12_ * m21_ - m02_ * m13_ * m21_ - m03_ * m11_ * m22_ + m01_ * m13_ * m22_ + m02_ * m11_ * m23_ - m01_ * m12_ * m23_;
	r.m10_ = m13_ * m22_ * m30_ - m12_ * m23_ * m30_ - m13_ * m20_ * m32_ + m10_ * m23_ * m32_ + m12_ * m20_ * m33_ - m10_ * m22_ * m33_;
	r.m11_ = m02_ * m23_ * m30_ - m03_ * m22_ * m30_ + m03_ * m20_ * m32_ - m00_ * m23_ * m32_ - m02_ * m20_ * m33_ + m00_ * m22_ * m33_;
	r.m12_ = m03_ * m12_ * m30_ - m02_ * m13_ * m30_ - m03_ * m10_ * m32_ + m00_ * m13_ * m32_ + m02_ * m10_ * m33_ - m00_ * m12_ * m33_;
	r.m13_ = m02_ * m13_ * m20_ - m03_ * m12_ * m20_ + m03_ * m10_ * m22_ - m00_ * m13_ * m22_ - m02_ * m10_ * m23_ + m00_ * m12_ * m23_;
	r.m20_ = m11_ * m23_ * m30_ - m13_ * m21_ * m30_ + m13_ * m20_ * m31_ - m10_ * m23_ * m31_ - m11_ * m20_ * m33_ + m10_ * m21_ * m33_;
	r.m21_ = m03_ * m21_ * m30_ - m01_ * m23_ * m30_ - m03_ * m20_ * m31_ + m00_ * m23_ * m31_ + m01_ * m20_ * m33_ - m00_ * m21_ * m33_;
	r.m22_ = m01_ * m13_ * m30_ - m03_ * m11_ * m30_ + m03_ * m10_ * m31_ - m00_ * m13_ * m31_ - m01_ * m10_ * m33_ + m00_ * m11_ * m33_;
	r.m23_ = m03_ * m11_ * m20_ - m01_ * m13_ * m20_ - m03_ * m10_ * m21_ + m00_ * m13_ * m21_ + m01_ * m10_ * m23_ - m00_ * m11_ * m23_;
	r.m30_ = m12_ * m21_ * m30_ - m11_ * m22_ * m30_ - m12_ * m20_ * m31_ + m10_ * m22_ * m31_ + m11_ * m20_ * m32_ - m10_ * m21_ * m32_;
	r.m31_ = m01_ * m22_ * m30_ - m02_ * m21_ * m30_ + m02_ * m20_ * m31_ - m00_ * m22_ * m31_ - m01_ * m20_ * m32_ + m00_ * m21_ * m32_;
	r.m32_ = m02_ * m11_ * m30_ - m01_ * m12_ * m30_ - m02_ * m10_ * m31_ + m00_ * m12_ * m31_ + m01_ * m10_ * m32_ - m00_ * m11_ * m32_;
	r.m33_ = m01_ * m12_ * m20_ - m02_ * m11_ * m20_ + m02_ * m10_ * m21_ - m00_ * m12_ * m21_ - m01_ * m10_ * m22_ + m00_ * m11_ * m22_;


	return r * (1.0f / Det());
}

OMatrix4x4 OMatrix4x4::invert()
{
	OMatrix4x4 r;
	r.m00_ = m12_ * m23_ * m31_ - m13_ * m22_ * m31_ + m13_ * m21_ * m32_ - m11_ * m23_ * m32_ - m12_ * m21_ * m33_ + m11_ * m22_ * m33_;
	r.m01_ = m03_ * m22_ * m31_ - m02_ * m23_ * m31_ - m03_ * m21_ * m32_ + m01_ * m23_ * m32_ + m02_ * m21_ * m33_ - m01_ * m22_ * m33_;
	r.m02_ = m02_ * m13_ * m31_ - m03_ * m12_ * m31_ + m03_ * m11_ * m32_ - m01_ * m13_ * m32_ - m02_ * m11_ * m33_ + m01_ * m12_ * m33_;
	r.m03_ = m03_ * m12_ * m21_ - m02_ * m13_ * m21_ - m03_ * m11_ * m22_ + m01_ * m13_ * m22_ + m02_ * m11_ * m23_ - m01_ * m12_ * m23_;
	r.m10_ = m13_ * m22_ * m30_ - m12_ * m23_ * m30_ - m13_ * m20_ * m32_ + m10_ * m23_ * m32_ + m12_ * m20_ * m33_ - m10_ * m22_ * m33_;
	r.m11_ = m02_ * m23_ * m30_ - m03_ * m22_ * m30_ + m03_ * m20_ * m32_ - m00_ * m23_ * m32_ - m02_ * m20_ * m33_ + m00_ * m22_ * m33_;
	r.m12_ = m03_ * m12_ * m30_ - m02_ * m13_ * m30_ - m03_ * m10_ * m32_ + m00_ * m13_ * m32_ + m02_ * m10_ * m33_ - m00_ * m12_ * m33_;
	r.m13_ = m02_ * m13_ * m20_ - m03_ * m12_ * m20_ + m03_ * m10_ * m22_ - m00_ * m13_ * m22_ - m02_ * m10_ * m23_ + m00_ * m12_ * m23_;
	r.m20_ = m11_ * m23_ * m30_ - m13_ * m21_ * m30_ + m13_ * m20_ * m31_ - m10_ * m23_ * m31_ - m11_ * m20_ * m33_ + m10_ * m21_ * m33_;
	r.m21_ = m03_ * m21_ * m30_ - m01_ * m23_ * m30_ - m03_ * m20_ * m31_ + m00_ * m23_ * m31_ + m01_ * m20_ * m33_ - m00_ * m21_ * m33_;
	r.m22_ = m01_ * m13_ * m30_ - m03_ * m11_ * m30_ + m03_ * m10_ * m31_ - m00_ * m13_ * m31_ - m01_ * m10_ * m33_ + m00_ * m11_ * m33_;
	r.m23_ = m03_ * m11_ * m20_ - m01_ * m13_ * m20_ - m03_ * m10_ * m21_ + m00_ * m13_ * m21_ + m01_ * m10_ * m23_ - m00_ * m11_ * m23_;
	r.m30_ = m12_ * m21_ * m30_ - m11_ * m22_ * m30_ - m12_ * m20_ * m31_ + m10_ * m22_ * m31_ + m11_ * m20_ * m32_ - m10_ * m21_ * m32_;
	r.m31_ = m01_ * m22_ * m30_ - m02_ * m21_ * m30_ + m02_ * m20_ * m31_ - m00_ * m22_ * m31_ - m01_ * m20_ * m32_ + m00_ * m21_ * m32_;
	r.m32_ = m02_ * m11_ * m30_ - m01_ * m12_ * m30_ - m02_ * m10_ * m31_ + m00_ * m12_ * m31_ + m01_ * m10_ * m32_ - m00_ * m11_ * m32_;
	r.m33_ = m01_ * m12_ * m20_ - m02_ * m11_ * m20_ + m02_ * m10_ * m21_ - m00_ * m12_ * m21_ - m01_ * m10_ * m22_ + m00_ * m11_ * m22_;


	return r;
}

OMatrix4x4 OMatrix4x4::Transpose()
{
	OMatrix4x4 r;
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			r.matrix_[i][j] = matrix_[j][i];
		}
	}
	return r;
}

void OMatrix4x4::Print()
{
	printf("\n");

	printf("[%.2f %.2f %.2f %.2f]\n", m00_, m01_, m02_, m03_);
	printf("[%.2f %.2f %.2f %.2f]\n", m10_, m11_, m12_, m13_);
	printf("[%.2f %.2f %.2f %.2f]\n", m20_, m21_, m22_, m23_);
	printf("[%.2f %.2f %.2f %.2f]  ", m30_, m31_, m32_, m33_);

	printf("\n");
}

void OMatrix4x4::TranslationMatrix(const OVector3& pos)
{
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(i == j) 
				matrix_[i][j] = 1.0f;
			else
				matrix_[i][j] = 0.0f;
		}
	}

	m03_ = pos.vec_[0];
	m13_ = pos.vec_[1];
	m23_ = pos.vec_[2];
}

void OMatrix4x4::MakeIdentity()
{
	int i, j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 4; j++) {
			if(i == j) 
				matrix_[i][j] = 1.0f;
			else
				matrix_[i][j] = 0.0f;
		}
	}
}

void OMatrix4x4::RotationMatrix(const OVector3& axis, const float& angle)
{
	for(int i = 0; i < 16; i++) {
		m_[i] = 0.0f;
	}
	m33_ = 1.0f;
	
	const float hcos = cosf(angle / 2.0f);
	const float hsin = sinf(angle / 2.0f);

	const float h2cos = hcos * hcos;
	const float h2sin = hsin * hsin;

	m00_ = 2.0f * h2sin * axis.x_ * axis.x_ + 2.0f * h2cos - 1.0f;
	m11_ = 2.0f * h2sin * axis.y_ * axis.y_ + 2.0f * h2cos - 1.0f;
	m22_ = 2.0f * h2sin * axis.z_ * axis.z_ + 2.0f * h2cos - 1.0f;

	m01_ = 2.0f * h2sin * axis.x_ * axis.y_ - 2.0f * hsin * hcos * axis.z_;
	m10_ = 2.0f * h2sin * axis.x_ * axis.y_ + 2.0f * hsin * hcos * axis.z_;

	m02_ = 2.0f * h2sin * axis.x_ * axis.z_ + 2.0f * hsin * hcos * axis.y_;
	m20_ = 2.0f * h2sin * axis.x_ * axis.z_ - 2.0f * hsin * hcos * axis.y_;

	m12_ = 2.0f * h2sin * axis.y_ * axis.z_ - 2.0f * hsin * hcos * axis.x_;
	m21_ = 2.0f * h2sin * axis.y_ * axis.z_ + 2.0f * hsin * hcos * axis.x_;

}