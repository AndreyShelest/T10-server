#ifndef T10SERVERMAIN_H
#define T10SERVERMAIN_H


#include <QFile>
#include <QCoreApplication>
#include <QtGui>
#include <Windows/serverwiget.h>
#include <Windows/t10tray.h>
#include <Windows/joywidget.h>
#include <Windows/aircraftwidget.h>
#include "qCustomPlot/graphwindow.h"
#include <Windows/comportwidget.h>

class T10ServerMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit T10ServerMain(QWidget *parent = 0);
    ~T10ServerMain();

    bool loadSettings(QSettings * _settings);
    void writeSettings();

private:
    QString styleSheet;
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
    QAction * actionGraphs;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *messageAction;
    QAction *quitAction;
    ComPortWidget * comPortWGT;
    ServerWiget* serverWgt;
    JoyWidget *joyWgt;
    AircraftWidget *aircraftWgt;
    GraphWindow* graphWindow;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    void createMenuAndToolBar();
    void createTrayIcon();
    bool createTabs ();
    bool activeComPort,activeJoy,activeAircraft,activeServer;
    void closeEvent(QCloseEvent *e);
signals:

private slots:
    void slotMinimize();
    void slotRestore();
   // void setIcon(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    //void messageClicked();
    bool eventFilter(QObject *obj, QEvent *event);

public slots:
    void slotServerActionToggled(bool arg);
    void slotComPortActionToggled(bool arg);
    void slotAircraftActionToggled(bool arg);
    void slotJoystickActionToggled(bool arg);
    void slotGraphsActionToggled(bool arg);
};

#endif // T10SERVERMAIN_H
