#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QHostAddress>
#include "tcpsocket.h"
#include"ComPort/comporttransmitter.h"

class ServerThread;

enum DataModes
{
    undefined,
    raw,
    filtered,
    matlab,
    visualisation_programm,
    web_browser
};

struct PeerInfo
{
    quint16 id;
    QString name;
    ServerThread* pThread;
    QHostAddress address;
    quint16 port;
    DataModes dataMode;
    QList<float*> dataComponents;
};


class ServerThread : public QThread
{
    Q_OBJECT
public:
    ServerThread(int socketDescriptor, QObject *parent = 0);
    ~ServerThread();

protected:
    void run();
    void send(QByteArray msg);

private:
    TcpSocket * tcpServerConnection;
    int socketDescriptor;
    PeerInfo peerInfo;
    QByteArray packet;
    QString lineEnd;

    void floatArr2ByteArr(QList<float>* floatArr, QByteArray* byteArr);
    
signals:
    void incomingMessage(PeerInfo* peer_info, QByteArray msg);
    void peerConnected(PeerInfo* peer_info);
    void peerDisconnected(PeerInfo* peer_info);
    void write(QByteArray msg);
    
protected slots:
    void incomingData_slot();
    void disconnected();

public slots:
    void SendMessage(QByteArray msg);
    void DataReady(QList<float> msg);
};

#endif // SERVERTHREAD_H
