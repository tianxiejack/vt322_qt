#include "jos.h"
#include "ui_jos.h"
#include <QDebug>
#include "mainwindow.h"

//int mousePress = 0;
//QMutex send_mutex;
//unsigned char send_arr[64];
//unsigned short sectrk_x = 0;
//unsigned short sectrk_y = 0;

typedef struct resp
{
    unsigned char autocheck;
    unsigned char sensor;
    unsigned char sensor_bind;
    unsigned char trk;
    unsigned char mmt;
    unsigned char mmtselect;
    unsigned char enh;
    unsigned char posmove;
    unsigned char axismove;
    unsigned char zoom;
    unsigned char sectrk;
    unsigned char mtd;
    unsigned char pinp;
    unsigned char sensor_trans;
    unsigned char vframerate;
    unsigned char vquality;
    unsigned char osdcolor;
    unsigned char osdfont;
    unsigned char osdsize;
    unsigned char setconfig;
    unsigned char getconfig;
    unsigned char downconfig;
    unsigned char saveconfig;
    unsigned char joyskeyboard;

}resp_t;
resp_t respstate = {0};
extern QMutex send_mutex;
extern qint32 mySetSerialBaud( QSerialPort *com, int n);
extern QSerialPort::DataBits mySetSerialDataBits( QSerialPort *com,int n);
extern QSerialPort::Parity mySetSerialParity(QSerialPort *com1,int n1);
extern QSerialPort::StopBits smySetSerialStopBit(QSerialPort *com,int n);

Jos::Jos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Jos)
{
    ui->setupUi(this);
        connect_flag=1;
    this->setWindowTitle("手柄控制");
    //this->setGeometry(1260,1080,600,600);
    serialPort_command_jos = new QSerialPort(this);
            //connect(socket_jos, SIGNAL(readyRead()), this, SLOT(rcvData_SerialPort()));//当有数据来时，触发接收槽函数
        
    socket_jos = new QTcpSocket(this);
            //connect(socket_jos, SIGNAL(readyRead()), this, SLOT(socketRead_Data()));
        
}

Jos::~Jos()
{
    delete ui;
}

void Jos::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    //paint.drawRect(POINTX-WIDTH/2, POINTY-HEIGHT/2, WIDTH, HEIGHT);
    // 反走样
    paint.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    // 设置画刷颜色
    paint.setBrush(QColor(200, 255, 250));
    paint.drawEllipse(POINTX,POINTY,CENTER,CENTER);
   // paint.drawRect(POINTX-WIDTH/RATIO/2, POINTY-HEIGHT/RATIO/2, WIDTH/RATIO, HEIGHT/RATIO);
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    //paint.drawLine(QPointF(a-5, b), QPointF(a+5, b));
    //paint.drawLine(QPointF(a, b-5), QPointF(a, b+5));
    paint.drawEllipse(a-5,b-5,10,10);
    paint.drawPoint(a,b);

}

void Jos::mousePressEvent(QMouseEvent *event)
{

}

void Jos::mouseReleaseEvent(QMouseEvent *e)
{

}

void Jos::mouseMoveEvent(QMouseEvent *event)
{

}

void Jos::netReceiveJosSlot(int port, QString ip)
{
    socket_jos->connectToHost(ip,port);
    if(!socket_jos->waitForConnected(300))
    {
        qDebug() << "Connection failed!";
        QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
        return;
    }
    this->show();
    qDebug() << "Connect successfully!";
    connect_flag = 2;
    this->show();
}

void Jos::serialReceiveJosSlot(QString port, qint32 baud, int check, int data, int stop)
{
    serialPort_command_jos->close();
    serialPort_command_jos->setPortName(port);
    bool openflag = serialPort_command_jos->open(QIODevice::ReadWrite);
    if(true == openflag ) {
        connect_flag = 1;
        mySetSerialBaud(serialPort_command_jos,baud);
        mySetSerialDataBits(serialPort_command_jos,data);
        mySetSerialParity(serialPort_command_jos,check);
        smySetSerialStopBit(serialPort_command_jos,stop);

    }else{// 串口打开失败时，弹出提示窗口
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
    }
         this->show();
}

void Jos::rcvData_SerialPort()
{

}

void Jos::socketRead_Data()
{

}
char Jos::convertHex2Char(char ch)
{
    if((ch>='0')&& (ch<='9')){
        return ch-0x30;
    }else if((ch>='A') && (ch<='F')){
        return ch-'A'+10;
    }else if((ch>='a') && (ch<='f')){
        return ch-'a'+10;
    }else{
        return (-1);
    }
}
QByteArray Jos::string2hex(QString str, bool &flag)
{
    QByteArray senddata;
    int hexdata,lowHexdata;
    int hexdatalen=0;
    int len=str.length();
    char lstr,hstr;
    senddata.resize(len/2);
    for(int i=0;i<len;i++){
        hstr=str[i].toLatin1();
        if(hstr==' '){
            continue;
        }
        i++;
        lstr=str[i].toLatin1();
        if(lstr==' '|| i>=len){
            hexdata=0;
            lowHexdata=convertHex2Char(hstr);
        }else{
            hexdata=convertHex2Char(hstr);
            lowHexdata=convertHex2Char(lstr);
        }
        if((hexdata== -1) || (lowHexdata== -1)){
            flag=false;
            senddata.resize(hexdatalen);
            return senddata;
        }else{
            hexdata=hexdata*16+lowHexdata;

        }
        senddata[hexdatalen]=(char)hexdata;
         hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
void Jos::send_oneframe(int length)
{
    int len=length+5;
    send_arr[0] = 0xEB;
    send_arr[1] = 0x53;
    send_arr[2] = length;
    send_arr[3] = 0x00;
    unsigned char sum=0;
    for(int n = 1; n<len-1; n++) {
        sum ^= send_arr[n];
     }
    send_arr[len-1] = sum;

    QString str1;
    for(int m = 0; m< len; m++){
        str1 += QString("%1").arg(send_arr[m]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
    }
    bool checkf = true;
    sndData_02 = string2hex(str1,checkf);
    //qDebug()<<sndData_02;
    sendNum += sndData_02.length();
    memset(&respstate, 0, sizeof(respstate));
    if(checkf == true){
        if(1 == connect_flag)
        {
            serialPort_command_jos->write(sndData_02);
        }
        else if(2 == connect_flag)
        {
            socket_jos->write(sndData_02);//通过网口发送数据
            socket_jos->flush();
        }
    }
    //ui->label->setText(str1);
}
