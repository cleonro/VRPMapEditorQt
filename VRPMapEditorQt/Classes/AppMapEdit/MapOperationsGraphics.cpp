#include "MapOperationsGraphics.h"
#include "../Draw2D.h"
#include "../Utils/OTextures.h"
#include "../Utils/draw_utils.h"

#include <windows.h>
#include <process.h>
#include <QApplication>
#include "..\..\ccentralwidget.h"
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
	::TerminateThread((HANDLE)thread_google_, -1000);
}

void OMapOperationsGraphics::Init(void *data)
{
	view_ = (CGLWidget*)data;
	GetImageFromGoogle();
}

void OMapOperationsGraphics::GetImageFromGoogleThread2(void* data)
{
	OMapOperationsGraphics& obj = *((OMapOperationsGraphics*)data);

	OMapEvent* event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_START_TIMER;
	QApplication::postEvent(obj.view_, event);

	double xs, ys;
	double xw, yw;
	double lat, longit;

	for(int i = 0; i < 9; i++) {
		xs = patch_center_screen_coordinates[2 * i];
		ys = patch_center_screen_coordinates[2 * i + 1];
		obj.FromScreenCoordToWorldCoord(xs, ys, xw, yw);
		obj.FromWorldCoordToLatLong(xw, yw, lat, longit);

		char tstr[100];
		char addr[2000] = "http://maps.google.com/maps/api/staticmap?center=";
		sprintf_s(tstr, "%.6lf,%.6lf&zoom=%d&", lat, longit, obj.zoom_);
		strcat_s(addr, tstr);
		sprintf_s(tstr, "size=%dx%d&", SIZEMAP, SIZEMAP);
		strcat_s(addr, tstr);
		sprintf_s(tstr, "maptype=%s&sensor=false", obj.maptype_);
		strcat_s(addr, tstr);

		if(!obj.CallCurl(addr)) {
			continue;
		}

		obj.pixmaps_[i].loadFromData(QByteArray(obj.buffer_, size_b_), "png");
		event = new OMapEvent();
		event->Type() = OMapEvent::E_MAP_TEXTURE_READY;
		tTextureData* tdata = new tTextureData;
		tdata->pixmap_ = &obj.pixmaps_[i];
		tdata->texid_ = &obj.texid_[i];
		event->Data() = (void*)tdata;
		QApplication::postEvent(obj.view_, event);
	}

	obj.translate_x_ = 0;
	obj.translate_y_ = 0;

	event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_STOP_TIMER;
	QApplication::postEvent(obj.view_, event);
}

void OMapOperationsGraphics::GetImageFromGoogleThread(void* data)
{
	
	OMapOperationsGraphics& obj = *((OMapOperationsGraphics*)data);

	OMapEvent* event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_START_TIMER;
	QApplication::postEvent(obj.view_, event);

	obj.view_->hiddenWidget->makeCurrent();

	double xs, ys;
	double xw, yw;
	double lat, longit;

	for(int i = 0; i < 9; i++) {

		xs = patch_center_screen_coordinates[2 * i];
		ys = patch_center_screen_coordinates[2 * i + 1];
		obj.FromScreenCoordToWorldCoord(xs, ys, xw, yw);
		obj.FromWorldCoordToLatLong(xw, yw, lat, longit);

		char tstr[100];
		char addr[2000] = "http://maps.google.com/maps/api/staticmap?center=";
		//center=40.702147,-74.015794&zoom=1&size=512x512&maptype=satellite&sensor=false";
		//sprintf_s(tstr, "%.6lf,%.6lf&zoom=%d&", center_latitude_, center_longitude_, zoom_);
		sprintf_s(tstr, "%.6lf,%.6lf&zoom=%d&", lat, longit, obj.zoom_);
		strcat_s(addr, tstr);
		sprintf_s(tstr, "size=%dx%d&", SIZEMAP, SIZEMAP);
		strcat_s(addr, tstr);
		sprintf_s(tstr, "maptype=%s&sensor=false", obj.maptype_);
		strcat_s(addr, tstr);

		if(!obj.CallCurl(addr)) {
			continue;
		}

		QImage pixmap, cpixmap;
		pixmap.loadFromData(QByteArray(obj.buffer_, size_b_), "png");

		glEnable(GL_TEXTURE_2D);

		if(!obj.texid_[i]) {
			cpixmap = pixmap.convertToFormat(QImage::Format_RGB32);
			obj.texid_[i] = obj.view_->bindTexture(cpixmap);
		} else {

			cpixmap = obj.view_->hiddenWidget->convertToGLFormat(pixmap);

			const unsigned int w = cpixmap.width();
			const unsigned int h = cpixmap.height();

			glBindTexture(GL_TEXTURE_2D, obj.texid_[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
								GL_RGBA, GL_UNSIGNED_BYTE, cpixmap.bits());
		}
	}

	obj.translate_x_ = 0;
	obj.translate_y_ = 0;

	event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_STOP_TIMER;
	QApplication::postEvent(obj.view_, event);
}

bool OMapOperationsGraphics::GetImageFromGoogle()
{
	view_->mParent->EnableThreadControls(false);
#if _USE_INTEL_
	thread_google_ = _beginthread(OMapOperationsGraphics::GetImageFromGoogleThread2, 0, (void*)this);
#else
	thread_google_ = _beginthread(OMapOperationsGraphics::GetImageFromGoogleThread, 0, (void*)this);
#endif
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

	//show_fps(10, 10, 10, 10, "MAP");
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
		glBindTexture(GL_TEXTURE_2D, texid_[i]);
		glPushMatrix();

		xs = patch_center_screen_coordinates[2 * i];
		ys = patch_center_screen_coordinates[2 * i + 1];
		glTranslatef(xs + translate_x_, ys + translate_y_, 0.0f);		
		glDrawArrays(GL_QUADS, 0, 4);
		glPopMatrix();
	}

	//VDraws->DrawAxes(sz, 1.0f);
}