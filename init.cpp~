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

    QAction* act_othCfg=new QAction("OSD配置");
    menu[0]->addAction(act_othCfg);
//    QMenu *osd=new QMenu("OSD配置");
//    QAction* act_othCfg1=new QAction("OSD1");
//    osd->addAction(act_othCfg1);
//    QAction* act_othCfg2=new QAction("OSD2");
//    osd->addAction(act_othCfg2);
//    QAction* act_othCfg3=new QAction("OSD3");
//    osd->addAction(act_othCfg3);
//    menu[0]->addMenu(osd);

    QMenu* capture=new QMenu("捕获框配置");
    QAction* act_cap1=new QAction("捕获框");
    capture->addAction(act_cap1);
    QAction* act_cap2=new QAction("波门");
    capture->addAction(act_cap2);
    QAction* act_cap3=new QAction("画线");
    capture->addAction(act_cap3);
    menu[0]->addMenu(capture);

    QAction* act_rstCfg=new QAction("恢复默认");
    menu[0]->addAction(act_rstCfg);

    ui->menuBar->addMenu(menu[0]);

    connect(act_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showSysCfg()));
    connect(act_platCfg,SIGNAL(triggered(bool)),this,SLOT(showPlat()));
    connect(act_cmrCfg,SIGNAL(triggered(bool)),this,SLOT(showCamera()));
    connect(act_algCfg1,SIGNAL(triggered(bool)),this,SLOT(showAlg()));
    connect(act_algCfg2,SIGNAL(triggered(bool)),this,SLOT(showAlg2()));
    connect(act_algCfg3,SIGNAL(triggered(bool)),this,SLOT(showAlg3()));
    connect(act_othCfg,SIGNAL(triggered(bool)),this,SLOT(showOther()));
    connect(act_cap1,SIGNAL(triggered(bool)),this,SLOT(showCapture1()));
    connect(act_cap2,SIGNAL(triggered(bool)),this,SLOT(showCapture2()));
    connect(act_cap3,SIGNAL(triggered(bool)),this,SLOT(showCapture3()));
    connect(act_rstCfg,SIGNAL(triggered(bool)),this,SLOT(resetAction()));

}

