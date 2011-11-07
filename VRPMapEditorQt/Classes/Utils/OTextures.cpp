#include "OTextures.h"

#include "..\..\OtherSources\il\il.h"

OTextures::OTextures()
{

}

OTextures::~OTextures()
{

}

GLuint OTextures::LoadPNGFromBufferToGL(char* buffer, unsigned int size, GLuint texture_id)
{
	GLuint res = 0;
	ILuint texid;

	ilInit();
	ilGenImages(1, &texid);
	ilBindImage(texid);
	ILboolean succ = ilLoadL(IL_PNG, buffer, size);

	//FILE* f = fopen("imdest_s.png","wb");
	//for(int i = 0; i < size; i++) {
	//	fwrite(buffer, size, 1, f);
	//}
	//fclose(f);

	//ILboolean succ = ilLoadImage((LPWSTR)"imdest.png");

	if(succ) {

		ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		if(texture_id > 0) {
			res = texture_id;
		} else{
			glGenTextures(1, &res);
		}
		glBindTexture(GL_TEXTURE_2D, res);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), 
						ilGetInteger(IL_IMAGE_WIDTH),
						ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
						ilGetData());

		ilDeleteImages(1, &texid);
	}

	return res;
}