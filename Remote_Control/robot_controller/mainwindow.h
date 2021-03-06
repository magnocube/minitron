#pragma once


#include <QMainWindow>
#include <udp_connection.h>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>


#include <graphicspeedsensor.h>
#include <graphicstofsensor.h>
#include <graphicproxysensor.h>
#include <graphicBattery.h>
#include "graphiccamera.h"
#include "graphiccompass.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void udpHasAUpdate();
    void SendUdpToRobot();
    void on_buttonBrakeMode_clicked();

    void on_pushButton_clicked();

    void on_ClearReceivedButton_clicked();

    void on_SendIrButton_clicked();

private:

    UDP_Connection *robotConnection;
    QGraphicsScene * scene;
    void setupUI();

    GraphicSpeedSensor * speedMotor1;
    GraphicSpeedSensor * speedMotor2;
    graphicsTOFSensor * TOFSensor;
    graphicProxySensor * proxySensorLeft;
    graphicProxySensor * proxySensorRight;
    GraphicBattery * battery;
    graphicCamera * camera;
    graphicCompass * compass;

    uint8_t IRFlowDataInput = 0;// input to robot
    uint8_t IRFlowDataOutput = 0;// output to Gui

    void setupPlots();
    void updatePlots();

    struct ConntrolData{
        int32_t Motor1OldSpeed = 0;
        int32_t Motor2OldSpeed = 0;
        bool WPressed = false;
        bool SPressed = false;
        bool APressed = false;
        bool DPressed = false;
        uint32_t timeSinceLastUpdate; //probably not needed
    } controlData;



};


