/********************************************************************************
** Form generated from reading UI file 'CustomRoutesUi.ui'
**
** Created: Mon May 30 22:53:52 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMROUTESUI_H
#define UI_CUSTOMROUTESUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CustomRoutesUi
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QTreeView *treeView;
    QLabel *label_2;
    QListView *listView;

    void setupUi(QDialog *CustomRoutesUi)
    {
        if (CustomRoutesUi->objectName().isEmpty())
            CustomRoutesUi->setObjectName(QString::fromUtf8("CustomRoutesUi"));
        CustomRoutesUi->resize(498, 703);
        verticalLayout = new QVBoxLayout(CustomRoutesUi);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(CustomRoutesUi);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(100, 20));
        pushButton->setMaximumSize(QSize(100, 20));

        horizontalLayout->addWidget(pushButton);

        toolButton = new QToolButton(CustomRoutesUi);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(CustomRoutesUi);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        treeView = new QTreeView(CustomRoutesUi);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);

        label_2 = new QLabel(CustomRoutesUi);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        listView = new QListView(CustomRoutesUi);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMaximumSize(QSize(16777215, 150));

        verticalLayout->addWidget(listView);


        retranslateUi(CustomRoutesUi);
        QObject::connect(pushButton, SIGNAL(clicked()), CustomRoutesUi, SLOT(OnReadFileButton()));
        QObject::connect(toolButton, SIGNAL(clicked()), CustomRoutesUi, SLOT(OnSaveButton()));

        QMetaObject::connectSlotsByName(CustomRoutesUi);
    } // setupUi

    void retranslateUi(QDialog *CustomRoutesUi)
    {
        CustomRoutesUi->setWindowTitle(QApplication::translate("CustomRoutesUi", "Custom Routes", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CustomRoutesUi", "Read File...", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("CustomRoutesUi", "SAVE", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CustomRoutesUi", "Routes", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CustomRoutesUi", "Unidentified nodes", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CustomRoutesUi: public Ui_CustomRoutesUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMROUTESUI_H
