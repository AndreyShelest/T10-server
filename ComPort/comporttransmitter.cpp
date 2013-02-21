#include "comporttransmitter.h"


ComPortTransmitter::ComPortTransmitter(QObject *parent) :
    QObject(parent)
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    //dataToMcSize = settings.value("ComPort/dataToMcSize", 10).toInt();
dataToMcSize=10;
    zavislo = true;
    packetLen = 32;
    start_sequence.clear();
    buff.clear();
    buff2.clear();
    packet.clear();
    dataToMc.clear();
    dataToMc.fill(128, dataToMcSize);
    start_sequence.append((unsigned char)'s');
    start_sequence.append((unsigned char)'t');
    COM_connected = false;
    port = 0;

    connect(&dataToMcTimer, SIGNAL(timeout()), this, SLOT(slot_DataToMcTimeout()));

}

ComPortTransmitter::~ComPortTransmitter()
{
    if (port != 0)
    {
        delete port;
        port = 0;
    }
}

bool ComPortTransmitter::COM_isConnected()
{
    return COM_connected;
}

bool ComPortTransmitter::COM_reconnect()
{
    if (port != 0)
    {
        dataToMcTimer.stop();
        port->close();
        delete port;
        port = 0;
    }
    COM_connected = false;

    buff.clear();
    packet.clear();

    port = new AbstractSerial(this);
    connect(port, SIGNAL(readyRead()), this, SLOT(slot_Recieved()));
    connect(&watchDog, SIGNAL(timeout()), this, SLOT(slot_watchDog()));
    watchDog.start(1000);

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    deviceName = settings.value("ComPort/name", "/dev/ttyUSB0").toString();
    port->setDeviceName(deviceName);
    if (!port->open(AbstractSerial::ReadWrite))
    {
        qDebug() << "Serial device " << port->deviceName() << " not open!!!";
        qDebug() << port->errorString();
        return false;
    }

    qDebug() << "Serial device " << port->deviceName() << " open in " << port->openMode();

    //        qDebug() << "= Default parameters =";
    //        qDebug() << "Device name            : " << port->deviceName();
    //        qDebug() << "Baud rate              : " << port->baudRate();
    //        qDebug() << "Data bits              : " << port->dataBits();
    //        qDebug() << "Parity                 : " << port->parity();
    //        qDebug() << "Stop bits              : " << port->stopBits();
    //        qDebug() << "Flow                   : " << port->flowControl();
    //        qDebug() << "Total read timeout constant, msec : " << port->totalReadConstantTimeout();
    //        qDebug() << "Char interval timeout, usec       : " << port->charIntervalTimeout();

    if (!port->setBaudRate(AbstractSerial::BaudRate115200)) {
        qDebug() << "Set baud rate " <<  AbstractSerial::BaudRate115200 << " error.";
        return false;
    };

    if (!port->setDataBits(AbstractSerial::DataBits8)) {
        qDebug() << "Set data bits " <<  AbstractSerial::DataBits8 << " error.";
        return false;
    }

    if (!port->setParity(AbstractSerial::ParityNone)) {
        qDebug() << "Set parity " <<  AbstractSerial::ParityNone << " error.";
        return false;
    }

    if (!port->setStopBits(AbstractSerial::StopBits1)) {
        qDebug() << "Set stop bits " <<  AbstractSerial::StopBits1 << " error.";
        return false;
    }

    if (!port->setFlowControl(AbstractSerial::FlowControlOff)) {
        qDebug() << "Set flow " <<  AbstractSerial::FlowControlOff << " error.";
        return false;
    }

    // Here set total timeout for read 1 ms, if open mode is Unbuffered only!
#if defined (Q_OS_UNIX)
    // Method setTotalReadConstantTimeout() not supported in *.nix.
    if (port->openMode() & AbstractSerial::Unbuffered)
        port->setCharIntervalTimeout(5000);//5 msec
#elif defined (Q_OS_WIN)
    if (port->openMode() & AbstractSerial::Unbuffered)
        port->setTotalReadConstantTimeout(100);
#endif

    dataToMcTimer.start(100);
    COM_connected = true;

    return true;
}

QString ComPortTransmitter::getDeviceName()
{
    return deviceName;
}

void ComPortTransmitter::COM_disconnect()
{
    if (port != 0)
    {
        port->close();
        delete port;
        port = 0;
    }
    COM_connected = false;
    zavislo = true;
}

void ComPortTransmitter::slotJoyXChanged(int value)
{
    unsigned char val = (value+32767) / 256;
    dataToMc[1] = val;
}

