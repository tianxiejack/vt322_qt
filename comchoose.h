#ifndef COMCHOOSE_H
#define COMCHOOSE_H

#include <QWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include "jos.h"
#include <QDialog>
#include <QPainter>
#include <QEvent>
#include <QMutex>
#include <QDebug>
#include <QWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QStackedLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QStringList>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QCheckBox>
#include <QVariant>
#include <QSerialPort>

//struct serial_command{
//    QString port;
//    qint32 baud;
//    int check;
//    int data;
//    int stop;
//};
//Q_DECLARE_METATYPE(serial_command)
class comChoose : public QWidget
{
    Q_OBJECT
public:
    explicit comChoose(QWidget *parent = nullptr);

signals:
    void toMain();
   void netToMain(int port ,QString ip);
   void netToJos(int port ,QString ip);
   void serialToMain(QString port,qint32 baud,int check,int data,int stop);
   void serialToJos(QString port,qint32 baud,int check,int data,int stop);


public slots:
    void btnconfigSlot();
    void serialSlot();//配置串口
    void netSlot();//配置网口
    void toCloseSlot();//取消按钮关闭界面
    //void modeToMainSlot(int i);
    void toOtherSlot();//ok按钮发送信号


public:
   // serial_command ser;
    QWidget w_config_serial,w_config_net;
    QComboBox *box_serial;
    //QComboBox *box_baud,*box_check,*box_data,*box_stop,*box3;
    QLabel *buard_label, *check_label, *data_label, *stop_label;
    QGroupBox *groupBox_trackboard;
    QString serial_port;
    qint32 serial_baud;
    int serial_check,serial_data,serial_stop;
    int net_port;
    QString net_ip;

    QLineEdit *lineEdit_ip;
    //QLineEdit *lineEdit_port;
    QLabel *port_label;
    int mutex;//用于串口和网络的判断

    QComboBox *box2;

};

#endif // COMCHOOSE_H
