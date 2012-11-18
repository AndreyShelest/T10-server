/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Nov 18 14:38:47 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSettings;
    QAction *actionServer;
    QAction *actionCom_port;
    QAction *actionShowDataFromCom;
    QAction *actionShow_data_from_aircraft_model;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QAction *actionShow_info_about_clients;
    QAction *actionJoystick;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_server;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton_7;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_4;
    QLabel *label_13;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_2;
    QLabel *labelClientsConnected;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_5;
    QLabel *labelClients;
    QPushButton *pBsimulate;
    QListWidget *listWidget_Log;
    QListWidget *listWidget_peerList;
    QListWidget *listWidget;
    QWidget *tab_com;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox_comPort;
    QGridLayout *gridLayout;
    QLabel *label_comPortName;
    QLineEdit *lineEditPort;
    QPushButton *pushButton_comPortReconnect;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_14;
    QListWidget *list_toCom;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_2;
    QWidget *tab_joy;
    QWidget *widget1;
    QGroupBox *groupBox_netServer;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QWidget *widget_4;
    QGroupBox *groupBox_joystick;
    QComboBox *comboBox;
    QToolButton *toolButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *tab_settings;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(709, 514);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSettings->setCheckable(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icons/gears.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon);
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionServer->setCheckable(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/icons/computer.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionServer->setIcon(icon1);
        actionCom_port = new QAction(MainWindow);
        actionCom_port->setObjectName(QString::fromUtf8("actionCom_port"));
        actionCom_port->setCheckable(true);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/icons/plug_in.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionCom_port->setIcon(icon2);
        actionShowDataFromCom = new QAction(MainWindow);
        actionShowDataFromCom->setObjectName(QString::fromUtf8("actionShowDataFromCom"));
        actionShowDataFromCom->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/icons/com.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShowDataFromCom->setIcon(icon3);
        actionShow_data_from_aircraft_model = new QAction(MainWindow);
        actionShow_data_from_aircraft_model->setObjectName(QString::fromUtf8("actionShow_data_from_aircraft_model"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/icons/airplane.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_data_from_aircraft_model->setIcon(icon4);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/icons/Monkey.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/icons/Qt-logo.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_Qt->setIcon(icon6);
        actionShow_info_about_clients = new QAction(MainWindow);
        actionShow_info_about_clients->setObjectName(QString::fromUtf8("actionShow_info_about_clients"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/icons/community.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_info_about_clients->setIcon(icon7);
        actionJoystick = new QAction(MainWindow);
        actionJoystick->setObjectName(QString::fromUtf8("actionJoystick"));
        actionJoystick->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/icons/joystick.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionJoystick->setIcon(icon8);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(500, 400));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tab_server = new QWidget();
        tab_server->setObjectName(QString::fromUtf8("tab_server"));
        widget = new QWidget(tab_server);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(170, 0, 302, 151));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(1, -1, -1, -1);
        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        pushButton_7 = new QPushButton(page);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(50, 230, 131, 23));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/icons/disapprove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon9);
        pushButton_7->setIconSize(QSize(20, 20));
        layoutWidget = new QWidget(page);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, -10, 291, 151));
        gridLayout_4 = new QGridLayout(layoutWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 0, 0, 2, 2);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 1, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 1, 2, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_9, 2, 1, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 2, 2, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_10, 3, 1, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 3, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 4, 1, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_3, 5, 0, 1, 2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_5, 6, 0, 1, 2);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 6, 2, 1, 1);

        stackedWidget->addWidget(page);
        layoutWidget->raise();
        pushButton_7->raise();
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_3 = new QHBoxLayout(page_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));

        horizontalLayout_3->addWidget(widget_2);

        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        labelClientsConnected = new QLabel(tab_server);
        labelClientsConnected->setObjectName(QString::fromUtf8("labelClientsConnected"));
        labelClientsConnected->setGeometry(QRect(83, 2, 16, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        labelClientsConnected->setFont(font);
        layoutWidget1 = new QWidget(tab_server);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 681, 361));
        gridLayout_5 = new QGridLayout(layoutWidget1);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        labelClients = new QLabel(layoutWidget1);
        labelClients->setObjectName(QString::fromUtf8("labelClients"));
        labelClients->setMinimumSize(QSize(65, 0));
        labelClients->setMaximumSize(QSize(65, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Verdana"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        labelClients->setFont(font1);

        gridLayout_5->addWidget(labelClients, 0, 0, 1, 1);

        pBsimulate = new QPushButton(layoutWidget1);
        pBsimulate->setObjectName(QString::fromUtf8("pBsimulate"));

        gridLayout_5->addWidget(pBsimulate, 2, 1, 1, 1);

        listWidget_Log = new QListWidget(layoutWidget1);
        listWidget_Log->setObjectName(QString::fromUtf8("listWidget_Log"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget_Log->sizePolicy().hasHeightForWidth());
        listWidget_Log->setSizePolicy(sizePolicy2);
        listWidget_Log->setMinimumSize(QSize(300, 100));
        listWidget_Log->setMaximumSize(QSize(16777215, 100));
        listWidget_Log->setFrameShape(QFrame::NoFrame);

        gridLayout_5->addWidget(listWidget_Log, 2, 2, 1, 1);

        listWidget_peerList = new QListWidget(layoutWidget1);
        listWidget_peerList->setObjectName(QString::fromUtf8("listWidget_peerList"));
        listWidget_peerList->setMaximumSize(QSize(150, 16777215));
        listWidget_peerList->setFrameShape(QFrame::NoFrame);
        listWidget_peerList->setAutoScroll(true);

        gridLayout_5->addWidget(listWidget_peerList, 1, 0, 2, 1);

        listWidget = new QListWidget(layoutWidget1);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_5->addWidget(listWidget, 1, 1, 1, 1);

        tabWidget->addTab(tab_server, icon1, QString());
        layoutWidget->raise();
        widget->raise();
        labelClientsConnected->raise();
        tab_com = new QWidget();
        tab_com->setObjectName(QString::fromUtf8("tab_com"));
        gridLayout_2 = new QGridLayout(tab_com);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBox_comPort = new QGroupBox(tab_com);
        groupBox_comPort->setObjectName(QString::fromUtf8("groupBox_comPort"));
        sizePolicy.setHeightForWidth(groupBox_comPort->sizePolicy().hasHeightForWidth());
        groupBox_comPort->setSizePolicy(sizePolicy);
        groupBox_comPort->setMaximumSize(QSize(190, 110));
        groupBox_comPort->setFlat(false);
        groupBox_comPort->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_comPort);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_comPortName = new QLabel(groupBox_comPort);
        label_comPortName->setObjectName(QString::fromUtf8("label_comPortName"));

        gridLayout->addWidget(label_comPortName, 0, 0, 1, 1);

        lineEditPort = new QLineEdit(groupBox_comPort);
        lineEditPort->setObjectName(QString::fromUtf8("lineEditPort"));

        gridLayout->addWidget(lineEditPort, 0, 1, 1, 1);

        pushButton_comPortReconnect = new QPushButton(groupBox_comPort);
        pushButton_comPortReconnect->setObjectName(QString::fromUtf8("pushButton_comPortReconnect"));
        pushButton_comPortReconnect->setMinimumSize(QSize(180, 26));
        pushButton_comPortReconnect->setMaximumSize(QSize(180, 26));
        pushButton_comPortReconnect->setIcon(icon2);
        pushButton_comPortReconnect->setIconSize(QSize(20, 20));
        pushButton_comPortReconnect->setCheckable(false);
        pushButton_comPortReconnect->setChecked(false);
        pushButton_comPortReconnect->setAutoRepeat(false);
        pushButton_comPortReconnect->setFlat(false);

        gridLayout->addWidget(pushButton_comPortReconnect, 1, 0, 1, 2);

        pushButton = new QPushButton(groupBox_comPort);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(180, 26));
        pushButton->setMaximumSize(QSize(180, 26));
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(20, 20));

        gridLayout->addWidget(pushButton, 2, 0, 1, 2);


        gridLayout_2->addWidget(groupBox_comPort, 0, 0, 1, 1);

        groupBox = new QGroupBox(tab_com);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        widget_3 = new QWidget(tab_com);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_14 = new QLabel(widget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy3.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy3);

        gridLayout_3->addWidget(label_14, 0, 0, 1, 1);

        list_toCom = new QListWidget(widget_3);
        list_toCom->setObjectName(QString::fromUtf8("list_toCom"));

        gridLayout_3->addWidget(list_toCom, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        pushButton_2 = new QPushButton(widget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_3->addWidget(pushButton_2);


        gridLayout_3->addLayout(verticalLayout_3, 1, 1, 1, 1);


        gridLayout_2->addWidget(widget_3, 1, 0, 1, 2);

        tabWidget->addTab(tab_com, icon2, QString());
        tab_joy = new QWidget();
        tab_joy->setObjectName(QString::fromUtf8("tab_joy"));
        widget1 = new QWidget(tab_joy);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(270, 19, 200, 131));
        widget1->setMinimumSize(QSize(200, 0));
        widget1->setMaximumSize(QSize(200, 16777215));
        groupBox_netServer = new QGroupBox(widget1);
        groupBox_netServer->setObjectName(QString::fromUtf8("groupBox_netServer"));
        groupBox_netServer->setGeometry(QRect(10, 0, 151, 141));
        label = new QLabel(groupBox_netServer);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 20, 46, 13));
        lineEdit_2 = new QLineEdit(groupBox_netServer);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(51, 17, 91, 20));
        label_2 = new QLabel(groupBox_netServer);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(6, 46, 61, 16));
        lineEdit_3 = new QLineEdit(groupBox_netServer);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(63, 44, 81, 20));
        pushButton_5 = new QPushButton(groupBox_netServer);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 70, 131, 23));
        pushButton_5->setIcon(icon1);
        pushButton_5->setIconSize(QSize(20, 20));
        pushButton_6 = new QPushButton(groupBox_netServer);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 100, 131, 23));
        pushButton_6->setIcon(icon);
        pushButton_6->setIconSize(QSize(20, 20));
        widget_4 = new QWidget(tab_joy);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(29, 70, 211, 141));
        groupBox_joystick = new QGroupBox(widget_4);
        groupBox_joystick->setObjectName(QString::fromUtf8("groupBox_joystick"));
        groupBox_joystick->setGeometry(QRect(20, 10, 191, 121));
        comboBox = new QComboBox(groupBox_joystick);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(8, 20, 141, 22));
        comboBox->setEditable(true);
        toolButton_2 = new QToolButton(groupBox_joystick);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(161, 17, 26, 26));
        toolButton_2->setMinimumSize(QSize(26, 26));
        toolButton_2->setMaximumSize(QSize(26, 26));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/resources/icons/refresh.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon10);
        toolButton_2->setIconSize(QSize(20, 20));
        pushButton_3 = new QPushButton(groupBox_joystick);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 60, 180, 26));
        pushButton_3->setMinimumSize(QSize(180, 26));
        pushButton_3->setMaximumSize(QSize(180, 26));
        pushButton_4 = new QPushButton(groupBox_joystick);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 90, 180, 26));
        pushButton_4->setMinimumSize(QSize(180, 26));
        pushButton_4->setMaximumSize(QSize(180, 26));
        pushButton_4->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_4->setIcon(icon);
        pushButton_4->setIconSize(QSize(20, 20));
        tabWidget->addTab(tab_joy, icon8, QString());
        tab_settings = new QWidget();
        tab_settings->setObjectName(QString::fromUtf8("tab_settings"));
        tabWidget->addTab(tab_settings, icon, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 709, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionServer);
        mainToolBar->addAction(actionCom_port);
        mainToolBar->addAction(actionJoystick);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionShow_info_about_clients);
        mainToolBar->addAction(actionShowDataFromCom);
        mainToolBar->addAction(actionShow_data_from_aircraft_model);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSettings);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAbout);
        mainToolBar->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);
        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSettings->setToolTip(QApplication::translate("MainWindow", "Edit settings", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0, QApplication::UnicodeUTF8));
        actionServer->setText(QApplication::translate("MainWindow", "Server", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionServer->setToolTip(QApplication::translate("MainWindow", "Start server", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCom_port->setText(QApplication::translate("MainWindow", "Com port", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCom_port->setToolTip(QApplication::translate("MainWindow", "Connect to COM port", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCom_port->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0, QApplication::UnicodeUTF8));
        actionShowDataFromCom->setText(QApplication::translate("MainWindow", "Show data from COM port", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShowDataFromCom->setToolTip(QApplication::translate("MainWindow", "Show data from COM port", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShow_data_from_aircraft_model->setText(QApplication::translate("MainWindow", "Show data from aircraft model", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "About T-10 server", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbout_Qt->setToolTip(QApplication::translate("MainWindow", "About Qt", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionShow_info_about_clients->setText(QApplication::translate("MainWindow", "Show info about cliebts", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShow_info_about_clients->setToolTip(QApplication::translate("MainWindow", "Show info about connected clients", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionJoystick->setText(QApplication::translate("MainWindow", "Joystick", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionJoystick->setToolTip(QApplication::translate("MainWindow", "Connect to joystick", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_7->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Requested data:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Name:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Bocman", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Ip address:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "192.168.0.100", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Port:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "8054", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "83751", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bytes send:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Bytes recieved:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "4578", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        labelClientsConnected->setStatusTip(QApplication::translate("MainWindow", "Number of connected clients", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelClientsConnected->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        labelClients->setStatusTip(QApplication::translate("MainWindow", "Number of connected clients", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        labelClients->setText(QApplication::translate("MainWindow", "Clients:", 0, QApplication::UnicodeUTF8));
        pBsimulate->setText(QApplication::translate("MainWindow", "Simulate", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "Ailerons", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Rudder", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "Velocity", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "Vertical speed", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "Joystick X", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "Joystick Y", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "Joystick Z", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        tabWidget->setTabText(tabWidget->indexOf(tab_server), QApplication::translate("MainWindow", "Server", 0, QApplication::UnicodeUTF8));
        groupBox_comPort->setTitle(QApplication::translate("MainWindow", "COM port", 0, QApplication::UnicodeUTF8));
        label_comPortName->setText(QApplication::translate("MainWindow", "name:", 0, QApplication::UnicodeUTF8));
        lineEditPort->setText(QApplication::translate("MainWindow", "/dev/ttyUSB0", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_comPortReconnect->setToolTip(QApplication::translate("MainWindow", "Com Port reconnect", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_comPortReconnect->setText(QApplication::translate("MainWindow", "Reconnect", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "COM port settings", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Data transmited to Com Port", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Clear Data", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_com), QApplication::translate("MainWindow", "Com Port", 0, QApplication::UnicodeUTF8));
        groupBox_netServer->setTitle(QApplication::translate("MainWindow", "Net server", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Listen IP:", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("MainWindow", "0.0.0.0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Listen port:", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("MainWindow", "1989", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "Start server", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("MainWindow", "Server settings", 0, QApplication::UnicodeUTF8));
        groupBox_joystick->setTitle(QApplication::translate("MainWindow", "Joystick", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QString());
        pushButton_3->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MainWindow", "Joystick settings", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_joy), QApplication::translate("MainWindow", "Joystick", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_settings), QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
