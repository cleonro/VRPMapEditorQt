/********************************************************************************
** Form generated from reading UI file 'FindNodeUi.ui'
**
** Created: Mon May 30 03:00:22 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDNODEUI_H
#define UI_FINDNODEUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindNodeDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineNodeName;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;

    void setupUi(QDialog *FindNodeDlg)
    {
        if (FindNodeDlg->objectName().isEmpty())
            FindNodeDlg->setObjectName(QString::fromUtf8("FindNodeDlg"));
        FindNodeDlg->resize(200, 85);
        FindNodeDlg->setMinimumSize(QSize(200, 85));
        FindNodeDlg->setMaximumSize(QSize(200, 85));
        verticalLayout = new QVBoxLayout(FindNodeDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(FindNodeDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineNodeName = new QLineEdit(FindNodeDlg);
        lineNodeName->setObjectName(QString::fromUtf8("lineNodeName"));

        horizontalLayout->addWidget(lineNodeName);


        verticalLayout->addLayout(horizontalLayout);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(FindNodeDlg);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(FindNodeDlg);
        QObject::connect(okButton, SIGNAL(clicked()), FindNodeDlg, SLOT(accept()));

        QMetaObject::connectSlotsByName(FindNodeDlg);
    } // setupUi

    void retranslateUi(QDialog *FindNodeDlg)
    {
        FindNodeDlg->setWindowTitle(QApplication::translate("FindNodeDlg", "Find Node", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FindNodeDlg", "Node:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("FindNodeDlg", "Find Node", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FindNodeDlg: public Ui_FindNodeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDNODEUI_H
