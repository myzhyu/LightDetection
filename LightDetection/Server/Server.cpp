#include "Server.h"
#include <string>

Server::Server(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_iPort = 8008;
    m_pQTimerReceive = new QTimer(this); 
    m_pQTimerHeartbeat = new QTimer(this);
    m_iMessageCount = 0;
    m_iClientNumber = 10;
    spinBox_clientNumber_slot(m_iClientNumber);

    connect(ui.pushButton_start, SIGNAL(clicked()), this, SLOT(pushButton_start_slot()));
    connect(m_pQTimerReceive, SIGNAL(timeout()), this, SLOT(QTimerReceive_slot()));
    connect(m_pQTimerHeartbeat, SIGNAL(timeout()), this, SLOT(QTimerHeartbeat_slot()));
    connect(ui.spinBox_clientNumber, SIGNAL(valueChanged(int)), this, SLOT(spinBox_clientNumber_slot(int)));
    // connect(ui.lineEdit_port, SIGNAL(textChanged(QString)), this, SLOT(lineEdit_port_slot(QString)));
}

void Server::pushButton_start_slot()
{
    ui.spinBox_clientNumber->setReadOnly(true);
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
    m_pQTimerHeartbeat->start(1000);
    disconnect(ui.spinBox_clientNumber, 0, 0, 0); // ��ʼ�����Ժ��ֹ�޸Ŀͻ�����Ŀ
    ui.statusBar->showMessage(u8"����������������˿�:" + strPort);
    
}

Server::~Server()
{
    delete m_pQTimerReceive;
    delete m_pQTimerHeartbeat;
}

void Server::lineEdit_port_slot(QString strText)
{
    m_iPort = strText.toInt();
    // ui.statusBar->showMessage(u8"�����˿��Ѹ�Ϊ��" + QString::number(m_iPort));
}

void Server::QTimerReceive_slot()
{
    char ClientIP[20] = { 0 };
    char Message[105] = { 0 };
    int iMessageLength = m_sock.getMessage(ClientIP, Message);
    if (iMessageLength > 0)
    {
        // ��Ϣ����ʾ
        ui.tableWidget_packageShow->insertRow(m_iMessageCount);
        ui.tableWidget_packageShow->setItem(m_iMessageCount, 1, new QTableWidgetItem(ClientIP));
        ui.tableWidget_packageShow->setItem(m_iMessageCount, 2, new QTableWidgetItem(Message));
        ui.tableWidget_packageShow->scrollToBottom();
        
        // ��Ϣ��ȡ����
        // ID
        char cID[3] = { 0 };
        cID[0] = Message[0];
        cID[1] = Message[1];
        cID[2] = '\0';
        ui.tableWidget_packageShow->setItem(m_iMessageCount, 0, new QTableWidgetItem(cID));
        int iID = atoi(cID);
        char cVoltage[4] = { 0 };
        char cCurrent[6] = { 0 };
        switch (Message[3])
        {
        case 'L':
            m_mLightsStatus[iID].clearLostHeartbeat();
            break;

        case 'H':
            m_mLightsStatus[iID].clearLostHeartbeat();
            break;

        case 'S':
            if (Message[11] == 'n')
            {
                m_mLightsStatus[iID].setIsSwitchOn(true);
            }
            else
            {
                m_mLightsStatus[iID].setIsSwitchOn(false);
            }
            break;

        case 'V':
            cVoltage[0] = Message[11];
            cVoltage[1] = Message[12];
            cVoltage[2] = Message[13];
            m_mLightsStatus[iID].setVoltage(atoi(cVoltage));
            break;

        case 'C':
            cCurrent[0] = Message[11];
            cCurrent[1] = Message[12];
            cCurrent[2] = Message[13];
            cCurrent[3] = Message[14];
            cCurrent[4] = Message[15];
            m_mLightsStatus[iID].setCurrent(atof(cCurrent));
            break;
        }

        // �ͻ���״̬��ʾ
        for (int i = 0; i < m_iClientNumber; ++i)
        {
            // ��ʾ�ͻ���ID
            ui.tableWidget_clientStates->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
            // ��ʾ�ͻ���IP
            char cIP[20] = { 0 };
            m_mLightsStatus[i].getIP(cIP);
            ui.tableWidget_clientStates->setItem(i, 1, new QTableWidgetItem(cIP));
            // ��ʾ�ͻ�������״̬
            if (m_mLightsStatus[i].getIsOnline())
            {
                QTableWidgetItem *pItem = new QTableWidgetItem("Online");
                pItem->setBackgroundColor(QColor(0, 255, 0));
                ui.tableWidget_clientStates->setItem(i, 2, pItem);
                // ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Online"));
                // ui.tableWidget_clientStates->item(i, 2).setBackground(QBrush(QColor(255, 0, 0)));
            }
            else
            {
                QTableWidgetItem *pItem = new QTableWidgetItem("Offline");
                pItem->setBackgroundColor(QColor(255, 0, 0));
                ui.tableWidget_clientStates->setItem(i, 2, pItem);
                // ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Offline"));
            }
            // ��ʾ�ͻ��˿���״̬
            if (m_mLightsStatus[i].getIsSwitchOn())
            {
                QTableWidgetItem *pItem = new QTableWidgetItem("On");
                pItem->setBackgroundColor(QColor(0, 255, 0));
                ui.tableWidget_clientStates->setItem(i, 3, pItem);
                //ui.tableWidget_clientStates->setItem(i, 3, new QTableWidgetItem("On"));
            }
            else
            {
                QTableWidgetItem *pItem = new QTableWidgetItem("Off");
                pItem->setBackgroundColor(QColor(255, 0, 0));
                ui.tableWidget_clientStates->setItem(i, 3, pItem);
                //ui.tableWidget_clientStates->setItem(i, 3, new QTableWidgetItem("Off"));
            }
            // ��ʾ�ͻ������е�ѹ
            ui.tableWidget_clientStates->setItem(i, 4, new QTableWidgetItem(QString::number(m_mLightsStatus[i].getVoltage())));
            // ��ʾ�ͻ������е���
            ui.tableWidget_clientStates->setItem(i, 5, new QTableWidgetItem(QString::number(m_mLightsStatus[i].getCurrent())));
        }

        m_iMessageCount++;
    }
}

