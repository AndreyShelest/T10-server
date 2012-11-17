#include "datacontainer.h"
#include <QTime>
#include <QtCore/qmath.h>

DataContainer::DataContainer(QObject *parent) :
    QObject(parent)
{
    deltaW = 10;
    time_interval = 100;
    stage = 0;
    pitch_z = 128;
    roll_z = 128;
    yaw_z = 128;
    InitH = 140;
    for (int i = 0; i < num_arrays; i++)
    {
        QQueue<float>* t = new QQueue<float>;
        data_arrays.append(t);
        for (int j = 0; j < num_elems_in_arr; j++)
            t->enqueue(0.0);
    }

//    data.clear();
//    for (int i = 0; i < num_arrays; i++)
//        data.append('\1');
//    data2com.clear();
//    for (int i = 0; i < num_data2com; i++)
//        data2com.append('\1');

//    data_arrays[HEADING]->clear();
//    for (int i = 0; i < num_elems_in_arr; i++)
//         data_arrays[HEADING]->append(InitH);
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
//    timer->start(time_interval);
//    timer_uart = new QTimer(this);
//    connect(timer_uart, SIGNAL(timeout()), this, SLOT(timeout2com()));
//    timer_uart->start(time_interval);

//    qsrand(QTime::currentTime().msec());
}

void DataContainer::startSimulation()
{
    stage = 1;
}

void DataContainer::timeout2com()
{
    /*if (data2com[0] == 1) data2com[0] = 0;
    else data2com[0] = 1;*/
    /*if (data[0] > 25000)
        data2com[0] = 2;
    else
    {
        if (data[0] < -25000)
            data2com[0] = 0;
        else
            data2com[0] = 1;
    }

    if (data[1] > 25000)
        data2com[1] = 2;
    else
    {
        if (data[1] < -25000)
            data2com[1] = 0;
        else
            data2com[1] = 1;
    }
    if (data[2] > 25000)
        data2com[2] = 2;
    else
    {
        if (data[2] < -25000)
            data2com[2] = 0;
        else
            data2com[2] = 1;
    }*/
//    unsigned char dead_zone = 10;
//    data2com[0] = (data[1] / 256) + 128;
//    data2com[1] = (data[0] / 256) + 128;
//    data2com[2] = (data[2] / 256) + 128;
//    if ((data2com[0] > 128) && (data2com[0] < dead_zone+128)) data2com[0] = 128;
//    if ((data2com[0] < 128) && (data2com[0] > 128-dead_zone)) data2com[0] = 128;
//    if ((data2com[1] > 128) && (data2com[1] < dead_zone+128)) data2com[1] = 128;
//    if ((data2com[1] < 128) && (data2com[1] > 128-dead_zone)) data2com[1] = 128;
//    if ((data2com[2] > 128) && (data2com[2] < dead_zone+128)) data2com[2] = 128;
//    if ((data2com[2] < 128) && (data2com[2] > 128-dead_zone)) data2com[2] = 128;

//    QString s;
//    for (int i = 0; i < data2com.size(); i++)
//        s = s + QString::number(data2com[i]) + ", ";
//    qDebug() << "Write: " << s;

    QByteArray ba;
    ba.clear();
//    for (int i = 0; i < data2com.size(); i++)
//        ba.append(data2com[i]);


//    ba.append(pitch_z);
//    ba.append(roll_z);
//    ba.append(yaw_z);

//    ba.append(data_arrays[JOYSTICK_X_AXIS]->at(num_elems_in_arr-1));
//    ba.append(data_arrays[JOYSTICK_Y_AXIS]->at(num_elems_in_arr-1));
//    ba.append(data_arrays[JOY3]->at(num_elems_in_arr-1));

    ba.append(data2com.at(0));
    ba.append(data2com.at(1));
    ba.append(data2com.at(2));

    emit ready2com(ba);
}

DataContainer::~DataContainer()
{
    for (int i = 0; i < num_arrays; i++)
        delete data_arrays[i];
}

void DataContainer::AddToArr(quint8 n, float d)
{
    data_arrays[n]->enqueue(d);
    if (data_arrays[n]->size() > num_elems_in_arr)
        data_arrays[n]->dequeue();
}

