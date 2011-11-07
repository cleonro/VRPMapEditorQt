#include "GLWidget.h"
#include <QMouseEvent>

#include "Classes\AppBaseState.h"
#include "Classes\InputMgr.h"
#include "Classes\Draw2D.h"
#include <QGLContext>
#include "ccentralwidget.h"
#include "Classes\AppMapEdit\AppMapEdit.h"
#include "Classes\AppMapEdit\OMapEvent.h"

CGLWidget::CGLWidget(QWidget *parent) : QGLWidget(parent)
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
	hiddenWidget = NULL;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
}


CGLWidget::~CGLWidget()
{
	delete timer;
	if(hiddenWidget) {
		delete hiddenWidget;
		hiddenWidget = NULL;
	}
}

void CGLWidget::LoadTexture(void* data) 
{
	OMapOperationsGraphics::tTextureData* tdata = (OMapOperationsGraphics::tTextureData*)data;
	if(data == NULL) {
		return;
	}
	QImage cpixmap;
	if(*(tdata->texid_) == 0) {
		cpixmap = tdata->pixmap_->convertToFormat(QImage::Format_RGB32);
		*(tdata->texid_) = this->bindTexture(cpixmap);
	} else {

		cpixmap = this->convertToGLFormat(*(tdata->pixmap_));

		const unsigned int w = cpixmap.width();
		const unsigned int h = cpixmap.height();

		glBindTexture(GL_TEXTURE_2D, *(tdata->texid_));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
			GL_RGBA, GL_UNSIGNED_BYTE, cpixmap.bits());
	}
	delete tdata;
}

bool CGLWidget::event(QEvent* e)
{
	if(e->type() == QEvent::User) {
		OMapEvent* ev = (OMapEvent*)e;
		
		if(ev->Type() == OMapEvent::E_MAP_START_TIMER) {
			StartTimer();
		}
		if(ev->Type() == OMapEvent::E_MAP_STOP_TIMER) {
			StopTimer();
			mParent->EnableThreadControls(true);
		}
		if(ev->Type() == OMapEvent::E_MAP_TEXTURE_READY) {
			LoadTexture(ev->Data());
		}
		return true;
	}

	return QGLWidget::event(e);
}

void CGLWidget::OnTimer()
{
	updateGL();
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
}

void CGLWidget::StartTimer(bool show)
{
	timerCounter++;
	if(timerCounter == 1) {
		showWaiting = show;
		timer->start(1000.0 / 60.0);
	}
}

void CGLWidget::StopTimer()
{
	timerCounter--;
	if(timerCounter == 0) {
		showWaiting = false;
		timer->stop();
		updateGL();
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
	timerImageId = this->bindTexture(timerImage.toImage());

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// 	glEnable(GL_DEPTH_TEST);
// 	glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_2D);

	glPixelZoom(1.0,1.0);

	QGLFormat format = this->context()->format();
	hiddenWidget = new QGLWidget(/*format,*/ NULL, this);
	
	//init own stuff
// 	APPMNGR.ChangeState(OAppManager::APP_BASE_STATE);
// 	float aspect = 0.7;
// 	APPMNGR.GetState()->Init(&aspect);
// 	INPUTMGR->ChangeState(INPUT_BASE);

	APPMNGR.ChangeState(OAppManager::APP_MAP_EDIT);
	APPMNGR.GetState()->Init(this);
	INPUTMGR->ChangeState(INPUT_MAP_EDIT);

}

void CGLWidget::paintGL()
{
	glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//APPMNGR.GetState()->Update();
	((OAppMapEdit*)APPMNGR.GetState())->Draw(transparency_);

	//this->renderText(0, 0, 0, "Test text");

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

	//3d camera
	OGL3DCamera* camera = &(APPMNGR.GetState()->GetCamera());
	OVector4 persp = camera->GetPerspective();
	persp[3] = (cx + 0.0f) / (cy + 0.0f);
	camera->SetPerspective(persp);

	 //
	camera->SwitchToOrthoProjection(OVector4(-cx / 2, cx / 2, -cy / 2, cy / 2));
}

void CGLWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->pos();
		
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
	QPoint point = event->pos();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	INPUTMGR->OnMouseMove(point);
	updateGL();
}

void CGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		QPoint point = event->pos();

		int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
		int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
		point.setY(y);
		point.setX(x);

		INPUTMGR->OnLButtonUp(point);
	}
}

void CGLWidget::wheelEvent(QWheelEvent *event)
{
	QPoint point = event->pos();

	int y = (-(cy + 0.0f) / (cy- 1.0f) * (point.y() + 0.0f) + (cy + 0.0f) / 2.0f);
	int x = ((cx + 0.0f) / (cx- 1.0f) * (point.x() + 0.0f) - (cx + 0.0f) / 2.0f);
	point.setY(y);
	point.setX(x);

	int delta = event->delta();

	INPUTMGR->OnMouseWheel( delta, point);

	updateGL();
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