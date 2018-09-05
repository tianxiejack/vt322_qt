#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    show_stat = 0;
}
void MyWidget::closeEvent(QCloseEvent *event)
{
    show_stat = 0;
}

