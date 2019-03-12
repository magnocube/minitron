#ifndef GRAPHICSPEEDSENSOR_H
#define GRAPHICSPEEDSENSOR_H

#include <QGraphicsItem>
#include <QPainter>



class GraphicSpeedSensor : public QGraphicsItem
{
public:
    GraphicSpeedSensor();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSpeed(int s);
    void setAcceleration(int a);

private:
    int speed;
    int acceleration;

};

#endif // GRAPHICSPEEDSENSOR_H
