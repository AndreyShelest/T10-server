#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <cmath>
#include <cstdlib>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>

GraphWindow::GraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GraphWindow)
{
    ui->setupUi(this);
   // setGeometry(150, 150, 546, 390);
screenShotCount=0;
timePoint=0;
addTime=false;
graphMap=Aircraft::getQmapData();
ui->cb_data->addItems(graphMap.values());
    //setupDemo(14);

    // 0:  setupQuadraticDemo(ui->customPlot);
    // 1:  setupSimpleDemo(ui->customPlot);
    // 2:  setupSincScatterDemo(ui->customPlot);
    // 3:  setupScatterStyleDemo(ui->customPlot);
    // 4:  setupScatterPixmapDemo(ui->customPlot);
    // 5:  setupLineStyleDemo(ui->customPlot);
    // 6:  setupDateDemo(ui->customPlot);
    // 7:  setupTextureBrushDemo(ui->customPlot);
    // 8:  setupMultiAxisDemo(ui->customPlot);
    // 9:  setupLogarithmicDemo(ui->customPlot);
    // 10: setupRealtimeDataDemo(ui->customPlot);
    // 11: setupParametricCurveDemo(ui->customPlot);
    // 12: setupBarChartDemo(ui->customPlot);
    // 13: setupStatisticalDemo(ui->customPlot);

    // for making screenshots of the current demo or all demos (for website screenshots):
    //QTimer::singleShot(350, this, SLOT(allScreenShots()));
//QTimer::singleShot(1000, this, SLOT(screenShot()));
connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
        this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
}
void GraphWindow::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
  // Rename a graph by double clicking on its legend item

  Q_UNUSED(legend)
  if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
  {
    QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
    bool ok;
    QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
    if (ok)
    {
      plItem->plottable()->setName(newName);
      ui->customPlot->replot();
    }
  }
}

void GraphWindow::setAirctaftData(Aircraft *acrft)
{
    graphAircraft=acrft;
}
void GraphWindow::setupDemo(int demoIndex)
{
  switch (demoIndex)
  {
    case 0:  setupQuadraticDemo(ui->customPlot); break;
    case 1:  setupSimpleDemo(ui->customPlot); break;
    case 2:  setupSincScatterDemo(ui->customPlot); break;
    case 3:  setupScatterStyleDemo(ui->customPlot); break;
    case 4:  setupScatterPixmapDemo(ui->customPlot); break;
    case 5:  setupLineStyleDemo(ui->customPlot); break;
    case 6:  setupDateDemo(ui->customPlot); break;
    case 7:  setupTextureBrushDemo(ui->customPlot); break;
    case 8:  setupMultiAxisDemo(ui->customPlot); break;
    case 9:  setupLogarithmicDemo(ui->customPlot); break;
    case 10: setupRealtimeDataDemo(ui->customPlot); break;
    case 11: setupParametricCurveDemo(ui->customPlot); break;
    case 12: setupBarChartDemo(ui->customPlot); break;
    case 13: setupStatisticalDemo(ui->customPlot); break;
    case 14: setupRealtimeT10Data(ui->customPlot); break;
  }
  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
  currentDemoIndex = demoIndex;
  ui->customPlot->replot();

}

void GraphWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
  demoName = "Quadratic Demo";
  // generate some data:
  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = x[i]*x[i];  // let's plot a quadratic function
  }
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(0, 1);
}

void GraphWindow::setupSimpleDemo(QCustomPlot *customPlot)
{
  demoName = "Simple Demo";

  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(250), y0(250), y1(250);
  for (int i=0; i<250; ++i)
  {
    x[i] = i;
    y0[i] = exp(-i/150.0)*cos(i/10.0); // exponentially decaying cosine
    y1[i] = exp(-i/150.0);             // exponential envelope
  }
  // configure right and top axis to show ticks but no labels (could've also just called customPlot->setupFullAxesBox):
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // make range moveable by mouse interaction (click and drag):
  customPlot->setRangeDrag(Qt::Horizontal | Qt::Vertical);
  customPlot->setRangeZoom(Qt::Horizontal | Qt::Vertical);
  customPlot->setInteraction(QCustomPlot::iSelectPlottables); // allow selection of graphs via mouse click
}

void GraphWindow::setupSincScatterDemo(QCustomPlot *customPlot)
{
  demoName = "Sinc Scatter Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica",9));
  // set locale to english, so we get english decimal separator:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // add confidence band graphs:
  customPlot->addGraph();
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor(QColor(180,180,180));
  customPlot->graph(0)->setName("Confidence Band 68%");
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
  customPlot->addGraph();
  customPlot->legend->removeItem(customPlot->legend->itemCount()-1); // don't show two confidence band graphs in legend
  customPlot->graph(1)->setPen(pen);
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
  // add theory curve graph:
  customPlot->addGraph();
  pen.setStyle(Qt::DashLine);
  pen.setWidth(2);
  pen.setColor(Qt::red);
  customPlot->graph(2)->setPen(pen);
  customPlot->graph(2)->setName("Theory Curve");
  // add data point graph:
  customPlot->addGraph();
  customPlot->graph(3)->setPen(QPen(Qt::blue));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPGraph::ssCross);
  customPlot->graph(3)->setScatterSize(4);
  customPlot->graph(3)->setErrorType(QCPGraph::etValue);
  customPlot->graph(3)->setErrorPen(QPen(QColor(180,180,180)));
  customPlot->graph(3)->setName("Measurement");

  // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
  QVector<double> x0(250), y0(250);
  QVector<double> yConfUpper(250), yConfLower(250);
  for (int i=0; i<250; ++i)
  {
    x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
    y0[i] = sin(x0[i])/x0[i]; // sinc function
    yConfUpper[i] = y0[i]+0.15;
    yConfLower[i] = y0[i]-0.15;
    x0[i] *= 1000;
  }
  QVector<double> x1(50), y1(50), y1err(50);
  for (int i=0; i<50; ++i)
  {
    // generate a gaussian distributed random number:
    double tmp1 = rand()/(double)RAND_MAX;
    double tmp2 = rand()/(double)RAND_MAX;
    double r = sqrt(-2*log(tmp1))*cos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
    // set y1 to value of y0 plus a random gaussian pertubation:
    x1[i] = (i/50.0-0.5)*30+0.25;
    y1[i] = sin(x1[i])/x1[i]+r*0.15;
    x1[i] *= 1000;
    y1err[i] = 0.15;
  }
  // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
  customPlot->graph(0)->setData(x0, yConfUpper);
  customPlot->graph(1)->setData(x0, yConfLower);
  customPlot->graph(2)->setData(x0, y0);
  customPlot->graph(3)->setDataValueError(x1, y1, y1err);
  customPlot->graph(2)->rescaleAxes();
  customPlot->graph(3)->rescaleAxes(true);
  // setup look of bottom tick labels:
  customPlot->xAxis->setTickLabelRotation(30);
  customPlot->xAxis->setAutoTickCount(9);
  customPlot->xAxis->setNumberFormat("ebc");
  customPlot->xAxis->setNumberPrecision(1);
  customPlot->xAxis->moveRange(-10);
  // make top right axes clones of bottom left axes, looks prettier:
  customPlot->setupFullAxesBox();
}

