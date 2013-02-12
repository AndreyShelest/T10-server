#include "mikrohttpserver.h"

MikroHttpServer::MikroHttpServer()
{
    htmlDir = ":/resources/html/for_net_server";

    replyHeaders.clear();
    replyHeaders.append("HTTP/1.1 {HTTP_CODE}\r\n");
    replyHeaders.append("Server: T10_Server\r\n");
    replyHeaders.append("Content-Type: {CONTENT_TYPE}\r\n");
    replyHeaders.append("Content-Length: {CONTENT_LENGTH}\r\n");
    replyHeaders.append("Connection: close\r\n");
    replyHeaders.append("\r\n");

    //text/html; charset=utf-8
    //
}

QByteArray MikroHttpServer::request(QByteArray r)
{
    qDebug() << " ";
    qDebug() << "Http request:";
    qDebug() << "=================";
    qDebug() << r;
    reply.clear();
    QString s(r);
    QStringList req = s.split('\n');
    QStringList request = req.at(0).split(" ");

    requestedFile = request.at(1);

    if (requestedFile == "/")
        requestedFile = htmlDir + "/index.html";
    else
        requestedFile = htmlDir + requestedFile;
    return getFile(requestedFile);
}

QString MikroHttpServer::getContentType(QString fileName)
{
    if (fileName.endsWith(".html", Qt::CaseInsensitive))
        return "text/html; charset=utf-8";
    else if (fileName.endsWith(".jpg", Qt::CaseInsensitive))
        return "image/jpeg";
    else if (fileName.endsWith(".css", Qt::CaseInsensitive))
        return "text/css";
    else

    return "Unknown";
}

QByteArray MikroHttpServer::getFile(QString fileName)
{
    QByteArray ba;
    QString temp;
    QByteArray r;
    r.clear();
    ba.clear();
    temp.clear();

    if (QFile::exists(fileName))
    {
        QFile f(fileName);
        if (!f.open(QFile::ReadOnly))
            return errorNotFound(fileName);
        ba = f.readAll();
    }
    else
    {
        return errorNotFound(fileName);
    }

    QString contentType = getContentType(fileName);

    temp = replyHeaders.replace("{HTTP_CODE}", "200 OK");
    temp = temp.replace("{CONTENT_TYPE}", contentType);
    temp = temp.replace("{CONTENT_LENGTH}", QString::number(ba.length()));
    r.append(temp);
    r.append(ba);

    qDebug() << " ";
    qDebug() << "Http reply:";
    qDebug() << "=================";
    qDebug() << r;

    return r;
}

QByteArray MikroHttpServer::errorNotFound(QString fileName)
{
    QByteArray ba;
    QString temp;
    QByteArray r;
    r.clear();
    ba.clear();

    QFile f(htmlDir + "/page.html");
    f.open(QFile::ReadOnly);
    ba = f.readAll();
    temp = replyHeaders.replace("{HTTP_CODE}", "404 Not Found");
    temp = temp.replace("{CONTENT_TYPE}", "text/html; charset=utf-8");
    temp = temp.replace("{CONTENT_LENGTH}", QString::number(ba.length()));
    r.append(temp);


    temp.clear();
    temp = ba.replace("{PAGE_CONTENT}", "<h1>Not found...</h1>");
    temp = temp.replace("{TITLE}", "Not found...");

    r.append(temp);

    qDebug() << " ";
    qDebug() << "Http reply:";
    qDebug() << "=================";
    qDebug() << r;

    return r;
}