void DataContainer::Save2File_from_com_port(QByteArray data)
{
    QFile file(QCoreApplication::applicationDirPath() + "/data_from_com_port.log");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
        return;
    }
    //qDebug() << QCoreApplication::applicationDirPath() + "/data_from_com_port.log";
    QString s, temps;
    for (int i = 0; i < data.size(); i++)
    {
        temps = QString::number((unsigned char)data[i]);
        for (int j = temps.length(); j < 4; j++)
            temps.append(" ");
        s = s + temps;
    }
    QTextStream out(&file);
    out.seek(file.size());
    out << s + "\r\n";
    out.flush();
    file.close();
}

void DataContainer::Save2File(QList<float> data)
{
    QFile file(QCoreApplication::applicationDirPath() + "/data.log");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
        return;
    }
    //qDebug() << QCoreApplication::applicationDirPath() + "/data.log";
    QString s, temps;
    for (int i = 0; i < data.size(); i++)
    {
        temps = QString::number(data[i]);
        for (int j = temps.length(); j < 9; j++)
            temps.append(" ");
        s = s + temps;
    }
    QTextStream out(&file);
    out.seek(file.size());
    out << s + "\r\n";
    out.flush();
    file.close();
}

void DataContainer::timeout()
{
    bool simulate = true;
    if (simulate)
    {
        for (int i = DATA_FROM_COM_PORT; i < num_arrays; i++)
        {
            if (i == DATA_FROM_COM_PORT)
                AddToArr(i, qSin(QTime::currentTime().second())*30);
            else
                AddToArr(i, i);

            //s += QString::number((unsigned char)packet.at(i)) + ",";
        }
        //data[1] = qSin(QTime::currentTime().second())*30;data2save
        //data[2] = qSin(QTime::currentTime().second()+30)*20;
    }

    //CalculateALL();

    bool filter = true;

    for (int i = 0; i < num_arrays; i++)
    {
        if (filter)
        {
            int sum = 0;
            for (int j = 0; j < num_elems_in_arr; j++)
            {
                sum = sum + data_arrays[i]->at(j);
            }
            data[i] = sum / num_elems_in_arr;
        }
        else
            data[i] = data_arrays[i]->at(num_elems_in_arr-1);
    }

//    QString t;
//    t.clear();
//    for (int i = 0; i < num_arrays; i++)
//    {
//        t.append(QString::number((float)data[i])).append(", ");
//    }
    //qDebug() << data;
    //Save2File(data);

    emit DataReady(data);
}

