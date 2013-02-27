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
    QWidget * joyButtons;
    VJoystickAdapter * joystick;
    QStringList JoyList;
    QToolButton * rescanButton;
    QSettings * settings;
    QPushButton * createButton(const int num);

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
    void joyButtonChecked(int button_num,bool state);
    void joyButtonToggled(bool arg);
    void slotJoyConnect(bool arg);
    void rescanJoystick();
};

#endif // JOYWIDGET_H
