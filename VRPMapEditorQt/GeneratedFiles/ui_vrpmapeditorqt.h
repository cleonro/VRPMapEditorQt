/********************************************************************************
** Form generated from reading UI file 'vrpmapeditorqt.ui'
**
** Created: Sun May 29 22:43:57 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRPMAPEDITORQT_H
#define UI_VRPMAPEDITORQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include "ccentralwidget.h"

QT_BEGIN_NAMESPACE

class Ui_VRPMapEditorQtClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionGenereaza_muchii;
    QAction *actionGenereaza_rute;
    QAction *actionGaseste_nod;
    QAction *actionMoveMap;
    QAction *actionAddClient;
    QAction *actionAddStart;
    QAction *actionAddDepot;
    QAction *actionAddTransfer;
    QAction *actionAddConnection;
    QAction *actionErase;
    QAction *actionInf;
    QAction *actionCinf;
    QAction *actionImport_Xml;
    QAction *actionRute_externe;
    CCentralWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuOperatii;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *VRPMapEditorQtClass)
    {
        if (VRPMapEditorQtClass->objectName().isEmpty())
            VRPMapEditorQtClass->setObjectName(QString::fromUtf8("VRPMapEditorQtClass"));
        VRPMapEditorQtClass->resize(600, 400);
        actionNew = new QAction(VRPMapEditorQtClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(VRPMapEditorQtClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(VRPMapEditorQtClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(VRPMapEditorQtClass);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionGenereaza_muchii = new QAction(VRPMapEditorQtClass);
        actionGenereaza_muchii->setObjectName(QString::fromUtf8("actionGenereaza_muchii"));
        actionGenereaza_rute = new QAction(VRPMapEditorQtClass);
        actionGenereaza_rute->setObjectName(QString::fromUtf8("actionGenereaza_rute"));
        actionGaseste_nod = new QAction(VRPMapEditorQtClass);
        actionGaseste_nod->setObjectName(QString::fromUtf8("actionGaseste_nod"));
        actionMoveMap = new QAction(VRPMapEditorQtClass);
        actionMoveMap->setObjectName(QString::fromUtf8("actionMoveMap"));
        actionMoveMap->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/move.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveMap->setIcon(icon);
        actionAddClient = new QAction(VRPMapEditorQtClass);
        actionAddClient->setObjectName(QString::fromUtf8("actionAddClient"));
        actionAddClient->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/client.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddClient->setIcon(icon1);
        actionAddStart = new QAction(VRPMapEditorQtClass);
        actionAddStart->setObjectName(QString::fromUtf8("actionAddStart"));
        actionAddStart->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddStart->setIcon(icon2);
        actionAddDepot = new QAction(VRPMapEditorQtClass);
        actionAddDepot->setObjectName(QString::fromUtf8("actionAddDepot"));
        actionAddDepot->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/depot.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddDepot->setIcon(icon3);
        actionAddTransfer = new QAction(VRPMapEditorQtClass);
        actionAddTransfer->setObjectName(QString::fromUtf8("actionAddTransfer"));
        actionAddTransfer->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/transfer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddTransfer->setIcon(icon4);
        actionAddConnection = new QAction(VRPMapEditorQtClass);
        actionAddConnection->setObjectName(QString::fromUtf8("actionAddConnection"));
        actionAddConnection->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/connection.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAddConnection->setIcon(icon5);
        actionErase = new QAction(VRPMapEditorQtClass);
        actionErase->setObjectName(QString::fromUtf8("actionErase"));
        actionErase->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/erase.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionErase->setIcon(icon6);
        actionInf = new QAction(VRPMapEditorQtClass);
        actionInf->setObjectName(QString::fromUtf8("actionInf"));
        actionInf->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/inf.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInf->setIcon(icon7);
        actionCinf = new QAction(VRPMapEditorQtClass);
        actionCinf->setObjectName(QString::fromUtf8("actionCinf"));
        actionCinf->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/cinf.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCinf->setIcon(icon8);
        actionImport_Xml = new QAction(VRPMapEditorQtClass);
        actionImport_Xml->setObjectName(QString::fromUtf8("actionImport_Xml"));
        actionRute_externe = new QAction(VRPMapEditorQtClass);
        actionRute_externe->setObjectName(QString::fromUtf8("actionRute_externe"));
        centralWidget = new CCentralWidget(VRPMapEditorQtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        VRPMapEditorQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VRPMapEditorQtClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuOperatii = new QMenu(menuBar);
        menuOperatii->setObjectName(QString::fromUtf8("menuOperatii"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        VRPMapEditorQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VRPMapEditorQtClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        VRPMapEditorQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VRPMapEditorQtClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        VRPMapEditorQtClass->setStatusBar(statusBar);
        toolBar = new QToolBar(VRPMapEditorQtClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        VRPMapEditorQtClass->addToolBar(Qt::LeftToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuOperatii->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionImport_Xml);
        menuOperatii->addAction(actionGenereaza_muchii);
        menuOperatii->addAction(actionGenereaza_rute);
        menuOperatii->addAction(actionGaseste_nod);
        menuOperatii->addAction(actionRute_externe);
        toolBar->addAction(actionMoveMap);
        toolBar->addAction(actionAddClient);
        toolBar->addAction(actionAddStart);
        toolBar->addAction(actionAddDepot);
        toolBar->addAction(actionAddTransfer);
        toolBar->addAction(actionAddConnection);
        toolBar->addAction(actionErase);
        toolBar->addAction(actionInf);
        toolBar->addAction(actionCinf);

        retranslateUi(VRPMapEditorQtClass);
        QObject::connect(toolBar, SIGNAL(actionTriggered(QAction*)), VRPMapEditorQtClass, SLOT(ActionTriggered(QAction*)));
        QObject::connect(menuBar, SIGNAL(triggered(QAction*)), VRPMapEditorQtClass, SLOT(ActionTriggered(QAction*)));

        QMetaObject::connectSlotsByName(VRPMapEditorQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *VRPMapEditorQtClass)
    {
        VRPMapEditorQtClass->setWindowTitle(QApplication::translate("VRPMapEditorQtClass", "VRPMapEditorQt", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("VRPMapEditorQtClass", "New", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("VRPMapEditorQtClass", "Open...", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("VRPMapEditorQtClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_As->setText(QApplication::translate("VRPMapEditorQtClass", "Save As...", 0, QApplication::UnicodeUTF8));
        actionGenereaza_muchii->setText(QApplication::translate("VRPMapEditorQtClass", "Genereaza muchii", 0, QApplication::UnicodeUTF8));
        actionGenereaza_rute->setText(QApplication::translate("VRPMapEditorQtClass", "Genereaza rute...", 0, QApplication::UnicodeUTF8));
        actionGaseste_nod->setText(QApplication::translate("VRPMapEditorQtClass", "Gaseste nod...", 0, QApplication::UnicodeUTF8));
        actionMoveMap->setText(QApplication::translate("VRPMapEditorQtClass", "moveMap", 0, QApplication::UnicodeUTF8));
        actionAddClient->setText(QApplication::translate("VRPMapEditorQtClass", "addClient", 0, QApplication::UnicodeUTF8));
        actionAddStart->setText(QApplication::translate("VRPMapEditorQtClass", "addStart", 0, QApplication::UnicodeUTF8));
        actionAddDepot->setText(QApplication::translate("VRPMapEditorQtClass", "addDepot", 0, QApplication::UnicodeUTF8));
        actionAddTransfer->setText(QApplication::translate("VRPMapEditorQtClass", "addTransfer", 0, QApplication::UnicodeUTF8));
        actionAddConnection->setText(QApplication::translate("VRPMapEditorQtClass", "addConnection", 0, QApplication::UnicodeUTF8));
        actionErase->setText(QApplication::translate("VRPMapEditorQtClass", "erase", 0, QApplication::UnicodeUTF8));
        actionInf->setText(QApplication::translate("VRPMapEditorQtClass", "inf", 0, QApplication::UnicodeUTF8));
        actionCinf->setText(QApplication::translate("VRPMapEditorQtClass", "cinf", 0, QApplication::UnicodeUTF8));
        actionImport_Xml->setText(QApplication::translate("VRPMapEditorQtClass", "Import Xml...", 0, QApplication::UnicodeUTF8));
        actionRute_externe->setText(QApplication::translate("VRPMapEditorQtClass", "Rute externe...", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("VRPMapEditorQtClass", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("VRPMapEditorQtClass", "Edit", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("VRPMapEditorQtClass", "View", 0, QApplication::UnicodeUTF8));
        menuOperatii->setTitle(QApplication::translate("VRPMapEditorQtClass", "Operatii", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("VRPMapEditorQtClass", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("VRPMapEditorQtClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VRPMapEditorQtClass: public Ui_VRPMapEditorQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRPMAPEDITORQT_H
