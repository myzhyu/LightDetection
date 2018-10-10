#include "Server.h"
#include <string>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_iPort = 80;

    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(pushButton_start_slot()));
    // connect(ui.lineEdit_port, SIGNAL(textChanged(QString)), this, SLOT(lineEdit_port_slot(QString)));
}

void Server::pushButton_start_slot()
{
    QString strPort = ui.lineEdit_port->text();
    m_iPort = strPort.toInt();
    if (m_iPort == 0)
    {
        ui.statusBar->showMessage(u8"��������ȷ�Ķ˿�!");
    }
    m_sock = UdpServer(m_iPort);
    if (m_sock.startBind() == false)
    {
        ui.statusBar->showMessage(u8"Init or Bind Error!");
    }

    ui.statusBar->showMessage(u8"����������������˿�:" + strPort);
}

void Server::lineEdit_port_slot(QString strText)
{
    m_iPort = strText.toInt();
    ui.statusBar->showMessage(u8"�����˿��Ѹ�Ϊ��" + QString::number(m_iPort));
}
