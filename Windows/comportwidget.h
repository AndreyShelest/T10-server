#ifndef COMPORTWIDGET_H
#define COMPORTWIDGET_H

#include <QtGui>
#include <ComPort/comporttransmitter.h>


class ComPortWidget : public QWidget
{
    Q_OBJECT
private:
ComPortTransmitter* comPort;
public:
    explicit ComPortWidget(QWidget *parent = 0);
QLabel * labelComPortStatus;
signals:
void comPortConnected(bool active);
void comPortError();
public slots:
void comPortNotResponding();
void comPortRepaired();
void slot_turnOnComPort(bool arg1);
};

#endif // COMPORTWIDGET_H
