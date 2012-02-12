#include "GenerateRoutesUi.h"
#include "Classes/AppMapEdit/MapOperationsInput.h"
#include "Classes/AppMapEdit/AppMapEdit.h"
#include <process.h>
#include <QFileDialog>
#include <fstream>
#include "UiModels.h"

CGenerateRoutesUi::CGenerateRoutesUi(QWidget* parent) : QDialog(parent)
{
	ui_.setupUi(this);

	//ui_.treeView->setModel(MAPOPP.GetGenerator().GetUiModel());
	UIMDLS.SetUiForRoutesModel(ui_.treeView);
	ui_.treeView->expandAll();
	if(!MAPOPP.GetGenerator().Initialized()) {
		ui_.toolButtonAll->setDisabled(true);
		ui_.toolButtonOne->setDisabled(true);
		ui_.toolButtonSave->setDisabled(true);
		ui_.toolButtonReset->setDisabled(true);
	} else {
		ui_.toolButtonInit->setDisabled(true);
	}
	ui_.progressBarInitializing->hide();
	ui_.labelInitializing->hide();

// 	QItemSelectionModel* sel_model = ui_.treeView->selectionModel();
// 	connect(sel_model, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
// 			this, SLOT(OnCurrentChanged(const QModelIndex&, const QModelIndex&)));
}


CGenerateRoutesUi::~CGenerateRoutesUi()
{
	
}

void CGenerateRoutesUi::Show()
{
	//ui_.treeView->setModel(MAPOPP.GetGenerator().GetUiModel());
	this->show();
}

void CGenerateRoutesUi::OnButtonOne()
{
	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	if(generator.temp_day_ >= NDAYS) {
		return;
	}

	float r;
	QString hours = ui_.lineHours->text();
	r = atof(hours.toAscii().data());
	if(r > 0) {
		generator.max_time_ = r;
	}

	int vehtype = generator.FindAvVehType();
	if(vehtype < 0) {
		generator.temp_day_++;
		generator.InitTempData();
		OnButtonOne();
		return;
	}

	OVehicleRoute route;
	generator.temp_vehicles_[vehtype]--;
	generator.FindLRouteForOneVehicle(vehtype, generator.temp_day_, route);

	if(route.Sequence().size() > 1) {
		generator.MarkRoute(route);
		generator.AddRouteToQtModel(route, generator.temp_day_);
		generator.all_routes_->push_back(route);
	}

	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

void CGenerateRoutesUi::OnButtonAll()
{
	ORoutesGenerator& generator = MAPOPP.GetGenerator();

	float r;
	QString hours = ui_.lineHours->text();
	r = atof(hours.toAscii().data());
	if(r > 0) {
		generator.max_time_ = r;
	}

	generator.FindRoutes();
	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

void CGenerateRoutesUi::OnButtonSave()
{
	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), app_path, tr("Xml files (*.xml)"));
	if(file_name == "") {
		return;
	}

	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	generator.PrintRoutesXml(file_name.toAscii().data());
}

void CGenerateRoutesUi::OnButtonReset()
{
	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	generator.Clear();

	this->Clear();
}

void CGenerateRoutesUi::OnButtonInit()
{
	ui_.toolButtonInit->setDisabled(true);

	ui_.labelInitializing->show();
	ui_.progressBarInitializing->show();

	//_beginthread(CGenerateRoutesUi::InitializeThread, 0, (void*)this);
	InitializeThread((void*)this);
	emit showRead(true);
}

 void CGenerateRoutesUi::InitializeThread(void* data)
 {
	 CGenerateRoutesUi* dlg = (CGenerateRoutesUi*)data;
	 MAPOPP.GetGenerator().Init(MAPOPP.graph_);

	 dlg->ui_.labelInitializing->hide();
	 dlg->ui_.progressBarInitializing->hide();

	 dlg->ui_.toolButtonAll->setEnabled(true);
	 dlg->ui_.toolButtonOne->setEnabled(true);
	 dlg->ui_.toolButtonSave->setDisabled(false);
	 dlg->ui_.toolButtonReset->setDisabled(false);
 }

 void CGenerateRoutesUi::Clear()
 {
	 ui_.toolButtonInit->setDisabled(false);

	 this->ui_.toolButtonAll->setEnabled(false);
	 this->ui_.toolButtonOne->setEnabled(false);
	 this->ui_.toolButtonSave->setDisabled(true);
	 this->ui_.toolButtonReset->setDisabled(true);

	 emit showRead(false);
	 UIMDLS.ClearRoutesModel();
	 //ui_.treeView->setModel( MAPOPP.GetGenerator().GetUiModel());
 }
  
 void CGenerateRoutesUi::OnCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
 {
	printf("\n OnCurrentChanged\n");
 }
 
//class CUiCustomRoutes
CUiCustomRoutes::CUiCustomRoutes(QWidget* parent) : QDialog(parent)
{
	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	ui_.setupUi(this);
	//ui_.treeView->setModel(generator.customRoutesUiModel_);
	UIMDLS.SetUiForRoutesModel(ui_.treeView, 1);
	ui_.treeView->expandAll();
	//ui_.listView->setModel(generator.unidentified_nodes_ui_model_);
	UIMDLS.SetUiForUnidentifiedNodesModel(ui_.listView);

	ui_.pushButton->setEnabled(false);
	ui_.toolButton->setEnabled(false);
}

CUiCustomRoutes::~CUiCustomRoutes()
{

}

void CUiCustomRoutes::Show()
{
	//ORoutesGenerator& generator = MAPOPP.GetGenerator();
	//ui_.treeView->setModel(generator.customRoutesUiModel_);
	this->show();
}

void CUiCustomRoutes::ShowRead(bool show)
{
	ui_.pushButton->setEnabled(show);
	ui_.toolButton->setEnabled(show);

	//ORoutesGenerator& generator = MAPOPP.GetGenerator();
	//ui_.treeView->setModel(generator.customRoutesUiModel_);
}

void CUiCustomRoutes::Clear()
{

}

void CUiCustomRoutes::OnReadFileButton()
{
	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open Custom Routes File"), app_path, tr("Maps (*.txt)"));
	if(file_name == "") {
		return;
	}
	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	
	generator.ClearCustomRoutes();
	UIMDLS.ClearRoutesModel(1);
// 	ui_.treeView->setModel(generator.customRoutesUiModel_);

	generator.InitDaysQuantities();
	generator.ParseCustomRoutesFile(file_name.toAscii().data());
	generator.InitDaysQuantities();
}

 void CUiCustomRoutes::OnSaveButton()
 {
// 	 ORoutesGenerator& generator = MAPOPP.GetGenerator();
// 	 std::fstream f("tst_model_print", std::ios::out);
// 	 f<<generator.customRoutesUiModel_;
// 	 f.close();
// 	 generator.PrintRoutes(1);
	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), app_path, tr("Xml files (*.xml)"));
	if(file_name == "") {
		return;
	}

	ORoutesGenerator& generator = MAPOPP.GetGenerator();
	generator.PrintRoutesXml(file_name.toAscii().data(), 1);
 }