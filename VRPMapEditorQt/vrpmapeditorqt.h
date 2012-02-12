#ifndef VRPMAPEDITORQT_H
#define VRPMAPEDITORQT_H

#include <QtGui/QMainWindow>
#include "ui_vrpmapeditorqt.h"
#include <QVector>
#include "GenerateRoutesUi.h"

class VRPMapEditorQt : public QMainWindow
{
	Q_OBJECT

public:
	VRPMapEditorQt(QWidget *parent = 0, Qt::WFlags flags = 0);
	~VRPMapEditorQt();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

signals:
	void clearGenRoutesDlg();

protected slots:
	void ActionTriggered(QAction*);
	void MapChanged();

protected:
	void closeEvent(QCloseEvent * event);
	static void StartThreadGenerateConnections(void* param);
private:
	Ui::VRPMapEditorQtClass ui;
	QVector<QAction*> actions_;
	int amax_;//number of actions in toolbar
	int nChecked_;//action that is currently checked
	QString documentName_;
	QString documentFilePath_;
	QString appName_;
	bool	saved_;
	CGenerateRoutesUi* dlgGenerateRoutes_;
	CUiCustomRoutes* dlgCustomRoutes_;

	void New();
	void Save();
	void SaveAs();
	void Open();
	void ImportXml();
	void GenerateRoutes();
	void FindNode();
	void CustomRoutes();
	void GenereazaConexiuni();
};

#endif // VRPMAPEDITORQT_H
