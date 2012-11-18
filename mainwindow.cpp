#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
       // ui->groupBox_comPort->hide();
        //ui->groupBox_joystick->hide();
       //ui->groupBox_netServer->hide();


    QFile file(":/resources/qss/green.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    //settings=new QSettings(QSettings::IniFormat, QSettings::UserScope,QCoreApplication::organizationName(), QCoreApplication::applicationName());
    this->setWindowTitle(QCoreApplication::applicationName());
    comPort = 0;

    labelServerStatus = new QLabel(tr("Server: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("stopped") + "</span>");
    labelComPortStatus = new QLabel(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not connected") + "</span>");
    labelJoystickStatus = new QLabel(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not connected") + "</span>");
    ui->statusBar->addPermanentWidget(labelServerStatus);
    ui->statusBar->addPermanentWidget(labelComPortStatus);
    ui->statusBar->addPermanentWidget(labelJoystickStatus);

    ui->actionSettings->setStatusTip(tr("Edit settings"));
    ui->actionServer->setStatusTip(tr("Start server"));
    ui->actionCom_port->setStatusTip(tr("Connect to COM port"));
    ui->actionJoystick->setStatusTip(tr("Connect to Joystick"));
    ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    qDebug() << "Settings file name: " << settings.fileName();

    aircraft = new Aircraft();
    //aircraft->startSimulation();

    server = new NetServer();
    if (settings.value("NetServer/autostart", true).toBool())
        ui->actionServer->setChecked(true);
   // dataContainer = new DataContainer();
    //connect(dataContainer, SIGNAL(DataReady(QList<float>)), server, SLOT(DataReady(QList<float>)));
    comPort = new ComPortTransmitter(this);
    connect(comPort, SIGNAL(Zavislo()), this, SLOT(comPortNotResponding()));
    connect(comPort, SIGNAL(Otvislo()), this, SLOT(comPortRepaired()));
    if (settings.value("ComPort/autoConnect", "").toBool())
       { ui->actionCom_port->setChecked(true);
ui->pushButton_comPortReconnect->setEnabled(true);
    }
    else ui->pushButton_comPortReconnect->setEnabled(true);

    joystick = new VJoystickAdapter();
    if (settings.value("Joystick/autoConnect", true).toBool())
        ui->actionJoystick->setChecked(true);
    connect(comPort,SIGNAL(dataTransmitedToCom(QByteArray)),this,SLOT(showDataToCom(QByteArray)));

//    ui->listWidget_Log->clear();
//    this->log(tr("Server started") + " [0.0.0.0:1989]");

//    this->log(tr("COM port: connected to COM8"));
//    labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("transferring") + "</span>");
    //    QListWidgetItem* lwi;
    //    lwi = new QListWidgetItem("Approximator [192.168.0.56]");
    //    ui->listWidget_peerList->addItem(lwi);
    //    lwi = new QListWidgetItem("Drozd [192.168.0.100]");
    //    ui->listWidget_peerList->addItem(lwi);
    //    ui->labelClientsConnected->setText("2");
}

MainWindow::~MainWindow()
{
    delete server;
    delete aircraft;
    delete ui;
    delete joystick;
}

void MainWindow::log(QString data)
{
    ui->listWidget_Log->addItem(QTime::currentTime().toString("HH:mm:ss").append(" -> ") + data);
    ui->listWidget_Log->scrollToBottom();
}

void MainWindow::rebuildPeerList(PeerInfo *pinfo, bool disconnected, bool renamed)
{
    ui->labelClientsConnected->setText(QString::number(server->peers.count()));
    ui->listWidget_peerList->clear();
    QListWidgetItem* lwi;
    foreach (PeerInfo* pi, server->peers)
    {
        lwi = new QListWidgetItem(pi->name + " [" + pi->address.toString() + "]");
        if (pinfo == pi)
        {
            if (!renamed)
                lwi->setForeground(QBrush(Qt::green));
            else
                lwi->setForeground(QBrush(QColor::fromRgb(0, 200, 200)));
        }
        ui->listWidget_peerList->addItem(lwi);
    }
    if (disconnected)
    {
        lwi = new QListWidgetItem(pinfo->name + " [" + pinfo->address.toString() + "]");
        lwi->setForeground(QBrush(Qt::gray));
        ui->listWidget_peerList->addItem(lwi);
    }
}

void MainWindow::on_actionServer_toggled(bool arg1)
{
    if (arg1)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                         QCoreApplication::organizationName(), QCoreApplication::applicationName());

        QHostAddress addr(settings.value("NetServer/address", "0.0.0.0").toString());
        quint16 port = settings.value("NetServer/port", 1988).toInt();

        if (server->listen(addr, port))
        {
            this->log(tr("Server started") + " [" + addr.toString() + ":" + QString::number(port) + "]");

            connect(server, SIGNAL(peerConnected(PeerInfo*)), this, SLOT(peerConnected(PeerInfo*)));
            connect(server, SIGNAL(peerDisconnected(PeerInfo*)), this, SLOT(peerDisconnected(PeerInfo*)));
            connect(server, SIGNAL(peerNameChanged(PeerInfo*,QString)), this, SLOT(peerNameChanged(PeerInfo*,QString)));

            ui->actionServer->setStatusTip(tr("Stop server"));
            ui->actionServer->setToolTip(ui->actionServer->statusTip());
            labelServerStatus->setText(tr("Server: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("running") + "</span>");
        }
        else
        {
            this->log(tr("Unable to start server: ") + server->errorString());
            ui->actionServer->setChecked(false);
            //ui->groupBox_netServer->show();
            this->repositionOnSidebar();
        }
    }
    else
    {
        server->close();
        this->log(tr("Server stopped"));
        ui->actionServer->setStatusTip(tr("Start server"));
        ui->actionServer->setToolTip(ui->actionServer->statusTip());
        labelServerStatus->setText(tr("Server: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("stopped") + "</span>");
    }
}

void MainWindow::on_actionJoystick_toggled(bool arg1)
{
    if (arg1)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                         QCoreApplication::organizationName(), QCoreApplication::applicationName());
        QStringList sl = VJoystickAdapter::getAvaliableJoystickName();

        qDebug() << "Available joysticks: ";
        qDebug() << sl;

        int m_joyId = -1;
        for (int i = 0; i < sl.count(); i++)
        {
            if (sl[i] == settings.value("Joystick/name", "").toString())
            {
                m_joyId = i;
                break;
            }
        }

        if((m_joyId > -1) && joystick->open(m_joyId))
        {

            labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("connected") + "</span>");

            connect(joystick, SIGNAL(sigXAxisChanged(int)), comPort, SLOT(slotJoyXChanged(int)));
            connect(joystick, SIGNAL(sigYAxisChanged(int)), comPort, SLOT(slotJoyYChanged(int)));
            connect(joystick, SIGNAL(sigZAxisChanged(int)), comPort, SLOT(slotJoyZChanged(int)));

            ui->actionJoystick->setStatusTip(tr("Disconnect from Joystick"));
            ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
            qDebug() << "Joystick connected: " << joystick->getJoystickName();
        }
        else
        {
            //ui->label_Joystick_status->setText("<font color=red>"+tr("Not connected")+"</font>");
            //labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to joystick") + "</span>");
            ui->actionJoystick->setChecked(false);
            //ui->groupBox_joystick->show();
            this->repositionOnSidebar();
            qDebug() << "Unable to connect to joystick: " << joystick->getJoystickName();
        }

    }
    else
    {
        if (!joystick->isConnected())
            labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to joystick") + "</span>");
        else
        {
            labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("disconnected") + "</span>");
            joystick->close();
        }
        ui->actionJoystick->setStatusTip(tr("Connect to Joystick"));
        ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
    }
}

void MainWindow::repositionOnSidebar()
{
    int y = 0;
    if (ui->groupBox_comPort->isVisible())
    {
        ui->groupBox_comPort->move(0, 0);
        y = y + ui->groupBox_comPort->height();
    }
    if (ui->groupBox_joystick->isVisible())
    {
        ui->groupBox_joystick->move(0, y);
        y = y + ui->groupBox_joystick->height();
    }
    if (ui->groupBox_netServer->isVisible())
    {
        ui->groupBox_netServer->move(0, y);
        y = y + ui->groupBox_netServer->height();
    }
}

void MainWindow::on_actionCom_port_toggled(bool arg1)
{
    if (arg1)
    {
        if (comPort->COM_reconnect())
        {
            ui->actionCom_port->setStatusTip(tr("Disconnect from COM port"));
            ui->actionCom_port->setToolTip(ui->actionCom_port->statusTip());
            this->log(tr("COM port: connected to ") + comPort->getDeviceName());
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("connected") + "</span>");
            ui->pushButton_comPortReconnect->setEnabled(true);
            //            connect(comPort, SIGNAL(Zavislo()), this, SLOT(comPortNotResponding()));
            //            connect(comPort, SIGNAL(Otvislo()), this, SLOT(comPortRepaired()));
        }
        else
        {

            //delete comPort;
            //comPort = 0;
            ui->actionCom_port->setChecked(false);
            //ui->groupBox_comPort->show();
            this->repositionOnSidebar();
        }

////        connect(trans, SIGNAL(DataReady(QByteArray)), dataContainer, SLOT(comPortDataReady(QByteArray)));
////        connect(dataContainer, SIGNAL(ready2com(QByteArray)), trans, SLOT(slot_Write(QByteArray)));

    }
    else
    {
        if (!comPort->COM_isConnected())
        {
            this->log(tr("COM port: unable to connect to ") + comPort->getDeviceName());
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to") + " " + comPort->getDeviceName() + "</span>");
        }
        else
        {
            this->log(tr("COM port: disconnected"));
            labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("disconnected") + "</span>");
        }
        comPort->COM_disconnect();
        ui->actionCom_port->setStatusTip(tr("Connect to COM port"));
        ui->actionCom_port->setToolTip(ui->actionCom_port->statusTip());
    }
}

