#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>

class UdpClient
{
public:
    UdpClient(std::string strIP = "127.0.0.1", int iPort = 8008);
    ~UdpClient();
    int sentMessage(std::string strMessage);

private:
    std::string m_strIP;
    int m_iPort;
    int m_iID;
    WSADATA m_wsa;
    bool m_bInitSuccess;
    SOCKET m_sock;
    SOCKADDR_IN m_serverAddr; // 服务器地址信息
};

