//#include "StdAfx.h"
#include "Quaternion.h"
#include <cmath>
#include "Matrix4x4.h"

OQuaternion::OQuaternion()
{

}

OQuaternion::~OQuaternion()
{

}

OQuaternion& OQuaternion::operator=(const OQuaternion& q)
{
	for(int i = 0; i < 4; i++) {
		vec_[i] = q.vec_[i];
	}
	return *this;
}

OQuaternion OQuaternion::operator*(const OQuaternion& q) const
{
	OQuaternion qr;
	qr.w_ = w_ * q.w_ - V3().Dot(q.V3());
	OVector3 vector = w_ * q.V3() + q.w_ * V3() + V3() * q.V3();
    qr.X() = vector.X();
    qr.Y() = vector.Y();
    qr.Z() = vector.Z();
	return qr;
}

OQuaternion OQuaternion::Invert()
{
	OQuaternion qr(OVector4((-1.0f) * V3(), w_));
	qr = OVector4(qr) * (1.0f / OVector4(*this).Dot(OVector4(*this)));
	return qr;
}

OQuaternion OQuaternion::Transpose()
{
	OQuaternion qr(OVector4((-1.0f) * V3(), w_));
	return qr;
}

OMatrix4x4 OQuaternion::ToMatrix()
{
	OMatrix4x4 r;
	r.m00_ = 2.0f * x_ * x_ + 2.0f * w_ * w_ - 1.0f;
	r.m11_ = 2.0f * y_ * y_ + 2.0f * w_ * w_ - 1.0f;
	r.m22_ = 2.0f * z_ * z_ + 2.0f * w_ * w_ - 1.0f;
	r.m33_ = 1.0f;

	r.m01_ = 2.0f * x_ * y_ - 2.0f * w_ * z_;
	r.m10_ = 2.0f * x_ * y_ + 2.0f * w_ * z_;

	r.m02_ = 2.0f * x_ * z_ + 2.0f * w_ * y_;
	r.m20_ = 2.0f * x_ * z_ - 2.0f * w_ * y_;

	r.m12_ = 2.0f * y_ * z_ - 2.0f * w_ * x_;
	r.m21_ = 2.0f * y_ * z_ + 2.0f * w_ * x_;

	return r;
}

void OQuaternion::FromMatrix(const OMatrix4x4& m, bool fast)
{
	if(!fast)
		w_ = sqrt(fabs(m.m00_ + m.m11_ + m.m22_ + 1.0f)) / 2.0f;
	else
		w_ = SQRT(fabs(m.m00_ + m.m11_ + m.m22_ + 1.0f)) / 2.0f;

	if(w_ > /*0.0001f*/0.001f) {
		const float cw = 1.0f / (4.0f * w_);

		x_ = (m.m21_ - m.m12_) * cw;
		y_ = (m.m02_ - m.m20_) * cw;
		z_ = (m.m10_ - m.m01_) * cw;
	} else {
		x_ = sqrt((m.m00_ + 1) * 0.5f);
		y_ = sqrt((m.m11_ + 1) * 0.5f);
		z_ = sqrt((m.m22_ + 1) * 0.5f);
		if(x_ > 0.0001f) {
			y_ = std::copysign(y_, m.m01_);
			z_ = std::copysign(z_, m.m02_);
			return;
		}
		if(y_ > 0.0001f) {
			x_ = std::copysign(x_, m.m01_);
			z_ = std::copysign(z_, m.m12_);
			return;
		}
		if(z_ > 0.0001f) {
			y_ = std::copysign(y_, m.m12_);
			x_ = std::copysign(x_, m.m02_);
			return;
		}
	}
}