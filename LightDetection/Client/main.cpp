/****************
Light Detection Client
Main
Environment:VS2015, Qt5.8
Author:Zy
Date:2018.10.07
****************/



#include "Client.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    return a.exec();
}