void GraphWindow::setupScatterStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setPositionStyle(QCPLegend::psRight);
  QPen pen;
  QStringList scatterNames;
  scatterNames << "ssCross" << "ssPlus" << "ssCircle" << "ssDisc"
               << "ssSquare" << "ssStar" << "ssTriangle" << "ssTriangleInverted"
               << "ssCrossSquare" << "ssPlusSquare" << "ssCrossCircle"
               << "ssPlusCircle" << "ssPeace";
  // add graphs with different scatter styles:
  for (int i=QCPGraph::ssCross; i<=QCPGraph::ssPeace; ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(sin(i*0.3)*100+100, sin(i*0.6+0.7)*100+100, sin(i*0.4+0.6)*100+100));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(scatterNames.at(i-QCPGraph::ssCross));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setScatterStyle((QCPGraph::ScatterStyle)i);
    customPlot->graph()->setScatterSize(10);
    // generate data:
    QVector<double> x(10), y(10);
    for (int j=0; j<10; ++j)
    {
      x[j] = j/10.0 * 4*3.14 + 0.01;
      y[j] = 7*sin(x[j])/x[j] + (i-QCPGraph::ssCross)*5;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
  }
  // zoom out a bit:
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  // set blank axis lines:
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(false);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(false);
  // make top right axes clones of bottom left axes:
  customPlot->setupFullAxesBox();
}

void GraphWindow::setupLineStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Line Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setPositionStyle(QCPLegend::psTopRight);
  QPen pen;
  QStringList lineNames;
  lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight"
               << "lsStepCenter" << "lsImpulse";
  // add graphs with different line styles:
  for (int i=QCPGraph::lsNone; i<=QCPGraph::lsImpulse; ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(sin(i*1+1.2)*80+80, sin(i*0.3+0)*80+80, sin(i*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)i);
    customPlot->graph()->setScatterStyle(QCPGraph::ssCircle);
    customPlot->graph()->setScatterSize(5);
    // generate data:
    QVector<double> x(15), y(15);
    for (int j=0; j<15; ++j)
    {
      x[j] = j/15.0 * 5*3.14 + 0.01;
      y[j] = 7*sin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
  }
  // zoom out a bit:
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
  // set blank axis lines:
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(true);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(true);
  // make top right axes clones of bottom left axes:
  customPlot->setupFullAxesBox();
}

void GraphWindow::setupScatterPixmapDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Pixmap Demo";
  customPlot->setAxisBackground(QPixmap("./solarpanels.jpg"));
  customPlot->addGraph();
  customPlot->graph()->setLineStyle(QCPGraph::lsLine);
  QPen pen;
  pen.setColor(QColor(255, 200, 20, 200));
  pen.setStyle(Qt::DashLine);
  pen.setWidthF(2.5);
  customPlot->graph()->setPen(pen);
  customPlot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
  customPlot->graph()->setScatterStyle(QCPGraph::ssPixmap);
  customPlot->graph()->setScatterPixmap(QPixmap("./sun.png"));
  // set graph name, will show up in legend next to icon:
  customPlot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
  // set data:
  QVector<double> year, value;
  year  << 2005 << 2006 << 2007 << 2008  << 2009  << 2010;
  value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33;
  customPlot->graph()->setData(year, value);

  // set title of plot:
  customPlot->setTitle("Regenerative Energies");
  // set a fixed tick-step to one tick per year value:
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(1);
  customPlot->xAxis->setSubTickCount(3);
  // other axis configurations:
  customPlot->xAxis->setLabel("Year");
  customPlot->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setSubTickCount(0);
  customPlot->yAxis2->setSubTickCount(0);
  customPlot->xAxis->setRange(2004.5, 2010.5);
  customPlot->yAxis->setRange(0, 30);
  // setup legend position:
  customPlot->legend->setPositionStyle(QCPLegend::psTopLeft);
}

void GraphWindow::setupDateDemo(QCustomPlot *customPlot)
{
  demoName = "Date Demo";
  // set locale to english, so we get english month names:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // seconds of current time, we'll use it as starting point in time for data:
  double now = QDateTime::currentDateTime().toTime_t();
  srand(8); // set the random seed, so we always get the same random data
  // create multiple graphs:
  for (int gi=0; gi<5; ++gi)
  {
    customPlot->addGraph();
    QPen pen;
    pen.setColor(QColor(0, 0, 255, 200));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setBrush(QBrush(QColor(255/4.0*gi,160,50,150)));
    // generate random walk data:
    QVector<double> time(250), value(250);
    for (int i=0; i<250; ++i)
    {
      time[i] = now + 24*3600*i;
      if (i == 0)
        value[i] = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      else
        value[i] = fabs(value[i-1])*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
    }
    customPlot->graph()->setData(time, value);
  }
  // configure bottom axis to show date and time instead of number:
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("MMMM\nyyyy");
  // set a more compact font size for bottom and left axis tick labels:
  customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
  // set a fixed tick-step to one tick per month:
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2628000); // one month in seconds
  customPlot->xAxis->setSubTickCount(3);
  // apply manual tick and tick label for left axis:
  QVector<double> tickVector;
  QVector<QString> tickLabels;
  tickVector << 5 << 55;
  tickLabels << "Not so\nhigh" << "Very\nhigh";
  customPlot->yAxis->setAutoTicks(false);
  customPlot->yAxis->setAutoTickLabels(false);
  customPlot->yAxis->setTickVector(&tickVector, true);
  customPlot->yAxis->setTickVectorLabels(&tickLabels, true);
  // set axis labels:
  customPlot->xAxis->setLabel("Date");
  customPlot->yAxis->setLabel("Random wobbly lines value");
  // make top and right axes visible but without ticks and labels:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set axis ranges to show all data:
  customPlot->xAxis->setRange(now, now+24*3600*249);
  customPlot->yAxis->setRange(0, 60);
  // activate legend and position it in top left corner:
  customPlot->legend->setVisible(true);
  customPlot->legend->setPositionStyle(QCPLegend::psTopLeft);
}

