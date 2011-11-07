/*
 *  VariousObjects.h
 *  Dame
 *
 *  Created by Catalin Ciobirca on 3/24/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _VARIOUSOBJECTS_H_
#define _VARIOUSOBJECTS_H_

#include <windows.h>
//#include <afxwin.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#define VDraws OVariousObjects::GetInstance()

#include "Math/Quaternion.h"

class OVariousObjects
{
protected:
	OVariousObjects();
	~OVariousObjects();
	GLfloat quad[12];
	GLfloat quad_norm[12];
	GLfloat cube[24];
public:
	static OVariousObjects* GetInstance();
	void DrawCone(GLfloat height,GLfloat radius,GLint points);
	void DrawAxes(GLfloat size,GLfloat linewidth);
	
	void DrawHorizontalQuad(GLfloat size_x, GLfloat size_y);
	void DrawCube();
	void DrawHorizontalObject(GLfloat size_x, GLfloat size_y, GLfloat size_z,
							  GLfloat dist, GLfloat angle);

	void DrawVector(GLfloat ox, GLfloat oy, GLfloat oz, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat length);

	//new functions
	void DrawPlaneEq(OVector3 n, float d); //draws a quad, included in a plane with the normal "n" 
										  //and at distance "d" from the origin
	void DrawTriangle(OVector3 v0, OVector3 v1, OVector3 v2);
	void DrawTriQuad(OVector3 v0, OVector3 v1, OVector3 v2, OVector3 v3);
};

#endif