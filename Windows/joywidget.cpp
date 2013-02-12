#include "joywidget.h"

JoyWidget::JoyWidget(QWidget *parent) :
    QWidget(parent)
{
m_grLayout=new QGridLayout;
cmbxJoy=new QComboBox();
m_grLayout->addWidget(cmbxJoy);
cmbxJoy->addItem("No joysticks");
    labelJoystickStatus = new QLabel(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not connected") + "</span>");
this->setLayout(m_grLayout);
}

JoyWidget::~JoyWidget()
{
    qDebug()<< "JoyWidget deleted";
}

void JoyWidget::setSettings(QSettings *_settings)
{
    settings=_settings;
}

void JoyWidget::createJoystick()
{
    joystick = new VJoystickAdapter();
    JoyList=joystick->getAvaliableJoystickName();
    cmbxJoy->clear();
    cmbxJoy->addItems(JoyList);
}

bool JoyWidget::rescanJoystick()
{
    if(joystick!=NULL)
    {
        delete joystick;
    createJoystick();
        return true;
    }
    else return false;
}

void JoyWidget::slotJoyConnect(bool arg)
{
    qDebug() << "Available joysticks: ";
    qDebug() << JoyList;
    if (arg)
    {
    int m_joyId = -1;
//    for (int i = 0; i < JoyList.count(); i++)
//    {
//        if (JoyList[i] == settings->value("Joystick/name", "").toString())
//        {
//            m_joyId = i;
//            break;
//        }
//    }
    m_joyId=cmbxJoy->currentIndex();

    if((m_joyId > -1) && joystick->open(m_joyId))
    {

        labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#008800;font-weight:bold;\">" + tr("connected") + "</span>");

        //ui->actionJoystick->setStatusTip(tr("Disconnect from Joystick"));
       // ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
        qDebug() << "Joystick connected: " << joystick->getJoystickName();
    }

    else
    {
        //ui->label_Joystick_status->setText("<font color=red>"+tr("Not connected")+"</font>");
        //labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to joystick") + "</span>");
        emit JoyConnected(false);
        qDebug() << "Unable to connect to joystick: " << joystick->getJoystickName();
    }
    }
else
{
    if (!joystick->isConnected())
        labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("unable to connect to joystick") + "</span>");
    else
    {
        labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("disconnected") + "</span>");
        joystick->close();
    }
    emit JoyConnected(false);

   // ui->actionJoystick->setStatusTip(tr("Connect to Joystick"));
   // ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
}
}
