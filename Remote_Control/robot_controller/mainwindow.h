#ifndef MAINWINDOW_H
#define MAINWINDOW_H



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

private:
    Ui::MainWindow *ui;
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

#endif // MAINWINDOW_H
