#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qCustomPlot/qcustomplot.h"
#include "Aircraft/aircraft.h"
namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT
    
public:
  explicit GraphWindow(QWidget *parent = 0);
  ~GraphWindow();

  void setupDemo(int demoIndex,Aircraft *acrft=0);
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
  void setupRealtimeT10Data(QCustomPlot *customPlot,Aircraft *acrft);

private slots:
  void realtimeDataSlot();
  void realtimeT10Slot(QList<int> indata);
  void screenShot();
  void allScreenShots();

private:
  Ui::GraphWindow *ui;
  QString demoName;
  QTimer realRealtimeDataTimer;
  int currentDemoIndex;
};

#endif // GRAPHWINDOW_H
