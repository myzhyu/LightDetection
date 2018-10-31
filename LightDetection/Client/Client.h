#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Client.h"
#include "UdpClient.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);

private:
    Ui::ClientClass ui;
    std::string m_strServerIP;
    int m_iPort;
    bool m_bLightOn;
    bool m_bLightOffline;
    int m_iVoltage;
    double m_dCurrent;
    int m_iID;
    std::string m_strID;
    UdpClient m_sock;

private slots:
    void radioButton_LightOn_slot();
    void radioButton_LightOff_slot();
    void radioButton_OfflineYes_slot();
    void radioButton_OfflineNo_slot();
    void pushButton_Login_slot();
    void spinBox_Voltage_slot(int iVoltage);
    void doubleSpinBox_Current_slot(double dCurrent);
};



