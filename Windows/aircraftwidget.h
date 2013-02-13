#ifndef AIRCRAFTWIDGET_H
#define AIRCRAFTWIDGET_H

#include <QtGui>

#include <Aircraft/aircraft.h>

class AircraftWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout * m_grLayout;
   //QComboBox * cmbxJoy;
    Aircraft * aircraft;
    QStringList JoyList;
    QSettings * settings;
public:
    explicit AircraftWidget(QWidget *parent = 0);
    Aircraft * getAircraft();
    ~AircraftWidget();
signals:
    
public slots:
    void slotSimulate(bool arg);
};

#endif // AIRCRAFTWIDGET_H
