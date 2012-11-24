#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/resources/qss/green.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
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

    server = new NetServer();
    if (settings.value("NetServer/autostart", true).toBool())
        ui->actionServer->setChecked(true);

    comPort = new ComPortTransmitter(this);
    connect(comPort, SIGNAL(Zavislo()), this, SLOT(comPortNotResponding()));
    connect(comPort, SIGNAL(Otvislo()), this, SLOT(comPortRepaired()));
    if (settings.value("ComPort/autoConnect", "").toBool())
    { ui->actionCom_port->setChecked(true);
        ui->pushButton_comPortReconnect->setEnabled(true);
    }
    else ui->pushButton_comPortReconnect->setEnabled(true);

    joystick = new VJoystickAdapter();
    if (settings.value("Joystick/autoConnect", true).toBool()){
        ui->actionJoystick->setChecked(true);
    }
    connect(comPort,SIGNAL(dataTransmitedToCom(QByteArray)),this,SLOT(showDataToCom(QByteArray)));
    if (joystick->isConnected()) ui->pb_joy_refresh->click();

    this->set_transmit_mode('d');
    ui->PPN_wgt->setHidden(!ui->tb_custom_pp->isChecked());

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
          buf.append(QString::number((unsigned char)dataToMc[i])+", ");

        }

        ui->list_toCom->addItem(buf);

        ui->list_toCom->scrollToBottom();
    }

}

void MainWindow::on_pBsimulate_clicked()
{
    connect(comPort,SIGNAL(dataTransmitedToCom(QByteArray)),server,SLOT(dataFromJoystic(QByteArray)));
}


void MainWindow::on_pb_joy_refresh_clicked()
{
    QStringList joyList=joystick->getAvaliableJoystickName();
    if (joyList.count()>0){
        for (int i=0;i<joyList.count();i++)
        {
            ui->cb_joycticks->setItemText(i,joyList[i]);
        }
    }
    else ui->cb_joycticks->setItemText(0,"no joysticks");

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("Joystick/name", ui->cb_joycticks->itemText(ui->cb_joycticks->currentIndex()));
}



void MainWindow::on_list_toCom_itemClicked(QListWidgetItem *item)
{
    QStringList ListToCom=item->text().split(", ");
    ui->lbl_con_byte->setText(ListToCom[0]);
    QStandardItemModel model(ui->table_toCom->rowCount(),ui->table_toCom->columnCount());
    int n=0;
    for (int i=0;i<3;i++)
    {
        for (int j=0;j<3;j++)
        {
            ui->table_toCom->model()->setData(model.index(j,i),ListToCom[n+1]);
            n++;
        }
    }
}

