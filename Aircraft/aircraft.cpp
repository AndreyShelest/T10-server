#include "aircraft.h"

Aircraft::Aircraft(QObject *parent) :
    QObject(parent)
{
    velocity = new QVector3D();
    aerodynamicForce = new QVector3D();
    aerodynamicMoments = new QVector3D();
        // TODO: what is lambda
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

//    settings.setValue("AircraftModel/initialTime", 0);
//    settings.setValue("AircraftModel/dt", 0.1);
//    settings.setValue("AircraftModel/initialPitch", 0);
//    settings.setValue("AircraftModel/initialRoll", 0);
//    settings.setValue("AircraftModel/initialYaw", 0);
//    settings.setValue("AircraftModel/initialHeading", 0);
//    settings.setValue("AircraftModel/initialHeight", 3000);
//    settings.setValue("AircraftModel/initialVelocityMagnitude", 100);
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
    dt = settings.value("AircraftModel/dt", 0.1).toFloat();
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

    connect(&modelingTimer, SIGNAL(timeout()), this, SLOT(modelingStep()));

}

Aircraft::~Aircraft()
{
    delete velocity;
    delete aerodynamicForce;
    delete aerodynamicMoments;
}

QList<int> Aircraft::getJoyData()
{
    QList<int> data;
     data.append(joyX);
    data.append(joyY);
    data.append(joyZ);
    return data;
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
    mapOfdata[7]="unused7"  ;           //7
    mapOfdata[8]="X_coord";  //8
    mapOfdata[9]="Y_coord";  //9
    mapOfdata[10]="Z_coord";  //10
    mapOfdata[11]="unused11";             //11
    mapOfdata[12]="slide_angle"; //12
    mapOfdata[13]="attack_angle";  //13
    mapOfdata[14]="unused14";
    mapOfdata[15]="unused15";
    mapOfdata[16]="unused16";
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
   mapOfdata[26]="Dus3";
   mapOfdata[26]="Dus4";
    return mapOfdata;
}




float Aircraft::trapz(float previous, float current, float t)
{
    return ((previous+current)/2) * t;
}

void Aircraft::setJoyX(int param)
{
    this->joyX=param;
}

void Aircraft::setJoyY(int param)
{
    this->joyY=param;
}

void Aircraft::setJoyZ(int param)
{
    this->joyZ=param;
}

void Aircraft::setDataFromBoard(QByteArray indata)
{

    dataFromBoard.clear();
    foreach(int i,indata)
    {
    dataFromBoard.append(i);
    }
    roll=(int)dataFromBoard[4]+76;
    pitch=(int)dataFromBoard[5]-113;
 if (pitch<-13)
        pitch=-13;
    yaw=(int)dataFromBoard[6]+101;

}

void Aircraft::setServerData()
{
    QList<int> dataToserver;
     dataToserver.clear();
    dataToserver.append(joyX);         //0
   dataToserver.append(joyY);          //1
   dataToserver.append(joyZ);          //2
   dataToserver.append((int)heading);  //3
   dataToserver.append((int)velocity->x()); //4
   dataToserver.append((int)velocity->y()); //5
   dataToserver.append((int)velocity->z()); //6
   dataToserver.append(0);             //7
   dataToserver.append((int)X_coord);  //8
   dataToserver.append((int)Y_coord);  //9
   dataToserver.append((int)Z_coord);  //10
   dataToserver.append(0);             //11
   dataToserver.append((int)slide_angle);   //12
   dataToserver.append((int)attack_angle);   //13
   for (int i=dataToserver.size();i<naviDataLength;i++)
   {
       dataToserver.append(0);
   }
//    dataToserver.append((joyX) / 256);
//dataToserver.append((joyY) / 256);
// dataToserver.append((joyZ) / 256);
 for (int i=0;i<dataFromBoard.size();i++)
 {
     dataToserver.append((int)dataFromBoard[i]);
 }
//dataToserver[naviDataLength+4]=(int)roll;
//dataToserver[naviDataLength+5]=(int)pitch;
//dataToserver[naviDataLength+6]=(int)yaw;
  emit serverDataReady(dataToserver);
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

    emit joyDataReady(getJoyData());
    emit signal_modelingStep();

}

void Aircraft::startSimulation()
{
    if(!modelingTimer.isActive())
    {
    modelingTimer.start(dt*1000);
    }
}

void Aircraft::stopSimulation()
{
    modelingTimer.stop();
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
