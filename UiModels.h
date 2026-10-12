#pragma once
#include <QObject>

#define UIMDLS CUiModels::GetInstance()

class QStandardItemModel;
class QStandardItem;
class QTreeView;
class QListView;
class QModelIndex;
class OGraphNode;
class OGraphRoute;

class CUiModels : QObject
{
	Q_OBJECT
public:
	static CUiModels& GetInstance();

	//clist_model access functions;
	void SetUiForCListModel(QTreeView* ui);
	void AddItemToClistModel(OGraphNode*);
	void UpdateItemInCListModel(OGraphNode*, bool delete_item = false);
	void ClearCListModel();
	QStandardItemModel* CListModel() {return clist_model_;}

	//routes_ui_model access functions, sel = 0 routes_ui_model_, sel = 1 croutes_ui_model_
	QStandardItemModel* RoutesModel(int sel = 0);
	void SetUiForRoutesModel(QTreeView* ui, int sel = 0);
	void ClearRoutesModel(int sel = 0);

	//unidentified_nodes_ui_model access functions
	inline QStandardItemModel* UnidentifiedNodesModel() {return unidentified_nodes_ui_model_;}
	void SetUiForUnidentifiedNodesModel(QListView* ui);

protected slots:
	void OnCListCurrentChanged(const QModelIndex& current, const QModelIndex& previous);
	void OnRoutesCurrentChanged(const QModelIndex& current, const QModelIndex& previous);

protected:
	CUiModels();
	~CUiModels();

	QStandardItemModel* clist_model_;//nodes list in central widget;
	QStandardItemModel* routes_ui_model_;//model for treeview in routes generator widget
	QStandardItemModel* croutes_ui_model_;//model for treeview in custom routes widget
	QStandardItemModel* unidentified_nodes_ui_model_;

	void MarkRoute(QStandardItem* item_veh);//mark selected a route from model (item_veh is a route item)
};

