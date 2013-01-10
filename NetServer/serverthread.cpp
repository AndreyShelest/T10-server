#include "serverthread.h"

ServerThread::ServerThread(int socketDescriptor, QObject *parent) :
    QThread(parent),
    tcpServerConnection(0),
    socketDescriptor(socketDescriptor)
{
    lineEnd = '\n';
}

ServerThread::~ServerThread()
{
   this->exit(0);
}

void ServerThread::run()
{
    tcpServerConnection = new TcpSocket;
    if (!tcpServerConnection->setSocketDescriptor(socketDescriptor))
    {
        qDebug() << tr("Unable to set socket descriptor...");
        return;
    }
    else{
    peerInfo.id = socketDescriptor;
    peerInfo.name = "Unnamed";
    peerInfo.address = tcpServerConnection->peerAddress();
    peerInfo.port = tcpServerConnection->peerPort();
    peerInfo.packets_received=0;
    peerInfo.packets_send=0;
    peerInfo.dataMode = DataModes(undefined);
    peerInfo.pThread = this;


    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(incomingData_slot()));
    connect(tcpServerConnection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpServerConnection, SIGNAL(disconnected()), tcpServerConnection, SLOT(deleteLater()));
    connect(this, SIGNAL(write(QByteArray)), tcpServerConnection, SLOT(onWrite(QByteArray)));

    emit peerConnected(&peerInfo);

   exec();
    }
//    tcpServerConnection->disconnectFromHost();
//    delete tcpServerConnection;
//    tcpServerConnection = 0;
}

void ServerThread::send(QByteArray msg)
{
    emit write(msg); // send to child
}

void ServerThread::floatArr2ByteArr(QList<float> *floatArr, QByteArray *byteArr)
{
    const quint8 floatSize = sizeof(float);
    floatArr->clear();
    char* c;
    for (int i = 0; i < byteArr->size()/floatSize; i++)
        floatArr->append(0);
    c = (char*)&floatArr->first();
    int i = 0;
    while (i < byteArr->size())
    {
        *c = byteArr->at(i);
        i++;
        c++;
    }

}

void ServerThread::incomingData_slot()
{
    QByteArray msg = tcpServerConnection->readAll();
    peerInfo.packets_received++;
    emit incomingMessage(&peerInfo, msg);
}

void ServerThread::disconnected()
{

    emit peerDisconnected(&peerInfo);
    this->deleteLater();
}

void ServerThread::SendMessage(QByteArray msg)
{
    send(msg);
    peerInfo.packets_send++;
}

void ServerThread::DataReady(QList<float> msg)
{

    switch (this->peerInfo.dataMode)
    {
        case DataModes(matlab):
        {
            QByteArray s;
            s.clear();
            for (int i = 0; i < msg.size(); i++)
            {
                s.clear();
                s.append(QString::number((float)msg.at(i)));
                         s.append(10);

                      //   qDebug()<<s;
                send(s);

            }

            break;
        }
        case DataModes(raw):
        {
            QByteArray packet;
            packet.clear();
            floatArr2ByteArr(&msg, &packet);
            send(packet);
//            QList<float> list;
//            ByteArr2FloatArr(&packet, &list);
//            qDebug() << list;
            break;
        }
        case DataModes(filtered):
        {
            break;
        }
        case DataModes(visualisation_programm):
        {
                break;
        }
        case DataModes(web_browser):
        {
            break;
        }
        case DataModes(undefined):
        {
            break;
        }
    }
}
