#ifndef SERVERWIGET_H
#define SERVERWIGET_H

#include <QWidget>
#include <NetServer/netserver.h>
#include <NetServer/peerwidget.h>
class ServerWiget : public QWidget
{
    Q_OBJECT
private:
     NetServer* server;
     PeerWidget* peers;
     QGridLayout * m_grLayout;
     QLCDNumber * peer_count;
     QListWidget * listWidget_peerList;
     QListWidget * listWidget_Log;
     quint16 port;
public:
    explicit ServerWiget(QWidget *parent = 0);
     ~ServerWiget();
     QLabel* labelServerStatus;
signals:
    

public slots:
     void rebuildPeerList(PeerInfo *pinfo, bool disconnected=0, bool renamed=0);
     void peerConnected(PeerInfo *peerInfo);
     void peerDisconnected(PeerInfo *peerInfo);
     void peerNameChanged(PeerInfo* peerInfo, QString oldName);
     void on_listWidget_peerList_clicked(const QModelIndex &index);
     void log(QString data);
     void slotConnectServer(bool arg);
};

#endif // SERVERWIGET_H
