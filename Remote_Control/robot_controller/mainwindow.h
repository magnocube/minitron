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



};

#endif // MAINWINDOW_H
