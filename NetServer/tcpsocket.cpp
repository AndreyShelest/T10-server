#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent) :
    QTcpSocket(parent)
{
}

void TcpSocket::onWrite(QByteArray msg)
{
    write(msg);
}
