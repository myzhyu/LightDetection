/****************
Light Detection Server
Main
Environment:VS2015, Qt5.8
Author:Zy
Date:2018.10.07
****************/


#include "Server.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.show();
    return a.exec();
}