void MainWindow::init_sysCfg()
{
    w_config=new QWidget;
    w_config->setWindowTitle(tr("系统配置"));
    lineEdit=new QLineEdit;
    QComboBox *box1=new QComboBox;
    box1->addItem("0");
    box1->addItem("1");
    box1->addItem("2");
    box1->addItem("3");
    box1->addItem("4");
    box1->addItem("5");
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

    QPushButton *btnDown=new QPushButton;
    btnDown->setText("导入");
    QPushButton *btnUp=new QPushButton;
    btnUp->setText("导出");
    CBox_font=new QComboBox;
    CBox_font->addItem("宋体");
    CBox_font->addItem("黑体");
    CBox_font_size=new QComboBox;
    CBox_font_size->addItem("五号");
    CBox_font_size->addItem("六号");
    QPushButton *btnSave=new QPushButton;
    btnSave->setText("保存");

    QGroupBox *groupBox_upgrade = new QGroupBox();
    groupBox_upgrade->setTitle("文件传输");
    upgrade_ip = new QLineEdit(groupBox_upgrade);
    upgrade_ip->setInputMask("000.000.000.000");
    upgrade_ip->setText("192.168.1.202");
    upgrade_port = new QLineEdit(groupBox_upgrade);
    upgrade_port->setText("8999");
    QPushButton *btnUpdate=new QPushButton(groupBox_upgrade);
    btnUpdate->setText("升级");
    upgrade_show = new QTextEdit(groupBox_upgrade);

    QComboBox *CBox=new QComboBox;
    CBox->addItem("最慢");
    CBox->addItem("低中");
    CBox->addItem("高中");
    CBox->addItem("最高");
    CBox->setCurrentIndex(1);

    QFormLayout *vlayout = new QFormLayout;
    vlayout->addRow("IP：",upgrade_ip);
    vlayout->addRow("端口：",upgrade_port);
    vlayout->addRow("软件升级",btnUpdate);
    vlayout->addRow("导入配置", btnDown);
    vlayout->addRow("导出配置", btnUp);
    vlayout->addRow(upgrade_show);
    groupBox_upgrade->setLayout(vlayout);

    QFormLayout *pLayout = new QFormLayout;

    pLayout->addRow(QStringLiteral("相机通道总数"), lineEdit);
    pLayout->addRow("相机通道选择", box1);
    pLayout->addRow("串口/网口选择", box2);
    pLayout->addRow("串口/网络配置", s);
    pLayout->addRow("OSD字体配置", CBox_font);
    pLayout->addRow("OSD字号配置", CBox_font_size);
    pLayout->addRow("变焦速度等级", CBox);
    pLayout->addRow("保存配置", btnSave);
    pLayout->addRow(groupBox_upgrade);

    connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(lEdt_sysCfg_Slot()));
    connect(box1,SIGNAL(activated(int)),SLOT(CBox_sysCfg_Slot(int)));
    connect(box2,SIGNAL(currentIndexChanged(int)),this,SLOT(toNetSlot(int)));
    connect(btnSerial,SIGNAL(clicked(bool)),this,SLOT(btnSerialSlot()));
    connect(btnNet,SIGNAL(clicked(bool)),this,SLOT(btnNetSlot()));
    connect(btnDown,SIGNAL(clicked(bool)),this,SLOT(btnDownSlot()));
    connect(btnUp,SIGNAL(clicked(bool)),this,SLOT(btnUpSlot()));
    connect(btnSave,SIGNAL(clicked(bool)),this,SLOT(btnSaveSlot())); 
    connect(btnUpdate,SIGNAL(clicked(bool)),this,SLOT(btnUpdate()));
    connect(CBox_font,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_Slot(int)));
    connect(CBox_font_size,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_size_Slot(int)));
    connect(CBox,SIGNAL(activated(int)),this,SLOT(CBox_View_Slot(int)));

    w_config->setLayout(pLayout);
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
    paint.drawEllipse(a-10,b-10,20,20);

    QPainter painter(this);
    QPen pen(Qt::black,2,Qt::DotLine,Qt::RoundCap,Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawLine(QPointF(POINTX, POINTY+CENTER/2), QPointF(POINTX+CENTER, POINTY+CENTER/2));
    painter.drawLine(QPointF(POINTX+CENTER/2, POINTY), QPointF(POINTX+CENTER/2, POINTY+CENTER));


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    int x=event->pos().x();
//    int y=event->pos().y();
    mousePress = 1;
   if((abs(event->pos().x()-a)<=10)&&((event->pos().y()-b)<=10)){
       m_dragging = 1;
     // qDebug()<<"x"<<x<<endl<<"y"<<y<<endl;
   }
   else
       m_dragging = 0;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(mousePress==1){
        if(a!=(POINTX+CENTER/2)||b!=(POINTY+CENTER/2)){
            mousePress = 0;
            a=POINTX+CENTER/2;
            b=POINTY+CENTER/2;
            send_mutex.lock();
            send_arr[4] = 0x15;
            send_arr[5]=0x00;
            send_arr[6]=0x00;
            send_arr[7]=0x00;
            send_arr[8]=0x00;
            old_x=a;
            old_y=b;
            send_oneframe(5);
            send_mutex.unlock();
            update();
        }
    }
}
void MainWindow::calculationCircle(int center_a, int center_b, int x, int y)
{
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{


    if (mousePress&&m_dragging)
    {
        int x=event->pos().x();
        int y=event->pos().y();
//        int l1=0.414*x+42.604;
//        int l2=(-0.414)*x+385.396;
//        int l3=(y+785.396)/2.414;
//        int l4=(y-1213.396)/(-2.414);
//        int l5=2.414*x-785.396;
//        int l6=(-2.414)*x+1213.396;

        int m=qAbs(x-a_center);
        int n=qAbs(y-b_center);
        int l=qSqrt(((x-POINTX-CENTER/2)*(x-POINTX-CENTER/2)+(y-POINTY-CENTER/2)*(y-POINTY-CENTER/2)));

        if(l>CENTER/2)
        {
            sectrk_x = (event->pos().x()-POINTX)*RATIO+CENTER/2;
            sectrk_y = (event->pos().y()-POINTY)*RATIO+CENTER/2;
           if((y-b_center)<0)
              b=b_center-n*CENTER/(2*l);
           else
              b=b_center+n*CENTER/(2*l);
           if(x-a_center<0)
              a=a_center-m*CENTER/(2*l);
           else
              a=a_center+m*CENTER/(2*l);
           update();
        }else{
           sectrk_x = (event->pos().x()-POINTX)*RATIO+CENTER/2;
           sectrk_y = (event->pos().y()-POINTY)*RATIO+CENTER/2;
           a=event->pos().x();
           b=event->pos().y();
           update();

        }
//        if(judgment==1){//跟踪微调

//            if(l>CENTER/4){
//               if(y>l2 && y<l1 && x>0){//右
//                   jud_area=1;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(y<l2 && y>l1){//左
//                   jud_area=5;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(x<l4 && x>l3 ){//上
//                   jud_area=7;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(x>l4 && x<l3 ){//下
//                   jud_area=3;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(y>l1 && l<l5){//右上
//                   jud_area=2;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(y<l1 && l>l5){//左下
//                   jud_area=6;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(y>l2 && y<l6){//左上
//                   jud_area=4;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }else if(y<l2 && y>l6){//右下
//                   jud_area=8;
//                   time->start(500);
//                   qDebug()<<jud_area;
//               }}else{
//                jud_area=0;

//                send_mutex.lock();
//                send_arr[4] = 0x08;
//                send_arr[5] = 0x00;
//                send_arr[6] = 0x00;
//                send_oneframe(3);
//                send_mutex.unlock();
//                qDebug()<<jud_area;
         //   }


       // }else{//手柄传输控制
        send_mutex.lock();
        send_arr[4] = 0x15;
        if(x-a_center>0){//判断方位
            send_arr[5]=0x02;
        }else if(x-a_center<0){
            send_arr[5]=0x01;
        }else{
            send_arr[5]=0x00;
        }
        if(qAbs(a-a_center)*2/3==64){
            send_arr[6]=0x3F;
        }else{
            send_arr[6]=qAbs(a-a_center)*2/3;
        }

        if(y-b_center>0){//判断俯仰
            send_arr[7]=0x02;
        }else if(y-b_center<0){
            send_arr[7]=0x01;
        }else{
            send_arr[7]=0x00;
        }
        if(qAbs(b-b_center)*2/3==64){
            send_arr[8]=0x3F;
        }else{
            send_arr[8]=qAbs(b-b_center)*2/3;
        }

        //保留上一次x，y的值。
        old_x=a;
        old_y=b;
        send_oneframe(5);
        send_mutex.unlock();
        }
   // }
}
void MainWindow::timeoutSlot()
{
    switch( value_search){
        case 0:
            value_y-=5;
          break;
        case 1:
            value_x+=5;
          break;
        case 2:
            value_x-=5;
          break;
        case 3:
            value_y+=5;
          break;
    default:
        break;
    }
    send_mutex.lock();
    send_arr[4] = 0x0b;
    send_arr[5] = 0x01;
    send_arr[6] = value_x&0xff;
    send_arr[7] =(value_x>>8)&0xff;
    send_arr[8] = value_y&0xff;
    send_arr[9] = (value_y>>8)&0xff;
    send_oneframe(6);
    send_mutex.unlock();
}

void MainWindow::showJos()
{
    j.show();
}

void MainWindow::showSysCfg()
{
    w_config->show();
}

void MainWindow::showPlat()
{
    w_plat=new QWidget;
    w_plat->setWindowTitle("平台配置");

    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x01;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=1;i<9;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x02;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=1;i<8;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x03;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    QPushButton* btn_jos_default=new QPushButton;
    QPushButton* btn_jos_update=new QPushButton;
    btn_jos_default->setText("默认");
    btn_jos_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_jos_default);
    v1->addWidget(btn_jos_update);
    QLabel *label=new QLabel;
    label->setText("平台参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_Jos=new QGroupBox();
    gbox_Jos->setTitle("手柄");

    josDead_lineEdt=new QLineEdit;
    josPoint_lineEdt=new QLineEdit;
    josInputG_x=new QLineEdit;
    josInputG_y=new QLineEdit;
//    josOutputG_x=new QLineEdit;
//    josOutputG_y=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(jos_s[0],josDead_lineEdt);
    f1->addRow(jos_s[1],josPoint_lineEdt);
    f1->addRow(jos_s[2],josInputG_x);
    f1->addRow(jos_s[3],josInputG_y);
//    f1->addRow(jos_s[4],josOutputG_x);
//    f1->addRow(jos_s[5],josOutputG_y);
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
//    outMode=new QComboBox;
//    outMode->addItem(string_outMode[0]);
//    outMode->addItem(string_outMode[1]);
//    outMode->addItem(string_outMode[2]);
//    outMode->addItem(string_outMode[3]);
//    outMode->addItem(string_outMode[4]);
//    outMode->addItem(string_outMode[5]);
//    outMode->addItem(string_outMode[6]);
//    outMode->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
    f3->addRow(plat_s[0],bleedx_plat);
    f3->addRow(plat_s[1],bleedy_plat);
    f3->addRow(plat_s[2],mx_plat);
    f3->addRow(plat_s[3],my_plat);
    f3->addRow(plat_s[4],deadx_plat);
    f3->addRow(plat_s[5],deady_plat);
    f3->addRow(plat_s[6],a_plat);
   // f3->addRow(plat_s[7],outMode);
    gbox_plat->setLayout(f3);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_Jos);
    v->addWidget(gbox_PID);
    v->addWidget(gbox_plat);

    w_plat->setLayout(v);

    connect(btn_jos_default,SIGNAL(clicked(bool)),this,SLOT(btn_Jos_Default_Slot()));
    connect(btn_jos_update,SIGNAL(clicked(bool)),this,SLOT(btn_Jos_Update_Slot()));
    connect(josDead_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos1_Slot()));
    connect(josPoint_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos2_Slot()));
    connect(josInputG_x,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos3_Slot()));
    connect(josInputG_y,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos4_Slot()));
