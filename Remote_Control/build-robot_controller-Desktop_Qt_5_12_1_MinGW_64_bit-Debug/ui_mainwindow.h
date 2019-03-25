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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
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
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox;
    QPushButton *buttonBrakeMode;
    QGridLayout *gridLayout;
    QSlider *CornerSlider;
    QLabel *label;
    QLabel *label_3;
    QSlider *topSpeedSlider;
    QLabel *TopSpeedSlider;
    QSlider *accelerationSlider;
    QLabel *cameraLabel;
    QLabel *label_status_bar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1291, 644);
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

        buttonBrakeMode = new QPushButton(centralWidget);
        buttonBrakeMode->setObjectName(QString::fromUtf8("buttonBrakeMode"));

        verticalLayout_2->addWidget(buttonBrakeMode);


        horizontalLayout->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        CornerSlider = new QSlider(centralWidget);
        CornerSlider->setObjectName(QString::fromUtf8("CornerSlider"));
        CornerSlider->setMinimum(10);
        CornerSlider->setMaximum(30000);
        CornerSlider->setValue(2000);
        CornerSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(CornerSlider, 0, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        topSpeedSlider = new QSlider(centralWidget);
        topSpeedSlider->setObjectName(QString::fromUtf8("topSpeedSlider"));
        topSpeedSlider->setMinimum(100);
        topSpeedSlider->setMaximum(150000);
        topSpeedSlider->setValue(3000);
        topSpeedSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(topSpeedSlider, 0, 1, 1, 1);

        TopSpeedSlider = new QLabel(centralWidget);
        TopSpeedSlider->setObjectName(QString::fromUtf8("TopSpeedSlider"));

        gridLayout->addWidget(TopSpeedSlider, 1, 1, 1, 1);

        accelerationSlider = new QSlider(centralWidget);
        accelerationSlider->setObjectName(QString::fromUtf8("accelerationSlider"));
        accelerationSlider->setMinimum(1000);
        accelerationSlider->setMaximum(60000);
        accelerationSlider->setValue(10000);
        accelerationSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(accelerationSlider, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        cameraLabel = new QLabel(centralWidget);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(cameraLabel);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        label_status_bar = new QLabel(centralWidget);
        label_status_bar->setObjectName(QString::fromUtf8("label_status_bar"));

        verticalLayout_4->addWidget(label_status_bar);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
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
        label->setText(QApplication::translate("MainWindow", "acceleration", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "corner sensitivity", nullptr));
        TopSpeedSlider->setText(QApplication::translate("MainWindow", "topSpeed", nullptr));
        cameraLabel->setText(QApplication::translate("MainWindow", "imageLabel", nullptr));
        label_status_bar->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
