#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include "ComPort/comporttransmitter.h"

const quint8 num_arrays = 50;
const quint8 num_data2com = 3;
const quint8 num_elems_in_arr = 10;
const quint8 com_port_packet_len = 32;

const quint8 DATA_FROM_COM_PORT = num_arrays - com_port_packet_len;

const quint8 JOYSTICK_X_AXIS = 0;
const quint8 JOYSTICK_Y_AXIS = 1;
const quint8 JOY3 = 2;
const quint8 HEADING = 3;
const quint8 SPEED = 4;
const quint8 SPEED_X = 5;
const quint8 SPEED_Y = 6;
const quint8 SPEED_Z = 7;
const quint8 X = 8;
const quint8 Y = 9;
const quint8 Z = 10;
const quint8 ACCELLERATION = 11;

const quint8 PITCH = 0 + DATA_FROM_COM_PORT;
const quint8 ROLL = 1 + DATA_FROM_COM_PORT;
const quint8 YAW = 2 + DATA_FROM_COM_PORT;
    //quint8 JOYSTICK_X_AXIS = 2;

// PITCH
const quint8 pitch_min_ed = 100;
const quint8 pitch_middle_ed = 127;
const quint8 pitch_max_ed = 135;
const quint8 pitch_amplitude_g = 15;

// ROLL
const quint8 roll_min_ed = 137;
const quint8 roll_middle_ed = 196;
const quint8 roll_max_ed = 247;
const quint8 roll_amplitude_g = 20;


class DataContainer : public QObject
{
    Q_OBJECT
public:
    explicit DataContainer(QObject *parent = 0);
    ~DataContainer();

private:
    int stage;
    int deltaW;
    int time_interval;
    QList<QQueue<float>*> data_arrays;

    QTimer* timer;
    QTimer* timer_uart;

    QList<float> data;
    QList<unsigned char> data2com;
    enum { MAX_JOYSTICK_BUTTONS = 30 };

    unsigned char pitch_z;
    unsigned char roll_z;
    unsigned char yaw_z;

    float InitH;

    void AddToArr(quint8 n, float d);
    void Save2File_from_com_port(QByteArray data);
    void Save2File(QList<float> data);
    void CalculateALL();

signals:
    void DataReady(QList<float>);
    void ready2com(QByteArray ba);

public slots:
    void joystickAxesChanged(int id, int state);
    void joystickButtonChanged(int id, int state);
    void comPortDataReady(QByteArray packet);
    void startSimulation();

private slots:
    void timeout();
    void timeout2com();
};

#endif // DATACONTAINER_H