void GraphWindow::setupTextureBrushDemo(QCustomPlot *customPlot)
{
  demoName = "Texture Brush Demo";
  // add two graphs with a textured fill:
  customPlot->addGraph();
  QPen redDotPen;
  redDotPen.setStyle(Qt::DotLine);
  redDotPen.setColor(QColor(170, 100, 100, 180));
  redDotPen.setWidthF(2);
  customPlot->graph(0)->setPen(redDotPen);
  customPlot->graph(0)->setBrush(QBrush(QPixmap("./dali.png"))); // fill with texture of specified png-image

  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));

  // activate channel fill for graph 0 towards graph 1:
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  // generate data:
  QVector<double> x(250);
  QVector<double> y0(250), y1(250);
  for (int i=0; i<250; ++i)
  {
    // just playing with numbers, not much to learn here
    x[i] = 3*i/250.0;
    y0[i] = 1+exp(-x[i]*x[i]*0.8)*(x[i]*x[i]+x[i]);
    y1[i] = 1-exp(-x[i]*x[i]*0.4)*(x[i]*x[i])*0.1;
  }

  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // activate top and right axes, which are invisible by default:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  // make tick labels invisible on top and right axis:
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set ranges:
  customPlot->xAxis->setRange(0, 2.5);
  customPlot->yAxis->setRange(0.9, 1.6);
  // assign top/right axes same properties as bottom/left:
  customPlot->setupFullAxesBox();
}

void GraphWindow::setupMultiAxisDemo(QCustomPlot *customPlot)
{
  demoName = "Multi Axis Demo";

  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
  customPlot->setAntialiasedElement(QCustomPlot::aeScatters);

  customPlot->legend->setVisible(true);
  QFont legendFont = font();  // start out with GraphWindow's font..
  legendFont.setPointSize(9); // and make a bit smaller for legend
  customPlot->legend->setFont(legendFont);
  customPlot->legend->setPositionStyle(QCPLegend::psBottomRight);
  customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));

  // setup for graph 0: key axis left, value axis bottom
  // will contain left maxwell-like function
  customPlot->addGraph(customPlot->yAxis, customPlot->xAxis);
  customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
  customPlot->graph(0)->setBrush(QBrush(QPixmap("./dali.png"))); // fill with texture of specified png-image
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPGraph::ssDisc);
  customPlot->graph(0)->setScatterSize(5);
  customPlot->graph(0)->setName("Left maxwell function");

  // setup for graph 1: key axis bottom, value axis left (those are the default axes)
  // will contain bottom maxwell-like function
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setBrush(QBrush(QPixmap("./dali.png"))); // same fill as we used for graph 0
  customPlot->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
  customPlot->graph(1)->setScatterStyle(QCPGraph::ssCircle);
  customPlot->graph(1)->setErrorType(QCPGraph::etValue);
  customPlot->graph(1)->setName("Bottom maxwell function");

  // setup for graph 2: key axis top, value axis right
  // will contain high frequency sine with low frequency beating:
  customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis2);
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setName("High frequency sine");

  // setup for graph 3: same axes as graph 2
  // will contain low frequency beating envelope of graph 2
  customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis2);
  QPen blueDotPen;
  blueDotPen.setColor(QColor(30, 40, 255, 150));
  blueDotPen.setStyle(Qt::DotLine);
  blueDotPen.setWidthF(4);
  customPlot->graph(3)->setPen(blueDotPen);
  customPlot->graph(3)->setName("Sine envelope");

  // setup for graph 4: key axis right, value axis top
  // will contain parabolically distributed data points with some random perturbance
  customPlot->addGraph(customPlot->yAxis2, customPlot->xAxis2);
  customPlot->graph(4)->setPen(QColor(50, 50, 50, 255));
  customPlot->graph(4)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(4)->setScatterStyle(QCPGraph::ssPlus);
  customPlot->graph(4)->setScatterSize(4);
  customPlot->graph(4)->setName("Some random data around\na quadratic function");

  // generate data, just playing with numbers, not much to learn here:
  QVector<double> x0(50), y0(50);
  QVector<double> x1(25), y1(25), y1err(25);
  QVector<double> x2(250), y2(250);
  QVector<double> x3(250), y3(250);
  QVector<double> x4(250), y4(250);
  for (int i=0; i<50; ++i) // data for graph 0
  {
    x0[i] = 5*i/50.0;
    y0[i] = exp(-x0[i]*x0[i]*0.8)*(x0[i]*x0[i]+x0[i]);
  }
  for (int i=0; i<25; ++i) // data for graph 1
  {
    x1[i] = 5*i/25.0;;
    y1[i] = exp(-x1[i]*x1[i])*(x1[i]*x1[i])*2.6;
    y1err[i] = y1[i]*0.25;
  }
  for (int i=0; i<250; ++i) // data for graphs 2, 3 and 4
  {
    x2[i] = i/250.0*3*M_PI;
    x3[i] = x2[i];
    x4[i] = i/250.0*100-50;
    y2[i] = sin(x2[i]*12)*cos(x2[i])*10;
    y3[i] = cos(x3[i])*10;
    y4[i] = 0.01*x4[i]*x4[i] + 1.5*(rand()/(double)RAND_MAX-0.5) + 1.5*M_PI;
  }
  // pass data points to graphs:
  customPlot->graph(0)->setData(x0, y0);
  customPlot->graph(1)->setDataValueError(x1, y1, y1err);
  customPlot->graph(2)->setData(x2, y2);
  customPlot->graph(3)->setData(x3, y3);
  customPlot->graph(4)->setData(x4, y4);
  // activate top and right axes, which are invisible by default:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  // set ranges appropriate to show data:
  customPlot->xAxis->setRange(0, 2.7);
  customPlot->yAxis->setRange(0, 2.6);
  customPlot->xAxis2->setRange(0, 3.0*M_PI);
  customPlot->yAxis2->setRange(-70, 35);
  // set pi ticks on top axis:
  QVector<double> piTicks;
  QVector<QString> piLabels;
  piTicks << 0  << 0.5*M_PI << M_PI << 1.5*M_PI << 2*M_PI << 2.5*M_PI << 3*M_PI;
  piLabels << "0" << QString::fromUtf8("½π") << QString::fromUtf8("π") << QString::fromUtf8("1½π") << QString::fromUtf8("2π") << QString::fromUtf8("2½π") << QString::fromUtf8("3π");
  customPlot->xAxis2->setAutoTicks(false);
  customPlot->xAxis2->setAutoTickLabels(false);
  customPlot->xAxis2->setTickVector(&piTicks, true);
  customPlot->xAxis2->setTickVectorLabels(&piLabels, true);
  // set labels:
  customPlot->setTitle("Way too many graphs in one plot");
  customPlot->xAxis->setLabel("Bottom axis with outward ticks");
  customPlot->yAxis->setLabel("Left axis label");
  customPlot->xAxis2->setLabel("Top axis label");
  customPlot->yAxis2->setLabel("Right axis label");
  // make ticks on bottom axis go outward:
  customPlot->xAxis->setTickLength(0, 5);
  customPlot->xAxis->setSubTickLength(0, 3);
  // make ticks on right axis go inward and outward:
  customPlot->yAxis2->setTickLength(3, 3);
  customPlot->yAxis2->setSubTickLength(1, 1);
}

