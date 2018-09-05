#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QButtonGroup>

QByteArray copy_bytearray;
volatile unsigned char rcv_buf[5000];
volatile unsigned int BufWrite = 0;
volatile unsigned int BufRead = 0;
volatile unsigned char BufRcvStatus=BUFFER_EMPTY;
volatile qint32 recvNum =0;

QByteArray socket_copy_bytearray;
volatile qint32 socket_recvNum =0;
volatile unsigned char socket_rcv_buf[5000];
volatile unsigned int socket_BufWrite = 0;
volatile unsigned int socket_BufRead = 0;
volatile unsigned char socket_BufRcvStatus=BUFFER_EMPTY;

QByteArray usocket_copy_bytearray;
volatile unsigned char usocket_rcv_buf[5000];
volatile unsigned int usocket_BufWrite = 0;
volatile unsigned int usocket_BufRead = 0;
volatile unsigned char usocket_BufRcvStatus=BUFFER_EMPTY;

extern volatile bool thread_run;
extern volatile bool thread_run_socket;
extern volatile bool thread_run_usocket;

QMutex send_mutex;
QMutex usocket_mutex;
unsigned char send_arr[64];
unsigned short sectrk_x = 0;
unsigned short sectrk_y = 0;
unsigned char output_array[1024];
unsigned char output_array_6[1024];
unsigned char output_array_7[1024];
unsigned char output_array_8[1024];
unsigned char uoutput_array[5000] = {0};
extern int connect_flag;
extern int current_povstat;
int data_length=0;
QTcpSocket *usocket;
QFile expfile;
QTextEdit *upgrade_show;
MainWindow *pthis = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pthis = this;
    init_menu();
    init_sysCfg();
    init_platCfg();
    init_dbCfg();
    init_speedconvCfg();
    init_utcCfg();
    init_captureCfg();
    init_OSDCfg();
    init_cameraCfg();


    this->setWindowTitle("控制界面");
    old_x=a_center=a=POINTX+CENTER/2;
    old_y=b_center=b=POINTY+CENTER/2;

    this->resize(580,450);

    serialPort_command = new QSerialPort(this);
    connect(this,&MainWindow::copy_Done, this ,&MainWindow::parse_bytearray);


    thread_01 = new recSerial(this);//定义一个线程对象（接收）
    connect(this,&MainWindow::destroyed, this,&MainWindow::stop_thread_now);
    thread_run = true;
    thread_01->start();

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    connect(this,&MainWindow::socket_copy_Done, this ,&MainWindow::socket_parse_bytearray);
	connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    thread_socket = new RcvSocketdata(this);
    thread_run_socket = true;
    thread_socket->start();

    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
	socket_time=new QTimer(this);
    connect(socket_time,SIGNAL(timeout()),this,SLOT(socketTimeoutSlot()));

    usocket = new QTcpSocket(this);
    thread_usocket = new RcvUSocketdata(this);
    connect(usocket, &QTcpSocket::readyRead, this, &MainWindow::usocket_Read_Data);
    connect(this,&MainWindow::usocket_copy_Done, this ,&MainWindow::usocket_parse_bytearray);
    connect(thread_usocket,&RcvUSocketdata::socket2main_signal, this, &MainWindow::upgrade_showtext);
    thread_run_usocket = true;
    thread_usocket->start();

}

MainWindow::~MainWindow()
{
    delete ui;

}
void MainWindow::socketTimeoutSlot()
{
    if(!socketIsconnect){
        socket->abort();
        socket->connectToHost(net_ip,net_port);
       if(!socket->waitForConnected(300))
       {

       }
        socketIsconnect=true;
    }

}
void MainWindow::clientDisconnected()
{
    socketIsconnect=false;
    socket_time->start(1000);
}
qint32 mySetSerialBaud( QSerialPort *com, int n)
{
//    qint32 num = combobox->currentText().toInt();
    qint32 num=n;
    switch(num)
    {   // 此处的Baud1200--Baud115200，是QSerialPort类中的枚举量
        case QSerialPort::Baud1200:
        com->setBaudRate(QSerialPort::Baud1200);
        break;
        case QSerialPort::Baud2400:
        com->setBaudRate(QSerialPort::Baud2400);
        break;
        case QSerialPort::Baud4800:
        com->setBaudRate(QSerialPort::Baud4800);
        break;
        case QSerialPort::Baud9600:
        com->setBaudRate(QSerialPort::Baud9600);
        break;
        case QSerialPort::Baud19200:
        com->setBaudRate(QSerialPort::Baud19200);
        break;
        case QSerialPort::Baud38400:
        com->setBaudRate(QSerialPort::Baud38400);
        break;
        case QSerialPort::Baud57600:
        com->setBaudRate(QSerialPort::Baud57600);
        break;
        case QSerialPort::Baud115200:
        com->setBaudRate(QSerialPort::Baud115200);
        break;
    default:
        break;
    }
    return num;
}

QSerialPort::DataBits mySetSerialDataBits( QSerialPort *com,int n)
{
    QSerialPort::DataBits num = (QSerialPort::DataBits)n;
    switch(num)
    {   // 此处的Data5\6\7\8，是QSerialPort类中的枚举量
        case QSerialPort::Data5:
        com->setDataBits(QSerialPort::Data5);
        break;
        case QSerialPort::Data6:
        com->setDataBits(QSerialPort::Data6);
        break;
        case QSerialPort::Data7:
        com->setDataBits(QSerialPort::Data7);
        break;
        case QSerialPort::Data8:
        com->setDataBits(QSerialPort::Data8);
        break;
        default:
        break;
    }
    return num;
}

QSerialPort::Parity mySetSerialParity(QSerialPort *com1,int n1)
{
    QSerialPort::Parity num =(QSerialPort::Parity)n1;

    switch(num)
    {   // 此处的 0,1,2代表的是下拉框的索引值；
        case 0:
        com1->setParity(QSerialPort::NoParity);
        break;
        case 1:
        com1->setParity(QSerialPort::EvenParity);
        break;
        case 2:
        com1->setParity(QSerialPort::OddParity);
        break;

        default:
        break;
    }

    return num;
}

