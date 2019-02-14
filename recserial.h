#ifndef RECSERIAL_H
#define RECSERIAL_H
#include <QThread>

class recSerial : public QThread
{
 Q_OBJECT
public:
    explicit recSerial(QObject *parent = nullptr);
    void importfileresp(unsigned char *uoutput_array);
    void upgraderesp(unsigned char *uoutput_array);
    void serial_Read_Data();
    void exportfile(unsigned char *uoutput_array);
protected:
    void run();
signals:
    void socket2main_signal(int i,int percent);
};

#endif // RECSERIAL_H
