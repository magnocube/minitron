#include "graphiccamera.h"


QRectF graphicCamera::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void graphicCamera::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);

    QPen pen(Qt::red);
    pen.setWidth(2);
    QFont f;

    f.setPointSize(20);
    painter->setFont(f);


    painter->setPen(pen);
    painter->drawRect(QRect(0,0,200,200));

    painter->setBrush(brush);

    painter->drawEllipse(QPointF(y*2,200- x*2), 10, 10);
    pen.setColor(Qt::black);
    QString i;
    i.append("X = ");
    i.append(QString::number(x));
    i.append("  y = ");
    i.append(QString::number(y));
    painter->drawText(0,230, i);


}

void graphicCamera::setlocation(int _x, int _y)
{
    x = _x;
    y = _y;

}
