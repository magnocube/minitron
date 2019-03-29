#include "graphicstofsensor.h"

graphicsTOFSensor::graphicsTOFSensor()
{
    distance = -1;

}

QRectF graphicsTOFSensor::boundingRect() const
{
    return QRectF(0,0,width,heigth);
}

void graphicsTOFSensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    QPen pen(Qt::black);
    QFont f;

    f.setPointSize(30);
    painter->setFont(f);

    QString i;
    i.append("TOF Sensor: ");\
    if(distance == -1)
    {
        i.append("ERROR sensor not working");

    }
    else {
        i.append(QString::number(distance));
        i.append(" mm");

    }
    painter->drawText(2,365,i);


    //painter->fillRect(rect,brush);
//   painter->drawRect(rect);


}

void graphicsTOFSensor::setDistance(int d)
{
    distance = d;
}
