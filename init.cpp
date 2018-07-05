#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::init_menu()
{
    menu[0]=new QMenu("配置");
    QAction* act_sysCfg=new QAction("系统配置");
    menu[0]->addAction(act_sysCfg);
    QAction* act_platCfg=new QAction("平台配置");
    menu[0]->addAction(act_platCfg);


    QAction* act_cmrCfg=new QAction("相机配置");
    menu[0]->addAction(act_cmrCfg);


//    QAction* act_algCfg=new QAction("算法配置");
//    menu[0]->addAction(act_algCfg);
    QMenu *utc=new QMenu("算法配置");
    QAction* act_algCfg1=new QAction("UTC1");
    utc->addAction(act_algCfg1);
    QAction* act_algCfg2=new QAction("UTC2");
    utc->addAction(act_algCfg2);
    QAction* act_algCfg3=new QAction("UTC3");
    utc->addAction(act_algCfg3);
    menu[0]->addMenu(utc);


    //QAction* act_othCfg=new QAction("OSD配置");
    //menu[0]->addAction(act_othCfg);
    QMenu *osd=new QMenu("OSD配置");
    QAction* act_othCfg1=new QAction("OSD1");
    osd->addAction(act_othCfg1);
    QAction* act_othCfg2=new QAction("OSD2");
    osd->addAction(act_othCfg2);
    QAction* act_othCfg3=new QAction("OSD3");
    osd->addAction(act_othCfg3);
    menu[0]->addMenu(osd);

    QAction* act_rstCfg=new QAction("全局复位");
    menu[0]->addAction(act_rstCfg);

    ui->menuBar->addMenu(menu[0]);

    connect(act_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showSysCfg()));
    connect(act_platCfg,SIGNAL(triggered(bool)),this,SLOT(showPlat()));
    connect(act_cmrCfg,SIGNAL(triggered(bool)),this,SLOT(showCamera()));
    connect(act_algCfg1,SIGNAL(triggered(bool)),this,SLOT(showAlg()));
    connect(act_othCfg1,SIGNAL(triggered(bool)),this,SLOT(showOther()));
    connect(act_rstCfg,SIGNAL(triggered(bool)),this,SLOT(resetAction()));

}

void MainWindow::init_sysCfg()
{
    w_config.setWindowTitle(tr("系统配置"));
    QLineEdit *lineEdit=new QLineEdit;
    QComboBox *box1=new QComboBox;
    box1->addItem("1");
    box1->addItem("2");
    box1->addItem("3");
    box1->addItem("4");
    box1->addItem("5");
    box1->addItem("6");
    QComboBox *box2=new QComboBox;
    box2->addItem("串口");
    box2->addItem("网络");
    s=new QStackedLayout;
    QPushButton *btnSerial=new QPushButton;
    QPushButton *btnNet=new QPushButton;
    btnSerial->setText("串口配置");
    btnNet->setText("网络配置");
    s->addWidget(btnSerial);
    s->addWidget(btnNet);

    QPushButton *btnLoad=new QPushButton;
    btnLoad->setText("加载");
    QPushButton *btnSave=new QPushButton;
    btnSave->setText("保存");
    QPushButton *btnUpdate=new QPushButton;
    btnUpdate->setText("升级");

    QFormLayout *pLayout = new QFormLayout;

    pLayout->addRow(QStringLiteral("相机通道总数"), lineEdit);
    pLayout->addRow("相机通道选择", box1);
    pLayout->addRow("串口/网口选择", box2);
    pLayout->addRow("串口/网络配置", s);
    pLayout->addRow("加载配置", btnLoad);
    pLayout->addRow("保存配置", btnSave);
    pLayout->addRow("软件升级", btnUpdate);


    connect(box2,SIGNAL(currentIndexChanged(int)),this,SLOT(toNetSlot(int)));
    connect(btnSerial,SIGNAL(clicked(bool)),this,SLOT(btnSerialSlot()));
    connect(btnNet,SIGNAL(clicked(bool)),this,SLOT(btnNetSlot()));
    connect(btnLoad,SIGNAL(clicked(bool)),this,SLOT(btnLoadSlot()));
    connect(btnSave,SIGNAL(clicked(bool)),this,SLOT(btnSaveSlot()));
    connect(btnUpdate,SIGNAL(clicked(bool)),this,SLOT(btnUpdate()));


    w_config.setLayout(pLayout);


}


