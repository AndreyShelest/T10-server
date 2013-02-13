#include "aircraft.h"

Aircraft::Aircraft(QObject *parent) :
    QObject(parent)
{
    velocity = new QVector3D();
    aerodynamicForce = new QVector3D();
    aerodynamicMoments = new QVector3D();
    qmapData=new QMap<int, QString>(getQmapData());
   // qmapData=&;
        // TODO: what is lambda
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

       setFiltered(settings.value("AircraftModel/filteredData", false).toBool());
    naviDataLength=settings.value("AircraftModel/naviDataLength", 18).toInt();
    clientDataLength=settings.value("AircraftModel/naviDataLength", 50).toInt();
    X_coord=settings.value("AircraftModel/initialX", 0).toFloat();
    Y_coord=settings.value("AircraftModel/initialY", 0).toFloat();
    Z_coord=settings.value("AircraftModel/initialZ", 0).toFloat();
    joyX=0;
    joyY=0;
    joyZ=0;
    slide_angle= settings.value("AircraftModel/slide_angle", 0).toFloat();
    attack_angle= settings.value("AircraftModel/attack_angle", 0).toFloat();
    time = settings.value("AircraftModel/initialTime", 0).toFloat();
    dt = settings.value("AircraftModel/dt", 0.05).toFloat();
    pitch = settings.value("AircraftModel/initialPitch", 0).toFloat();float temp = velocity->x() * qSin(pitch) +
            velocity->y() * qCos(pitch) * qCos(roll) -
            velocity->z() * qCos(pitch) * qSin(roll);
height = height + trapz(dhdt, temp, dt);
dhdt = temp;
    roll = settings.value("AircraftModel/initialRoll", 0).toFloat();
    yaw = settings.value("AircraftModel/initialYaw", 0).toFloat();
    heading = settings.value("AircraftModel/initialHeading", 0).toFloat();
    height = settings.value("AircraftModel/initialHeight", 3000).toFloat();
    velocity->setY(settings.value("AircraftModel/initialVelocityMagnitude", 100).toFloat());
    wx = settings.value("AircraftModel/initialWx", 0).toFloat();
    wy = settings.value("AircraftModel/initialWy", 0).toFloat();
    wz = settings.value("AircraftModel/initialWz", 0).toFloat();

    mx = -0.615;    // FIXME: aaa
    my = -0.94;     // FIXME: aaa
    mz = -6.725;    // FIXME: aaa
    S = 2.77;
    l = 2.7;
    ba = 0.841;
    Ix = 26.8;
    Iy = 154.6;
    Iz = 2.8;
    cx = 5.12;      // FIXME: aaa
    cy = 0.26;      // FIXME: aaa
    cz = 0.47;      // FIXME: aaa
    G = 9.8;
    m = 175;

    dhdt = 0;
    dwx = 0;
    dwy = 0;
    dwz = 0;
    dPitch = 0;
    dYaw = 0;
    dRoll = 0;
    dVx = 0;
    dVy = 0;
    dVz = 0;
    dataToserver=new QVector<float>;
    dataToserver->fill(0,clientDataLength);
 avrg4Data =new QList<QList<float> >;
    connect(&modelingTimer, SIGNAL(timeout()), this, SLOT(modelingStep()));

}

Aircraft::~Aircraft()
{
    delete velocity;
    delete aerodynamicForce;
    delete aerodynamicMoments;
    delete qmapData;
    delete avrg4Data;

}

QList<int> Aircraft::getJoyData()
{
    QList<int> data;
     data.append(joyX);
    data.append(joyY);
    data.append(joyZ);
    return data;
}

void Aircraft::setFiltered(bool _turn)
{
    filtered=_turn;
//    if (_turn)
//       avrg4Data =new QList<QList<float> >;
//    else delete avrg4Data;
}



QMap<int, QString> Aircraft::getQmapData()
{
    QMap<int, QString> mapOfdata;
    mapOfdata[0]="JoyX";         //0
    mapOfdata[1]="JoyY";          //1
    mapOfdata[2]="JoyZ";          //2
    mapOfdata[3]="heading";  //3
    mapOfdata[4]="velocity->X"; //4
    mapOfdata[5]="velocity->Y"; //5
    mapOfdata[6]="velocity->Z"; //6
    mapOfdata[7]="time"  ;           //7
    mapOfdata[8]="X_coord";  //8
    mapOfdata[9]="Y_coord";  //9
    mapOfdata[10]="Z_coord";  //10
    mapOfdata[11]="unused11";             //11
    mapOfdata[12]="slide_angle"; //12
    mapOfdata[13]="attack_angle";  //13
    mapOfdata[14]="Rau_X";
    mapOfdata[15]="Rau_Y";
    mapOfdata[16]="Rau_Z";
    mapOfdata[17]="unused17";
   mapOfdata[18]="rudder";
   mapOfdata[19]="aileron";
   mapOfdata[20]="right_stab";
   mapOfdata[21]="left_stab";
   mapOfdata[22]="roll";
   mapOfdata[23]="pitch";
   mapOfdata[24]="yaw";
   mapOfdata[25]="Dus1";
   mapOfdata[26]="Dus2";
   mapOfdata[27]="Dus3";
   mapOfdata[28]="Dus4";
   return mapOfdata;
}

