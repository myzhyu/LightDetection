#pragma once

#include <winsock2.h>
#include <Windows.h>

class UdpServer
{
public:
    UdpServer(int iPort=8008);
    ~UdpServer();
    bool startBind(); // 开始监听
    int getMessage(char strClientIP[20], char strMessage[105]); // 获取接收的IP及消息
private:
    int m_iPort; // 端口号
    WSADATA m_wsa;
    SOCKET m_sock;
    SOCKADDR_IN m_serverAddr; // 服务器地址信息
    bool m_bInitSuccess;
    struct timeval m_timeout; // 设置消息接收超时时间
};

