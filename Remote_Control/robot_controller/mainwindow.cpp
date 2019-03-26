#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    robotConnection = new UDP_Connection("192.168.137.68");



    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(SendUdpToRobot()));
    timer->start(25);

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
    speedMotor1->setPos(-150,700);
    speedMotor2->setPos(1000,700);
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
    if(arg1 == "Manual IR"){
        robotConnection->sharedVariables.inputs.mode = controlModes::MANUAL_IR;
    } else if(arg1 == "Manual Wifi"){
        robotConnection->sharedVariables.inputs.mode = controlModes::MANUAL_WIFI;
    } else if(arg1 == "Manual Balance Mode"){
        robotConnection->sharedVariables.inputs.mode = controlModes::MANUAL_WIFI_BALANCE;
    } else if(arg1 == "Off"){
        robotConnection->sharedVariables.inputs.mode = controlModes::OFF;
    } else if(arg1 == "Automatic Object Search"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_OBJECT_SEARCH;
    } else if(arg1 == "Automatic Dyson Mode"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_DYSON_MODE;
    } else if(arg1 == "Automatic Battle Mode"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_BATTLE_MODE;
    } else if(arg1 == "Automatic Headless Mode"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_HEADLESS_MODE;
    } else if(arg1 == "Automatic Epileptic Mode"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_EPILEPTIC_MODE;
    } else if(arg1 == "Automatic Balance Object Search"){
        robotConnection->sharedVariables.inputs.mode = controlModes::AUTOMATIC_BALANCE_OBJECT_SEARCH;
    }
}


// will update the gui with the updated variables
void MainWindow::udpHasAUpdate()
{
    qDebug()<< "updating main" << endl;

    if(robotConnection->sharedVariables.inputs.mode == controlModes::MANUAL_WIFI){
        speedMotor1->setSpeed(robotConnection->sharedVariables.inputs.steppers.motor1TargetSpeed);
        speedMotor2->setSpeed(robotConnection->sharedVariables.inputs.steppers.motor2TargetSpeed);
        speedMotor1->setAcceleration(robotConnection->sharedVariables.inputs.steppers.acceleration);
        speedMotor2->setAcceleration(robotConnection->sharedVariables.inputs.steppers.acceleration);
    }else{
        speedMotor1->setSpeed(robotConnection->sharedVariables.outputs.steppers.motor1TargetSpeed/100);
        speedMotor2->setSpeed(robotConnection->sharedVariables.outputs.steppers.motor2TargetSpeed/100);
        speedMotor1->setAcceleration(robotConnection->sharedVariables.outputs.steppers.acceleration);
        speedMotor2->setAcceleration(robotConnection->sharedVariables.outputs.steppers.acceleration);
    }

    ui->progressBarCameraAngle->setValue(robotConnection->sharedVariables.outputs.servoPosition);
    ui->label_status_bar->setText(QString::number(robotConnection->sharedVariables.outputs.servoPosition));
    int leftLight = robotConnection->sharedVariables.outputs.lightLeft;
    leftLight = leftLight * (2 - 0.001 * leftLight);
    ui->ProgressbarIRLeft->setValue(leftLight);
    int rightLight = robotConnection->sharedVariables.outputs.lightRight;
    rightLight = rightLight * (2 - 0.001 * rightLight);
    ui->ProgressbarIRRight->setValue(rightLight);
    ui->progressBarProxyLeft->setValue(robotConnection->sharedVariables.outputs.proximityLeft);
    ui->progressBarProxyRight->setValue(robotConnection->sharedVariables.outputs.proximityRight);
    if(robotConnection->sharedVariables.outputs.TOFSensorWorking)
    {
        TOFSensor->setDistance(robotConnection->sharedVariables.outputs.TOFSensorDistanceMM);
    }
    else {
        TOFSensor->setDistance(-1);
    }
    battery->setVoltage(robotConnection->sharedVariables.outputs.voltage);
    proxySensorLeft->setProxy(robotConnection->sharedVariables.outputs.proximityLeft);
    //proxySensorRight->setProxy(robotConnection->sharedVariables.outputs.proximityRight);
    float accel = abs(robotConnection->sharedVariables.outputs.acceleration[0])+abs(robotConnection->sharedVariables.outputs.acceleration[1])+abs(robotConnection->sharedVariables.outputs.acceleration[2]);
    if(accel>1.5)
    {
        proxySensorRight->setProxy(accel*500);

    }
    else {

            proxySensorRight->setProxy(0);

    }
    qDebug()<<robotConnection->sharedVariables.outputs.lightLeft << endl;

    update();
}

