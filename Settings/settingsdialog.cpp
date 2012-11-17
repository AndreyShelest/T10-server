#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    QStringList joyList=VJoystickAdapter::getAvaliableJoystickName();
    if (joyList.count()>0){
    for (int i=0;i<joyList.count();i++)
    {
        ui->comboBox->setItemText(i,joyList[i]);
    }
    }
    else ui->comboBox->setItemText(0,"no joysticks");


}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_clicked(QAbstractButton *button)
{

    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                     QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("Joystick/name", ui->comboBox->currentText());
}
