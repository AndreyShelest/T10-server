#ifndef MIKROHTTPSERVER_H
#define MIKROHTTPSERVER_H

#include <QStringList>
#include <QFile>
#include <QDebug>

class MikroHttpServer
{
public:
    MikroHttpServer();

    QByteArray request(QByteArray r);

private:
    QString htmlDir;
    QString replyHeaders;
    QString requestedFile;

    QString getContentType(QString fileName);
    QByteArray getFile(QString fileName);
    QByteArray errorNotFound(QString fileName);

    QByteArray reply;
};

#endif // MIKROHTTPSERVER_H
