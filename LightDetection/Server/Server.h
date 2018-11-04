#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"
#include "UdpServer.h"
#include "qtimer.h"
#include "LightStatus.h"
#include <map>

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = Q_NULLPTR);
    ~Server();

private:
    Ui::ServerClass ui;
    int m_iPort; // 记录端口号
    UdpServer m_sock;
    QTimer *m_pQTimerReceive; // 消息接收定时器
    QTimer *m_pQTimerHeartbeat; // 心跳包检查定时器
    int m_iMessageCount; // 记录消息条数
    int m_iClientNumber; // 记录客户端数目
    std::map<int, LightStatus> m_mLightsStatus;

private slots:
    void pushButton_start_slot();
    void lineEdit_port_slot(QString strText);
    void QTimerReceive_slot();
    void QTimerHeartbeat_slot();
    void spinBox_clientNumber_slot(int iClient);
};
