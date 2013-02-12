#ifndef JOYWIDGET_H
#define JOYWIDGET_H

#include <QtGui>
#include <Joystick/v_joystick_adapter.h>

class JoyWidget : public QWidget
{
    Q_OBJECT
private:
    QGridLayout * m_grLayout;
    QComboBox * cmbxJoy;
    VJoystickAdapter * joystick;
    QStringList JoyList;
    QSettings * settings;
public:
    explicit JoyWidget(QWidget *parent = 0);
    ~JoyWidget();
    void setSettings(QSettings * _settings);
    void createJoystick();
    bool rescanJoystick();

    QLabel * labelJoystickStatus;
signals:
    void JoyConnected(bool con);
public slots:
    void slotJoyConnect(bool arg);
};

#endif // JOYWIDGET_H
