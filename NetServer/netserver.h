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

    QHash<QString, quint8> comPortDataIndexes;
    
signals:
    void peerConnected(PeerInfo *peerInfo);
    void peerDisconnected(PeerInfo *peerInfo);
    void peerNameChanged(PeerInfo* peerInfo, QString oldName);
    void toThreadsDataReady(QList<float>);
    
public slots:
   void peerConnected_slot(PeerInfo* peerInfo);
   void peerDisconnected_slot(PeerInfo* peerInfo);
   void incomingMessage_slot(PeerInfo* peerInfo, QByteArray msg);
   //void dataReady(QList<float> data);
   void dataFromComPort(const QByteArray data);
   void dataFromJoystic(const QByteArray data);
    
};

#endif // NETSERVER_H
