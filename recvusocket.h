#ifndef RECVUSOCKET_H
#define RECVUSOCKET_H
#include <QThread>
class RcvUSocketdata : public QThread
{
    Q_OBJECT
public:
    explicit RcvUSocketdata(QObject *parent = nullptr);
    void exportfile(unsigned char *uoutput_array);

protected:
    void run();

signals:
    void usocket2main_signal(int i);
public slots:
};
#endif // RECVUSOCKET_H
