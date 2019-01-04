 #include "comchoose.h"
#include <QSettings>
comChoose::comChoose(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Choose");

    box2=new QComboBox;
    box2->addItem("串口");
    box2->addItem("网络");
    //box3=new QComboBox;
    //box3->addItem("配置模式");
    //box3->addItem("手柄模式");
    QPushButton *comconfig = new QPushButton;
    comconfig->setText("配置");

    QDialogButtonBox* btn = new QDialogButtonBox();
    btn->addButton( "下一步", QDialogButtonBox::YesRole);
    btn->addButton( "退出", QDialogButtonBox::NoRole);

    QFormLayout *pLayout = new QFormLayout;
    pLayout->addRow("通讯接口选择", box2);
    pLayout->addRow("", comconfig);
    //pLayout->addRow("模式选择", box3);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(pLayout);
    v->addWidget(btn);

    this->setLayout(v);

     serial_port=" ";
     serial_baud=0;
     serial_check=0;
     serial_data=0;
     serial_stop=0;
     net_port=0;
     net_ip=" ";

     mutex=0;//默认是串口

    connect(comconfig,SIGNAL(clicked(bool)),this,SLOT(btnconfigSlot()));
    connect(btn,SIGNAL(accepted()),this,SLOT(toOtherSlot()));
    connect(btn,SIGNAL(rejected()),this,SLOT(toCloseSlot()));
}

void comChoose::btnconfigSlot()
{
    if(0 == box2->currentIndex())
    {
        mutex=0;
        w_config_serial.setWindowTitle("串口配置");
        w_config_serial.setWindowModality(Qt::ApplicationModal); //阻塞除当前窗体之外的所有的窗体

        QStringList portNameList;
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
            portNameList.append(info.portName());
        }


        groupBox_trackboard = new QGroupBox();
        groupBox_trackboard->setTitle("串口");
        box_serial= new QComboBox(groupBox_trackboard);
        box_serial->addItems(portNameList);
        /*
        box_baud = new QComboBox(groupBox_trackboard);
        box_baud->addItem("115200");
        box_baud->addItem("1200");
        box_baud->addItem("2400");
        box_baud->addItem("4800");
        box_baud->addItem("9600");
        box_baud->addItem("19200");
        box_baud->addItem("38400");
        box_baud->addItem("57600");
        box_check = new QComboBox(groupBox_trackboard);
        box_check->addItem("None");
        box_check->addItem("Even");
        box_check->addItem("Odd");
        box_data = new QComboBox(groupBox_trackboard);
        box_data->addItem("8");
        box_data->addItem("7");
        box_data->addItem("6");
        box_data->addItem("5");
        box_stop = new QComboBox(groupBox_trackboard);
        box_stop->addItem("1");
        box_stop->addItem("1.5");
        box_stop->addItem("2");
        */
        buard_label = new QLabel(groupBox_trackboard);
        buard_label->setText("115200");
        check_label = new QLabel(groupBox_trackboard);
        check_label->setText("None");
        data_label = new QLabel(groupBox_trackboard);
        data_label->setText("8");
        stop_label = new QLabel(groupBox_trackboard);
        stop_label->setText("1");

        QDialogButtonBox* button = new QDialogButtonBox();
        button->addButton( "OK", QDialogButtonBox::YesRole);
        button->addButton( "Cancel", QDialogButtonBox::NoRole);


        QFormLayout *playout_s1 = new QFormLayout();
        playout_s1->addRow(QStringLiteral("命令端口"), box_serial);
        //playout_s1->addRow(QStringLiteral("波特率"), box_baud);
        //playout_s1->addRow(QStringLiteral("校验"), box_check);
        //playout_s1->addRow(QStringLiteral("数据位"), box_data);
        //playout_s1->addRow(QStringLiteral("停止位"), box_stop);
        playout_s1->addRow(QStringLiteral("波特率"), buard_label);
        playout_s1->addRow(QStringLiteral("校验"), check_label);
        playout_s1->addRow(QStringLiteral("数据位"), data_label);
        playout_s1->addRow(QStringLiteral("停止位"), stop_label);
        groupBox_trackboard->setLayout(playout_s1);

        QHBoxLayout *mainlayout3 = new QHBoxLayout;
        mainlayout3->addWidget(groupBox_trackboard);

        QVBoxLayout *mainlayout4 = new QVBoxLayout;
        mainlayout4->addLayout(mainlayout3);
        mainlayout4->addWidget(button);

        w_config_serial.setLayout(mainlayout4);

        connect(button,SIGNAL(accepted()),this,SLOT(serialSlot()));
        connect(button,SIGNAL(rejected()),this,SLOT(toCloseSlot()));
        w_config_serial.show();

    }
    else if(1 == box2->currentIndex())
    {
        mutex=1;
        w_config_net.setWindowTitle(tr("网络配置"));

        w_config_net.setWindowModality(Qt::ApplicationModal);
        //lineEdit_port = new QLineEdit();
        port_label = new QLabel();
        port_label->setText("10000");
        lineEdit_ip = new QLineEdit();
        QSettings *configIniRead = new QSettings("socket.ini", QSettings::IniFormat);
        QString ipResult = configIniRead->value("/ip").toString();
        QString portResult = configIniRead->value("/port").toString();
        lineEdit_ip->setText(ipResult);
        //lineEdit_port->setText(portResult);
        delete configIniRead;
        lineEdit_ip->setInputMask("000.000.000.000");


        QDialogButtonBox* button_socket = new QDialogButtonBox();
        button_socket->addButton( "OK", QDialogButtonBox::YesRole);
        button_socket->addButton( "Cancel", QDialogButtonBox::NoRole);

        QFormLayout *pLayout_socket = new QFormLayout();
        pLayout_socket->addRow(QStringLiteral("IP："), lineEdit_ip);
        //pLayout_socket->addRow(QStringLiteral("端口："), lineEdit_port);
        pLayout_socket->addRow(QStringLiteral("端口："), port_label);

        QVBoxLayout *socket_layout2 = new QVBoxLayout;
        socket_layout2->addLayout(pLayout_socket);
        socket_layout2->addWidget(button_socket);
        w_config_net.setLayout(socket_layout2);

         connect(button_socket,SIGNAL(accepted()),this,SLOT(netSlot()));
        connect(button_socket,SIGNAL(rejected()),this,SLOT(toCloseSlot()));
        w_config_net.show();
    }
}

