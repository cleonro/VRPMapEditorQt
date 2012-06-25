#include "vrpmapeditorqt.h"

#include <process.h>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "Classes\AppMapEdit\MapOperationsInput.h"
#include "ui_FindNodeUi.h"
#include "Classes\AppBaseState.h"
#include "Classes\AppMapEdit\AppMapEdit.h"
#include "UiModels.h"
#include "AppMapEdit/OMapEvent.h"

VRPMapEditorQt::VRPMapEditorQt(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	this->setBaseSize(QSize(1024, 768));
	ui.setupUi(this);
	
	ui.actionMoveMap->setChecked(true);
	nChecked_ = 0;

	actions_.push_back(ui.actionMoveMap);		//0
	actions_.push_back(ui.actionAddClient);		//1
	actions_.push_back(ui.actionAddStart);		//2
	actions_.push_back(ui.actionAddDepot);		//3
	actions_.push_back(ui.actionAddTransfer);	//4
	actions_.push_back(ui.actionAddConnection);	//5
	actions_.push_back(ui.actionErase);			//6
	actions_.push_back(ui.actionInf);			//7
	actions_.push_back(ui.actionCinf);			//8
	amax_ = 8;
	documentName_ = "untitled";
	appName_ = "VRPMapEditorQt";
	documentFilePath_ = ".\\";
	saved_ = true;
	this->setWindowTitle(appName_ + " - " + documentName_);
	connect(&(MAPOPP), SIGNAL(mapChanged()), this, SLOT(MapChanged()));
	QApplication* inst = (QApplication*)QApplication::instance();//?

	dlgGenerateRoutes_ = new CGenerateRoutesUi(this);
	dlgCustomRoutes_ = new CUiCustomRoutes(this);

	connect(this, SIGNAL(clearGenRoutesDlg()), dlgGenerateRoutes_, SLOT(Clear()));
	connect(dlgGenerateRoutes_, SIGNAL(showRead(bool)),
			dlgCustomRoutes_, SLOT(ShowRead(bool)));
}

VRPMapEditorQt::~VRPMapEditorQt()
{
	delete dlgGenerateRoutes_;
}

void VRPMapEditorQt::MapChanged()
{
	if(saved_) {
		this->setWindowTitle(this->windowTitle() + "*");
		saved_ = false;
	}
}

QSize VRPMapEditorQt::minimumSizeHint() const
{
	return QSize(1024, 768);
}

QSize VRPMapEditorQt::sizeHint() const
{
	return QSize(1024, 768);
}

void VRPMapEditorQt::ActionTriggered(QAction* act)
{
	if(act == ui.actionNew) {
		New();
		return;
	}

	if(act == ui.actionOpen) {
		Open();
		return;
	}

	if(act == ui.actionSave) {
		Save();
		return;
	}

	if(act == ui.actionSave_As) {
		SaveAs();
		return;
	}
	
	if(act == ui.actionImport_Xml) {
		ImportXml();
		return;
	}

	if(act == ui.actionGenereaza_rute) {
		GenerateRoutes();
		return;
	}

	if(act == ui.actionGaseste_nod) {
		FindNode();
		return;
	}

	if(act == ui.actionRute_externe) {
		CustomRoutes();
		return;
	}

	if(act == ui.actionGenereaza_muchii) {
		GenereazaConexiuni();
		return;
	}

	int nCmdID = actions_.indexOf(act);
	
	if(nCmdID == nChecked_) {
		return;
	}

	actions_[nChecked_]->setChecked(false);
	nChecked_ = nCmdID;
	
	switch(nCmdID) {
		case 0:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_MOVE);
			break;
		case 1:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_ADD_NODE_CL);
			break;
		case 2:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_ADD_NODE_ST);
			break;
		case 3:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_ADD_NODE_DP);
			break;
		case 4:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_ADD_NODE_TR);
			break;
		case 5:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_ADD_ROUTE);
			break;
		case 6:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_DEL);
			break;
		case 7:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_NODE_INF);
			break;
		case 8:
			MAPOPP.ChangeActionState(OMapOperationsInput::MAP_NODE_CINF);
			break;
		
	}
}

void VRPMapEditorQt::closeEvent(QCloseEvent * event)
{
	if(!saved_) {
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Save) {
			Save();
		}
	}
	QApplication::quit();
}

