/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_3;
    QProgressBar *ProgressbarIRLeft;
    QLabel *label_7;
    QLabel *label_6;
    QProgressBar *ProgressbarIRRight;
    QLabel *label_10;
    QLabel *label_9;
    QProgressBar *progressBarProxyLeft;
    QProgressBar *progressBarProxyRight;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QPushButton *buttonBrakeMode;
    QPushButton *pushButton;
    QGridLayout *gridLayout;
    QDial *CornerSlider;
    QLabel *TopSpeedSlider;
    QDial *accelerationSlider;
    QLabel *label;
    QLabel *label_3;
    QDial *topSpeedSlider;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QGridLayout *gridLayout_4;
    QProgressBar *progressBarCameraAngle;
    QLabel *label_8;
    QLabel *labelCameraAngle;
    QLabel *cameraLabel;
    QLabel *label_status_bar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(928, 569);
        MainWindow->setStyleSheet(QLatin1String("/*\n"
"	Copyright 2013 Emanuel Claesson\n"
"\n"
"	Licensed under the Apache License, Version 2.0 (the \"License\");\n"
"	you may not use this file except in compliance with the License.\n"
"	You may obtain a copy of the License at\n"
"\n"
"		http://www.apache.org/licenses/LICENSE-2.0\n"
"\n"
"	Unless required by applicable law or agreed to in writing, software\n"
"	distributed under the License is distributed on an \"AS IS\" BASIS,\n"
"	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n"
"	See the License for the specific language governing permissions and\n"
"	limitations under the License.\n"
"*/\n"
"\n"
"/*\n"
"	COLOR_DARK     = #191919\n"
"	COLOR_MEDIUM   = #353535\n"
"	COLOR_MEDLIGHT = #5A5A5A\n"
"	COLOR_LIGHT    = #DDDDDD\n"
"	COLOR_ACCENT   = #3D7848\n"
"*/\n"
"\n"
"* {\n"
"	background: #191919;\n"
"	color: #DDDDDD;\n"
"	border: 1px solid #5A5A5A;\n"
"}\n"
"\n"
"QWidget::item:selected {\n"
"	background: #3D7848;\n"
"}\n"
"\n"
"QCheckBox, QRadioButton {\n"
"	border: none;\n"
"}\n"
""
                        "\n"
"QRadioButton::indicator, QCheckBox::indicator {\n"
"	width: 13px;\n"
"	height: 13px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked, QCheckBox::indicator::unchecked {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: none;\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover, QCheckBox::indicator:unchecked:hover {\n"
"	border: 1px solid #DDDDDD;\n"
"}\n"
"\n"
"QRadioButton::indicator::checked, QCheckBox::indicator::checked {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: #5A5A5A;\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover, QCheckBox::indicator:checked:hover {\n"
"	border: 1px solid #DDDDDD;\n"
"	background: #DDDDDD;\n"
"}\n"
"\n"
"QGroupBox {\n"
"	margin-top: 6px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"	top: -7px;\n"
"	left: 7px;\n"
"}\n"
"\n"
"QScrollBar {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: #191919;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"	height: 15px;\n"
"	margin: 0px 0px 0px 32px;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"	width: 15px;\n"
"	margin: 32px 0px 0px 0px;\n"
""
                        "}\n"
"\n"
"QScrollBar::handle {\n"
"	background: #353535;\n"
"	border: 1px solid #5A5A5A;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"	border-width: 0px 1px 0px 1px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"	border-width: 1px 0px 1px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"	min-width: 20px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"	min-height: 20px;\n"
"}\n"
"\n"
"QScrollBar::add-line, QScrollBar::sub-line {\n"
"	background:#353535;\n"
"	border: 1px solid #5A5A5A;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::add-line {\n"
"	position: absolute;\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal {\n"
"	width: 15px;\n"
"	subcontrol-position: left;\n"
"	left: 15px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical {\n"
"	height: 15px;\n"
"	subcontrol-position: top;\n"
"	top: 15px;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"	width: 15px;\n"
"	subcontrol-position: top left;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical {\n"
"	height: 15px;\n"
"	subcontrol-position"
                        ": top;\n"
"}\n"
"\n"
"QScrollBar:left-arrow, QScrollBar::right-arrow, QScrollBar::up-arrow, QScrollBar::down-arrow {\n"
"	border: 1px solid #5A5A5A;\n"
"	width: 3px;\n"
"	height: 3px;\n"
"}\n"
"\n"
"QScrollBar::add-page, QScrollBar::sub-page {\n"
"	background: none;\n"
"}\n"
"\n"
"QAbstractButton:hover {\n"
"	background: #353535;\n"
"}\n"
"\n"
"QAbstractButton:pressed {\n"
"	background: #5A5A5A;\n"
"}\n"
"\n"
"QAbstractItemView {\n"
"	show-decoration-selected: 1;\n"
"	selection-background-color: #3D7848;\n"
"	selection-color: #DDDDDD;\n"
"	alternate-background-color: #353535;\n"
"}\n"
"\n"
"QHeaderView {\n"
"	border: 1px solid #5A5A5A;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"	background: #191919;\n"
"	border: 1px solid #5A5A5A;\n"
"	padding: 4px;\n"
"}\n"
"\n"
"QHeaderView::section:selected, QHeaderView::section::checked {\n"
"	background: #353535;\n"
"}\n"
"\n"
"QTableView {\n"
"	gridline-color: #5A5A5A;\n"
"}\n"
"\n"
"QTabBar {\n"
"	margin-left: 2px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"	border-radius: 0px;\n"
""
                        "	padding: 4px;\n"
"	margin: 4px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"	background: #353535;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: #353535;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: #353535;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"	width: 3px;\n"
"	height: 3px;\n"
"	border: 1px solid #5A5A5A;\n"
"}\n"
"\n"
"QAbstractSpinBox {\n"
"	padding-right: 15px;\n"
"}\n"
"\n"
"QAbstractSpinBox::up-button, QAbstractSpinBox::down-button {\n"
"	border: 1px solid #5A5A5A;\n"
"	background: #353535;\n"
"	subcontrol-origin: border;\n"
"}\n"
"\n"
"QAbstractSpinBox::up-arrow, QAbstractSpinBox::down-arrow {\n"
"	width: 3px;\n"
"	height: 3px;\n"
"	border: 1px solid #5A5A5A;\n"
"}\n"
"\n"
"QSlider {\n"
"	border: none;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	height: 5px;\n"
"	margin: 4px 0px 4px 0px;\n"
"}\n"
"\n"
"QSlider::groove:vertical {\n"
"	width: 5px;\n"
"	margin: 0px 4px 0px 4px;\n"
"}\n"
"\n"
"QSlider::handle {\n"
""
                        "	border: 1px solid #5A5A5A;\n"
"	background: #353535;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"	width: 15px;\n"
"	margin: -4px 0px -4px 0px;\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"	height: 15px;\n"
"	margin: 0px -4px 0px -4px;\n"
"}\n"
"\n"
"QSlider::add-page:vertical, QSlider::sub-page:horizontal {\n"
"	background: #3D7848;\n"
"}\n"
"\n"
"QSlider::sub-page:vertical, QSlider::add-page:horizontal {\n"
"	background: #353535;\n"
"}\n"
"\n"
"QLabel {\n"
"	border: none;\n"
"}\n"
"\n"
"QProgressBar {\n"
"	text-align: center;\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"	width: 1px;\n"
"	background-color: #3D7848;\n"
"}\n"
"\n"
"QMenu::separator {\n"
"	background: #353535;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        ProgressbarIRLeft = new QProgressBar(centralWidget);
        ProgressbarIRLeft->setObjectName(QStringLiteral("ProgressbarIRLeft"));
        ProgressbarIRLeft->setMaximum(1000);
        ProgressbarIRLeft->setValue(24);

        gridLayout_3->addWidget(ProgressbarIRLeft, 2, 1, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_3->addWidget(label_7, 2, 3, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 2, 0, 1, 1);

        ProgressbarIRRight = new QProgressBar(centralWidget);
        ProgressbarIRRight->setObjectName(QStringLiteral("ProgressbarIRRight"));
        ProgressbarIRRight->setMaximum(1000);
        ProgressbarIRRight->setValue(24);

        gridLayout_3->addWidget(ProgressbarIRRight, 2, 2, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_3->addWidget(label_9, 0, 3, 1, 1);

        progressBarProxyLeft = new QProgressBar(centralWidget);
        progressBarProxyLeft->setObjectName(QStringLiteral("progressBarProxyLeft"));
        progressBarProxyLeft->setMaximum(1000);
        progressBarProxyLeft->setValue(24);

        gridLayout_3->addWidget(progressBarProxyLeft, 0, 1, 1, 1);

        progressBarProxyRight = new QProgressBar(centralWidget);
        progressBarProxyRight->setObjectName(QStringLiteral("progressBarProxyRight"));
        progressBarProxyRight->setMaximum(1000);
        progressBarProxyRight->setValue(24);

        gridLayout_3->addWidget(progressBarProxyRight, 0, 2, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        buttonBrakeMode = new QPushButton(centralWidget);
        buttonBrakeMode->setObjectName(QStringLiteral("buttonBrakeMode"));

        verticalLayout_2->addWidget(buttonBrakeMode);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        CornerSlider = new QDial(centralWidget);
        CornerSlider->setObjectName(QStringLiteral("CornerSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CornerSlider->sizePolicy().hasHeightForWidth());
        CornerSlider->setSizePolicy(sizePolicy);
        CornerSlider->setMaximum(10000);
        CornerSlider->setSingleStep(300);
        CornerSlider->setPageStep(300);

        gridLayout->addWidget(CornerSlider, 0, 2, 1, 1);

        TopSpeedSlider = new QLabel(centralWidget);
        TopSpeedSlider->setObjectName(QStringLiteral("TopSpeedSlider"));

        gridLayout->addWidget(TopSpeedSlider, 2, 1, 1, 1);

        accelerationSlider = new QDial(centralWidget);
        accelerationSlider->setObjectName(QStringLiteral("accelerationSlider"));
        sizePolicy.setHeightForWidth(accelerationSlider->sizePolicy().hasHeightForWidth());
        accelerationSlider->setSizePolicy(sizePolicy);
        accelerationSlider->setMinimum(1000);
        accelerationSlider->setMaximum(50000);
        accelerationSlider->setSingleStep(100);
        accelerationSlider->setPageStep(100);

        gridLayout->addWidget(accelerationSlider, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        topSpeedSlider = new QDial(centralWidget);
        topSpeedSlider->setObjectName(QStringLiteral("topSpeedSlider"));
        sizePolicy.setHeightForWidth(topSpeedSlider->sizePolicy().hasHeightForWidth());
        topSpeedSlider->setSizePolicy(sizePolicy);
        topSpeedSlider->setMinimum(100);
        topSpeedSlider->setMaximum(150000);
        topSpeedSlider->setSingleStep(1500);
        topSpeedSlider->setPageStep(1500);

        gridLayout->addWidget(topSpeedSlider, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        progressBarCameraAngle = new QProgressBar(centralWidget);
        progressBarCameraAngle->setObjectName(QStringLiteral("progressBarCameraAngle"));
        progressBarCameraAngle->setMinimum(50);
        progressBarCameraAngle->setMaximum(170);
        progressBarCameraAngle->setValue(100);

        gridLayout_4->addWidget(progressBarCameraAngle, 0, 2, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 0, 0, 1, 1);

        labelCameraAngle = new QLabel(centralWidget);
        labelCameraAngle->setObjectName(QStringLiteral("labelCameraAngle"));

        gridLayout_4->addWidget(labelCameraAngle, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        cameraLabel = new QLabel(centralWidget);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(cameraLabel);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        label_status_bar = new QLabel(centralWidget);
        label_status_bar->setObjectName(QStringLiteral("label_status_bar"));

        verticalLayout_4->addWidget(label_status_bar);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(accelerationSlider, SIGNAL(valueChanged(int)), label_2, SLOT(setNum(int)));
        QObject::connect(topSpeedSlider, SIGNAL(valueChanged(int)), label_4, SLOT(setNum(int)));
        QObject::connect(CornerSlider, SIGNAL(valueChanged(int)), label_5, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "IR Sensor Right Background Light", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "IR Sensor Left Background Light", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "IR Proximity Left", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "IR Proximity Right", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Manual Wifi", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Manual IR", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Manual Balance Mode", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "Off", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "Automatic Object Search", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "Automatic Dyson Mode", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "Automatic Battle Mode", nullptr));
        comboBox->setItemText(7, QApplication::translate("MainWindow", "Automatic Headless Mode", nullptr));
        comboBox->setItemText(8, QApplication::translate("MainWindow", "Automatic Epileptic Mode", nullptr));
        comboBox->setItemText(9, QApplication::translate("MainWindow", "Automatic Balance Object Search", nullptr));
        comboBox->setItemText(10, QApplication::translate("MainWindow", "Automatic Balance Dyson Mode", nullptr));

        buttonBrakeMode->setText(QApplication::translate("MainWindow", "BrakeMode: Normal", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Speed preset: None", nullptr));
        TopSpeedSlider->setText(QApplication::translate("MainWindow", "topSpeed", nullptr));
        label->setText(QApplication::translate("MainWindow", "acceleration", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "corner sensitivity", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Camera Angle", nullptr));
        labelCameraAngle->setText(QApplication::translate("MainWindow", "0", nullptr));
        cameraLabel->setText(QApplication::translate("MainWindow", "imageLabel", nullptr));
        label_status_bar->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