void comChoose::serialSlot()
{
    mutex=0;
    serial_port=box_serial->currentText();
    /*
    serial_baud=box_baud->currentText().toInt();
    serial_check=box_check->currentIndex();
    serial_data=box_data->currentText().toInt();
    serial_stop=box_stop->currentIndex();
    */
    serial_baud = 115200;
    serial_check = 0;
    serial_data = 8;
    serial_stop = 0;

    w_config_serial.close();
}
void comChoose::netSlot()
{
    mutex=1;
QSettings *configIniWrite = new QSettings("socket.ini", QSettings::IniFormat);
     configIniWrite->setValue("ip", lineEdit_ip->text());
     //configIniWrite->setValue("port", lineEdit_port->text());
     configIniWrite->setValue("port", "10000");
     delete configIniWrite;
    //net_port=lineEdit_port->text().toInt();
    net_port=10000;
    net_ip=lineEdit_ip->text();
    w_config_net.close();
}

void comChoose::toCloseSlot()
{
    w_config_net.close();
    w_config_serial.close();
}
void comChoose::toOtherSlot()
{
    //if(box3->currentIndex()==0){//到主界面
        if(mutex==0){//串口
            emit serialToMain(serial_port,serial_baud,serial_check,serial_data,serial_stop);
        }else{//网络
            emit netToMain(net_port,net_ip);
        }
        /*
    }else{//到手柄界面
        if(mutex==0){//串口
            emit serialToJos(serial_port,serial_baud,serial_check,serial_data,serial_stop);
        }else{//网络
            emit netToJos(net_port,net_ip);
        }
    }
    */
    this->close();
}
