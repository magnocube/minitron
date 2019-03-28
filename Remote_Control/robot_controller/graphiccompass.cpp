#include "graphicCompass.h"


QRectF graphicCompass::boundingRect() const
{
    return QRectF(0,0,200,200);
}

void graphicCompass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);

    QPen pen(Qt::red);
    pen.setWidth(2);
    QFont f;

    f.setPointSize(20);
    painter->setFont(f);


    painter->setPen(pen);


    painter->setBrush(brush);

    QImage image(":/backgroundImages/images/transparentCompass.png");
    image = image.scaled(200, 200, Qt::KeepAspectRatio);

    QImage a(200, 200, QImage::Format_ARGB32_Premultiplied );
      QPainter p;
      p.begin( &a );
      p.drawImage(0,0,image);
      p.end();


    painter->translate(100,100);
    painter->rotate(angle);
    painter->translate(-100,-100);
    painter->drawImage(0,0,a);
//    QString i;
//    i.append("X = ");
//    i.append(QString::number(x));
//    i.append("  y = ");
//    i.append(QString::number(y));
//    painter->drawText(0,230, i);


}



void graphicCompass::setRotation(int d)
{
    angle = d;
}
