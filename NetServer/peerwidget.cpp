#include "peerwidget.h"

PeerWidget::PeerWidget(QWidget *parent) :
    QWidget(parent)
{
    g_layout=new QGridLayout();
    l_name=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                      + tr("Name") + "</span>");
    peer_name=new QLabel("");
    l_IP=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                      + tr("IP adress") + "</span>");
    peer_IP=new QLabel(" ");
    l_port=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                      + tr("Port") + "</span>");
     peer_port=new QLabel("");
     l_received=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                       + tr("Received") + "</span>");
    peer_received=new QLabel("");
    l_send=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                      + tr("Send") + "</span>");
      peer_send=new QLabel("");
      l_dataMode=new QLabel("<span style=\"color:#52d4c0;font-weight:bold;\">"
                        + tr("Data mode") + "</span>");
        peer_dataMode=new QLabel("");
    g_layout->addWidget(l_name,0,0,1,1,Qt::AlignLeft);
    g_layout->addWidget(peer_name,0,1,1,1,Qt::AlignRight);
    g_layout->addWidget(l_IP,1,0,1,1,Qt::AlignLeft);
     g_layout->addWidget(peer_IP,1,1,1,1,Qt::AlignRight);
     g_layout->addWidget(l_port,2,0,1,1,Qt::AlignLeft);
     g_layout->addWidget(peer_port,2,1,1,1,Qt::AlignRight);
     g_layout->addWidget(l_received,3,0,1,1,Qt::AlignLeft);
     g_layout->addWidget(peer_received,3,1,1,1,Qt::AlignRight);
     g_layout->addWidget(l_send,4,0,1,1,Qt::AlignLeft);
     g_layout->addWidget(peer_send,4,1,1,1,Qt::AlignRight);
     //g_layout->addWidget(l_dataMode,5,0,1,1,Qt::AlignLeft);
     //g_layout->addWidget(peer_dataMode,5,1,1,1,Qt::AlignRight);

    this->setLayout(g_layout);
   // this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
     //this->setMaximumSize(1200,1200);
     //this->autoFillBackground();
    //this->show();
}

void PeerWidget::updateData(PeerInfo *peerInfo)
{
    peer_name->setText(peerInfo->name);
    peer_IP->setText(peerInfo->address.toString());
    peer_port->setText(QString::number(peerInfo->port));
    peer_received->setText(QString::number(peerInfo->packets_received));
    peer_send->setText(QString::number(peerInfo->packets_send));
    //peer_dataMode->setText(peerInfo->dataMode);
}
