#include "netserver.h"

NetServer::NetServer(QObject *parent) :
    QTcpServer(parent)
{
    peers.clear();
    comPortDataIndexes.clear();

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

//    settings.beginGroup("NetServer/dataIndexes/fromComPort");
//    settings.setValue("pitch_suspension", 1);
//    settings.endGroup();

    httpServer = new MikroHttpServer();
}

NetServer::~NetServer()
{
    delete httpServer;
}

void NetServer::incomingConnection(int socketDescriptor)
{
    ServerThread* thread = new ServerThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(peerConnected(PeerInfo*)), this, SLOT(peerConnected_slot(PeerInfo*)));
    connect(thread, SIGNAL(peerDisconnected(PeerInfo*)), this, SLOT(peerDisconnected_slot(PeerInfo*)));
     connect(thread, SIGNAL(incomingMessage(PeerInfo*,QByteArray)), this, SLOT(incomingMessage_slot(PeerInfo*,QByteArray)));

       thread->start();
}

void NetServer::peerConnected_slot(PeerInfo *peerInfo)
{
    peers.append(peerInfo);
    qDebug() << tr("New connection: ") << peerInfo->id << " ::: "  << peerInfo->address;
    connect(this, SIGNAL(toThreadsCustomDataReady(QList<float>)), peerInfo->pThread, SLOT(DataReady(QList<float>)));
    emit peerConnected(peerInfo);
}

void NetServer::peerDisconnected_slot(PeerInfo *peerInfo)
{

    qDebug() << tr("Disconnected: ") << peerInfo->id << " ::: "  << peerInfo->address;
        int n = peers.indexOf(peerInfo);
    if (n != -1)
    {
         // peers.at(n)->pThread->deleteLater();

            peers.removeAt(n);
            disconnect(this, SIGNAL(toThreadsDataReady(QList<float>)),
                       peerInfo->pThread, SLOT(DataReady(QList<float>)));
            disconnect(this, SIGNAL(toThreadsCustomDataReady(QList<float>)),
                       peerInfo->pThread, SLOT(DataReady(QList<float>)));
              emit peerDisconnected(peerInfo);
emit peerDisconnected(peerInfo);
    }


}

void NetServer::incomingMessage_slot(PeerInfo *peerInfo, QByteArray msg)
{
    if (msg.startsWith("GET"))              // Http запрос
    {
        peerInfo->dataMode = DataModes(web_browser);
        peerInfo->pThread->SendMessage(httpServer->request(msg));
        return;
    }

    QString s = msg;
    qDebug() << s;
    QStringList sl = s.split('\n');

    for (int i = 0; i < sl.count(); i++)
    {
        QString s = sl[i];
        if (s.indexOf("My name is: ") == 0)
        {
            s = s.remove(0, 12);
            if (s[s.length()-1] == '\n')
                s = s.remove(s.length()-1, 1);
            if (s[s.length()-1] == '\r')
                s = s.remove(s.length()-1, 1);

            QString oldname = peerInfo->name;
            peerInfo->name = s;
            peerInfo->pThread->SendMessage("OK. Your name changed.\n");
            emit peerNameChanged(peerInfo, oldname);
        } else

            if (s.startsWith("Start data transfer"))
            {
  connect(this, SIGNAL(toThreadsDataReady(QList<float>)), peerInfo->pThread, SLOT(DataReady(QList<float>)));
            } else
{
                if (s.startsWith("Set data mode: "))
                {
                    s = s.remove(0, 15);
                    if (s[s.length()-1] == '\n')
                        s = s.remove(s.length()-1, 1);
                    if (s[s.length()-1] == '\r')
                        s = s.remove(s.length()-1, 1);
                    if (s == "raw")
                    {
                        peerInfo->dataMode = DataModes(raw);
                        peerInfo->pThread->SendMessage("OK. Data mode: raw\n");
                    }
                    else if (s == "visualisation_programm")
                    {
                        peerInfo->dataMode = DataModes(matlab);
                        peerInfo->pThread->SendMessage("OK. Data mode: visualisation_programm\n");
                        //qDebug()<<"Подключено";
                    }
                    else if (s == "filtered")
                    {
                        peerInfo->dataMode = DataModes(filtered);
                        peerInfo->pThread->SendMessage("OK. Data mode: filtered\n");
                    }
                    else if (s == "undefined")
                    {
                        peerInfo->dataMode = DataModes(undefined);
                        peerInfo->pThread->SendMessage("OK. Data mode: undefined\n");
                    }
                    else if (s == "matlab")
                    {
                        peerInfo->dataMode = DataModes(matlab);
                        peerInfo->pThread->SendMessage("OK. Data mode: matlab\n");
                    }
                    else
                    {
                        peerInfo->dataMode = DataModes(undefined);
                        peerInfo->pThread->SendMessage("FAIL. Unknown data mode\n");
                    }
                }
            }
        if (s.startsWith("Get: "))
        {
            s=s.remove(0,5);
            QStringList datalist = s.split(",");
           QList<int> dataNumbers;
            foreach (QString st,datalist)
            {
            dataNumbers.append(st.toInt());
            }
//            QString str="you request "+QString::number(dataNumbers.size())+"\n";

//            peerInfo->pThread->SendMessage(str.toAscii());

            emit getServerData(dataNumbers);

        }
        if (s.startsWith("BYE"))
        {
            disconnect(this, SIGNAL(toThreadsDataReady(QList<float>)),
                       peerInfo->pThread, SLOT(DataReady(QList<float>)));
            disconnect(this, SIGNAL(toThreadsCustomDataReady(QList<float>)),
                       peerInfo->pThread, SLOT(DataReady(QList<float>)));
              emit peerDisconnected(peerInfo);
        }
    }
}

void NetServer::setServerData(QList<int> indata)
{
    QList<float> lData;
    foreach(int i,indata){
        lData.append((float)i);

    }
//qDebug()<<lData;
  clientData=lData;
  emit toThreadsDataReady(lData);

}

void NetServer::setCustomServerData(QList<int> indata)
{
    QList<float> lData;
    foreach(int i,indata){
        lData.append((float)i);

    }
  clientData=lData;
  emit toThreadsCustomDataReady(lData);
}


