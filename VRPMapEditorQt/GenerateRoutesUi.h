#pragma once
#include <QDialog>
#include "ui_GenerateRoutesUi.h"
#include "ui_CustomRoutesUi.h"

class CGenerateRoutesUi : public QDialog
{
	Q_OBJECT
public:
	CGenerateRoutesUi(QWidget* parent = 0);
	~CGenerateRoutesUi();
	void Show();

signals:	
	void showRead(bool);

protected:
	Ui_GenerateRoutesUi ui_;

	static void InitializeThread(void* data);
	void InitiliazeVehicles();

protected slots:
	void OnButtonOne();
	void OnButtonAll();
	void OnButtonInit();
	void OnButtonSave();
	void OnButtonReset();
	void Clear();

	void OnCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
};

class CUiCustomRoutes : public QDialog
{
	Q_OBJECT
public:
	CUiCustomRoutes(QWidget* parent = 0);
	~CUiCustomRoutes();
	void Show();

protected:
	Ui_CustomRoutesUi ui_;
protected slots:
	void OnReadFileButton();
	void OnSaveButton();
	void Clear();
	void ShowRead(bool);//show/hide Read button
};

