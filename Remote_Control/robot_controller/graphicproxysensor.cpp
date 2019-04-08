#include "graphicproxysensor.h"

graphicProxySensor::graphicProxySensor(int whichOne)
{
 proxy = 0;
 whichSide = whichOne;
}

QRectF graphicProxySensor::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void graphicProxySensor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    QPen pen(Qt::red);
    pen.setWidth(8);
    QFont f;


    painter->setPen(pen);

    for(int i = 0;i<=proxy;i++)
    {
        if(whichSide)
        {
            painter->drawArc(0,100-10*i,20*i,20*i,(-70)*16,(140)*16);

        }
        else
        {
            painter->drawArc(200-20*i,100-10*i,20*i,20*i,(-70+180)*16,(140)*16);

        }
    }

}

void graphicProxySensor::setProxy(int p)
{
    proxy = (p/100.0) * (2 - 0.001* p);

}
