#include <QtTest>
#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QFile>
#include <QSurfaceFormat>
#include <QTcpServer>
#include <QTcpSocket>
#include <cmath>
#include <cstring>

#include "vrpmapeditorqt.h"
#include "Classes/AppMapEdit/GraphMap/GraphMap.h"
#include "Classes/AppMapEdit/MapOperationsIAccess.h"
#include "Classes/AppMapEdit/MapOperationsInput.h"
#include "Classes/AppMapEdit/OMapEvent.h"
#include "Classes/Math/Quaternion.h"
#include "Classes/Utils/WorkerThread.h"

class NetworkProbe : public OMapOperationsIAccess
{
public:
    NetworkProbe() = default;
    using OMapOperationsIAccess::FetchUrl;
    using OMapOperationsIAccess::ParseDirectionsResponseXML;
};

class MigrationTests : public QObject
{
    Q_OBJECT
private slots:
    void legacyMapRoundTrip()
    {
        QFile file(QStringLiteral(TEST_DATA_DIR "/qtsavetest.vrpm"));
        QVERIFY(file.open(QIODevice::ReadOnly));
        const QByteArray original = file.readAll();
        QDataStream input(original);
        input.setVersion(QDataStream::Qt_4_8);
        OGraphMap map;
        input >> map;
        QCOMPARE(input.status(), QDataStream::Ok);
        QVERIFY(input.atEnd());
        QCOMPARE(map.GetSize(), 3);
        QByteArray saved;
        QDataStream output(&saved, QIODevice::WriteOnly);
        output.setVersion(QDataStream::Qt_4_8);
        output << map;
        QCOMPARE(output.status(), QDataStream::Ok);
        QCOMPARE(saved, original);
    }

    void routeWireFormat()
    {
        OGraphRoute route;
        *route.GetPathAddr() = {45.0, 25.0, 46.0, 26.0};
        route.SetRouteInf({12.0f, 34.0f});
        tRouteAddr address{};
        qstrncpy(address.start_address_, "Start", sizeof(address.start_address_));
        qstrncpy(address.end_address_, "End", sizeof(address.end_address_));
        route.SetRouteAddr(address);
        QByteArray saved;
        QDataStream output(&saved, QIODevice::WriteOnly);
        output.setVersion(QDataStream::Qt_4_8);
        output << route;
        // A 64-bit size_t must still be written as the old 32-bit count.
        QCOMPARE(saved.left(4).toHex(), QByteArray("00000004"));
        QDataStream input(saved);
        input.setVersion(QDataStream::Qt_4_8);
        OGraphRoute restored;
        input >> restored;
        QVERIFY(input.atEnd());
        QCOMPARE(*restored.GetPathAddr(), *route.GetPathAddr());
        QCOMPARE(QByteArray(restored.GetRouteAddr().start_address_), QByteArray("Start"));
    }

    void unicodeNodeRoundTrip()
    {
        OGraphNode node;
        node.SetType(OGraphNode::N_CLIENT);
        node.SetCoordinates(45.0, 25.0);
        qstrncpy(node.GetName(), "Bra\xc8\x99ov", 20);
        QByteArray data;
        QDataStream output(&data, QIODevice::WriteOnly);
        output.setVersion(QDataStream::Qt_4_8);
        output << node;
        QDataStream input(data);
        input.setVersion(QDataStream::Qt_4_8);
        OGraphNode restored;
        input >> restored;
        QCOMPARE(QByteArray(restored.GetName()), QByteArray(node.GetName()));
        QCOMPARE(input.status(), QDataStream::Ok);
    }

    void portableMath()
    {
        QCOMPARE(SQRT(25.0f), 5.0f);
        QVERIFY(std::abs(RSQRT(25.0f) - 0.2f) < 1e-6f);
        const OQuaternion rotation(0, 0, std::sqrt(0.5f), std::sqrt(0.5f));
        const OVector3 rotated = (rotation * OQuaternion(1, 0, 0, 0) *
                                 OQuaternion(0, 0, -std::sqrt(0.5f), std::sqrt(0.5f))).V3();
        QVERIFY(std::abs(rotated.Norm() - 1.0f) < 1e-6f);
        OVector3 vector = rotated;
        QVERIFY(std::abs(vector.X()) < 1e-6f);
        QVERIFY(std::abs(vector.Y() - 1.0f) < 1e-6f);
    }

