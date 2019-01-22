#include "myqspinbox.h"
#include  "mainwindow.h"

 void MyQSpinBox::stepBy(int steps)
 {
    int value = this->value() + steps;
    this->setValue(value);
    pthis->mystepby(spid);
 }
