#include "mainwindow.h"
#include <QApplication>
#include "jos.h"
#include "comchoose.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Jos j;
    comChoose c;
    c.show();

    a.connect(&c,SIGNAL(toMain()),&w,SLOT(toMainTest()));
    a.connect(&c,SIGNAL(netToMain(int,QString)),&w,SLOT(netReceiveMainSlot(int,QString)));
    a.connect(&c,SIGNAL(serialToMain(QString,qint32,int,int,int)),&w,SLOT(serialReceiveMainSlot(QString,qint32,int,int,int)));
    //a.connect(&c,SIGNAL(netToJos(int,QString)),&j,SLOT(netReceiveJosSlot(int,QString)));
    //a.connect(&c,SIGNAL(serialToJos(QString,qint32,int,int,int)),&j,SLOT(serialReceiveJosSlot(QString,qint32,int,int,int)));
    return a.exec();
}
