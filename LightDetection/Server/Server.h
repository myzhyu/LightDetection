#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Server.h"

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = Q_NULLPTR);

private:
    Ui::ServerClass ui;
    int m_iPort; // ��¼�˿ں�

private slots:
    void button_start_slot();
};
