#include "graphicspeedsensor.h"

GraphicSpeedSensor::GraphicSpeedSensor()
{

    speed = 40;
    acceleration = 100;
}

QRectF GraphicSpeedSensor::boundingRect() const
{
    return QRectF(0,0,150,200);
}

void GraphicSpeedSensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    QPen pen(Qt::black);

    QFont f;
    f.setPointSize(20);
    painter->setFont(f);
    painter->drawText(2,25,"speed: ");

    f.setPointSize(50);
    painter->setFont(f);
    painter->drawText(0,80,QString::number(speed));

    f.setPointSize(20);
    painter->setFont(f);
    painter->drawText(2,105,"acceleration:");

    f.setPointSize(40);
    painter->setFont(f);
    painter->drawText(2,150,QString::number(acceleration));

    //painter->fillRect(rect,brush);
    //painter->drawRect(rect);

    int barX = 10;
    int barY = 160;
    int barW = 130;
    int barH = 30;

    painter->drawRect(barX,barY,barW,barH);
    brush.setColor(Qt::red);
    QRectF percentageBar(barX,barY,speed/10000.0*barW,barH);
    painter->fillRect(percentageBar,brush);
    painter->drawRect(percentageBar);






}

void GraphicSpeedSensor::setSpeed(int s)
{
    speed = s;
}

void GraphicSpeedSensor::setAcceleration(int a)
{
    acceleration = a;
}
