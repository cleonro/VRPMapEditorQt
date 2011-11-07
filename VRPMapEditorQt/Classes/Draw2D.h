#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
//#include <afxwin.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#define DRAW2D (ODraw2D::GetInstance())

enum ePolyType {
	HEXAGON,
	SQUARE,
	TRIANGLE,
	CIRCLE
};

class ODraw2D
{
public:
	static ODraw2D& GetInstance();
	void SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void DrawPoly(float x, float y, float r, float angle = 0.0f, ePolyType type = HEXAGON);//position x,y, radius r
	void FillPoly(float x, float y, float r, float angle = 0.0f, ePolyType type = HEXAGON);
	void DrawLine(float x0, float y0, float x1, float y1, float width = 1.0f);

	//utils
	float DistanceFromPointToSegment(float x, float y, float x1, float y1, float x2, float y2);

protected:

	GLfloat r_;//red
	GLfloat g_;//green
	GLfloat b_;//blue
	GLfloat a_;//alpha

	GLfloat hexagon_[12 + 4];
	GLfloat square_[8 + 4];
	GLfloat triangle_[6 + 4];
	GLfloat circle_[20 * 2 + 4];

	ODraw2D(void);
	~ODraw2D(void);
};

