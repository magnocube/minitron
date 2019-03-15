#ifndef GRAPHICSTOFSENSOR_H
#define GRAPHICSTOFSENSOR_H


#include <QGraphicsItem>
#include <QPainter>


class graphicsTOFSensor : public QGraphicsItem
{
public:
    graphicsTOFSensor();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setDistance(int d);


private:
    int distance;
    const int width = 400;
    const int heigth = 400;

};

#endif // GRAPHICSTOFSENSOR_H
