#ifndef MYQSPINBOX_H
#define MYQSPINBOX_H

#include "QSpinBox"
#include "QMouseEvent"

enum{
    fix_spinx_sec,
    fix_spiny_sec,
    switch1_spinx_sec,
    switch2_spinx_sec,
    switch3_spinx_sec,
    switch4_spinx_sec,
    switch5_spinx_sec,
    switch1_spiny_sec,
    switch2_spiny_sec,
    switch3_spiny_sec,
    switch4_spiny_sec,
    switch5_spiny_sec,
    continue1_spinx_sec,
    continue2_spinx_sec,
    continue3_spinx_sec,
    continue4_spinx_sec,
    continue5_spinx_sec,
    continue6_spinx_sec,
    continue7_spinx_sec,
    continue1_spiny_sec,
    continue2_spiny_sec,
    continue3_spiny_sec,
    continue4_spiny_sec,
    continue5_spiny_sec,
    continue6_spiny_sec,
    continue7_spiny_sec,
};
class MyQSpinBox : public QSpinBox
{
public:
    unsigned int spid;
protected:
    void stepBy(int steps);
};

#endif // MYQSPINBOX_H
