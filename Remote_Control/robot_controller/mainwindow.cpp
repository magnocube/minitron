#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robotConnection = new UDP_Connection("192.168.137.148");

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), robotConnection, SLOT(send()));
    timer->start(100);

    scene = new QGraphicsScene(this);
    setupUI();
    ui->graphicsView->setScene(scene);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
 //  QMainWindow::resizeEvent(event);




}
void MainWindow::paintEvent(QPaintEvent *e)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

}

void MainWindow::setupUI()
{
    QGraphicsPixmapItem *robotImage;
    robotImage = new QGraphicsPixmapItem(QPixmap(":/backgroundImages/images/transpartentImagev1.png").scaled(1000,1000));
    robotImage->setPos(0,0);
    robotImage->setZValue(0);
    scene->addItem(robotImage);



    speedMotor1 = new GraphicSpeedSensor();
    speedMotor2 = new GraphicSpeedSensor();
    speedMotor1->setPos(-150,700);
    speedMotor2->setPos(1000,700);
    speedMotor1->setAcceleration(100);
    speedMotor2->setAcceleration(100);
    speedMotor1->setSpeed(80);
    speedMotor2->setSpeed(40);

    TOFSensor = new graphicsTOFSensor();
    TOFSensor->setPos(300,-180);
    TOFSensor->setDistance(20); //in mm

    proxySensorLeft = new graphicProxySensor(0);
    proxySensorLeft->setPos(0,180);
    proxySensorLeft->setProxy(2);
    proxySensorRight = new graphicProxySensor(1);
    proxySensorRight->setPos(800,180);
    proxySensorRight->setProxy(5);

    scene->addItem(speedMotor1);
    scene->addItem(speedMotor2);
    scene->addItem(TOFSensor);
    scene->addItem(proxySensorLeft);
    scene->addItem(proxySensorRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug() << "mode changed " << arg1;
}
