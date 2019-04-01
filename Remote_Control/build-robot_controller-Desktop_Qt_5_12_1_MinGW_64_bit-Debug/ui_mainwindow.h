/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QProgressBar *progressBarIRProxyLeft;
    QProgressBar *progressBarIRProxyRight;
    QLabel *label_10;
    QLabel *label_9;
    QProgressBar *ProgressbarIRRight;
    QLabel *label_6;
    QFrame *line_3;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *buttonBrakeMode;
    QFrame *line_5;
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
    QFrame *line_6;
    QGridLayout *gridLayout_4;
    QLabel *label_8;
    QSlider *horizontalServoSlider;
    QProgressBar *progressBarCameraAngle;
    QLabel *label_11;
    QSlider *Slider_accelerationAngle;
    QLabel *labelAccelerationAngle;
    QLabel *label_21;
    QLCDNumber *lcd_AccelerationAngle;
    QLCDNumber *lcdServoAngle;
    QFrame *line;
    QGridLayout *gridLayout_2;
    QSlider *PSlider;
    QSlider *ISlider;
    QLabel *label_13;
    QLCDNumber *lcdP;
    QLCDNumber *lcdD;
    QLabel *label_14;
    QLCDNumber *lcdI;
    QLabel *label_12;
    QSlider *DSlider;
    QFrame *line_2;
    QGridLayout *gridLayout_6;
    QSlider *Slider_UdateFerquency;
    QLabel *label_18;
    QLabel *label_16;
    QSlider *Slider_ComplemetaryFilter;
    QSlider *Slider_PIDMaxSpeed;
    QSlider *Slider_DefaultSetPoint;
    QLabel *label_17;
    QLabel *label_15;
    QLCDNumber *lcdComFilter;
    QLCDNumber *lcdUpdateFilter;
    QLCDNumber *lcdWorkingAngle;
    QLCDNumber *lcdPIDMAXSPEED;
    QLCDNumber *lcdDefaultSetPoint;
    QSlider *Slider_WorkingAngle;
    QLabel *label_19;
    QLCDNumber *lcdStandStill;
    QSlider *Slider_StandStill;
    QLabel *label_20;
    QLabel *cameraLabel;
    QLabel *label_status_bar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(2106, 1006);
        MainWindow->setStyleSheet(QString::fromUtf8("/*\n"
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
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout_2->addWidget(graphicsView);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        ProgressbarIRLeft = new QProgressBar(centralWidget);
        ProgressbarIRLeft->setObjectName(QString::fromUtf8("ProgressbarIRLeft"));
        ProgressbarIRLeft->setMaximum(1000);
        ProgressbarIRLeft->setValue(24);

        gridLayout_3->addWidget(ProgressbarIRLeft, 1, 2, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 1, 5, 1, 1);

        progressBarIRProxyLeft = new QProgressBar(centralWidget);
        progressBarIRProxyLeft->setObjectName(QString::fromUtf8("progressBarIRProxyLeft"));
        progressBarIRProxyLeft->setMaximum(1000);
        progressBarIRProxyLeft->setValue(24);

        gridLayout_3->addWidget(progressBarIRProxyLeft, 0, 2, 1, 1);

        progressBarIRProxyRight = new QProgressBar(centralWidget);
        progressBarIRProxyRight->setObjectName(QString::fromUtf8("progressBarIRProxyRight"));
        progressBarIRProxyRight->setMaximum(1000);
        progressBarIRProxyRight->setValue(24);

        gridLayout_3->addWidget(progressBarIRProxyRight, 0, 4, 1, 1);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 5, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 0, 0, 1, 1);

        ProgressbarIRRight = new QProgressBar(centralWidget);
        ProgressbarIRRight->setObjectName(QString::fromUtf8("ProgressbarIRRight"));
        ProgressbarIRRight->setMaximum(1000);
        ProgressbarIRRight->setValue(24);

        gridLayout_3->addWidget(ProgressbarIRRight, 1, 4, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 0, 3, 1, 1);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_4, 1, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
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
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_2->addWidget(comboBox);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        buttonBrakeMode = new QPushButton(centralWidget);
        buttonBrakeMode->setObjectName(QString::fromUtf8("buttonBrakeMode"));

        verticalLayout_2->addWidget(buttonBrakeMode);


        horizontalLayout->addLayout(verticalLayout_2);

        line_5 = new QFrame(centralWidget);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        CornerSlider = new QDial(centralWidget);
        CornerSlider->setObjectName(QString::fromUtf8("CornerSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CornerSlider->sizePolicy().hasHeightForWidth());
        CornerSlider->setSizePolicy(sizePolicy);
        CornerSlider->setMaximum(30000);
        CornerSlider->setSingleStep(300);
        CornerSlider->setPageStep(300);

        gridLayout->addWidget(CornerSlider, 0, 2, 1, 1);

        TopSpeedSlider = new QLabel(centralWidget);
        TopSpeedSlider->setObjectName(QString::fromUtf8("TopSpeedSlider"));

        gridLayout->addWidget(TopSpeedSlider, 2, 1, 1, 1);

        accelerationSlider = new QDial(centralWidget);
        accelerationSlider->setObjectName(QString::fromUtf8("accelerationSlider"));
        sizePolicy.setHeightForWidth(accelerationSlider->sizePolicy().hasHeightForWidth());
        accelerationSlider->setSizePolicy(sizePolicy);
        accelerationSlider->setMinimum(1000);
        accelerationSlider->setMaximum(10000000);
        accelerationSlider->setSingleStep(100);
        accelerationSlider->setPageStep(100);

        gridLayout->addWidget(accelerationSlider, 0, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        topSpeedSlider = new QDial(centralWidget);
        topSpeedSlider->setObjectName(QString::fromUtf8("topSpeedSlider"));
        sizePolicy.setHeightForWidth(topSpeedSlider->sizePolicy().hasHeightForWidth());
        topSpeedSlider->setSizePolicy(sizePolicy);
        topSpeedSlider->setMinimum(100);
        topSpeedSlider->setMaximum(150000);
        topSpeedSlider->setSingleStep(1500);
        topSpeedSlider->setPageStep(1500);

        gridLayout->addWidget(topSpeedSlider, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_6);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 2, 0, 1, 1);

        horizontalServoSlider = new QSlider(centralWidget);
        horizontalServoSlider->setObjectName(QString::fromUtf8("horizontalServoSlider"));
        horizontalServoSlider->setMinimum(50);
        horizontalServoSlider->setMaximum(170);
        horizontalServoSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(horizontalServoSlider, 1, 2, 1, 1);

        progressBarCameraAngle = new QProgressBar(centralWidget);
        progressBarCameraAngle->setObjectName(QString::fromUtf8("progressBarCameraAngle"));
        progressBarCameraAngle->setMinimum(50);
        progressBarCameraAngle->setMaximum(170);
        progressBarCameraAngle->setValue(100);

        gridLayout_4->addWidget(progressBarCameraAngle, 2, 2, 1, 1);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        Slider_accelerationAngle = new QSlider(centralWidget);
        Slider_accelerationAngle->setObjectName(QString::fromUtf8("Slider_accelerationAngle"));
        Slider_accelerationAngle->setMaximum(95);
        Slider_accelerationAngle->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(Slider_accelerationAngle, 0, 2, 1, 1);

        labelAccelerationAngle = new QLabel(centralWidget);
        labelAccelerationAngle->setObjectName(QString::fromUtf8("labelAccelerationAngle"));

        gridLayout_4->addWidget(labelAccelerationAngle, 0, 1, 1, 1);

        label_21 = new QLabel(centralWidget);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout_4->addWidget(label_21, 0, 0, 1, 1);

        lcd_AccelerationAngle = new QLCDNumber(centralWidget);
        lcd_AccelerationAngle->setObjectName(QString::fromUtf8("lcd_AccelerationAngle"));

        gridLayout_4->addWidget(lcd_AccelerationAngle, 0, 3, 1, 1);

        lcdServoAngle = new QLCDNumber(centralWidget);
        lcdServoAngle->setObjectName(QString::fromUtf8("lcdServoAngle"));

        gridLayout_4->addWidget(lcdServoAngle, 2, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        PSlider = new QSlider(centralWidget);
        PSlider->setObjectName(QString::fromUtf8("PSlider"));
        PSlider->setValue(30);
        PSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(PSlider, 1, 1, 1, 1);

        ISlider = new QSlider(centralWidget);
        ISlider->setObjectName(QString::fromUtf8("ISlider"));
        ISlider->setValue(4);
        ISlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(ISlider, 2, 1, 1, 1);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 2, 0, 1, 1);

        lcdP = new QLCDNumber(centralWidget);
        lcdP->setObjectName(QString::fromUtf8("lcdP"));

        gridLayout_2->addWidget(lcdP, 1, 2, 1, 1);

        lcdD = new QLCDNumber(centralWidget);
        lcdD->setObjectName(QString::fromUtf8("lcdD"));

        gridLayout_2->addWidget(lcdD, 3, 2, 1, 1);

        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 3, 0, 1, 1);

        lcdI = new QLCDNumber(centralWidget);
        lcdI->setObjectName(QString::fromUtf8("lcdI"));

        gridLayout_2->addWidget(lcdI, 2, 2, 1, 1);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 1, 0, 1, 1);

        DSlider = new QSlider(centralWidget);
        DSlider->setObjectName(QString::fromUtf8("DSlider"));
        DSlider->setValue(50);
        DSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(DSlider, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        Slider_UdateFerquency = new QSlider(centralWidget);
        Slider_UdateFerquency->setObjectName(QString::fromUtf8("Slider_UdateFerquency"));
        Slider_UdateFerquency->setMinimum(1000);
        Slider_UdateFerquency->setMaximum(10000);
        Slider_UdateFerquency->setValue(9000);
        Slider_UdateFerquency->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_UdateFerquency, 7, 1, 1, 1);

        label_18 = new QLabel(centralWidget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        gridLayout_6->addWidget(label_18, 1, 0, 1, 1);

        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_6->addWidget(label_16, 7, 0, 1, 1);

        Slider_ComplemetaryFilter = new QSlider(centralWidget);
        Slider_ComplemetaryFilter->setObjectName(QString::fromUtf8("Slider_ComplemetaryFilter"));
        Slider_ComplemetaryFilter->setMinimum(900);
        Slider_ComplemetaryFilter->setMaximum(999);
        Slider_ComplemetaryFilter->setValue(975);
        Slider_ComplemetaryFilter->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_ComplemetaryFilter, 2, 1, 1, 1);

        Slider_PIDMaxSpeed = new QSlider(centralWidget);
        Slider_PIDMaxSpeed->setObjectName(QString::fromUtf8("Slider_PIDMaxSpeed"));
        Slider_PIDMaxSpeed->setMinimum(100);
        Slider_PIDMaxSpeed->setMaximum(1000);
        Slider_PIDMaxSpeed->setValue(400);
        Slider_PIDMaxSpeed->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_PIDMaxSpeed, 1, 1, 1, 1);

        Slider_DefaultSetPoint = new QSlider(centralWidget);
        Slider_DefaultSetPoint->setObjectName(QString::fromUtf8("Slider_DefaultSetPoint"));
        Slider_DefaultSetPoint->setMinimum(-20);
        Slider_DefaultSetPoint->setMaximum(20);
        Slider_DefaultSetPoint->setValue(10);
        Slider_DefaultSetPoint->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_DefaultSetPoint, 8, 1, 1, 1);

        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_6->addWidget(label_17, 2, 0, 1, 1);

        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_6->addWidget(label_15, 8, 0, 1, 1);

        lcdComFilter = new QLCDNumber(centralWidget);
        lcdComFilter->setObjectName(QString::fromUtf8("lcdComFilter"));

        gridLayout_6->addWidget(lcdComFilter, 2, 2, 1, 1);

        lcdUpdateFilter = new QLCDNumber(centralWidget);
        lcdUpdateFilter->setObjectName(QString::fromUtf8("lcdUpdateFilter"));

        gridLayout_6->addWidget(lcdUpdateFilter, 7, 2, 1, 1);

        lcdWorkingAngle = new QLCDNumber(centralWidget);
        lcdWorkingAngle->setObjectName(QString::fromUtf8("lcdWorkingAngle"));

        gridLayout_6->addWidget(lcdWorkingAngle, 0, 2, 1, 1);

        lcdPIDMAXSPEED = new QLCDNumber(centralWidget);
        lcdPIDMAXSPEED->setObjectName(QString::fromUtf8("lcdPIDMAXSPEED"));

        gridLayout_6->addWidget(lcdPIDMAXSPEED, 1, 2, 1, 1);

        lcdDefaultSetPoint = new QLCDNumber(centralWidget);
        lcdDefaultSetPoint->setObjectName(QString::fromUtf8("lcdDefaultSetPoint"));

        gridLayout_6->addWidget(lcdDefaultSetPoint, 8, 2, 1, 1);

        Slider_WorkingAngle = new QSlider(centralWidget);
        Slider_WorkingAngle->setObjectName(QString::fromUtf8("Slider_WorkingAngle"));
        Slider_WorkingAngle->setMinimum(20);
        Slider_WorkingAngle->setMaximum(100);
        Slider_WorkingAngle->setValue(30);
        Slider_WorkingAngle->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_WorkingAngle, 0, 1, 1, 1);

        label_19 = new QLabel(centralWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_6->addWidget(label_19, 0, 0, 1, 1);

        lcdStandStill = new QLCDNumber(centralWidget);
        lcdStandStill->setObjectName(QString::fromUtf8("lcdStandStill"));

        gridLayout_6->addWidget(lcdStandStill, 9, 2, 1, 1);

        Slider_StandStill = new QSlider(centralWidget);
        Slider_StandStill->setObjectName(QString::fromUtf8("Slider_StandStill"));
        Slider_StandStill->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(Slider_StandStill, 9, 1, 1, 1);

        label_20 = new QLabel(centralWidget);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_6->addWidget(label_20, 9, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_6);

        cameraLabel = new QLabel(centralWidget);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(cameraLabel);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        label_status_bar = new QLabel(centralWidget);
        label_status_bar->setObjectName(QString::fromUtf8("label_status_bar"));

        verticalLayout_4->addWidget(label_status_bar);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(accelerationSlider, SIGNAL(valueChanged(int)), label_2, SLOT(setNum(int)));
        QObject::connect(topSpeedSlider, SIGNAL(valueChanged(int)), label_4, SLOT(setNum(int)));
        QObject::connect(CornerSlider, SIGNAL(valueChanged(int)), label_5, SLOT(setNum(int)));
        QObject::connect(PSlider, SIGNAL(valueChanged(int)), lcdP, SLOT(display(int)));
        QObject::connect(ISlider, SIGNAL(valueChanged(int)), lcdI, SLOT(display(int)));
        QObject::connect(DSlider, SIGNAL(valueChanged(int)), lcdD, SLOT(display(int)));
        QObject::connect(Slider_WorkingAngle, SIGNAL(valueChanged(int)), lcdWorkingAngle, SLOT(display(int)));
        QObject::connect(Slider_PIDMaxSpeed, SIGNAL(valueChanged(int)), lcdPIDMAXSPEED, SLOT(display(int)));
        QObject::connect(Slider_ComplemetaryFilter, SIGNAL(valueChanged(int)), lcdComFilter, SLOT(display(int)));
        QObject::connect(Slider_UdateFerquency, SIGNAL(valueChanged(int)), lcdUpdateFilter, SLOT(display(int)));
        QObject::connect(Slider_DefaultSetPoint, SIGNAL(valueChanged(int)), lcdDefaultSetPoint, SLOT(display(int)));
        QObject::connect(Slider_StandStill, SIGNAL(valueChanged(int)), lcdStandStill, SLOT(display(int)));
        QObject::connect(Slider_accelerationAngle, SIGNAL(valueChanged(int)), lcd_AccelerationAngle, SLOT(display(int)));
        QObject::connect(progressBarCameraAngle, SIGNAL(valueChanged(int)), lcdServoAngle, SLOT(display(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "IR Sensor Right Background Light", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "IR Distance Right", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "IR Distance Left", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "IR Sensor Left Background Light", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Off", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Manual Wifi", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Manual IR", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "Manual Balance Mode", nullptr));
        comboBox->setItemText(4, QApplication::translate("MainWindow", "Automatic Object Search", nullptr));
        comboBox->setItemText(5, QApplication::translate("MainWindow", "Automatic Dyson Mode", nullptr));
        comboBox->setItemText(6, QApplication::translate("MainWindow", "Automatic Battle Mode", nullptr));
        comboBox->setItemText(7, QApplication::translate("MainWindow", "Automatic Headless Mode", nullptr));
        comboBox->setItemText(8, QApplication::translate("MainWindow", "Automatic Epileptic Mode", nullptr));
        comboBox->setItemText(9, QApplication::translate("MainWindow", "Automatic Balance Object Search", nullptr));
        comboBox->setItemText(10, QApplication::translate("MainWindow", "Automatic Balance Dyson Mode", nullptr));

        pushButton->setText(QApplication::translate("MainWindow", "Speed preset: None", nullptr));
        buttonBrakeMode->setText(QApplication::translate("MainWindow", "BrakeMode: Normal", nullptr));
        TopSpeedSlider->setText(QApplication::translate("MainWindow", "topSpeed", nullptr));
        label->setText(QApplication::translate("MainWindow", "acceleration", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "corner sensitivity", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "0", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Camera Angle", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Servo Slider", nullptr));
        labelAccelerationAngle->setText(QString());
        label_21->setText(QApplication::translate("MainWindow", "Acceleration Angle", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "I-Value", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "D-Value", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "P-Value", nullptr));
        label_18->setText(QApplication::translate("MainWindow", "PID Max Speed", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "Update Frequency", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "Complementary Filter ", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "Default Set Point", nullptr));
        label_19->setText(QApplication::translate("MainWindow", "Working Angle", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "StandStillPoint", nullptr));
        cameraLabel->setText(QApplication::translate("MainWindow", "imageLabel", nullptr));
        label_status_bar->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
