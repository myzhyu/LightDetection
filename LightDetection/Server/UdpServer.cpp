#include "UdpServer.h"
#include <winsock2.h>
#include <Windows.h>


UdpServer::UdpServer(int iPort)
{
    m_iPort = iPort;
    m_bInitSuccess = true;
    // ��ʼ�����绷��
    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
    {
        m_bInitSuccess = false;
    }
    // ����һ��UDP��socket
    m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sock == SOCKET_ERROR)
    {
        m_bInitSuccess = false;
    }
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(m_iPort);
    m_serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
}


UdpServer::~UdpServer()
{
}


bool UdpServer::startBind()
{
    if (m_bInitSuccess)
    {
        if (bind(m_sock, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr)) != SOCKET_ERROR)
        {
            return true;
        }
    }
    return false;
}


/*
// Introduction:��ȡ���յ���Ϣ
// Param pClientIP:���ؿͻ���IP
// Param pMessage:���ؽ��յ���Ϣ
// Return:�ɹ�������Ϣ����,ʧ�ܷ���-1
*/
int UdpServer::getMessage(char * pClientIP, char * pMessage)
{
    char buf[100];
    //����ڵ����Ϣ����������ͻ��˵�������Ϣ
    SOCKADDR_IN clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    int clientAddrLen = sizeof(SOCKADDR);
    //���տͻ��˷���������
    int ret = recvfrom(m_sock, buf, 100, 0, (SOCKADDR*)&clientAddr, &clientAddrLen);
    *pClientIP = *inet_ntoa(clientAddr.sin_addr);
    *pMessage = *buf;
    // printf("Recv msg: %s from IP:[%s] Port:[%d]\n", buf, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    return ret;
}
