#pragma once

#include <QGLWidget>
#include <QTimer>
#include <QPixmap>

class CCentralWidget;

class CGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	CGLWidget(QWidget *parent = 0);
	~CGLWidget();

	//?
	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void StartTimer(bool show = true);
	void StopTimer();
	bool event(QEvent* e);
	
	QGLWidget* hiddenWidget;
	CCentralWidget* mParent;
	float transparency_;
	bool showGrid;
protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	void mousePressEvent(QMouseEvent *event);
 	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void LoadTexture(void* data);

	void DrawTimer();
	void DrawGrid();

	int cx;//size x
	int cy;//size y
	QTimer* timer;
	int timerCounter;
	bool showWaiting;
	
	QPixmap timerImage;
	GLuint timerImageId;
	float angle;

protected slots:
	void OnTimer();

};

