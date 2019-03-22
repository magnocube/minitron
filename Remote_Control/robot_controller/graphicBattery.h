#ifndef GRAPHICBATTERY_H
#define GRAPHICBATTERY_H

#include <QGraphicsItem>
#include <QPainter>
#include <QMath.h>


class GraphicBattery : public QGraphicsItem
{
public:
    GraphicBattery();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setVoltage(double s);


private:
    double voltage;


};

#endif // GRAPHICBATTERY_H