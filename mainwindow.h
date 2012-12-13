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
#include "QListWidget"
#include "QStandardItemModel"
#include "qCustomPlot/qcustomplot.h"
#include "qCustomPlot/graphwidget.h"

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


    void peerConnected(PeerInfo *peerInfo);
    void peerDisconnected(PeerInfo *peerInfo);
    void peerNameChanged(PeerInfo* peerInfo, QString oldName);

    void on_actionShowDataFromCom_toggled(bool arg1);
    void comPortNotResponding();
    void comPortRepaired();



    void on_stackedWidget_currentChanged(int arg1);

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionJoystick_toggled(bool arg1);


    void on_actionSettings_triggered(bool checked);

    void on_pushButton_comPortReconnect_clicked();
    void showDataToCom(QByteArray dataToMc);
    void showAircraftData(QList<int> data);
    void on_pb_joy_refresh_clicked();


    void on_list_toCom_itemClicked(QListWidgetItem *item);
    void set_transmit_mode(char com);
    void on_tb_data_on_clicked(bool checked);

    void on_tb_data_on_toggled(bool checked);

    void on_tb_data_rau_joy_toggled(bool checked);

    void on_tb_data_on_Joy_toggled(bool checked);

    void on_tb_custom_on_toggled(bool checked);

    void on_pushButton_2_clicked();


    void on_listWidgetSettings_clicked(const QModelIndex &index);


    void on_aircraft_Simulate_triggered(bool checked);


    void on_tb_custom_rau_toggled(bool checked);

    void on_tb_custom_pp_toggled(bool checked);

    void on_pBsimulate_toggled(bool checked);

    void on_actionPlots_toggled(bool arg1);

public slots:
    void log(QString data);

private:
    Ui::MainWindow *ui;
    QLabel* labelServerStatus;
    QLabel* labelComPortStatus;
    QLabel* labelJoystickStatus;
    NetServer* server;

    ComPortTransmitter* comPort;
    Aircraft* aircraft;
    VJoystickAdapter* joystick;
    GraphWidget graphWindow;

    void rebuildPeerList(PeerInfo* pinfo, bool disconnected = false, bool renamed = false);
};

#endif // MAINWINDOW_H




