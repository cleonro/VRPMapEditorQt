/*
 *  VariousObjects.cpp
 *  Dame
 *
 *  Created by Catalin Ciobirca on 3/24/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "VariousObjects.h"
#include "Utils/math_utils.h"

#include "Math/Matrix4x4.h"

OVariousObjects::OVariousObjects()
{
	
	quad [0] = -1.0f; quad[1] = -1.0f; quad[2] = 0.0f;
	quad [3] = 1.0f; quad[4] = -1.0f; quad[5] = 0.0f;
	quad [6] = -1.0f; quad[7] = 1.0f; quad[8] = 0.0f;
	quad [9] = 1.0f; quad[10] = 1.0f; quad[11] = 0.0f;

	quad_norm[0] = 0; quad_norm[1] = 0; quad_norm[2] = 1;
	quad_norm[3] = 0; quad_norm[4] = 0; quad_norm[5] = 1;
	quad_norm[6] = 0; quad_norm[7] = 0; quad_norm[8] = 1;
	quad_norm[9] = 0; quad_norm[10] = 0; quad_norm[11] = 1;

	cube[0] = -1.0f; cube[1] = -1.0f; cube[2] = 1.0f;    //0
	cube[3] = 1.0f; cube[4] = -1.0f; cube[5] = 1.0f;    //1
	cube[6] = 1.0f; cube[7] = 1.0f; cube[8] = 1.0f;    //2
	cube[9] = -1.0f; cube[10] = 1.0f; cube[11] = 1.0f;  //3
	cube[12] = -1.0f; cube[13] = 1.0f; cube[14] = -1.0f; //4
	cube[15] = 1.0f; cube[16] = 1.0f; cube[17] = -1.0f; //5
	cube[18] = 1.0f; cube[19] = -1.0f; cube[20] = -1.0f; //6
	cube[21] = -1.0f; cube[22] = -1.0f; cube[23] = -1.0f; //7
}

OVariousObjects::~OVariousObjects()
{

}

OVariousObjects* OVariousObjects::GetInstance()
{
	static OVariousObjects instance;
	return &instance;
}

void OVariousObjects::DrawCone(GLfloat height,GLfloat radius,GLint points)
{
	
	GLfloat *vertex = new GLfloat[3 * (points+1)];
	GLfloat *normals = new GLfloat[3 * (points + 1)];
	GLfloat x,y,z;
	x=0;
	y=0;
	z=height;
	vertex[0]=x;
	vertex[1]=y;
	vertex[2]=z;
	int i;
	int ind;
	for(i=1;i<=points;i++){
		z = 0;
		x = radius * cos(2 * (i-1.0f) * (GLfloat)M_PI / (points-1.0f));
		y = radius * sin(2 * (i-1.0f) * (GLfloat)M_PI / (points-1.0f));
		ind = 3 * i;
		vertex[ind] = x;
		vertex[ind + 1] = y;
		vertex[ind + 2] =z ;
	}
	
	normals[0] = 0;
	normals[1] = 0;
	normals[2] = 1;
	for(i = 1; i <= points; i++) {
		ind = 3 * i;
		normals[ind] = 0;
		normals[ind + 1] = cos(2 * (i-1.0f) * (GLfloat)M_PI / (points-1.0f));
		normals[ind + 2] = sin(2 * (i-1.0f) * (GLfloat)M_PI / (points-1.0f));
	}

	//glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0,vertex);
	glNormalPointer(GL_FLOAT, 0, normals);
	glDrawArrays(GL_TRIANGLE_FAN, 0, points+1);
	
	//glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	delete [] vertex;
	delete [] normals;
}

void OVariousObjects::DrawAxes(GLfloat size,GLfloat linewidth)
{
	//Axe de coordonate
	
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);

	glLineWidth(linewidth);
	GLfloat vx[]={
			-size, 0.0f, 0.0f,
			 size, 0.0f, 0.0f
	};
	GLfloat vy[]={
		0.0f, -size, 0.0f,
		0.0f, size, 0.0f
	};
	GLfloat vz[]={
		0.0f, 0.0f, -size,
		0.0f, 0.0f,  size
	};
	
	//x line
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glVertexPointer(3, GL_FLOAT, 0, vx);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glPushMatrix();
	glTranslatef(size,0.0f,0.0f);
	glRotatef(90.0f,0.0f,1.0f,0.0f);
	DrawCone(size/10.0f,size/50.0f,50);
	glPopMatrix();
	
	//y line
	glColor4f(0.0f,1.0f,0.0f,1.0f);
	glVertexPointer(3, GL_FLOAT, 0, vy);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glPushMatrix();
	glTranslatef(0.0f,size,0.0f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	DrawCone(size/10.0f,size/50.0f,50);
	glPopMatrix();
	
	//z line
	glColor4f(0.0f,0.0f,1.0f,1.0f);
	glVertexPointer(3, GL_FLOAT, 0, vz);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,size);
	DrawCone(size/10.0f,size/50.0f,50);
	glPopMatrix();
	
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	
	glLineWidth(1.0f);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_NORMAL_ARRAY);
}

GLfloat tex_quad[8] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f
};

void OVariousObjects::DrawHorizontalQuad(GLfloat size_x, GLfloat size_y)
{
	glDisable(GL_TEXTURE_2D);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(0.7, 0.6, 0.5, 0.7);

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glPushMatrix();
	glScalef(size_x, size_y, 1.0f);
	glColor4f( 0.25f, 0.5f, 0.9f, 0.7f );
	glVertexPointer(3, GL_FLOAT, 0, quad);
	glNormalPointer(GL_FLOAT, 0, quad_norm);
	//glTexCoordPointer(2, GL_FLOAT, 0, tex_quad);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glColor4f( 1.f, 1.f, 1.f, 1.f );
	
	glDisable(GL_BLEND);
}//

void OVariousObjects::DrawCube()
{
/*	
	GLfloat indices[] = {
			0, 1, 3, 2,
			4, 5,
			1, 6,
			0, 7,
			3, 4,
			6, 7
	};
 */
	GLushort indices[] = {
			0, 1, 2, 3, 4, 5, 2, 1, 6, 7, 0, 3, 2, 5, 6, 7, 4
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, cube);
	glColor4f(0.25f, 0.9f, 0.5f, 0.5f);
	glDrawElements(GL_LINE_STRIP, 17, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OVariousObjects::DrawHorizontalObject(GLfloat size_x, GLfloat size_y, GLfloat size_z,
						  GLfloat dist, GLfloat angle)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glPushMatrix();
	glTranslatef(dist*cos(angle), 0.0f, dist*sin(angle));
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glScalef(size_x, size_y, size_z);
	DrawCube();
	glScalef(1.f/size_x, 1.f/size_y, 1.f/size_z);
	DrawAxes( ((size_x<size_z)?size_z:size_x) + size_x / 10.0f, 1.0f);
	glPopMatrix();
	glDisableClientState(GL_VERTEX_ARRAY);
}

