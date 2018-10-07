#include "Server.h"
#include <string>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_iPort = 80;

    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(button_start_slot()));
}

void Server::button_start_slot()
{
    QString strPort = ui.lineEdit_port->text();
    m_iPort = strPort.toInt();
    ui.statusBar->showMessage(u8"服务端启动，监听端口" + strPort);
}