//    connect(josOutputG_x,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos5_Slot()));
//    connect(josOutputG_y,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos6_Slot()));

    connect(kp1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot()));
    connect(ki1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot()));
    connect(kd1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot()));
    connect(k1,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot()));
    connect(kp2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot()));
    connect(ki2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot()));
    connect(kd2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot()));
    connect(k2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot()));

    connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
    connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(mx_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat3_Slot()));
    connect(my_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat4_Slot()));
    connect(deadx_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat5_Slot()));
    connect(deady_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat6_Slot()));
    connect(a_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat7_Slot()));
   // connect(outMode,SIGNAL(activated(int)),this,SLOT(outMode_Slot(int)));
    w_plat->show();
}

void MainWindow::showCamera()
{
    w_sersor1=new QWidget;
    w_sersor1->setWindowTitle("通道1");

    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道1参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);


//    for(int i=0;i<7;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x17;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    change1=new QComboBox;
    change1->addItem("固定视场");
    change1->addItem("可切换视场");
    change1->addItem("连续视场");

    //qDebug()<<change1->currentIndex();
    lineEdit_fieldRadio=new QLineEdit;
    QLabel *l=new  QLabel;
    l->setText("*");
    lineEdit_fieldResolution=new QLineEdit;
    lineEdit_fieldResolution2=new QLineEdit;
//    lineEdit_fieldResolution->setValidator(new QIntValidator(100,10000,this));
//    lineEdit_fieldResolution2->setValidator(new QIntValidator(100,10000,this));

    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_fieldResolution);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_fieldResolution2);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1[0],change1);
    f1->addRow(sensor_s1[1],lineEdit_fieldRadio);
    f1->addRow(sensor_s1[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");

    QLabel* l1=new QLabel;
    l1->setText("水平视场");
    QLabel* l2=new QLabel;
    l2->setText("靶心X位置");
    QLabel* l3=new QLabel;
    l3->setText("靶心Y位置");
    QLabel* l4=new QLabel;
    l4->setText(" ");

    lEdt=new QLineEdit;
    sp=new QSpinBox;
    sp2=new QSpinBox;
    sp->setRange(0,9999);
    sp2->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l1,0,0,1,1);
    gl->addWidget(l2,0,1,1,1);
    gl->addWidget(l3,0,2,1,1);
    gl->addWidget(l4,0,3,1,1);
    gl->addWidget(lEdt,1,0,1,1);
    gl->addWidget(sp,1,1,1,1);
    gl->addWidget(sp2,1,2,1,1);
   // gl->addWidget(ok,1,3,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(change1,SIGNAL(activated(int)),this,SLOT(tosersor_fix(int)));
    connect(lineEdit_fieldRadio,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot()));
    connect(lineEdit_fieldResolution,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot()));
    connect(lineEdit_fieldResolution2,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot()));
    connect(lEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot()));
    connect(sp,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot(int)));
    connect(sp2,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot(int)));
   // connect(ok,SIGNAL(clicked(bool)),this,SLOT(btn_fix_Slot()));
    w_sersor1->setLayout(v);
    w_sersor1->resize(300,200);
    w_sersor1->show();

}

void MainWindow::showAlg()
{
    utc1=new QWidget;
    utc1->setWindowTitle("UTC1参数配置");
//    for(int i=0;i<16;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x04;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    btn_utc1_default=new QPushButton;
    btn_utc1_update=new QPushButton;
    btn_utc1_default->setText("默认");
    btn_utc1_update->setText("保存");
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

    connect(btn_utc1_default,SIGNAL(clicked(bool)),this,SLOT(btn_utc1_default_Slot()));
    connect(btn_utc1_update,SIGNAL(clicked(bool)),this,SLOT(btn_utc1_update_Slot()));
    connect(utc1_l0,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l0_Slot()));
    connect(utc1_l1,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l1_Slot()));
    connect(utc1_l2,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l2_Slot()));
    connect(utc1_l3,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l3_Slot()));
    connect(utc1_l4,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l4_Slot()));
    connect(utc1_l5,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l5_Slot()));
    connect(utc1_l6,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l6_Slot()));
    connect(utc1_l7,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l7_Slot()));
    connect(utc1_l8,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l8_Slot()));
    connect(utc1_l9,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l9_Slot()));
    connect(utc1_l10,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l10_Slot()));
    connect(utc1_l11,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l11_Slot()));
    connect(utc1_l12,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l12_Slot()));
    connect(utc1_l13,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l13_Slot()));
    connect(utc1_l14,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l14_Slot()));
    connect(utc1_l15,SIGNAL(returnPressed()),this,SLOT(lEdt_utc1_l15_Slot()));

    utc1->setLayout(v);
    utc1->show();
}