void GraphWindow::setupLogarithmicDemo(QCustomPlot *customPlot)
{
  demoName = "Logarithmic Demo";
  customPlot->addGraph();
  QPen pen;
  pen.setColor(QColor(255,170,100));
  pen.setWidth(2);
  pen.setStyle(Qt::DotLine);
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setName("x");

  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
  customPlot->graph(1)->setErrorType(QCPGraph::etBoth);
  customPlot->graph(1)->setName("-sin(x)exp(x)");

  customPlot->addGraph();
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
  customPlot->graph(2)->setName(" sin(x)exp(x)");

  customPlot->addGraph();
  pen.setColor(QColor(0,0,0));
  pen.setWidth(1);
  pen.setStyle(Qt::DashLine);
  customPlot->graph(3)->setPen(pen);
  customPlot->graph(3)->setBrush(QBrush(QColor(0,0,0,15)));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsStepCenter);
  customPlot->graph(3)->setName("x!");

  QVector<double> x0(200), y0(200);
  QVector<double> x1(200), y1(200);
  QVector<double> x2(200), y2(200);
  QVector<double> x3(21), y3(21);
  for (int i=0; i<200; ++i)
  {
    x0[i] = i/10.0;
    y0[i] = x0[i];
    x1[i] = i/10.0;
    y1[i] = -sin(x1[i])*exp(x1[i]);
    x2[i] = i/10.0;
    y2[i] = sin(x2[i])*exp(x2[i]);
  }
  for (int i=0; i<21; ++i)
  {
    x3[i] = i;
    y3[i] = 1;
    for (int k=1; k<=i; ++k) y3[i] *= k; // factorial
  }
  customPlot->graph(0)->setData(x0, y0);
  customPlot->graph(1)->setData(x1, y1);
  customPlot->graph(2)->setData(x2, y2);
  customPlot->graph(3)->setData(x3, y3);

  customPlot->yAxis->setSubGrid(true);
  customPlot->xAxis->setSubGrid(true);
  customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
  customPlot->yAxis->setScaleLogBase(100);
  customPlot->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
  customPlot->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
  customPlot->yAxis->setSubTickCount(10);
  customPlot->xAxis->setRange(0, 19.9);
  customPlot->yAxis->setRange(1e-2, 1e10);
  // make range draggable and zoomable:
  customPlot->setRangeZoom(Qt::Horizontal | Qt::Vertical);
  customPlot->setRangeDrag(Qt::Horizontal | Qt::Vertical);

  // make top right axes clones of bottom left axes:
  customPlot->setupFullAxesBox();
  // connect signals so top and right axes move in sync with bottom and left axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  customPlot->legend->setVisible(true);
  customPlot->legend->setPositionStyle(QCPLegend::psTopLeft);
  customPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
}

void GraphWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  demoName = "Real Time Data Demo";
  /*
  // include this section to fully disable antialiasing for higher performance:
  customPlot->setAntialiasedElements(0);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickFont(font);
  customPlot->yAxis->setTickFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

  customPlot->addGraph(); // blue dot
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(2)->setScatterStyle(QCPGraph::ssDisc);
  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPGraph::ssDisc);

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls GraphWindow::realtimeDataSlot:
  connect(&realRealtimeDataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  realRealtimeDataTimer.start(0); // Interval 0 means to refresh as fast as possible
}
void GraphWindow::setupRealtimeT10Data(QCustomPlot *customPlot)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  demoName = "Real Time T10 data";
  /*
  // include this section to fully disable antialiasing for higher performance:
  customPlot->setAntialiasedElements(0);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickFont(font);
  customPlot->yAxis->setTickFont(font);
  customPlot->legend->setFont(font);
  */
  dataVector.clear();
QVector<double> buf;
//buf.append(0);
  int n=ui->tableGraphics->count();
QMap<int, QString> ::iterator it=currentgraphMap.begin();
  for (int i=0;i<n;i++)
  {
      customPlot->addGraph(); // blue line
      customPlot->graph(i)->setPen(QPen(getColor(i)));
       customPlot->graph(i)->setName(it.value());
       dataVector.append(buf);
      //customPlot->graph(i)->setBrush(QBrush(QColor(240, 255, 200)));
++it;
       }

  for (int i=n;i<2*n;i++)
  {
      customPlot->addGraph(); // blue dot
      customPlot->graph(i)->setPen(QPen(getColor(i-n)));
      customPlot->graph(i)->setLineStyle(QCPGraph::lsNone);
      customPlot->graph(i)->setScatterStyle(QCPGraph::ssDisc);
      customPlot->legend->removeItem(customPlot->legend->item(n));
  }

  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
  customPlot->xAxis->setAutoTickStep(false);
  customPlot->xAxis->setTickStep(2);
  customPlot->setupFullAxesBox();
    ui->customPlot->legend->setVisible(true);
  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