float Aircraft::getCurrentTime()
{

    return time;
}
bool Aircraft::isactiveSimulate()
{
    return modelingTimer.isActive();
}




float Aircraft::trapz(float previous, float current, float t)
{
    return ((previous+current)/2) * t;
}

float Aircraft::avrg4(float current, float current_1, float current_2, float current_3)
{
    return ((current+current_1+current_2+current_3)/4);
}

void Aircraft::setJoyX(int param)
{
    if (!filtered)
    this->joyX=param;
    else
     this->joyX=trapz(this->joyX,param);

    }

void Aircraft::setJoyY(int param)
{
    if (!filtered)
    this->joyY=param;
    else
     this->joyY=trapz(this->joyY,param);
}

void Aircraft::setJoyZ(int param)
{
    if (!filtered)
    this->joyZ=param;
    else
     this->joyZ=trapz(this->joyZ,param);
}

void Aircraft::setDataFromBoard(QByteArray indata)
{


    if (!filtered){
        dataFromBoard.clear();
        foreach(float i,indata)
        {
        dataFromBoard.append((unsigned char)i);
        }
    }
    else
     {
        if(avrg4Data->size()<3){

        for(int i=0;i<indata.size();i++)
          dataFromBoard.replace(i,trapz(dataFromBoard[i],(unsigned char)indata[i]));
        avrg4Data->append(dataFromBoard);
        }
        else
        {
            for(int i=0;i<indata.size();i++)
            {
              dataFromBoard.replace(i,
                                    avrg4((unsigned char)indata[i],
                                    avrg4Data->at(0).at(i),
                                    avrg4Data->at(1).at(i),
                                    avrg4Data->at(2).at(i)));
              avrg4Data->removeFirst();
              avrg4Data->append(dataFromBoard);
            }
            }
        }


    roll=dataFromBoard[4]-180;
    pitch=dataFromBoard[5]-113;
 if (pitch<-13)
        pitch=-13;
    yaw=dataFromBoard[6]-158;

    //yaw=dataFromBoard[6];

}

void Aircraft::setServerData()
{

     dataToserver->clear();
    dataToserver->append(joyX);         //0
   dataToserver->append(joyY);          //1
   dataToserver->append(joyZ);          //2
   dataToserver->append(heading);  //3
   dataToserver->append(velocity->x()); //4
   dataToserver->append(velocity->y()); //5
   dataToserver->append(velocity->z()); //6
   dataToserver->append(time*1000);             //7
   dataToserver->append(X_coord);  //8
   dataToserver->append(Y_coord);  //9
   dataToserver->append(Z_coord);  //10
   dataToserver->append(0);             //11
   dataToserver->append(slide_angle);   //12
   dataToserver->append(attack_angle);   //13
   for (int i=dataToserver->size();i<naviDataLength;i++)
   {
       dataToserver->append(0);
   }
//    dataToserver->append((joyX) / 256);
//dataToserver->append((joyY) / 256);
// dataToserver->append((joyZ) / 256);
   if (dataFromBoard.size()==32)
   {
 for (int i=0;i<dataFromBoard.size();i++)
 {
     dataToserver->append(dataFromBoard[i]);
 }
   }
   else
   {
       for (int i=0;i<(clientDataLength-naviDataLength);i++)
       {
           dataToserver->append(0);
       }
   }
dataToserver->replace(naviDataLength+4,roll);
dataToserver->replace(naviDataLength+5,pitch);
dataToserver->replace(naviDataLength+6,yaw);
dataToserver->replace(naviDataLength+7,dataToserver->at(naviDataLength+7)-128);
dataToserver->replace(naviDataLength+8,dataToserver->at(naviDataLength+8)-128);
dataToserver->replace(naviDataLength+9,dataToserver->at(naviDataLength+9)-128);
dataToserver->replace(naviDataLength+10,dataToserver->at(naviDataLength+10)-108);
dataToserver->replace(14,(joyX/256)/9);
dataToserver->replace(15,(joyY/256)/8);
dataToserver->replace(16,(joyZ/256)/7);
QList<float> sendData=dataToserver->toList();

  emit serverDataReady(sendData);
}

