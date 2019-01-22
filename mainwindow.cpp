#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QButtonGroup>
#include <iostream>

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
QTcpSocket *socket;
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

    init_pidCfg();
    init_pidCfg2();
    init_pidCfg3();
    init_pidCfg4();
    init_pidCfg5();
    init_vedioCfg();
    init_vedioCfg_sec();
    init_vedioCfg_thi();
    init_vedioCfg_fou();
    init_vedioCfg_fif();
    init_dbCfg();
    init_speedconvCfg();
    init_speedconvCfg_sec();
    init_speedconvCfg_thi();
    init_speedconvCfg_fou();
    init_speedconvCfg_fif();
    init_mtdCfg();
    init_utcCfg();
    init_captureCfg();
    init_OSDCfg();
    init_resl();
    init_realtime_output();


    this->setWindowTitle("控制界面");
    a = POINTX;
    b = POINTY;

    this->resize(580,450);

    serialPort_command = new QSerialPort(this);
    connect(this,&MainWindow::copy_Done, this ,&MainWindow::parse_bytearray);


    thread_01 = new recSerial(this);//定义一个线程对象（接收）
    connect(this,&MainWindow::destroyed, this,&MainWindow::stop_thread_now);
    thread_run = true;
    thread_01->start();

    socket = new QTcpSocket(this);
    //connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    connect(this,&MainWindow::socket_copy_Done, this ,&MainWindow::socket_parse_bytearray);
	connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    thread_socket = new RcvSocketdata(this);
    thread_run_socket = true;
    //thread_socket->start();

    time=new QTimer(this);
    connect(time,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
	socket_time=new QTimer(this);
    connect(socket_time,SIGNAL(timeout()),this,SLOT(socketTimeoutSlot()));

    usocket = new QTcpSocket(this);
    thread_usocket = new RcvUSocketdata(this);
    connect(this,&MainWindow::usocket_copy_Done, this ,&MainWindow::usocket_parse_bytearray);
    connect(thread_usocket,&RcvUSocketdata::socket2main_signal, this, &MainWindow::upgrade_showtext);
    thread_run_usocket = true;
    //thread_usocket->start();


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
        //return;
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
    /*

    int c_channel = box1->currentText().toInt();
    send_mutex.lock();
    send_arr[4] = 02;
    send_arr[5] = c_channel-1;
    send_oneframe(2);
    send_mutex.unlock();
    */

}



