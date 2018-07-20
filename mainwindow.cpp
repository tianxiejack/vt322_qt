#include "mainwindow.h"
#include "ui_mainwindow.h"

QByteArray copy_bytearray;
volatile unsigned char rcv_buf[5000];
volatile unsigned int BufWrite = 0;
volatile unsigned int BufRead = 0;
volatile unsigned char BufRcvStatus=BUFFER_EMPTY;

QByteArray socket_copy_bytearray;
volatile qint32 socket_recvNum =0;
volatile unsigned char socket_rcv_buf[5000];
volatile unsigned int socket_BufWrite = 0;
volatile unsigned int socket_BufRead = 0;
volatile unsigned char socket_BufRcvStatus=BUFFER_EMPTY;

extern volatile bool thread_run;
extern volatile bool thread_run_socket;

QMutex send_mutex;
unsigned char send_arr[64];
unsigned short sectrk_x = 0;
unsigned short sectrk_y = 0;
unsigned char output_array[64];
unsigned char output_array_6[64];
unsigned char output_array_7[64];
unsigned char output_array_8[64];
extern int connect_flag;
extern int current_povstat;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_menu();
    //init_btn();
    init_sysCfg();
    this->setWindowTitle("控制界面");
    old_x=a_center=a=POINTX+CENTER/2;
    old_y=b_center=b=POINTY+CENTER/2;

    this->resize(580,450);

    btnStack=new QStackedLayout;
    btnStack->addWidget(ui->btnCapture);
    btnStack->addWidget(ui->btnTrack);




    serialPort_command = new QSerialPort(this);
    connect(serialPort_command, &QSerialPort::readyRead, this, &MainWindow::RcvData_SerialPort);//当有数据来时，触发接收槽函数；
    connect(this,&MainWindow::copy_Done, this ,&MainWindow::parse_bytearray);


    thread_01 = new recSerial(this);//定义一个线程对象（接收）
    connect(thread_01,&recSerial::send2main_signal, this, &MainWindow::output_to_label);
    connect(this,&MainWindow::destroyed, this,&MainWindow::stop_thread_now);
    thread_run = true;
    thread_01->start();

    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    connect(this,&MainWindow::socket_copy_Done, this ,&MainWindow::socket_parse_bytearray);
    thread_socket = new RcvSocketdata(this);
    connect(thread_socket,&RcvSocketdata::socket2main_signal, this, &MainWindow::output_to_label);
    thread_run_socket = true;
    thread_socket->start();

    usocket = new QTcpSocket(this);
    connect(usocket, &QTcpSocket::readyRead,
            [=]()
                {

                   QByteArray buf = usocket->readAll();
                   upgrade_show->append(buf);
                }
        );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RcvData_SerialPort()
{
    RcvData = serialPort_command->readAll();
    copy_bytearray = RcvData;
    emit copy_Done();
    RcvData.clear();
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

QSerialPort::Parity mySetSerialParity(QSerialPort *com,int n)
{
    QSerialPort::Parity num =(QSerialPort::Parity)n;


    switch(num)
    {   // 此处的 0,1,2代表的是下拉框的索引值；
        case 0:
        com->setParity(QSerialPort::EvenParity);
        break;
        case 1:
        com->setParity(QSerialPort::NoParity);
        break;
        case 2:
        com->setParity(QSerialPort::OddParity);
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


    socket->connectToHost(ip,port);
//    if(socket->isOpen()){
//        qDebug()<<"连接成功！";
//     this->show();
//   }
//    else{
//        qDebug()<<"连接失败！";

//   }

    //等待连接成功
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
//    QString port=s.port;
//    quint32 baud=s.baud;
//    int check=s.check;
//    int data=s.data;
//    int stop=s.stop;
//    serial_command askData;
//        askData = s.value<serial_command_main>();
//    qDebug()<<askData.port;

//    qDebug()<<"port"<< port<<endl;
//    qDebug()<<"baud"<< baud<<endl;
//    qDebug()<<"check"<<check<<endl;
//    qDebug()<<"data"<< data<<endl;
//    qDebug()<<"stop"<< stop<<endl;
    serialPort_command->close();
    serialPort_command->setPortName(port);
    bool openflag = serialPort_command->open(QIODevice::ReadWrite);
    if(true == openflag ) {
        connect_flag = 1;
        mySetSerialBaud(serialPort_command,baud);
        mySetSerialDataBits(serialPort_command,data);
        mySetSerialParity(serialPort_command,check);
        smySetSerialStopBit(serialPort_command,stop);
    }else{// 串口打开失败时，弹出提示窗口
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
    }
         this->show();
}
void MainWindow::btnToNet()
{
    int net_port=lineEdit_port->text().toInt();
    QString net_ip=lineEdit_ip->text();
    if(socket->isOpen())
       socket->close();
    if(serialPort_command->isOpen())
       serialPort_command->close();
    socket->connectToHost(net_ip,net_port);
    if(!socket->waitForConnected(300))
    {
        qDebug() << "Connection failed!";
        QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
        return;
    }
    w_config_net.close();

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
         w_config_serial.close();
    }else{// 串口打开失败时，弹出提示窗口
        QMessageBox::warning(NULL, tr("警告"), tr("串口被占用"), QMessageBox::Close);
    }
}

void MainWindow::btnToClose()
{
    w_config_net.close();
    w_config_serial.close();
}


void MainWindow::on_btnTrack_clicked()
{
    btnStack->setCurrentIndex(0);
    send_mutex.lock();
    send_arr[3] = 0x04;
    send_arr[4] = 0x00;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnCapture_clicked()
{
    btnStack->setCurrentIndex(1);
    send_mutex.lock();
    send_arr[3] = 0x04;
    send_arr[4] = 0x01;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnSersorSwitch_clicked()
{
    if(sersor_count==6){
        sersor_count=0;
    }
    switch (sersor_count) {
    case 0:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x00;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    case 1:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x01;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    case 2:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x02;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    case 3:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x03;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    case 4:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x04;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    case 5:
        send_mutex.lock();
        send_arr[3] =0x02;
        send_arr[4] =0x05;
        send_oneframe(6);
        send_mutex.unlock();
        break;
    default:
        sersor_count=0;
        break;
    }
    sersor_count++;

}

void MainWindow::on_btnViewPlus_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x12;
    send_arr[4] = 0x02;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnViewMinus_clicked()
{
    send_mutex.lock();
    send_arr[3] =0x12;
    send_arr[4] = 0x01;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnForcePlus_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x14;
    send_arr[4] = 0x01;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnForceMinus_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x14;
    send_arr[4] = 0x02;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnAperturePlus_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x13;
    send_arr[4] = 0x02;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::on_btnApertureMinus_clicked()
{
    send_mutex.lock();
    send_arr[3] = 0x13;
    send_arr[4] = 0x01;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_sysCfg_Slot()
{

}

void MainWindow::CBox_sysCfg_Slot(int i)
{
    switch (i){
        case 1:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 00;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 2:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 01;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 3:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 02;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 4:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 03;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 5:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 04;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        case 6:
            send_mutex.lock();
            send_arr[3] = 02;
            send_arr[4] = 05;
            send_oneframe(6);
            send_mutex.unlock();
            break;
        default:
            break;
    }
}

void MainWindow::lEdt_fix_Radio_Slot()
{   float value=lineEdit_fieldRadio->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x07;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}


void MainWindow::lEdt_Resolution_Slot()
{
    float value=lineEdit_fieldResolution->text().toInt();
    qDebug()<<value;
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x07;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_Resolution2_Slot()
{
    float value=lineEdit_fieldResolution2->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x07;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::btn_fix_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_fix_view_Slot()
{
    float value=lEdt->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x07;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::sp_fix_x_Slot(int i)
{
    qDebug()<<"sp:"<<sp->text().toInt();
//    send_mutex.lock();
//    send_arr[3] = 0x30;
//    send_arr[4] = 0x07;
//    send_arr[5] = 0x05;
//    memcpy(send_arr+6,&i,4);
//    send_oneframe(11);
//    send_mutex.unlock();
}

void MainWindow::sp_fix_y_Slot(int i)
{
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x07;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&i,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::sp_test_Slot()
{

}

void MainWindow::lEdt_switch_Radio_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_switch_Resolution_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_switch1_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_switch2_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_switch3_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_switch4_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_switch5_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_continue_Radio_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_continue_Resolution_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue1_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue2_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue3_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue4_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue5_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue6_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue7_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue8_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue9_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue10_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue11_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue12_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_continue13_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_utc1_default_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::btn_utc1_update_Slot()
{
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l0_Slot()
{
    float value=utc1_l0->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x00;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l1_Slot()
{
    float value=utc1_l1->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc1_l2_Slot()
{
    float value=utc1_l2->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l3_Slot()
{
    float value=utc1_l3->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l4_Slot()
{

    float value=utc1_l4->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l5_Slot()
{
    float value=utc1_l5->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x05;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l6_Slot()
{
    float value=utc1_l6->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l7_Slot()
{
    float value=utc1_l7->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x07;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l8_Slot()
{
    float value=utc1_l8->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x08;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l9_Slot()
{
    float value=utc1_l9->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x09;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc1_l10_Slot()
{
    float value=utc1_l10->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0a;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l11_Slot()
{
    float value=utc1_l11->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0b;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l12_Slot()
{
    float value=utc1_l12->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0c;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l13_Slot()
{
    float value=utc1_l13->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0d;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l14_Slot()
{
    float value=utc1_l14->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0e;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc1_l15_Slot()
{
    float value=utc1_l15->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x04;
    send_arr[5] = 0x0f;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::btn_utc2_default_Slot()
{

}

void MainWindow::btn_utc2_update_Slot()
{

}

void MainWindow::lEdt_utc2_l0_Slot()
{
    float value=utc2_l0->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x00;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l1_Slot()
{
    float value=utc2_l1->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l2_Slot()
{
    float value=utc2_l2->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l3_Slot()
{
    float value=utc2_l3->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l4_Slot()
{
    float value=utc2_l4->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l5_Slot()
{
    float value=utc2_l5->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x05;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l6_Slot()
{
    float value=utc2_l6->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc2_l7_Slot()
{
    float value=utc2_l7->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x07;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l8_Slot()
{
    float value=utc2_l8->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x08;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc2_l9_Slot()
{
    float value=utc2_l9->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x09;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l10_Slot()
{
    float value=utc2_l10->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0a;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l11_Slot()
{
    float value=utc2_l11->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0b;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l12_Slot()
{
    float value=utc2_l12->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0c;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l13_Slot()
{
    float value=utc2_l13->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0d;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l14_Slot()
{
    float value=utc2_l14->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0e;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc2_l15_Slot()
{
    float value=utc2_l15->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x05;
    send_arr[5] = 0x0f;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::btn_utc3_default_Slot()
{

}

void MainWindow::btn_utc3_update_Slot()
{

}

void MainWindow::lEdt_utc3_l0_Slot()
{
    float value=utc3_l0->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x00;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l1_Slot()
{
    float value=utc3_l1->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l2_Slot()
{
    float value=utc3_l2->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l3_Slot()
{
    float value=utc3_l3->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l4_Slot()
{
    float value=utc3_l4->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l5_Slot()
{
    float value=utc3_l5->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x05;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc3_l6_Slot()
{
    float value=utc3_l6->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l7_Slot()
{
    float value=utc3_l7->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x07;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();

}

void MainWindow::lEdt_utc3_l8_Slot()
{
    float value=utc3_l8->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x08;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l9_Slot()
{
    float value=utc3_l9->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x09;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l10_Slot()
{
    float value=utc3_l10->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0a;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l11_Slot()
{
    float value=utc3_l11->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0b;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l12_Slot()
{
    float value=utc3_l12->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0c;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l13_Slot()
{
    float value=utc3_l13->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0d;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l14_Slot()
{
    float value=utc3_l14->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0e;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_utc3_l15_Slot()
{
    float value=utc3_l15->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x06;
    send_arr[5] = 0x0f;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::btn_osd_default_Slot()
{

}

void MainWindow::btn_osd_update_Slot()
{
            QString msg=osd1_lineEdit_context->text();
            int length=msg.size()*2+12;
            send_mutex.lock();
            downFrame.my_send[0] = 0xEB;
            downFrame.my_send[1] = 0x53;
            downFrame.my_send[2] = length;
            downFrame.my_send[3] = 0x20;
//            send_arr[5] = sectrk_x&0xff;
//            send_arr[6] = (sectrk_x>>8)&0xff;
//            send_arr[7] = sectrk_y&0xff;
//            send_arr[8] = (sectrk_y>>8)&0xff;
            downFrame.my_send[4] =osd1_pos_x->text().toInt()&0xff;
            downFrame.my_send[5]= (osd1_pos_x->text().toInt()>>8)&0xff;
            downFrame.my_send[6] =osd1_pos_y->text().toInt()&0xff;
            downFrame.my_send[7] = (osd1_pos_y->text().toInt()>>8)&0xff;
            downFrame.my_send[8] =CBox_color->currentIndex()+1;
            downFrame.my_send[9]=osd1_lineEdit_transparency->text().toInt();
            downFrame.my_send[10]=0x01;
            downFrame.my_send[11]=0x01;

            unsigned char sum=0;
            for(int n = 3; n<11; n++) {
                sum ^= downFrame.my_send[n];
             }
            downFrame.my_send[11] = sum;

            QString str1;
            for(int m = 0; m< 10; m++){
                str1 += QString("%1").arg(downFrame.my_send[m]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
            }
            QString str2=str1 += QString("%1").arg(downFrame.my_send[11]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
            bool checkf = true;
            sndData_02 = string2hex(str1,checkf);
            QByteArray data;
            data.append(sndData_02);
            data.append(msg.toUtf8());
            data.append(string2hex(str2,checkf));
            if(checkf == true){
                if(1 == connect_flag)
                {
                    serialPort_command->write(data);
                }
                else if(2 == connect_flag)
                {
                    socket->write(data);//通过网口发送数据
                    socket->flush();
                }
            }
           // ui->label->setText(str1);
            send_mutex.unlock();
}

void MainWindow::CBox_osd_choose_Slot(int i)
{

}

void MainWindow::checkBox_Slot(int i)
{
    if(i == Qt::Checked)
    {
        qDebug()<<"Checked";
//        send_mutex.lock();
//        send_arr[3] = 0x01;
//        send_arr[4] = 0x01;
//        send_oneframe(6);
//        send_mutex.unlock();
    }
    else if(i == Qt::Unchecked)
    {
          qDebug()<<"UnChecked";
//        send_mutex.lock();
//        send_arr[3] = 0x01;
//        send_arr[4] = 0x02;
       send_oneframe(6);
//        send_mutex.unlock();
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
            send_mutex.lock();
            send_arr[3] = 0x20;
            send_arr[4] = 0x02;
            send_oneframe(6);
            send_mutex.unlock();
}

void MainWindow::CBox_osd_font_Slot(int i)
{
    send_mutex.lock();
    send_arr[3] = 0x21;
    send_arr[4] =CBox_font->currentIndex()+1;
    send_arr[5] =CBox_font_size->currentIndex()+1;
    send_oneframe(7);
    send_mutex.unlock();
    QMessageBox::information(this,"提示","重启板卡生效",QMessageBox::Ok,QMessageBox::Cancel);
    qDebug()<<"ok";
}

void MainWindow::CBox_osd_font_size_Slot(int i)
{
    send_mutex.lock();
    send_arr[3] = 0x21;
    send_arr[4] =CBox_font->currentIndex()+1;
    send_arr[5] =CBox_font_size->currentIndex()+1;
    send_oneframe(7);
    send_mutex.unlock();
    QMessageBox::information(this,"提示","重启板卡生效",QMessageBox::Ok,QMessageBox::Cancel);
    qDebug()<<"ok";
}

void MainWindow::CBox_osd_color_Slot(int i)
{

}



void MainWindow::lEdt_transparency_Slot()
{

}

void MainWindow::resetAction()
{
    QMessageBox::information(this,"提示","是否恢复出厂设置",QMessageBox::Ok,QMessageBox::Cancel);
    send_mutex.lock();
    send_arr[3] = 1;
    send_arr[4] = 1;
    send_oneframe(6);
    send_mutex.unlock();
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

    send_arr[3] = 0x01;
    send_arr[4] = 0x01;
    send_oneframe(6);
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

}

void MainWindow::btn_Jos_Update_Slot()
{

}

void MainWindow::lEdt_Jos1_Slot()
{
    float value=josDead_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x01;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos2_Slot()
{
    float value=josPoint_lineEdt->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x01;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos3_Slot()
{
    float value=josInputG_x->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x01;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos4_Slot()
{
    float value=josInputG_y->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x01;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_Jos5_Slot()
{

}

void MainWindow::lEdt_Jos6_Slot()
{

}

void MainWindow::lEdt_PID1_Slot()
{

    float value=kp1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID2_Slot()
{
    float value=ki1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID3_Slot()
{
    float value=kd1_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID4_Slot()
{
    float value=k1->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID5_Slot()
{
    float value=kp2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x05;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID6_Slot()
{
    float value=ki2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID7_Slot()
{
    float value=kd2_pid->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x07;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_PID8_Slot()
{
    float value=k2->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x02;
    send_arr[5] = 0x08;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat1_Slot()
{
    float value=bleedx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x01;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat2_Slot()
{
    float value=bleedy_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x02;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat3_Slot()
{
    float value=mx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x03;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat4_Slot()
{
    float value=my_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x04;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat5_Slot()
{
    float value=deadx_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x05;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat6_Slot()
{
    float value=deady_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x06;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}

void MainWindow::lEdt_plat7_Slot()
{
    float value=a_plat->text().toFloat();
    send_mutex.lock();
    send_arr[3] = 0x30;
    send_arr[4] = 0x03;
    send_arr[5] = 0x07;
    memcpy(send_arr+6,&value,4);
    send_oneframe(11);
    send_mutex.unlock();
}



void MainWindow::btnDownSlot()
{
     QString path=QFileDialog::getExistingDirectory(NULL, tr("选择文件夹"),"E:\\",QFileDialog::ShowDirsOnly);
     QFile file(path);

}

void MainWindow::btnSaveSlot()
{
    QString path= QFileDialog::getSaveFileName(this, tr("Save File"),"",tr("Text files (*.txt)"));
//      QFile file(path);
//      //file.setFileName();
//      if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
//          qDebug()<<"open the file fail!!!!";
//          return;
//      }
//      QByteArray da="hello kitty!";
//      file.write(da);
//      file.close();
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
        qDebug()<<"filepath="<<filePath;
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
            int port = upgrade_port->text().toInt();
            QString ip = upgrade_ip->text();
            usocket->connectToHost(ip,port);
            if(!usocket->waitForConnected(300))
            {
                upgrade_show->append("连接服务器失败");
                return;
            }
            do
            {  //每次发送数据大小
              len = 0;
              len = file.read(buf,1024);
              usocket->write(buf,len);
              sendsize += len;
            }while(len >0);
            if(sendsize == filesize)
            {
                file.close();
                upgrade_show->append("文件发送完毕");
            }
            else
            {
                upgrade_show->append("文件发送失败");
            }
            usocket->disconnectFromHost();
            usocket->close();
        }
    }
    else
        upgrade_show->append("选择文件无效");
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
}
void MainWindow::output_to_label(int i)//解析下位机的反馈信息,从串口读到正确的一帧数据的时候执行此函数。
{
//    int flag = 0;
//    float value1 = 0;
//    float value2 = 0;
//    short trkerrx = 0;
//    short trkerry = 0;
    switch(i)
    {
        case 0x35:
            upgrade_show->append("升级成功");
            break;
        default:
            break;
    }
}
void MainWindow::socket_Read_Data()
{
    socketRcvData = socket->readAll();//读网口
    socket_copy_bytearray = socketRcvData;
    emit socket_copy_Done();
    socketRcvData.clear();
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
