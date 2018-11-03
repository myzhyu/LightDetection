#pragma once

#include <winsock2.h>
#include <Windows.h>

class UdpServer
{
public:
    UdpServer(int iPort=8008);
    ~UdpServer();
    bool startBind(); // ��ʼ����
    int getMessage(char strClientIP[20], char strMessage[105]); // ��ȡ���յ�IP����Ϣ
private:
    int m_iPort; // �˿ں�
    WSADATA m_wsa;
    SOCKET m_sock;
    SOCKADDR_IN m_serverAddr; // ��������ַ��Ϣ
    bool m_bInitSuccess;
    struct timeval m_timeout; // ������Ϣ���ճ�ʱʱ��
};

