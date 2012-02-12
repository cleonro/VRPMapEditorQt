#pragma once

#include <QDialog>
#include "ui_nodeviewdialog.h"

class CNodeViewDialog : public QDialog
{
	Q_OBJECT
public:
	CNodeViewDialog(QWidget* parent = 0);
	~CNodeViewDialog();
	Ui::NodeViewDialog ui;

	QString mType;
	QString mName;
	float	mTime;
	float	mQuantity;
	QString	mVehicles;

	float mAccessibility;
	float mHabitants;
	float mContracts;
	float mPrice;

	void DataExchange(bool set = true);

protected slots:
	void ShowVehiclesWidget();
};

