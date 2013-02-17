#include "joywidget.h"

JoyWidget::JoyWidget(QWidget *parent) :
    QWidget(parent)
{
    m_grLayout=new QGridLayout;
    cmbxJoy=new QComboBox();
    m_grLayout->addWidget(cmbxJoy,0,0);
    rescanButton=new QToolButton();
    rescanButton->setIcon(QIcon(":/resources/icons/refresh.svg"));
    m_grLayout->addWidget(rescanButton,1,0);
    cmbxJoy->addItem("No joysticks");
    labelJoystickStatus = new QLabel(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("not connected") + "</span>");
    this->setLayout(m_grLayout);
    connect(rescanButton,SIGNAL(clicked()),this,SLOT(rescanJoystick()));
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

bool JoyWidget::joyAvailable()
{
    if(joystick->getNumAvaliableJoystick()>0)
        return true;
    else
        return false;
}

void JoyWidget::rescanJoystick()
{
    if(joystick!=NULL)
    {
        delete joystick;
        createJoystick();

    }
    else createJoystick();
}

VJoystickAdapter *JoyWidget::getJoystick()
{
    return joystick;
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
            //labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("connecting error") + "</span>");
            emit JoyConnected(false);
            qDebug() << "connecting error: " << joystick->getJoystickName();
        }
    }
    else
    {
        if (!joystick->isConnected())
            labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("connecting error") + "</span>");
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