timePoint=QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  // setup a timer that repeatedly calls GraphWindow::realtimeDataSlot:
  //connect(graphAircraft, SIGNAL(serverDataReady(QList<int>)), this, SLOT(realtimeT10Slot(QList<int>)));
  //connect(&realRealtimeDataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  //realRealtimeDataTimer.start(0); // Interval 0 means to refresh as fast as possible
}
void GraphWindow::setupParametricCurveDemo(QCustomPlot *customPlot)
{
  demoName = "Parametric Curves Demo";

  customPlot->setInteraction(QCustomPlot::iSelectPlottables);

  // create empty curve objects and add them to customPlot:
  QCPCurve *fermatSpiral1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  QCPCurve *fermatSpiral2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  QCPCurve *deltoidRadial = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  customPlot->addPlottable(fermatSpiral1);
  customPlot->addPlottable(fermatSpiral2);
  customPlot->addPlottable(deltoidRadial);
  // generate the curve data points:
  int pointCount = 500;
  QVector<double> x1(pointCount), y1(pointCount);
  QVector<double> x2(pointCount), y2(pointCount);
  QVector<double> x3(pointCount), y3(pointCount);
  for (int i=0; i<pointCount; ++i)
  {
    double phi = (i/(double)(pointCount-1))*8*M_PI;
    x1[i] = sqrt(phi)*cos(phi);
    y1[i] = sqrt(phi)*sin(phi);
    x2[i] = -x1[i];
    y2[i] = -y1[i];
    double t = i/(double)(pointCount-1)*2*M_PI;
    x3[i] = 2*cos(2*t)+cos(1*t)+2*sin(t);
    y3[i] = 2*sin(2*t)-sin(1*t);
  }
  // pass the data to the curves:
  fermatSpiral1->setData(x1, y1);
  fermatSpiral2->setData(x2, y2);
  deltoidRadial->setData(x3, y3);
  // color the curves:
  fermatSpiral1->setPen(QPen(Qt::blue));
  fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
  fermatSpiral2->setPen(QPen(QColor(255, 120, 0)));
  fermatSpiral2->setBrush(QBrush(QColor(255, 120, 0, 30)));
  QRadialGradient radialGrad(QPointF(310, 180), 200);
  radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
  radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
  radialGrad.setColorAt(1,QColor(120, 20, 240, 10));
  deltoidRadial->setPen(QPen(QColor(170, 20, 240)));
  deltoidRadial->setBrush(QBrush(radialGrad));
  // set some basic customPlot config:
  customPlot->setRangeDrag(Qt::Horizontal | Qt::Vertical);
  customPlot->setRangeZoom(Qt::Horizontal | Qt::Vertical);
  customPlot->setupFullAxesBox();
  customPlot->rescaleAxes();
}

void GraphWindow::setupBarChartDemo(QCustomPlot *customPlot)
{
  demoName = "Bar Chart Demo";
  // create empty bar chart objects:
  QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *nuclear = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  customPlot->addPlottable(regen);
  customPlot->addPlottable(nuclear);
  customPlot->addPlottable(fossil);
  // set names and colors:
  QPen pen;
  pen.setWidthF(1.2);
  fossil->setName("Fossil fuels");
  pen.setColor(QColor(255, 131, 0));
  fossil->setPen(pen);
  fossil->setBrush(QBrush(QColor(255, 131, 0, 50)));
  nuclear->setName("Nuclear");
  pen.setColor(QColor(1, 92, 191));
  nuclear->setPen(pen);
  nuclear->setBrush(QBrush(QColor(1, 92, 191, 50)));
  regen->setName("Regenerative");
  pen.setColor(QColor(150, 222, 0));
  regen->setPen(pen);
  regen->setBrush(QBrush(QColor(150, 222, 0, 70)));
  // stack bars ontop of eachother:
  nuclear->moveAbove(fossil);
  regen->moveAbove(nuclear);

  // prepare x axis with country labels:
  QVector<double> ticks;
  QVector<QString> labels;
  ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
  labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
  customPlot->xAxis->setAutoTicks(false);
  customPlot->xAxis->setAutoTickLabels(false);
  customPlot->xAxis->setTickVector(&ticks, true);
  customPlot->xAxis->setTickVectorLabels(&labels, true);
  customPlot->xAxis->setTickLabelRotation(60);
  customPlot->xAxis->setSubTickCount(0);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setGrid(false);
  customPlot->xAxis->setRange(0, 8);

  // prepare y axis:
  customPlot->yAxis->setRange(0, 12.1);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
  customPlot->yAxis->setSubGrid(true);
  QPen gridPen;
  gridPen.setStyle(Qt::SolidLine);
  gridPen.setColor(QColor(0, 0, 0, 25));
  customPlot->yAxis->setGridPen(gridPen);
  gridPen.setStyle(Qt::DotLine);
  customPlot->yAxis->setSubGridPen(gridPen);

  // Add data:
  QVector<double> fossilData, nuclearData, regenData;
  fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
  nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
  regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
  fossil->setData(ticks, fossilData);
  nuclear->setData(ticks, nuclearData);
  regen->setData(ticks, regenData);

  // setup legend:
  customPlot->legend->setVisible(true);
  customPlot->legend->setPositionStyle(QCPLegend::psTop);
  customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 200)));
  QPen legendPen;
  legendPen.setJoinStyle(Qt::RoundJoin);
  legendPen.setColor(QColor(130, 130, 130, 200));
  customPlot->legend->setBorderPen(legendPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  customPlot->legend->setFont(legendFont);

  customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
  customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);

}

void GraphWindow::setupStatisticalDemo(QCustomPlot *customPlot)
{
  demoName = "Statistical Demo";
  // create empty statistical box plottables:
  QCPStatisticalBox *sample1 = new QCPStatisticalBox(customPlot->xAxis, customPlot->yAxis);
  QCPStatisticalBox *sample2 = new QCPStatisticalBox(customPlot->xAxis, customPlot->yAxis);
  QCPStatisticalBox *sample3 = new QCPStatisticalBox(customPlot->xAxis, customPlot->yAxis);
  customPlot->addPlottable(sample1);
  customPlot->addPlottable(sample2);
  customPlot->addPlottable(sample3);
  QBrush boxBrush(QColor(60, 60, 255, 100));
  boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
  sample1->setBrush(boxBrush);
  sample2->setBrush(boxBrush);
  sample3->setBrush(boxBrush);

  // set data:
  sample1->setKey(1);
  sample1->setMinimum(1.1);
  sample1->setLowerQuartile(1.9);
  sample1->setMedian(2.25);
  sample1->setUpperQuartile(2.7);
  sample1->setMaximum(4.2);

  sample2->setKey(2);
  sample2->setMinimum(0.8);
  sample2->setLowerQuartile(1.6);
  sample2->setMedian(2.2);
  sample2->setUpperQuartile(3.2);
  sample2->setMaximum(4.9);
  sample2->setOutliers(QVector<double>() << 0.7 << 0.39 << 0.45 << 6.2 << 5.84);

  sample3->setKey(3);
  sample3->setMinimum(0.2);
  sample3->setLowerQuartile(0.7);
  sample3->setMedian(1.1);
  sample3->setUpperQuartile(1.6);
  sample3->setMaximum(2.9);

  // prepare manual x axis labels:
  customPlot->xAxis->setSubTickCount(0);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setTickLabelRotation(20);
  customPlot->xAxis->setAutoTicks(false);
  customPlot->xAxis->setAutoTickLabels(false);
  QVector<double> ticks;
  QVector<QString> labels;
  ticks << 1 << 2 << 3;
  labels << "Sample 1" << "Sample 2" << "Control Group";
  customPlot->xAxis->setTickVector(&ticks, true);
  customPlot->xAxis->setTickVectorLabels(&labels, true);

  // prepare axes:
  customPlot->yAxis->setLabel(QString::fromUtf8("O₂ Absorption [mg]"));
  customPlot->rescaleAxes();
  customPlot->xAxis->scaleRange(1.7, customPlot->xAxis->range().center());
  customPlot->yAxis->setRange(0, 7);
  customPlot->setRangeDrag(Qt::Horizontal|Qt::Vertical);
  customPlot->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void GraphWindow::realtimeDataSlot()
{
  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
  double value0 = sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
  double value1 = sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
  // add data to lines:
  ui->customPlot->graph(0)->addData(key, value0);
  ui->customPlot->graph(1)->addData(key, value1);
  // set data of dots:
  ui->customPlot->graph(2)->clearData();
  ui->customPlot->graph(2)->addData(key, value0);
  ui->customPlot->graph(3)->clearData();
  ui->customPlot->graph(3)->addData(key, value1);
  // remove data of lines that's outside visible range:
  ui->customPlot->graph(0)->removeDataBefore(key-8);
  ui->customPlot->graph(1)->removeDataBefore(key-8);
  // rescale value (vertical) axis to fit the current data:
  ui->customPlot->graph(0)->rescaleValueAxis();
  ui->customPlot->graph(1)->rescaleValueAxis(true);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);

  ui->customPlot->replot();

  // calculate frames per second:
  static double lastSec;
  static int frameCount;
  ++frameCount;
  if (key-lastSec > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastSec), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
          , 0);
    lastSec = key;
    frameCount = 0;
  }
}

