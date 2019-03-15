#ifndef GRAPHICPROXYSENSOR_H
#define GRAPHICPROXYSENSOR_H



#include <QGraphicsItem>
#include <QPainter>


class graphicProxySensor : public QGraphicsItem
{
public:
    graphicProxySensor(int whichOne);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setProxy(int p);


private:
    int proxy;
    int whichSide;


};

#endif // GRAPHICPROXYSENSOR_H