void MainWindow::on_dataFromComPort(QByteArray data)
{

}

void MainWindow::peerConnected(PeerInfo *peerInfo)
{
    log(tr("Client connected") + ": " + peerInfo->name + " [" + peerInfo->address.toString() + "]");
    rebuildPeerList(peerInfo);
}

void MainWindow::peerDisconnected(PeerInfo *peerInfo)
{
    log(peerInfo->name + " " + tr("disconnected") + "... (");
    rebuildPeerList(peerInfo, true);
}

void MainWindow::peerNameChanged(PeerInfo *peerInfo, QString oldName)
{
    log(oldName +" " + tr("change his name to") + " " + peerInfo->name);
    rebuildPeerList(peerInfo, false, true);
}

void MainWindow::on_actionShowDataFromCom_toggled(bool arg1)
{
    if (arg1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::comPortNotResponding()
{
    labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not responding") + "</span>");
}

void MainWindow::comPortRepaired()
{
    labelComPortStatus->setText(tr("COM port: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("transferring") + "</span>");
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("T-10 Server"),
             tr("aboutme"));
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
//    QByteArray ba;
//    ba.clear();
//    ba.append((unsigned char)position);
//    ui->label_14->setText(QString::number(position));
//    comPort->setDataToMC(ba);
}




void MainWindow::on_actionSettings_triggered(bool checked)
{


}

void MainWindow::on_pushButton_comPortReconnect_clicked()
{
    ui->actionCom_port->setChecked(false);
QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                     QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("ComPort/name", ui->lineEditPort->text());
    ui->actionCom_port->setChecked(true);

}


void MainWindow::showDataToCom(QByteArray dataToMc)
{
   QString buf;
   if (comPort->COM_isConnected())
   {

    for(int i=0; i<dataToMc.size();i++)
    {
            buf+=QString::number((unsigned char)dataToMc[i])+", ";
    }
    ui->list_toCom->addItem(buf);

    ui->list_toCom->scrollToBottom();
   }

}

void MainWindow::on_pBsimulate_clicked()
{
    connect(comPort,SIGNAL(dataTransmitedToCom(QByteArray)),server,SLOT(dataFromJoystic(QByteArray)));
}

