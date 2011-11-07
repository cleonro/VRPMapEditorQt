/********************************************************************************
** Form generated from reading UI file 'ccentralwidget.ui'
**
** Created: Sun May 15 01:44:38 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCENTRALWIDGET_H
#define UI_CCENTRALWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "GLwidget.h"

QT_BEGIN_NAMESPACE

class Ui_CCentralWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    CGLWidget *glwidget;
    QWidget *toolbox;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *upButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *leftButton;
    QToolButton *rightButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *downButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSlider *verticalSlider;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QFormLayout *formLayout_2;
    QCheckBox *showGrid;
    QCheckBox *showConnections;
    QFormLayout *formLayout;
    QComboBox *mapType;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QSlider *horizontalSlider;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *spinBox;
    QLabel *label_2;

    void setupUi(QWidget *CCentralWidget)
    {
        if (CCentralWidget->objectName().isEmpty())
            CCentralWidget->setObjectName(QString::fromUtf8("CCentralWidget"));
        CCentralWidget->resize(560, 490);
        gridLayout = new QGridLayout(CCentralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        glwidget = new CGLWidget(CCentralWidget);
        glwidget->setObjectName(QString::fromUtf8("glwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(glwidget->sizePolicy().hasHeightForWidth());
        glwidget->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(glwidget);

        toolbox = new QWidget(CCentralWidget);
        toolbox->setObjectName(QString::fromUtf8("toolbox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolbox->sizePolicy().hasHeightForWidth());
        toolbox->setSizePolicy(sizePolicy1);
        toolbox->setMinimumSize(QSize(240, 0));
        toolbox->setMaximumSize(QSize(240, 16777215));
        groupBox = new QGroupBox(toolbox);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 231, 111));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 151, 91));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        upButton = new QToolButton(layoutWidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        upButton->setIcon(icon);
        upButton->setIconSize(QSize(12, 24));

        horizontalLayout->addWidget(upButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        leftButton = new QToolButton(layoutWidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        leftButton->setIcon(icon1);
        leftButton->setIconSize(QSize(24, 12));

        horizontalLayout_3->addWidget(leftButton);

        rightButton = new QToolButton(layoutWidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        rightButton->setIcon(icon2);
        rightButton->setIconSize(QSize(24, 12));

        horizontalLayout_3->addWidget(rightButton);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        downButton = new QToolButton(layoutWidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/VRPMapEditorQt/Resources/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        downButton->setIcon(icon3);
        downButton->setIconSize(QSize(12, 24));

        horizontalLayout_2->addWidget(downButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        verticalSlider = new QSlider(layoutWidget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMinimum(5);
        verticalSlider->setMaximum(18);
        verticalSlider->setValue(13);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setInvertedAppearance(true);
        verticalSlider->setTickPosition(QSlider::TicksBothSides);
        verticalSlider->setTickInterval(1);

        horizontalLayout_4->addWidget(verticalSlider);

        groupBox_2 = new QGroupBox(toolbox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 110, 231, 91));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 132, 76));
        formLayout_2 = new QFormLayout(layoutWidget1);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        showGrid = new QCheckBox(layoutWidget1);
        showGrid->setObjectName(QString::fromUtf8("showGrid"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, showGrid);

        showConnections = new QCheckBox(layoutWidget1);
        showConnections->setObjectName(QString::fromUtf8("showConnections"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, showConnections);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        mapType = new QComboBox(layoutWidget1);
        mapType->setObjectName(QString::fromUtf8("mapType"));

        formLayout->setWidget(0, QFormLayout::LabelRole, mapType);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label);


        formLayout_2->setLayout(3, QFormLayout::LabelRole, formLayout);

        verticalLayoutWidget = new QWidget(groupBox_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(149, 10, 85, 71));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSlider = new QSlider(verticalLayoutWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMaximumSize(QSize(75, 15));
        horizontalSlider->setMinimum(0);
        horizontalSlider->setMaximum(10);
        horizontalSlider->setPageStep(1);
        horizontalSlider->setValue(7);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(false);
        horizontalSlider->setInvertedControls(false);
        horizontalSlider->setTickPosition(QSlider::TicksAbove);

        verticalLayout_2->addWidget(horizontalSlider);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        spinBox = new QSpinBox(verticalLayoutWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximumSize(QSize(25, 16777215));
        spinBox->setMinimum(1);
        spinBox->setMaximum(5);

        horizontalLayout_6->addWidget(spinBox);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_5->addWidget(toolbox);

        horizontalLayout_5->setStretch(0, 10);

        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);


        retranslateUi(CCentralWidget);
        QObject::connect(upButton, SIGNAL(clicked()), CCentralWidget, SLOT(UpClicked()));
        QObject::connect(leftButton, SIGNAL(clicked()), CCentralWidget, SLOT(LeftClicked()));
        QObject::connect(downButton, SIGNAL(clicked()), CCentralWidget, SLOT(DownClicked()));
        QObject::connect(rightButton, SIGNAL(clicked()), CCentralWidget, SLOT(RightClicked()));
        QObject::connect(verticalSlider, SIGNAL(sliderReleased()), CCentralWidget, SLOT(SliderReleased()));
        QObject::connect(showGrid, SIGNAL(clicked()), CCentralWidget, SLOT(ShowGridClicked()));
        QObject::connect(mapType, SIGNAL(currentIndexChanged(QString)), CCentralWidget, SLOT(ComboBoxIndexChanged(QString)));
        QObject::connect(showConnections, SIGNAL(clicked()), CCentralWidget, SLOT(ShowConnectionsClicked()));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), CCentralWidget, SLOT(SliderValueChanged(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), CCentralWidget, SLOT(LineWidthChanged(int)));

        QMetaObject::connectSlotsByName(CCentralWidget);
    } // setupUi

    void retranslateUi(QWidget *CCentralWidget)
    {
        CCentralWidget->setWindowTitle(QApplication::translate("CCentralWidget", "CCentralWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        upButton->setText(QApplication::translate("CCentralWidget", "...", 0, QApplication::UnicodeUTF8));
        leftButton->setText(QApplication::translate("CCentralWidget", "...", 0, QApplication::UnicodeUTF8));
        rightButton->setText(QApplication::translate("CCentralWidget", "...", 0, QApplication::UnicodeUTF8));
        downButton->setText(QApplication::translate("CCentralWidget", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        showGrid->setText(QApplication::translate("CCentralWidget", "Show Grid", 0, QApplication::UnicodeUTF8));
        showConnections->setText(QApplication::translate("CCentralWidget", "Show Connections", 0, QApplication::UnicodeUTF8));
        mapType->clear();
        mapType->insertItems(0, QStringList()
         << QApplication::translate("CCentralWidget", "roadmap", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CCentralWidget", "satellite", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CCentralWidget", "terrain", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CCentralWidget", "hybrid", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("CCentralWidget", "Map type", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CCentralWidget", "Transparency", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CCentralWidget", "Line Width", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CCentralWidget: public Ui_CCentralWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCENTRALWIDGET_H
