#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "qCustomPlot/qcustomplot.h"
namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();
    void setupDemo(int demoIndex);
    void setupQuadraticDemo(QCustomPlot *customPlot);
    void setupSimpleDemo(QCustomPlot *customPlot);
    void setupSincScatterDemo(QCustomPlot *customPlot);
    void setupScatterStyleDemo(QCustomPlot *customPlot);
    void setupLineStyleDemo(QCustomPlot *customPlot);
    void setupScatterPixmapDemo(QCustomPlot *customPlot);
    void setupDateDemo(QCustomPlot *customPlot);
    void setupTextureBrushDemo(QCustomPlot *customPlot);
    void setupMultiAxisDemo(QCustomPlot *customPlot);
    void setupLogarithmicDemo(QCustomPlot *customPlot);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void setupParametricCurveDemo(QCustomPlot *customPlot);
    void setupBarChartDemo(QCustomPlot *customPlot);
    void setupStatisticalDemo(QCustomPlot *customPlot);
    void setupPlayground(QCustomPlot *customPlot);
private slots:
    void realtimeDataSlot();
    void screenShot();
    void allScreenShots();
private:
    QString demoName;
    QTimer realRealtimeDataTimer;
    int currentDemoIndex;
    // QStatusBar* statusbar;
    Ui::GraphWidget *ui;
};

#endif // GRAPHWIDGET_H