void MainWindow::showAlg2()
{
    utc2=new QWidget;
    utc2->setWindowTitle("UTC2参数配置");
    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x05;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    btn_utc2_default=new QPushButton;
    btn_utc2_update=new QPushButton;
    btn_utc2_default->setText("默认");
    btn_utc2_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_utc2_default);
    v1->addWidget(btn_utc2_update);
    QLabel *label=new QLabel;
    label->setText("UTC1参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    utc2_l0=new QLineEdit;
    utc2_l1=new QLineEdit;
    utc2_l2=new QLineEdit;
    utc2_l3=new QLineEdit;
    utc2_l4=new QLineEdit;
    utc2_l5=new QLineEdit;
    utc2_l6=new QLineEdit;
    utc2_l7=new QLineEdit;
    utc2_l8=new QLineEdit;
    utc2_l9=new QLineEdit;
    utc2_l10=new QLineEdit;
    utc2_l11=new QLineEdit;
    utc2_l12=new QLineEdit;
    utc2_l13=new QLineEdit;
    utc2_l14=new QLineEdit;
    utc2_l15=new QLineEdit;
    QFormLayout *f=new QFormLayout();
    f->addRow(utc_s2[0],utc2_l0);
    f->addRow(utc_s2[1],utc2_l1);
    f->addRow(utc_s2[2],utc2_l2);
    f->addRow(utc_s2[3],utc2_l3);
    f->addRow(utc_s2[4],utc2_l4);
    f->addRow(utc_s2[5],utc2_l5);
    f->addRow(utc_s2[6],utc2_l6);
    f->addRow(utc_s2[7],utc2_l7);
    f->addRow(utc_s2[8],utc2_l8);
    f->addRow(utc_s2[9],utc2_l9);
    f->addRow(utc_s2[10],utc2_l10);
    f->addRow(utc_s2[11],utc2_l11);
    f->addRow(utc_s2[12],utc2_l12);
    f->addRow(utc_s2[13],utc2_l13);
    f->addRow(utc_s2[14],utc2_l14);
    f->addRow(utc_s2[15],utc2_l15);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);

    connect(btn_utc2_default,SIGNAL(clicked(bool)),this,SLOT(btn_utc2_default_Slot()));
    connect(btn_utc2_update,SIGNAL(clicked(bool)),this,SLOT(btn_utc2_update_Slot()));
    connect(utc2_l0,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l0_Slot()));
    connect(utc2_l1,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l1_Slot()));
    connect(utc2_l2,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l2_Slot()));
    connect(utc2_l3,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l3_Slot()));
    connect(utc2_l4,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l4_Slot()));
    connect(utc2_l5,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l5_Slot()));
    connect(utc2_l6,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l6_Slot()));
    connect(utc2_l7,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l7_Slot()));
    connect(utc2_l8,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l8_Slot()));
    connect(utc2_l9,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l9_Slot()));
    connect(utc2_l10,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l10_Slot()));
    connect(utc2_l11,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l11_Slot()));
    connect(utc2_l12,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l12_Slot()));
    connect(utc2_l13,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l13_Slot()));
    connect(utc2_l14,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l14_Slot()));
    connect(utc2_l15,SIGNAL(returnPressed()),this,SLOT(lEdt_utc2_l15_Slot()));

    utc2->setLayout(v);
    utc2->show();
}
void MainWindow::showAlg3()
{
    utc3=new QWidget;
    utc3->setWindowTitle("UTC3参数配置");

//    for(int i=0;i<16;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x06;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    btn_utc3_default=new QPushButton;
    btn_utc3_update=new QPushButton;
    btn_utc3_default->setText("默认");
    btn_utc3_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_utc3_default);
    v1->addWidget(btn_utc3_update);
    QLabel *label=new QLabel;
    label->setText("UTC1参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    utc3_l0=new QLineEdit;
    utc3_l1=new QLineEdit;
    utc3_l2=new QLineEdit;
    utc3_l3=new QLineEdit;
    utc3_l4=new QLineEdit;
    utc3_l5=new QLineEdit;
    utc3_l6=new QLineEdit;
    utc3_l7=new QLineEdit;
    utc3_l8=new QLineEdit;
    utc3_l9=new QLineEdit;
    utc3_l10=new QLineEdit;
    utc3_l11=new QLineEdit;
    utc3_l12=new QLineEdit;
    utc3_l13=new QLineEdit;
    utc3_l14=new QLineEdit;
    utc3_l15=new QLineEdit;
    QFormLayout *f=new QFormLayout();
    f->addRow(utc_s3[0],utc3_l0);
    f->addRow(utc_s3[1],utc3_l1);
    f->addRow(utc_s3[2],utc3_l2);
    f->addRow(utc_s3[3],utc3_l3);
    f->addRow(utc_s3[4],utc3_l4);
    f->addRow(utc_s3[5],utc3_l5);
    f->addRow(utc_s3[6],utc3_l6);
    f->addRow(utc_s3[7],utc3_l7);
    f->addRow(utc_s3[8],utc3_l8);
    f->addRow(utc_s3[9],utc3_l9);
    f->addRow(utc_s3[10],utc3_l10);
    f->addRow(utc_s3[11],utc3_l11);
    f->addRow(utc_s3[12],utc3_l12);
    f->addRow(utc_s3[13],utc3_l13);
    f->addRow(utc_s3[14],utc3_l14);
    f->addRow(utc_s3[15],utc3_l15);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f);

    connect(btn_utc3_default,SIGNAL(clicked(bool)),this,SLOT(btn_utc3_default_Slot()));
    connect(btn_utc3_update,SIGNAL(clicked(bool)),this,SLOT(btn_utc3_update_Slot()));
    connect(utc3_l0,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l0_Slot()));
    connect(utc3_l1,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l1_Slot()));
    connect(utc3_l2,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l2_Slot()));
    connect(utc3_l3,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l3_Slot()));
    connect(utc3_l4,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l4_Slot()));
    connect(utc3_l5,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l5_Slot()));
    connect(utc3_l6,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l6_Slot()));
    connect(utc3_l7,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l7_Slot()));
    connect(utc3_l8,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l8_Slot()));
    connect(utc3_l9,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l9_Slot()));
    connect(utc3_l10,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l10_Slot()));
    connect(utc3_l11,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l11_Slot()));
    connect(utc3_l12,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l12_Slot()));
    connect(utc3_l13,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l13_Slot()));
    connect(utc3_l14,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l14_Slot()));
    connect(utc3_l15,SIGNAL(returnPressed()),this,SLOT(lEdt_utc3_l15_Slot()));

    utc3->setLayout(v);
    utc3->show();
}



void MainWindow::showCapture1()
{
    w_capture1=new QWidget;
    w_capture1->setWindowTitle("捕获框参数设置");

//    for(int i=0;i<12;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x2D;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    btn_capture_default=new QPushButton;
    btn_capture_update=new QPushButton;
    btn_capture_default->setText("默认");
    btn_capture_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_capture_default);
    v1->addWidget(btn_capture_update);
    QLabel *label=new QLabel;
    label->setText("捕获框参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    cap_0_w=new QLineEdit;
    cap_1_w=new QLineEdit;
    cap_2_w=new QLineEdit;
    cap_3_w=new QLineEdit;
    cap_4_w=new QLineEdit;
    cap_5_w=new QLineEdit;
    cap_0_h=new QLineEdit;
    cap_1_h=new QLineEdit;
    cap_2_h=new QLineEdit;
    cap_3_h=new QLineEdit;
    cap_4_h=new QLineEdit;
    cap_5_h=new QLineEdit;

    QGroupBox *cap=new QGroupBox;
    cap->setTitle("捕获框");
    QFormLayout *f1=new QFormLayout();
    f1->addRow(string_cap[0],cap_0_w);
    f1->addRow(string_cap[1],cap_1_w);
    f1->addRow(string_cap[2],cap_2_w);
    f1->addRow(string_cap[3],cap_3_w);
    f1->addRow(string_cap[4],cap_4_w);
    f1->addRow(string_cap[5],cap_5_w);
    f1->addRow(string_cap[6],cap_0_h);
    f1->addRow(string_cap[7],cap_1_h);
    f1->addRow(string_cap[8],cap_2_h);
    f1->addRow(string_cap[9],cap_3_h);
    f1->addRow(string_cap[10],cap_4_h);
    f1->addRow(string_cap[11],cap_5_h);
    cap->setLayout(f1);

    QVBoxLayout *h=new QVBoxLayout;
    h->addLayout(h1);
    h->addWidget(cap);

    connect(btn_capture_default,SIGNAL(clicked(bool)),this,SLOT(btn_capture_default_Slot()));
    connect(btn_capture_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture_update_Slot()));
    connect(cap_0_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_0()));
    connect(cap_1_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_1()));
    connect(cap_2_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_2()));
    connect(cap_3_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_3()));
    connect(cap_4_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_4()));
    connect(cap_5_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_5()));
    connect(cap_0_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_6()));
    connect(cap_1_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_7()));
    connect(cap_2_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_8()));
    connect(cap_3_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_9()));
    connect(cap_4_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_10()));
    connect(cap_5_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_capture_11()));

    w_capture1->setLayout(h);
    w_capture1->show();

}