void MainWindow::paintEvent(QPaintEvent *event)
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x();
    int y=event->pos().y();
    mousePress = 1;
   if((abs(event->pos().x()-a)<=10)&&((event->pos().y()-b)<=10)){
       m_dragging = 1;
      qDebug()<<"x"<<x<<endl<<"y"<<y<<endl;
   }
   else
       m_dragging = 0;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(mousePress==1){
        mousePress = 0;
        a=POINTX+CENTER/2;
        b=POINTY+CENTER/2;
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePress&&m_dragging)
    {
        int x=event->pos().x();
        int y=event->pos().y();
        if(x>POINTX && x<(POINTX+CENTER) && y>POINTY && y<(POINTY+CENTER) && ((x-POINTX-CENTER/2)*(x-POINTX-CENTER/2)+(y-POINTY-CENTER/2)*(y-POINTY-CENTER/2))<CENTER*CENTER/4)
        {
            sectrk_x = (event->pos().x()-POINTX)*RATIO+CENTER/2;
            sectrk_y = (event->pos().y()-POINTY)*RATIO+CENTER/2;
             //ui->label_xy->setText(tr("(")+QString::number(sectrk_x)+","+QString::number(sectrk_y)+")");
            a=event->pos().x();
            b=event->pos().y();
            if(0)
            {
                send_mutex.lock();
                send_arr[3] = 0x0b;
                send_arr[4] = 0x01;
                send_arr[5] = sectrk_x&0xff;
                send_arr[6] = (sectrk_x>>8)&0xff;
                send_arr[7] = sectrk_y&0xff;
                send_arr[8] = (sectrk_y>>8)&0xff;
                //send_oneframe(10);
                send_mutex.unlock();
            }
            update();
            //repaint();
        }
    }
}

void MainWindow::showJos()
{
    j.show();
}

void MainWindow::showSysCfg()
{
    w_config.show();
    //子界面嵌套。
//    QScrollArea *scroll = new QScrollArea(this);
//    scroll->setBackgroundRole(QPalette::Dark);
//    this->setCentralWidget(scroll);//将滚动条添加到“mainWindow”中间区域
//    //
//    w = new QWidget(scroll);
//    scroll->setWidget(w);//在滚动条上添加widget
//    w->setGeometry(0,0,1460,500);

//    QPushButton *addBtn = new QPushButton("+",w);
    //    addBtn->setText("nm");
}

void MainWindow::showPlat()
{
    w_plat.setWindowTitle("平台配置");

    gbox_Jos=new QGroupBox();
    gbox_Jos->setTitle("手柄");

    josDead_lineEdt=new QLineEdit;
    josPoint_lineEdt=new QLineEdit;
    josInputG_x=new QLineEdit;
    josInputG_y=new QLineEdit;
    josOutputG_x=new QLineEdit;
    josOutputG_y=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(jos_s[0],josDead_lineEdt);
    f1->addRow(jos_s[1],josPoint_lineEdt);
    f1->addRow(jos_s[2],josInputG_x);
    f1->addRow(jos_s[3],josInputG_y);
    f1->addRow(jos_s[4],josOutputG_x);
    f1->addRow(jos_s[5],josOutputG_y);
    gbox_Jos->setLayout(f1);


    gbox_PID=new QGroupBox();
    gbox_PID->setTitle("PID");

    kp1_pid=new QLineEdit;
    ki1_pid=new QLineEdit;
    kd1_pid=new QLineEdit;
    k1=new QLineEdit;
    kp2_pid=new QLineEdit;
    ki2_pid=new QLineEdit;
    kd2_pid=new QLineEdit;
    k2=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s[0],kp1_pid);
    f2->addRow(pid_s[1],ki1_pid);
    f2->addRow(pid_s[2],kd1_pid);
    f2->addRow(pid_s[3],k1);
    f2->addRow(pid_s[4],kp2_pid);
    f2->addRow(pid_s[5],ki2_pid);
    f2->addRow(pid_s[6],kd2_pid);
    f2->addRow(pid_s[7],k2);
    gbox_PID->setLayout(f2);


    gbox_plat=new QGroupBox();
    gbox_plat->setTitle("平台");

    bleedx_plat=new QLineEdit;
    bleedy_plat=new QLineEdit;
    mx_plat=new QLineEdit;
    my_plat=new QLineEdit;
    deadx_plat=new QLineEdit;
    deady_plat=new QLineEdit;
    a_plat=new QLineEdit;

    QFormLayout *f3=new QFormLayout();
    f3->addRow(plat_s[0],bleedx_plat);
    f3->addRow(plat_s[1],bleedy_plat);
    f3->addRow(plat_s[2],mx_plat);
    f3->addRow(plat_s[3],my_plat);
    f3->addRow(plat_s[4],deadx_plat);
    f3->addRow(plat_s[5],deady_plat);
    f3->addRow(plat_s[6],a_plat);
    gbox_plat->setLayout(f3);

    QVBoxLayout *v=new QVBoxLayout;
    v->addWidget(gbox_Jos);
    v->addWidget(gbox_PID);
    v->addWidget(gbox_plat);

    w_plat.setLayout(v);

    w_plat.show();
}

