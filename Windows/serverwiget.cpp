#include "serverwiget.h"

ServerWiget::ServerWiget(QWidget *parent) :
    QWidget(parent)
{
    qDebug()<<"Server Widget created";
    server=new NetServer();
     port = 1988;
    peers=new PeerWidget();
    m_grLayout=new QGridLayout(this);
    listWidget_peerList =new QListWidget();
    listWidget_Log=new QListWidget();

    peer_count=new QLCDNumber();
    peer_count->setSegmentStyle(QLCDNumber::Filled);

    m_hbLayout=new QHBoxLayout();
    m_hbLayout->addWidget(new QLabel("<span style=\"color:#0f615b;\">" + tr("Clients:") + "</span>"),Qt::AlignLeft);
    m_hbLayout->addStretch(50);
    m_hbLayout->addWidget(peer_count,Qt::AlignRight);
    server_Parameters=new QWidget();
    sp_gboxLayout=new QGridLayout();
     sp_gboxLayout->addWidget(new QLabel("<span style=\"color:#31cd69;\">" + tr("Server Info:") + "</span>"),0,0,1,2,Qt::AlignCenter);
    sp_gboxLayout->addLayout(m_hbLayout,1,0,1,2,Qt::AlignCenter);
    labelServerIP=new QLabel("<span style=\"color:#2343b3;\">" + getServerIP(2) + "</span>");
     labelServerIP2=new QLabel("<span style=\"color:#2343b3;\">" + getServerIP(4) + "</span>");
    sp_gboxLayout->addWidget(new QLabel("<span style=\"color:#0f615b;\">" + tr("Server IP:") + "</span>"),2,0,2,1,Qt::AlignLeft);
    sp_gboxLayout->addWidget(labelServerIP,2,1 ,Qt::AlignRight);
    sp_gboxLayout->addWidget(labelServerIP2,3,1 ,Qt::AlignRight);
        sp_gboxLayout->addWidget(new QLabel("<span style=\"color:#0f615b;\">" + tr("Port:") + "</span>"),4,0,1,1,Qt::AlignLeft);
    labelServerPort=new QLabel ("<span style=\"color:#2343b3;\">" + QString::number(port) + "</span>");
    sp_gboxLayout->addWidget(labelServerPort,4,1 ,Qt::AlignRight);
    UpdateServerInfo=new QPushButton("&Update info");
       sp_gboxLayout->addWidget(UpdateServerInfo,5,0,1,3,Qt::AlignCenter);
    sp_gboxLayout->setColumnStretch(1,2.0);
    server_Parameters->setLayout(sp_gboxLayout);
    m_grLayout->addWidget(listWidget_peerList,0,0,1,1,Qt::AlignLeft);
    m_grLayout->setColumnStretch(0,1);
    m_grLayout->setRowStretch(0,3.0);
    m_grLayout->setRowStretch(1,1);
    m_grLayout->addWidget(peers,0,1,1,1);
    m_grLayout->addWidget(listWidget_Log,1,1,1,1);
    m_grLayout->addWidget(server_Parameters,1,0);
    m_grLayout->setColumnStretch(1,4);
    labelServerStatus=new QLabel(tr("Server: ") + "<span style=\"color:#000088;\">" + tr("stopped") + "</span>");
    connect(UpdateServerInfo,SIGNAL(clicked()),this,SLOT(updateServerInfo()));
    connect(listWidget_peerList,SIGNAL(clicked(QModelIndex)),this,SLOT(on_listWidget_peerList_clicked(QModelIndex)));
       this->setLayout(m_grLayout);
}

ServerWiget::~ServerWiget()
{
    delete server_Parameters;
    delete listWidget_Log;
    delete listWidget_peerList;
    delete server;
    delete peers;
    qDebug()<<"Server Widget deleted";

}

NetServer *ServerWiget::getServer()
{
    return server;
}

int ServerWiget::getPeersCount()
{
    return peer_count->value();
}

QString ServerWiget::getServerIP(int num)
{
    QString locIP;
     QList<QHostAddress> addr = QNetworkInterface::allAddresses();
//     for (int i=0;i<addr.size();i++)
//     {
//            locIP = addr.at(i).toString();
//     qDebug()<<locIP;
//     }

     locIP = addr.at(num).toString();
     return locIP;

}

void ServerWiget::log(QString data)
{
    listWidget_Log->addItem(QTime::currentTime().toString("HH:mm:ss").append(" -> ") + data);
    listWidget_Log->scrollToBottom();

}

