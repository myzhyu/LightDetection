#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include "UdpClient.h"
#include "qtimer.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);
    ~Client();

private:
    void getID();

    Ui::ClientClass ui;
    std::string m_strServerIP;
    int m_iPort;
    bool m_bLightOn;
    bool m_bLightOffline;
    int m_iVoltage;
    double m_dCurrent;
    char m_cID[3] = { 0 };
    UdpClient m_sock;
    QTimer *m_pQTimerHeartbeat; // 心跳包定时器

private slots:
    void radioButton_LightOn_slot();
    void radioButton_LightOff_slot();
    void radioButton_OfflineYes_slot();
    void radioButton_OfflineNo_slot();
    void pushButton_Login_slot();
    void spinBox_Voltage_slot(int iVoltage = 220);
    void doubleSpinBox_Current_slot(double dCurrent = 2.0);
    void QTimerHeartbeat_slot();
};



