#include "t10servermain.h"


T10ServerMain::T10ServerMain(QWidget *parent) :
    QMainWindow(parent)
{
    // подключаем файл внешнего вида
    QFile file(":/resources/qss/green.qss");
    file.open(QFile::ReadOnly);

    //устанавливаем стили из этого файла
    QString styleSheet = QLatin1String(file.readAll());
     this->setStyleSheet(styleSheet);
    this->setWindowTitle(QCoreApplication::applicationName());

    //загружаются настройки из файла
    settings =new QSettings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());
    activeTabs =new QStringList();
       main_tab_wgt =new QTabWidget();
if (loadSettings(settings))
{
    qDebug() << "Settings file LOADED: " << settings->fileName();
    if (!createTabs())
    {
        qDebug()<<"!!Ошибка при создании вкладок";
    }
    else
    {
         qDebug()<<"вкладки созданы";
    }
}
else
{
    qDebug() << "Settings file NOT LOADED!!: " << settings->fileName();

    main_tab_wgt->addTab(new QLabel("Ошибка при чтении файла настроек",main_tab_wgt),"error");
}
    this->setCentralWidget(main_tab_wgt);
createMenuAndToolBar();


    this->resize(700,500);

}

T10ServerMain::~T10ServerMain()
{
    delete gMainLayout;
    delete cntrlWgt;
    delete main_tab_wgt;
    delete settings;
    delete activeTabs;
    delete iconsToolBar;
    delete actionComPort;
    delete actionAircraft;
    delete actionServer;
    delete actionJoystick;
    qDebug()<<"T10serverMain Closed";

}

bool T10ServerMain::loadSettings(QSettings *_settings)
{
    //load ComPort settings
    _settings->beginGroup("/ComPort");
    activeComPort=_settings->value("/TabON", "true").toBool();
    if(activeComPort) activeTabs->append("ComPort");

     _settings->endGroup();

     //load Server settings
      _settings->beginGroup("/Server");
      activeServer=_settings->value("/TabON", "true").toBool();
      if(activeServer) activeTabs->append("Server");
      _settings->endGroup();

    //save Aircraft setings
    _settings->beginGroup("/Aircraft");
    activeAircraft=_settings->value("Aircraft/TabON", "true").toBool();

    if(activeAircraft) activeTabs->append("Aircraft");
   _settings->endGroup();


   //load Joystick settings
    _settings->beginGroup("/Joystick");
   activeJoy=_settings->value("/TabON", "true").toBool();

   if(activeJoy) activeTabs->append("Joystick");
   _settings->endGroup();


  return true;

}

void T10ServerMain::writeSettings()
{

    settings->beginGroup("/ComPort");
    settings->setValue("/TabON",activeComPort);
    //save ComPort settings
    settings->endGroup();

    settings->beginGroup("/Aircraft");
    settings->setValue("/TabON",activeAircraft);
    //save Aircraft setings
    settings->endGroup();

    settings->beginGroup("/Joystick");
    //save Joystick settings
    settings->setValue("/TabON",activeJoy);

    settings->endGroup();

    settings->beginGroup("/Server");
    //save Server settings
    settings->setValue("/TabON",activeServer);

    settings->endGroup();

}

void T10ServerMain::createMenuAndToolBar()
{
    iconsToolBar=new QToolBar("Main ToolBar",this);
     actionComPort=new QAction(QIcon(":/resources/icons/plug_in.svg"),"ComPort",this);
    iconsToolBar->addAction(actionComPort);
    actionComPort->setCheckable(true);
    actionComPort->setToolTip("Подключить COM порт");
    connect (this->actionComPort,SIGNAL(toggled(bool)),this,SLOT(slotComPortActionToggled(bool)));

    actionServer=new QAction(QIcon(":/resources/icons/computer.svg"),"Start/Stop",this);
   iconsToolBar->addAction(actionServer);
   actionServer->setCheckable(true);
   actionServer->setToolTip("Включить сервер");
   connect (this->actionServer,SIGNAL(toggled(bool)),this,SLOT(slotServerActionToggled(bool)));

   actionAircraft=new QAction(QIcon(":/resources/icons/airplane.svg"),"Aircraft",this);
  iconsToolBar->addAction(actionAircraft);
  actionAircraft->setCheckable(true);
  actionAircraft->setToolTip("Включить моделирование");
  connect (this->actionAircraft,SIGNAL(toggled(bool)),this,SLOT(slotAircraftActionToggled(bool)));

  actionJoystick=new QAction(QIcon(":/resources/icons/joystick.svg"),"Joystick",this);
 iconsToolBar->addAction(actionJoystick);
 actionJoystick->setCheckable(true);
 actionJoystick->setToolTip("Подключить джойстик");
 connect (this->actionJoystick,SIGNAL(toggled(bool)),this,SLOT(slotJoystickActionToggled(bool)));
 iconsToolBar->addSeparator();
    this->addToolBar(iconsToolBar);
 //создание статусбара
 main_statusbar=new QStatusBar(this);
// main_statusbar->set
}

bool T10ServerMain::createTabs()
{
    for(int i=0;i<activeTabs->size();i++)
    {
    main_tab_wgt->addTab(new QLabel(activeTabs->at(i),main_tab_wgt),activeTabs->at(i));

    }
    if (main_tab_wgt->count()>0)
            return true;
    else
    return false;
}

void T10ServerMain::closeEvent(QCloseEvent *e)
{
    if (QMessageBox::question(this, tr("T10_Server"),
                              tr("Are you sure you want to exit?"),
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::No) == QMessageBox::Yes)
    {
//       this->hide();
        this->writeSettings();
                 }
    else
        e->ignore();
}

void T10ServerMain::slotServerActionToggled(bool arg)
{
    if (arg)
    {
        actionServer->setToolTip("Включить сервер");

        qDebug()<<"Server connected";
    }
    else
    {
        actionServer->setToolTip("Выключить сервер");
        qDebug()<<"Server disconnected";
    }
}

void T10ServerMain::slotComPortActionToggled(bool arg)
{
    if (arg)
    {
        actionComPort->setToolTip("Подключить COM порт");
        qDebug()<<"COMport connected";
    }
    else
    {
        actionComPort->setToolTip("Отключить COM порт");
        qDebug()<<"COMport disconnected";
    }
}

void T10ServerMain::slotAircraftActionToggled(bool arg)
{
    if (arg)
    {
        actionAircraft->setToolTip("Включить моделирование");
        qDebug()<<"Simulation started";
    }
    else
    {
        actionAircraft->setToolTip("Остановить моделирование");
        qDebug()<<"Simulation stopped";
    }
}

void T10ServerMain::slotJoystickActionToggled(bool arg)
{

    if (arg)
    {
        actionAircraft->setToolTip("Подключить джойстик");
        qDebug()<<"Joystick connected";
    }
    else
    {
        actionAircraft->setToolTip("Отключить джойстик");
        qDebug()<<"Joystick disconnected";
    }
}
