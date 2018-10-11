#include "Server.h"
#include <string>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_iPort = 80;
    m_pQTimerReceive = new QTimer(this); 

    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(pushButton_start_slot()));
    connect(m_pQTimerReceive, SIGNAL(timeout()), this, SLOT(QTimerRecv_slot()));
    // connect(ui.lineEdit_port, SIGNAL(textChanged(QString)), this, SLOT(lineEdit_port_slot(QString)));
}

void Server::pushButton_start_slot()
{
    QString strPort = ui.lineEdit_port->text();
    m_iPort = strPort.toInt();
    if (m_iPort == 0)
    {
        ui.statusBar->showMessage(u8"请设置正确的端口!");
    }
    m_sock = UdpServer(m_iPort);
    if (m_sock.startBind() == false)
    {
        ui.statusBar->showMessage(u8"Init or Bind Error!");
    }
    m_pQTimerReceive->start(50); // 定时器启动，间隔50ms
    ui.statusBar->showMessage(u8"服务端启动，监听端口:" + strPort);
}

Server::~Server()
{
    delete m_pQTimerReceive;
}

void Server::lineEdit_port_slot(QString strText)
{
    m_iPort = strText.toInt();
    ui.statusBar->showMessage(u8"监听端口已改为：" + QString::number(m_iPort));
}

void Server::QTimerRecv_slot()
{
    char ClientIP[20];
    char Message[105];
    int iMessageLength = m_sock.getMessage(ClientIP, Message);
    if (iMessageLength > 0)
    {
        ;
    }
}
