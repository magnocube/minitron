#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <udp_connection.h>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>


#include <graphicspeedsensor.h>
#include <graphicstofsensor.h>
#include <graphicproxysensor.h>
#include <graphicBattery.h>

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

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void udpHasAUpdate();
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



};

#endif // MAINWINDOW_H
