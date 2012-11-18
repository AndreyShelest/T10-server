#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QTime>
#include <QLabel>
#include <QMessageBox>
#include "NetServer/netserver.h"
#include "ComPort/comporttransmitter.h"
#include "Aircraft/aircraft.h"
#include "Joystick/v_joystick_adapter.h"
#include "datacontainer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionServer_toggled(bool arg1);
    void on_actionCom_port_toggled(bool arg1);

    void on_dataFromComPort(QByteArray data);
    void peerConnected(PeerInfo *peerInfo);
    void peerDisconnected(PeerInfo *peerInfo);
    void peerNameChanged(PeerInfo* peerInfo, QString oldName);

    void on_actionShowDataFromCom_toggled(bool arg1);
    void comPortNotResponding();
    void comPortRepaired();



    void on_stackedWidget_currentChanged(int arg1);

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_horizontalSlider_sliderMoved(int position);

    void on_actionJoystick_toggled(bool arg1);
    void repositionOnSidebar();

    void on_actionSettings_triggered(bool checked);

    void on_pushButton_comPortReconnect_clicked();
    void showDataToCom(QByteArray dataToMc);


    void on_pBsimulate_clicked();

public slots:
    void log(QString data);

private:
    Ui::MainWindow *ui;
    QLabel* labelServerStatus;
    QLabel* labelComPortStatus;
    QLabel* labelJoystickStatus;
            NetServer* server;
    ComPortTransmitter* comPort;
    DataContainer* dataContainer;
    Aircraft* aircraft;
    VJoystickAdapter* joystick;

    void rebuildPeerList(PeerInfo* pinfo, bool disconnected = false, bool renamed = false);
};

#endif // MAINWINDOW_H




