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

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    T10ServerMain* appMainWindow=NULL;
    MainWindow* w=NULL;
    if (argv[1]!=NULL){
        if (!strcmp(argv[1],"--new-style")){
            appMainWindow=new T10ServerMain();
            appMainWindow->setWindowIcon(QIcon(":/resources/icons/appIcon.png"));
            appMainWindow->show();
        }
    } else {
        w=new MainWindow();
        w->show();
    }

        int ret= a.exec();
        if (w!=NULL)
            delete w;
        if (appMainWindow!=NULL)
            delete appMainWindow;
        return ret;

}
