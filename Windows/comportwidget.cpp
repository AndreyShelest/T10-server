#include "comportwidget.h"

ComPortWidget::ComPortWidget(QWidget *parent) :
    QWidget(parent)
{
    comPort = new ComPortTransmitter(this);
    labelComPortStatus=new QLabel(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not active") + "</span>");
    connect(comPort, SIGNAL(Zavislo()), this, SLOT(comPortNotResponding()));
    connect(comPort, SIGNAL(Otvislo()), this, SLOT(comPortRepaired()));
    comPort->setControlByte('d');
}

void ComPortWidget::slot_turnOnComPort(bool arg1)
{
    if (arg1)
    {
        if (comPort->COM_reconnect())
        {
        //   emit comPortConnected(true);
//           ui->actionCom_port->setStatusTip(tr("Disconnect from COM port"));
//           ui->actionCom_port->setToolTip(ui->actionCom_port->statusTip());
//            this->log(tr("COM port: connected to ") + comPort->getDeviceName());
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("connected") + "</span>");
            //ui->pushButton_comPortReconnect->setEnabled(true);
         //  connect(aircraft, SIGNAL(serverDataReady(QList<float>)), this, SLOT(showAircraftData(QList<float>)));

        }
        else
        {
emit comPortConnected(false);
                   //  ui->actionCom_port->setChecked(false);

        }

          }
    else
    {
        if (!comPort->COM_isConnected())
        {
           // this->log(tr("COM port: unable to connect to ") + comPort->getDeviceName());
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to") + " " + comPort->getDeviceName() + "</span>");
            emit comPortError();
        }
        else
        {
           // this->log(tr("COM port: disconnected"));
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("disconnected") + "</span>");
        emit comPortConnected(false);
        }
        comPort->COM_disconnect();
        //disconnect(aircraft, SIGNAL(serverDataReady(QList<float>)), this, SLOT(showAircraftData(QList<float>)));

//        ui->actionCom_port->setStatusTip(tr("Connect to COM port"));
//        ui->actionCom_port->setToolTip(ui->actionCom_port->statusTip());

    }

}
void ComPortWidget::comPortNotResponding()
{
    labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not responding") + "</span>");
}

void ComPortWidget::comPortRepaired()
{
    labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("transferring") + "</span>");
}