void MainWindow::showCapture2()
{
    w_capture2=new QWidget;
    w_capture2->setWindowTitle("波门参数设置");

//    for(int i=0;i<12;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x2E;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    btn_capture2_default=new QPushButton;
    btn_capture2_update=new QPushButton;
    btn_capture2_default->setText("默认");
    btn_capture2_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_capture2_default);
    v1->addWidget(btn_capture2_update);
    QLabel *label=new QLabel;
    label->setText("波门参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    bomen_0_w=new QLineEdit;
    bomen_1_w=new QLineEdit;
    bomen_2_w=new QLineEdit;
    bomen_3_w=new QLineEdit;
    bomen_4_w=new QLineEdit;
    bomen_5_w=new QLineEdit;
    bomen_0_h=new QLineEdit;
    bomen_1_h=new QLineEdit;
    bomen_2_h=new QLineEdit;
    bomen_3_h=new QLineEdit;
    bomen_4_h=new QLineEdit;
    bomen_5_h=new QLineEdit;

    QGroupBox *bomen=new QGroupBox;
    QFormLayout *f2=new QFormLayout();
    f2->addRow(string_bomen[0],bomen_0_w);
    f2->addRow(string_bomen[1],bomen_1_w);
    f2->addRow(string_bomen[2],bomen_2_w);
    f2->addRow(string_bomen[3],bomen_3_w);
    f2->addRow(string_bomen[4],bomen_4_w);
    f2->addRow(string_bomen[5],bomen_5_w);
    f2->addRow(string_bomen[6],bomen_0_h);
    f2->addRow(string_bomen[7],bomen_1_h);
    f2->addRow(string_bomen[8],bomen_2_h);
    f2->addRow(string_bomen[9],bomen_3_h);
    f2->addRow(string_bomen[10],bomen_4_h);
    f2->addRow(string_bomen[11],bomen_5_h);
    bomen->setTitle("波门");
    bomen->setLayout(f2);

    QVBoxLayout *h=new QVBoxLayout;
    h->addLayout(h1);
    h->addWidget(bomen);

    connect(btn_capture2_default,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_default_SLot()));
    connect(btn_capture2_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));

    connect(bomen_0_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_0()));
    connect(bomen_1_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_1()));
    connect(bomen_2_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_2()));
    connect(bomen_3_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_3()));
    connect(bomen_4_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_4()));
    connect(bomen_5_w,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_5()));
    connect(bomen_0_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_6()));
    connect(bomen_1_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_7()));
    connect(bomen_2_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_8()));
    connect(bomen_3_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_9()));
    connect(bomen_4_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_10()));
    connect(bomen_5_h,SIGNAL(textChanged(QString)),this,SLOT(lEdt_bomen_11()));

    w_capture2->setLayout(h);
    w_capture2->show();
}

void MainWindow::showCapture3()
{
    w_capture3=new QWidget;
    w_capture3->setWindowTitle("画线参数设置");

//    for(int i=0;i<12;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x2F;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

    btn_capture3_default=new QPushButton;
    btn_capture3_update=new QPushButton;
    btn_capture3_default->setText("默认");
    btn_capture3_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_capture3_default);
    v1->addWidget(btn_capture3_update);
    QLabel *label=new QLabel;
    label->setText("画线参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    QGroupBox *drawLine=new QGroupBox;
    drawLine->setTitle("画线");
    drawLine_0=new QLineEdit;
    drawLine_1=new QLineEdit;
    drawLine_2=new QLineEdit;
    drawLine_3=new QLineEdit;
    drawLine_4=new QLineEdit;
    drawLine_5=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(string_drawLine[0],drawLine_0);
    f3->addRow(string_drawLine[1],drawLine_1);
    f3->addRow(string_drawLine[2],drawLine_2);
    f3->addRow(string_drawLine[3],drawLine_3);
    f3->addRow(string_drawLine[4],drawLine_4);
    f3->addRow(string_drawLine[5],drawLine_5);
    drawLine->setLayout(f3);

    QVBoxLayout *h=new QVBoxLayout;
    h->addLayout(h1);
    h->addWidget(drawLine);

    connect(btn_capture3_default,SIGNAL(clicked(bool)),this,SLOT(btn_capture3_default_Slot()));
    connect(btn_capture3_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture3_update_Slot()));

    connect(drawLine_0,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_0()));
    connect(drawLine_1,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_1()));
    connect(drawLine_2,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_2()));
    connect(drawLine_3,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_3()));
    connect(drawLine_4,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_4()));
    connect(drawLine_5,SIGNAL(textChanged(QString)),this,SLOT(lEdt_drawLine_5()));

    w_capture3->setLayout(h);
    w_capture3->show();
}

