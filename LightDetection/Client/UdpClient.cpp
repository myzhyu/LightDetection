#include "UdpClient.h"



UdpClient::UdpClient(std::string strIP, int iPort)
{
    m_strIP = strIP;
    m_iPort = iPort;
    m_bInitSuccess = true;
    m_bIsOffline = false;
    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
    {
        // WSAStartup failed
        m_bInitSuccess = false;
        return;
    }
    m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sock == SOCKET_ERROR)
    {
        // create socket failed
        m_bInitSuccess = false;
        return;
    }
    // ����һ�������ַ��Ϣ�Ľṹ�壬����������ĵ�ַ��Ϣ
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(m_iPort);
    m_serverAddr.sin_addr.S_un.S_addr = inet_addr(m_strIP.c_str());
}


UdpClient::~UdpClient()
{
    // �ر�SOCKET����
    // closesocket(m_sock);
    // �������绷��
    // WSACleanup();
}

int UdpClient::sentMessage(char strMessage[105])
{
    if (m_bInitSuccess == false) // init fail
    {
        return 1;
    }
    if (m_bIsOffline)
    {
        return 3;
    }
    int iSentData = sendto(m_sock, strMessage, strlen(strMessage), 0, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));
    if (iSentData == 0) // send fail
    {
        return 2;
    }
    return 0;
}

void UdpClient::setIsOffline(bool bIsOffline)
{
    m_bIsOffline = bIsOffline;
}
