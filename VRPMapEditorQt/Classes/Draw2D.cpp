#include "Draw2D.h"
#include <math.h>

ODraw2D::ODraw2D(void)
{
	hexagon_[0] = 0.0;
	hexagon_[1] = 0.0;
	for(int i = 1; i <= 6; i++) {
		hexagon_[2 * i] = cos(i * M_PI / 3.0f);
		hexagon_[2 * i + 1] = sin(i * M_PI / 3.0f);
	}
	hexagon_[14] = hexagon_[2];
	hexagon_[15] = hexagon_[3];

	square_[0] = 0.0;
	square_[1] = 0.0;
	for(int i = 1; i <= 4; i++) {
		square_[2 * i] = cos(M_PI / 4.0f + i * M_PI / 2.0f);
		square_[2 * i + 1] = sin(M_PI / 4.0f + i * M_PI / 2.0f);
	}
	square_[10] = square_[2];
	square_[11] = square_[3];

	triangle_[0] = 0.0;
	triangle_[1] = 0.0;
	for(int i = 1; i <= 3; i++) {
		triangle_[2 * i] = cos(M_PI / 2.0f + i * 2.0f * M_PI / 3.0f);
		triangle_[2 * i + 1] = sin(M_PI / 2.0f + i * 2.0f * M_PI / 3.0f);
	}
	triangle_[8] = triangle_[2];
	triangle_[9] = triangle_[3];

	circle_[0] = 0.0;
	circle_[1] = 0.0;
	for(int i = 1; i <= 20; i++) {
		circle_[2 * i] = cos(i * 2.0f * M_PI / 20.0f);
		circle_[2 * i + 1] = sin(i * 2.0f * M_PI / 20.0f);
	}
	circle_[42] = circle_[2];
	circle_[43] = circle_[3];

	r_ = 1.0f;
	g_ = 1.0f;
	b_ = 1.0f;
}

ODraw2D::~ODraw2D(void)
{

}

ODraw2D& ODraw2D::GetInstance()
{
	static ODraw2D instance;
	return instance;
}

void ODraw2D::SetColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

void ODraw2D::DrawPoly(float x, float y, float r, float angle, ePolyType type)
{
	GLfloat* polygon;
	int sz;

	switch(type) {
		case HEXAGON:
			polygon = hexagon_;
			sz = 6;
			break;
		case SQUARE:
			polygon = square_;
			sz = 4;
			break;
		case TRIANGLE:
			polygon = triangle_;
			sz = 3;
			break;
		case CIRCLE:
			polygon = circle_;
			sz = 20;
			break;
	}

	glPushMatrix();
	glColor4f(r_, g_, b_, a_);
	glTranslatef(x, y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(r, r, 1.0f);

	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, polygon + 2);
	glDrawArrays(GL_LINE_STRIP, 0, sz + 1);
	glEnable(GL_TEXTURE_2D);

	glPopMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void ODraw2D::FillPoly(float x, float y, float r, float angle, ePolyType type)
{
	GLfloat* polygon;
	int sz;

	switch(type) {
	case HEXAGON:
		polygon = hexagon_;
		sz = 6;
		break;
	case SQUARE:
		polygon = square_;
		sz = 4;
		break;
	case TRIANGLE:
		polygon = triangle_;
		sz = 3;
		break;
	case CIRCLE:
		polygon = circle_;
		sz = 20;
		break;
	}

	glPushMatrix();
	glColor4f(r_, g_, b_, a_);
	glTranslatef(x, y, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glScalef(r, r, 1.0f);

	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, polygon);
	glDrawArrays(GL_TRIANGLE_FAN, 0, sz + 2);
	glEnable(GL_TEXTURE_2D);

	glPopMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void ODraw2D::DrawLine(float x0, float y0, float x1, float y1, float width)
{
	glColor4f(r_, g_, b_, a_);
	glLineWidth(width);

	float coord[] = {
		x0, y0,
		x1, y1
	};

	glDisable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, coord);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glEnable(GL_TEXTURE_2D);

	glLineWidth(1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

//utils
float ODraw2D::DistanceFromPointToSegment(float x, float y, float x1, float y1, float x2, float y2)
{
	float r;

	float nx = x2 - x1;
	float ny = y2 - y1;
	float l = sqrt(nx * nx + ny * ny);
	nx /= l;
	ny /= l;
	float pr = (x - x1) * nx + (y - y1) * ny;
	if(pr < 0) {
		float d1 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
		return d1;
	} else if(pr > l){
		float d2 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
		return d2;
	}

	r = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y) - pr * pr);

	return r;
}