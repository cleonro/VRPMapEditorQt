/********************************************************************************
** Form generated from reading UI file 'nodeviewdialog.ui'
**
** Created: Sun May 15 01:44:38 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEVIEWDIALOG_H
#define UI_NODEVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeViewDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QGroupBox *groupBox;
    QGroupBox *groupBox_2;
    QWidget *widget;
    QFormLayout *formLayout_2;
    QLabel *labelAccessibility;
    QLineEdit *lineAccessibility;
    QLabel *labelHabitants;
    QLineEdit *lineEditHabitants;
    QLabel *labelContracts;
    QLineEdit *lineEditContracts;
    QLabel *labelPrice;
    QLineEdit *lineEditPrice;
    QWidget *widget1;
    QFormLayout *formLayout;
    QLabel *labelType;
    QLineEdit *lineType;
    QLabel *labelName;
    QLineEdit *lineName;
    QLabel *labelTime;
    QLineEdit *lineTime;
    QLabel *labelQuantity;
    QLineEdit *lineQuantity;
    QLabel *labelVehicles;
    QLineEdit *lineVehicles;

    void setupUi(QDialog *NodeViewDialog)
    {
        if (NodeViewDialog->objectName().isEmpty())
            NodeViewDialog->setObjectName(QString::fromUtf8("NodeViewDialog"));
        NodeViewDialog->resize(325, 350);
        NodeViewDialog->setMinimumSize(QSize(325, 350));
        NodeViewDialog->setMaximumSize(QSize(325, 350));
        layoutWidget = new QWidget(NodeViewDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 300, 291, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);

        groupBox = new QGroupBox(NodeViewDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 291, 141));
        groupBox_2 = new QGroupBox(NodeViewDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 170, 291, 121));
        widget = new QWidget(NodeViewDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 180, 201, 111));
        formLayout_2 = new QFormLayout(widget);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        labelAccessibility = new QLabel(widget);
        labelAccessibility->setObjectName(QString::fromUtf8("labelAccessibility"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, labelAccessibility);

        lineAccessibility = new QLineEdit(widget);
        lineAccessibility->setObjectName(QString::fromUtf8("lineAccessibility"));
        lineAccessibility->setMaximumSize(QSize(70, 20));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineAccessibility);

        labelHabitants = new QLabel(widget);
        labelHabitants->setObjectName(QString::fromUtf8("labelHabitants"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, labelHabitants);

        lineEditHabitants = new QLineEdit(widget);
        lineEditHabitants->setObjectName(QString::fromUtf8("lineEditHabitants"));
        lineEditHabitants->setMaximumSize(QSize(70, 20));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEditHabitants);

        labelContracts = new QLabel(widget);
        labelContracts->setObjectName(QString::fromUtf8("labelContracts"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, labelContracts);

        lineEditContracts = new QLineEdit(widget);
        lineEditContracts->setObjectName(QString::fromUtf8("lineEditContracts"));
        lineEditContracts->setMaximumSize(QSize(70, 20));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEditContracts);

        labelPrice = new QLabel(widget);
        labelPrice->setObjectName(QString::fromUtf8("labelPrice"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, labelPrice);

        lineEditPrice = new QLineEdit(widget);
        lineEditPrice->setObjectName(QString::fromUtf8("lineEditPrice"));
        lineEditPrice->setMaximumSize(QSize(70, 20));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEditPrice);

        widget1 = new QWidget(NodeViewDialog);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 20, 271, 126));
        formLayout = new QFormLayout(widget1);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        labelType = new QLabel(widget1);
        labelType->setObjectName(QString::fromUtf8("labelType"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelType);

        lineType = new QLineEdit(widget1);
        lineType->setObjectName(QString::fromUtf8("lineType"));
        lineType->setEnabled(false);
        lineType->setMaximumSize(QSize(100, 20));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineType);

        labelName = new QLabel(widget1);
        labelName->setObjectName(QString::fromUtf8("labelName"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelName);

        lineName = new QLineEdit(widget1);
        lineName->setObjectName(QString::fromUtf8("lineName"));
        lineName->setMaximumSize(QSize(100, 20));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineName);

        labelTime = new QLabel(widget1);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelTime);

        lineTime = new QLineEdit(widget1);
        lineTime->setObjectName(QString::fromUtf8("lineTime"));
        lineTime->setMaximumSize(QSize(100, 20));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineTime);

        labelQuantity = new QLabel(widget1);
        labelQuantity->setObjectName(QString::fromUtf8("labelQuantity"));

        formLayout->setWidget(3, QFormLayout::LabelRole, labelQuantity);

        lineQuantity = new QLineEdit(widget1);
        lineQuantity->setObjectName(QString::fromUtf8("lineQuantity"));
        lineQuantity->setMaximumSize(QSize(100, 20));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineQuantity);

        labelVehicles = new QLabel(widget1);
        labelVehicles->setObjectName(QString::fromUtf8("labelVehicles"));

        formLayout->setWidget(4, QFormLayout::LabelRole, labelVehicles);

        lineVehicles = new QLineEdit(widget1);
        lineVehicles->setObjectName(QString::fromUtf8("lineVehicles"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineVehicles);


        retranslateUi(NodeViewDialog);
        QObject::connect(okButton, SIGNAL(clicked()), NodeViewDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), NodeViewDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NodeViewDialog);
    } // setupUi

    void retranslateUi(QDialog *NodeViewDialog)
    {
        NodeViewDialog->setWindowTitle(QApplication::translate("NodeViewDialog", "Informatii nod", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NodeViewDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("NodeViewDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        groupBox_2->setTitle(QString());
        labelAccessibility->setText(QApplication::translate("NodeViewDialog", "Indice de accesibilitate", 0, QApplication::UnicodeUTF8));
        labelHabitants->setText(QApplication::translate("NodeViewDialog", "Numar de locuitori", 0, QApplication::UnicodeUTF8));
        labelContracts->setText(QApplication::translate("NodeViewDialog", "Numar de contracte", 0, QApplication::UnicodeUTF8));
        labelPrice->setText(QApplication::translate("NodeViewDialog", "Tarif (lei/persoana/luna)", 0, QApplication::UnicodeUTF8));
        labelType->setText(QApplication::translate("NodeViewDialog", "Tip nod", 0, QApplication::UnicodeUTF8));
        labelName->setText(QApplication::translate("NodeViewDialog", "Nume nod", 0, QApplication::UnicodeUTF8));
        labelTime->setText(QApplication::translate("NodeViewDialog", "Timp colectare (ore)", 0, QApplication::UnicodeUTF8));
        labelQuantity->setText(QApplication::translate("NodeViewDialog", "Cantitate (metri cubi)", 0, QApplication::UnicodeUTF8));
        labelVehicles->setText(QApplication::translate("NodeViewDialog", "Tipuri vehicule", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NodeViewDialog: public Ui_NodeViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEVIEWDIALOG_H
