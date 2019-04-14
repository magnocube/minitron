#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::setupPlots(){
    // add two new graphs and set their look:
    ui->PlotViewerSpeeds->addGraph();
    ui->PlotViewerSpeeds->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->PlotViewerSpeeds->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->PlotViewerSpeeds->addGraph();
    ui->PlotViewerSpeeds->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    //ui->PlotViewerSpeeds->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(2510), y0(2510), y1(2510);
    for (int i=0; i<2510; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->PlotViewerSpeeds->xAxis2->setVisible(true);
    ui->PlotViewerSpeeds->xAxis2->setTickLabels(false);
    ui->PlotViewerSpeeds->yAxis2->setVisible(true);
    ui->PlotViewerSpeeds->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->PlotViewerSpeeds->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->PlotViewerSpeeds->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->PlotViewerSpeeds->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->PlotViewerSpeeds->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->PlotViewerSpeeds->graph(0)->setData(x, y0);
    ui->PlotViewerSpeeds->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->PlotViewerSpeeds->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    ui->PlotViewerSpeeds->graph(1)->rescaleAxes(true);
    // Note: we could have also just called ui->PlotViewerSpeeds->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->PlotViewerSpeeds->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables );

}

void MainWindow::updatePlots()
{

}
