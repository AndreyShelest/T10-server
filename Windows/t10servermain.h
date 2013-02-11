#ifndef T10SERVERMAIN_H
#define T10SERVERMAIN_H

//#include <QMainWindow>
#include <QFile>
#include <QCoreApplication>
#include <QtGui>
#include <Windows/serverwiget.h>
class T10ServerMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit T10ServerMain(QWidget *parent = 0);
    ~T10ServerMain();


    bool loadSettings(QSettings * _settings);
    void writeSettings();
private:
    QGridLayout * gMainLayout;
    QWidget * cntrlWgt;
    QTabWidget * main_tab_wgt;
    QSettings * settings;
    QList<bool> * activeTabs;
    QToolBar * iconsToolBar;
    QStatusBar * main_statusbar;
    QAction * actionComPort;
    QAction * actionAircraft;
    QAction * actionServer;
    QAction * actionJoystick;
    ServerWiget * serverWgt;
    void createMenuAndToolBar();
    bool createTabs ();
    bool activeComPort,activeJoy,activeAircraft,activeServer;
    void closeEvent(QCloseEvent *e);
signals:
    
public slots:
    void slotServerActionToggled(bool arg);
    void slotComPortActionToggled(bool arg);
    void slotAircraftActionToggled(bool arg);
    void slotJoystickActionToggled(bool arg);
};

#endif // T10SERVERMAIN_H
