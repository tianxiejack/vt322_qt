#ifndef RECVSOCKET_H
#define RECVSOCKET_H
#include <QThread>



class RcvSocketdata : public QThread
{
    Q_OBJECT
public:
    explicit RcvSocketdata(QObject *parent = nullptr);

protected:
    void run();

signals:
    void socket2main_signal(int i);

public slots:
};
#endif // RECVSOCKET_H