void OVariousObjects::DrawVector(GLfloat ox, GLfloat oy, GLfloat oz, 
								GLfloat nx, GLfloat ny, GLfloat nz, GLfloat length)
{
	GLfloat v[] = {
		ox, oy, oz,
		ox + nx*length, oy + ny*length, oz + nz*length 
	};
	GLfloat azimut = rad2deg(atan2(nx, nz));
	GLfloat elevation = -rad2deg(asin(ny));
	glVertexPointer(3, GL_FLOAT, 0, v);
	glDrawArrays(GL_LINE_STRIP, 0, 2);
	glPushMatrix();
	glTranslatef(ox + nx*length, oy + ny*length, oz + nz*length);

	glRotatef(azimut, 0.0f, 1.0f, 0.0f);
	glRotatef(elevation, 1.0f, 0.0f, 0.0f);
	
	DrawCone(length/4.0f, length/20.0f, 5);
	glPopMatrix();
}

void OVariousObjects::DrawPlaneEq(OVector3 n, float d)
{
	n = n * (n.FastInvertNorm());
	OVector3 qn = OVector3(0, 0, 1) * n;
	if (qn.FastNorm() > 0.0001) {
		qn = qn * (1.0f / qn.Norm());
	}
	float ang = acosf(n.Dot(OVector3(0, 0, 1)));
	OQuaternion q = OQuaternion(qn * sinf(ang * 0.5f), cosf(ang * 0.5f));

// 	Vector3 px = (q * Quaternion(1, 0, 0, 1) * q.Transpose()).V3();
// 	Vector3 py = (q * Quaternion(0, 1, 0, 1) * q.Transpose()).V3();

	glPushMatrix();
	glMultMatrixf(q.ToMatrix().GetSafeM());
	glTranslatef(0, 0, d);
	DrawHorizontalQuad(100, 100);
	//DrawAxes(100, 1);
	glPopMatrix();

}

void OVariousObjects::DrawTriangle(OVector3 v0, OVector3 v1, OVector3 v2)
{
	OVector3 norm = (v2 - v0) * (v1 - v0);

	OVector3 norm1(norm.X(), 0.7f * norm.Y(), 0.5f * norm.Z());
	norm1 = norm1 * (norm1.FastInvertNorm());

	OVector3 norm2(norm.X(), 0.5f * norm.Y(), 0.7f * norm.Z());
	norm2 = norm2 * (norm2.FastInvertNorm());

	GLfloat points[9] = {
		v0.X(), v0.Y(), v0.Z(),
		v1.X(), v1.Y(), v1.Z(),
		v2.X(), v2.Y(), v2.Z()
	};

	GLfloat normals[9] = {
		norm.X(), norm.Y(), norm.Z(),
		norm1.X(), norm1.Y(), norm1.Z(),
		norm2.X(), norm2.Y(), norm2.Z()
	};

	GLfloat colours[12] = {
		0.1f, 0.3f, 0.5f, 0.8f,
		0.1f, 0.5f, 0.7f, 0.8f,
		0.3f, 0.5f, 0.9f, 0.8f
	};

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	//glColor4f(0.1f, 0.1f, 0.7f, 0.7f);
	
	glEnable(GL_COLOR_MATERIAL);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, points);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(4, GL_FLOAT, 0, colours);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void OVariousObjects::DrawTriQuad(OVector3 v0, OVector3 v1, OVector3 v2, OVector3 v3)
{
	DrawTriangle(v0, v1, v2);
	DrawTriangle(v2, v3, v0);
}