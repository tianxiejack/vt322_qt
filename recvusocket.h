#ifndef RECVUSOCKET_H
#define RECVUSOCKET_H
#include <QThread>
class RcvUSocketdata : public QThread
{
    Q_OBJECT
public:
    explicit RcvUSocketdata(QObject *parent = nullptr);
    void exportfile(unsigned char *uoutput_array);
    void importfileresp(unsigned char *uoutput_array);
    void upgraderesp(unsigned char *uoutput_array);
    void upgradefpgaresp(unsigned char *uoutput_array);
    void usocket_Read_Data();

    QByteArray usocketRcvData;

protected:
    void run();
signals:
    void socket2main_signal(int i,int percent);
};
#endif // RECVUSOCKET_H
