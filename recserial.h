#ifndef RECSERIAL_H
#define RECSERIAL_H
#include <QThread>

class recSerial : public QThread
{
 Q_OBJECT
public:
    explicit recSerial(QObject *parent = nullptr);
protected:
    void run();

signals:
    void send2main_signal(int i);

public slots:
};

#endif // RECSERIAL_H
