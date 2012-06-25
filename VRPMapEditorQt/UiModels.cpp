#include "UiModels.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QListView>
#include <QPixmap>
#include <QItemSelectionModel>

#include "Classes\AppMapEdit\GraphMap\GraphNode.h"
#include "Classes\AppMapEdit\GraphMap\GraphRoute.h"
#include "Classes/AppMapEdit/MapOperationsInput.h"
#include "Classes/AppMapEdit/AppMapEdit.h"


CUiModels::CUiModels()
{
	clist_model_ = new QStandardItemModel();
	clist_model_->setColumnCount(2);
	clist_model_->setHorizontalHeaderItem(0, new QStandardItem("Noduri"));
	clist_model_->setHorizontalHeaderItem(1, new QStandardItem("Cantitati necolectate"));

	QStandardItemModel** models[2] = {
		&routes_ui_model_,
		&croutes_ui_model_
	};
	for(int i = 0; i < 2; i++)
	{
		(*models[i]) = new QStandardItemModel();
		(*models[i])->setColumnCount(5);
		(*models[i])->setHorizontalHeaderItem(0, new QStandardItem("Nume / Tip Veh."));
		(*models[i])->setHorizontalHeaderItem(1, new QStandardItem("Noduri"));
		(*models[i])->setHorizontalHeaderItem(2, new QStandardItem("Distanta"));
		(*models[i])->setHorizontalHeaderItem(3, new QStandardItem("Timp"));
		(*models[i])->setHorizontalHeaderItem(4, new QStandardItem("Cost"));
	}

	unidentified_nodes_ui_model_ = new QStandardItemModel();
	unidentified_nodes_ui_model_->setColumnCount(1);
	unidentified_nodes_ui_model_->setHorizontalHeaderItem(0, new QStandardItem("Noduri neidentificate"));

}


CUiModels::~CUiModels()
{
	delete clist_model_;
	delete routes_ui_model_;
	delete croutes_ui_model_;
	delete unidentified_nodes_ui_model_;
}

CUiModels& CUiModels::GetInstance()
{
	static CUiModels instance;
	return instance;
}

//clist_model access functions
void CUiModels::SetUiForCListModel(QTreeView* ui)
{
	ui->setModel(clist_model_);
	ui->setSortingEnabled(true);
	QItemSelectionModel *clist_selection = ui->selectionModel();
	connect(clist_selection, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
						this, SLOT(OnCListCurrentChanged(const QModelIndex&, const QModelIndex&)));
}

void CUiModels::AddItemToClistModel(OGraphNode* node)
{
	if(node == NULL) {
		return;
	}
	QList<QStandardItem*> it_list;
	QStandardItem* it = new QStandardItem(node->GetName());
	
	float quant = node->GetNodeInf().quantity_;

	QStandardItem* it_quant = new QStandardItem(QString("%1").arg(quant)); 
	void *p = node;
	QVariant dt = qVariantFromValue(p);;
	//dt.fromValue<void*>(p);
	it->setData(dt);
	QPixmap im;
	switch (node->GetType()){
		case OGraphNode::N_CLIENT:
			im.load(":/VRPMapEditorQt/Resources/client.png", "png");
			break;
		case OGraphNode::N_DEPOT:
			im.load(":/VRPMapEditorQt/Resources/depot.png", "png");
			break;
		case OGraphNode::N_START:
			im.load(":/VRPMapEditorQt/Resources/start.png", "png");
			break;
		case OGraphNode::N_TRANSIT:
			im.load(":/VRPMapEditorQt/Resources/transfer.png", "png");
			break;
	}
	if(!im.isNull()){
		it->setData(QVariant(im.scaled(16, 16)),Qt::DecorationRole);
	}
	it->setEditable(false);

	it_list.append(it);
	it_list.append(it_quant);
	//clist_model_->appendRow(it);
	clist_model_->appendRow(it_list);
}

void CUiModels::UpdateItemInCListModel(OGraphNode* node, bool delete_item)
{
	bool found = false;
	QModelIndex idx;
	QModelIndex idx2;
	QStandardItem* it;
	QStandardItem* it2;
	QVariant dt;
	for(int i = 0; i < clist_model_->rowCount(); i++) {
		idx = clist_model_->index(i, 0);
		idx2 = clist_model_->index(i, 1);
		it = clist_model_->itemFromIndex(idx);
		it2 = clist_model_->itemFromIndex(idx2);
		dt = it->data();
		void *p = dt.value<void*>();
		if(p == node) {
			found = true;
			if(delete_item) {
				clist_model_->removeRow(i);
			}
			break;
		}
	}
	if(found && !delete_item) {
		it->setText(node->GetName());
		float quant = node->GetNodeInf().quantity_;
		it2->setText(QString("%1").arg(quant));
	}
}

void CUiModels::ClearCListModel()
{
	while(clist_model_->rowCount()) {
		clist_model_->removeRow(0);
	}
}

