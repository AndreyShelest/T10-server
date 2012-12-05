#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QObject>
#include <QSettings>
#include <QCoreApplication>
#include <QVector3D>
#include <QtCore/qmath.h>
#include <QDebug>
#include <QTimer>

class Aircraft : public QObject
{
    Q_OBJECT
public:
    explicit Aircraft(QObject *parent = 0);
    ~Aircraft();
    QList<int> getJoyData();

private:
    float time;             // модельное время, секунд
    float dt;               // период квантования, секунд
    float pitch;            // тангаж
    float roll;             // крен
    float yaw;              // рыскание
    float heading;          // курс
    float height;           // высота, метров
    float airDensity;       // плотность воздуха
    float ramAir;           // скоростной напор
//    float velocityMagnitude;
//    float velosityX;
//    float velosityY;
//    float velosityZ;
    QVector3D* velocity;     // м/с
    QVector3D* aerodynamicForce;
    QVector3D* aerodynamicMoments;
    int joyX;
    int joyY;
    int joyZ;
    float dVx, dVy, dVz;
    float mx, my, mz;       // коэффициенты моментов аэродинамических сил относительно осей связанной системы координат
    float cx, cy, cz;       // коэффициенты проекций аэродинамических сил относительно на оси связанной системы координат
    float S;                // площадь крыла
    float l;                // размах крыла
    float ba;               // средняя аэродинамическая хорда крыла
    float m;                // масса

    float dhdt;
    // угловые скорости
    float wx, wy, wz, dwx, dwy, dwz;
    float Ix, Iy, Iz;       // моменты инерции относительно осей связанной системы координат
    float dPitch, dYaw, dRoll; // производные углов
    float G;
    float Gx, Gy, Gz;       // проекции силы тяжести на оси связанной СК


    inline float trapz(float previous, float current, float t);
    
    QTimer modelingTimer;
signals:
   void joyDataReady(QList<int>);
public slots:
    void setJoyX(int param);
    void setJoyY(int param);
    void setJoyZ(int param);
    void modelingStep();
    void startSimulation();
    void stopSimulation();
    
};

#endif // AIRCRAFT_H