void MainWindow::btn_vediosersor_fix_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 23;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 24;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_fix_update_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::fixChanelNum_Slot(int i)
{
    float value= 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=00;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=00;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fixchanel_enable_Slot(int i)
{
    float value= 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=02;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=02;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fix_vediohaveornot_Slot(int i)
{
    float value= 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=03;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4]=0x30;
        send_arr[5]=23;
        send_arr[6]=03;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fix_vedio_dpi_Slot(int index)
{
    if(index == 4)
        index = 5;

    float value = index;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=23;
    send_arr[6]=04;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gateshow_Slot(int i)
{
    float value = 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 07;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 07;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fix_bullshow_Slot(int i)
{
    float value = 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 8;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 8;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fix_autogate_Slot(int i)
{
    float value = 0;
    if(i == Qt::Checked){
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 9;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 9;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::fix_gate_sizex_Slot()
{
    float value=fix_gate_sizex->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::gate_sizex_Slot()
{
    float value=gate_sizex->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gate_sizex_Slot()
{
    float value=continue_gate_sizex->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gate_sizex_Slot_sec()
{
    float value=continue_gate_sizex_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_Slot()
{
    float value=fix_gate_sizey->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gate_sizey_Slot_sec()
{
    float value=fix_gate_sizey_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::gate_sizey_Slot()
{
    float value=gate_sizey->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gate_sizey_Slot()
{
    float value=continue_gate_sizey->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationx_Slot()
{
    float value=fix_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::gatelocationx_Slot()
{
    float value=gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gatelocationx_Slot()
{
    float value=continue_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gatelocationx_Slot_sec()
{
    float value=continue_gatelocationx_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationy_Slot()
{
    float value=fix_gatelocationy->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::gatelocationy_Slot()
{
    float value=gatelocationy->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gatelocationy_Slot()
{
    float value=continue_gatelocationy->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 23;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gatelocationy_Slot_sec()
{
    float value=continue_gatelocationy_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::set_azimuth_Slot()
{
    unsigned short value=ledt_set_azimuth->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_azimuth_Slot()
{
    unsigned short value=Change_ledt_set_azimuth->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_azimuth_Slot()
{
    unsigned short value=continue_ledt_set_azimuth->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_azimuth_Slot_sec()
{
    unsigned short value=continue_ledt_set_azimuth_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_pitch_Slot()
{
    unsigned short value=ledt_set_pitch->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_pitch_Slot()
{
    unsigned short value=Change_ledt_set_pitch->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_pitch_Slot()
{
    unsigned short value=continue_ledt_set_pitch->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_pitch_Slot_sec()
{
    unsigned short value=continue_ledt_set_pitch_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_zoom_Slot()
{
    unsigned short value=ledt_set_zoom->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_zoom_Slot()
{
    unsigned short value=Change_ledt_set_zoom->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_zoom_Slot()
{
    unsigned short value=continue_ledt_set_zoom->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_zoom_Slot_sec()
{
    unsigned short value=continue_ledt_set_zoom_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::search_azimuth_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x60;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::search_pitch_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x61;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::search_zoom_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x62;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::fix_lEdt_Slot()
{
    float value=fix_lEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vertical_Slot()
{
    float value=fix_vertical->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_sp_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =2;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_sp2_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =3;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::btn_vediosersor_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 23;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 25;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 26;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_continue_default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 23;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 27;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 56;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 57;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_continue_default_Slot_sec()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 58;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 62;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 63;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 64;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_continue_default_Slot_thi()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 65;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 69;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 70;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 71;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::vedio_fovclass_Slot(int i)
{
    float value = i;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x25;
    send_arr[6] = 0x00;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov0_Slot()
{
    float valuef=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =1;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_s1_Fov1_Slot()
{
    float valuef=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov2_Slot()
{
    float valuef=vedio_s1_Fov2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =9;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov3_Slot()
{
    float valuef=vedio_s1_Fov3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =13;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov4_Slot()
{
    float valuef=vedio_s1_Fov4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =1;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical1_Slot()
{
    float valuef=Change_vertical1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =2;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::Change_vertical2_Slot()
{
    float valuef=Change_vertical2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =6;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical3_Slot()
{
    float valuef=Change_vertical3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =10;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical4_Slot()
{
    float valuef=Change_vertical4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =14;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical5_Slot()
{
    float valuef=Change_vertical5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =2;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch1_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =3;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch2_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =7;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch3_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =11;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch4_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =15;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch5_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =3;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch1_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =4;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch2_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =8;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch3_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =12;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch4_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =0;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch5_Slot(int value)
{
    float valuef = value;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =4;
    memcpy(send_arr+7,&valuef,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::test_1_Slot()
{
    float value=test_1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l1_continue_Slot()
{
    float value=vedio_l1_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l2_continue_Slot()
{
    float value=vedio_l2_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l3_continue_Slot()
{
    float value=vedio_l3_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l4_continue_Slot()
{
    float value=vedio_l4_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l5_continue_Slot()
{
    float value=vedio_l5_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l6_continue_Slot()
{
    float value=vedio_l6_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l7_continue_Slot()
{
    float value=vedio_l7_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov0_Slot()
{
    float value=vedio_continue_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov1_Slot()
{
    float value=vedio_continue_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov2_Slot()
{
    float value=vedio_continue_Fov2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov3_Slot()
{
    float value=vedio_continue_Fov3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov4_Slot()
{
    float value=vedio_continue_Fov4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov5_Slot()
{
    float value=vedio_continue_Fov5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov6_Slot()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov7_Slot()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical1_Slot()
{
    float value=continue_vertical1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical2_Slot()
{
    float value=continue_vertical2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::continue_vertical3_Slot()
{
    float value=continue_vertical3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical4_Slot()
{
    float value=continue_vertical4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical5_Slot()
{
    float value=continue_vertical5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical6_Slot()
{
    float value=continue_vertical6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical7_Slot()
{
    float value=continue_vertical7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue1_Slot()
{
    float value=vedio_spbx_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue2_Slot()
{
    float value=vedio_spbx_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue3_Slot()
{
    float value=vedio_spbx_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue4_Slot()
{
    float value=vedio_spbx_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue5_Slot()
{
    float value=vedio_spbx_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue6_Slot()
{
    float value=vedio_spbx_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue7_Slot()
{
    float value=vedio_spbx_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue1_Slot()
{
    float value=vedio_spby_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue2_Slot()
{
    float value=vedio_spby_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue3_Slot()
{
    float value=vedio_spby_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue4_Slot()
{
    float value=vedio_spby_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue5_Slot()
{
    float value=vedio_spby_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue6_Slot()
{
    float value=vedio_spby_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue7_Slot()
{
    float value=vedio_spby_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
//通道二
void MainWindow::fixChanelNum_Slot_sec()
{
    int i = fixChanelNum_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_ChanelNum_Slot_sec()
{
    int i = ChanelNum_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_ChanelNum_Slot_sec()
{
    int i = continueChanelNum_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fixchanelname_Slot_sec()
{
    int i = fixenable_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_chanelname_Slot_sec()
{
    int i = enable_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_chanelname_Slot_sec()
{
    int i = continueenable_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vediohaveornot_Slot_sec()
{
    int i = fix_vediohaveornot_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_vediohaveornot_Slot_sec()
{
    int i = vediohaveornot_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vediohaveornot_Slot_sec()
{
    int i = continue_vediohaveornot_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vedio_dpi_Slot_sec(int index)
{
    float value = index;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=4;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gateshow_Slot_sec()
{
    int i = fix_gateshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_gateshow_Slot_sec()
{
    int i = gateshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gateshow_Slot_sec()
{
    int i = continue_gateshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_bullshow_Slot_sec()
{
    int i = fix_bullshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_bullshow_Slot_sec()
{
    int i = bullshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_bullshow_Slot_sec()
{
    int i = continue_bullshow_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_autogate_Slot_sec()
{
    int i = fix_autogate_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_autogate_Slot_sec()
{
    int i = autogate_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_autogate_Slot_sec()
{
    int i = continue_autogate_sec->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=58;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizex_Slot_sec()
{
    float value=fix_gate_sizex_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_Slot_sec()
{
    float value=fix_gate_sizey_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_gatelocationx_Slot_sec()
{
    float value=fix_gatelocationx_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizex_change_Slot_sec()
{
    float value=gate_sizex_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_change_Slot_sec()
{
    float value=gate_sizey_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationx_change_Slot_sec()
{
    float value=gatelocationx_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationy_change_Slot_sec()
{
    float value=gatelocationy_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationy_Slot_sec()
{
    float value=fix_gatelocationy_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 58;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::set_azimuth_Slot_sec()
{
    unsigned short value=ledt_set_azimuth_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_azimuth_change_Slot_sec()
{
    unsigned short value=Change_ledt_set_azimuth_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_pitch_Slot_sec()
{
    unsigned short value=ledt_set_pitch_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_pitch_change_Slot_sec()
{
    unsigned short value=Change_ledt_set_pitch_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_zoom_Slot_sec()
{
    unsigned short value=ledt_set_zoom_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_zoom_change_Slot_sec()
{
    unsigned short value=Change_ledt_set_zoom_sec->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::fix_lEdt_Slot_sec()
{
    float value=fix_lEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =59;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vertical_Slot_sec()
{
    float value=fix_vertical_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =59;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_sp_Slot_sec()
{
    float value=fix_sp_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =59;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_sp2_Slot_sec()
{
    float value=fix_sp2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =59;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_default_Slot_sec()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 58;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 60;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 61;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::vedio_fovclass_Slot_sec(int i)
{
    float value = i;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 60;
    send_arr[6] = 0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov0_Slot_sec()
{
    float value=vedio_s1_Fov0_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_s1_Fov1_Slot_sec()
{
    float value=vedio_s1_Fov1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov2_Slot_sec()
{
    float value=vedio_s1_Fov2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov3_Slot_sec()
{
    float value=vedio_s1_Fov3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov4_Slot_sec()
{
    float value=vedio_s1_Fov4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =61;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical1_Slot_sec()
{
    float value=Change_vertical1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::Change_vertical2_Slot_sec()
{
    float value=Change_vertical2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical3_Slot_sec()
{
    float value=Change_vertical3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical4_Slot_sec()
{
    float value=Change_vertical4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical5_Slot_sec()
{
    float value=Change_vertical5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =61;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch1_Slot_sec()
{
    float value=vedio_spbx_switch1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch2_Slot_sec()
{
    float value=vedio_spbx_switch2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch3_Slot_sec()
{
    float value=vedio_spbx_switch3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch4_Slot_sec()
{
    float value=vedio_spbx_switch4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch5_Slot_sec()
{
    float value=vedio_spbx_switch5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =61;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch1_Slot_sec()
{
    float value=vedio_spby_switch1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch2_Slot_sec()
{
    float value=vedio_spby_switch2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch3_Slot_sec()
{
    float value=vedio_spby_switch3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =60;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch4_Slot_sec()
{
    float value=vedio_spby_switch4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =61;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch5_Slot_sec()
{
    float value=vedio_spby_switch5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =61;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::test_1_Slot_sec()
{
    float value = test_1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =64;
    send_arr[6] =3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l1_continue_Slot_sec()
{
    float value=vedio_l1_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_l2_continue_Slot_sec()
{
    float value=vedio_l2_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l3_continue_Slot_sec()
{
    float value=vedio_l3_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l4_continue_Slot_sec()
{
    float value=vedio_l4_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l5_continue_Slot_sec()
{
    float value=vedio_l5_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l6_continue_Slot_sec()
{
    float value=vedio_l6_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l7_continue_Slot_sec()
{
    float value=vedio_l7_continue_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov0_Slot_sec()
{
    float value=vedio_continue_Fov0_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov1_Slot_sec()
{
    float value=vedio_continue_Fov1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov2_Slot_sec()
{
    float value=vedio_continue_Fov2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov3_Slot_sec()
{
    float value=vedio_continue_Fov3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov4_Slot_sec()
{
    float value=vedio_continue_Fov4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov5_Slot_sec()
{
    float value=vedio_continue_Fov5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov6_Slot_sec()
{
    float value=vedio_continue_Fov6_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical1_Slot_sec()
{
    float value=continue_vertical1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical2_Slot_sec()
{
    float value=continue_vertical2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::continue_vertical3_Slot_sec()
{
    float value=continue_vertical3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical4_Slot_sec()
{
    float value=continue_vertical4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical5_Slot_sec()
{
    float value=continue_vertical5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical6_Slot_sec()
{
    float value=continue_vertical6_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical7_Slot_sec()
{
    float value=continue_vertical7_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =64;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue1_Slot_sec()
{
    float value=vedio_spbx_continue1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue2_Slot_sec()
{
    float value=vedio_spbx_continue2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue3_Slot_sec()
{
    float value=vedio_spbx_continue3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue4_Slot_sec()
{
    float value=vedio_spbx_continue4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue5_Slot_sec()
{
    float value=vedio_spbx_continue5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue6_Slot_sec()
{
    float value=vedio_spbx_continue6_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue7_Slot_sec()
{
    float value=vedio_spbx_continue7_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =64;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue1_Slot_sec()
{
    float value=vedio_spby_continue1_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue2_Slot_sec()
{
    float value=vedio_spby_continue2_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue3_Slot_sec()
{
    float value=vedio_spby_continue3_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =62;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue4_Slot_sec()
{
    float value=vedio_spby_continue4_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue5_Slot_sec()
{
    float value=vedio_spby_continue5_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue6_Slot_sec()
{
    float value=vedio_spby_continue6_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =63;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue7_Slot_sec()
{
    float value=vedio_spby_continue7_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =64;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::btn_vediosersor_fix_default_Slot_sec()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 58;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 59;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_fix_default_Slot_thi()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 65;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 66;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::fixChanelNum_Slot_thi()
{
    int i = fixChanelNum_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_ChanelNum_Slot_thi()
{
    int i = ChanelNum_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_ChanelNum_Slot_thi()
{
    int i = continueChanelNum_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fixchanelname_Slot_thi()
{
    int i = fixenable_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_chanelname_Slot_thi()
{
    int i = enable_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_chanelname_Slot_thi()
{
    int i = continueenable_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=2;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vediohaveornot_Slot_thi()
{
    int i = fix_vediohaveornot_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_vediohaveornot_Slot_thi()
{
    int i = vediohaveornot_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vediohaveornot_Slot_thi()
{
    int i = continue_vediohaveornot_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_vedio_dpi_Slot_thi(int index)
{
    float value = index;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=4;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gateshow_Slot_thi()
{
    int i = fix_gateshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_gateshow_Slot_thi()
{
    int i = gateshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_gateshow_Slot_thi()
{
    int i = continue_gateshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=7;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_bullshow_Slot_thi()
{
    int i = fix_bullshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_bullshow_Slot_thi()
{
    int i = bullshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_bullshow_Slot_thi()
{
    int i = continue_bullshow_thi->isChecked();
    float value = i;

    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=8;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_autogate_Slot_thi()
{
    int i = fix_autogate_thi->isChecked();
    float value = i;

    value = 1;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_autogate_Slot_thi()
{
    int i = autogate_thi->isChecked();
    float value = i;

    value = 1;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_autogate_Slot_thi()
{
    int i = continue_autogate_thi->isChecked();
    float value = i;

    value = 1;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=65;
    send_arr[6]=9;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizex_Slot_thi()
{
    float value=fix_gate_sizex_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_Slot_thi()
{
    float value=fix_gate_sizey_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}


void MainWindow::change_fix_gate_sizex_Slot_thi()
{
    float value=gate_sizex_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_fix_gate_sizey_Slot_thi()
{
    float value=gate_sizey_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_fix_gate_sizex_Slot_thi()
{
    float value=continue_gate_sizex_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_fix_gate_sizey_Slot_thi()
{
    float value=continue_gate_sizey_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationx_Slot_thi()
{
    float value=fix_gatelocationx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gatelocationy_Slot_thi()
{
    float value=fix_gatelocationy_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_fix_gatelocationx_Slot_thi()
{
    float value=gatelocationx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::change_fix_gatelocationy_Slot_thi()
{
    float value=gatelocationy_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_fix_gatelocationx_Slot_thi()
{
    float value=continue_gatelocationx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_fix_gatelocationy_Slot_thi()
{
    float value=continue_gatelocationx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 65;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::set_azimuth_Slot_thi()
{
    unsigned short value=ledt_set_azimuth_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_azimuth_Slot_thi()
{
    unsigned short value=Change_ledt_set_azimuth_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_azimuth_Slot_thi()
{
    unsigned short value=continue_ledt_set_azimuth_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_pitch_Slot_thi()
{
    unsigned short value=ledt_set_pitch_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_pitch_Slot_thi()
{
    unsigned short value=Change_ledt_set_pitch_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_pitch_Slot_thi()
{
    unsigned short value=continue_ledt_set_pitch_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::set_zoom_Slot_thi()
{
    unsigned short value=ledt_set_zoom_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::change_set_zoom_Slot_thi()
{
    unsigned short value=Change_ledt_set_zoom_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::continue_set_zoom_Slot_thi()
{
    unsigned short value=continue_ledt_set_zoom_thi->text().toUShort();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,2);
    send_oneframe(3);
    send_mutex.unlock();
}

void MainWindow::fix_lEdt_Slot_thi()
{
    float value=fix_lEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =66;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_vertical_Slot_thi()
{
    float value=fix_vertical_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =66;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp_Slot_thi()
{
    float value=fix_sp_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =66;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp2_Slot_thi()
{
    float value=fix_sp2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =66;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::btn_vediosersor_default_Slot_thi()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 65;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 67;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 68;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::vedio_fovclass_Slot_thi(int i)
{
    float value = i;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 67;
    send_arr[6] = 0;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov0_Slot_thi()
{
    float value=vedio_s1_Fov0_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_s1_Fov1_Slot_thi()
{
    float value=vedio_s1_Fov1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov2_Slot_thi()
{
    float value=vedio_s1_Fov2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov3_Slot_thi()
{
    float value=vedio_s1_Fov3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov4_Slot_thi()
{
    float value=vedio_s1_Fov4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =68;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical1_Slot_thi()
{
    float value=Change_vertical1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::Change_vertical2_Slot_thi()
{
    float value=Change_vertical2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical3_Slot_thi()
{
    float value=Change_vertical3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical4_Slot_thi()
{
    float value=Change_vertical4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical5_Slot_thi()
{
    float value=Change_vertical5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =68;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch1_Slot_thi()
{
    float value=vedio_spbx_switch1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch2_Slot_thi()
{
    float value=vedio_spbx_switch2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch3_Slot_thi()
{
    float value=vedio_spbx_switch3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch4_Slot_thi()
{
    float value=vedio_spbx_switch4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch5_Slot_thi()
{
    float value=vedio_spbx_switch5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =68;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch1_Slot_thi()
{
    float value=vedio_spby_switch1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch2_Slot_thi()
{
    float value=vedio_spby_switch2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch3_Slot_thi()
{
    float value=vedio_spby_switch3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =67;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch4_Slot_thi()
{
    float value=vedio_spby_switch4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =68;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch5_Slot_thi()
{
    float value=vedio_spby_switch5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =68;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::test_1_Slot_thi()
{
    float value = test_1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =71;
    send_arr[6] =3;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l1_continue_Slot_thi()
{
    float value=vedio_l1_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l2_continue_Slot_thi()
{
    float value=vedio_l2_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l3_continue_Slot_thi()
{
    float value=vedio_l3_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l4_continue_Slot_thi()
{
    float value=vedio_l4_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l5_continue_Slot_thi()
{
    float value=vedio_l5_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l6_continue_Slot_thi()
{
    float value=vedio_l6_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l7_continue_Slot_thi()
{
    float value=vedio_l7_continue_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov0_Slot_thi()
{
    float value=vedio_continue_Fov0_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov1_Slot_thi()
{
    float value=vedio_continue_Fov1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov2_Slot_thi()
{
    float value=vedio_continue_Fov2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov3_Slot_thi()
{
    float value=vedio_continue_Fov3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov4_Slot_thi()
{
    float value=vedio_continue_Fov4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov5_Slot_thi()
{
    float value=vedio_continue_Fov5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov6_Slot_thi()
{
    float value=vedio_continue_Fov6_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical1_Slot_thi()
{
    float value=continue_vertical1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical2_Slot_thi()
{
    float value=continue_vertical2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::continue_vertical3_Slot_thi()
{
    float value=continue_vertical3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical4_Slot_thi()
{
    float value=continue_vertical4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical5_Slot_thi()
{
    float value=continue_vertical5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical6_Slot_thi()
{
    float value=continue_vertical6_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical7_Slot_thi()
{
    float value=continue_vertical7_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =71;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue1_Slot_thi()
{
    float value=vedio_spbx_continue1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue2_Slot_thi()
{
    float value=vedio_spbx_continue2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue3_Slot_thi()
{
    float value=vedio_spbx_continue3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue4_Slot_thi()
{
    float value=vedio_spbx_continue4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue5_Slot_thi()
{
    float value=vedio_spbx_continue5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue6_Slot_thi()
{
    float value=vedio_spbx_continue6_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue7_Slot_thi()
{
    float value=vedio_spbx_continue7_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =71;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue1_Slot_thi()
{
    float value=vedio_spby_continue1_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue2_Slot_thi()
{
    float value=vedio_spby_continue2_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue3_Slot_thi()
{
    float value=vedio_spby_continue3_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =69;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue4_Slot_thi()
{
    float value=vedio_spby_continue4_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue5_Slot_thi()
{
    float value=vedio_spby_continue5_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue6_Slot_thi()
{
    float value=vedio_spby_continue6_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =70;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue7_Slot_thi()
{
    float value=vedio_spby_continue7_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =71;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_fix_default_Slot_fou()
{

}

void MainWindow::btn_vediosersor_fix_update_Slot_fou()
{

}

void MainWindow::fixChanelNum_Slot_fou(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x50;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x50;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::fixchanelname_Slot_fou()
{

}

void MainWindow::fix_vediohaveornot_Slot_fou(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x52;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x52;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_vedio_dpi_Slot_fou(int index)
{
    switch(index)
    {
        case 0:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
            break;
        case 1:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
            break;
        case 2:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x02;
        send_oneframe(2);
        send_mutex.unlock();
        break;
        case 3:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x03;
        send_oneframe(2);
        send_mutex.unlock();
        break;
         default:
        break;
    }


}

void MainWindow::fix_gateshow_Slot_fou(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x55;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x55;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_bullshow_Slot_fou(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x56;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x56;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_autogate_Slot_fou(int i)
{
    if( i== Qt::Checked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_gate_sizex_Slot_fou()
{
    float value=fix_gate_sizex->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_Slot_fou()
{
    float value=fix_gate_sizey->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_gatelocationx_Slot_fou()
{
    float value=fix_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_gatelocationy_Slot_fou()
{
    float value=fix_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::set_azimuth_Slot_fou()
{
    int value=ledt_set_azimuth->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::set_pitch_Slot_fou()
{
    int value=ledt_set_pitch->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::set_zoom_Slot_fou()
{
    int value=ledt_set_zoom->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::search_azimuth_Slot_fou()
{
    send_mutex.lock();
    send_arr[4] = 0x60;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::search_pitch_Slot_fou()
{
    send_mutex.lock();
    send_arr[4] = 0x61;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::search_zoom_Slot_fou()
{
    send_mutex.lock();
    send_arr[4] = 0x62;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::fix_lEdt_Slot_fou()
{
    float value=fix_lEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_vertical_Slot_fou()
{
    float value=fix_vertical->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp_Slot_fou()
{
    float value=fix_sp->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp2_Slot_fou()
{
    float value=fix_sp->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::btn_vediosersor_default_Slot_fou()
{

}

void MainWindow::btn_vediosersor_update_Slot_fou()
{

}

void MainWindow::vedio_fovclass_Slot_fou(int i)
{
    switch (i) {
    case 0:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x03;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x04;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x05;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;



}

}

void MainWindow::vedio_s1_Fov0_Slot_fou()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_s1_Fov1_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov2_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov3_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov4_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical1_Slot_fou()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::Change_vertical2_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical3_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical4_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical5_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch1_Slot_fou()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch2_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch3_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch4_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch5_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch1_Slot_fou()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch2_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch3_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch4_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch5_Slot_fou()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::test_1_Slot_fou()
{
    int value=test_1->text().toInt();
    if(value ==1){
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =3;
    send_arr[7] =1;
    send_oneframe(7);
    send_mutex.unlock();
    }else if (value ==2) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =2;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==3) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =3;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==4) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =4;
        send_oneframe(7);
        send_mutex.unlock();

    }
    else if (value ==5) {
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] =57;
            send_arr[6] =3;
            send_arr[7] =5;
            send_oneframe(7);
            send_mutex.unlock();

        }else if (value ==6) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =6;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==7) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =7;
        send_oneframe(7);
        send_mutex.unlock();

    }
}

void MainWindow::vedio_l1_continue_Slot_fou()
{
    float value=vedio_l1_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_l2_continue_Slot_fou()
{
    float value=vedio_l2_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l3_continue_Slot_fou()
{
    float value=vedio_l3_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l4_continue_Slot_fou()
{
    float value=vedio_l4_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l5_continue_Slot_fou()
{
    float value=vedio_l5_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l6_continue_Slot_fou()
{
    float value=vedio_l6_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l7_continue_Slot_fou()
{
    float value=vedio_l7_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov0_Slot_fou()
{
    float value=vedio_continue_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov1_Slot_fou()
{
    float value=vedio_continue_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov2_Slot_fou()
{
    float value=vedio_continue_Fov2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov3_Slot_fou()
{
    float value=vedio_continue_Fov3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov4_Slot_fou()
{
    float value=vedio_continue_Fov4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov5_Slot_fou()
{
    float value=vedio_continue_Fov5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov6_Slot_fou()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov7_Slot_fou()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical1_Slot_fou()
{
    float value=continue_vertical1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical2_Slot_fou()
{
    float value=continue_vertical2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::continue_vertical3_Slot_fou()
{
    float value=continue_vertical3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical4_Slot_fou()
{
    float value=continue_vertical4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical5_Slot_fou()
{
    float value=continue_vertical5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical6_Slot_fou()
{
    float value=continue_vertical6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical7_Slot_fou()
{
    float value=continue_vertical7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue1_Slot_fou()
{
    float value=vedio_spbx_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue2_Slot_fou()
{
    float value=vedio_spbx_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue3_Slot_fou()
{
    float value=vedio_spbx_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue4_Slot_fou()
{
    float value=vedio_spbx_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue5_Slot_fou()
{
    float value=vedio_spbx_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue6_Slot_fou()
{
    float value=vedio_spbx_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue7_Slot_fou()
{
    float value=vedio_spbx_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue1_Slot_fou()
{
    float value=vedio_spby_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue2_Slot_fou()
{
    float value=vedio_spby_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue3_Slot_fou()
{
    float value=vedio_spby_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue4_Slot_fou()
{
    float value=vedio_spby_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue5_Slot_fou()
{
    float value=vedio_spby_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue6_Slot_fou()
{
    float value=vedio_spby_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue7_Slot_fou()
{
    float value=vedio_spby_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_vediosersor_fix_default_Slot_fif()
{

}

void MainWindow::btn_vediosersor_fix_update_Slot_fif()
{

}
//
void MainWindow::fixChanelNum_Slot_fif(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x50;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x50;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::fixchanelname_Slot_fif()
{

}

void MainWindow::fix_vediohaveornot_Slot_fif(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x52;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x52;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_vedio_dpi_Slot_fif(int index)
{
    switch(index)
    {
        case 0:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
            break;
        case 1:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
            break;
        case 2:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x02;
        send_oneframe(2);
        send_mutex.unlock();
        break;
        case 3:

        send_mutex.lock();
        send_arr[4] = 0x06;
        send_arr[5] = 0x03;
        send_oneframe(2);
        send_mutex.unlock();
        break;
         default:
        break;
    }


}

void MainWindow::fix_gateshow_Slot_fif(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x55;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x55;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_bullshow_Slot_fif(int i)
{
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x56;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x56;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_autogate_Slot_fif(int i)
{
    if( i== Qt::Checked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked)
    {
        send_mutex.lock();
        send_arr[4] = 0x0d;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }

}

void MainWindow::fix_gate_sizex_Slot_fif()
{
    float value=fix_gate_sizex->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::fix_gate_sizey_Slot_fif()
{
    float value=fix_gate_sizey->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_gatelocationx_Slot_fif()
{
    float value=fix_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_gatelocationy_Slot_fif()
{
    float value=fix_gatelocationx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 0x23;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::set_azimuth_Slot_fif()
{
    int value=ledt_set_azimuth->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x57;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::set_pitch_Slot_fif()
{
    int value=ledt_set_pitch->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x58;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::set_zoom_Slot_fif()
{
    int value=ledt_set_zoom->text().toInt();
    send_mutex.lock();
    send_arr[4] = 0x59;
    memcpy(send_arr+5,&value,4);
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::search_azimuth_Slot_fif()
{
    send_mutex.lock();
    send_arr[4] = 0x60;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::search_pitch_Slot_fif()
{
    send_mutex.lock();
    send_arr[4] = 0x61;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::search_zoom_Slot_fif()
{
    send_mutex.lock();
    send_arr[4] = 0x62;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::fix_lEdt_Slot_fif()
{
    float value=fix_lEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_vertical_Slot_fif()
{
    float value=fix_vertical->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp_Slot_fif()
{
    float value=fix_sp->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::fix_sp2_Slot_fif()
{
    float value=fix_sp->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =24;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::btn_vediosersor_default_Slot_fif()
{

}

void MainWindow::btn_vediosersor_update_Slot_fif()
{

}

void MainWindow::vedio_fovclass_Slot_fif(int i)
{
    switch (i) {
    case 0:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x01;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 1:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x02;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x03;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x04;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x25;
        send_arr[6] = 0x00;
        send_arr[7] = 0x05;
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;



}

}

void MainWindow::vedio_s1_Fov0_Slot_fif()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_s1_Fov1_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov2_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov3_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_s1_Fov4_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical1_Slot_fif()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::Change_vertical2_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical3_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical4_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::Change_vertical5_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch1_Slot_fif()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch2_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch3_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch4_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_switch5_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch1_Slot_fif()
{
    float value=vedio_s1_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch2_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch3_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =25;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch4_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_switch5_Slot_fif()
{
    float value=vedio_s1_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =26;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::test_1_Slot_fif()
{
    int value=test_1->text().toInt();
    if(value ==1){
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =3;
    send_arr[7] =1;
    send_oneframe(7);
    send_mutex.unlock();
    }else if (value ==2) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =2;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==3) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =3;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==4) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =4;
        send_oneframe(7);
        send_mutex.unlock();

    }
    else if (value ==5) {
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] =57;
            send_arr[6] =3;
            send_arr[7] =5;
            send_oneframe(7);
            send_mutex.unlock();

        }else if (value ==6) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =6;
        send_oneframe(7);
        send_mutex.unlock();

    }else if (value ==7) {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] =57;
        send_arr[6] =3;
        send_arr[7] =7;
        send_oneframe(7);
        send_mutex.unlock();

    }
}

void MainWindow::vedio_l1_continue_Slot_fif()
{
    float value=vedio_l1_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::vedio_l2_continue_Slot_fif()
{
    float value=vedio_l2_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l3_continue_Slot_fif()
{
    float value=vedio_l3_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l4_continue_Slot_fif()
{
    float value=vedio_l4_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l5_continue_Slot_fif()
{
    float value=vedio_l5_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l6_continue_Slot_fif()
{
    float value=vedio_l6_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_l7_continue_Slot_fif()
{
    float value=vedio_l7_continue->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov0_Slot_fif()
{
    float value=vedio_continue_Fov0->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov1_Slot_fif()
{
    float value=vedio_continue_Fov1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov2_Slot_fif()
{
    float value=vedio_continue_Fov2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov3_Slot_fif()
{
    float value=vedio_continue_Fov3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov4_Slot_fif()
{
    float value=vedio_continue_Fov4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov5_Slot_fif()
{
    float value=vedio_continue_Fov5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov6_Slot_fif()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_continue_Fov7_Slot_fif()
{
    float value=vedio_continue_Fov6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical1_Slot_fif()
{
    float value=continue_vertical1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical2_Slot_fif()
{
    float value=continue_vertical2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


void MainWindow::continue_vertical3_Slot_fif()
{
    float value=continue_vertical3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical4_Slot_fif()
{
    float value=continue_vertical4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical5_Slot_fif()
{
    float value=continue_vertical5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical6_Slot_fif()
{
    float value=continue_vertical6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::continue_vertical7_Slot_fif()
{
    float value=continue_vertical7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue1_Slot_fif()
{
    float value=vedio_spbx_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue2_Slot_fif()
{
    float value=vedio_spbx_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue3_Slot_fif()
{
    float value=vedio_spbx_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue4_Slot_fif()
{
    float value=vedio_spbx_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue5_Slot_fif()
{
    float value=vedio_spbx_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue6_Slot_fif()
{
    float value=vedio_spbx_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spbx_continue7_Slot_fif()
{
    float value=vedio_spbx_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue1_Slot_fif()
{
    float value=vedio_spby_continue1->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue2_Slot_fif()
{
    float value=vedio_spby_continue2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue3_Slot_fif()
{
    float value=vedio_spby_continue3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =27;
    send_arr[6] =14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue4_Slot_fif()
{
    float value=vedio_spby_continue4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue5_Slot_fif()
{
    float value=vedio_spby_continue5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue6_Slot_fif()
{
    float value=vedio_spby_continue6->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =56;
    send_arr[6] =13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::vedio_spby_continue7_Slot_fif()
{
    float value=vedio_spby_continue7->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] =57;
    send_arr[6] =2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}


//
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

void MainWindow::btn_keep1_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::btn_osd_update_Slot()
{
    if(checkBox->isChecked()){


    if(checkBox2->isChecked()){
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
        send_arr[12]=CBox_transparency->currentIndex();
        for(int i=0;i<dd.size();i++){
           int addr1=dd[i] & 0x000000FF;
           send_arr[13+i]=addr1;
        }
        send_oneframe(length);
        send_mutex.unlock();
    }
    }
    else
    {
        QMessageBox::warning(this,"警告","请点击用户自定义字符显示使能开关",QMessageBox::Ok);
    }
}

void MainWindow::CBox_osd_choose_Slot(int i)
{
    osd1_lineEdit_context->clear();
    osd1_pos_y->clear();
    osd1_pos_x->clear();
    //osd1_lineEdit_transparency->clear();
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
    if(i == Qt::Checked){

        send_mutex.lock();
        send_arr[4]=0x48;
        send_arr[5]=0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked){
        send_mutex.lock();
        send_arr[4]=0x48;
        send_arr[5]=0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}
void MainWindow::checkBox_cross_Slot()
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

void MainWindow::checkBox_channel_Slot()
{
    int value = 0xFF;
    //box1->clear();
    if(checkBox_channel1->isChecked())
    {
        value |= 1;
        //box1->addItem("1");
    }
    else
        value &= ~(1);

    if(checkBox_channel2->isChecked())
    {
        value |= (1<<1);
        //box1->addItem("2");
    }
    else
        value &= ~(1<<1);

    if(checkBox_channel3->isChecked())
    {
        value |= (1<<2);
        //box1->addItem("3");
    }
    else
        value &= ~(1<<2);

    if(checkBox_channel4->isChecked())
    {
        value |= (1<<3);
        //box1->addItem("4");
    }
    else
        value &= ~(1<<3);

    if(checkBox_channel5->isChecked())
    {
        value |= (1<<4);
        //box1->addItem("5");
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
    float value = 0;
    switch (BG1->checkedId()) {
    case 1:
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 0;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 0;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        value = 2;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 0;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        value = 3;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 0;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle2_Slot()
{
    float value = 0;
    switch (BG2->checkedId()) {
    case 1:
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 1;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 1;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        value = 2;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 1;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        value = 3;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 1;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle3_Slot()
{
    float value = 0;
    switch (BG3->checkedId()) {
    case 1:
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 2;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 2;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        value = 2;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 2;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        value = 3;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 2;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle4_Slot()
{
    float value = 0;
    switch (BG4->checkedId()) {
    case 1:
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 3;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 2:
        value = 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 3;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 3:
        value = 2;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 3;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    case 4:
        value = 3;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 3;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_aisle5_Slot()
{
    float value = 0;
    switch (BG5->checkedId()) {
    case 1:
        value = 0;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 51;
        send_arr[6] = 4;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        break;
    default:
        break;
    }
}

void MainWindow::btn_resolution_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x06;
    send_arr[5] = BG1->checkedId()-1;
    send_arr[6] = BG2->checkedId()-1;
    send_arr[7] = BG3->checkedId()-1;
    send_arr[8] = BG4->checkedId()-1;
    send_arr[9] = BG5->checkedId()-1;
    send_oneframe(6);
    send_mutex.unlock();
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
/*
void MainWindow::CBox_View_Slot(int i)
{
    send_mutex.lock();
    send_arr[4]=0x11;
    send_arr[5]=i;
    send_oneframe(2);
    send_mutex.unlock();
}
*/
void MainWindow::CBox_osd_color_Slot(int i)
{

}

void MainWindow::CBox_transparency_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x20;
    send_arr[5] =CBox_font->currentIndex()+1;

    send_oneframe(2);
    send_mutex.unlock();

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

void MainWindow::callback_autobomen(int arg1)
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

void MainWindow::btn_mtd_Default_Slot()
{
        send_mutex.lock();
        send_arr[4] = 0x09;
        send_arr[5] = 54;
        send_oneframe(2);
        send_mutex.unlock();

}

void MainWindow::btn_mtd_Update_Slot()
{
        send_mutex.lock();
        send_arr[4] = 0x34;
        send_oneframe(1);
        send_mutex.unlock();

}

void MainWindow::zone_setting_Slot()
{
    if(zone_setting->isChecked())
    {
        send_mutex.lock();
        send_arr[4] = 0x47;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock(); 
    }
    else
    {
        send_mutex.lock();
        send_arr[4] = 0x47;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::lEdt_rigion_Slot()
{/*
        //float value=rigion->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 0;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
        */

}

void MainWindow::lEdt_rigion_Cen_x_Slot()
{
    float value=rigion_Cen_x->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 10;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_rigion_Cen_y_Slot()
{
    float value=rigion_Cen_y->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 11;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_rigion_Cen_w_Slot()
{
    float value=rigion_Cen_w->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 12;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_rigion_Cen_h_Slot()
{
    float value=rigion_Cen_h->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 13;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_maxnum_Slot()
{
    float value=maxnum->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 1;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_uspeed_Slot()
{
        float value=uspeed->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 2;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_maxpix_Slot()
{
    float value=maxpix->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 3;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_minpix_Slot()
{
    float value=minpix->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 4;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_sensitive_Slot()
{
    float value=sensitive->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 5;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
}

void MainWindow::lEdt_dspeed_Slot()
{
    float value=dspeed->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 6;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::lEdt_trktime_Slot()
{
    float value=trktime->text().toFloat();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 54;
        send_arr[6] = 7;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();

}

void MainWindow::combox_Priority_judgment_Slot(int index)
{
    float value;
        printf("index = %d\n", index);
        switch(index)
        {
            case 0:
            value = 1.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            case 1:
            value = 2.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            case 2:
            value = 3.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
            case 3:
            value = 4.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            case 4:
            value = 5.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            case 5:
            value = 6.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 14;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
            default:
                break;
        }

}

void MainWindow::combox_output_Slot(int index)
{
    float value;
        printf("index = %d\n", index);
        switch(index)
        {
            case 0:
            value = 1.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 8;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            case 1:
            value = 2.0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 54;
            send_arr[6] = 8;
            send_arr[7] = value;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
                break;
            default:
                break;
        }

}

void MainWindow::combox_polar_Slot(int index)
{

        float value;
            printf("index = %d\n", index);
            switch(index)
            {
                case 0:
                value = 1.0;
                send_mutex.lock();
                send_arr[4] = 0x30;
                send_arr[5] = 54;
                send_arr[6] = 9;
                send_arr[7] = value;
                memcpy(send_arr+7,&value,4);
                send_oneframe(7);
                send_mutex.unlock();
                    break;
                case 1:
                value = 2.0;
                send_mutex.lock();
                send_arr[4] = 0x30;
                send_arr[5] = 54;
                send_arr[6] = 9;
                send_arr[7] = value;
                memcpy(send_arr+7,&value,4);
                send_oneframe(7);
                send_mutex.unlock();
                    break;
                default:
                    break;
            }

}

void MainWindow::lEdt_Alarm_delay_Slot()
{
    float value=Alarm_delay->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 54;
    send_arr[6] = 15;
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

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 3;
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


void MainWindow::lEdt_maxspeedx_Slot()
{
    float value=maxspeedx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 3;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_maxspeedy_Slot()
{
    float value=maxspeedy->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 3;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deadx_Slot()
{
    float value=deadx->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 3;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deady_Slot()
{
    float value=deady->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 3;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_out_address_Slot()
{
    float value=out_address->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 52;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_output_d_type_Slot(int index)
{
        float value = index + 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 3;
        send_arr[6] = 14;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
}

void MainWindow::combox_baud_rate_type_Slot(int index)
{
    float value;
    switch(index)
    {
        case 0:
            value = 2400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 4800;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 9600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 19200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 4:
            value = 38400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 5:
            value = 57600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 6:
            value = 115200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_data_bit_type_Slot(int index)
{
    float value;
    switch (index)
    {
        case 0:
            value = 5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 6;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 7;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 8;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_stop_bit_type_Slot(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1.5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_parity_bit_type_Slot(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
         default:
            break;
    }
}

void MainWindow::combox_flow_control_type_Slot(int index)
{
    float value = index + 1;
    switch (index) {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 52;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::lEdt_speedx1_Slot_sec()
{
    float value=speedx1_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx2_Slot_sec()
{
    float value=speedx2_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx3_Slot_sec()
{
    float value=speedx3_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx4_Slot_sec()
{
    float value=speedx4_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx5_Slot_sec()
{
    float value=speedx5_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx6_Slot_sec()
{
    float value=speedx6_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx7_Slot_sec()
{
    float value=speedx7_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx8_Slot_sec()
{
    float value=speedx8_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx9_Slot_sec()
{
    float value=speedx9_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedx10_Slot_sec()
{
    float value=speedx10_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy1_Slot_sec()
{
    float value=speedy1_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy2_Slot_sec()
{
    float value=speedy2_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy3_Slot_sec()
{
    float value=speedy3_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy4_Slot_sec()
{
    float value=speedy4_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy5_Slot_sec()
{
    float value=speedy5_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy6_Slot_sec()
{
    float value=speedy6_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy7_Slot_sec()
{
    float value=speedy7_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 99;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy8_Slot_sec()
{
    float value=speedy8_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy9_Slot_sec()
{
    float value=speedy9_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedy10_Slot_sec()
{
    float value=speedy10_lineEdt_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}



void MainWindow::btn_Speed_Default_Slot_sec()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 99;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 100;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 107;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Update_Slot_sec()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_maxspeedx_Slot_sec()
{
    float value=maxspeedx_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_maxspeedy_Slot_sec()
{
    float value=maxspeedy_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deadx_Slot_sec()
{
    float value=deadx_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deady_Slot_sec()
{
    float value=deady_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 100;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_out_address_Slot_sec()
{
    float value=out_address_sec->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 107;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_output_d_type_Slot_sec(int index)
{
        float value = index + 1;
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 100;
        send_arr[6] = 8;
        memcpy(send_arr+7,&value,4);
        send_oneframe(7);
        send_mutex.unlock();
}

void MainWindow::combox_baud_rate_type_Slot_sec(int index)
{
    float value;
    switch(index)
    {
        case 0:
            value = 2400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 4800;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 9600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 19200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 4:
            value = 38400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 5:
            value = 57600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 6:
            value = 115200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_data_bit_type_Slot_sec(int index)
{
    float value;
    switch (index)
    {
        case 0:
            value = 5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 6;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 7;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 8;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_stop_bit_type_Slot_sec(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1.5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_parity_bit_type_Slot_sec(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
         default:
            break;
    }
}

void MainWindow::combox_flow_control_type_Slot_sec(int index)
{
    float value = index + 1;
    switch (index) {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 107;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::lEdt_speedx1_Slot_thi()
{
    float value=speedx1_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx2_Slot_thi()
{
    float value=speedx2_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx3_Slot_thi()
{
    float value=speedx3_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx4_Slot_thi()
{
    float value=speedx4_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx5_Slot_thi()
{
    float value=speedx5_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx6_Slot_thi()
{
    float value=speedx6_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx7_Slot_thi()
{
    float value=speedx7_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx8_Slot_thi()
{
    float value=speedx8_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx9_Slot_thi()
{
    float value=speedx9_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedx10_Slot_thi()
{
    float value=speedx10_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy1_Slot_thi()
{
    float value=speedy1_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy2_Slot_thi()
{
    float value=speedy2_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy3_Slot_thi()
{
    float value=speedy3_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy4_Slot_thi()
{
    float value=speedy4_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy5_Slot_thi()
{
    float value=speedy5_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy6_Slot_thi()
{
    float value=speedy6_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy7_Slot_thi()
{
    float value=speedy7_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 101;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy8_Slot_thi()
{
    float value=speedy8_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy9_Slot_thi()
{
    float value=speedy9_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedy10_Slot_thi()
{
    float value=speedy10_lineEdt_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}



void MainWindow::btn_Speed_Default_Slot_thi()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 101;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 102;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 108;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Update_Slot_thi()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_maxspeedx_Slot_thi()
{
    float value=maxspeedx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_maxspeedy_Slot_thi()
{
    float value=maxspeedy_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deadx_Slot_thi()
{
    float value=deadx_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deady_Slot_thi()
{
    float value=deady_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_out_address_Slot_thi()
{
    float value=out_address_thi->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 108;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_output_d_type_Slot_thi(int index)
{
    float value = index + 1;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 102;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_baud_rate_type_Slot_thi(int index)
{
    float value;
    switch(index)
    {
        case 0:
            value = 2400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 4800;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 9600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 19200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 4:
            value = 38400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 5:
            value = 57600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 6:
            value = 115200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_data_bit_type_Slot_thi(int index)
{
    float value;
    switch (index)
    {
        case 0:
            value = 5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 6;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 7;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 8;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_stop_bit_type_Slot_thi(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1.5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_parity_bit_type_Slot_thi(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
         default:
            break;
    }
}

void MainWindow::combox_flow_control_type_Slot_thi(int index)
{
    float value = index + 1;
    switch (index) {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 108;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::lEdt_speedx1_Slot_fou()
{
    float value=speedx1_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx2_Slot_fou()
{
    float value=speedx2_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx3_Slot_fou()
{
    float value=speedx3_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx4_Slot_fou()
{
    float value=speedx4_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx5_Slot_fou()
{
    float value=speedx5_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx6_Slot_fou()
{
    float value=speedx6_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx7_Slot_fou()
{
    float value=speedx7_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx8_Slot_fou()
{
    float value=speedx8_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx9_Slot_fou()
{
    float value=speedx9_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedx10_Slot_fou()
{
    float value=speedx10_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy1_Slot_fou()
{
    float value=speedy1_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy2_Slot_fou()
{
    float value=speedy2_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy3_Slot_fou()
{
    float value=speedy3_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy4_Slot_fou()
{
    float value=speedy4_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy5_Slot_fou()
{
    float value=speedy5_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy6_Slot_fou()
{
    float value=speedy6_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy7_Slot_fou()
{
    float value=speedy7_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 103;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy8_Slot_fou()
{
    float value=speedy8_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy9_Slot_fou()
{
    float value=speedy9_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedy10_Slot_fou()
{
    float value=speedy10_lineEdt_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Default_Slot_fou()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 103;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 104;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 109;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Update_Slot_fou()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_maxspeedx_Slot_fou()
{
    float value=maxspeedx_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_maxspeedy_Slot_fou()
{
    float value=maxspeedy_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deadx_Slot_fou()
{
    float value=deadx_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_deady_Slot_fou()
{
    float value=deady_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_out_address_Slot_fou()
{
    float value=out_address_fou->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 109;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_output_d_type_Slot_fou(int index)
{
    float value = index + 1;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 104;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_baud_rate_type_Slot_fou(int index)
{
    float value;
    switch(index)
    {
        case 0:
            value = 2400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 4800;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 9600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 19200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 4:
            value = 38400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 5:
            value = 57600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 6:
            value = 115200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_data_bit_type_Slot_fou(int index)
{
    float value;
    switch (index)
    {
        case 0:
            value = 5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 6;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 7;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 8;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_stop_bit_type_Slot_fou(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1.5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_parity_bit_type_Slot_fou(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
         default:
            break;
    }
}

void MainWindow::combox_flow_control_type_Slot_fou(int index)
{
    float value = index + 1;
    switch (index) {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 109;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::lEdt_speedx1_Slot_fif()
{
    float value=speedx1_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx2_Slot_fif()
{
    float value=speedx2_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx3_Slot_fif()
{
    float value=speedx3_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx4_Slot_fif()
{
    float value=speedx4_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx5_Slot_fif()
{
    float value=speedx5_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx6_Slot_fif()
{
    float value=speedx6_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx7_Slot_fif()
{
    float value=speedx7_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx8_Slot_fif()
{
    float value=speedx8_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedx9_Slot_fif()
{
    float value=speedx9_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedx10_Slot_fif()
{
    float value=speedx10_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 2;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy1_Slot_fif()
{
    float value=speedy1_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 9;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy2_Slot_fif()
{
    float value=speedy2_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 10;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy3_Slot_fif()
{
    float value=speedy3_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 11;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy4_Slot_fif()
{
    float value=speedy4_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 12;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy5_Slot_fif()
{
    float value=speedy5_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 13;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy6_Slot_fif()
{
    float value=speedy6_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 14;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy7_Slot_fif()
{
    float value=speedy7_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 105;
    send_arr[6] = 15;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy8_Slot_fif()
{
    float value=speedy8_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 0;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow::lEdt_speedy9_Slot_fif()
{
    float value=speedy9_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 1;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_speedy10_Slot_fif()
{
    float value=speedy10_lineEdt_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 3;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Default_Slot_fif()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 105;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 106;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 110;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_Speed_Update_Slot_fif()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_maxspeedx_Slot_fif()
{
    float value=maxspeedx_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 4;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_maxspeedy_Slot_fif()
{
    float value=maxspeedy_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 5;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_deadx_Slot_fif()
{
    float value=deadx_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_deady_Slot_fif()
{
    float value=deady_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 7;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_out_address_Slot_fif()
{
    float value=out_address_fif->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 110;
    send_arr[6] = 6;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_output_d_type_Slot_fif(int index)
{
    float value = index + 1;
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 106;
    send_arr[6] = 8;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::combox_baud_rate_type_Slot_fif(int index)
{
    float value;
    switch(index)
    {
        case 0:
            value = 2400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 4800;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 9600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 19200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 4:
            value = 38400;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 5:
            value = 57600;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 6:
            value = 115200;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 1;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_data_bit_type_Slot_fif(int index)
{
    float value;
    switch (index)
    {
        case 0:
            value = 5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 6;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 7;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 3:
            value = 8;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 2;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_stop_bit_type_Slot_fif(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1.5;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 4;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::combox_parity_bit_type_Slot_fif(int index)
{
    float value;
    switch (index) {
        case 0:
            value = 0;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            value = 1;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            value = 2;
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 3;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
         default:
            break;
    }
}

void MainWindow::combox_flow_control_type_Slot_fif(int index)
{
    float value = index + 1;
    switch (index) {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[4] = 0x30;
            send_arr[5] = 110;
            send_arr[6] = 5;
            memcpy(send_arr+7,&value,4);
            send_oneframe(7);
            send_mutex.unlock();
            break;
        default:
            break;
    }
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

void MainWindow:: x_ratio_control_Slot()
{
    float value=ky_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::y_ratio_control_Slot()
{
    float value=ky_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 48;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}
void MainWindow:: lEdt_errx_Slot()
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

void MainWindow::lEdt_speedx10_Slot()
{
    float value=speedx10_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 50;
    send_arr[6] = 2;
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

void MainWindow::lEdt_speedy10_Slot()
{
    float value=speedy10_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 50;
    send_arr[6] = 3;
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

void MainWindow::btn_pid_Default_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 2;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 48;
    send_oneframe(2);
    send_mutex.unlock();
}
void MainWindow::btn_pid_Updata_Slot()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_kx_Slot2()
{
    float value=kx_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_ky_Slot2()
{
    float value=ky_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::x_ratio_control_Slot2()
{
    float value=x_ratio_control2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::y_ratio_control_Slot2()
{
    float value=y_ratio_control2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_errx_Slot2()
{
    float value=errx_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_erry_Slot2()
{
    float value=erry_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_time_Slot2()
{
    float value=time_lineEdt2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID1_Slot2()
{
    float value=kp1_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot2()
{
    float value=ki1_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot2()
{
    float value=kd1_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID4_Slot2()
{
    float value=k12->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID5_Slot2()
{
    float value=kp2_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot2()
{
    float value=ki2_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot2()
{
    float value=kd2_pid2->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID8_Slot2()
{
    float value=k22->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 91;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Default_Slot2()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 92;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 91;
    send_oneframe(2);
    send_mutex.unlock();

}

void MainWindow::btn_pid_Updata_Slot2()
{

    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_kx_Slot3()
{
    float value=kx_lineEdt3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_ky_Slot3()
{
    float value=ky_lineEdt3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::x_ratio_control_Slot3()
{
    float value=x_ratio_control3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::y_ratio_control_Slot3()
{
    float value=y_ratio_control3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_errx_Slot3()
{
    float value=errx_lineEdt3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_erry_Slot3()
{
    float value=erry_lineEdt3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_time_Slot3()
{
    float value=time_lineEdt3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 94;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID1_Slot3()
{
    float value=kp1_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot3()
{
    float value=ki1_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot3()
{
    float value=kd1_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID4_Slot3()
{
    float value=k13->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_PID5_Slot3()
{
    float value=kp2_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot3()
{
    float value=ki2_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot3()
{
    float value=kd2_pid3->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID8_Slot3()
{
    float value=k23->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 93;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Default_Slot3()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 93;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 94;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Updata_Slot3()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}
void MainWindow::lEdt_kx_Slot4()
{
    float value=kx_lineEdt4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_ky_Slot4()
{
    float value=ky_lineEdt4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::x_ratio_control_Slot4()
{
    float value=x_ratio_control4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::y_ratio_control_Slot4()
{
    float value=y_ratio_control4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_errx_Slot4()
{
    float value=errx_lineEdt4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_erry_Slot4()
{
    float value=erry_lineEdt4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_time_Slot4()
{
    float value=time_lineEdt4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 96;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID1_Slot4()
{
    float value=kp1_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot4()
{
    float value=ki1_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot4()
{
    float value=kd1_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID4_Slot4()
{
    float value=k14->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();

}

void MainWindow::lEdt_PID5_Slot4()
{
    float value=kp2_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot4()
{
    float value=ki2_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot4()
{
    float value=kd2_pid4->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 95;
    send_arr[6] = 0x07;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID8_Slot4()
{
    float value=k24->text().toFloat();
     send_mutex.lock();
     send_arr[4] = 0x30;
     send_arr[5] = 95;
     send_arr[6] = 0x08;
     memcpy(send_arr+7,&value,4);
     send_oneframe(7);
     send_mutex.unlock();

}

void MainWindow::btn_pid_Default_Slot4()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 95;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 96;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Updata_Slot4()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
    send_mutex.unlock();
}

void MainWindow::lEdt_kx_Slot5()
{
    float value=kx_lineEdt5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x00;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_ky_Slot5()
{
    float value=ky_lineEdt5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::x_ratio_control_Slot5()
{
    float value=x_ratio_control5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::y_ratio_control_Slot5()
{
    float value=x_ratio_control5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_errx_Slot5()
{
    float value=errx_lineEdt5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_erry_Slot5()
{
    float value=erry_lineEdt5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x03;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_time_Slot5()
{
    float value=time_lineEdt5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 98;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID1_Slot5()
{
    float value=kp1_pid5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x01;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot5()
{
    float value=ki1_pid5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x02;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot5()
{
    float value=kd1_pid5->text().toFloat();
     send_mutex.lock();
     send_arr[4] = 0x30;
     send_arr[5] = 97;
     send_arr[6] = 0x03;
     memcpy(send_arr+7,&value,4);
     send_oneframe(7);
     send_mutex.unlock();

}

void MainWindow::lEdt_PID4_Slot5()
{

    float value=k15->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x04;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID5_Slot5()
{
    float value=kp2_pid5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x05;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot5()
{
    float value=ki2_pid5->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x06;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot5()
{
    float value=kd2_pid5->text().toFloat();
     send_mutex.lock();
     send_arr[4] = 0x30;
     send_arr[5] = 97;
     send_arr[6] = 0x07;
     memcpy(send_arr+7,&value,4);
     send_oneframe(7);
     send_mutex.unlock();

}

void MainWindow::lEdt_PID8_Slot5()
{
    float value=k25->text().toFloat();
    send_mutex.lock();
    send_arr[4] = 0x30;
    send_arr[5] = 97;
    send_arr[6] = 0x08;
    memcpy(send_arr+7,&value,4);
    send_oneframe(7);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Default_Slot5()
{
    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 97;
    send_oneframe(2);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4] = 0x09;
    send_arr[5] = 98;
    send_oneframe(2);
    send_mutex.unlock();
}

void MainWindow::btn_pid_Updata_Slot5()
{
    send_mutex.lock();
    send_arr[4] = 0x34;
    send_oneframe(1);
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
        //QString ip = upgrade_ip->text();
        //int port = upgrade_port->text().toInt();
        QString ip = net_ip;
        int port = 8999;
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

void MainWindow::btnselectsw_clicked()
{
    filePath_updatesw = QFileDialog::getOpenFileName(this,"open","../");
    if( false == filePath_updatesw.isEmpty())
    {
        editsw->setText(filePath_updatesw);
    }
}

void MainWindow::btnUpdate()
{
    //QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    QString filePath = editsw->text();
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

        //QString ip = upgrade_ip->text();
        //int port = upgrade_port->text().toInt();
        QString ip = net_ip;
        int port = 8999;
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

void MainWindow::btnFPGA_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    unsigned char usocket_send_buf[1024+256] = {0};
    qint64 len = 0;
    char buf[1024+256] = {0};
    unsigned char checksum = 0;

     if( false == filePath.isEmpty())
     {
        // 获取文件信息
        fpgafileName.clear();
        fpgafilesize =0;
        QFileInfo info(filePath);
        fpgafileName = info.fileName();
        fpgafilesize = info.size();
        fpgasendsize = 0;
        int packet_flag;

        if(fpgafilesize>4294967295)
        {
            upgrade_show->append("文件大小不能超过4294967295字节！");
            return;
        }

        fpgafile.setFileName(filePath);
        bool isok = fpgafile.open(QFile::ReadOnly);
        if(false == isok)
        {
            upgrade_show->append("打开文件失败");
            return;
        }

        usocket_send_buf[0] = 0xEB;
        usocket_send_buf[1] = 0x53;
        usocket_send_buf[4] = 0x37;
        usocket_send_buf[5] = fpgafilesize&0xff;
        usocket_send_buf[6] = (fpgafilesize>>8)&0xff;
        usocket_send_buf[7] = (fpgafilesize>>16)&0xff;
        usocket_send_buf[8] = (fpgafilesize>>24)&0xff;
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
        while(len = fpgafile.read(buf,1024))
        {  //每次发送数据大小
          checksum = 0;
          if(len<0)
          {
              upgrade_show->append("文件读取失败");
              break;
          }
          fpgasendsize += len;
          if(packet_flag == 0)
          {
              usocket_send_buf[9] = 0;
              packet_flag = 1;
          }
          else if(fpgasendsize == fpgafilesize)
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
          trans_percent = fpgasendsize*100/fpgafilesize;
          //upgrade_show->setText(tr("文件发送中...%")+QString("%1").arg(trans_percent&0xFF,2,10));
        }
        if(fpgasendsize == fpgafilesize)
        {
            fpgafile.close();
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

void MainWindow::vedio_tosersor_fix(int i)
{
    float value = i;
    send_mutex.lock();
    send_arr[4]=0x30;
    send_arr[5]=23;
    send_arr[6]=05;
    memcpy(send_arr+7, &value, 4);
    send_oneframe(7);
    send_mutex.unlock();

    if(i==1)
    {
        w_sersor_1->close();
        vedio_btnSensor1SwitchSlot();
    }
    else if(i==2)
    {
        w_sersor_1->close();
        vedio_btnSensor2ContinueSlot();
    }
}

void MainWindow::vedio_toSensor_switch(int i)
{
    float value = 0;
   if(i==1){
       value = 0;
       w_seitchField_1->close();
       showvedioCfg1();
       send_mutex.lock();
       send_arr[4] = 0x30;
       send_arr[5] =23;
       send_arr[6] = 0x05;
       memcpy(send_arr+7, &value, 4);
       send_oneframe(7);
       send_mutex.unlock();

   }else if(i==2){
       value = 2;
       w_seitchField_1->close();;
       vedio_btnSensor2ContinueSlot();
       send_mutex.lock();
       send_arr[4] = 0x30;
       send_arr[5] = 23;
       send_arr[6] = 0x05;
       memcpy(send_arr+7, &value, 4);
       send_oneframe(7);
       send_mutex.unlock();
   }
}
void MainWindow::vedio_tosersor_continue(int i)
{
    float value = 0;
    if(i==1){
        w_ContinueField_1->close();
        value = 0;
        showvedioCfg1();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 0x05;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }else if(i==2){
        value = 1;
        w_ContinueField_1->close();
        vedio_btnSensor1SwitchSlot();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 23;
        send_arr[6] = 0x05;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_tosersor_fix_sec(int i)
{
    float value = 0;
    if(i==1)
    {
        value = 1;
        w_sersor_1_sec->close();
        vedio_btnSensor1SwitchSlot_sec();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==2)
    {
        value = 2;
        w_sersor_1_sec->close();
        vedio_btnSensor2ContinueSlot_sec();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_toSensor_switch_sec(int i)
{
    float value = 0;
    if(i==1){
        value = 0;
        w_seitchField_1_sec->close();
        showvedioCfg2();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();

    }else if(i==2){
        value = 2;
        w_seitchField_1_sec->close();;
        vedio_btnSensor2ContinueSlot_sec();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }

}

void MainWindow::vedio_tosersor_continue_sec(int i)
{
    float value = 0;
    if(i==1){
        value = 0;
        w_ContinueField_1_sec->close();
        showvedioCfg2();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }else if(i==2){
        value = 1;
        w_ContinueField_1_sec->close();
        vedio_btnSensor1SwitchSlot_sec();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 58;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_tosersor_fix_thi(int i)
{
    float value = 0;
    if(i==1)
    {
        value = 1;
        w_sersor_1_thi->close();
        vedio_btnSensor1SwitchSlot_thi();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==2)
    {
        value = 2;
        w_sersor_1_thi->close();
        vedio_btnSensor2ContinueSlot_thi();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_toSensor_switch_thi(int i)
{
    float value = 0;
    if(i==1){
        value = 0;
        w_seitchField_1_thi->close();
        showvedioCfg3();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();

    }else if(i==2){
        value = 2;
        w_seitchField_1_thi->close();
        vedio_btnSensor2ContinueSlot_thi();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_tosersor_continue_thi(int i)
{
    float value = 0;
    if(i==1){
        value = 0;
        w_ContinueField_1_thi->close();
        showvedioCfg3();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_mutex.unlock();
    }else if(i==2){
        value = 1;
        w_ContinueField_1_thi->close();
        vedio_btnSensor1SwitchSlot_thi();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 65;
        send_arr[6] = 5;
        memcpy(send_arr+7, &value, 4);
        send_oneframe(7);
        send_mutex.unlock();
    }
}

void MainWindow::vedio_tosersor_fix_fou(int i)
{
    if(i==0)
    {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==1)
    {
        w_sersor_1_fou->close();
        vedio_btnSensor1SwitchSlot_fou();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 2;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==2)
    {
        w_sersor_1_fou->close();
        vedio_btnSensor2ContinueSlot_fou();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 3;
        send_oneframe(7);
        send_mutex.unlock();
    }

}

void MainWindow::vedio_toSensor_switch_fou(int i)
{
    if(i==1){
        w_seitchField_1_fou->close();
        showvedioCfg3();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 0x23;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();

    }else if(i==2){
        w_seitchField_1_fou->close();;
        vedio_btnSensor2ContinueSlot_fou();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 3;
        send_oneframe(7);
        send_mutex.unlock();
    }



}

void MainWindow::vedio_tosersor_continue_fou(int i)
{

    if(i==1){
        w_ContinueField_1_fou->close();
        showvedioCfg4();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();
    }else if(i==2){
        w_ContinueField_1_fou->close();
        vedio_btnSensor1SwitchSlot_fou();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 72;
        send_arr[6] = 0x05;
        send_arr[7] = 2;
        send_oneframe(7);
        send_mutex.unlock();
    }

}

void MainWindow::vedio_tosersor_fix_fif(int i)
{
    if(i==0)
    {
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==1)
    {
        w_sersor_1_fif->close();
        vedio_btnSensor1SwitchSlot_fif();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 2;
        send_oneframe(7);
        send_mutex.unlock();
    }
    else if(i==2)
    {
        w_sersor_1_fif->close();
        vedio_btnSensor2ContinueSlot_fif();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 3;
        send_oneframe(7);
        send_mutex.unlock();
    }

}

void MainWindow::vedio_toSensor_switch_fif(int i)
{
    if(i==1){
        w_ContinueField_1_fif->close();
        showvedioCfg5();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();
    }else if(i==2){
        w_ContinueField_1_fif->close();
        vedio_btnSensor1SwitchSlot_fif();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 3;
        send_oneframe(7);
        send_mutex.unlock();
    }


}

void MainWindow::vedio_tosersor_continue_fif(int i)
{
    if(i==1){
        w_ContinueField_1_fif->close();
        showvedioCfg5();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 1;
        send_oneframe(7);
        send_mutex.unlock();
    }else if(i==2){
        w_ContinueField_1_fif->close();
        vedio_btnSensor1SwitchSlot_fif();
        send_mutex.lock();
        send_arr[4] = 0x30;
        send_arr[5] = 79;
        send_arr[6] = 0x05;
        send_arr[7] = 2;
        send_oneframe(7);
        send_mutex.unlock();
    }

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

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 57;
     send_oneframe(2);
     send_mutex.unlock();
 }
 void MainWindow:: btn_default_Slot3()
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

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 56;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 58;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot_sec()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 59;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot2_sec()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 60;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 65;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot3_sec()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 61;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 62;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 63;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 64;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 66;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot_thi()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 67;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot2_thi()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 68;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 73;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot3_thi()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 69;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 70;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 71;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 72;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 74;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot_fou()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 75;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot2_fou()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 76;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 81;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot3_fou()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 77;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 78;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 79;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 80;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 82;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot_fif()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 83;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot2_fif()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 84;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 89;
     send_oneframe(2);
     send_mutex.unlock();
 }

 void MainWindow::btn_default_Slot3_fif()
 {
     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 85;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 86;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 87;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 88;
     send_oneframe(2);
     send_mutex.unlock();

     send_mutex.lock();
     send_arr[4] =0x09;
     send_arr[5] = 90;
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
    /*
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
    */



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

void MainWindow::on_comboBox_acqmode_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
            send_mutex.lock();
            send_arr[4] = 0x18;
            send_arr[5] = 0x02;
            send_oneframe(2);
            send_mutex.unlock();
            break;
        case 1:
            send_mutex.lock();
            send_arr[4] = 0x18;
            send_arr[5] = 0x01;
            send_oneframe(2);
            send_mutex.unlock();
            break;
        case 2:
            break;
        default:
            break;
    }
}

void MainWindow::on_radioButton_workmode_clicked(bool checked)
{
    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x42;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow:: on_radioButton_2_workmode_clicked(bool checked)
{

    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x42;
        send_arr[5] = 0x02;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_radioButton_3_workmode_clicked(bool checked)
{
    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x42;
        send_arr[5] = 0x03;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_radioButton_acqmode_clicked(bool checked)
{
    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x43;
        send_arr[5] = 0x00;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_radioButton_2_acqmode_clicked(bool checked)
{
    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x43;
        send_arr[5] = 0x01;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_radioButton_3_acqmode_clicked(bool checked)
{
    if(checked ==true)
    {
        send_mutex.lock();
        send_arr[4] = 0x43;
        send_arr[5] = 0x02;
        send_oneframe(2);
        send_mutex.unlock();
    }
}

void MainWindow::on_call_preset_bit_clicked()
{
    send_mutex.lock();
    send_arr[4] = 0x49;
    send_arr[5] = 0x01;
    send_oneframe(2);
    send_mutex.unlock();
}
