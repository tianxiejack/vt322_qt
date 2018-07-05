#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_menu();
    //init_btn();
    init_sysCfg();
    this->setWindowTitle("控制界面");
    a=POINTX+CENTER/2;
    b=POINTY+CENTER/2;
    this->resize(580,450);

}

MainWindow::~MainWindow()
{
    delete ui;
}