void Aircraft::setCustomServerData(QList<int> dataNumbers)
{
 QList<float> clientData;
    QMap<int, QString> ::iterator it=qmapData->begin();
    for(;it!=qmapData->end();++it)
    {
        for(int i=0;i<dataNumbers.size();i++)
        {
            if (it.key()==dataNumbers[i])
                clientData.append(dataToserver->at(it.key()));
        }

    }

    emit serverCustomDataReady(clientData);
}

void Aircraft::modelingStep()
{
  //  qDebug() << wx << wy << wz << velocity->length() << time;

    // расчет высоты
//    float temp = velocity->x() * qSin(pitch) +
//                 velocity->y() * qCos(pitch) * qCos(roll) -
//                 velocity->z() * qCos(pitch) * qSin(roll);
//    height = height + trapz(dhdt, temp, dt);
//    dhdt = temp;

//    // плотность воздуха
//    airDensity = 0.125 * qExp(-0.0001*height);
//    // скоростной напор
//    ramAir = (airDensity * qPow(velocity->length(), 2)) / 2;

//    // аэродинамические моменты
//    aerodynamicMoments->setX(mx * ramAir * S * l);
//    aerodynamicMoments->setY(my * ramAir * S * l);
//    aerodynamicMoments->setZ(mz * ramAir * S * ba);

//    // угловые скорости
//    temp = (aerodynamicMoments->x() - (Ix-Iy) * wy * wz) / Ix;
//    wx = wx + trapz(dwx, temp, dt);
//    dwx = temp;
//    temp = (aerodynamicMoments->y() - (Ix-Iz) * wy * wx) / Iy;
//    wy = wy + trapz(dwy, temp, dt);
//    dwy = temp;
//    temp = (aerodynamicMoments->z() - (Iy-Ix) * wx * wy) / Iz;
//    wz = wz + trapz(dwz, temp, dt);
//    dwz = temp;

//    // углы
//    temp = ((1/qCos(pitch)) * (wy*qCos(roll) - wz*qSin(roll)));
//    yaw = yaw + trapz(dYaw, temp, dt);
//    dYaw = temp;
//    temp = wy*qSin(roll) + wz*qCos(roll);
//    pitch = pitch + trapz(dPitch, temp, dt);
//    dPitch = temp;
//    temp = wx - qTan(pitch) * (wy*qCos(roll) - wz*qSin(roll));
//    roll = roll + trapz(dRoll, temp, dt);
//    dRoll = temp;

//    // аэродинамические силы
//    aerodynamicForce->setX(-cx * ramAir * S);
//    aerodynamicForce->setY(cy * ramAir * S);
//    aerodynamicForce->setZ(cz * ramAir * S);

//    // проекции силы тяжести на оси связанной СК
//    Gx = -G * qSin(pitch);
//    Gy = -G * qCos(pitch) * qCos(roll);
//    Gz = G * qCos(pitch) * qCos(roll);

//    // скорость
//    temp = ((aerodynamicForce->x() + Gx) / m) - wy*velocity->z() + wz*velocity->y();
//    velocity->setX(velocity->x() + trapz(dVx, temp, dt));
//    dVx = temp;
//    temp = ((aerodynamicForce->y() + Gy) / m) - wz*velocity->x() + wx*velocity->z();
//    velocity->setY(velocity->y() + trapz(dVy, temp, dt));
//    dVy = temp;
//    temp = ((aerodynamicForce->z() + Gz) / m) - wx*velocity->y() + wy*velocity->x();
//    velocity->setZ(velocity->z() + trapz(dVz, temp, dt));
//    dVz = temp;


    time = time + dt;
    qDebug()<<"ssd";
    emit joyDataReady(getJoyData());
    emit signal_modelingStep();

}

void Aircraft::startSimulation()
{
    if(!modelingTimer.isActive())
    {
    modelingTimer.start(dt*1000);
    dataToserver=new QVector<float>;
    }
}

void Aircraft::stopSimulation()
{
    modelingTimer.stop();
    delete dataToserver;
}


void Aircraft::slotCalculateControl(QList<int> inJoy)
{
   QList<int> out;
    foreach(int i,inJoy)
    {
        out.append(i);
    }
    out.append(inJoy.at(2));
    out.append(inJoy.at(0));
    out.append(inJoy.at(1));
        emit customDataReady(out);
}
