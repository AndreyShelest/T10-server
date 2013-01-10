#ifndef NETSERVER_H
#define NETSERVER_H

#include <QTcpServer>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QCoreApplication>
#include <QHash>
#include <QSettings>
#include "serverthread.h"
#include "mikrohttpserver.h"

class NetServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit NetServer(QObject *parent = 0);
    ~NetServer();
    void incomingConnection(int socketDescriptor);
    QList<PeerInfo*> peers;

private:
    MikroHttpServer* httpServer;
QList<float> clientData;
    QHash<QString, quint8> comPortDataIndexes;
    
signals:
    void peerConnected(PeerInfo *peerInfo);
    void peerDisconnected(PeerInfo *peerInfo);
    void peerNameChanged(PeerInfo* peerInfo, QString oldName);
    void toThreadsDataReady(QList<float>);
    void toThreadsCustomDataReady(QList<float>);
    void getServerData (QList<int> dataNumber);

public slots:
   void peerConnected_slot(PeerInfo* peerInfo);
   void peerDisconnected_slot(PeerInfo* peerInfo);
   void incomingMessage_slot(PeerInfo* peerInfo, QByteArray msg);
   void setServerData (QList<int> indata);
   void setCustomServerData (QList<int> indata);


    
};

#endif // NETSERVER_H