void CUiModels::OnCListCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
	QStandardItem* it = clist_model_->itemFromIndex(current);
	if(it == NULL) {
		return;
	}
	QVariant dt = it->data();
	OGraphNode* node = (OGraphNode*)dt.value<void*>();
	if(node == NULL) {
		return;
	}
	MAPOPP.graph_.UnSelectAll();
	node->Select(true);
	((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
}

//routes_ui_model access functions
QStandardItemModel* CUiModels::RoutesModel(int sel)
{
	QStandardItemModel* model = NULL;
	switch(sel) {
	case 0:
		model = routes_ui_model_;
		break;
	case 1:
		model = croutes_ui_model_;
		break;
	}
	return model;
}

void CUiModels::SetUiForRoutesModel(QTreeView* ui, int sel)
{
	ClearRoutesModel(sel);
	QStandardItemModel* model = NULL;
	switch(sel) {
	case 0:
		model = routes_ui_model_;
		break;
	case 1:
		model = croutes_ui_model_;
		break;
	}

	if(model == NULL) {
		return;
	}
	ui->setModel(model);
	QItemSelectionModel *routes_selection_model = ui->selectionModel();
	connect(routes_selection_model, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(OnRoutesCurrentChanged(const QModelIndex&, const QModelIndex&)));
}

void CUiModels::ClearRoutesModel(int sel)
{
	QStandardItemModel* model = NULL;
	switch(sel) {
		case 0:
			model = routes_ui_model_;
			break;
		case 1:
			model = croutes_ui_model_;
			break;
	}

	if(model == NULL) {
		return;
	}

	while(model->rowCount()){
		model->removeRow(0);
	}
	if(sel == 1){
		while(unidentified_nodes_ui_model_->rowCount()){
			unidentified_nodes_ui_model_->removeRow(0);
		}
	}

	const char* item_names[6] = {
		"Luni",
		"Marti",
		"Miercuri",
		"Joi",
		"Vineri",
		"Total"
	};

	//total item has data -3
	//day item has data -2
	//vehicle type (route) item has data -1
	//node item has data the node index in graph
	for(int i = 0; i < 6; i++) {
		QStandardItem* day = new QStandardItem(item_names[i]);
		day->setEditable(false);
		if(i < 5) {
			day->setData(-2);
		} else {
			day->setData(-3);
		}
		QList<QStandardItem*> dayList;
		dayList.append(day);
		QStandardItem* dayNodes = new QStandardItem();
		dayNodes->setEditable(false);
		QStandardItem* dayDistance = new QStandardItem();
		dayDistance->setEditable(false);
		QStandardItem* dayTime = new QStandardItem();
		dayTime->setEditable(false);
		QStandardItem* dayCost = new QStandardItem();
		dayCost->setEditable(false);
		dayList.append(dayNodes);
		dayList.append(dayDistance);
		dayList.append(dayTime);
		dayList.append(dayCost);
		model->appendRow(dayList);
	}
}

void CUiModels::OnRoutesCurrentChanged(const QModelIndex& current, const QModelIndex& previous)
{
	QStandardItemModel* model = (QStandardItemModel*)current.model();
	QModelIndex sibling = current.sibling(current.row(), 0);
	QStandardItem* item = model->itemFromIndex(sibling);

	if(item == NULL) {
		return;
	}
	MAPOPP.graph_.UnSelectAll();

	int data = item->data().toInt();
	
	//node selected
	if(data >= 0) {
		MAPOPP.graph_.GetNode(data)->Select(true);
		((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
		return;
	}

	//total selected
	if(data == -3) {
		for(int i = 0; i < 5; i++) {
			QStandardItem* item_day = model->item(i);
			for(int j = 0; j < item_day->rowCount(); j++) {
				QStandardItem* item_veh = item_day->child(j);
				MarkRoute(item_veh);
			}
		}
		((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
		return;
	}

	//day selected
	if(data == -2) {
		for(int i = 0; i < item->rowCount(); i++) {
			QStandardItem* item_veh = item->child(i);
			MarkRoute(item_veh);
		}
		((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
		return;
	}

	//route (veh type) selected
	if(data == -1) {
		MarkRoute(item);
		((OAppMapEdit*)APPMNGR.GetState())->ReDraw();
		return;
	}
}

void CUiModels::MarkRoute(QStandardItem* item_veh)
{
	int data = item_veh->data().toInt();
	if(data != -1) {
		return;//not a route item
	}
	OVehicleRoute route;
	for(int i = 0; i < item_veh->rowCount(); i++) {
		QStandardItem* item_node = item_veh->child(i);
		int idx = item_node->data().toInt();
		if(idx < 0) {
			return;//not a correct route
		}
		route.Sequence().push_back(idx);		
	}
	MAPOPP.GetGenerator().MarkRoute(route);
}

//unidentified_nodes_ui_model access functions
void CUiModels::SetUiForUnidentifiedNodesModel(QListView* ui)
{
	ui->setModel(unidentified_nodes_ui_model_);
	//ui->setSor;
}