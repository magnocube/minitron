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

    connect(robotConnection,SIGNAL(udpUpdate()),this,SLOT(udpHasAUpdate()));

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
    speedMotor1->setPos(1000,700);
    speedMotor2->setPos(-150,700);
    speedMotor1->setAcceleration(0);
    speedMotor2->setAcceleration(0);
    speedMotor1->setSpeed(1);
    speedMotor2->setSpeed(1);

    TOFSensor = new graphicsTOFSensor();
    TOFSensor->setPos(300,-180);
    TOFSensor->setDistance(999); //in mm

    proxySensorLeft = new graphicProxySensor(0);
    proxySensorLeft->setPos(0,180);
    proxySensorLeft->setProxy(3);
    proxySensorRight = new graphicProxySensor(1);
    proxySensorRight->setPos(800,180);
    proxySensorRight->setProxy(3);

    battery = new GraphicBattery();
    battery->setPos(0,0);
    battery->setVoltage(0);

    scene->addItem(battery);
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


// will update the gui with the updated variables
void MainWindow::udpHasAUpdate()
{
    qDebug()<< "updating main" << endl;
    speedMotor1->setSpeed(robotConnection->sharedVariables.outputs.steppers.motor1TargetSpeed/100);
    speedMotor2->setSpeed(robotConnection->sharedVariables.outputs.steppers.motor2TargetSpeed/100);
    speedMotor1->setAcceleration(robotConnection->sharedVariables.outputs.steppers.acceleration_motor1);
    speedMotor2->setAcceleration(robotConnection->sharedVariables.outputs.steppers.acceleration_motor2);
    TOFSensor->setDistance(robotConnection->sharedVariables.outputs.TOFSensorDistanceMM);
    battery->setVoltage(robotConnection->sharedVariables.outputs.voltage);
    proxySensorLeft->setProxy(robotConnection->sharedVariables.outputs.proximityLeft/100);
    proxySensorRight->setProxy(robotConnection->sharedVariables.outputs.proximityRight/100);
    qDebug()<<robotConnection->sharedVariables.outputs.lightLeft << endl;

    update();
}