void GraphWindow::realtimeT10Slot(QList<int> indata)
{
    // calculate two new data points:
  #if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
  #else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

  #endif
int n=ui->tableGraphics->count();
    QVector<double> value;
    QMap<int, QString> ::iterator it=currentgraphMap.begin();
    for(;it!=currentgraphMap.end();++it)
    {
        value.append((float)indata[it.key()]);

    }

// add data to lines:
    for (int i=0;i<n;i++)
    {
    ui->customPlot->graph(i)->addData(key, value[i]);
    // remove data of lines that's outside visible range:
    ui->customPlot->graph(i)->removeDataBefore(key-8);

    }
    for (int i=n;i<2*n;i++)
    {
    // set data of dots:
    ui->customPlot->graph(i)->clearData();
    ui->customPlot->graph(i)->addData(key, value[i-n]);
//ui->customPlot->legend->removeItem(i);
    }
    // rescale value (vertical) axis to fit the current data:
    ui->customPlot->rescaleAxes();
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);

//    ui->customPlot->legend->setVisible(true);
    ui->customPlot->replot();
    if (addTime)
    { // data saved to file
        emit readyToSaveData(value);
  time.append(key-timePoint);

}

       // calculate frames per second:
    static double lastSec;
    static int frameCount;
    int pointsCount=0;
    for(int i=0; i<ui->customPlot->graphCount();++i)
    {
    pointsCount+=ui->customPlot->graph(i)->data()->count();

    }

    ++frameCount;
    if (key-lastSec > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastSec), 0, 'f', 0)
            .arg(pointsCount)
            , 0);
      lastSec = key;
      frameCount = 0;
    }

}

void GraphWindow::setupPlayground(QCustomPlot *customPlot)
{
  Q_UNUSED(customPlot)
  /*
  QVector<double> keys(20);
  QVector<double> values(20);
  for (int i=0; i<keys.size(); ++i)
  {
    keys[i] = i*0.5; // 500 msecs per step
    values[i] = sin(i*0.2);
  }
  customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  customPlot->xAxis->setDateTimeFormat("hh:mm:ss.zzz");
  customPlot->xAxis->setTickLabelRotation(45);
  customPlot->addGraph();
  customPlot->graph(0)->setData(keys, values);
  customPlot->rescaleAxes();
  customPlot->replot();
  */
}

GraphWindow::~GraphWindow()
{
  delete ui;
}

void GraphWindow::screenShot()
{
    screenShotCount++;
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+5, this->y(), this->frameGeometry().width()-10, this->frameGeometry().height()-5);
  QString fileName = QString::number(screenShotCount)+"_qcustomplot-"+demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  //qApp->quit();

  // ui->customPlot->savePng("./outsave.png");
  // ui->customPlot->savePdf("./outsave.pdf", true);
}

void GraphWindow::allScreenShots()
{
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+5, this->y(), this->frameGeometry().width()-10, this->frameGeometry().height()-5);
  QString fileName = "qcustomplot-"+demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);

  if (currentDemoIndex < 13)
  {
    if (realRealtimeDataTimer.isActive())
      realRealtimeDataTimer.stop();
    delete ui->customPlot;
    //ui->customPlot = new QCustomPlot(ui->centralWidget);
    ui->verticalLayout->addWidget(ui->customPlot);
    setupDemo(currentDemoIndex+1);
    int delay = 100;
    if (demoName == "Real Time Data Demo")
      delay = 5000; // realtime demo needs more time to develop proper look
    QTimer::singleShot(delay, this, SLOT(allScreenShots()));
  } else
  {
    qApp->quit();
  }
}

void GraphWindow::slotSaveData(QVector<double> aVectorData)
{

    for (int i=0;i<dataVector.size();++i)
    {
        dataVector[i].append(aVectorData.value(i));
            }

}

void GraphWindow::on_actionWriteDataToFile_toggled(bool arg1)
{
    if(arg1)
    {
        time.clear();
        addTime=true;
        connect(this,SIGNAL(readyToSaveData(QVector<double>)),this,SLOT(slotSaveData(QVector<double>)));

    }
    else
    {
    disconnect(this,SIGNAL(readyToSaveData(QVector<double>)),this,SLOT(slotSaveData(QVector<double>)));
    ui->actionSave_to_File->setEnabled(true);
addTime=false;
dataVector.append(time);
dataList.append(dataVector);
currentGraphMapList.append(currentgraphMap);
//dataVector.clear();
//currentgraphMap.clear();
    }

}


void GraphWindow::on_actionShot_triggered()
{
    this->screenShot();

}

Qt::GlobalColor GraphWindow::getColor(int kind)
{
    switch (kind)
    {
    case 0:
    {
    return Qt::blue;
    break;
    }
    case 1:
    {
    return Qt::red;
    break;
    }
    case 2:
    {
    return Qt::green;
    break;
    }
    case 3:
    {
    return Qt::cyan;
    break;
    }
    case 4:
    {
    return Qt::gray;
    break;
    }
    case 5:
    {
    return Qt::magenta;
    break;
    }
    case 6:
    {
    return Qt::yellow;
    break;
    }

    default:
    {
    return Qt::black;
    break;
    }

    }

}

