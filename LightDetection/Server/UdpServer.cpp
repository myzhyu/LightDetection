#include "UdpServer.h"
#include <winsock2.h>
#include <Windows.h>


UdpServer::UdpServer(int iPort)
{
    m_iPort = iPort;
    m_bInitSuccess = true;
    // 初始化网络环境
    if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0)
    {
        m_bInitSuccess = false;
        // return;
    }
    // 建立一个UDP的socket
    m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sock == SOCKET_ERROR)
    {
        m_bInitSuccess = false;
        // return;
    }
    // 设置1us超时时间
    m_timeout.tv_sec = 0;
    m_timeout.tv_usec = 1;
    int iTimeout = 1;
    if (setsockopt(m_sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&iTimeout, sizeof(int)) == -1)
    {
        m_bInitSuccess = false;
        // return;
    }
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(m_iPort);
    m_serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    
}


UdpServer::~UdpServer()
{
    // 关闭SOCKET连接
    // closesocket(m_sock);
    // 清理网络环境
    // WSACleanup();
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
// Introduction:获取接收的消息
// Param pClientIP:返回客户端IP
// Param pMessage:返回接收的消息
// Return:成功返回消息长度,失败返回-1
*/
int UdpServer::getMessage(char strClientIP[20], char strMessage[105])
{
    char buf[105] = { 0 };
    //网络节点的信息，用来保存客户端的网络信息
    SOCKADDR_IN clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    int clientAddrLen = sizeof(SOCKADDR);
    //接收客户端发来的数据
    int ret = recvfrom(m_sock, buf, 100, 0, (SOCKADDR*)&clientAddr, &clientAddrLen);
    // strClientIP = *inet_ntoa(clientAddr.sin_addr);
    // strMessage = *buf;
    strcpy(strClientIP, inet_ntoa(clientAddr.sin_addr));
    strcpy(strMessage, buf);
    // printf("Recv msg: %s from IP:[%s] Port:[%d]\n", buf, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    return ret;
}

