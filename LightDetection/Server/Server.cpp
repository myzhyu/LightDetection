#include "Server.h"
#include <string>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_iPort = 8008;
    m_pQTimerReceive = new QTimer(this); 
    m_iMessageCount = 0;
    m_iClientNumber = 10;
    spinBox_clientNumber_slot(m_iClientNumber);

    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(pushButton_start_slot()));
    connect(m_pQTimerReceive, SIGNAL(timeout()), this, SLOT(QTimerRecv_slot()));
    connect(ui.spinBox_clientNumber, SIGNAL(valueChanged(int)), this, SLOT(spinBox_clientNumber_slot(int)));
    // connect(ui.lineEdit_port, SIGNAL(textChanged(QString)), this, SLOT(lineEdit_port_slot(QString)));
}

void Server::pushButton_start_slot()
{
    QString strPort = ui.lineEdit_port->text();
    m_iPort = strPort.toInt();
    if (m_iPort == 0)
    {
        ui.statusBar->showMessage(u8"��������ȷ�Ķ˿�!");
        return;
    }
    m_sock = UdpServer(m_iPort);
    if (m_sock.startBind() == false)
    {
        ui.statusBar->showMessage(u8"Init or Bind Error!");
        return;
    }
    m_pQTimerReceive->start(50); // ��ʱ�����������50ms
    disconnect(ui.spinBox_clientNumber, 0, 0, 0); // ��ʼ�����Ժ��ֹ�޸Ŀͻ�����Ŀ
    ui.statusBar->showMessage(u8"����������������˿�:" + strPort);
    
}

Server::~Server()
{
    delete m_pQTimerReceive;
}

void Server::lineEdit_port_slot(QString strText)
{
    m_iPort = strText.toInt();
    ui.statusBar->showMessage(u8"�����˿��Ѹ�Ϊ��" + QString::number(m_iPort));
}

void Server::QTimerRecv_slot()
{
    char ClientIP[20];
    char Message[105];
    int iMessageLength = m_sock.getMessage(ClientIP, Message);
    if (iMessageLength > 0)
    {
        ui.tableWidget_packageShow->insertRow(m_iMessageCount);
        ui.tableWidget_packageShow->setItem(m_iMessageCount, 1, new QTableWidgetItem(ClientIP));
        ui.tableWidget_packageShow->setItem(m_iMessageCount, 2, new QTableWidgetItem(Message));
        m_iMessageCount++;
    }
}

void Server::spinBox_clientNumber_slot(int iClient)
{
    ui.tableWidget_clientStates->clearContents();
    ui.tableWidget_clientStates->setRowCount(0);
    for (int i = 0; i < iClient; ++i)
    {
        ui.tableWidget_clientStates->insertRow(i);
        // ��ʾ�ͻ���ID
        ui.tableWidget_clientStates->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        // ��ʾ�ͻ���״̬
        ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Offline"));
    }
    m_iClientNumber = iClient;
    // ui.statusBar->showMessage(u8"�ͻ�����Ŀ��Ϊ��" + QString::number(m_iClientNumber));
}