void MainWindow::showOther()
{
    w_osd1=new QWidget;
    w_osd1->setWindowTitle("OSD参数配置");
//    for(int j=7;j<23;j++){
//        for(int i=0;i<4;i++){
//                send_mutex.lock();
//                send_arr[4]=0x31;
//                send_arr[5]=j;
//                send_arr[6]=i;
//                send_oneframe(3);
//                send_mutex.unlock();
//        }
//    }
//    for(int j=7;j<23;j++){
//        for(int i=5;i<7;i++){
//                send_mutex.lock();
//                send_arr[4]=0x31;
//                send_arr[5]=j;
//                send_arr[6]=i;
//                send_oneframe(3);
//                send_mutex.unlock();
//        }
//    }
//    for(int j=29;j<45;j++){
//        for(int i=0;i<4;i++){
//                send_mutex.lock();
//                send_arr[4]=0x31;
//                send_arr[5]=j;
//                send_arr[6]=i;
//                send_oneframe(3);
//                send_mutex.unlock();
//        }
//    }

//    for(int j=29;j<45;j++){
//        for(int i=5;i<7;i++){
//                send_mutex.lock();
//                send_arr[4]=0x31;
//                send_arr[5]=j;
//                send_arr[6]=i;
//                send_oneframe(3);
//                send_mutex.unlock();
//        }
//    }
    btn_osd1_default=new QPushButton;
    btn_osd1_update=new QPushButton;
    btn_osd1_default->setText("默认");
    btn_osd1_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_osd1_default);
    v1->addWidget(btn_osd1_update);
    QLabel *label=new QLabel;
    label->setText("OSD参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);


    c=new QComboBox;
    c->addItem("OSD1");
    c->addItem("OSD2");
    c->addItem("OSD3");
    c->addItem("OSD4");
    c->addItem("OSD5");
    c->addItem("OSD6");
    c->addItem("OSD7");
    c->addItem("OSD8");
    c->addItem("OSD9");
    c->addItem("OSD10");
    c->addItem("OSD11");
    c->addItem("OSD12");
    c->addItem("OSD13");
    c->addItem("OSD14");
    c->addItem("OSD15");
    c->addItem("OSD16");
    c->addItem("OSD17");
    c->addItem("OSD18");
    c->addItem("OSD19");
    c->addItem("OSD20");
    c->addItem("OSD21");
    c->addItem("OSD22");
    c->addItem("OSD23");
    c->addItem("OSD24");
    c->addItem("OSD25");
    c->addItem("OSD26");
    c->addItem("OSD27");
    c->addItem("OSD28");
    c->addItem("OSD29");
    c->addItem("OSD30");
    c->addItem("OSD31");
    c->addItem("OSD32");

    checkBox=new QCheckBox;
    osd1_pos_x=new QLineEdit;
    osd1_pos_y=new QLineEdit;
    osd1_lineEdit_label=new QLineEdit;
    osd1_lineEdit_context=new QLineEdit;

    CBox_color=new QComboBox;
    CBox_color->addItem("黑色");
    CBox_color->addItem("白色");
    CBox_color->addItem("红色");
    CBox_color->addItem("黄色");
    CBox_color->addItem("蓝色");
    CBox_color->addItem("绿色");
    CBox_color->addItem("保存");
    CBox_color->setCurrentIndex(1);


//    osd1_lineEdit_font=new QLineEdit;
//    osd1_lineEdit_color=new QLineEdit;
    osd1_lineEdit_transparency=new QLineEdit;
    osd1_pos_x->setText("30");
    osd1_pos_y->setText("5");
    osd1_lineEdit_context->setText("云顶");
    osd1_lineEdit_transparency->setText("1");


    QFormLayout *f=new QFormLayout();
    f->addRow(osd_s[0],checkBox);
    f->addRow(osd_s[1],osd1_pos_x);
    f->addRow(osd_s[2],osd1_pos_y);
    //f->addRow(osd_s[3],osd1_lineEdit_label);
    f->addRow(osd_s[4],osd1_lineEdit_context);
//    f->addRow(osd_s[5],CBox_font);
//    f->addRow(osd_s[6],CBox_font_size);
    f->addRow(osd_s[7],CBox_color);
    f->addRow(osd_s[8],osd1_lineEdit_transparency);

    connect(c,SIGNAL(activated(int)),this,SLOT(toCBox(int)));

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(c);
    v->addLayout(f);

    connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(btn_osd_default_Slot()));
    connect(btn_osd1_update,SIGNAL(clicked(bool)),this,SLOT(btn_osd_update_Slot()));
    connect(c,SIGNAL(activated(int)),this,SLOT(CBox_osd_choose_Slot(int)));
   // connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(checkBox_Slot(int)));
   // connect(osd1_pos_x,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_x_Slot()));
    //connect(osd1_pos_y,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_y_Slot()));
   // connect(osd1_lineEdit_context,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_context_Slot()));

   // connect(CBox_color,SIGNAL(activated(int)),this,SLOT(CBox_osd_color_Slot(int)));
    //connect(osd1_lineEdit_transparency,SIGNAL(returnPressed()),this,SLOT(lEdt_)))
    w_osd1->setLayout(v);
    w_osd1->show();
}
void MainWindow::btnSensor1SwitchSlot()
{

    w_seitchField=new QWidget;
    w_seitchField->setWindowTitle("可切换视场");

//    for(int i=0;i<15;i++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x18;
//        send_arr[6]=i;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

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

    change2=new QComboBox;
    change2->addItem("可切换视场");
    change2->addItem("固定视场");
    change2->addItem("连续视场");
    lineEdit_switchRadio=new QLineEdit;

    lineEdit_switchResolution=new QLineEdit;
    lineEdit_switchResolution2=new QLineEdit;
    lineEdit_switchResolution->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2->setValidator(new QIntValidator(100,10000,this));
    QLabel *l=new  QLabel;
    l->setText("*");
    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_switchResolution);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_switchResolution2);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1[0],change2);
    f1->addRow(sensor_s1[1],lineEdit_switchRadio);
    f1->addRow(sensor_s1[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("可切换视场视场");

    QGridLayout *gl=new QGridLayout;
    QLabel* l1=new QLabel;
    l1->setText("水平视场");
    QLabel* l2=new QLabel;
    l2->setText("靶心X位置");
    QLabel* l3=new QLabel;
    l3->setText("靶心Y位置");
    QLabel* l4=new QLabel;
    l4->setText(" ");
    gl->addWidget(l1,0,0,1,1);
    gl->addWidget(l2,0,1,1,1);
    gl->addWidget(l3,0,2,1,1);
    gl->addWidget(l4,0,3,1,1);


    lineEdit_s1_Fov0=new QLineEdit;
    lineEdit_s1_Fov1=new QLineEdit;
    lineEdit_s1_Fov2=new QLineEdit;
    lineEdit_s1_Fov3=new QLineEdit;
    lineEdit_s1_Fov4=new QLineEdit;
    gl->addWidget(lineEdit_s1_Fov0,1,0,1,1);
    gl->addWidget(lineEdit_s1_Fov1,2,0,1,1);
    gl->addWidget(lineEdit_s1_Fov2,3,0,1,1);
    gl->addWidget(lineEdit_s1_Fov3,4,0,1,1);
    gl->addWidget(lineEdit_s1_Fov4,5,0,1,1);


    spbx_switch1=new QSpinBox;
    spbx_switch2=new QSpinBox;
    spbx_switch3=new QSpinBox;
    spbx_switch4=new QSpinBox;
    spbx_switch5=new QSpinBox;
    spbx_switch1->setRange(0,9999);
    spbx_switch2->setRange(0,9999);
    spbx_switch3->setRange(0,9999);
    spbx_switch4->setRange(0,9999);
    spbx_switch5->setRange(0,9999);
    gl->addWidget(spbx_switch1,1,1,1,1);
    gl->addWidget(spbx_switch2,2,1,1,1);
    gl->addWidget(spbx_switch3,3,1,1,1);
    gl->addWidget(spbx_switch4,4,1,1,1);
    gl->addWidget(spbx_switch5,5,1,1,1);

    spby_switch1=new QSpinBox;
    spby_switch2=new QSpinBox;
    spby_switch3=new QSpinBox;
    spby_switch4=new QSpinBox;
    spby_switch5=new QSpinBox;
    spby_switch1->setRange(0,9999);
    spby_switch2->setRange(0,9999);
    spby_switch3->setRange(0,9999);
    spby_switch4->setRange(0,9999);
    spby_switch5->setRange(0,9999);
    gl->addWidget(spby_switch1,1,2,1,1);
    gl->addWidget(spby_switch2,2,2,1,1);
    gl->addWidget(spby_switch3,3,2,1,1);
    gl->addWidget(spby_switch4,4,2,1,1);
    gl->addWidget(spby_switch5,5,2,1,1);

//    QPushButton *btn1=new QPushButton;
//    btn1->setText("确定");
//    QPushButton *btn2=new QPushButton;
//    btn2->setText("确定");
//    QPushButton *btn3=new QPushButton;
//    btn3->setText("确定");
//    QPushButton *btn4=new QPushButton;
//    btn4->setText("确定");
//    QPushButton *btn5=new QPushButton;
//    btn5->setText("确定");
//    gl->addWidget(btn1,1,3,1,1);
//    gl->addWidget(btn2,2,3,1,1);
//    gl->addWidget(btn3,3,3,1,1);
//    gl->addWidget(btn4,4,3,1,1);
//    gl->addWidget(btn5,5,3,1,1);

   g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(f1);
    v->addWidget(g);

    connect(change2,SIGNAL(activated(int)),this,SLOT(toSensor_switch(int)));
    connect(lineEdit_switchRadio,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot()));
    connect(lineEdit_switchResolution2,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot()));