void ServerWiget::turnOnServer(Aircraft *aircraft, bool activate)
{
    if (activate)
    {

        connect(aircraft,SIGNAL(serverDataReady(QList<float>)),
                server,SLOT(setServerData(QList<float>)));
        connect(server,SIGNAL(getServerData(QList<int>)),
                aircraft,SLOT(setCustomServerData(QList<int>)));
        connect(aircraft,SIGNAL(serverCustomDataReady(QList<float>)),
                server,SLOT(setCustomServerData(QList<float>)));

        qDebug()<<"Server connected with modeling";


    }
    else
    {
        disconnect(aircraft,SIGNAL(serverDataReady(QList<float>)),
                   server,SLOT(setServerData(QList<float>)));
        disconnect(server,SIGNAL(getServerData(QList<int>)),
                   aircraft,SLOT(setCustomServerData(QList<int>)));
        disconnect(aircraft,SIGNAL(serverCustomDataReady(QList<float>)),
                   server,SLOT(setCustomServerData(QList<float>)));

        qDebug()<<"Server disconnected";
    }
}


void ServerWiget::slotConnectServer(bool arg)
{
    if (arg){

        QHostAddress addr("0.0.0.0");
        //settings.value("NetServer/address", "0.0.0.0").toString());

        //settings.value("NetServer/port", 1988).toInt();

        if (server->listen(addr, port))
        {
            this->log(tr("Server started") + " [" + addr.toString() + ":" + QString::number(port) + "]");

            connect(server, SIGNAL(peerConnected(PeerInfo*)), this, SLOT(peerConnected(PeerInfo*)));
            connect(server, SIGNAL(peerDisconnected(PeerInfo*)), this, SLOT(peerDisconnected(PeerInfo*)));
            connect(server, SIGNAL(peerNameChanged(PeerInfo*,QString)), this, SLOT(peerNameChanged(PeerInfo*,QString)));
            connect(server, SIGNAL(peerConnected(PeerInfo*)), peers, SLOT(updateData(PeerInfo*)));
            labelServerStatus->setText(tr("Server: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("running") + "</span>");
        }
        else
        {
            this->log(tr("Unable to start server: ") + server->errorString());

            server->close();
            emit serverError(false);


        }
    }
    else
    {
        disconnect(server, SIGNAL(peerDisconnected(PeerInfo*)), this, SLOT(peerDisconnected(PeerInfo*)));
        disconnect(server, SIGNAL(peerNameChanged(PeerInfo*,QString)), this, SLOT(peerNameChanged(PeerInfo*,QString)));
        disconnect(server, SIGNAL(peerConnected(PeerInfo*)), this, SLOT(peerConnected(PeerInfo*)));
        disconnect(server, SIGNAL(peerConnected(PeerInfo*)), peers, SLOT(updateData(PeerInfo*)));
        server->close();

        this->log(tr("Server stopped"));
        labelServerStatus->setText(tr("Server: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("stopped") + "</span>");
    }
}

void ServerWiget::updateServerInfo()
{
    labelServerIP->setText("<span style=\"color:#2343b3;\">" + getServerIP(2) + "</span>");
     labelServerIP2->setText("<span style=\"color:#2343b3;\">" + getServerIP(4) + "</span>");
     labelServerPort->setText("<span style=\"color:#2343b3;\">" + QString::number(port) + "</span>");
//qDebug()<<QString::number(port);
}

void ServerWiget::rebuildPeerList(PeerInfo *pinfo, bool disconnected, bool renamed)
{
    peer_count->display(server->peers.count());
    listWidget_peerList->clear();
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
        listWidget_peerList->addItem(lwi);
    }
    if (disconnected)
    {
        lwi = new QListWidgetItem(pinfo->name + " [" + pinfo->address.toString() + "]");
        lwi->setForeground(QBrush(Qt::gray));
        listWidget_peerList->addItem(lwi);
    }
}

void ServerWiget::peerConnected(PeerInfo *peerInfo)
{
    log(tr("Client connected") + ": " + peerInfo->name + " [" + peerInfo->address.toString() + "]");
    rebuildPeerList(peerInfo);
    on_listWidget_peerList_clicked(listWidget_peerList->indexAt(QPoint(
                                                                    listWidget_peerList->count(),1)));
}

void ServerWiget::peerDisconnected(PeerInfo *peerInfo)
{
    log(peerInfo->name + " " + tr("disconnected") + "... (");
    rebuildPeerList(peerInfo, true);
}

void ServerWiget::peerNameChanged(PeerInfo *peerInfo, QString oldName)
{
    rebuildPeerList(peerInfo, false, true);
}

void ServerWiget::on_listWidget_peerList_clicked(const QModelIndex &index)
{
    if (index.row()<=server->peers.size()-1)
    {
        peers->updateData(server->peers[index.row()]);
        //обновляются данные о выбраном пользователе
        connect(server->peers[index.row()]->pThread,SIGNAL(peerConnected(PeerInfo*))
                ,peers,SLOT(updateData(PeerInfo*)));
        connect(server,SIGNAL(peerNameChanged(PeerInfo*,QString))
                ,peers,SLOT(updateData(PeerInfo*)));
        connect(server->peers[index.row()]->pThread,SIGNAL(incomingMessage(PeerInfo*,QByteArray))
                ,peers,SLOT(updateData(PeerInfo*)));
    }
}