void MainWindow::SendUdpToRobot()
{

    int32_t maxSpeed = ui->topSpeedSlider->value();
    int32_t steeringSensitivity = ui->CornerSlider->value();
    int32_t deltaWheels = 2 * steeringSensitivity;
    int32_t motor1Speed = 0;
    int32_t motor2Speed = 0;


    if(controlData.WPressed){
        motor1Speed += maxSpeed;
        motor2Speed += maxSpeed;
    }
    if(controlData.APressed){
       motor1Speed += steeringSensitivity;
       motor2Speed -= steeringSensitivity;
    }
    if(controlData.DPressed){
        motor1Speed -= steeringSensitivity;
        motor2Speed += steeringSensitivity;
    }
    if(controlData.SPressed){
        motor1Speed -= maxSpeed;
        motor2Speed -= maxSpeed;
    }
//    qDebug() << "motor" <<robotConnection->sharedVariables.inputs.steppers.motor1TargetSpeed<< " "<<robotConnection->sharedVariables.inputs.steppers.motor2TargetSpeed;

    if(ui->buttonBrakeMode->text() == "BrakeMode: Fast"){
        if(qFabs(motor1Speed) < qFabs(controlData.Motor1OldSpeed)){
            robotConnection->sharedVariables.inputs.steppers.acceleration = 600000;
        } else{
            robotConnection->sharedVariables.inputs.steppers.acceleration = ui->accelerationSlider->value();
        }
        if(qFabs(motor2Speed) < qFabs(controlData.Motor2OldSpeed)){
            robotConnection->sharedVariables.inputs.steppers.acceleration = 600000;
        } else{
            robotConnection->sharedVariables.inputs.steppers.acceleration = ui->accelerationSlider->value();
        }
        //robotConnection->sharedVariables.inputs.steppers.acceleration_motor2 = ui->accelerationSlider->value();
    }else{
        robotConnection->sharedVariables.inputs.steppers.acceleration = ui->accelerationSlider->value();
        robotConnection->sharedVariables.inputs.steppers.acceleration = ui->accelerationSlider->value();
    }
    robotConnection->sharedVariables.inputs.steppers.motor1TargetSpeed = motor1Speed;
    robotConnection->sharedVariables.inputs.steppers.motor2TargetSpeed = motor2Speed;


    if(robotConnection->sharedVariables.inputs.mode == controlModes::MANUAL_WIFI){
        speedMotor1->setSpeed(robotConnection->sharedVariables.inputs.steppers.motor1TargetSpeed);
        speedMotor2->setSpeed(robotConnection->sharedVariables.inputs.steppers.motor2TargetSpeed);
        speedMotor1->setAcceleration(robotConnection->sharedVariables.inputs.steppers.acceleration);
        speedMotor2->setAcceleration(robotConnection->sharedVariables.inputs.steppers.acceleration);
    }

    robotConnection->send();
    update();


    controlData.Motor1OldSpeed = motor1Speed;
    controlData.Motor2OldSpeed = motor2Speed;
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    qDebug()  << "key pressed:   " << ev->text() << endl;
    if(ev->key() == Qt::Key_W){
        controlData.WPressed = true;
    } else if(ev->key() == Qt::Key_S){
        controlData.SPressed = true;
    } else if(ev->key() == Qt::Key_A){
        controlData.APressed = true;
    } else if(ev->key() == Qt::Key_D){
        controlData.DPressed = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug()  << "key releassed: " << ev->text() << endl;
    if(ev->key() == Qt::Key_W){
        controlData.WPressed = false;

    } else if(ev->key() == Qt::Key_S){
        controlData.SPressed = false;
    } else if(ev->key() == Qt::Key_A){
        controlData.APressed = false;
    } else if(ev->key() == Qt::Key_D){
        controlData.DPressed = false;
    }
}

void MainWindow::on_buttonBrakeMode_clicked()
{
    if(ui->buttonBrakeMode->text() == "BrakeMode: Normal"){
        ui->buttonBrakeMode->setText("BrakeMode: Fast");
    } else {
        ui->buttonBrakeMode->setText("BrakeMode: Normal");
    }
}

void MainWindow::on_pushButton_clicked() // speed preset button
{

      if(ui->pushButton->text() == "Speed preset: None"){
          ui->pushButton->setText("Speed preset: Slow");
      } else if(ui->pushButton->text() == "Speed preset: Fast"){
          ui->pushButton->setText("Speed preset: Slow");
      } else if(ui->pushButton->text() == "Speed preset: Slow"){
          ui->pushButton->setText("Speed preset: Fast");
      }

}
