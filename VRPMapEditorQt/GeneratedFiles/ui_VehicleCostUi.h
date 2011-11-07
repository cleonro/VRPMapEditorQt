/********************************************************************************
** Form generated from reading UI file 'VehicleCostUi.ui'
**
** Created: Tue Oct 18 01:28:12 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEHICLECOSTUI_H
#define UI_VEHICLECOSTUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VehicleCostDlg
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *comboVehType;
    QLabel *label_2;
    QLineEdit *lineGas;
    QLabel *label_3;
    QLineEdit *lineMaint;
    QLabel *label_4;
    QLineEdit *lineEquip;
    QLabel *label_5;
    QLineEdit *lineSal;
    QLabel *label_6;
    QPushButton *pushButton;
    QLineEdit *lineIdle;
    QLabel *label_7;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;

    void setupUi(QDialog *VehicleCostDlg)
    {
        if (VehicleCostDlg->objectName().isEmpty())
            VehicleCostDlg->setObjectName(QString::fromUtf8("VehicleCostDlg"));
        VehicleCostDlg->resize(220, 250);
        VehicleCostDlg->setMinimumSize(QSize(220, 250));
        VehicleCostDlg->setMaximumSize(QSize(220, 250));
        verticalLayout = new QVBoxLayout(VehicleCostDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(VehicleCostDlg);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        comboVehType = new QComboBox(VehicleCostDlg);
        comboVehType->setObjectName(QString::fromUtf8("comboVehType"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboVehType);

        label_2 = new QLabel(VehicleCostDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineGas = new QLineEdit(VehicleCostDlg);
        lineGas->setObjectName(QString::fromUtf8("lineGas"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineGas);

        label_3 = new QLabel(VehicleCostDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        lineMaint = new QLineEdit(VehicleCostDlg);
        lineMaint->setObjectName(QString::fromUtf8("lineMaint"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineMaint);

        label_4 = new QLabel(VehicleCostDlg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEquip = new QLineEdit(VehicleCostDlg);
        lineEquip->setObjectName(QString::fromUtf8("lineEquip"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEquip);

        label_5 = new QLabel(VehicleCostDlg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineSal = new QLineEdit(VehicleCostDlg);
        lineSal->setObjectName(QString::fromUtf8("lineSal"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineSal);

        label_6 = new QLabel(VehicleCostDlg);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        pushButton = new QPushButton(VehicleCostDlg);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(6, QFormLayout::FieldRole, pushButton);

        lineIdle = new QLineEdit(VehicleCostDlg);
        lineIdle->setObjectName(QString::fromUtf8("lineIdle"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineIdle);

        label_7 = new QLabel(VehicleCostDlg);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_7);


        verticalLayout->addLayout(formLayout);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(VehicleCostDlg);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(VehicleCostDlg);
        QObject::connect(okButton, SIGNAL(clicked()), VehicleCostDlg, SLOT(accept()));
        QObject::connect(pushButton, SIGNAL(clicked()), VehicleCostDlg, SLOT(OnButtonMem()));
        QObject::connect(comboVehType, SIGNAL(currentIndexChanged(int)), VehicleCostDlg, SLOT(OnIndexChanged(int)));

        QMetaObject::connectSlotsByName(VehicleCostDlg);
    } // setupUi

    void retranslateUi(QDialog *VehicleCostDlg)
    {
        VehicleCostDlg->setWindowTitle(QApplication::translate("VehicleCostDlg", "Cost Vehicul", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VehicleCostDlg", "Tip Vehicul", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VehicleCostDlg", "Cost combustibil ( /  km)", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("VehicleCostDlg", "Cost mentenanta ( / ora)", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("VehicleCostDlg", "Cost echipamente ( / ora)", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("VehicleCostDlg", "Cost salarii ( / ora)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("VehicleCostDlg", "Memoreaza cost", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("VehicleCostDlg", "Mem", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("VehicleCostDlg", "Cost stationare ( / ora)", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("VehicleCostDlg", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VehicleCostDlg: public Ui_VehicleCostDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEHICLECOSTUI_H
