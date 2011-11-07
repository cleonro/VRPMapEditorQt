#ifndef _O_TEXTURES_H_
#define _O_TEXTURES_H_

#include <windows.h>
//#include <afxwin.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class OTextures 
{
public:
	OTextures();
	~OTextures();

	static GLuint LoadPNGFromBufferToGL(char* buffer, unsigned int size, GLuint texture_id = 0);

protected:

};

#endif