void VRPMapEditorQt::Save()
{
	if(saved_) {
		return;
	}
	QString app_path = QApplication::applicationDirPath();
	if(documentName_ == "untitled") {
		QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), app_path, tr("Maps (*.vrpm)"));
		if(file_name == "") {
			return;
		}
		documentFilePath_ = file_name;
	}
	QFile file(documentFilePath_);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file); 
	out << MAPOPP;
	documentName_ = file.fileName();
	this->setWindowTitle(appName_ + " - " + documentName_);
	saved_ = true;
}

void VRPMapEditorQt::SaveAs()
{
	QString app_path = QApplication::applicationDirPath();

		QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), app_path, tr("Maps (*.vrpm)"));
		if(file_name == "") {
			return;
		}
		documentFilePath_ = file_name;
	
	QFile file(documentFilePath_);
	file.open(QIODevice::WriteOnly);
	QDataStream out(&file); 
	out << MAPOPP;
	documentName_ = file.fileName();
	this->setWindowTitle(appName_ + " - " + documentName_);
	saved_ = true;
}

void VRPMapEditorQt::New()
{
	if(!saved_) {
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Save) {
			Save();
		} else if(ret == QMessageBox::Cancel) {
			return;
		}
	}

	MAPOPP.Clear();
	emit clearGenRoutesDlg();
	UIMDLS.ClearCListModel();

	documentName_ = "untitled";
	this->setWindowTitle(appName_ + " - " + documentName_);
}

void VRPMapEditorQt::Open()
{
	if(!saved_) {
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Save) {
			Save();
		} else if(ret == QMessageBox::Cancel) {
			return;
		}
	}

	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open File"), app_path, tr("Maps (*.vrpm)"));
	if(file_name == "") {
		return;
	}

	UIMDLS.ClearCListModel();
	MAPOPP.Clear();
	emit clearGenRoutesDlg();

	QFile file(file_name);
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	in>>MAPOPP;
	documentName_ = file.fileName();
	documentFilePath_ = documentName_;
	this->setWindowTitle(appName_ + " - " + documentName_);
	saved_ = true;

	for(int i = 0; i < MAPOPP.graph_.GetSize(); i++) {
		UIMDLS.AddItemToClistModel(MAPOPP.graph_.GetNode(i));
	}
}

void VRPMapEditorQt::ImportXml()
{
	if(!saved_) {
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Save) {
			Save();
		} else if(ret == QMessageBox::Cancel) {
			return;
		}
	}

	QString app_path = QApplication::applicationDirPath();
	QString file_name = QFileDialog::getOpenFileName(this, tr("Import Xml File"), app_path, tr("Xml (*.xml)"));
	if(file_name == "") {
		return;
	}

	MAPOPP.ImportGraphFromXml(file_name.toAscii().data());
	documentName_ = "untitled";
	saved_ = false;
	this->setWindowTitle(appName_ + " - " + documentName_ + "*");
}

void VRPMapEditorQt::GenerateRoutes()
{
	dlgGenerateRoutes_->Show();
}

void VRPMapEditorQt::FindNode()
{
	QDialog dlg;
	Ui_FindNodeDlg ui;
	ui.setupUi(&dlg);
	if(dlg.exec() == QDialog::Accepted) {
		QString node = ui.lineNodeName->text();
		//const char* name = node.toAscii().data();
		int indx = atoi(node.toAscii().data());
		if(indx == 0) {
			if(strcmp("0", node.toAscii().data()) != 0) {
				indx = -1;
			}
		}
		MAPOPP.FindNode(node.toAscii().data(), indx);
		((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
	}
}

void VRPMapEditorQt::CustomRoutes()
{
	dlgCustomRoutes_->Show();
}

void VRPMapEditorQt::GenereazaConexiuni()
{
	QMessageBox msgBox;
	msgBox.setText(tr("This operation could erase all the existing graph connections."));
	msgBox.setInformativeText(tr("Do you want to continue?"));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Save);
	int ret = msgBox.exec();
	if(ret == QMessageBox::No) {
		return;
	}
	CCentralWidget* cw = (CCentralWidget*)this->centralWidget();
	cw->StartTimer();

	void *param = (void*)cw;
	_beginthread(VRPMapEditorQt::StartThreadGenerateConnections, 0, param);
}

void VRPMapEditorQt::StartThreadGenerateConnections(void* param)
{
	CCentralWidget* cw = (CCentralWidget*)param;
	MAPOPP.GenerateRoutes();
	//cw->StopTimer();
	OMapEvent* event = new OMapEvent();
	event->Type() = OMapEvent::E_MAP_STOP_TIMER;
	QApplication::postEvent(MAPOPP.View(), event);
}