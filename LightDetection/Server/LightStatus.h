#pragma once

#include <string>

class LightStatus
{
public:
    LightStatus();
    ~LightStatus();

    void setIsSwitchOn(bool bSwitchOn);
    bool getIsSwitchOn();

    bool getIsOnline();
    void setLostHeartbeat();
    void clearLostHeartbeat();

    void setVoltage(int iVoltage);
    int getVoltage();

    void setCurrent(double dCurrent);
    double getCurrent();

    void setIP(char cIP[20]);
    void getIP(char cIP[20]);

private:
    bool m_bSwitchOn; // ¿ª¹Ø×´Ì¬
    bool m_bOnline;
    int m_iVoltage;
    double m_dCurrent;
    int m_iLostHeartbeatCount;
    char m_cIP[20];
};

