#ifndef PEERWIDGET_H
#define PEERWIDGET_H

#include <QWidget>
#include <QtGui>
#include <NetServer/serverthread.h>

class PeerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PeerWidget(QWidget *parent = 0);
 private:
    QGridLayout *g_layout;
    QLabel* l_name;
    QLabel* peer_name;
    QLabel* l_IP;
    QLabel* peer_IP;
    QLabel* l_port;
    QLabel* peer_port;
    QLabel* l_received;
    QLabel* peer_received;
    QLabel* l_send;
    QLabel* peer_send;
    QLabel* l_dataMode;
    QLabel* peer_dataMode;
signals:
    
public slots:
    void updateData(PeerInfo * peerInfo);
};

#endif // PEERWIDGET_H
