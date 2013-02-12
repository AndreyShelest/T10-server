#include "t10tray.h"

t10tray::t10tray(QWidget *parent)
{
    createIconGroupBox();
    createMessageGroupBox();

    parentWgt=parent;
    iconLabel->setMinimumWidth(durationLabel->sizeHint().width());

    createActions();
    createTrayIcon();

    connect(showMessageButton, SIGNAL(clicked()), parentWgt, SLOT(showMessage()));
    connect(showIconCheckBox, SIGNAL(toggled(bool)),
            trayIcon, SLOT(setVisible(bool)));
    connect(iconComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setIcon(int)));
    connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(iconGroupBox);
    mainLayout->addWidget(messageGroupBox);
    setLayout(mainLayout);

    iconComboBox->setCurrentIndex(1);
    trayIcon->show();

    setWindowTitle(tr("Systray"));
    resize(400, 300);
}
void t10tray::setVisible(bool visible)
{
    minimizeAction->setEnabled(parentWgt->isVisible());
    maximizeAction->setEnabled(!parentWgt->isMaximized());
    restoreAction->setEnabled(parentWgt->isMaximized() || !visible);

parentWgt->setVisible(visible);

}

bool t10tray::isVisibleTray()
{
    return trayIcon->isVisible();
}


void t10tray::setIcon(int index)
{
    QIcon icon = iconComboBox->itemIcon(index);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip(iconComboBox->itemText(index));
}

void t10tray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1)
                                      % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage();
        break;
    default:
        ;
    }
}

void t10tray::showMessage()
{
    QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(
            typeComboBox->itemData(typeComboBox->currentIndex()).toInt());
    trayIcon->showMessage(titleEdit->text(), bodyEdit->toPlainText(), icon,
                          durationSpinBox->value() * 1000);
}

void t10tray::messageClicked()
{
    QMessageBox::information(0, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void t10tray::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));

    iconLabel = new QLabel("Icon:");

    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/resources/icons/appIcon48.png"), tr("Bad"));
    iconComboBox->addItem(QIcon(":resources/icons/Qt-logo.svg"), tr("Heart"));
    iconComboBox->addItem(QIcon(":/images/trash.svg"), tr("Trash"));

    showIconCheckBox = new QCheckBox(tr("Show icon"));
    showIconCheckBox->setChecked(true);

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconLabel);
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconLayout->addWidget(showIconCheckBox);
    iconGroupBox->setLayout(iconLayout);
}

void t10tray::createMessageGroupBox()
{
    messageGroupBox = new QGroupBox(tr("Balloon Message"));

    typeLabel = new QLabel(tr("Type:"));

    typeComboBox = new QComboBox;
    typeComboBox->addItem(tr("None"), QSystemTrayIcon::NoIcon);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxInformation), tr("Information"),
            QSystemTrayIcon::Information);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxWarning), tr("Warning"),
            QSystemTrayIcon::Warning);
    typeComboBox->addItem(style()->standardIcon(
            QStyle::SP_MessageBoxCritical), tr("Critical"),
            QSystemTrayIcon::Critical);
    typeComboBox->setCurrentIndex(1);

    durationLabel = new QLabel(tr("Duration:"));

    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(5, 60);
    durationSpinBox->setSuffix(" s");
    durationSpinBox->setValue(15);

    durationWarningLabel = new QLabel(tr("(some systems might ignore this "
                                         "hint)"));
    durationWarningLabel->setIndent(10);

    titleLabel = new QLabel(tr("Title:"));

    titleEdit = new QLineEdit(tr("Cannot connect to network"));

    bodyLabel = new QLabel(tr("Body:"));

    bodyEdit = new QTextEdit;
    bodyEdit->setPlainText(tr("Don't believe me. Honestly, I don't have a "
                              "clue.\nClick this balloon for details."));

    showMessageButton = new QPushButton(tr("Show Message"));
    showMessageButton->setDefault(true);

    QGridLayout *messageLayout = new QGridLayout;
    messageLayout->addWidget(typeLabel, 0, 0);
    messageLayout->addWidget(typeComboBox, 0, 1, 1, 2);
    messageLayout->addWidget(durationLabel, 1, 0);
    messageLayout->addWidget(durationSpinBox, 1, 1);
    messageLayout->addWidget(durationWarningLabel, 1, 2, 1, 3);
    messageLayout->addWidget(titleLabel, 2, 0);
    messageLayout->addWidget(titleEdit, 2, 1, 1, 4);
    messageLayout->addWidget(bodyLabel, 3, 0);
    messageLayout->addWidget(bodyEdit, 3, 1, 2, 4);
    messageLayout->addWidget(showMessageButton, 5, 4);
    messageLayout->setColumnStretch(3, 1);
    messageLayout->setRowStretch(4, 1);
    messageGroupBox->setLayout(messageLayout);
}

void t10tray::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), parentWgt);
    connect(minimizeAction, SIGNAL(triggered()), parentWgt, SLOT(hide()));

    maximizeAction = new QAction(tr("Ma&ximize"), parentWgt);
    connect(maximizeAction, SIGNAL(triggered()), parentWgt, SLOT(showMaximized()));

    restoreAction = new QAction(tr("&Restore"), parentWgt);
    connect(restoreAction, SIGNAL(triggered()), parentWgt, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), parentWgt);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void t10tray::createTrayIcon()
{
    trayIconMenu = new QMenu(parentWgt);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(parentWgt);
    trayIcon->setContextMenu(trayIconMenu);

}
