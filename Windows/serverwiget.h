#ifndef SERVERWIGET_H
#define SERVERWIGET_H

#include <QWidget>
#include <NetServer/netserver.h>
#include <NetServer/peerwidget.h>
#include <Aircraft/aircraft.h>
#include <QNetworkInterface>
//#include <Windows/t10servermain.h>
class ServerWiget : public QWidget
{
    Q_OBJECT
private:
     NetServer* server;
     PeerWidget* peers;
     QGridLayout * m_grLayout;
     QHBoxLayout * m_hbLayout;
     QLCDNumber * peer_count;
     QListWidget * listWidget_peerList;
     QListWidget * listWidget_Log;
     QWidget* server_Parameters;
     QGridLayout* sp_gboxLayout;
     QLabel* labelServerIP;
     QLabel* labelServerIP2;
     QLabel* labelServerPort;
     QPushButton* UpdateServerInfo;
     quint16 port;
public:
    explicit ServerWiget(QWidget *parent = 0);
     ~ServerWiget();
     QLabel* labelServerStatus;
     NetServer* getServer();
     int getPeersCount();
     QString getServerIP (int num);

signals:
     void serverError(bool);

public slots:
     void rebuildPeerList(PeerInfo *pinfo, bool disconnected=0, bool renamed=0);
     void peerConnected(PeerInfo *peerInfo);
     void peerDisconnected(PeerInfo *peerInfo);
     void peerNameChanged(PeerInfo* peerInfo, QString oldName);
     void on_listWidget_peerList_clicked(const QModelIndex &index);
     void log(QString data);
     void turnOnServer(Aircraft * aircraft, bool activate);
     void slotConnectServer(bool arg);
     void updateServerInfo();
};

#endif // SERVERWIGET_H
