#include "mainwindow.h"
#include <QApplication>
#include "jos.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Jos j;
    w.show();

    return a.exec();
}
