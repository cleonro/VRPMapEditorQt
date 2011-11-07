#ifndef _DRAW_UTILS_H_
#define _DRAW_UTILS_H_

#include <math.h>
#include <string>
#include <direct.h>
#include <windows.h>
//#include <afxwin.h>
#include <GL/gl.h>
#include "glut.h"
#include "glext.h"


template <class T> void swp(T &a, T &b)  { T tmp=a;  a=b;  b=tmp; }
template <class T>  T t_max(T a, T b) { if (a > b) return a;  else return b; }
template <class T>  T t_max(T a, T b, T c) { if(a>b) return t_max(a,c);  else return t_max(b,c); }
template <class T>  T t_min(T a, T b) { if (a < b) return a;  else return b; }
template <class T>  T t_min(T a, T b, T c) { if(a<b) return t_min(a,c);  else return t_min(b,c); }
template <class T>  int sgn(T a) { if(a>0) return 1; else if(a<0) return -1; else return 0; }

static void saveBmp24(int w, int h) {  
	long rP, bPR=(long)w*3L;  if(bPR%4L==0L) rP=0L;  else rP=4L-(bPR%4L);  bPR+=rP;
	struct HBmp {
		long b1L; short b2S,b3S; long b4L,b5L,b6L,b7L; short b8S,b9S; long b10L,b11L,b12L,b13L,b14L,b15L;
	} hBmp;  
	hBmp.b2S=0;hBmp.b3S=0;hBmp.b4L=54L;hBmp.b5L=40L;hBmp.b6L=(long)w;hBmp.b7L=(long)h;hBmp.b8S=1;hBmp.b9S=24;
	hBmp.b10L=0L;hBmp.b11L=bPR*h;hBmp.b12L=0L;hBmp.b13L=0L;hBmp.b14L=0L;hBmp.b15L=0L;hBmp.b1L=54L+hBmp.b11L;
	static int imgCnt=0;  if(imgCnt==0) _mkdir("AVI");   ++imgCnt;       
	std::string fName = "AVI/screen"; if (imgCnt<100) if(imgCnt<10) fName+="00";  else fName+="0";
	char tmpStr[20];  _itoa_s(imgCnt,tmpStr, 20, 10);  fName+=tmpStr; fName+=".bmp";
	//std::cout << "Saving Screenshot... : " << fileName << std::endl;
	FILE *f; unsigned char *D = new unsigned char[3*w*h];
	if (!(fopen_s(&f, fName.c_str(),"wb")))  { delete [] D; return; }
	fwrite("BM",1,2*sizeof(char),f);  fwrite(&hBmp,1,sizeof(HBmp),f);
	glReadPixels(0,0,w,h, GL_RGB, GL_UNSIGNED_BYTE, &D[0]);
	int i,j;
	for (j=0;j<h;++j) {  for (i=0;i<w;++i) {    
		fwrite(&D[3*(j*w+i)+2],1,1,f); fwrite(&D[3*(j*w+i)+1],1,1,f); fwrite(&D[3*(j*w+i)+0],1,1,f);
	} if (rP>0) fwrite(0,rP,1,f); }  
	delete [] D;  fclose(f);  
}

struct bitmap_utils {
	static void renderBitmapString(float x, float y, void *font, char *string) {
		char *c; glRasterPos2f(x, y);
		for (c=string; *c != '\0'; c++) { glutBitmapCharacter(font, *c); }
	}
	static void setOrthographicProjection(int winwidth, int winheight) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();    
		gluOrtho2D(0, winwidth, 0, winheight);    
		glScalef(1, -1, 1);
		glTranslatef(0, -winheight, 0);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}
	static void resetPerspectiveProjection() {
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}
}; // end struct bitmap_utils

static void show_fps(float x, float y, int w, int h, char *s) {
	bitmap_utils::setOrthographicProjection(w, h);
	glPushAttrib(GL_LIGHTING_BIT); glPushAttrib(GL_TEXTURE_BIT);
	glDisable(GL_LIGHTING); glDisable(GL_TEXTURE_2D); glDisable(GL_TEXTURE_3D);
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	bitmap_utils::renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_12, s);
	glPopAttrib(); glPopAttrib();
	bitmap_utils::resetPerspectiveProjection();
}

#endif