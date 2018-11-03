#include "LightStatus.h"



LightStatus::LightStatus()
{
    m_bSwitchOn = false;
    m_bOnline = false;
    m_iVoltage = 0;
    m_dCurrent = 0;
    m_iLostHeartbeatCount = 99;
    m_cIP[0] = '\0';
    strcat(m_cIP, "null");
}


LightStatus::~LightStatus()
{

}

void LightStatus::setIsSwitchOn(bool bSwitchOn)
{
    m_bSwitchOn = bSwitchOn;
}

bool LightStatus::getIsSwitchOn()
{
    return m_bSwitchOn;
}

bool LightStatus::getIsOnline()
{
    if (m_iLostHeartbeatCount > 3)
    {
        m_bOnline = false;
    }
    else
    {
        m_bOnline = true;
    }
    return m_bOnline;
}

void LightStatus::setVoltage(int iVoltage)
{
    m_iVoltage = iVoltage;
}

int LightStatus::getVoltage()
{
    return m_iVoltage;
}

void LightStatus::setCurrent(double dCurrent)
{
    m_dCurrent = dCurrent;
}

double LightStatus::getCurrent()
{
    return m_dCurrent;
}

void LightStatus::setLostHeartbeat()
{
    m_iLostHeartbeatCount++;
}

void LightStatus::clearLostHeartbeat()
{
    m_iLostHeartbeatCount = 0;
}

void LightStatus::getIP(char cIP[20])
{
    strcpy(cIP, m_cIP);
    return ;
}

void LightStatus::setIP(char cIP[20])
{
    strcpy(m_cIP, cIP);
}