void MainWindow::showCamera()
{
    w_sersor1.setWindowTitle("通道1");



//    QPushButton *btn_sensor_switch=new QPushButton;
//    btn_sensor_switch->setText("可切换视场");
//    QPushButton *btn_sersor_continue=new QPushButton;
//    btn_sersor_continue->setText("连续视场");
//    lineEdit_fieldRadio=new QLineEdit;
//    lineEdit_fieldResolution=new QLineEdit;

//    QFormLayout *f1=new QFormLayout;
//    f1->addRow(sensor_s1[0],btn_sensor_switch);
//    f1->addRow(sensor_s1[1],btn_sersor_continue);
//    f1->addRow(sensor_s1[2],lineEdit_fieldRadio);
//    f1->addRow(sensor_s1[3],lineEdit_fieldResolution);


//    lineEdit_FOV_x=new QLineEdit;
//    lineEdit_FOV_y=new QLineEdit;
//    QLabel *label=new QLabel;
//    label->setText("x方向");
//    QGroupBox *g=new QGroupBox;
//    g->setTitle("固定视场");

//    QFormLayout *f2=new QFormLayout;
//    f2->addRow(sensor_s1[4],label);
//    f2->addRow(sensor_s1[5],lineEdit_FOV_x);
//    f2->addRow(sensor_s1[6],lineEdit_FOV_y);
//    g->setLayout(f2);

//    QVBoxLayout *v=new QVBoxLayout;
//    v->addLayout(f1);
//    v->addWidget(g);




    QComboBox *change=new QComboBox;
    change->addItem(" ");
    change->addItem("固定视场");
    change->addItem("可切换视场");
    change->addItem("连续视场");
    lineEdit_fieldRadio=new QLineEdit;
    lineEdit_fieldResolution=new QLineEdit;

    sta=new QStackedLayout;
    QPushButton *blank=new QPushButton;
    QPushButton *btn_sensor_fix=new QPushButton;
    btn_sensor_fix->setText("固定视场");
    QPushButton *btn_sensor_switch=new QPushButton;
    btn_sensor_switch->setText("可切换视场");
    QPushButton *btn_sersor_continue=new QPushButton;
    btn_sersor_continue->setText("连续视场");
    sta->addWidget(blank);
    sta->addWidget(btn_sensor_fix);
    sta->addWidget(btn_sensor_switch);
    sta->addWidget(btn_sersor_continue);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1[0],change);
    f1->addRow(sensor_s1[1],sta);
    f1->addRow(sensor_s1[2],lineEdit_fieldRadio);
    f1->addRow(sensor_s1[3],lineEdit_fieldResolution);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(f1);
    connect(change,SIGNAL(currentIndexChanged(int)),this,SLOT(toSensor_switch(int)));



    connect(btn_sensor_switch,SIGNAL(clicked(bool)),this,SLOT(btnSensor1SwitchSlot()));
    connect(btn_sersor_continue,SIGNAL(clicked(bool)),this,SLOT(btnSensor2ContinueSlot()));
    w_sersor1.setLayout(v);
    w_sersor1.show();

}

