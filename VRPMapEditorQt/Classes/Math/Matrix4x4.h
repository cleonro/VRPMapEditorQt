#pragma once

#define COLUMN_MAJOR

//#include "Vector4.h"
class OVector4;
class OVector3;

class OMatrix4x4
{
	friend class OVector4;
public:
//constructors
	OMatrix4x4();
	OMatrix4x4(float m[4][4]);
	OMatrix4x4(const OMatrix4x4&);
	//construct matrix from 4 columns
	OMatrix4x4(const OVector4&, const OVector4&, const OVector4&, const OVector4&);
	~OMatrix4x4();
//access functions
	OMatrix4x4& operator=(const OMatrix4x4&);
	inline const float* GetSafeM() {return m_;}
	inline  float*  GetM(){return m_;}
	float& operator()(int i, int j);
	void Print();
//math functions
	OMatrix4x4 operator*(const OMatrix4x4&) const;
	OVector4 operator*(const OVector4&) const;
	OMatrix4x4 operator*(const float&) const;
	float Det();
	OMatrix4x4 Invert();
	OMatrix4x4 invert();// a * (a*) = det(a) * a^(-1)
	OMatrix4x4 Transpose();
//conversion functions
	void TranslationMatrix(const OVector3&);
	void RotationMatrix(const OVector3&, const float&);
	void MakeIdentity();
protected:
//data
	union {
		float m_[16];
		float matrix_[4][4];
#ifdef COLUMN_MAJOR
		struct{
			float m00_, m10_, m20_, m30_,
				  m01_, m11_, m21_, m31_,
				  m02_, m12_, m22_, m32_,
				  m03_, m13_, m23_, m33_;
		};
#else
		struct {
			float m00_, m01_, m02_, m03_,
				m10_, m11_, m12_, m13_,
				m20_, m21_, m22_, m23_,
				m30_, m31_, m32_, m33_;
		};
#endif
	};
};

OMatrix4x4 operator*(const float&, const OMatrix4x4&);