#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qCustomPlot/qcustomplot.h"
#include "Aircraft/aircraft.h"
#include "QStandardItemModel"
#include "QListWidgetItem"
#include "QInputDialog"
#include "QFileDialog"
#include "QLabel"
#include "qCustomPlot/writer.h"
#include "QComboBox"
namespace Ui {
class GraphWindow;
}

class GraphWindow : public QMainWindow
{
    Q_OBJECT
    
public:
  explicit GraphWindow(QWidget *parent = 0);
    void setAirctaftData(Aircraft *acrft);
  ~GraphWindow();

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
  void setupRealtimeT10Data(QCustomPlot *customPlot);
private slots:
  void realtimeDataSlot();
  void realtimeT10Slot(QList<int> indata);
  void screenShot();
  void allScreenShots();
    void slotSaveData(QVector<double> aVectorData);

void saveFilterChanged(const QString &filter);
void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void on_actionShot_triggered();

  void on_pb_add_clicked();

  void on_actionStart_toggled(bool arg1);

  void on_actionPause_triggered();

  void on_pb_remove_clicked();

  void on_tableGraphics_itemClicked(QListWidgetItem *item);

  void on_actionSave_to_File_triggered();

  void on_actionWriteDataToFile_toggled(bool arg1);
signals:
  void readyToSaveData(QVector<double> aVectorData);
private:
  Aircraft *graphAircraft;
  QMap<int, QString> graphMap;
  QMap<int, QString> currentgraphMap;
  Qt::GlobalColor getColor(int kind);
  Ui::GraphWindow *ui;
  QString demoName;
  QTimer realRealtimeDataTimer;
  QVector <double> time;
  double timePoint;
  bool addTime;

  int screenShotCount;
  int currentDemoIndex;
  QComboBox* currentgraphList;
  QVector<QVector <double> > dataVector;

};

#endif // GRAPHWINDOW_H