QSerialPort::StopBits smySetSerialStopBit(QSerialPort *com,int n)
{
    QSerialPort::StopBits num = (QSerialPort::StopBits)n;
    switch(num)
    {   // 此处的 0,1,2代表的是下拉框的索引值；
        case 0:
        com->setStopBits(QSerialPort::OneStop);
        break;
        case 1:
        com->setStopBits(QSerialPort::OneAndHalfStop);
        break;
        case 2:
        com->setStopBits(QSerialPort::TwoStop);
        break;
        default:
        break;
    }
    return num;
}

void MainWindow::netReceiveMainSlot(int port ,QString ip)
{

	net_ip=ip;
    net_port=port;
    socket->connectToHost(ip,port);

    if(!socket->waitForConnected(300))
    {
        qDebug() << "Connection failed!";
        QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
        return;
    }
    this->show();
    qDebug() << "Connect successfully!";
    connect_flag = 2;

}

void MainWindow::serialReceiveMainSlot(QString port,qint32 baud,int check,int data,int stop)
{

    serialPort_command->close();
    serialPort_command->setPortName(port);
    bool openflag = serialPort_command->open(QIODevice::ReadWrite);
    if(true == openflag ) {
        connect_flag = 1;
        mySetSerialBaud(serialPort_command,baud);
        mySetSerialDataBits(serialPort_command,data);
        mySetSerialParity(serialPort_command,check);
        smySetSerialStopBit(serialPort_command,stop);
        connect(serialPort_command, &QSerialPort::readyRead, this, &MainWindow::RcvData_SerialPort);//当有数据来时，触发接收槽函数；
    }else{// 串口打开失败时，弹出提示窗口
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
    }
         this->show();
}
void MainWindow::btnToNet()
{
    net_port=lineEdit_port->text().toInt();
    net_ip=lineEdit_ip->text();
    if(socket->isOpen())
       socket->close();
    if(serialPort_command->isOpen())
       serialPort_command->close();
    socket->abort();
     socket->connectToHost(net_ip,net_port);
    if(!socket->waitForConnected(300))
    {
        qDebug() << "Connection failed!";
        QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
        return;
    }
    w_config_net->close();
	socketIsconnect=true;
    qDebug() << "Connect successfully!";
    connect_flag = 2;
}

void MainWindow::btnToSerial()
{
    QString serial_port=box_serial->currentText();
    qint32 serial_baud=box_baud->currentText().toInt();
    int serial_check=box_check->currentIndex();
    int  serial_data=box_data->currentText().toInt();
    int serial_stop=box_stop->currentIndex();
    if(socket->isOpen())
       socket->close();
    if(serialPort_command->isOpen())
       serialPort_command->close();
    serialPort_command->setPortName(serial_port);
    bool openflag = serialPort_command->open(QIODevice::ReadWrite);
    if(true == openflag) {
        connect_flag = 1;
        mySetSerialBaud(serialPort_command,serial_baud);
        mySetSerialDataBits(serialPort_command,serial_data);
        mySetSerialParity(serialPort_command,serial_check);
        smySetSerialStopBit(serialPort_command,serial_stop);
         w_config_serial->close();
    }else{// 串口打开失败时，弹出提示窗口
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
    }
}

void MainWindow::btnToClose()
{
    w_config_net->close();
    w_config_serial->close();
}


