#include "OTextures.h"
#include <QImage>

OTextures::OTextures() = default;
OTextures::~OTextures() = default;

GLuint OTextures::LoadPNGFromBufferToGL(char* buffer, unsigned int size, GLuint texture_id)
{
    QImage image;
    if (!image.loadFromData(reinterpret_cast<const uchar*>(buffer), size, "PNG")) {
        return 0;
    }
    image = image.convertToFormat(QImage::Format_RGBA8888).flipped(Qt::Vertical);
    if (!texture_id) { glGenTextures(1, &texture_id); }
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, image.constBits());
    return texture_id;
}