void GraphWindow::on_pb_add_clicked()
{
    bool unique=true;
    for(int i=0;i<ui->tableGraphics->count();i++)
    {
        if(ui->cb_data->currentText()==ui->tableGraphics->itemAt(i,0)->text())
            unique=false;
    }
    if (unique)
    {
    ui->tableGraphics->addItem(ui->cb_data->currentText());
    currentgraphMap[ui->cb_data->currentIndex()]=graphMap[ui->cb_data->currentIndex()];
    }
}


void GraphWindow::on_actionStart_toggled(bool arg1)
{
     ui->customPlot->clearGraphs();

    if (arg1)
    {
        if(ui->tableGraphics->count()>0)
        {
        ui->actionPause->setEnabled(true);
        ui->actionStart->setEnabled(false);
        ui->actionWriteDataToFile->setEnabled(true);
        setupDemo(14);
        connect(graphAircraft, SIGNAL(serverDataReady(QList<int>)), this, SLOT(realtimeT10Slot(QList<int>)));
        ui->pb_add->setEnabled(false);
        }
        else ui->actionStart->setChecked(false);

    }
    else
    {
      ui->pb_add->setEnabled(true);
       disconnect(graphAircraft, SIGNAL(serverDataReady(QList<int>)), this, SLOT(realtimeT10Slot(QList<int>)));
              ui->actionPause->setEnabled(false);
         ui->actionStart->setEnabled(true);
         if(ui->tableGraphics->count()>0)
         {
         ui->actionWriteDataToFile->setEnabled(false);
        // ui->actionWriteDataToFile->setChecked(false);
         }
    }
}

void GraphWindow::on_actionPause_triggered()
{
    ui->actionPause->setEnabled(false);
    ui->actionStart->setChecked(false);
}



void GraphWindow::on_pb_remove_clicked()
{



    ui->tableGraphics->model()->removeRow(ui->tableGraphics->currentRow());
    ui->tableGraphics->repaint();
    ui->pb_remove->setEnabled(false);
    ui->pb_add->setEnabled(true);
    ui->tableGraphics->clearSelection();
}


void GraphWindow::on_tableGraphics_itemClicked(QListWidgetItem *item)
{
    ui->pb_remove->setEnabled(true);
    ui->pb_add->setEnabled(false);
}
//void GraphWindow::closeEvent(QCloseEvent *event)
//{
//    event->accept();
//    on_actionPause_triggered();
//    emit windowClosed(false);
//}

/**
 * This function is used to save the current data of the simulation in different formats, such as:.txt;.png;.pdf; etc,
 *
 */
//void GraphsWindow::saveFile()
//{
//    int numRobots = robotGroup->actions().size();
//    if (numRobots <= 0) {
//        QMessageBox::warning(this, tr("Save"), tr("There are no robots in the scene"), QMessageBox::Ok);
//        return;
//    }

//    robotList->clear();
//    // robotList->addItem("All");       Future Implementation
//    for(int i = 0; i < numRobots; i++)
//        robotList->addItem("Robot " + QString::number(i+1));

//    QFileDialog *dialog = new QFileDialog(this);
//    dialog->setAcceptMode(QFileDialog::AcceptSave);
//    QStringList filters;
//    filters << ".MAT-files (*.mat)"
//            << "CSV (comma-separate) (*.csv)"
//            << "Text Document (*.txt)"
//            << "Adobe PDF files (Current view) (*.pdf)"
//            << "PNG file - Portable Network Graphics (Current view) (*.png)";
//    dialog->setNameFilters(filters);
//    QLayout *layout = dialog->layout();
//    QGridLayout *gridbox = qobject_cast<QGridLayout*>(layout);
//    if (gridbox) {
//        gridbox->addWidget(new QLabel("Select Robot:"));
//        gridbox->addWidget(robotList);
//    }
//    dialog->setLayout(gridbox);
//    dialog->setOption(QFileDialog::DontUseNativeDialog);
//    connect(dialog, SIGNAL(filterSelected(QString)), this, SLOT(saveFilterChanged(QString)));

//    if (!dialog->exec())
//        return;

//    QString fileName = dialog->selectedFiles().first();
//    int selectedExtension = filters.indexOf(dialog->selectedNameFilter());
//    int selectedRobot = robotList->currentIndex();
//    int l= fileName.length();

//    QString tmp = "Robot" + QString::number(selectedRobot + 1);
//    QString tmp1, tmp2;
//    QList<QString> varNames;
//    varNames.push_back(tmp + "Posx");
//    varNames.push_back(tmp + "Posy");
//    varNames.push_back(tmp + "Velx");
//    varNames.push_back(tmp + "Vely");
//    bool btmp;

//    switch (selectedExtension) {
//    case 0:             // .MAT-files (*.mat)
//        if (!((fileName[l-4]=='.')&&(fileName[l-3]=='m')&&(fileName[l-2]=='a')&&(fileName[l-1]=='t')))
//            fileName += ".mat";
//        btmp = Writer::Save2MAT(fileName , &robotsDataList[selectedRobot], &varNames);
//        break;
//    case 1:             // CSV (comma-separate) (*.csv)
//        if (!((fileName[l-4]=='.')&&(fileName[l-3]=='c')&&(fileName[l-2]=='s')&&(fileName[l-1]=='v')))
//            fileName += ".csv";
//        btmp = Writer::Save2CSV(fileName , &robotsDataList[selectedRobot], &varNames);
//        break;
//    case 2:             // Text Document (*.txt)
//        if (!((fileName[l-4]=='.')&&(fileName[l-3]=='t')&&(fileName[l-2]=='x')&&(fileName[l-1]=='t')))
//            fileName += ".txt";
//        btmp = Writer::Save2TXT(fileName , &robotsDataList[selectedRobot], &varNames);
//        break;
//    case 3:             // Adobe PDF files (Current view) (*.pdf)
//        if ((fileName[l-4]=='.')&&(fileName[l-3]=='p')&&(fileName[l-2]=='d')&&(fileName[l-1]=='f'))
//            fileName.remove(l-4, 4);
//        tmp1 = fileName + " (position).pdf";
//        plotPosition->savePdf(tmp1);
//        tmp2 = fileName + " (velocity).pdf";
//        plotVelocity->savePdf(tmp2);
//        break;
//    case 4:             // PNG file - Portable Network Graphics (Current view) (*.png)
//        if ((fileName[l-4]=='.')&&(fileName[l-3]=='p')&&(fileName[l-2]=='n')&&(fileName[l-1]=='g'))
//            fileName.remove(l-4, 4);
//        tmp1 = fileName + " (position).png";
//        plotPosition->savePng(tmp1);
//        tmp2 = fileName + " (velocity).png";
//        plotVelocity->savePng(tmp2);
//        break;
//    }