//    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(btn_switch1_Slot()));
//    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(btn_switch2_Slot()));
//    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(btn_switch3_Slot()));
//    connect(btn4,SIGNAL(clicked(bool)),this,SLOT(btn_switch4_Slot()));
//    connect(btn5,SIGNAL(clicked(bool)),this,SLOT(btn_switch5_Slot()));

    w_seitchField->setLayout(v);
    w_seitchField->resize(300,200);
    w_seitchField->show();
}

void MainWindow::btnSensor2ContinueSlot()
{
    w_ContinueField=new QWidget;
    w_ContinueField->setWindowTitle("连续视场");

//    for(int j=25;j<27;j++){
//        for(int i=0;i<16;i++){
//            send_mutex.lock();
//            send_arr[4]=0x31;
//            send_arr[5]=j;
//            send_arr[6]=i;
//            send_oneframe(3);
//            send_mutex.unlock();
//        }
//    }

//    for(int m=0;m<7;m++){
//        send_mutex.lock();
//        send_arr[4]=0x31;
//        send_arr[5]=0x21;
//        send_arr[6]=m;
//        send_oneframe(3);
//        send_mutex.unlock();
//    }

//    QPushButton* btn_continue_default=new QPushButton;
//    QPushButton* btn_continue_update=new QPushButton;
//    btn_continue_default->setText("默认");
//    btn_continue_update->setText("刷新");
//    QVBoxLayout *v1=new QVBoxLayout;
//    v1->addWidget(btn_continue_default);
//    v1->addWidget(btn_continue_update);
//    QLabel *label=new QLabel;
//    label->setText("连续视场参数设置");
//    QHBoxLayout *h1=new QHBoxLayout;
//    h1->addLayout(v1);
//    h1->addWidget(label);

    change3=new QComboBox;
    change3->addItem("连续视场");
    change3->addItem("固定视场");
    change3->addItem("可切换视场");

    lineEdit_continueRadio=new QLineEdit;
    lineEdit_continueResolution=new QLineEdit;
    lineEdit_continueResolution2=new QLineEdit;
    lineEdit_continueResolution->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2->setValidator(new QIntValidator(100,10000,this));
    QLabel *l=new  QLabel;
    l->setText("*");
    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_continueResolution);

    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_continueResolution2);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1[0],change3);
    f1->addRow(sensor_s1[1],lineEdit_continueRadio);
    f1->addRow(sensor_s1[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("连续视场");

    QGridLayout *gl=new QGridLayout;
    QLabel* l1=new QLabel;
    l1->setText("ZOOM");
    QLabel* l2=new QLabel;
    l2->setText("靶心X位置");
    QLabel* l3=new QLabel;
    l3->setText("靶心Y位置");
    QLabel* l4=new QLabel;
    l4->setText(" ");
    gl->addWidget(l1,0,0,1,1);
    gl->addWidget(l2,0,1,1,1);
    gl->addWidget(l3,0,2,1,1);
    gl->addWidget(l4,0,3,1,1);

    lEdt1=new QLineEdit;
    lEdt2=new QLineEdit;
    lEdt3=new QLineEdit;
    lEdt4=new QLineEdit;
    lEdt5=new QLineEdit;
    lEdt6=new QLineEdit;
    lEdt7=new QLineEdit;
    lEdt8=new QLineEdit;
    lEdt9=new QLineEdit;
    lEdt10=new QLineEdit;
    lEdt11=new QLineEdit;
    lEdt12=new QLineEdit;
    lEdt13=new QLineEdit;
    gl->addWidget(lEdt1,1,0,1,1);
    gl->addWidget(lEdt2,2,0,1,1);
    gl->addWidget(lEdt3,3,0,1,1);
    gl->addWidget(lEdt4,4,0,1,1);
    gl->addWidget(lEdt5,5,0,1,1);
    gl->addWidget(lEdt6,6,0,1,1);
    gl->addWidget(lEdt7,7,0,1,1);
    gl->addWidget(lEdt8,8,0,1,1);
    gl->addWidget(lEdt9,9,0,1,1);
    gl->addWidget(lEdt10,10,0,1,1);
    gl->addWidget(lEdt11,11,0,1,1);
    gl->addWidget(lEdt12,12,0,1,1);
    gl->addWidget(lEdt13,13,0,1,1);

    spbx1=new QSpinBox;
    spbx2=new QSpinBox;
    spbx3=new QSpinBox;
    spbx4=new QSpinBox;
    spbx5=new QSpinBox;
    spbx6=new QSpinBox;
    spbx7=new QSpinBox;
    spbx8=new QSpinBox;
    spbx9=new QSpinBox;
    spbx10=new QSpinBox;
    spbx11=new QSpinBox;
    spbx12=new QSpinBox;
    spbx13=new QSpinBox;
    spbx1->setRange(0,9999); //设置范围
    spbx2->setRange(0,9999);
    spbx3->setRange(0,9999);
    spbx4->setRange(0,9999);
    spbx5->setRange(0,9999);
    spbx6->setRange(0,9999);
    spbx7->setRange(0,9999);
    spbx8->setRange(0,9999);
    spbx9->setRange(0,9999);
    spbx10->setRange(0,9999);
    spbx11->setRange(0,9999);
    spbx12->setRange(0,9999);
    spbx13->setRange(0,9999);
    gl->addWidget(spbx1,1,1,1,1);
    gl->addWidget(spbx2,2,1,1,1);
    gl->addWidget(spbx3,3,1,1,1);
    gl->addWidget(spbx4,4,1,1,1);
    gl->addWidget(spbx5,5,1,1,1);
    gl->addWidget(spbx6,6,1,1,1);
    gl->addWidget(spbx7,7,1,1,1);
    gl->addWidget(spbx8,8,1,1,1);
    gl->addWidget(spbx9,9,1,1,1);
    gl->addWidget(spbx10,10,1,1,1);
    gl->addWidget(spbx11,11,1,1,1);
    gl->addWidget(spbx12,12,1,1,1);
    gl->addWidget(spbx13,13,1,1,1);

    spby1=new QSpinBox;
    spby2=new QSpinBox;
    spby3=new QSpinBox;
    spby4=new QSpinBox;
    spby5=new QSpinBox;
    spby6=new QSpinBox;
    spby7=new QSpinBox;
    spby8=new QSpinBox;
    spby9=new QSpinBox;
    spby10=new QSpinBox;
    spby11=new QSpinBox;
    spby12=new QSpinBox;
    spby13=new QSpinBox;
    spby1->setRange(0,9999);
    spby2->setRange(0,9999);
    spby3->setRange(0,9999);
    spby4->setRange(0,9999);
    spby5->setRange(0,9999);
    spby6->setRange(0,9999);
    spby7->setRange(0,9999);
    spby8->setRange(0,9999);
    spby9->setRange(0,9999);
    spby10->setRange(0,9999);
    spby11->setRange(0,9999);
    spby12->setRange(0,9999);
    spby13->setRange(0,9999);
    gl->addWidget(spby1,1,2,1,1);
    gl->addWidget(spby2,2,2,1,1);
    gl->addWidget(spby3,3,2,1,1);
    gl->addWidget(spby4,4,2,1,1);
    gl->addWidget(spby5,5,2,1,1);
    gl->addWidget(spby6,6,2,1,1);
    gl->addWidget(spby7,7,2,1,1);
    gl->addWidget(spby8,8,2,1,1);
    gl->addWidget(spby9,9,2,1,1);
    gl->addWidget(spby10,10,2,1,1);
    gl->addWidget(spby11,11,2,1,1);
    gl->addWidget(spby12,12,2,1,1);
    gl->addWidget(spby13,13,2,1,1);

//    QPushButton *btn1=new QPushButton;
//    btn1->setText("确定");
//    QPushButton *btn2=new QPushButton;
//    btn2->setText("确定");
//    QPushButton *btn3=new QPushButton;
//    btn3->setText("确定");
//    QPushButton *btn4=new QPushButton;
//    btn4->setText("确定");
//    QPushButton *btn5=new QPushButton;
//    btn5->setText("确定");
//    QPushButton *btn6=new QPushButton;
//    btn6->setText("确定");
//    QPushButton *btn7=new QPushButton;
//    btn7->setText("确定");
//    QPushButton *btn8=new QPushButton;
//    btn8->setText("确定");
//    QPushButton *btn9=new QPushButton;
//    btn9->setText("确定");
//    QPushButton *btn10=new QPushButton;
//    btn10->setText("确定");
//    QPushButton *btn11=new QPushButton;
//    btn11->setText("确定");
//    QPushButton *btn12=new QPushButton;
//    btn12->setText("确定");
//    QPushButton *btn13=new QPushButton;
//    btn13->setText("确定");
//    gl->addWidget(btn1,1,3,1,1);
//    gl->addWidget(btn2,2,3,1,1);
//    gl->addWidget(btn3,3,3,1,1);
//    gl->addWidget(btn4,4,3,1,1);
//    gl->addWidget(btn5,5,3,1,1);
//    gl->addWidget(btn6,6,3,1,1);
//    gl->addWidget(btn7,7,3,1,1);
//    gl->addWidget(btn8,8,3,1,1);
//    gl->addWidget(btn9,9,3,1,1);
//    gl->addWidget(btn10,10,3,1,1);
//    gl->addWidget(btn11,11,3,1,1);
//    gl->addWidget(btn12,12,3,1,1);
//    gl->addWidget(btn13,13,3,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    //v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(change3,SIGNAL(activated(int)),this,SLOT(tosersor_continue(int)));
    connect(lineEdit_continueRadio,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot()));
    connect(lineEdit_continueResolution2,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot()));
