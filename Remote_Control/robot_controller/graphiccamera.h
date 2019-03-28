#ifndef GRAPHICCAMERA_H
#define GRAPHICCAMERA_H

#include <QGraphicsItem>
#include <QPainter>

class graphicCamera: public QGraphicsItem
{
public:
    //graphicCamera();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setlocation(int x ,int y);


private:
    int x;
    int y;
    bool active = false;

};
#endif // GRAPHICCAMERA_H
