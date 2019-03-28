#ifndef GRAPHICCOMPASS_H
#define GRAPHICCOMPASS_H

#include <QGraphicsItem>
#include <QPainter>

class graphicCompass: public QGraphicsItem
{
public:
    //graphicCompass();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setRotation(int d);


private:
    int angle;


};
#endif // GRAPHICCOMPASS_H