//    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(btn_continue1_Slot()));
//    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(btn_continue2_Slot()));
//    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(btn_continue3_Slot()));
//    connect(btn4,SIGNAL(clicked(bool)),this,SLOT(btn_continue4_Slot()));
//    connect(btn5,SIGNAL(clicked(bool)),this,SLOT(btn_continue5_Slot()));
//    connect(btn6,SIGNAL(clicked(bool)),this,SLOT(btn_continue6_Slot()));
//    connect(btn7,SIGNAL(clicked(bool)),this,SLOT(btn_continue7_Slot()));
//    connect(btn8,SIGNAL(clicked(bool)),this,SLOT(btn_continue8_Slot()));
//    connect(btn9,SIGNAL(clicked(bool)),this,SLOT(btn_continue9_Slot()));
//    connect(btn10,SIGNAL(clicked(bool)),this,SLOT(btn_continue10_Slot()));
//    connect(btn11,SIGNAL(clicked(bool)),this,SLOT(btn_continue11_Slot()));
//    connect(btn12,SIGNAL(clicked(bool)),this,SLOT(btn_continue12_Slot()));
//    connect(btn13,SIGNAL(clicked(bool)),this,SLOT(btn_continue13_Slot()));

    w_ContinueField->setLayout(v);
    w_ContinueField->resize(300,500);
    w_ContinueField->show();
}



void MainWindow::tosersor_fix(int i)
{
    if(i==0){
    }else if(i==1){
        w_sersor1->close();
        btnSensor1SwitchSlot();

       }else if(i==2){
        w_sersor1->close();
        btnSensor2ContinueSlot();
       }

}


void MainWindow::toSensor_switch(int i)
{
   if(i==1){
       w_seitchField->close();
       showCamera();

   }else if(i==2){
       w_seitchField->close();;
       btnSensor2ContinueSlot();
   }
}

void MainWindow::tosersor_continue(int i)
{
    if(i==1){
        w_ContinueField->close();
        showCamera();
    }else if(i==2){
        w_ContinueField->close();
        btnSensor1SwitchSlot();
    }
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

    btn_serial_OK=new QPushButton;
    btn_serial_OK->setText("确定");
    btn_serial_NO=new QPushButton;
    btn_serial_NO->setText("取消");
    QHBoxLayout *hLayoutBtn=new QHBoxLayout;
    hLayoutBtn->addWidget(btn_serial_OK);
    hLayoutBtn->addWidget(btn_serial_NO);

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
    mainlayout4->addLayout(hLayoutBtn);

    connect(btn_serial_OK,SIGNAL(clicked(bool)),this,SLOT(btnToSerial()));
    connect(btn_serial_NO,SIGNAL(clicked(bool)),this,SLOT(btnToClose()));

    w_config_serial.setLayout(mainlayout4);

    w_config_serial.show();
}

void MainWindow::btnNetSlot()
{
    w_config_net.setWindowTitle(tr("网络配置"));
    lineEdit_port = new QLineEdit();
    lineEdit_ip = new QLineEdit();
    lineEdit_ip->setInputMask("000.000.000.000");

    btn_net_OK=new QPushButton;
    btn_net_OK->setText("确定");
    btn_net_NO=new QPushButton;
    btn_net_NO->setText("取消");
    QHBoxLayout *hLayoutBtn=new QHBoxLayout;
    hLayoutBtn->addWidget(btn_net_OK);
    hLayoutBtn->addWidget(btn_net_NO);

    QFormLayout *pLayout_socket = new QFormLayout();
    pLayout_socket->addRow(QStringLiteral("IP："), lineEdit_ip);
    pLayout_socket->addRow(QStringLiteral("端口："), lineEdit_port);

    QVBoxLayout *socket_layout2 = new QVBoxLayout;
    socket_layout2->addLayout(pLayout_socket);
    socket_layout2->addLayout(hLayoutBtn);

    connect(btn_net_OK,SIGNAL(clicked(bool)),this,SLOT(btnToNet()));
    connect(btn_net_NO,SIGNAL(clicked(bool)),this,SLOT(btnToClose()));


    w_config_net.setLayout(socket_layout2);

    w_config_net.show();
}

void MainWindow::toNetSlot(int i)
{
     s->setCurrentIndex(i);
}
