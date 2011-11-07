#include "ccentralwidget.h"
#include "Classes\AppMapEdit\MapOperationsInput.h"

CCentralWidget::CCentralWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.mapType->setCurrentIndex(2);
	ui.toolbox->setVisible(true);

	ui.showConnections->setChecked(false);
	MAPOPP.SetDrawArcs(false);

	
	ui.glwidget->mParent = this;
}

CCentralWidget::~CCentralWidget()
{

}

void CCentralWidget::UpClicked()
{
	MAPOPP.ScrollY(false);
}

void CCentralWidget::DownClicked()
{
	MAPOPP.ScrollY();
}

void CCentralWidget::LeftClicked()
{
	MAPOPP.ScrollX();
}

void CCentralWidget::RightClicked()
{
	MAPOPP.ScrollX(false);
}

void CCentralWidget::SliderReleased()
{
	int v = ui.verticalSlider->value();
	int nzoom = 5 + (18 - v);
	MAPOPP.Zoom(nzoom);
}

void CCentralWidget::ComboBoxIndexChanged(QString index)
{
	static bool f = true;
	if(f) {
		f = false;
		return;
	}
	MAPOPP.SetMapType(index.toAscii().data());
}

void CCentralWidget::ShowGridClicked()
{
	bool st = ui.glwidget->showGrid;
	ui.glwidget->showGrid = !st;
	ui.glwidget->updateGL();
}

void CCentralWidget::ShowConnectionsClicked()
{
	bool st = ui.showConnections->isChecked();
	MAPOPP.SetDrawArcs(st);
	ui.glwidget->updateGL();
}

void CCentralWidget::EnableThreadControls(bool enable)
{
	ui.upButton->setEnabled(enable);
	ui.downButton->setEnabled(enable);
	ui.leftButton->setEnabled(enable);
	ui.rightButton->setEnabled(enable);

	ui.verticalSlider->setEnabled(enable);
	ui.mapType->setEnabled(enable);
}

void CCentralWidget::SliderValueChanged(int value)
{
	ui.glwidget->transparency_ = value / 10.0f;
	ui.glwidget->updateGL();
}

void CCentralWidget::LineWidthChanged(int value)
{
	MAPOPP.LineWidth() = value;
	ui.glwidget->updateGL();
}