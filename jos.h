#ifndef JOS_H
#define JOS_H

#include <QWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include <QDialog>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
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
#include <QSpinBox>
#include "comchoose.h"
#include <QTcpSocket>
#include <QVariant>
#include <QMessageBox>
#include <QDataStream>
#include "recserial.h"
#include "recvsocket.h"

#include <QTime>
#include <QTimer>
#include <QTextEdit>

#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767
#define POINTX 100 //圆左上角坐标x
#define POINTY 30 //圆左上角坐标Y
#define CENTER 160//圆的半径
#define RATIO 10 //矩形框缩小比例

#define BUFFER_FULL          1
#define BUFFER_DATA          2
#define BUFFER_EMPTY         3

namespace Ui {
class Jos;
}

class Jos : public QWidget
{
    Q_OBJECT

public:
    explicit Jos(QWidget *parent = 0);
    ~Jos();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *event);
    QByteArray string2hex(QString str,bool &flag);
    char convertHex2Char(char ch);
    void send_oneframe(int length);
    volatile qint32 sendNum =0;

public slots:
    void netReceiveJosSlot(int port, QString ip);
    void serialReceiveJosSlot(QString port, qint32 baud, int check, int data, int stop);
    void rcvData_SerialPort();
    void socketRead_Data();

private:
    Ui::Jos *ui;
    int a, b, m_dragging;
    int connect_flag;
    QTcpSocket *socket_jos;
    QSerialPort * serialPort_command_jos;
    QByteArray sndData_02;
    unsigned char send_arr[64];
};

#endif // JOS_H