void MainWindow::showAlg()
{
    utc1.setWindowTitle("UTC1参数配置");

    btn_utc1_default=new QPushButton;
    btn_utc1_update=new QPushButton;
    btn_utc1_default->setText("默认");
    btn_utc1_update->setText("刷新");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_utc1_default);
    v1->addWidget(btn_utc1_update);
    QLabel *label=new QLabel;
    label->setText("UTC1参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    utc1_l0=new QLineEdit;
    utc1_l1=new QLineEdit;
    utc1_l2=new QLineEdit;
    utc1_l3=new QLineEdit;
    utc1_l4=new QLineEdit;
    utc1_l5=new QLineEdit;
    utc1_l6=new QLineEdit;
    utc1_l7=new QLineEdit;
    utc1_l8=new QLineEdit;
    utc1_l9=new QLineEdit;
    utc1_l10=new QLineEdit;
    utc1_l11=new QLineEdit;
    utc1_l12=new QLineEdit;
    utc1_l13=new QLineEdit;
    utc1_l14=new QLineEdit;
    utc1_l15=new QLineEdit;
    QFormLayout *f=new QFormLayout();
    f->addRow(utc_s1[0],utc1_l0);
    f->addRow(utc_s1[1],utc1_l1);
    f->addRow(utc_s1[2],utc1_l2);
    f->addRow(utc_s1[3],utc1_l3);
    f->addRow(utc_s1[4],utc1_l4);
    f->addRow(utc_s1[5],utc1_l5);
    f->addRow(utc_s1[6],utc1_l6);
    f->addRow(utc_s1[7],utc1_l7);
    f->addRow(utc_s1[8],utc1_l8);
    f->addRow(utc_s1[9],utc1_l9);
    f->addRow(utc_s1[10],utc1_l10);
    f->addRow(utc_s1[11],utc1_l11);
    f->addRow(utc_s1[12],utc1_l12);
    f->addRow(utc_s1[13],utc1_l13);
    f->addRow(utc_s1[14],utc1_l14);
    f->addRow(utc_s1[15],utc1_l15);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);
    utc1.setLayout(v);
    utc1.show();
}

void MainWindow::showOther()
{
    w_osd1.setWindowTitle("OSD1参数配置");

    btn_osd1_default=new QPushButton;
    btn_osd1_update=new QPushButton;
    btn_osd1_default->setText("默认");
    btn_osd1_update->setText("刷新");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_osd1_default);
    v1->addWidget(btn_osd1_update);
    QLabel *label=new QLabel;
    label->setText("OSD1参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    checkBox=new QCheckBox;
    osd1_pos_x=new QLineEdit;
    osd1_pos_y=new QLineEdit;
    osd1_lineEdit_label=new QLineEdit;
    osd1_lineEdit_context=new QLineEdit;
    osd1_lineEdit_font=new QLineEdit;
    osd1_lineEdit_color=new QLineEdit;
    osd1_lineEdit_transparency=new QLineEdit;


    QFormLayout *f=new QFormLayout();
    f->addRow(osd_s[0],checkBox);
    f->addRow(osd_s[1],osd1_pos_x);
    f->addRow(osd_s[2],osd1_pos_y);
    f->addRow(osd_s[3],osd1_lineEdit_label);
    f->addRow(osd_s[4],osd1_lineEdit_context);
    f->addRow(osd_s[5],osd1_lineEdit_font);
    f->addRow(osd_s[6],osd1_lineEdit_color);
    f->addRow(osd_s[7],osd1_lineEdit_transparency);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);
    w_osd1.setLayout(v);
    w_osd1.show();
}
void MainWindow::resetAction()
{

}

void MainWindow::btnSerialSlot()
{
    w_config_serial.setWindowTitle("串口配置");


    QStringList portNameList;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        portNameList.append(info.portName());
    }


    groupBox_trackboard = new QGroupBox();
    groupBox_trackboard->setTitle("串口");
    box_serial= new QComboBox(groupBox_trackboard);
    box_serial->addItems(portNameList);
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
    box_check->addItem("Even");
    box_check->addItem("None");
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

    QDialogButtonBox* button = new QDialogButtonBox();
    button->addButton( "OK", QDialogButtonBox::YesRole);
    button->addButton( "Cancel", QDialogButtonBox::NoRole);


    QFormLayout *playout_s1 = new QFormLayout();
    playout_s1->addRow(QStringLiteral("命令端口"), box_serial);
    playout_s1->addRow(QStringLiteral("波特率"), box_baud);
    playout_s1->addRow(QStringLiteral("校验"), box_check);
    playout_s1->addRow(QStringLiteral("数据位"), box_data);
    playout_s1->addRow(QStringLiteral("停止位"), box_stop);
    groupBox_trackboard->setLayout(playout_s1);

    QHBoxLayout *mainlayout3 = new QHBoxLayout;
    mainlayout3->addWidget(groupBox_trackboard);

    QVBoxLayout *mainlayout4 = new QVBoxLayout;
    mainlayout4->addLayout(mainlayout3);
    mainlayout4->addWidget(button);

    w_config_serial.setLayout(mainlayout4);

   w_config_serial.show();


}

