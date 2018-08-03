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
};
#endif // RECVSOCKET_H
