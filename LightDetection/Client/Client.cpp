#include "Client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_strServerIP = "127.0.0.1";
    m_iPort = 80;
    m_bLightOn = false;
    m_bLightOffline = false;
    m_iVoltage = 220;
    m_dCurrent = 2;
    m_iID = 0;

    connect(ui.radioButton_LightOn, SIGNAL(clicked()), this, SLOT(radioButton_LightOn_slot()));
    connect(ui.radioButton_LightOff, SIGNAL(clicked()), this, SLOT(radioButton_LightOff_slot()));
    connect(ui.radioButton_OfflineYes, SIGNAL(clicked()), this, SLOT(radioButton_OfflineYes_slot()));
    connect(ui.radioButton_OfflineNo, SIGNAL(clicked()), this, SLOT(radioButton_OfflineNo_slot()));
    connect(ui.pushButton_Login, SIGNAL(clicked()), this, SLOT(pushButton_Login_slot()));
    connect(ui.spinBox_Voltage, SIGNAL(valueChanged(int)), this, SLOT(spinBox_Voltage_slot(int)));
    connect(ui.doubleSpinBox_Current, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinBox_Current_slot(double)));
}

void Client::radioButton_LightOn_slot()
{
    ui.radioButton_LightOff->setChecked(false);
    m_bLightOn = true;
}

void Client::radioButton_LightOff_slot()
{
    ui.radioButton_LightOn->setChecked(false);
    m_bLightOn = false;
}

void Client::radioButton_OfflineYes_slot()
{
    ui.radioButton_OfflineNo->setChecked(false);
    m_bLightOffline = true;
}

void Client::radioButton_OfflineNo_slot()
{
    ui.radioButton_OfflineYes->setChecked(false);
    m_bLightOffline = false;
}

void Client::pushButton_Login_slot()
{
    m_iID = ui.lineEdit_id->text().toInt();
    m_iPort = ui.lineEdit_serverPort->text().toInt();
    ui.statusBar->showMessage(u8"µÇÂ½");
}

void Client::spinBox_Voltage_slot(int iVoltage)
{
    m_iVoltage = iVoltage;
    // ui.statusBar->showMessage(QString::number(iVoltage));
}

void Client::doubleSpinBox_Current_slot(double dCurrent)
{
    m_dCurrent = dCurrent;
    // ui.statusBar->showMessage(QString::number(dCurrent));
}
