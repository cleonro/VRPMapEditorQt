#pragma once

#include "../Utils/math_utils.h"

class OVector3
{
	friend class OMatrix4x4;
public:
//constructors
	OVector3();
	OVector3(float, float, float);
	OVector3(const OVector3&);
	~OVector3();
//access functions
	OVector3& operator=(const OVector3&);
	float& operator[](int);
	inline float& X(){return x_;}
	inline float& Y(){return y_;}
	inline float& Z(){return z_;}
	void Print();
//math operators
	OVector3 operator+(const OVector3&) const;
	OVector3 operator-(const OVector3&) const;
	OVector3 operator*(const float&) const;
	OVector3 operator*(const OVector3&) const;
	float Dot(const OVector3&) const;
	inline float FastNorm() const{return SQRT(x_ * x_ + y_ * y_ + z_ * z_);}
	inline float Norm() const {return sqrt(x_ * x_ + y_ * y_ + z_ * z_);}
	// 1 / FastNorm
	inline float FastInvertNorm() {return RSQRT(x_ * x_ + y_ * y_ + z_ * z_);}

protected:
	//data
	union {
		struct {
			float x_;
			float y_;
			float z_;
		};
		float vec_[3];
	};
};

OVector3 operator*(const float&, const OVector3&);