void DataContainer::CalculateALL()
{
    switch (stage)
    {
        case 0:
        {
                AddToArr(ACCELLERATION, 0);
        }
        break;

        case 1:
        {
            if (data_arrays[X]->at(num_elems_in_arr-1) < 2000)
                AddToArr(ACCELLERATION, 4);
            else
            {
                pitch_z = 135;
                stage = 2;
            }
        }
        break;
        case 2:
        {
            if (data_arrays[SPEED]->at(num_elems_in_arr-1) >= 100)
            {
                AddToArr(ACCELLERATION, 0);
            }
            if (data_arrays[Z]->at(num_elems_in_arr-1) >= 1500)
            {
                stage = 3;
                pitch_z = pitch_middle_ed;
            }
        }
        break;
    }

    if (stage < 1)
        return;
    // считаем курс как интеграл от крена
    float yaw = data_arrays[YAW]->at(num_elems_in_arr-1)    +
                    ((data_arrays[ROLL]->at(num_elems_in_arr-2)     +
                    data_arrays[ROLL]->at(num_elems_in_arr-1)) / 2) *
                    time_interval / 1000;
    yaw = yaw * 0.5;
    AddToArr(YAW, yaw);
    AddToArr(HEADING, InitH+yaw);

    // интегрируем ускорение, получаем скорость
    float speed = data_arrays[SPEED]->at(num_elems_in_arr-1)               +
                  ((data_arrays[ACCELLERATION]->at(num_elems_in_arr-2)     +
                  data_arrays[ACCELLERATION]->at(num_elems_in_arr-1)) / 2) *
                  time_interval / 1000;

    // проекции на оси
    float pitch = data_arrays[PITCH]->at(num_elems_in_arr-1) / 180 * M_PI;
    yaw = data_arrays[YAW]->at(num_elems_in_arr-1) / 180 * M_PI;
    float speed_X = speed *                                             // скорость умножаем на
                    qCos(pitch) *          // косинус тангажа и на
                    qCos(yaw);             // косинус курса
    float speed_Y = speed *                // скорость умножаем на
                    qSin(pitch) *          // косинус тангажа и на
                    qCos(yaw);             // синус курса
    float speed_Z = (-1)*speed *           // скорость умножаем на
                    qSin(yaw);             // синус курса
    if ((pitch < 0) && speed_Y > 0)
        speed_Y = speed_Y * (-1);
    if ((pitch > 0) && speed_Y < 0)
        speed_Y = speed_Y * (-1);

    AddToArr(SPEED, speed);
    AddToArr(SPEED_X, speed_X);
    AddToArr(SPEED_Y, speed_Y);
    AddToArr(SPEED_Z, speed_Z);

    // интегрируем составляющие скорости, получаем координаты
    float x = data_arrays[X]->at(num_elems_in_arr-1)               +
              ((data_arrays[SPEED_X]->at(num_elems_in_arr-2)       +
              data_arrays[SPEED_X]->at(num_elems_in_arr-1)) / 2)   *
              time_interval / 1000;
    float y = data_arrays[Y]->at(num_elems_in_arr-1)               +
              ((data_arrays[SPEED_Y]->at(num_elems_in_arr-2)       +
              data_arrays[SPEED_Y]->at(num_elems_in_arr-1)) / 2)   *
              time_interval / 1000;
    float z = data_arrays[Z]->at(num_elems_in_arr-1)               +
              ((data_arrays[SPEED_Z]->at(num_elems_in_arr-2)       +
              data_arrays[SPEED_Z]->at(num_elems_in_arr-1)) / 2)   *
              time_interval / 1000;

    if (y < 0)
        y = 0;

    AddToArr(X, x);
    AddToArr(Y, y);
    AddToArr(Z, z);
}

void DataContainer::joystickAxesChanged(int id, int state)
{
    switch(id)
    {
    case 0:
        this->AddToArr(JOYSTICK_X_AXIS, (float)state);
        break;
    case 1:
        this->AddToArr(JOYSTICK_Y_AXIS, (float)state);
        break;
    case 2:
        this->AddToArr(JOY3, (float)state);
        break;
    /*case 3:
        ui->joystickXrotationLabel->setText(tr("%1").arg(state));
        break;

    case 4:
        ui->joystickYrotationLabel->setText(tr("%1").arg(-1*state));

    break;

    case 5:
        this->AddToArr(JOY3, (float)state);
        break;*/
    }
}

void DataContainer::joystickButtonChanged(int id, int state)
{
    QVector<bool> buttonVector;
    buttonVector[id] = state;

    QString buttonTest = "";
    for(int i = 0; i < MAX_JOYSTICK_BUTTONS; ++i)
    {
        if(buttonVector[i] == true)
        {
            if(i < 10)
                buttonTest += tr("0%1  ").arg(i);
            else
                buttonTest += tr("%1").arg(i);
        }
    }
}

void DataContainer::comPortDataReady(QByteArray packet)
{
    Save2File_from_com_port(packet);

    /*float pitch = (unsigned char)packet.at(PITCH - DATA_FROM_COM_PORT);
    pitch = (pitch - pitch_middle_ed) / ((pitch_max_ed - pitch_min_ed) / pitch_amplitude_g);

    float roll = (unsigned char)packet.at(ROLL - DATA_FROM_COM_PORT);
    roll = (roll - roll_middle_ed) / ((roll_max_ed - roll_min_ed) / roll_amplitude_g);*/

    for (int i = 0; i< packet.length(); i++)
    {
        packet[i] = packet[i] + ((qrand()%6)-3);
    }

    for (int i = 0; i < packet.length(); i++)
    {
        AddToArr(DATA_FROM_COM_PORT + i, (unsigned char)packet.at(i));

    }
    /*AddToArr(PITCH-1, 99);
    if (stage < 2)
    {
        AddToArr(PITCH, 0);
        AddToArr(ROLL, 0);
    }
    else
    {
        AddToArr(PITCH, pitch);
        AddToArr(ROLL, roll);
    }*/
}
