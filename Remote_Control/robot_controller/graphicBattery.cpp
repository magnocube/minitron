#include "GraphicBattery.h"

#include <QDateTime>

GraphicBattery::GraphicBattery()
{

    voltage = 0.0;
}

QRectF GraphicBattery::boundingRect() const
{
    return QRectF(0,0,150,200);
}

void GraphicBattery::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QBrush brush(Qt::red);
    QPen pen(Qt::black);

    QFont f;
    f.setPointSize(20);
    painter->setFont(f);
    painter->drawText(2,25,"Voltage: ");

    f.setPointSize(50);
    painter->setFont(f);

    QString voltageText;
    if(QDateTime::currentMSecsSinceEpoch() - lastUpdate > 500)
    {
        lastUpdate = QDateTime::currentMSecsSinceEpoch();
        voltageText = QString().sprintf("%3.1f",voltage);
        oldVoltage = voltage;
    }
    else {
        voltageText = QString().sprintf("%3.1f",oldVoltage);
    }

    painter->drawText(0,80, voltageText);



    //painter->fillRect(rect,brush);
    //painter->drawRect(rect);

    int barX = 10;
    int barY = 90;
    int barW = 130;
    int barH = 30;

    painter->drawRect(barX,barY,barW,barH);
    brush.setColor(Qt::green);
    QRectF percentageBar(barX,barY,voltage/12.8*barW,barH);
    painter->fillRect(percentageBar,brush);
    painter->drawRect(percentageBar);






}


void GraphicBattery::setVoltage(double s)
{
    voltage = s;
}
