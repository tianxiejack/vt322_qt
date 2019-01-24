#ifndef MYQSPINBOX_H
#define MYQSPINBOX_H

#include "QSpinBox"
#include "QMouseEvent"

enum{
    fix_spinx,
    fix_spiny,
    switch1_spinx,
    switch2_spinx,
    switch3_spinx,
    switch4_spinx,
    switch5_spinx,
    switch1_spiny,
    switch2_spiny,
    switch3_spiny,
    switch4_spiny,
    switch5_spiny,
    continue1_spinx,
    continue2_spinx,
    continue3_spinx,
    continue4_spinx,
    continue5_spinx,
    continue6_spinx,
    continue7_spinx,
    continue1_spiny,
    continue2_spiny,
    continue3_spiny,
    continue4_spiny,
    continue5_spiny,
    continue6_spiny,
    continue7_spiny,

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

    fix_spinx_thi,
    fix_spiny_thi,
    switch1_spinx_thi,
    switch2_spinx_thi,
    switch3_spinx_thi,
    switch4_spinx_thi,
    switch5_spinx_thi,
    switch1_spiny_thi,
    switch2_spiny_thi,
    switch3_spiny_thi,
    switch4_spiny_thi,
    switch5_spiny_thi,
    continue1_spinx_thi,
    continue2_spinx_thi,
    continue3_spinx_thi,
    continue4_spinx_thi,
    continue5_spinx_thi,
    continue6_spinx_thi,
    continue7_spinx_thi,
    continue1_spiny_thi,
    continue2_spiny_thi,
    continue3_spiny_thi,
    continue4_spiny_thi,
    continue5_spiny_thi,
    continue6_spiny_thi,
    continue7_spiny_thi,
};
class MyQSpinBox : public QSpinBox
{
public:
    unsigned int spid;
protected:
    void stepBy(int steps);
};

#endif // MYQSPINBOX_H
