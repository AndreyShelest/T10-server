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

    //создание виджетов кнопок джойстика

    QGridLayout * jtopLayout=new QGridLayout;
    joyButtons=new QWidget();
    joyButtons->setLayout(jtopLayout);
     jtopLayout->addWidget(new QLabel("<span style=\"color:#91fb5d;font-weight:bold;\">" +tr("Joy Butons") + "</span>"),0,0,1,4,Qt::AlignCenter);
    int n=0;//цифра на кнопке
     for (int i=0; i<3;++i)
    for (int j=0; j<4;++j)
               {
            jtopLayout->addWidget(createButton(n),i+1,j);
           // qDebug()<<"i: "<<i<<" j: "<<j<<"--"<<n;
            n++;
        }
         joyButtons->setFixedSize(100,100);
    m_grLayout->addWidget(joyButtons,1,1);
}

JoyWidget::~JoyWidget()
{
    delete m_grLayout;
    delete cmbxJoy;
    delete rescanButton;
    delete labelJoystickStatus;
    delete joyButtons;
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

void JoyWidget::joyButtonChecked(int button_num, bool state)
{


        QList<QPushButton *> btnList= joyButtons->findChildren<QPushButton *>("");

                for(int i=0;i<btnList.size();++i)
        {
            if(btnList.at(i)->property("numButton").toInt()==button_num)
            {
                btnList.at(i)->setChecked(state);
                     //   qDebug()<<"property: "<<btnList.at(i)->property("numButton").toInt();
            }
        }
                if (state)
                {
        qDebug()<<"JoyBtn "<<button_num<<" clicked";
                }
}

void JoyWidget::joyButtonToggled(bool arg)
{
    ((QPushButton*)sender())->setChecked(arg);
   // qDebug()<<((QPushButton*)sender())->property("numButton").toInt();
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
  connect(joystick,SIGNAL(sigButtonChanged(int,bool)),this,SLOT(joyButtonChecked(int,bool)));
            //ui->actionJoystick->setStatusTip(tr("Disconnect from Joystick"));
            // ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
            qDebug() << "Joystick connected: " << joystick->getJoystickName();
        }

        else
        {
            //ui->label_Joystick_status->setText("<font color=red>"+tr("Not connected")+"</font>");
            //labelJoystickStatus->setText(tr("Joystick: ") + "<span style=\"color:#ff0000;font-weight:bold;\">" + tr("connecting error") + "</span>");
             disconnect(joystick,SIGNAL(sigButtonChanged(int,bool)),this,SLOT(joyButtonChecked(int,bool)));
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
          disconnect(joystick,SIGNAL(sigButtonChanged(int,bool)),this,SLOT(joyButtonChecked(int,bool)));
        emit JoyConnected(false);

        // ui->actionJoystick->setStatusTip(tr("Connect to Joystick"));
        // ui->actionJoystick->setToolTip(ui->actionJoystick->statusTip());
    }
}


QPushButton *JoyWidget::createButton(const int num)
{
    QPushButton * joyBtn=new QPushButton (QString::number(num+1));
    joyBtn->setFixedSize(20,20);
    joyBtn->setProperty("numButton",num);
    joyBtn->setCheckable(true);
    //joyBtn->setObjectName("joyBtn"+QString::number(num));
   connect(joyBtn,SIGNAL(toggled(bool)),this,SLOT(joyButtonToggled(bool)));
                return joyBtn;
}
