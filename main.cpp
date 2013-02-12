#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(T10_Server3);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    QCoreApplication::setOrganizationName("Approximator soft");
    QCoreApplication::setOrganizationDomain("approximator.org");
    QCoreApplication::setApplicationName("T10_server");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
