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
    QToolButton * rescanButton;
    QSettings * settings;
public:
    explicit JoyWidget(QWidget *parent = 0);
    ~JoyWidget();
    void setSettings(QSettings * _settings);
    void createJoystick();
    bool joyAvailable();
    VJoystickAdapter * getJoystick();

    QLabel * labelJoystickStatus;
signals:
    void JoyConnected(bool con);
public slots:
    void slotJoyConnect(bool arg);
    void rescanJoystick();
};

#endif // JOYWIDGET_H
