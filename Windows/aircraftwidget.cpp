#include "aircraftwidget.h"

AircraftWidget::AircraftWidget(QWidget *parent) :
    QWidget(parent)
{
    m_grLayout=new QGridLayout();
    aircraft=new Aircraft(this);
    this->setLayout(m_grLayout);
}

Aircraft *AircraftWidget::getAircraft()
{
    return aircraft;
}

AircraftWidget::~AircraftWidget()
{
    qDebug()<<"AircraftWgt deleted";
}

void AircraftWidget::slotSimulate(bool arg)
{
    if (arg)
    {
        aircraft->startSimulation();
        qDebug()<<"simulation started";
            }
    else
    {
        aircraft->stopSimulation();
        qDebug()<<"simulation stoped";

    }
}
