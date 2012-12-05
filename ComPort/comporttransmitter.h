#ifndef COMPORTTRANSMITTER_H
#define COMPORTTRANSMITTER_H

#include <QObject>
#include <QtCore>
#include <QTimer>
#include "abstractserial.h"

class ComPortTransmitter : public QObject
{
    Q_OBJECT
private:
    QByteArray packet;
    quint16 packetLen;
    QByteArray buff;
    QByteArray buff2;
    QByteArray dataToMc;
    quint32 dataToMcSize;

    QByteArray start_sequence;

    AbstractSerial* port;

    bool COM_connected;
    QString deviceName;
    bool zavislo;
    QTimer watchDog;
    QTimer dataToMcTimer;

    int findStartSeq(int from);

public:
     explicit ComPortTransmitter(QObject *parent = 0);
    ~ComPortTransmitter();
    bool COM_reconnect();
    bool COM_isConnected();
    QString getDeviceName();
    void getPacket(QByteArray &apacket);
signals:
    void DataReady(QByteArray data);
    void Zavislo();
    void Otvislo();
    void dataTransmitedToCom(QByteArray data);
private slots:
    void slot_watchDog();
    void slot_DataToMcTimeout();
public slots:
    void slot_Recieved();
    void slot_Write(QByteArray data);
    void COM_disconnect();
    void setControlByte(char cbyte);
    void setCustomPPNr(int rudder);
    void setCustomPPNa(int aileron);
    void setCustomPPNs(int stabilisator);
    void setCustomRauX(int raux);
    void setCustomRauY(int rauy);
    void setCustomRauZ(int rauz);

    void slotJoyXChanged(int value);
    void slotJoyYChanged(int value);
    void slotJoyZChanged(int value);

};

#endif // COMPORTTRANSMITTER_H
