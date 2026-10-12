#ifndef CCENTRALWIDGET_H
#define CCENTRALWIDGET_H

#include <QWidget>
#include "ui_ccentralwidget.h"

class CCentralWidget : public QWidget
{
	Q_OBJECT

public:
	CCentralWidget(QWidget *parent = 0);
	~CCentralWidget();

public slots:
	void EnableThreadControls(bool enable);

	void StartTimer(bool show = true);
	void StopTimer();
private:
	Ui::CCentralWidget ui;
	
protected slots:
	void UpClicked();
	void DownClicked();
	void LeftClicked();
	void RightClicked();
	void SliderReleased();
	void ShowGridClicked();
	void ShowConnectionsClicked();
	void ComboBoxIndexChanged(QString index);
	void SliderValueChanged(int value);
	void LineWidthChanged(int value);
};

#endif // CCENTRALWIDGET_H
