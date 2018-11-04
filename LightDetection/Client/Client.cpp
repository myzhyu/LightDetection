#include "Client.h"
#include <string>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_strServerIP = "127.0.0.1";
    m_iPort = 8008;
    m_bLightOn = false;
    m_bLightOffline = false;
    m_iVoltage = 220;
    m_dCurrent = 2;
    m_cID[0] = '0';
    m_pQTimerHeartbeat = new QTimer(this);

    connect(ui.radioButton_LightOn, SIGNAL(clicked()), this, SLOT(radioButton_LightOn_slot()));
    connect(ui.radioButton_LightOff, SIGNAL(clicked()), this, SLOT(radioButton_LightOff_slot()));
    connect(ui.radioButton_OfflineYes, SIGNAL(clicked()), this, SLOT(radioButton_OfflineYes_slot()));
    connect(ui.radioButton_OfflineNo, SIGNAL(clicked()), this, SLOT(radioButton_OfflineNo_slot()));
    connect(ui.pushButton_Login, SIGNAL(clicked()), this, SLOT(pushButton_Login_slot()));
    connect(ui.spinBox_Voltage, SIGNAL(valueChanged(int)), this, SLOT(spinBox_Voltage_slot(int)));
    connect(ui.doubleSpinBox_Current, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinBox_Current_slot(double)));
    connect(m_pQTimerHeartbeat, SIGNAL(timeout()), this, SLOT(QTimerHeartbeat_slot()));
}

Client::~Client()
{
    delete m_pQTimerHeartbeat;
}

void Client::getID()
{
    std::string strID = ui.lineEdit_id->text().toStdString();
    if (strID.size() == 0 || strID.size() > 2)
    {
        ui.statusBar->showMessage(u8"IDÉèÖÃ´íÎó!");
        return;
    }
    if (strID.size() == 1)
    {
        m_cID[0] = '0';
        m_cID[1] = '\0';
    }
    else if (strID.size() == 2)
    {
        m_cID[0] = '\0';
    }
    strcat(m_cID, strID.c_str());
}

void Client::radioButton_LightOn_slot()
{
    ui.radioButton_LightOff->setChecked(false);
    m_bLightOn = true;
    getID();
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Switch-On");
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
    }
    else
    {
        ui.statusBar->showMessage(u8"send Switch-On");
    }
}

void Client::radioButton_LightOff_slot()
{
    ui.radioButton_LightOn->setChecked(false);
    m_bLightOn = false;
    getID();
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Switch-Off");
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
    }
    else
    {
        ui.statusBar->showMessage(u8"send Switch-Off");
    }
}

void Client::radioButton_OfflineYes_slot()
{
    ui.radioButton_OfflineNo->setChecked(false);
    m_bLightOffline = true;
    m_sock.setIsOffline(m_bLightOffline);
}

void Client::radioButton_OfflineNo_slot()
{
    ui.radioButton_OfflineYes->setChecked(false);
    m_bLightOffline = false;
    m_sock.setIsOffline(m_bLightOffline);
}

void Client::pushButton_Login_slot()
{
    getID();
    m_iPort = ui.lineEdit_serverPort->text().toInt();
    m_strServerIP = ui.lineEdit_serverIP->text().toStdString();
    m_sock = UdpClient(m_strServerIP, m_iPort);
    m_sock.setIsOffline(m_bLightOffline);
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Login");
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
        return;
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
        return;
    }
    else
    {
        ui.statusBar->showMessage(u8"µÇÂ½");
        spinBox_Voltage_slot();
        doubleSpinBox_Current_slot();
        if (m_bLightOn)
        {
            radioButton_LightOn_slot();
        }
        else
        {
            radioButton_LightOff_slot();
        }
    }
    m_pQTimerHeartbeat->start(1000);
}

void Client::spinBox_Voltage_slot(int iVoltage)
{
    iVoltage = ui.spinBox_Voltage->value();
    m_iVoltage = iVoltage;
    char cVoltage[4] = { 0 };
    if (m_iVoltage < 100)
    {
        cVoltage[0] = '0';
    }
    if (m_iVoltage < 10)
    {
        cVoltage[1] = '0';
    }
    strcat(cVoltage, ui.spinBox_Voltage->text().toStdString().c_str());

    getID();
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Voltage-");
    strcat(buf, cVoltage);
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
    }
    else
    {
        ui.statusBar->showMessage(u8"Voltage");
    }
    // ui.statusBar->showMessage(QString::number(iVoltage));
}

void Client::doubleSpinBox_Current_slot(double dCurrent)
{
    dCurrent = ui.doubleSpinBox_Current->value();
    m_dCurrent = dCurrent;
    char cCurrent[6] = { 0 };
    if (m_dCurrent < 10)
    {
        cCurrent[0] = '0';
    }
    strcat(cCurrent, ui.doubleSpinBox_Current->text().toStdString().c_str());
    getID();
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Current-");
    strcat(buf, cCurrent);
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
    }
    else
    {
        ui.statusBar->showMessage(u8"Current");
    }
    // ui.statusBar->showMessage(QString::number(dCurrent));
}

void Client::QTimerHeartbeat_slot()
{
    getID();
    char buf[100] = { 0 };
    strcpy(buf, m_cID);
    strcat(buf, "-Heartbeat");
    int iSentRetval = m_sock.sentMessage(buf);
    if (iSentRetval == 1)
    {
        ui.statusBar->showMessage(u8"init fail");
    }
    else if (iSentRetval == 2)
    {
        ui.statusBar->showMessage(u8"send fail");
    }
    else
    {
        ui.statusBar->showMessage(u8"Heartbeat");
    }
}