void ComPortTransmitter::slotJoyYChanged(int value)
{
    unsigned char val = (value+32767) / 256;
    dataToMc[2] = val;
}

void ComPortTransmitter::slotJoyZChanged(int value)
{
    unsigned char val = (value+32767) / 256;
    dataToMc[3] = val;
}

void ComPortTransmitter::slotCustomAll(QList<int> indata)
{
    int i=4;
    unsigned char val;
    foreach(int value,indata)
    {

    val = (value+32767) / 256;
    dataToMc[i] = val;
    i++;
    }

    //invert aileron
    int value=indata[4];
            if (value<=0)
            {value=abs(value);}
            else {value=0-value;}
            val = (value+32767) / 256;
           dataToMc[8]=val ;
    //invert Stab
    value=indata[5];
            if (value<=0)
            {value=abs(value);}
            else {value=0-value;}
            val = (value+32767) / 256;
           dataToMc[9]=val ;


}

void ComPortTransmitter::slot_Recieved()
{
    watchDog.start(1000);
    if (zavislo)
    {
        zavislo = false;
        emit Otvislo();
    }

    buff.append(port->readAll());
    if (buff.length() < packetLen)
        return;

    while (buff.length() > 2)
    {
        int first_seq, second_seq;
        first_seq = findStartSeq(0);
        if (first_seq == -1)
            return;
        second_seq = findStartSeq(first_seq+1);
        if (second_seq == -1)
            return;

        packet.clear();
        int len = second_seq-(first_seq+start_sequence.length());
        packet.append(buff.mid(first_seq+start_sequence.length(), len));
        buff.remove(0, second_seq);

        for (int i = 0; i < packet.length(); i++)
        {
            if (packet[i] == start_sequence[0])
                packet.remove(i, 1);
        }

        QString s;
        s.clear();
        for (int i = 0; i < packet.size(); i++)
            s += QString::number(((unsigned char)packet[i]))+",";
        qDebug() << s;

        emit DataReady(packet);

    }
}

void ComPortTransmitter::slot_Write(QByteArray data)
{
    if (port == 0)
    {
        qDebug() << "Unable to write to COM port";
        return;
    }
    if (!port->isOpen())
    {
        qDebug() << "Unable to write to COM port";
        return;
    }
//    if (zavislo)
//        return;
    port->write(data);
    port->flush();
//                QString s;
//                for (int i = 0; i < data.size(); i++)
//                    s = s + QString::number((unsigned char)data.at(i));
//                qDebug() << "Write: " << s;
}

void ComPortTransmitter::slot_watchDog()
{
    if (!COM_connected)
        return;
    zavislo = true;
    emit Zavislo();
}

void ComPortTransmitter::slot_DataToMcTimeout()
{
       this->slot_Write(dataToMc);
    this->dataTransmitedToCom(dataToMc);
}

int ComPortTransmitter::findStartSeq(int from)
{
    int seqPos = buff.indexOf(start_sequence, from);
    if (seqPos == -1)
        return -1;
    if (seqPos == 0)
        return 0;

    if (buff[seqPos-1] == start_sequence[0])
        return findStartSeq(seqPos+1);
    else
        return seqPos;
}

void ComPortTransmitter::getPacket(QByteArray &apacket)
{
    apacket=packet;
    if (packetLen>10)
    { apacket.append(234);
                apacket.append(24);
                apacket.append(34);
    }
    else {
        for (int i=0; i<33 ;i++)
        {apacket.clear();
        apacket.append(i);
        }
        apacket.append(234);
                        apacket.append(24);
                        apacket.append(34);
    }
}


void ComPortTransmitter::setControlByte(char cbyte)
{

    dataToMc[0]=(unsigned char)cbyte;


}

void ComPortTransmitter::setCustomRauX(int raux)
{
    dataToMc[4]=(unsigned char)raux;
}

void ComPortTransmitter::setCustomRauY(int rauy)
{
    dataToMc[5]=(unsigned char)rauy;
}

void ComPortTransmitter::setCustomRauZ(int rauz)
{
    dataToMc[6]=(unsigned char)rauz;
}

void ComPortTransmitter::setCustomPPNr(int rudder)
{
    dataToMc[7]=(unsigned char)rudder;
}

void ComPortTransmitter::setCustomPPNa(int aileron)
{

    dataToMc[8]=(unsigned char) (aileron);

}

void ComPortTransmitter::setCustomPPNs(int stabilisator)
{
    dataToMc[9]=(unsigned char)stabilisator;

}