void Server::QTimerHeartbeat_slot()
{
    for (int i = 0; i < m_iClientNumber; ++i)
    {
        m_mLightsStatus[i].setLostHeartbeat();
        if (m_mLightsStatus[i].getIsOnline())
        {
            QTableWidgetItem *pItem = new QTableWidgetItem("Online");
            pItem->setBackgroundColor(QColor(0, 255, 0));
            ui.tableWidget_clientStates->setItem(i, 2, pItem);
            //ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Online"));
        }
        else
        {
            QTableWidgetItem *pItem = new QTableWidgetItem("Offline");
            pItem->setBackgroundColor(QColor(255, 0, 0));
            ui.tableWidget_clientStates->setItem(i, 2, pItem);
            //ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Offline"));
        }
    }
}

void Server::spinBox_clientNumber_slot(int iClient)
{
    ui.tableWidget_clientStates->clearContents();
    ui.tableWidget_clientStates->setRowCount(0);
    for (int i = 0; i < iClient; ++i)
    {
        m_mLightsStatus[i] = LightStatus();
        ui.tableWidget_clientStates->insertRow(i);
        // ��ʾ�ͻ���ID
        ui.tableWidget_clientStates->setItem(i, 0, new QTableWidgetItem(QString::number(i)));
        // ��ʾ�ͻ���IP
        char cIP[20] = { 0 };
        m_mLightsStatus[i].getIP(cIP);
        ui.tableWidget_clientStates->setItem(i, 1, new QTableWidgetItem(cIP));
        // ��ʾ�ͻ�������״̬
        if (m_mLightsStatus[i].getIsOnline())
        {
            ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Online"));
        }
        else
        {
            ui.tableWidget_clientStates->setItem(i, 2, new QTableWidgetItem("Offline"));
        }
        // ��ʾ�ͻ��˿���״̬
        if (m_mLightsStatus[i].getIsSwitchOn())
        {
            ui.tableWidget_clientStates->setItem(i, 3, new QTableWidgetItem("On"));
        }
        else
        {
            ui.tableWidget_clientStates->setItem(i, 3, new QTableWidgetItem("Off"));
        }
        // ��ʾ�ͻ������е�ѹ
        ui.tableWidget_clientStates->setItem(i, 4, new QTableWidgetItem(QString::number(m_mLightsStatus[i].getVoltage())));
        // ��ʾ�ͻ������е���
        ui.tableWidget_clientStates->setItem(i, 5, new QTableWidgetItem(QString::number(m_mLightsStatus[i].getCurrent())));
    }
    m_iClientNumber = iClient;
    // ui.statusBar->showMessage(u8"�ͻ�����Ŀ��Ϊ��" + QString::number(m_iClientNumber));
}