void MainWindow::btnNetSlot()
{
    w_config_net.setWindowTitle(tr("网络配置"));
    QLineEdit* lineEdit_port = new QLineEdit();
    QLineEdit* lineEdit_ip = new QLineEdit();
    lineEdit_ip->setInputMask("000.000.000.000");

    QDialogButtonBox* button_socket = new QDialogButtonBox();
    button_socket->addButton( "OK", QDialogButtonBox::YesRole);
    button_socket->addButton( "Cancel", QDialogButtonBox::NoRole);

    QFormLayout *pLayout_socket = new QFormLayout();
    pLayout_socket->addRow(QStringLiteral("IP："), lineEdit_ip);
    pLayout_socket->addRow(QStringLiteral("端口："), lineEdit_port);

    QVBoxLayout *socket_layout2 = new QVBoxLayout;
    socket_layout2->addLayout(pLayout_socket);
    socket_layout2->addWidget(button_socket);
    w_config_net.setLayout(socket_layout2);

    w_config_net.show();
}

void MainWindow::toNetSlot(int i)
{
     s->setCurrentIndex(i);

}

void MainWindow::btnLoadSlot()
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
    QString path=QFileDialog::getExistingDirectory(NULL, tr("选择文件夹"),"E:\\",QFileDialog::ShowDirsOnly);
}

void MainWindow::btnSensor1SwitchSlot()
{

    w_seitchField.setWindowTitle("可切换视场");

    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("刷新");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_s1Switch_default);
    v1->addWidget(btn_s1Switch_update);
    QLabel *label=new QLabel;
    label->setText("可切换视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);




    lineEdit_s1_Fov0=new QLineEdit;
    lineEdit_s1_Fov1=new QLineEdit;
    lineEdit_s1_Fov2=new QLineEdit;
    lineEdit_s1_Fov3=new QLineEdit;
    lineEdit_s1_Fov4=new QLineEdit;
    lineEdit_s1_Fov5=new QLineEdit;
    lineEdit_s1_Fov6=new QLineEdit;
    lineEdit_s1_Fov7=new QLineEdit;
    lineEdit_s1_Fov8=new QLineEdit;
    lineEdit_s1_Fov9=new QLineEdit;
    lineEdit_s1_Fov10=new QLineEdit;
    lineEdit_s1_Fov11=new QLineEdit;
    lineEdit_s1_Fov12=new QLineEdit;
    lineEdit_s1_Fov13=new QLineEdit;
    lineEdit_s1_Fov14=new QLineEdit;

    QFormLayout *f=new QFormLayout();
    f->addRow(sensor_switch_s1[0],lineEdit_s1_Fov0);
    f->addRow(sensor_switch_s1[1],lineEdit_s1_Fov1);
    f->addRow(sensor_switch_s1[2],lineEdit_s1_Fov2);
    f->addRow(sensor_switch_s1[3],lineEdit_s1_Fov3);
    f->addRow(sensor_switch_s1[4],lineEdit_s1_Fov4);
    f->addRow(sensor_switch_s1[5],lineEdit_s1_Fov5);
    f->addRow(sensor_switch_s1[6],lineEdit_s1_Fov6);
    f->addRow(sensor_switch_s1[7],lineEdit_s1_Fov7);
    f->addRow(sensor_switch_s1[8],lineEdit_s1_Fov8);
    f->addRow(sensor_switch_s1[9],lineEdit_s1_Fov9);
    f->addRow(sensor_switch_s1[10],lineEdit_s1_Fov10);
    f->addRow(sensor_switch_s1[11],lineEdit_s1_Fov11);
    f->addRow(sensor_switch_s1[12],lineEdit_s1_Fov12);
    f->addRow(sensor_switch_s1[13],lineEdit_s1_Fov13);
    f->addRow(sensor_switch_s1[14],lineEdit_s1_Fov14);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);
    w_seitchField.setLayout(v);
    w_seitchField.show();
}

