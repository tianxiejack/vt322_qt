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

protected:
    void run();
};
#endif // RECVUSOCKET_H