    void networkResponses()
    {
        QTcpServer server;
        QVERIFY(server.listen(QHostAddress::LocalHost, 0));
        QByteArray payload("response in chunks");
        connect(&server, &QTcpServer::newConnection, &server, [&] {
            QTcpSocket* socket = server.nextPendingConnection();
            connect(socket, &QTcpSocket::readyRead, socket, [&, socket] {
                socket->readAll();
                socket->write("HTTP/1.1 200 OK\r\nContent-Length: " +
                              QByteArray::number(payload.size()) + "\r\nConnection: close\r\n\r\n");
                socket->write(payload.left(3));
                QTimer::singleShot(5, socket, [&, socket] {
                    socket->write(payload.mid(3));
                    socket->disconnectFromHost();
                });
            });
            connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
        });
        const QByteArray url = "http://127.0.0.1:" + QByteArray::number(server.serverPort()) + "/";
        NetworkProbe network;
        QCOMPARE(network.FetchUrl(url.constData()), payload);
        payload = QByteArray(SIZEBUFF + 1, 'x');
        QVERIFY(network.FetchUrl(url.constData()).isEmpty());
    }

    void malformedDirections()
    {
        NetworkProbe network;
        QVERIFY(!network.ParseDirectionsResponseXML("<broken"));
        QVERIFY(!network.ParseDirectionsResponseXML("<DirectionsResponse/>"));
        QVERIFY(!network.ParseDirectionsResponseXML(
            "<DirectionsResponse><status>OK</status></DirectionsResponse>"));
        QVERIFY(!network.ParseDirectionsResponseXML(
            "<DirectionsResponse><status>REQUEST_DENIED</status></DirectionsResponse>"));
    }

    void workerShutdown()
    {
        WorkerThread worker;
        worker.Start([](void*) {
            while (!QThread::currentThread()->isInterruptionRequested()) { QThread::msleep(10); }
        }, nullptr);
        QTest::qWait(20);
        QElapsedTimer elapsed;
        elapsed.start();
        worker.Stop();
        QVERIFY(elapsed.elapsed() < 2000);
    }

    void openGLSmoke()
    {
        VRPMapEditorQt window;
        window.resize(1024, 768);
        window.show();
        QVERIFY(QTest::qWaitForWindowExposed(&window));
        auto* renderer = window.findChild<CGLWidget*>();
        QVERIFY(renderer);
        QTRY_VERIFY(renderer->isValid());
        QTRY_VERIFY(window.findChild<QComboBox*>("mapType")->isEnabled());
        const QImage initial = renderer->grabFramebuffer();
        QVERIFY(!initial.isNull());
        QVERIFY(initial.pixelColor(initial.width() / 2, initial.height() / 2).blue() > 100);
        window.findChild<QCheckBox*>("showGrid")->click();
        QTest::qWait(100);
        QVERIFY(renderer->grabFramebuffer() != initial);
        renderer->makeCurrent();
        QCOMPARE(glGetError(), GLenum(GL_NO_ERROR));
        renderer->doneCurrent();
        // A texture event must upload safely even when no context is current in event().
        GLuint id = 0;
        auto* event = new OMapEvent;
        event->Type() = OMapEvent::E_MAP_TEXTURE_READY;
        auto* texture = new OMapOperationsGraphics::tTextureData;
        texture->pixmap_ = QImage(2, 2, QImage::Format_RGBA8888);
        texture->pixmap_.fill(Qt::red);
        texture->texid_ = &id;
        event->Data() = texture;
        QApplication::postEvent(renderer, event);
        QTRY_VERIFY(id != 0);
        renderer->makeCurrent();
        QCOMPARE(glGetError(), GLenum(GL_NO_ERROR));
        glDeleteTextures(1, &id);
        renderer->doneCurrent();
        window.close();
    }
};

int main(int argc, char** argv)
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(2, 1);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    qunsetenv("GOOGLE_MAPS_API_KEY"); // Tests never call paid external services.
    QApplication application(argc, argv);
    MigrationTests tests;
    return QTest::qExec(&tests, argc, argv);
}

#include "migration_tests.moc"
