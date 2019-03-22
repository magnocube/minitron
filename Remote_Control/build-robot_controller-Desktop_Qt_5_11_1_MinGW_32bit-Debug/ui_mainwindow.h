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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1291, 644);
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


        horizontalLayout->addLayout(verticalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        CornerSlider = new QSlider(centralWidget);
        CornerSlider->setObjectName(QStringLiteral("CornerSlider"));
        CornerSlider->setMinimum(10);
        CornerSlider->setMaximum(10000);
        CornerSlider->setValue(2000);
        CornerSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(CornerSlider, 0, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        topSpeedSlider = new QSlider(centralWidget);
        topSpeedSlider->setObjectName(QStringLiteral("topSpeedSlider"));
        topSpeedSlider->setMinimum(100);
        topSpeedSlider->setMaximum(60000);
        topSpeedSlider->setValue(3000);
        topSpeedSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(topSpeedSlider, 0, 1, 1, 1);

        TopSpeedSlider = new QLabel(centralWidget);
        TopSpeedSlider->setObjectName(QStringLiteral("TopSpeedSlider"));

        gridLayout->addWidget(TopSpeedSlider, 1, 1, 1, 1);

        accelerationSlider = new QSlider(centralWidget);
        accelerationSlider->setObjectName(QStringLiteral("accelerationSlider"));
        accelerationSlider->setMinimum(1000);
        accelerationSlider->setMaximum(60000);
        accelerationSlider->setValue(10000);
        accelerationSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(accelerationSlider, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout);

        cameraLabel = new QLabel(centralWidget);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(cameraLabel);


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_2);

        label_status_bar = new QLabel(centralWidget);
        label_status_bar->setObjectName(QStringLiteral("label_status_bar"));

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
