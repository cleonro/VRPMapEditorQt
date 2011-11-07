
#include "AppMapEdit.h"

#include "..\..\GLWidget.h"

OAppMapEdit::OAppMapEdit(void)
{
	view_ = NULL;
}

OAppMapEdit::~OAppMapEdit(void)
{

}

OAppMapEdit& OAppMapEdit::GetInstance()
{
	static OAppMapEdit instance;
	return instance;
}

void OAppMapEdit::Init(void* data)
{
	view_ = (CGLWidget*)data;

	MAPOPP.Init(data);
	camera_.SwitchToOrthoProjection(OVector4(-50, 50, -50, 50));

	
}

void OAppMapEdit::Update(void* data)
{

}

void OAppMapEdit::Update2(void* data)
{

}

void OAppMapEdit::Draw(float transparency)
{
	MAPOPP.Draw(transparency);
}

void OAppMapEdit::ReDraw()
{
	((CGLWidget*)view_)->updateGL();
}

void* OAppMapEdit::GetDataForInput()
{

	return NULL;
}