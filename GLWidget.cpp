#include "GLWidget.h"
#include <QMouseEvent>
#include <QMessageBox>

#include "Classes/AppBaseState.h"
#include "Classes/InputMgr.h"
#include "Classes/Draw2D.h"
#include <QOpenGLContext>
#include <QImage>
#include "ccentralwidget.h"
#include "Classes/AppMapEdit/AppMapEdit.h"
#include "Classes/AppMapEdit/OMapEvent.h"

CGLWidget::CGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	this->setMouseTracking(true);
	cx = 0;
	cy = 0;
	angle = 0.0;
	timerCounter = 0;
	showWaiting = false;
	transparency_ = 0.7f;
	showGrid = false;
	timerImage.load(":/VRPMapEditorQt/Resources/wait.png", "png");
	timerImageId = 0;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
}


CGLWidget::~CGLWidget()
{
    MAPOPP.StopWorkers();
    CleanupGL();
}

void CGLWidget::CleanupGL()
{
    if (!context() || !isValid()) { return; }
    disconnect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &CGLWidget::CleanupGL);
    makeCurrent();
    glDeleteTextures(1, &timerImageId);
    timerImageId = 0;
    MAPOPP.ReleaseTextures();
    doneCurrent();
}

static GLuint UploadTexture(const QImage& image, GLuint id = 0)
{
    if (image.isNull()) { return id; }
    const QImage rgba = image.convertToFormat(QImage::Format_RGBA8888).flipped(Qt::Vertical);
    if (!id) { glGenTextures(1, &id); }
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgba.width(), rgba.height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.constBits());
    return id;
}

void CGLWidget::LoadTexture(void* data)
{
    const auto* texture = static_cast<OMapOperationsGraphics::tTextureData*>(data);
    if (texture) {
        // Upload only in paintGL(), where the widget's context is current.
        pendingTextures.append({texture->pixmap_, texture->texid_});
        update();
    }
}

bool CGLWidget::event(QEvent* e)
{
	if(e->type() == QEvent::User) {
		OMapEvent* ev = (OMapEvent*)e;
		
		if(ev->Type() == OMapEvent::E_MAP_START_TIMER) {
			StartTimer();
		}
		if(ev->Type() == OMapEvent::E_MAP_IMAGES_READY) {
            MAPOPP.ImagesReady();
        }
		if(ev->Type() == OMapEvent::E_MAP_STOP_TIMER || ev->Type() == OMapEvent::E_MAP_IMAGES_READY) {
			StopTimer();
			mParent->EnableThreadControls(true);
		}
		if(ev->Type() == OMapEvent::E_MAP_TEXTURE_READY) {
			LoadTexture(ev->Data());
		}
		if(ev->Type() == OMapEvent::E_MAP_GEN_STOP) {
			MAPOPP.MappChanged();
			QMessageBox::warning(mParent, tr("Google maps error"),
				tr("Connections generation was stopped. Save the map and try again later..."));
		}
		if(ev->Type() == OMapEvent::E_MAP_GEN_SUCCESS) {
			MAPOPP.MappChanged();
			QMessageBox::information(mParent, tr("Operation ended!"), tr("Connections were generated successfully..."));
		}
		return true;
	}

	return QOpenGLWidget::event(e);
}

void CGLWidget::OnTimer()
{
	update();
	angle -= (360.0 / (3.0 * 60.0));
}

void CGLWidget::DrawTimer()
{
	const float sz = -50.0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, timerImageId);

	static float coord[] = {
		-sz, -sz,
		-sz, sz,
		sz,  sz,
		sz, -sz
	};
	static float tcoord[] = {
		0.0, 0.0,
		0.0, 1.0,
		1.0, 1.0,
		1.0, 0.0
	} ;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, coord);
	glTexCoordPointer(2, GL_FLOAT, 0, tcoord);

	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glDrawArrays(GL_QUADS, 0, 4);
	glPopMatrix();
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLWidget::StartTimer(bool show)
{
	timerCounter++;
	if(timerCounter == 1) {
		showWaiting = show;
		timer->start(16);
	}
}

void CGLWidget::StopTimer()
{
	if (timerCounter == 0) { return; }
	timerCounter--;
	if(timerCounter == 0) {
		showWaiting = false;
		timer->stop();
		update();
	}
}

QSize CGLWidget::minimumSizeHint() const
{
	return QSize(50, 50);
}

QSize CGLWidget::sizeHint() const
{
	return QSize(800, 800);
}

void CGLWidget::initializeGL()
{
	connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &CGLWidget::CleanupGL, Qt::DirectConnection);
    timerImageId = UploadTexture(timerImage.toImage());

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 	glEnable(GL_DEPTH_TEST);
// 	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);

	glPixelZoom(1.0,1.0);

	APPMNGR.ChangeState(OAppManager::APP_MAP_EDIT);
	APPMNGR.GetState()->Init(this);
	INPUTMGR->ChangeState(INPUT_MAP_EDIT);

}

void CGLWidget::paintGL()
{
	glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
    for (const PendingTexture& texture : pendingTextures) {
        *texture.id = UploadTexture(texture.image, *texture.id);
    }
    pendingTextures.clear();
    glViewport(0, 0, qRound(width() * devicePixelRatioF()), qRound(height() * devicePixelRatioF()));
	((OAppMapEdit*)APPMNGR.GetState())->Draw(transparency_);


	if(showGrid) {
		DrawGrid();
	}
	if(showWaiting) {
		DrawTimer();
	}
}

void CGLWidget::resizeGL(int width, int height)
{
	cx = width;
	cy = height;

	glViewport( 0, 0, cx, cy); 

    OGL3DCamera* camera = &(APPMNGR.GetState()->GetCamera());
    camera->SwitchToOrthoProjection(OVector4(-cx / 2.0f, cx / 2.0f, -cy / 2.0f, cy / 2.0f));
}

void CGLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->position().toPoint();
		
		int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
		int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
		point.setY(y);
		point.setX(x);

		INPUTMGR->OnLButtonDown(point);
	}

	if(event->button() == Qt::RightButton) {
		StartTimer();
	}
}

void CGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point = event->position().toPoint();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	INPUTMGR->OnMouseMove(point);
	update();
}

void CGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->position().toPoint();

		int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
		int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
		point.setY(y);
		point.setX(x);

		INPUTMGR->OnLButtonUp(point);
	}
}

void CGLWidget::wheelEvent(QWheelEvent *event)
{
	QPoint point = event->position().toPoint();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	int delta = event->angleDelta().y();

	INPUTMGR->OnMouseWheel( delta, point);

	update();
}

#define DIST 20
void CGLWidget::DrawGrid()
{
	DRAW2D.SetColor(0.5, 0.5, 0.7, 0.8);
	for(int i = -cx / 2; i <= cx / 2; i += DIST) {
		DRAW2D.DrawLine(i, -cy / 2, i, cy / 2);
	}

	for(int i = -cy / 2; i <= cy / 2; i += DIST) {
		DRAW2D.DrawLine(-cx / 2, i, cx / 2, i);
	}
}
