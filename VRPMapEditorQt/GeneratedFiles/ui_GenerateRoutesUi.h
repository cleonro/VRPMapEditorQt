/********************************************************************************
** Form generated from reading UI file 'GenerateRoutesUi.ui'
**
** Created: Tue Sep 6 07:51:56 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEROUTESUI_H
#define UI_GENERATEROUTESUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GenerateRoutesUi
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButtonCost;
    QToolButton *toolButtonInit;
    QToolButton *toolButtonOne;
    QToolButton *toolButtonAll;
    QFrame *line;
    QToolButton *toolButtonSave;
    QToolButton *toolButtonReset;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *lineHours;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelInitializing;
    QProgressBar *progressBarInitializing;
    QSpacerItem *horizontalSpacer_2;
    QTreeView *treeView;

    void setupUi(QDialog *GenerateRoutesUi)
    {
        if (GenerateRoutesUi->objectName().isEmpty())
            GenerateRoutesUi->setObjectName(QString::fromUtf8("GenerateRoutesUi"));
        GenerateRoutesUi->resize(473, 706);
        verticalLayout = new QVBoxLayout(GenerateRoutesUi);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButtonCost = new QToolButton(GenerateRoutesUi);
        toolButtonCost->setObjectName(QString::fromUtf8("toolButtonCost"));

        horizontalLayout->addWidget(toolButtonCost);

        toolButtonInit = new QToolButton(GenerateRoutesUi);
        toolButtonInit->setObjectName(QString::fromUtf8("toolButtonInit"));

        horizontalLayout->addWidget(toolButtonInit);

        toolButtonOne = new QToolButton(GenerateRoutesUi);
        toolButtonOne->setObjectName(QString::fromUtf8("toolButtonOne"));

        horizontalLayout->addWidget(toolButtonOne);

        toolButtonAll = new QToolButton(GenerateRoutesUi);
        toolButtonAll->setObjectName(QString::fromUtf8("toolButtonAll"));

        horizontalLayout->addWidget(toolButtonAll);

        line = new QFrame(GenerateRoutesUi);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        toolButtonSave = new QToolButton(GenerateRoutesUi);
        toolButtonSave->setObjectName(QString::fromUtf8("toolButtonSave"));

        horizontalLayout->addWidget(toolButtonSave);

        toolButtonReset = new QToolButton(GenerateRoutesUi);
        toolButtonReset->setObjectName(QString::fromUtf8("toolButtonReset"));

        horizontalLayout->addWidget(toolButtonReset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(GenerateRoutesUi);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineHours = new QLineEdit(GenerateRoutesUi);
        lineHours->setObjectName(QString::fromUtf8("lineHours"));
        lineHours->setMaximumSize(QSize(30, 20));

        horizontalLayout->addWidget(lineHours);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelInitializing = new QLabel(GenerateRoutesUi);
        labelInitializing->setObjectName(QString::fromUtf8("labelInitializing"));

        horizontalLayout_2->addWidget(labelInitializing);

        progressBarInitializing = new QProgressBar(GenerateRoutesUi);
        progressBarInitializing->setObjectName(QString::fromUtf8("progressBarInitializing"));
        progressBarInitializing->setMaximumSize(QSize(200, 20));
        progressBarInitializing->setMinimum(0);
        progressBarInitializing->setMaximum(0);
        progressBarInitializing->setValue(-1);

        horizontalLayout_2->addWidget(progressBarInitializing);

        horizontalSpacer_2 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        treeView = new QTreeView(GenerateRoutesUi);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        verticalLayout->addWidget(treeView);


        retranslateUi(GenerateRoutesUi);
        QObject::connect(toolButtonOne, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonOne()));
        QObject::connect(toolButtonAll, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonAll()));
        QObject::connect(toolButtonInit, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonInit()));
        QObject::connect(toolButtonCost, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonCost()));
        QObject::connect(toolButtonSave, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonSave()));
        QObject::connect(toolButtonReset, SIGNAL(clicked()), GenerateRoutesUi, SLOT(OnButtonReset()));

        QMetaObject::connectSlotsByName(GenerateRoutesUi);
    } // setupUi

    void retranslateUi(QDialog *GenerateRoutesUi)
    {
        GenerateRoutesUi->setWindowTitle(QApplication::translate("GenerateRoutesUi", "Rute", 0, QApplication::UnicodeUTF8));
        toolButtonCost->setText(QApplication::translate("GenerateRoutesUi", "COST", 0, QApplication::UnicodeUTF8));
        toolButtonInit->setText(QApplication::translate("GenerateRoutesUi", "INIT", 0, QApplication::UnicodeUTF8));
        toolButtonOne->setText(QApplication::translate("GenerateRoutesUi", "ONE", 0, QApplication::UnicodeUTF8));
        toolButtonAll->setText(QApplication::translate("GenerateRoutesUi", "ALL", 0, QApplication::UnicodeUTF8));
        toolButtonSave->setText(QApplication::translate("GenerateRoutesUi", "SAVE", 0, QApplication::UnicodeUTF8));
        toolButtonReset->setText(QApplication::translate("GenerateRoutesUi", "RESET", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GenerateRoutesUi", "Working Day(Hours)", 0, QApplication::UnicodeUTF8));
        labelInitializing->setText(QApplication::translate("GenerateRoutesUi", "Initializing..", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GenerateRoutesUi: public Ui_GenerateRoutesUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEROUTESUI_H
