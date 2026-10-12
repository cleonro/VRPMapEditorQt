#ifndef _DRAW_UTILS_H_
#define _DRAW_UTILS_H_

#include <cmath>
#include <QDir>
#include <QImage>
#include <QPainter>
#include <QtGui/qopengl.h>

template <class T> void swp(T &a, T &b) { T tmp = a; a = b; b = tmp; }
template <class T> T t_max(T a, T b) { return a > b ? a : b; }
template <class T> T t_max(T a, T b, T c) { return t_max(t_max(a, b), c); }
template <class T> T t_min(T a, T b) { return a < b ? a : b; }
template <class T> T t_min(T a, T b, T c) { return t_min(t_min(a, b), c); }
template <class T> int sgn(T a) { return (a > 0) - (a < 0); }

inline void saveBmp24(int width, int height)
{
    static int imageCount = 0;
    QDir().mkpath("AVI");
    QImage image(width, height, QImage::Format_RGBA8888);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    image.flipped(Qt::Vertical).save(QString("AVI/screen%1.bmp").arg(++imageCount, 3, 10, QChar('0')));
}

inline void show_fps(float x, float y, int width, int height, const char* text)
{
    const QString label = QString::fromUtf8(text);
    const QFont font("Sans Serif", 10);
    const QFontMetrics metrics(font);
    QImage image(metrics.horizontalAdvance(label) + 2, metrics.height(), QImage::Format_RGBA8888);
    image.fill(Qt::transparent);
    {
        QPainter painter(&image);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(0, metrics.ascent(), label);
    }
    image = image.flipped(Qt::Vertical);
    glPushAttrib(GL_ENABLE_BIT | GL_PIXEL_MODE_BIT | GL_CURRENT_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2f(x, height - y);
    glDrawPixels(image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, image.constBits());
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
}

#endif
