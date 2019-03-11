#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    robotConnection = new UDP_Connection();
    robotConnection->send("lol+lol=hihi");


    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);



}

void MainWindow::resizeEvent(QResizeEvent* event)
{
 //  QMainWindow::resizeEvent(event);




}

MainWindow::~MainWindow()
{
    delete ui;
}