void MainWindow::on_btnTrack_clicked()
{
    value_x=960;
    value_y=540;
    send_mutex.lock();
    send_arr[4] = 0x04;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnCapture_clicked()
{
}

void MainWindow::on_btnSersorSwitch_clicked()
{
    send_mutex.lock();
    send_arr[4] =0x05;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_sysCfg_Slot()
{
    float value=lineEdit->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::CBox_sysCfg_Slot(int i)
{
    int c_channel = box1->currentText().toInt();
    send_mutex.lock();
    send_arr[4] = 02;
    send_arr[5] = c_channel-1;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::lEdt_fix_Radio_Slot()
{   float value=lineEdit_fieldRadio->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::lEdt_Resolution_Slot()
{
    float value=lineEdit_fieldResolution->text().toInt();
//    qDebug()<<value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Resolution2_Slot()
{
    float value=lineEdit_fieldResolution2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_fix_Slot()
{
    send_mutex.lock();
    send_arr[4] = 1;
    send_arr[5] = 1;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::lEdt_fix_view_Slot()
{
    float value=lEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::sp_fix_x_Slot(int i)
{
    float value=sp->text().toInt();
     qDebug()<<"i"<<i;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::sp_fix_y_Slot(int i)
{
    float value=sp2->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x17;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::sp_test_Slot()
{

}

void MainWindow::lEdt_switch_Radio_Slot()
{
 
}

void MainWindow::lEdt_switch_Resolution_Slot()
{
    
}

void MainWindow::btn_switch1_Slot()
{
  
}

void MainWindow::btn_switch2_Slot()
{
    
}

void MainWindow::btn_switch3_Slot()
{
    
}

void MainWindow::btn_switch4_Slot()
{
 
}

void MainWindow::btn_switch5_Slot()
{
   
}

void MainWindow::lEdt_continue_Radio_Slot()
{
   
}

void MainWindow::lEdt_continue_Resolution_Slot()
{
 
}

void MainWindow::btn_continue1_Slot()
{
   
}

void MainWindow::btn_continue2_Slot()
{
    
}

void MainWindow::btn_continue3_Slot()
{
    
}

void MainWindow::btn_continue4_Slot()
{
   
}

void MainWindow::btn_continue5_Slot()
{
  
}

void MainWindow::btn_continue6_Slot()
{
   
}

void MainWindow::btn_continue7_Slot()
{
  
}

void MainWindow::btn_continue8_Slot()
{
   
}

void MainWindow::btn_continue9_Slot()
{
   
}

void MainWindow::btn_continue10_Slot()
{
  
}

void MainWindow::btn_continue11_Slot()
{
    
}

void MainWindow::btn_continue12_Slot()
{
   
}

void MainWindow::btn_continue13_Slot()
{
    
}

void MainWindow::btn_utc1_default_Slot()
{
    send_mutex.lock();
    send_arr[4] =0x09;
    send_arr[5] = 0x04;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_utc1_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l0_Slot()
{
    float value=utc1_l0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l1_Slot()
{
    float value=utc1_l1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc1_l2_Slot()
{
    float value=utc1_l2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l3_Slot()
{
    float value=utc1_l3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l4_Slot()
{

    float value=utc1_l4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l5_Slot()
{
    float value=utc1_l5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l6_Slot()
{
    float value=utc1_l6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l7_Slot()
{
    float value=utc1_l7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l8_Slot()
{
    float value=utc1_l8->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l9_Slot()
{
    float value=utc1_l9->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc1_l10_Slot()
{
    float value=utc1_l10->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0a;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l11_Slot()
{
    float value=utc1_l11->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0b;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l12_Slot()
{
    float value=utc1_l12->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0c;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l13_Slot()
{
    float value=utc1_l13->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0d;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l14_Slot()
{
    float value=utc1_l14->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0e;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l15_Slot()
{
    float value=utc1_l15->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x04;
    send_arr[6] = 0x0f;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_utc2_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x05;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_utc2_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l0_Slot()
{
    float value=utc2_l0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l1_Slot()
{
    float value=utc2_l1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l2_Slot()
{
    float value=utc2_l2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l3_Slot()
{
    float value=utc2_l3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l4_Slot()
{
    float value=utc2_l4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l5_Slot()
{
    float value=utc2_l5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l6_Slot()
{
    float value=utc2_l6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc2_l7_Slot()
{
    float value=utc2_l7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l8_Slot()
{
    float value=utc2_l8->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc2_l9_Slot()
{
    float value=utc2_l9->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l10_Slot()
{
    float value=utc2_l10->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0a;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l11_Slot()
{
    float value=utc2_l11->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0b;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l12_Slot()
{
    float value=utc2_l12->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0c;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l13_Slot()
{
    float value=utc2_l13->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0d;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l14_Slot()
{
    float value=utc2_l14->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0e;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l15_Slot()
{
    float value=utc2_l15->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x05;
    send_arr[6] = 0x0f;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_utc3_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x06;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_utc3_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l0_Slot()
{
    float value=utc3_l0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l1_Slot()
{
    float value=utc3_l1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l2_Slot()
{
    float value=utc3_l2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l3_Slot()
{
    float value=utc3_l3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l4_Slot()
{
    float value=utc3_l4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l5_Slot()
{
    float value=utc3_l5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc3_l6_Slot()
{
    float value=utc3_l6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l7_Slot()
{
    float value=utc3_l7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc3_l8_Slot()
{
    float value=utc3_l8->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l9_Slot()
{
    float value=utc3_l9->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l10_Slot()
{
    float value=utc3_l10->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0a;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l11_Slot()
{
    float value=utc3_l11->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0b;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l12_Slot()
{
    float value=utc3_l12->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0c;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l13_Slot()
{
    float value=utc3_l13->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0d;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l14_Slot()
{
    float value=utc3_l14->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0e;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l15_Slot()
{
    float value=utc3_l15->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x06;
    send_arr[6] = 0x0f;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_osd_default_Slot()
{
    int count = c->currentIndex();

    if(count<16)
        count=count+7;
    else
        count=count+13;

    send_mutex.lock();
    send_arr[4] =0x09;
    send_arr[5] =count;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_osd_update_Slot()
{
    if(checkBox->isChecked()){
        value_check=0;
    }else{
        value_check=1;
    }
    int length=0;
    QString msg=osd1_lineEdit_context->text();
    QByteArray dd=msg.toUtf8();
    length=dd.size()+9;
    if(dd.size()>128){
        QMessageBox::warning(this,"警告","输入内容过多",QMessageBox::Ok);
    }else{
        send_mutex.lock();
        send_arr[4]=0x20;
        send_arr[5]=c->currentIndex();
        send_arr[6]=value_check;
        send_arr[7]=osd1_pos_x->text().toInt()&0xff;
        send_arr[8]=(osd1_pos_x->text().toInt()>>8)&0xff;
        send_arr[9]=osd1_pos_y->text().toInt()&0xff;
        send_arr[10]=(osd1_pos_y->text().toInt()>>8)&0xff;
        send_arr[11]=CBox_color->currentIndex()+1;
        send_arr[12]=osd1_lineEdit_transparency->text().toInt();
        for(int i=0;i<dd.size();i++){
           int addr1=dd[i] & 0x000000FF;
           send_arr[13+i]=addr1;
        }
        send_oneframe(length);
        send_mutex.unlock();
    }
}

void MainWindow::CBox_osd_choose_Slot(int i)
{
    osd1_lineEdit_context->clear();
    osd1_pos_y->clear();
    osd1_pos_x->clear();
    osd1_lineEdit_transparency->clear();
 if(i<16){
        for(int j=0;j<4;j++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=i+7;
            send_arr[6]=j;
            send_oneframe(3);
            send_mutex.unlock();
        }
        for(int j=5;j<7;j++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=i+7;
            send_arr[6]=j;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }else{
        for(int j=0;j<4;j++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=i+13;
            send_arr[6]=j;
            send_oneframe(3);
            send_mutex.unlock();
        }
        for(int j=5;j<7;j++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=i+13;
            send_arr[6]=j;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }
}

void MainWindow::checkBox_Slot(int i)
{
}
void MainWindow::checkBox_cross_Slot(int i)
{
    float value = 0;
    if(checkBox_cross->isChecked()){
        value=1;
    }else{
        value=0;
    }
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::checkBox_channel_Slot(int i)
{
    int value = 0xFF;
    box1->clear();
    if(checkBox_channel1->isChecked())
    {
        value |= 1;
        box1->addItem("1");
    }
    else
        value &= ~(1);

    if(checkBox_channel2->isChecked())
    {
        value |= (1<<1);
        box1->addItem("2");
    }
    else
        value &= ~(1<<1);

    if(checkBox_channel3->isChecked())
    {
        value |= (1<<2);
        box1->addItem("3");
    }
    else
        value &= ~(1<<2);

    if(checkBox_channel4->isChecked())
    {
        value |= (1<<3);
        box1->addItem("4");
    }
    else
        value &= ~(1<<3);

    if(checkBox_channel5->isChecked())
    {
        value |= (1<<4);
        box1->addItem("5");
    }
    else
        value &= ~(1<<4);

    send_mutex.lock();
    send_arr[4] = 0x03;
    send_arr[5] =value;
    send_oneframe(2);
    send_mutex.unlock();

}
void MainWindow::btn_aisle1_Slot()
{
    switch (BG1->checkedId()) {
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x00;
        send_arr[6] = 0x00;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x00;
        send_arr[6] = 0x01;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle2_Slot()
{
    switch (BG2->checkedId()) {
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x01;
        send_arr[6] = 0x00;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x01;
        send_arr[6] = 0x01;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle3_Slot()
{
    switch (BG3->checkedId()) {
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x02;
        send_arr[6] = 0x00;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x02;
        send_arr[6] = 0x01;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle4_Slot()
{
    switch (BG4->checkedId()) {
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x03;
        send_arr[6] = 0x00;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x03;
        send_arr[6] = 0x01;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle5_Slot()
{
    switch (BG5->checkedId()) {
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x04;
        send_arr[6] = 0x00;
        send_oneframe(3);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}
void MainWindow::lEdt_osd_x_Slot()
{

}

void MainWindow::lEdt_osd_y_Slot()
{

}

void MainWindow::lEdt_osd_context_Slot()
{

}

void MainWindow::CBox_osd_font_Slot(int i)
{
    send_mutex.lock();
    send_arr[4] = 0x21;
    send_arr[5] =CBox_font->currentIndex()+1;
    send_arr[6] =CBox_font_size->currentIndex()+1;
    send_oneframe(3);
    send_mutex.unlock();
    //QMessageBox::information(this,"提示","重启板卡生效",QMessageBox::Ok,QMessageBox::Cancel);

}

void MainWindow::CBox_osd_font_size_Slot(int i)
{
    send_mutex.lock();
    send_arr[4] = 0x21;
    send_arr[5] =CBox_font->currentIndex()+1;
    send_arr[6] =CBox_font_size->currentIndex()+1;
    send_oneframe(3);
    send_mutex.unlock();
    //QMessageBox::information(this,"提示","重启板卡生效",QMessageBox::Ok,QMessageBox::Cancel);
}

void MainWindow::CBox_View_Slot(int i)
{
    send_mutex.lock();
    send_arr[4]=0x11;
    send_arr[5]=i;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::CBox_osd_color_Slot(int i)
{

}

void MainWindow::lEdt_transparency_Slot()
{

}

void MainWindow::lEdt_capture_0()
{
    float value=cap_0_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_1()
{
    float value=cap_1_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_2()
{
    float value=cap_2_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_3()
{
    float value=cap_3_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_4()
{
    float value=cap_4_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_5()
{
    float value=cap_5_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_6()
{
    float value=cap_0_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_7()
{
    float value=cap_1_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_8()
{
    float value=cap_2_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_9()
{
    float value=cap_3_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_10()
{
    float value=cap_4_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x0a;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_capture_11()
{
    float value=cap_5_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2D;
    send_arr[6] = 0x0b;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_0()
{
    float value=bomen_0_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_1()
{
    float value=bomen_1_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_2()
{
    float value=bomen_2_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_3()
{
    float value=bomen_3_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_4()
{
    float value=bomen_4_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_5()
{
    float value=bomen_5_w->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_6()
{
    float value=bomen_0_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_7()
{
    float value=bomen_1_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_8()
{
    float value=bomen_2_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_9()
{
    float value=bomen_3_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_10()
{
    float value=bomen_4_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x0a;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_bomen_11()
{
    float value=bomen_5_h->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2E;
    send_arr[6] = 0x0b;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_drawLine_1()
{
    float value=drawLine_1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_drawLine_2()
{
    float value=drawLine_2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_drawLine_3()
{
    float value=drawLine_3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_drawLine_4()
{
    float value=drawLine_4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_drawLine_5()
{
    float value=drawLine_5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x2F;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_capture_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x2D;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_capture_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::btn_capture2_default_SLot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x2E;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_capture2_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::btn_capture3_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x2F;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_capture3_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::resetAction()
{
    QMessageBox::StandardButton reply;
    reply=QMessageBox::information(this,"提示","是否恢复出厂设置",QMessageBox::Ok,QMessageBox::Cancel);
    if(reply==QMessageBox::Ok){
        send_mutex.lock();
        send_arr[4] = 0x09;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::toCBox(int i)
{
    disconnect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD2Slot()));
    disconnect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD3Slot()));
    disconnect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD4Slot()));
    disconnect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD1Slot()));
    if(i==1){
        qDebug()<<"当前为2";
        connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD2Slot()));
    }else if(i==2){
        qDebug()<<"当前为3";
        connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD3Slot()));
    }else if(i==3){
        qDebug()<<"当前为4";
        connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD4Slot()));
    }else{
        qDebug()<<"当前为1";
        connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(toOSD1Slot()));
    }
}

void MainWindow::toOSD1Slot()
{

    send_arr[4] = 0x01;
    send_arr[5] = 0x01;
    send_oneframe(2);
    qDebug()<<"这是osd1";
}
void MainWindow::toOSD2Slot()
{
    qDebug()<<"这是osd2";
}
void MainWindow::toOSD3Slot()
{
    qDebug()<<"这是osd3";
}

void MainWindow::toOSD4Slot()
{
    qDebug()<<"这是osd4";
}

void MainWindow::toMainTest()
{
    this->show();
}

void MainWindow::btn_Jos_Default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x02;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 0x03;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Jos_Update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 49;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 50;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos1_Slot()
{
    float value=josDead_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos2_Slot()
{
    float value=josPoint_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos3_Slot()
{
    float value=josInputG_x->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos4_Slot()
{
    float value=josInputG_y->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos5_Slot()
{
    float value=josPoint_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos6_Slot()
{
    float value=josInputG_x2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_Jos7_Slot()
{
    float value=josInputG_y2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x01;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_PID1_Slot()
{

    float value=kp1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot()
{
    float value=ki1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot()
{
    float value=kd1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID4_Slot()
{
    float value=k1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID5_Slot()
{
    float value=kp2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot()
{
    float value=ki2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot()
{
    float value=kd2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID8_Slot()
{
    float value=k2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x02;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat1_Slot()
{
    float value=bleedx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat2_Slot()
{
    float value=bleedy_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat3_Slot()
{
    float value=mx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat4_Slot()
{
    float value=my_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat5_Slot()
{
    float value=deadx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat6_Slot()
{
    float value=deady_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat7_Slot()
{
    float value=a_plat->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_kx_Slot()
{
    float value=kx_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_ky_Slot()
{
    float value=ky_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_errx_Slot()
{
    float value=errx_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_erry_Slot()
{
    float value=erry_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_time_Slot()
{
    float value=time_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg5_Slot()
{
    float value=dbg5_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg6_Slot()
{
    float value=dbg6_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg7_Slot()
{
    float value=dbg7_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg8_Slot()
{
    float value=dbg8_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg9_Slot()
{
    float value=dbg9_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x09;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg10_Slot()
{
    float value=dbg10_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg11_Slot()
{
    float value=dbg11_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg12_Slot()
{
    float value=dbg12_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg13_Slot()
{
    float value=dbg13_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg14_Slot()
{
    float value=dbg14_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_dbg15_Slot()
{
    float value=dbg15_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx1_Slot()
{
    float value=speedx1_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx2_Slot()
{
    float value=speedx2_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx3_Slot()
{
    float value=speedx3_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx4_Slot()
{
    float value=speedx4_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx5_Slot()
{
    float value=speedx5_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx6_Slot()
{
    float value=speedx6_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx7_Slot()
{
    float value=speedx7_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx8_Slot()
{
    float value=speedx8_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx9_Slot()
{
    float value=speedx9_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy1_Slot()
{
    float value=speedy1_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy2_Slot()
{
    float value=speedy2_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy3_Slot()
{
    float value=speedy3_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy4_Slot()
{
    float value=speedy4_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy5_Slot()
{
    float value=speedy5_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy6_Slot()
{
    float value=speedy6_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy7_Slot()
{
    float value=speedy7_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 49;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy8_Slot()
{
    float value=speedy8_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 50;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy9_Slot()
{
    float value=speedy9_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 50;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::outMode_Slot(int i)
{
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x03;
    send_arr[6] = 0x09;
    send_arr[7] = i;
    send_oneframe(4);
    send_mutex.unlock();
}



void MainWindow::btnDownSlot()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    unsigned char usocket_send_buf[1024+256] = {0};
    qint64 len = 0;
    char buf[1024+256] = {0};
    unsigned char checksum = 0;

     if( false == filePath.isEmpty())
     {
        // 获取文件信息
        fileName.clear();
        filesize =0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        filesize = info.size();
        sendsize = 0;
        int packet_flag;

        if(filesize>4294967295)
        {
            upgrade_show->append("文件大小不能超过4294967295字节！");
            return;
        }
        if(0 == filesize)
        {
            upgrade_show->append("文件大小为0字节！");
            return;
        }

        file.setFileName(filePath);
        bool isok = file.open(QFile::ReadOnly);
        if(false == isok)
        {
            upgrade_show->append("打开文件失败");
            return;
        }

        usocket_send_buf[0] = 0xEB;
        usocket_send_buf[1] = 0x53;
        usocket_send_buf[4] = 0x32;
        usocket_send_buf[5] = filesize&0xff;
        usocket_send_buf[6] = (filesize>>8)&0xff;
        usocket_send_buf[7] = (filesize>>16)&0xff;
        usocket_send_buf[8] = (filesize>>24)&0xff;
        packet_flag = 0;

        QString ip = upgrade_ip->text();
        int port = upgrade_port->text().toInt();
        usocket->connectToHost(ip,port);
        if(!usocket->waitForConnected(300))
        {
            upgrade_show->append("连接服务器失败");
            return;
        }
        while(len = file.read(buf,1024))
        {  //每次发送数据大小
          checksum = 0;
          if(len<0)
          {
              upgrade_show->append("文件读取失败");
              break;
          }
          sendsize += len;
          if(packet_flag == 0)
          {
              usocket_send_buf[9] = 0;
              packet_flag = 1;
          }
          else if(sendsize == filesize)
          {
              usocket_send_buf[9] = 2;
          }
          else
          {
            usocket_send_buf[9] = 1;
          }
          usocket_send_buf[2] = (len+8)&0xff;
          usocket_send_buf[3] = ((len+8)>>8)&0xff;
          usocket_send_buf[10] = len&0xff;
          usocket_send_buf[11] = (len>>8)&0xff;
          memcpy(usocket_send_buf+12,buf, len);
          for(int m = 1; m<12+len;m++)
              checksum ^= usocket_send_buf[m];
          usocket_send_buf[12+len] = checksum;

          usocket->write((char *)usocket_send_buf,len+13);
        }
        if(sendsize == filesize)
        {
            file.close();
            upgrade_show->append("文件发送中...");
            //usocket->disconnectFromHost();
            //usocket->close();
        }
        else
        {
            upgrade_show->append("文件发送失败");
        }
    }
    else
        upgrade_show->append("选择文件无效");

}

void MainWindow::btnUpSlot()
{
    QString filePath= QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("YML files (*.yml)"));
    unsigned char usocket_send_buf[256] = {0};
    unsigned char sum = 0;
    if( false == filePath.isEmpty())
    {
        usocket_send_buf[0] = 0xEB;
        usocket_send_buf[1] = 0x53;
        usocket_send_buf[2] = 0x01;
        usocket_send_buf[3] = 0x00;
        usocket_send_buf[4] = 0x33;
        expfile.setFileName(filePath);
        for(int i = 1; i < 5; i++)
            sum ^= usocket_send_buf[i];
        usocket_send_buf[5] = sum;
        QString ip = upgrade_ip->text();
        int port = upgrade_port->text().toInt();
        usocket->connectToHost(ip,port);
        if(!usocket->waitForConnected(300))
        {
            upgrade_show->append("连接服务器失败");
            return;
        }
        usocket->write((char *)usocket_send_buf,6);
    }
    else
    {
        upgrade_show->append("选择文件无效");
    }

}

void MainWindow::btnSaveSlot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::btnUpdate()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    unsigned char usocket_send_buf[1024+256] = {0};
    qint64 len = 0;
    char buf[1024+256] = {0};
    unsigned char checksum = 0;

     if( false == filePath.isEmpty())
     {
        // 获取文件信息
        fileName.clear();
        filesize =0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        filesize = info.size();
        sendsize = 0;
        int packet_flag;

        if(filesize>4294967295)
        {
            upgrade_show->append("文件大小不能超过4294967295字节！");
            return;
        }

        file.setFileName(filePath);
        bool isok = file.open(QFile::ReadOnly);
        if(false == isok)
        {
            upgrade_show->append("打开文件失败");
            return;
        }
#if 0
        if(1 == connect_flag)//串口
        {
            usocket_send_buf[0] = 0xEB;
            usocket_send_buf[1] = 0x53;
            usocket_send_buf[4] = 0x35;
            usocket_send_buf[5] = filesize&0xff;
            usocket_send_buf[6] = (filesize>>8)&0xff;
            usocket_send_buf[7] = (filesize>>16)&0xff;
            usocket_send_buf[8] = (filesize>>24)&0xff;
            packet_flag = 0;
            while(len = file.read(buf,1024))
            {  //每次发送数据大小
              checksum = 0;
              if(len<0)
              {
                  upgrade_show->append("文件读取失败");
                  break;
              }
              sendsize += len;
              if(packet_flag == 0)
              {
                  usocket_send_buf[9] = 0;
                  packet_flag = 1;
              }
              else if(sendsize == filesize)
              {
                  usocket_send_buf[9] = 2;
              }
              else
              {
                usocket_send_buf[9] = 1;
              }
              usocket_send_buf[2] = (len+8)&0xff;
              usocket_send_buf[3] = ((len+8)>>8)&0xff;
              usocket_send_buf[10] = len&0xff;
              usocket_send_buf[11] = (len>>8)&0xff;
              memcpy(usocket_send_buf+12,buf, len);
              for(int m = 1; m<12+len;m++)
                  checksum ^= usocket_send_buf[m];
              usocket_send_buf[12+len] = checksum;
              serialPort_command->write((char *)usocket_send_buf,len+13);
            }
            if(sendsize == filesize)
            {
                file.close();
                upgrade_show->append("文件发送中...");
            }
            else
            {
                upgrade_show->append("文件发送失败");
            }
        }
        else if(2 == connect_flag)//网口
        {
#endif
		usocket_send_buf[0] = 0xEB;
		usocket_send_buf[1] = 0x53;
		usocket_send_buf[4] = 0x35;
		usocket_send_buf[5] = filesize&0xff;
		usocket_send_buf[6] = (filesize>>8)&0xff;
		usocket_send_buf[7] = (filesize>>16)&0xff;
		usocket_send_buf[8] = (filesize>>24)&0xff;
		packet_flag = 0;

		QString ip = upgrade_ip->text();
		int port = upgrade_port->text().toInt();
		usocket->connectToHost(ip,port);
        int trans_percent = 0;
		if(!usocket->waitForConnected(300))
		{
		    upgrade_show->append("连接服务器失败");
		    return;
		}
		while(len = file.read(buf,1024))
		{  //每次发送数据大小
		  checksum = 0;
		  if(len<0)
		  {
		      upgrade_show->append("文件读取失败");
		      break;
		  }
		  sendsize += len;
		  if(packet_flag == 0)
		  {
		      usocket_send_buf[9] = 0;
		      packet_flag = 1;
		  }
		  else if(sendsize == filesize)
		  {
		      usocket_send_buf[9] = 2;
		  }
		  else
		  {
		    usocket_send_buf[9] = 1;
		  }
		  usocket_send_buf[2] = (len+8)&0xff;
		  usocket_send_buf[3] = ((len+8)>>8)&0xff;
		  usocket_send_buf[10] = len&0xff;
		  usocket_send_buf[11] = (len>>8)&0xff;
		  memcpy(usocket_send_buf+12,buf, len);
		  for(int m = 1; m<12+len;m++)
		      checksum ^= usocket_send_buf[m];
		  usocket_send_buf[12+len] = checksum;

		  usocket->write((char *)usocket_send_buf,len+13);
          usocket->flush();
          trans_percent = sendsize*100/filesize;
          //upgrade_show->setText(tr("文件发送中...%")+QString("%1").arg(trans_percent&0xFF,2,10));
		}
		if(sendsize == filesize)
		{
		    file.close();
            //qDebug()<<"文件大小："<<filesize<<"发送大小："<<sendsize;
            //upgrade_show->append(tr("文件字节数")+QString("%1").arg(filesize,10,10));
            //usocket->disconnectFromHost();
            //usocket->close();
		}
		else
		{
		    upgrade_show->append("文件发送失败");
		}
		//}
    }
    else
            upgrade_show->append("选择文件无效");
     }

 void MainWindow::btn_default_Slot()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 23;
     send_oneframe(2);
     send_mutex.unlock();
 }
 void MainWindow::btn_default_Slot2()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 24;
     send_oneframe(2);
     send_mutex.unlock();
 }
 void MainWindow::btn_default_Slot3()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 25;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 26;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 27;
     send_oneframe(2);
     send_mutex.unlock();
 }

void MainWindow::stop_thread_now()  // 当点击窗口右上角的关闭按钮时，会自动触发MyWidget的destroyed信号，
{                              // 使用connect与其绑定此函数：在关闭窗口时若有线程正在运行则先退出线程再关闭窗口；
    if(thread_01->isRunning()){
        thread_run = false;
        thread_01->quit();
        thread_01->wait();
    }
    if(thread_socket->isRunning()){
        thread_run_socket = false;
        thread_socket->quit();
        thread_socket->wait();
    }
    if(thread_usocket->isRunning()){
            thread_run_usocket = false;
            thread_usocket->quit();
            thread_usocket->wait();
        }

}
QString ShowHex(QByteArray str)
{
    QDataStream out(&str,QIODevice::ReadWrite);   //将字节数组与数据流关联，操作数据流等同于操作字节数组；
    QString buf;

    while(!out.atEnd())  // 判断是否已经到数据末端
    {
        quint8 outChar = 0;
        out >> outChar;             //每次一个字节的拷贝至 outchar
        QString str = QString("%1").arg(outChar&0xFF,2,16,QLatin1Char('0')).trimmed().toUpper() + QString(" ");   //2 字符宽度
        buf += str;
    }
    return buf;
}

void MainWindow::socket_Read_Data()
{
    socketRcvData = socket->readAll();//读网口
    socket_copy_bytearray = socketRcvData;
    emit socket_copy_Done();
    QString rcvBuf;
    rcvBuf = ShowHex(socketRcvData);
    //ui->textEdit->setTextColor(QColor(Qt::blue));
    //ui->textEdit->append(rcvBuf);
    socketRcvData.clear();
}

void MainWindow::usocket_Read_Data()
{
    usocketRcvData = usocket->readAll();//读网口
    usocket_copy_bytearray = usocketRcvData;
    //emit usocket_copy_Done();
    {
        QDataStream out(usocket_copy_bytearray);
        int add_cnt = 0;
        unsigned char tmp_buf[5000];
        while(!out.atEnd()) {
            quint8 outChar = 0;
            out >> outChar;
            tmp_buf[add_cnt++] = outChar;
            if(add_cnt>=4999)
            {
                for(int i = 0; i<add_cnt; i++)
                {
                    usocket_mutex.lock();
                    usocket_rcv_buf[ usocket_BufWrite++ ] = tmp_buf[i];
                    usocket_BufWrite %= sizeof(usocket_rcv_buf);

                    if (usocket_BufWrite == usocket_BufRead) {
                        usocket_BufRcvStatus = BUFFER_FULL;
                    }
                    else
                    {
                        usocket_BufRcvStatus = BUFFER_DATA;
                    }
                    usocket_mutex.unlock();
                }
                outChar = 0;
                add_cnt = 0;
            }

        }
        for(int i = 0; i<add_cnt; i++)
        {
            usocket_mutex.lock();
            usocket_rcv_buf[ usocket_BufWrite++ ] = tmp_buf[i];
            usocket_BufWrite %= sizeof(usocket_rcv_buf);

            if (usocket_BufWrite == usocket_BufRead) {
                usocket_BufRcvStatus = BUFFER_FULL;
            }
            else
            {
                usocket_BufRcvStatus = BUFFER_DATA;
            }
            usocket_mutex.unlock();
        }
    }
    usocketRcvData.clear();
}


void MainWindow::socket_parse_bytearray()
{
     QDataStream out(socket_copy_bytearray);
    int add_cnt = 0;
    unsigned char tmp_buf[1000];
    while(!out.atEnd()) {
        quint8 outChar = 0;
        out >> outChar;
         tmp_buf[add_cnt++] = outChar;
    }
    for(int i = 0; i<add_cnt; i++)
    {
        socket_rcv_buf[ socket_BufWrite++ ] = tmp_buf[i];

        socket_BufWrite %= sizeof(socket_rcv_buf);

        if (socket_BufWrite == socket_BufRead) {
            socket_BufRcvStatus = BUFFER_FULL;
        }
        else {
            socket_BufRcvStatus = BUFFER_DATA;
         }
    }
}

void MainWindow::usocket_parse_bytearray()
{
    QDataStream out(usocket_copy_bytearray);
    int add_cnt = 0;
    unsigned char tmp_buf[5000];
    while(!out.atEnd()) {
        quint8 outChar = 0;
        out >> outChar;
        tmp_buf[add_cnt++] = outChar;
    }
    for(int i = 0; i<add_cnt; i++)
    {
        usocket_mutex.lock();
        usocket_rcv_buf[ usocket_BufWrite++ ] = tmp_buf[i];
        usocket_BufWrite %= sizeof(usocket_rcv_buf);

        if (usocket_BufWrite == usocket_BufRead) {
            usocket_BufRcvStatus = BUFFER_FULL;
        }
        else
        {
            usocket_BufRcvStatus = BUFFER_DATA;
        }
        usocket_mutex.unlock();
    }
}
void MainWindow::parse_bytearray()
{
     QDataStream out(copy_bytearray);
    int add_cnt = 0;
    unsigned char tmp_buf[1000];
    while(!out.atEnd()) {
        quint8 outChar = 0;
        out >> outChar;
         tmp_buf[add_cnt++] = outChar;

    }
    for(int i = 0; i<add_cnt; i++)
    {
        rcv_buf[ BufWrite++ ] = tmp_buf[i];

        BufWrite %= sizeof(rcv_buf);

        if (BufWrite == BufRead) {
            BufRcvStatus = BUFFER_FULL;
        }
        else {
            BufRcvStatus = BUFFER_DATA;
         }

    }
}
void MainWindow::RcvData_SerialPort()
{
    RcvData = serialPort_command->readAll();
    copy_bytearray = RcvData;
    emit copy_Done();
    QString rcvBuf;
    rcvBuf = ShowHex(RcvData);
    //ui->textEdit->setTextColor(QColor(Qt::blue));
    //ui->textEdit->append(rcvBuf);
    RcvData.clear();
}

void MainWindow::on_btn_ok_clicked()
{

       send_mutex.lock();
       send_arr[4] = 0x0b;
       send_arr[5] = 0x02;
       send_arr[6] = value_x&0xff;
       send_arr[7] =(value_x>>8)&0xff;
       send_arr[8] = value_y&0xff;
       send_arr[9] = (value_y>>8)&0xff;
       send_oneframe(6);
       send_mutex.unlock();
       value_x=960;
       value_y=540;
}





void MainWindow::on_btnAutoCheck_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x01;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}



void MainWindow::on_btnViewPlus_released()
{
    send_mutex.lock();
    send_arr[4] = 0x12;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnViewMinus_pressed()
{
    send_mutex.lock();
    send_arr[4] =0x12;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnViewMinus_released()
{
    send_mutex.lock();
    send_arr[4] =0x12;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnForcePlus_pressed()
{
    send_mutex.lock();
    send_arr[4] = 0x14;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnForceMinus_released()
{
    send_mutex.lock();
    send_arr[4] = 0x14;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnForcePlus_released()
{
    send_mutex.lock();
    send_arr[4] = 0x14;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnForceMinus_pressed()
{
    send_mutex.lock();
    send_arr[4] = 0x14;
    send_arr[5] = 0x02;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnAperturePlus_pressed()
{
    send_mutex.lock();
    send_arr[4] = 0x13;
    send_arr[5] = 0x02;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnAperturePlus_released()
{
    send_mutex.lock();
    send_arr[4] = 0x13;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnApertureMinus_pressed()
{
    send_mutex.lock();
    send_arr[4] = 0x13;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btnApertureMinus_released()
{
    send_mutex.lock();
    send_arr[4] = 0x13;
    send_arr[5] = 0x00;
    send_oneframe(2);
    send_mutex.unlock();
}


void MainWindow::on_btnViewPlus_pressed()
{
    send_mutex.lock();
    send_arr[4] = 0x12;
    send_arr[5] = 0x02;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::on_btn_up_2_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x08;
    send_arr[5] = 0x00;
    send_arr[6] = 0x01;
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::on_btn_down_2_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x08;
    send_arr[5] = 0x00;
    send_arr[6] = 0x02;
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::on_btn_left_2_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x08;
    send_arr[5] = 0x01;
    send_arr[6] = 0x00;
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::on_btn_right_2_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x08;
    send_arr[5] = 0x02;
    send_arr[6] = 0x00;
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::on_btn_up_pressed()
{
    value_search=0;
    value_y-=5;
    send_mutex.lock();
    send_arr[4] = 0x0b;
    send_arr[5] = 0x01;
    send_arr[6] = value_x&0xff;
    send_arr[7] =(value_x>>8)&0xff;
    send_arr[8] = value_y&0xff;
    send_arr[9] = (value_y>>8)&0xff;
    send_oneframe(6);
    send_mutex.unlock();
    time->start(50);
}

void MainWindow::on_btn_up_released()
{
    time->stop();
}

void MainWindow::on_btn_right_pressed()
{
    value_search=1;
    value_x+=5;
    send_mutex.lock();
    send_arr[4] = 0x0b;
    send_arr[5] = 0x01;
    send_arr[6] = value_x&0xff;
    send_arr[7] =(value_x>>8)&0xff;
    send_arr[8] = value_y&0xff;
    send_arr[9] = (value_y>>8)&0xff;
    send_oneframe(6);
    send_mutex.unlock();
    time->start(50);
}

void MainWindow::on_btn_right_released()
{
    time->stop();
}

void MainWindow::on_btn_left_pressed()
{
    value_search=2;
    value_x-=5;
    send_mutex.lock();
    send_arr[4] = 0x0b;
    send_arr[5] = 0x01;
    send_arr[6] = value_x&0xff;
    send_arr[7] =(value_x>>8)&0xff;
    send_arr[8] = value_y&0xff;
    send_arr[9] = (value_y>>8)&0xff;
    send_oneframe(6);
    send_mutex.unlock();
    time->start(50);
}

void MainWindow::on_btn_left_released()
{
    time->stop();
}

void MainWindow::on_btn_down_pressed()
{
    value_search=3;
    value_y+=5;
    send_mutex.lock();
    send_arr[4] = 0x0b;
    send_arr[5] = 0x01;
    send_arr[6] = value_x&0xff;
    send_arr[7] =(value_x>>8)&0xff;
    send_arr[8] = value_y&0xff;
    send_arr[9] = (value_y>>8)&0xff;
    send_oneframe(6);
    send_mutex.unlock();
    time->start(50);
}

void MainWindow::on_btn_down_released()
{
    time->stop();
}



void MainWindow::on_checkBox_acqmode_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        send_mutex.lock();
        send_arr[4] = 0x18;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(arg1 == Qt::Unchecked)
    {
        send_mutex.lock();
        send_arr[4] = 0x18;
        send_arr[5] = 0x02;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_checkBox_autobomen_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(arg1 == Qt::Unchecked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}