void MainWindow::set_transmit_mode(char com)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    if (ui->tb_data_on->isChecked())
    {ui->tb_data_on_Joy->setChecked(false);}
    switch (com)
    {
    case 'd':// only data
    {
        ui->tb_data_on->setEnabled(true);
        ui->tb_data_on->setChecked(true);
         ui->tb_data_on_Joy->setEnabled(false);
         ui->tb_data_on_Joy->setChecked(false);
        ui->tb_data_rau_joy->setEnabled(false);
        ui->tb_data_rau_joy->setChecked(false);
             ui->tb_custom_on->setEnabled(false);
              ui->tb_custom_on->setChecked(false);
              ui->tb_custom_pp->setChecked(false);
              ui->tb_custom_rau->setChecked(false);
              settings.setValue("ComPort/Mode", com);
                   comPort->setControlByte(com);
         break;
    }
    case 'j': // data and joy
    {
        ui->tb_data_on_Joy->setEnabled(true);
        ui->tb_data_on_Joy->setChecked(true);
         ui->tb_data_on->setEnabled(false);
          ui->tb_data_on->setChecked(false);
          ui->tb_data_rau_joy->setEnabled(false);
          ui->tb_data_rau_joy->setChecked(false);
               ui->tb_custom_on->setEnabled(false);
                ui->tb_custom_on->setChecked(false);
                ui->tb_custom_pp->setChecked(false);
                ui->tb_custom_rau->setChecked(false);
                settings.setValue("ComPort/Mode",com);
                 comPort->setControlByte(com);
        break;
    }
    case 'c':// control rau by joy
    {
        ui->tb_data_rau_joy->setEnabled(true);
        ui->tb_data_rau_joy->setChecked(true);
         ui->tb_data_on_Joy->setEnabled(false);
         ui->tb_data_on_Joy->setChecked(false);
        ui->tb_data_on->setEnabled(false);
        ui->tb_data_on->setChecked(false);
             ui->tb_custom_on->setEnabled(false);
              ui->tb_custom_on->setChecked(false);
              ui->tb_custom_pp->setChecked(false);
              ui->tb_custom_rau->setChecked(false);
              settings.setValue("ComPort/Mode", com);

              comPort->setControlByte(com);
        break;
    }
    case 'r':// custom rau and ppn control
    {
        ui->tb_custom_on->setEnabled(true);
        ui->tb_custom_on->setChecked(true);
         ui->tb_data_on_Joy->setEnabled(false);
         ui->tb_data_on_Joy->setChecked(false);
        ui->tb_data_rau_joy->setEnabled(false);
        ui->tb_data_rau_joy->setChecked(false);
             ui->tb_data_on->setEnabled(false);
              ui->tb_data_on->setChecked(false);
                   comPort->setControlByte(com);
                   ui->tb_custom_pp->setEnabled(true);
                   ui->tb_custom_rau->setEnabled(true);
                    settings.setValue("ComPort/Mode", com);
        break;
    }

    default:
    {
        ui->tb_data_on->setEnabled(true);
        ui->tb_data_on->setChecked(false);
         ui->tb_data_on_Joy->setEnabled(true);
         ui->tb_data_on_Joy->setChecked(false);
        ui->tb_data_rau_joy->setEnabled(true);
        ui->tb_data_rau_joy->setChecked(false);
             ui->tb_custom_on->setEnabled(true);
              ui->tb_custom_on->setChecked(false);
                                           ui->tb_custom_pp->setEnabled(false);
                                           ui->tb_custom_rau->setEnabled(false);
                                           ui->tb_custom_pp->setChecked(false);
                                           ui->tb_custom_rau->setChecked(false);
                                           ui->tb_custom_pp->setChecked(false);
                                           ui->tb_custom_rau->setChecked(false);
                                            ui->PPN_wgt->setHidden(true);
                   comPort->setControlByte(com);
        break;
    }
    }


}


void MainWindow::on_tb_data_on_clicked(bool checked)
{

}

void MainWindow::on_tb_data_on_toggled(bool checked)
{
    if (checked)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());
this->set_transmit_mode('d');
        settings.setValue("ComPort/Mode", 'd');

    }
    else {
        this->set_transmit_mode('q');}
}

void MainWindow::on_tb_data_rau_joy_toggled(bool checked)
{
    if (checked)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());
this->set_transmit_mode('c');
        settings.setValue("ComPort/Mode", 'c');

    }
    else {
        this->set_transmit_mode('q');}
}

void MainWindow::on_tb_data_on_Joy_toggled(bool checked)
{
    if (checked)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());
this->set_transmit_mode('j');
        settings.setValue("ComPort/Mode", 'j');

    }
    else {
        this->set_transmit_mode('q');}
}

void MainWindow::on_tb_custom_on_toggled(bool checked)
{
    if (checked)
    {
        QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                           QCoreApplication::organizationName(), QCoreApplication::applicationName());
this->set_transmit_mode('r');
        settings.setValue("ComPort/Mode", 'r');

    }
    else {
        this->set_transmit_mode('q');}
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->list_toCom->clear();
}


void MainWindow::on_listWidgetSettings_clicked(const QModelIndex &index)
{

    ui->stackedWidgetServerSettings->setCurrentIndex(index.row());
}

void MainWindow::on_tb_custom_pp_clicked(bool checked)
{
    ui->PPN_wgt->setHidden(!checked);
    if (checked)
    {
        connect(ui->ppn_rudder,SIGNAL(valueChanged(int)),comPort,SLOT(setCustomPPNr(int)));
        connect(ui->ppn_ailerons,SIGNAL(valueChanged(int)),comPort,SLOT(setCustomPPNa(int)));
                connect(ui->ppn_stab,SIGNAL(valueChanged(int)),comPort,SLOT(setCustomPPNs(int)));
    }
    else {
    ui->ppn_rudder->setValue(127);
    ui->ppn_ailerons->setValue(127);
    ui->ppn_stab->setValue(127);
    }
}




