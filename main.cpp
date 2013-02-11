#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"
#include "Windows/t10servermain.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(T10_Server3);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

    QCoreApplication::setOrganizationName("T10_Server");
    QCoreApplication::setOrganizationDomain("approximator.org");
    QCoreApplication::setApplicationName("T10_server");
    QCoreApplication::setApplicationVersion("4.0.0b");

    QApplication a(argc, argv);

    //    MainWindow w;
//    w.show();
    T10ServerMain appMainWindow;
    appMainWindow.setWindowIcon(QIcon(":/resources/icons/appIcon.png"));
    appMainWindow.show();
    return a.exec();
}