//}

///**
// * This function is used to determine the selected filter of a file.
// *
// *@param filter The selected filter of a file
// */
//void GraphsWindow::saveFilterChanged(const QString &filter)
//{
//    QStringList filters;
//    filters << ".MAT-files (*.mat)"
//            << "CSV (comma-separate) (*.csv)"
//            << "Text Document (*.txt)"
//            << "Adobe PDF files (Current view) (*.pdf)"
//            << "PNG file - Portable Network Graphics (Current view) (*.png)";
//    int selectedExtension = filters.indexOf(filter);
//    switch (selectedExtension) {
//    case 0:             // .MAT-files (*.mat)
//        robotList->setEnabled(true);
//        break;
//    case 1:             // CSV (comma-separate) (*.csv)
//        robotList->setEnabled(true);
//        break;
//    case 2:             // Text Document (*.txt)
//        robotList->setEnabled(true);
//        break;
//    case 3:             // Adobe PDF files (Current view) (*.pdf)
//        robotList->setDisabled(true);
//        break;
//    case 4:             // PNG file - Portable Network Graphics (Current view) (*.png)
//        robotList->setDisabled(true);
//        break;
//    }
//}

void GraphWindow::on_actionSave_to_File_triggered()
{
                if (currentGraphMapList.isEmpty()) {
            QMessageBox::warning(this, tr("Save"), tr("There are no graphics added"), QMessageBox::Ok);
            return;
        }

        QFileDialog *dialog = new QFileDialog(this);
        dialog->setAcceptMode(QFileDialog::AcceptSave);
        currentgraphList=new QComboBox(dialog);
                currentgraphList->clear();
                QList<QString> buf;
                QString bufStr;
                for (int i=0;i<currentGraphMapList.size();++i)
                {
                    bufStr=QString::number(i+1)+". "+currentGraphMapList[i].value(0);

                    buf.append(bufStr);
                }
                currentgraphList->addItems(buf);
        QStringList filters;
        filters << ".MAT-files (*.mat)"
                << "CSV (comma-separate) (*.csv)"
                << "Text Document (*.txt)"
                << "Adobe PDF files (Current view) (*.pdf)"
                << "PNG file - Portable Network Graphics (Current view) (*.png)";
        dialog->setNameFilters(filters);
        QLayout *layout = dialog->layout();
        QGridLayout *gridbox = qobject_cast<QGridLayout*>(layout);
        if (gridbox) {
            gridbox->addWidget(new QLabel("Exp number:"));
            gridbox->addWidget(currentgraphList);
        }
        dialog->setLayout(gridbox);
        dialog->setOption(QFileDialog::DontUseNativeDialog);
        //connect(dialog, SIGNAL(filterSelected(QString)), this, SLOT(saveFilterChanged(QString)));

        if (!dialog->exec())
            return;

        QString fileName = dialog->selectedFiles().first();
        int selectedExtension = filters.indexOf(dialog->selectedNameFilter());
        int selecteddata = currentgraphList->currentIndex();
        int l= fileName.length();

        QString tmp = "Robot" + QString::number(selecteddata + 1);
        QString tmp1, tmp2;
        QList<QString> varNames=currentGraphMapList[currentgraphList->currentIndex()].values();
        varNames.append("time");

           bool btmp;

        switch (selectedExtension) {
        case 0:             // .MAT-files (*.mat)
            if (!((fileName[l-4]=='.')&&(fileName[l-3]=='m')&&(fileName[l-2]=='a')&&(fileName[l-1]=='t')))
                fileName += ".mat";
            btmp = Writer::Save2MAT(fileName , &dataList[currentgraphList->currentIndex()], &varNames);
        break;
        case 1:             // CSV (comma-separate) (*.csv)
            if (!((fileName[l-4]=='.')&&(fileName[l-3]=='c')&&(fileName[l-2]=='s')&&(fileName[l-1]=='v')))
                fileName += ".csv";
            btmp = Writer::Save2CSV(fileName , &dataList[currentgraphList->currentIndex()], &varNames);
            break;
        case 2:             // Text Document (*.txt)
            if (!((fileName[l-4]=='.')&&(fileName[l-3]=='t')&&(fileName[l-2]=='x')&&(fileName[l-1]=='t')))
                fileName += ".txt";
            btmp = Writer::Save2TXT(fileName , &dataList[currentgraphList->currentIndex()], &varNames);
            break;
        case 3:             // Adobe PDF files (Current view) (*.pdf)
            if ((fileName[l-4]=='.')&&(fileName[l-3]=='p')&&(fileName[l-2]=='d')&&(fileName[l-1]=='f'))
                fileName.remove(l-4, 4);
            tmp1 = fileName + " (position).pdf";

            ui->customPlot->savePdf(tmp);
            //tmp2 = fileName + " (velocity).pdf";
            //plotVelocity->savePdf(tmp2);
            break;
        case 4:             // PNG file - Portable Network Graphics (Current view) (*.png)
            if ((fileName[l-4]=='.')&&(fileName[l-3]=='p')&&(fileName[l-2]=='n')&&(fileName[l-1]=='g'))
                fileName.remove(l-4, 4);
            tmp1 = fileName + " (position).png";
            ui->customPlot->savePng(tmp1);
//            tmp2 = fileName + " (velocity).png";
//            plotVelocity->savePng(tmp2);
            break;
                   }

}
/**
 * This function is used to determine the selected filter of a file.
 *
 *@param filter The selected filter of a file
 */
void GraphWindow::saveFilterChanged(const QString &filter)
{
    QStringList filters;
    filters << ".MAT-files (*.mat)"
            << "CSV (comma-separate) (*.csv)"
            << "Text Document (*.txt)"
            << "Adobe PDF files (Current view) (*.pdf)"
            << "PNG file - Portable Network Graphics (Current view) (*.png)";
    int selectedExtension = filters.indexOf(filter);
    switch (selectedExtension) {
    case 0:             // .MAT-files (*.mat)
        currentgraphList->setEnabled(true);
        break;
    case 1:             // CSV (comma-separate) (*.csv)
        currentgraphList->setEnabled(true);
        break;
    case 2:             // Text Document (*.txt)
        currentgraphList->setEnabled(true);
        break;
    case 3:             // Adobe PDF files (Current view) (*.pdf)
        currentgraphList->setDisabled(true);
        break;
    case 4:             // PNG file - Portable Network Graphics (Current view) (*.png)
        currentgraphList->setDisabled(true);
        break;
    }
}

