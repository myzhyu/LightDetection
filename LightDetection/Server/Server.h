#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"
#include "UdpServer.h"
#include "qtimer.h"

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
    QTimer *m_pQTimerReceive; // 定时器

private slots:
    void pushButton_start_slot();
    void lineEdit_port_slot(QString strText);
    void QTimerRecv_slot();
};
