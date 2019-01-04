#ifndef MYWIDGET_H
#define MYWIDGET_H
#include "QWidget"
class MyWidget : public QWidget
{
public:
    explicit MyWidget(QWidget *parent = 0);
    unsigned char show_stat;
protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MYWIDGET_H
