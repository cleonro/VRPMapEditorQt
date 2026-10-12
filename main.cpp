#include "vrpmapeditorqt.h"
#include <QApplication>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    // The existing renderer uses the fixed-function desktop OpenGL API.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(2, 1);
    format.setProfile(QSurfaceFormat::NoProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    QApplication application(argc, argv);
    VRPMapEditorQt window;
    window.resize(1024, 768);
    window.show();
    return application.exec();
}