void MainWindow::btnSensor2ContinueSlot()
{
    sta->setCurrentIndex(3);
    w_ContinueField.setWindowTitle("连续视场");

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("刷新");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_continue_default);
    v1->addWidget(btn_continue_update);
    QLabel *label=new QLabel;
    label->setText("连续视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    lineEdit_c0=new QLineEdit;
    lineEdit_c1=new QLineEdit;
    lineEdit_c2=new QLineEdit;
    lineEdit_c3=new QLineEdit;
    lineEdit_c4=new QLineEdit;
    lineEdit_c5=new QLineEdit;
    lineEdit_c6=new QLineEdit;
    lineEdit_c7=new QLineEdit;
    lineEdit_c8=new QLineEdit;
    lineEdit_c9=new QLineEdit;
    lineEdit_c10=new QLineEdit;
    lineEdit_c11=new QLineEdit;
    lineEdit_c12=new QLineEdit;
    lineEdit_c13=new QLineEdit;
    lineEdit_c14=new QLineEdit;
    lineEdit_c15=new QLineEdit;
    lineEdit_c16=new QLineEdit;
    lineEdit_c17=new QLineEdit;
    lineEdit_c18=new QLineEdit;
    lineEdit_c19=new QLineEdit;
    lineEdit_c20=new QLineEdit;
    lineEdit_c21=new QLineEdit;
    lineEdit_c22=new QLineEdit;
    lineEdit_c23=new QLineEdit;
    lineEdit_c24=new QLineEdit;
    lineEdit_c25=new QLineEdit;

    QFormLayout *f=new QFormLayout();

    f->addRow(sensor_Continue_s1[0],lineEdit_c0);
    f->addRow(sensor_Continue_s1[1],lineEdit_c1);
    f->addRow(sensor_Continue_s1[2],lineEdit_c2);
    f->addRow(sensor_Continue_s1[3],lineEdit_c3);
    f->addRow(sensor_Continue_s1[4],lineEdit_c4);
    f->addRow(sensor_Continue_s1[5],lineEdit_c5);
    f->addRow(sensor_Continue_s1[6],lineEdit_c6);
    f->addRow(sensor_Continue_s1[7],lineEdit_c7);
    f->addRow(sensor_Continue_s1[8],lineEdit_c8);
    f->addRow(sensor_Continue_s1[9],lineEdit_c9);
    f->addRow(sensor_Continue_s1[10],lineEdit_c10);
    f->addRow(sensor_Continue_s1[11],lineEdit_c11);
    f->addRow(sensor_Continue_s1[12],lineEdit_c12);
    f->addRow(sensor_Continue_s1[13],lineEdit_c13);
    f->addRow(sensor_Continue_s1[14],lineEdit_c14);
    f->addRow(sensor_Continue_s1[15],lineEdit_c15);
    f->addRow(sensor_Continue_s1[16],lineEdit_c16);
    f->addRow(sensor_Continue_s1[17],lineEdit_c17);
    f->addRow(sensor_Continue_s1[18],lineEdit_c18);
    f->addRow(sensor_Continue_s1[19],lineEdit_c19);
    f->addRow(sensor_Continue_s1[20],lineEdit_c20);
    f->addRow(sensor_Continue_s1[21],lineEdit_c21);
    f->addRow(sensor_Continue_s1[22],lineEdit_c22);
    f->addRow(sensor_Continue_s1[23],lineEdit_c23);
    f->addRow(sensor_Continue_s1[24],lineEdit_c24);
    f->addRow(sensor_Continue_s1[25],lineEdit_c25);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);
    w_ContinueField.setLayout(v);
    w_ContinueField.show();
}

void MainWindow::toSensor_switch(int i)
{
    if(i==1){
     sta->setCurrentIndex(1);
    }else if(i==2){
        sta->setCurrentIndex(2);
    }else{
        sta->setCurrentIndex(3);
    }
}


