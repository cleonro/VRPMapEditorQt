#include "MapOperationsGraphics.h"
#include "../Draw2D.h"

#include <QApplication>
#include "../../ccentralwidget.h"
#include "OMapEvent.h"

float patch_center_screen_coordinates[18] = {
	-512.0,  512.0, //0
	0.0,  512.0, //1
	512.0,  512.0, //2
	-512.0,    0.0, //3
	0.0,    0.0, //4 SCREEN CENTER
	512.0,    0.0, //5
	-512.0, -512.0, //6
	0.0, -512.0, //7
	512.0, -512.0  //8
};

OMapOperationsGraphics::OMapOperationsGraphics()
{
	drawline_ = false;

	for(int i = 0; i < 9; i++) {
		texid_[i] = 0;
	}
	translate_x_ = 0.0;
	translate_y_ = 0.0;

	access_blocked_ = false;
	draw_arcs_ = true;
	line_width_ = 1;
}

OMapOperationsGraphics::~OMapOperationsGraphics()
{
	StopWorkers();
}

void OMapOperationsGraphics::Init(void *data)
{
	view_ = (CGLWidget*)data;
	GetImageFromGoogle();
}

void OMapOperationsGraphics::GetImageFromGoogleThread(void* data)
{
	OMapOperationsGraphics& obj = *((OMapOperationsGraphics*)data);

	OMapEvent* event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_START_TIMER;
	QApplication::postEvent(obj.view_, event);

	double xs, ys;
	double xw, yw;
	double lat, longit;

	for(int i = 0; i < 9 && !QThread::currentThread()->isInterruptionRequested(); i++) {
		xs = patch_center_screen_coordinates[2 * i];
		ys = patch_center_screen_coordinates[2 * i + 1];
		obj.FromScreenCoordToWorldCoord(xs, ys, xw, yw);
		obj.FromWorldCoordToLatLong(xw, yw, lat, longit);

		const QByteArray addr = QString("https://maps.googleapis.com/maps/api/staticmap?center=%1,%2&zoom=%3&size=%4x%4&maptype=%5&sensor=false")
            .arg(lat, 0, 'f', 6).arg(longit, 0, 'f', 6).arg(obj.zoom_)
            .arg(SIZEMAP).arg(obj.maptype_).toUtf8();

		const QByteArray response = obj.FetchUrl(addr.constData());
        if(response.isEmpty()) {
			continue;
		}

		QImage image;
        if (!image.loadFromData(response, "png")) {
            continue;
        }
		event = new OMapEvent();
		event->Type() = OMapEvent::E_MAP_TEXTURE_READY;
		tTextureData* tdata = new tTextureData;
		tdata->pixmap_ = image;
		tdata->texid_ = &obj.texid_[i];
		event->Data() = (void*)tdata;
		QApplication::postEvent(obj.view_, event);
	}

	event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_IMAGES_READY;
	QApplication::postEvent(obj.view_, event);
}

bool OMapOperationsGraphics::GetImageFromGoogle()
{
	view_->mParent->EnableThreadControls(false);
	thread_google_.Start(OMapOperationsGraphics::GetImageFromGoogleThread, this);
	return true;
}

void OMapOperationsGraphics::Draw(float transparency)
{	
	DrawMap();
	glDisable(GL_TEXTURE_2D);
	if(!access_blocked_){
		graph_.Draw(transparency, line_width_);
	}

	//if(selected_ == 1 && (action_state_ == MAP_ADD_ROUTE || action_state_ == MAP_NODE_CINF)) {
	if(drawline_) {
		DRAW2D.SetColor(0.1f, 0.7f, 0.9f, transparency);
		DRAW2D.DrawLine(line_[0], line_[1], line_[2], line_[3], line_width_);
	}

}

void OMapOperationsGraphics::DrawMap()
{
	const float sz = 256.0;
	glEnable(GL_TEXTURE_2D);

	float xs, ys;
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

	for(int i = 0; i < 9; i++) {
		if (!texid_[i]) { continue; }
		glBindTexture(GL_TEXTURE_2D, texid_[i]);
		glPushMatrix();

		xs = patch_center_screen_coordinates[2 * i];
		ys = patch_center_screen_coordinates[2 * i + 1];
		glTranslatef(xs + translate_x_, ys + translate_y_, 0.0f);		
		glDrawArrays(GL_QUADS, 0, 4);
		glPopMatrix();
	}

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
	//VDraws->DrawAxes(sz, 1.0f);
}
void OMapOperationsGraphics::ReleaseTextures()
{
    glDeleteTextures(9, texid_);
    for (GLuint& id : texid_) { id = 0; }
}
