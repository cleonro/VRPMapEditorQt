#ifndef _O_TEXTURES_H_
#define _O_TEXTURES_H_

//#include <afxwin.h>
#include <QtGui/qopengl.h>

class OTextures 
{
public:
	OTextures();
	~OTextures();

	static GLuint LoadPNGFromBufferToGL(char* buffer, unsigned int size, GLuint texture_id = 0);

protected:

};

#endif