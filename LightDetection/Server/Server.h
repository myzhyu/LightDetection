#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"
#include "UdpServer.h"

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = Q_NULLPTR);

private:
    Ui::ServerClass ui;
    int m_iPort; // ¼ÇÂ¼¶Ë¿ÚºÅ
    UdpServer m_sock;

private slots:
    void pushButton_start_slot();
    void lineEdit_port_slot(QString strText);
};
