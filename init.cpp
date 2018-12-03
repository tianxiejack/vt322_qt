#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::init_menu()
{
    menu[0]=new QMenu("配置");
    QAction* act_sysCfg=new QAction("系统配置");
    menu[0]->addAction(act_sysCfg);
    QAction* act_platCfg=new QAction("平台配置");
    menu[0]->addAction(act_platCfg);

    QMenu* cameracfg=new QMenu("相机配置");
    QAction* act_cmrCfg1=new QAction("通道1");
    QAction* act_cmrCfg2=new QAction("通道2");
    QAction* act_cmrCfg3=new QAction("通道3");
    QAction* act_cmrCfg4=new QAction("通道4");
    QAction* act_cmrCfg5=new QAction("通道5");
    cameracfg->addAction(act_cmrCfg1);
    cameracfg->addAction(act_cmrCfg2);
    cameracfg->addAction(act_cmrCfg3);
    cameracfg->addAction(act_cmrCfg4);
    cameracfg->addAction(act_cmrCfg5);
    menu[0]->addMenu(cameracfg);

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

    QMenu* capture=new QMenu("波门配置");
    QAction* act_cap1=new QAction("捕获框");
    //capture->addAction(act_cap1);
    QAction* act_cap2=new QAction("波门");
    capture->addAction(act_cap2);
    QAction* act_cap3=new QAction("画线");
    capture->addAction(act_cap3);
    menu[0]->addMenu(capture);

     QAction* dbg_sysCfg=new QAction("捕获配置");
     menu[0]->addAction(dbg_sysCfg);

     QAction* speedconv_sysCfg=new QAction("转换表配置");
     menu[0]->addAction(speedconv_sysCfg);

     QAction* mtd_sysCfg=new QAction("移动检测配置");
     menu[0]->addAction(mtd_sysCfg);

    QAction* act_rstCfg=new QAction("恢复默认");
    menu[0]->addAction(act_rstCfg);

    ui->menuBar->addMenu(menu[0]);

    connect(act_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showSysCfg()));
    connect(act_platCfg,SIGNAL(triggered(bool)),this,SLOT(showPlat()));
    connect(act_cmrCfg1,SIGNAL(triggered(bool)),this,SLOT(showCamera()));
    connect(act_cmrCfg2,SIGNAL(triggered(bool)),this,SLOT(showCamera_sec()));
    connect(act_cmrCfg3,SIGNAL(triggered(bool)),this,SLOT(showCamera_thi()));
    connect(act_cmrCfg4,SIGNAL(triggered(bool)),this,SLOT(showCamera_fou()));
    connect(act_cmrCfg5,SIGNAL(triggered(bool)),this,SLOT(showCamera_fif()));
    connect(act_algCfg1,SIGNAL(triggered(bool)),this,SLOT(showAlg()));
    connect(act_algCfg2,SIGNAL(triggered(bool)),this,SLOT(showAlg2()));
    connect(act_algCfg3,SIGNAL(triggered(bool)),this,SLOT(showAlg3()));
    connect(act_othCfg,SIGNAL(triggered(bool)),this,SLOT(showOther()));
    connect(act_cap1,SIGNAL(triggered(bool)),this,SLOT(showCapture1()));
    connect(act_cap2,SIGNAL(triggered(bool)),this,SLOT(showCapture2()));
    connect(act_cap3,SIGNAL(triggered(bool)),this,SLOT(showCapture3()));
    connect(act_rstCfg,SIGNAL(triggered(bool)),this,SLOT(resetAction()));
    connect(dbg_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showdbgcfg()));
    connect(speedconv_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg()));
    connect(mtd_sysCfg,SIGNAL(triggered(bool)),this,SLOT(showmtdcfg()));
}

void MainWindow::init_sysCfg()
{
    w_config=new QWidget;
    w_config_serial=new QWidget;
    w_config_net=new QWidget;
    w_config->setWindowTitle(tr("系统配置"));
    checkBox_channel1=new QCheckBox;
    checkBox_channel2=new QCheckBox;
    checkBox_channel3=new QCheckBox;
    checkBox_channel4=new QCheckBox;
    checkBox_channel5=new QCheckBox;
    checkBox_channel1->setText("1");
    checkBox_channel2->setText("2");
    checkBox_channel3->setText("3");
    checkBox_channel4->setText("4");
    checkBox_channel5->setText("5");
    checkBox_channel1->setCheckState(Qt::Checked);
    checkBox_channel2->setCheckState(Qt::Checked);
    checkBox_channel3->setCheckState(Qt::Checked);
    checkBox_channel4->setCheckState(Qt::Checked);
    checkBox_channel5->setCheckState(Qt::Checked);
    QHBoxLayout *hsensor=new QHBoxLayout;
    hsensor->addWidget(checkBox_channel1);
    hsensor->addWidget(checkBox_channel2);
    hsensor->addWidget(checkBox_channel3);
    hsensor->addWidget(checkBox_channel4);
    hsensor->addWidget(checkBox_channel5);
    //lineEdit=new QLineEdit;
    /*
    box1=new QComboBox;
    box1->addItem("1");
    box1->addItem("2");
    box1->addItem("3");
    box1->addItem("4");
    box1->addItem("5");
    */
	QPushButton *btn_choose=new QPushButton;
    btn_choose->setText("打开分辨率选择");

    QPushButton *btnDown=new QPushButton;
    btnDown->setText("导入");
    QPushButton *btnUp=new QPushButton;
    btnUp->setText("导出");

    QPushButton *btnSave=new QPushButton;
    btnSave->setText("保存");

    QGroupBox *groupBox_upgrade = new QGroupBox();
    groupBox_upgrade->setTitle("文件传输");
    upgrade_ip = new QLineEdit();
    upgrade_ip->setInputMask("000.000.000.000");
    upgrade_ip->setText("192.168.0.188");
    upgrade_port = new QLineEdit();
    upgrade_port->setText("8999");
    QPushButton *btnUpdate=new QPushButton();
    btnUpdate->setText("升级");
    QPushButton *btnFPGA=new QPushButton();
    btnFPGA->setText("升级");
    upgrade_show = new QTextEdit();

    /*QComboBox *CBox=new QComboBox;
    CBox->addItem("最慢");
    CBox->addItem("低中");
    CBox->addItem("高中");
    CBox->addItem("最高");
    CBox->setCurrentIndex(1);*/

    QLineEdit *editsw = new QLineEdit();
    QPushButton *btnselectsw=new QPushButton();
    btnselectsw->setText("选择文件");
    QLineEdit *editfpga = new QLineEdit();
    QPushButton *btnselectfpga=new QPushButton();
    btnselectfpga->setText("选择文件");
    QLineEdit *editimportconf = new QLineEdit();
    QPushButton *btnselectimportconf=new QPushButton();
    btnselectimportconf->setText("选择文件");

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(editsw);
    hlayout1->addWidget(btnselectsw);
    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(editfpga);
    hlayout2->addWidget(btnselectfpga);
    QHBoxLayout *hlayout3 = new QHBoxLayout;
    hlayout3->addWidget(editimportconf);
    hlayout3->addWidget(btnselectimportconf);

    QVBoxLayout *vlayout1 = new QVBoxLayout();
    vlayout1->addLayout(hlayout1);
    vlayout1->addWidget(btnUpdate);
    QVBoxLayout *vlayout2 = new QVBoxLayout();
    vlayout2->addLayout(hlayout2);
    vlayout2->addWidget(btnFPGA);
    QVBoxLayout *vlayout3 = new QVBoxLayout();
    vlayout3->addLayout(hlayout3);
    vlayout3->addWidget(btnDown);

    QFormLayout *pLayout = new QFormLayout;
    //pLayout->addRow(QStringLiteral("水平速度"), lineEdit);
    pLayout->addRow("有效视频源：", hsensor);
    //pLayout->addRow("相机通道选择", box1);
    pLayout->addRow("各通道采集\n分辨率选择",btn_choose);
    //pLayout->addRow("变焦速度等级", CBox);
    pLayout->addRow("保存当前配置", btnSave);
    //pLayout->addRow("IP：",upgrade_ip);
    //pLayout->addRow("端口：",upgrade_port);
    //pLayout->addRow("软件升级",btnUpdate);
    //pLayout->addRow("FPGA升级", btnFPGA);
    //pLayout->addRow("导入配置文件", btnDown);
    pLayout->addRow("软件升级",vlayout1);
    pLayout->addRow("FPGA升级", vlayout2);
    pLayout->addRow("导入配置文件", vlayout3);
    pLayout->addRow("导出配置文件", btnUp);
    pLayout->addRow(upgrade_show);

    //connect(lineEdit,SIGNAL(returnPressed()),this,SLOT(lEdt_sysCfg_Slot()));
    //connect(box1,SIGNAL(activated(int)),SLOT(CBox_sysCfg_Slot(int)));
	connect(btn_choose,SIGNAL(clicked(bool)),SLOT(btn_choose_Slot()));
    connect(btnDown,SIGNAL(clicked(bool)),this,SLOT(btnDownSlot()));
    connect(btnUp,SIGNAL(clicked(bool)),this,SLOT(btnUpSlot()));
    connect(btnSave,SIGNAL(clicked(bool)),this,SLOT(btnSaveSlot())); 
    connect(btnUpdate,SIGNAL(clicked(bool)),this,SLOT(btnUpdate()));
    connect(btnFPGA,SIGNAL(clicked(bool)),this,SLOT(btnFPGA_clicked()));
    //connect(CBox,SIGNAL(activated(int)),this,SLOT(CBox_View_Slot(int)));
    connect(checkBox_channel1,SIGNAL(stateChanged(int)),this,SLOT(checkBox_channel_Slot(int)));
    connect(checkBox_channel2,SIGNAL(stateChanged(int)),this,SLOT(checkBox_channel_Slot(int)));
    connect(checkBox_channel3,SIGNAL(stateChanged(int)),this,SLOT(checkBox_channel_Slot(int)));
    connect(checkBox_channel4,SIGNAL(stateChanged(int)),this,SLOT(checkBox_channel_Slot(int)));
    connect(checkBox_channel5,SIGNAL(stateChanged(int)),this,SLOT(checkBox_channel_Slot(int)));

    w_config->setLayout(pLayout);
}
void MainWindow::init_platCfg()
{
    w_plat=new MyWidget;
    w_plat->setWindowTitle("平台配置");
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
    josPoint_lineEdt2=new QLineEdit;
    josInputG_x2=new QLineEdit;
    josInputG_y2=new QLineEdit;
//    josOutputG_x=new QLineEdit;
//    josOutputG_y=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(jos_s[0],josDead_lineEdt);
    f1->addRow(jos_s[1],josPoint_lineEdt);
    f1->addRow(jos_s[2],josInputG_x);
    f1->addRow(jos_s[3],josInputG_y);
    f1->addRow(jos_s[4],josPoint_lineEdt2);
    f1->addRow(jos_s[5],josInputG_x2);
    f1->addRow(jos_s[6],josInputG_y2);
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
    connect(josPoint_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos5_Slot()));
    connect(josInputG_x2,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos6_Slot()));
    connect(josInputG_y2,SIGNAL(returnPressed()),this,SLOT(lEdt_Jos7_Slot()));
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

    connect(mx_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat3_Slot()));
    connect(my_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat4_Slot()));
    connect(deadx_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat5_Slot()));
    connect(deady_plat,SIGNAL(returnPressed()),SLOT(lEdt_plat6_Slot()));
    connect(a_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat7_Slot()));
   // connect(outMode,SIGNAL(activated(int)),this,SLOT(outMode_Slot(int)));
}
void MainWindow::init_dbCfg()
{
    w_dbg=new MyWidget;
    w_dbg->setWindowTitle("捕获配置");
    bleedx_plat=new QLineEdit;
    bleedy_plat=new QLineEdit;
    kx_lineEdt=new QLineEdit;
    ky_lineEdt=new QLineEdit;
    errx_lineEdt=new QLineEdit;
    erry_lineEdt=new QLineEdit;
    time_lineEdt=new QLineEdit;
    dbg5_lineEdt=new QLineEdit;
    dbg6_lineEdt=new QLineEdit;
    dbg7_lineEdt=new QLineEdit;
    dbg8_lineEdt=new QLineEdit;
    dbg9_lineEdt=new QLineEdit;
    dbg10_lineEdt=new QLineEdit;
    dbg11_lineEdt=new QLineEdit;
    dbg12_lineEdt=new QLineEdit;
    dbg13_lineEdt=new QLineEdit;
    dbg14_lineEdt=new QLineEdit;
    dbg15_lineEdt=new QLineEdit;

    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s[0],kx_lineEdt);
    f3->addRow(dbg_s[1],ky_lineEdt);
    f3->addRow(dbg_s[2],errx_lineEdt);
    f3->addRow(dbg_s[3],erry_lineEdt);
    f3->addRow(dbg_s[4],time_lineEdt);
    f3->addRow(plat_s[0],bleedx_plat);
    f3->addRow(plat_s[1],bleedy_plat);
    /*
    f3->addRow(dbg_s[5],dbg5_lineEdt);
    f3->addRow(dbg_s[6],dbg6_lineEdt);
    f3->addRow(dbg_s[7],dbg7_lineEdt);
    f3->addRow(dbg_s[8],dbg8_lineEdt);
    f3->addRow(dbg_s[9],dbg9_lineEdt);
    f3->addRow(dbg_s[10],dbg10_lineEdt);
    f3->addRow(dbg_s[11],dbg11_lineEdt);
    f3->addRow(dbg_s[12],dbg12_lineEdt);
    f3->addRow(dbg_s[13],dbg13_lineEdt);
    f3->addRow(dbg_s[14],dbg14_lineEdt);
    f3->addRow(dbg_s[15],dbg15_lineEdt);
    */
    w_dbg->setLayout(f3);
    connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
    connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(kx_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot()));
    connect(ky_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot()));
    connect(errx_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot()));
    connect(erry_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot()));
    connect(time_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot()));
    /*
    connect(dbg5_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg5_Slot()));
    connect(dbg6_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg6_Slot()));
    connect(dbg7_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg7_Slot()));
    connect(dbg8_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg8_Slot()));
    connect(dbg9_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg9_Slot()));
    connect(dbg10_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg10_Slot()));
    connect(dbg11_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg11_Slot()));
    connect(dbg12_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg12_Slot()));
    connect(dbg13_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg13_Slot()));
    connect(dbg14_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg14_Slot()));
    connect(dbg15_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_dbg15_Slot()));
    */

}
void MainWindow::init_speedconvCfg()
{
    w_speedconv=new MyWidget;
    w_speedconv->setWindowTitle("转换表配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("转换表参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_speedx=new QGroupBox();
    gbox_speedx->setTitle("x轴");
    speedx1_lineEdt=new QLineEdit;
    speedx2_lineEdt=new QLineEdit;
    speedx3_lineEdt=new QLineEdit;
    speedx4_lineEdt=new QLineEdit;
    speedx5_lineEdt=new QLineEdit;
    speedx6_lineEdt=new QLineEdit;
    speedx7_lineEdt=new QLineEdit;
    speedx8_lineEdt=new QLineEdit;
    speedx9_lineEdt=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(speed_s[0],speedx1_lineEdt);
    f1->addRow(speed_s[1],speedx2_lineEdt);
    f1->addRow(speed_s[2],speedx3_lineEdt);
    f1->addRow(speed_s[3],speedx4_lineEdt);
    f1->addRow(speed_s[4],speedx5_lineEdt);
    f1->addRow(speed_s[5],speedx6_lineEdt);
    f1->addRow(speed_s[6],speedx7_lineEdt);
    f1->addRow(speed_s[7],speedx8_lineEdt);
    f1->addRow(speed_s[8],speedx9_lineEdt);
    gbox_speedx->setLayout(f1);

    gbox_speedy=new QGroupBox();
    gbox_speedy->setTitle("y轴");
    speedy1_lineEdt=new QLineEdit;
    speedy2_lineEdt=new QLineEdit;
    speedy3_lineEdt=new QLineEdit;
    speedy4_lineEdt=new QLineEdit;
    speedy5_lineEdt=new QLineEdit;
    speedy6_lineEdt=new QLineEdit;
    speedy7_lineEdt=new QLineEdit;
    speedy8_lineEdt=new QLineEdit;
    speedy9_lineEdt=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(speed_s[0],speedy1_lineEdt);
    f2->addRow(speed_s[1],speedy2_lineEdt);
    f2->addRow(speed_s[2],speedy3_lineEdt);
    f2->addRow(speed_s[3],speedy4_lineEdt);
    f2->addRow(speed_s[4],speedy5_lineEdt);
    f2->addRow(speed_s[5],speedy6_lineEdt);
    f2->addRow(speed_s[6],speedy7_lineEdt);
    f2->addRow(speed_s[7],speedy8_lineEdt);
    f2->addRow(speed_s[8],speedy9_lineEdt);
    gbox_speedy->setLayout(f2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_speedx);
    v->addWidget(gbox_speedy);
    w_speedconv->setLayout(v);

    connect(btn_speed_default,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Default_Slot()));
    connect(btn_speed_update,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Update_Slot()));
    connect(speedx1_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx1_Slot()));
    connect(speedx2_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx2_Slot()));
    connect(speedx3_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx3_Slot()));
    connect(speedx4_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx4_Slot()));
    connect(speedx5_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx5_Slot()));
    connect(speedx6_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx6_Slot()));
    connect(speedx7_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx7_Slot()));
    connect(speedx8_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx8_Slot()));
    connect(speedx9_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx9_Slot()));
    connect(speedy1_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot()));
    connect(speedy2_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot()));
    connect(speedy3_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot()));
    connect(speedy4_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot()));
    connect(speedy5_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot()));
    connect(speedy6_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot()));
    connect(speedy7_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot()));
    connect(speedy8_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot()));
    connect(speedy9_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot()));

}

void MainWindow::init_mtdCfg()
{
    w_mtd=new MyWidget;
    w_mtd->setWindowTitle("移动检测参数设置");

    btn_mtd_default=new QPushButton;
    btn_mtd_update=new QPushButton;
    btn_mtd_default->setText("默认");
    btn_mtd_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_mtd_default);
    v1->addWidget(btn_mtd_update);
    QLabel *label=new QLabel;
    label->setText("移动检测参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    rigion=new QLineEdit;
    maxnum=new QLineEdit;
    uspeed=new QLineEdit;
    maxpix=new QLineEdit;
    minpix=new QLineEdit;
    sensitive=new QLineEdit;
    dspeed=new QLineEdit;
    trktime=new QLineEdit;
    output = new QComboBox;
    output->addItem("使能");
    output->addItem("禁止");
    polar=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(mtd_s[0],rigion);
    f1->addRow(mtd_s[1],maxnum);
    f1->addRow(mtd_s[2],uspeed);
    f1->addRow(mtd_s[3],maxpix);
    f1->addRow(mtd_s[4],minpix);
    f1->addRow(mtd_s[5],sensitive);
    f1->addRow(mtd_s[6],dspeed);
    f1->addRow(mtd_s[7],trktime);
    f1->addRow(mtd_s[8],output);
    f1->addRow(mtd_s[9],polar);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    w_mtd->setLayout(v);
}

void MainWindow::init_utcCfg()
{
    utc1=new MyWidget;
    utc2=new MyWidget;
    utc3=new MyWidget;
    utc1->setWindowTitle("UTC1参数配置");
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

    QVBoxLayout *v11=new QVBoxLayout;
    v11->addLayout(h1);
    v11->addLayout(f);

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
    utc1->setLayout(v11);

    utc2->setWindowTitle("UTC2参数配置");
    btn_utc2_default=new QPushButton;
    btn_utc2_update=new QPushButton;
    btn_utc2_default->setText("默认");
    btn_utc2_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_utc2_default);
    v2->addWidget(btn_utc2_update);
    QLabel *label2=new QLabel;
    label2->setText("UTC2参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

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
    QFormLayout *f2=new QFormLayout();
    f2->addRow(utc_s2[0],utc2_l0);
    f2->addRow(utc_s2[1],utc2_l1);
    f2->addRow(utc_s2[2],utc2_l2);
    f2->addRow(utc_s2[3],utc2_l3);
    f2->addRow(utc_s2[4],utc2_l4);
    f2->addRow(utc_s2[5],utc2_l5);
    f2->addRow(utc_s2[6],utc2_l6);
    f2->addRow(utc_s2[7],utc2_l7);
    f2->addRow(utc_s2[8],utc2_l8);
    f2->addRow(utc_s2[9],utc2_l9);
    f2->addRow(utc_s2[10],utc2_l10);
    f2->addRow(utc_s2[11],utc2_l11);
    f2->addRow(utc_s2[12],utc2_l12);
    f2->addRow(utc_s2[13],utc2_l13);
    f2->addRow(utc_s2[14],utc2_l14);
    f2->addRow(utc_s2[15],utc2_l15);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);

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
    utc2->setLayout(v22);

    utc3->setWindowTitle("UTC3参数配置");
    btn_utc3_default=new QPushButton;
    btn_utc3_update=new QPushButton;
    btn_utc3_default->setText("默认");
    btn_utc3_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_utc3_default);
    v3->addWidget(btn_utc3_update);
    QLabel *label3=new QLabel;
    label3->setText("UTC1参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

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
    QFormLayout *f3=new QFormLayout();
    f3->addRow(utc_s3[0],utc3_l0);
    f3->addRow(utc_s3[1],utc3_l1);
    f3->addRow(utc_s3[2],utc3_l2);
    f3->addRow(utc_s3[3],utc3_l3);
    f3->addRow(utc_s3[4],utc3_l4);
    f3->addRow(utc_s3[5],utc3_l5);
    f3->addRow(utc_s3[6],utc3_l6);
    f3->addRow(utc_s3[7],utc3_l7);
    f3->addRow(utc_s3[8],utc3_l8);
    f3->addRow(utc_s3[9],utc3_l9);
    f3->addRow(utc_s3[10],utc3_l10);
    f3->addRow(utc_s3[11],utc3_l11);
    f3->addRow(utc_s3[12],utc3_l12);
    f3->addRow(utc_s3[13],utc3_l13);
    f3->addRow(utc_s3[14],utc3_l14);
    f3->addRow(utc_s3[15],utc3_l15);

    QVBoxLayout *v33=new QVBoxLayout;
    v33->addLayout(h3);
    v33->addLayout(f3);

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

    utc3->setLayout(v33);
}
void MainWindow::init_captureCfg()
{
    w_capture1=new MyWidget;
    w_capture2=new MyWidget;
    w_capture3=new MyWidget;
    w_capture1->setWindowTitle("捕获框参数设置");
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
    connect(cap_0_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_0()));
    connect(cap_1_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_1()));
    connect(cap_2_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_2()));
    connect(cap_3_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_3()));
    connect(cap_4_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_4()));
    connect(cap_5_w,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_5()));
    connect(cap_0_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_6()));
    connect(cap_1_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_7()));
    connect(cap_2_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_8()));
    connect(cap_3_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_9()));
    connect(cap_4_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_10()));
    connect(cap_5_h,SIGNAL(returnPressed()),this,SLOT(lEdt_capture_11()));
    w_capture1->setLayout(h);

    w_capture2->setWindowTitle("波门参数设置");
    btn_capture2_default=new QPushButton;
    btn_capture2_update=new QPushButton;
    btn_capture2_default->setText("默认");
    btn_capture2_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_capture2_default);
    v2->addWidget(btn_capture2_update);
    QLabel *label2=new QLabel;
    label2->setText("波门参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

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

    autobomen_checkbox = new QCheckBox;
    autobomen_checkbox->setText("自动波门");

    QGroupBox *bomen=new QGroupBox;
    QFormLayout *f2=new QFormLayout();
    f2->addRow(string_bomen[0],bomen_0_w);
    f2->addRow(string_bomen[5],bomen_0_h);
    f2->addRow(string_bomen[1],bomen_1_w);
    f2->addRow(string_bomen[6],bomen_1_h);
    f2->addRow(string_bomen[2],bomen_2_w);
    f2->addRow(string_bomen[7],bomen_2_h);
    f2->addRow(string_bomen[3],bomen_3_w);
    f2->addRow(string_bomen[8],bomen_3_h);
    f2->addRow(string_bomen[4],bomen_4_w);
    f2->addRow(string_bomen[9],bomen_4_h);

    bomen->setTitle("波门");
    bomen->setLayout(f2);

    QVBoxLayout *h22=new QVBoxLayout;
    h22->addLayout(h2);
    h22->addWidget(autobomen_checkbox);
    h22->addWidget(bomen);

    connect(btn_capture2_default,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_default_SLot()));
    connect(btn_capture2_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));

    connect(autobomen_checkbox,SIGNAL(stateChanged(int)),this,SLOT(callback_autobomen(int)));
    connect(bomen_0_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_0()));
    connect(bomen_1_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_1()));
    connect(bomen_2_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_2()));
    connect(bomen_3_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_3()));
    connect(bomen_4_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_4()));
    connect(bomen_5_w,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_5()));
    connect(bomen_0_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_6()));
    connect(bomen_1_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_7()));
    connect(bomen_2_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_8()));
    connect(bomen_3_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_9()));
    connect(bomen_4_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_10()));
    connect(bomen_5_h,SIGNAL(returnPressed()),this,SLOT(lEdt_bomen_11()));
    w_capture2->setLayout(h22);

    w_capture3->setWindowTitle("画线参数设置");
    btn_capture3_default=new QPushButton;
    btn_capture3_update=new QPushButton;
    btn_capture3_default->setText("默认");
    btn_capture3_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_capture3_default);
    v3->addWidget(btn_capture3_update);
    QLabel *label3=new QLabel;
    label3->setText("画线参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);
    QGroupBox *drawLine=new QGroupBox;
    drawLine->setTitle("画线");
    drawLine_1=new QLineEdit;
    drawLine_2=new QLineEdit;
    drawLine_3=new QLineEdit;
    drawLine_4=new QLineEdit;
    drawLine_5=new QLineEdit;
    checkBox_cross=new QCheckBox;
    QFormLayout *f3=new QFormLayout();
    f3->addRow("显示",checkBox_cross);
    //f3->addRow(string_drawLine[0],drawLine_0);
    //f3->addRow(string_drawLine[1],drawLine_1);
    //f3->addRow(string_drawLine[2],drawLine_2);
    //f3->addRow(string_drawLine[3],drawLine_3);
    //f3->addRow(string_drawLine[4],drawLine_4);
    //f3->addRow(string_drawLine[5],drawLine_5);
    drawLine->setLayout(f3);

    QVBoxLayout *h33=new QVBoxLayout;
    h33->addLayout(h3);
    h33->addWidget(drawLine);

    connect(btn_capture3_default,SIGNAL(clicked(bool)),this,SLOT(btn_capture3_default_Slot()));
    connect(btn_capture3_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture3_update_Slot()));
    connect(drawLine_1,SIGNAL(returnPressed()),this,SLOT(lEdt_drawLine_1()));
    connect(drawLine_2,SIGNAL(returnPressed()),this,SLOT(lEdt_drawLine_2()));
    connect(drawLine_3,SIGNAL(returnPressed()),this,SLOT(lEdt_drawLine_3()));
    connect(drawLine_4,SIGNAL(returnPressed()),this,SLOT(lEdt_drawLine_4()));
    connect(drawLine_5,SIGNAL(returnPressed()),this,SLOT(lEdt_drawLine_5()));
    connect(checkBox_cross,SIGNAL(stateChanged(int)),this,SLOT(checkBox_cross_Slot(int)));

    w_capture3->setLayout(h33);
}
void MainWindow::init_OSDCfg()
{
    w_osd1=new MyWidget;
    c=new QComboBox;
    checkBox=new QCheckBox;
    osd1_pos_x=new QLineEdit;
    osd1_pos_y=new QLineEdit;
    osd1_lineEdit_label=new QLineEdit;
    osd1_lineEdit_context=new QLineEdit;
    CBox_color=new QComboBox;

    btn_osd1_default=new QPushButton;
    btn_osd1_update=new QPushButton;
    btn_osd1_default->setText("默认");
    btn_osd1_update->setText("设置");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_osd1_default);
    v1->addWidget(btn_osd1_update);
    QLabel *label=new QLabel;
    label->setText("OSD参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    CBox_font=new QComboBox;
    CBox_font->addItem("宋体");
    CBox_font->addItem("黑体");
    CBox_font_size=new QComboBox;
    CBox_font_size->addItem("小");
    CBox_font_size->addItem("中");
    CBox_font_size->addItem("大");
    QFormLayout *pLayout = new QFormLayout;
    pLayout->addRow("OSD字体配置", CBox_font);
    pLayout->addRow("OSD字号配置", CBox_font_size);

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


    QFormLayout *f=new QFormLayout();
    f->addRow(osd_s[0],checkBox);
    f->addRow(osd_s[1],osd1_pos_x);
    f->addRow(osd_s[2],osd1_pos_y);
    //f->addRow(osd_s[3],osd1_lineEdit_label);
    f->addRow(osd_s[4],osd1_lineEdit_context);

    f->addRow(osd_s[7],CBox_color);
    f->addRow(osd_s[8],osd1_lineEdit_transparency);

    //connect(c,SIGNAL(activated(int)),this,SLOT(toCBox(int)));

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(pLayout);
    v->addWidget(c);
    v->addLayout(f);

    connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(btn_osd_default_Slot()));
    connect(btn_osd1_update,SIGNAL(clicked(bool)),this,SLOT(btn_osd_update_Slot()));
    connect(c,SIGNAL(activated(int)),this,SLOT(CBox_osd_choose_Slot(int)));
    connect(CBox_font,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_Slot(int)));
    connect(CBox_font_size,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_size_Slot(int)));
    // connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(checkBox_Slot(int)));
   // connect(osd1_pos_x,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_x_Slot()));
    //connect(osd1_pos_y,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_y_Slot()));
   // connect(osd1_lineEdit_context,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_context_Slot()));

   // connect(CBox_color,SIGNAL(activated(int)),this,SLOT(CBox_osd_color_Slot(int)));
    //connect(osd1_lineEdit_transparency,SIGNAL(returnPressed()),this,SLOT(lEdt_)))
    w_osd1->setLayout(v);
}

void MainWindow::init_cameraCfg()
{
    w_sersor1=new MyWidget;
    w_seitchField=new MyWidget;
    w_ContinueField=new MyWidget;

    w_sersor1->setWindowTitle("通道1固定视场");
    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道1固定视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
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

    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");

    lEdt=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    sp=new QSpinBox;
    sp2=new QSpinBox;
    sp->setRange(0,9999);
    sp2->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l11,0,0,1,1);
    gl->addWidget(l14,0,1,1,1);
    gl->addWidget(l14,0,2,1,1);
    gl->addWidget(l12,0,3,1,1);
    gl->addWidget(l13,0,4,1,1);
    gl->addWidget(l14,0,5,1,1);
    gl->addWidget(lEdt,1,0,1,1);
    gl->addWidget(l1d,1,1,1,1);
    gl->addWidget(l14,1,2,1,1);
    gl->addWidget(sp,1,3,1,1);
    gl->addWidget(sp2,1,4,1,1);

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

    w_seitchField->setWindowTitle("通道1可切换视场");
    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_s1Switch_default);
    v2->addWidget(btn_s1Switch_update);
    QLabel *label2=new QLabel;
    label2->setText("通道1可切换视场参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

    change2=new QComboBox;
    change2->addItem("可切换视场");
    change2->addItem("固定视场");
    change2->addItem("连续视场");
    lineEdit_switchRadio=new QLineEdit;

    lineEdit_switchResolution=new QLineEdit;
    lineEdit_switchResolution2=new QLineEdit;
    lineEdit_switchResolution->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2->setValidator(new QIntValidator(100,10000,this));
    QLabel *l222=new  QLabel;
    l222->setText("*");
    QHBoxLayout *sensor_Resolution2=new QHBoxLayout;
    sensor_Resolution2->addWidget(lineEdit_switchResolution);
    sensor_Resolution2->addWidget(l222);
    sensor_Resolution2->addWidget(lineEdit_switchResolution2);

    fovclass = new QComboBox;
    fovclass->addItem("可切换视场1");
    fovclass->addItem("可切换视场2");
    fovclass->addItem("可切换视场3");
    fovclass->addItem("可切换视场4");
    fovclass->addItem("可切换视场5");

    QFormLayout *f2=new QFormLayout;
    f2->addRow(sensor_s1[0],change2);
    f2->addRow(sensor_s1[1],lineEdit_switchRadio);
    f2->addRow(sensor_s1[2],sensor_Resolution2);
    f2->addRow("测试视场等级",fovclass);

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");

    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l22,0,3,1,1);
    gl2->addWidget(l23,0,4,1,1);
    gl2->addWidget(l24,0,5,1,1);

    QLabel *fovclass_label1 = new QLabel;
    QLabel *fovclass_label2 = new QLabel;
    QLabel *fovclass_label3 = new QLabel;
    QLabel *fovclass_label4 = new QLabel;
    QLabel *fovclass_label5 = new QLabel;
    fovclass_label1->setText("可切换视场1");
    fovclass_label2->setText("可切换视场2");
    fovclass_label3->setText("可切换视场3");
    fovclass_label4->setText("可切换视场4");
    fovclass_label5->setText("可切换视场5");
    gl2->addWidget(fovclass_label1,1,0,1,1);
    gl2->addWidget(fovclass_label2,2,0,1,1);
    gl2->addWidget(fovclass_label3,3,0,1,1);
    gl2->addWidget(fovclass_label4,4,0,1,1);
    gl2->addWidget(fovclass_label5,5,0,1,1);
    lineEdit_s1_Fov0=new QLineEdit;
    lineEdit_s1_Fov1=new QLineEdit;
    lineEdit_s1_Fov2=new QLineEdit;
    lineEdit_s1_Fov3=new QLineEdit;
    lineEdit_s1_Fov4=new QLineEdit;
    gl2->addWidget(lineEdit_s1_Fov0,1,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov1,2,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov2,3,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov3,4,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov4,5,1,1,1);

    QLabel* l1d21=new QLabel;
    QLabel* l1d22=new QLabel;
    QLabel* l1d23=new QLabel;
    QLabel* l1d24=new QLabel;
    QLabel* l1d25=new QLabel;
    l1d21->setText("度");
    l1d22->setText("度");
    l1d23->setText("度");
    l1d24->setText("度");
    l1d25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);


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
    gl2->addWidget(spbx_switch1,1,3,1,1);
    gl2->addWidget(spbx_switch2,2,3,1,1);
    gl2->addWidget(spbx_switch3,3,3,1,1);
    gl2->addWidget(spbx_switch4,4,3,1,1);
    gl2->addWidget(spbx_switch5,5,3,1,1);

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
    gl2->addWidget(spby_switch1,1,4,1,1);
    gl2->addWidget(spby_switch2,2,4,1,1);
    gl2->addWidget(spby_switch3,3,4,1,1);
    gl2->addWidget(spby_switch4,4,4,1,1);
    gl2->addWidget(spby_switch5,5,4,1,1);

//    QPushButton *btn21=new QPushButton;
//    btn21->setText("确定");
//    QPushButton *btn22=new QPushButton;
//    btn22->setText("确定");
//    QPushButton *btn23=new QPushButton;
//    btn23->setText("确定");
//    QPushButton *btn24=new QPushButton;
//    btn24->setText("确定");
//    QPushButton *btn25=new QPushButton;
//    btn25->setText("确定");
//    gl2->addWidget(btn21,1,3,1,1);
//    gl2->addWidget(btn22,2,3,1,1);
//    gl2->addWidget(btn23,3,3,1,1);
//    gl2->addWidget(btn24,4,3,1,1);
//    gl2->addWidget(btn25,5,3,1,1);

   g2->setLayout(gl2);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);
    v22->addWidget(g2);

    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(change2,SIGNAL(activated(int)),this,SLOT(toSensor_switch(int)));
    connect(lineEdit_switchRadio,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot()));
    connect(lineEdit_switchResolution2,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot()));
//    connect(btn1,SIGNAL(clicked(bool)),this,SLOT(btn_switch1_Slot()));
//    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(btn_switch2_Slot()));
//    connect(btn3,SIGNAL(clicked(bool)),this,SLOT(btn_switch3_Slot()));
//    connect(btn4,SIGNAL(clicked(bool)),this,SLOT(btn_switch4_Slot()));
//    connect(btn5,SIGNAL(clicked(bool)),this,SLOT(btn_switch5_Slot()));
    w_seitchField->setLayout(v22);
    w_seitchField->resize(300,200);

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_continue_default);
    v3->addWidget(btn_continue_update);
    QLabel *label3=new QLabel;
    label3->setText("通道1连续视场参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

    change3=new QComboBox;
    change3->addItem("连续视场");
    change3->addItem("固定视场");
    change3->addItem("可切换视场");

    lineEdit_continueRadio=new QLineEdit;
    lineEdit_continueResolution=new QLineEdit;
    lineEdit_continueResolution2=new QLineEdit;
    lineEdit_continueResolution->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2->setValidator(new QIntValidator(100,10000,this));
    QLabel *l3=new  QLabel;
    l3->setText("*");
    QHBoxLayout *sensor_Resolution3=new QHBoxLayout;
    sensor_Resolution3->addWidget(lineEdit_continueResolution);

    sensor_Resolution3->addWidget(l3);
    sensor_Resolution3->addWidget(lineEdit_continueResolution2);

    testfov = new QLineEdit;
    QFormLayout *f3=new QFormLayout;
    f3->addRow(sensor_s1[0],change3);
    f3->addRow(sensor_s1[1],lineEdit_continueRadio);
    f3->addRow(sensor_s1[2],sensor_Resolution3);
    f3->addRow("测试视场",testfov);

    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");

    QGridLayout *gl3=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的\n   反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    gl3->addWidget(l30,0,0,1,1);
    gl3->addWidget(l31,0,1,1,1);
    gl3->addWidget(l32,0,3,1,1);
    gl3->addWidget(l33,0,4,1,1);
    gl3->addWidget(l34,0,5,1,1);

    fEdt1=new QLineEdit;
    fEdt2=new QLineEdit;
    fEdt3=new QLineEdit;
    fEdt4=new QLineEdit;
    fEdt5=new QLineEdit;
    fEdt6=new QLineEdit;
    fEdt7=new QLineEdit;
    fEdt8=new QLineEdit;
    fEdt9=new QLineEdit;
    fEdt10=new QLineEdit;
    fEdt11=new QLineEdit;
    fEdt12=new QLineEdit;
    fEdt13=new QLineEdit;
    gl3->addWidget(fEdt1,1,0,1,1);
    gl3->addWidget(fEdt2,2,0,1,1);
    gl3->addWidget(fEdt3,3,0,1,1);
    gl3->addWidget(fEdt4,4,0,1,1);
    gl3->addWidget(fEdt5,5,0,1,1);
    gl3->addWidget(fEdt6,6,0,1,1);
    gl3->addWidget(fEdt7,7,0,1,1);
    gl3->addWidget(fEdt8,8,0,1,1);
    gl3->addWidget(fEdt9,9,0,1,1);
    gl3->addWidget(fEdt10,10,0,1,1);
    gl3->addWidget(fEdt11,11,0,1,1);
    gl3->addWidget(fEdt12,12,0,1,1);
    gl3->addWidget(fEdt13,13,0,1,1);

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
    gl3->addWidget(lEdt1,1,1,1,1);
    gl3->addWidget(lEdt2,2,1,1,1);
    gl3->addWidget(lEdt3,3,1,1,1);
    gl3->addWidget(lEdt4,4,1,1,1);
    gl3->addWidget(lEdt5,5,1,1,1);
    gl3->addWidget(lEdt6,6,1,1,1);
    gl3->addWidget(lEdt7,7,1,1,1);
    gl3->addWidget(lEdt8,8,1,1,1);
    gl3->addWidget(lEdt9,9,1,1,1);
    gl3->addWidget(lEdt10,10,1,1,1);
    gl3->addWidget(lEdt11,11,1,1,1);
    gl3->addWidget(lEdt12,12,1,1,1);
    gl3->addWidget(lEdt13,13,1,1,1);

    QLabel* l1d3_1=new QLabel;
    QLabel* l1d3_2=new QLabel;
    QLabel* l1d3_3=new QLabel;
    QLabel* l1d3_4=new QLabel;
    QLabel* l1d3_5=new QLabel;
    QLabel* l1d3_6=new QLabel;
    QLabel* l1d3_7=new QLabel;
    QLabel* l1d3_8=new QLabel;
    QLabel* l1d3_9=new QLabel;
    QLabel* l1d3_10=new QLabel;
    QLabel* l1d3_11=new QLabel;
    QLabel* l1d3_12=new QLabel;
    QLabel* l1d3_13=new QLabel;
    l1d3_1->setText("度");
    l1d3_2->setText("度");
    l1d3_3->setText("度");
    l1d3_4->setText("度");
    l1d3_5->setText("度");
    l1d3_6->setText("度");
    l1d3_7->setText("度");
    l1d3_8->setText("度");
    l1d3_9->setText("度");
    l1d3_10->setText("度");
    l1d3_11->setText("度");
    l1d3_12->setText("度");
    l1d3_13->setText("度");
    gl3->addWidget(l1d3_1,1,2,1,1);
    gl3->addWidget(l1d3_2,2,2,1,1);
    gl3->addWidget(l1d3_3,3,2,1,1);
    gl3->addWidget(l1d3_4,4,2,1,1);
    gl3->addWidget(l1d3_5,5,2,1,1);
    gl3->addWidget(l1d3_6,6,2,1,1);
    gl3->addWidget(l1d3_7,7,2,1,1);
    gl3->addWidget(l1d3_8,8,2,1,1);
    gl3->addWidget(l1d3_9,9,2,1,1);
    gl3->addWidget(l1d3_10,10,2,1,1);
    gl3->addWidget(l1d3_11,11,2,1,1);
    gl3->addWidget(l1d3_12,12,2,1,1);
    gl3->addWidget(l1d3_13,13,2,1,1);

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
    gl3->addWidget(spbx1,1,3,1,1);
    gl3->addWidget(spbx2,2,3,1,1);
    gl3->addWidget(spbx3,3,3,1,1);
    gl3->addWidget(spbx4,4,3,1,1);
    gl3->addWidget(spbx5,5,3,1,1);
    gl3->addWidget(spbx6,6,3,1,1);
    gl3->addWidget(spbx7,7,3,1,1);
    gl3->addWidget(spbx8,8,3,1,1);
    gl3->addWidget(spbx9,9,3,1,1);
    gl3->addWidget(spbx10,10,3,1,1);
    gl3->addWidget(spbx11,11,3,1,1);
    gl3->addWidget(spbx12,12,3,1,1);
    gl3->addWidget(spbx13,13,3,1,1);

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
    gl3->addWidget(spby1,1,4,1,1);
    gl3->addWidget(spby2,2,4,1,1);
    gl3->addWidget(spby3,3,4,1,1);
    gl3->addWidget(spby4,4,4,1,1);
    gl3->addWidget(spby5,5,4,1,1);
    gl3->addWidget(spby6,6,4,1,1);
    gl3->addWidget(spby7,7,4,1,1);
    gl3->addWidget(spby8,8,4,1,1);
    gl3->addWidget(spby9,9,4,1,1);
    gl3->addWidget(spby10,10,4,1,1);
    gl3->addWidget(spby11,11,4,1,1);
    gl3->addWidget(spby12,12,4,1,1);
    gl3->addWidget(spby13,13,4,1,1);

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

    g3->setLayout(gl3);

    QVBoxLayout *v3b=new QVBoxLayout;
    v3b->addLayout(h3);
    v3b->addLayout(f3);
    v3b->addWidget(g3);

    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
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

    w_ContinueField->setLayout(v3b);
    w_ContinueField->resize(300,500);
    w_ContinueField->setWindowTitle("通道1连续视场");
}

void MainWindow::init_cameraCfg_sec()
{
    w_sersor1_sec=new MyWidget;
    w_seitchField_sec=new MyWidget;
    w_ContinueField_sec=new MyWidget;

    w_sersor1_sec->setWindowTitle("通道2固定视场");
    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道2固定视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    change1_sec=new QComboBox;
    change1_sec->addItem("固定视场");
    change1_sec->addItem("可切换视场");
    change1_sec->addItem("连续视场");

    lineEdit_fieldRadio_sec=new QLineEdit;
    QLabel *l=new  QLabel;
    l->setText("*");
    lineEdit_fieldResolution_sec=new QLineEdit;
    lineEdit_fieldResolution2_sec=new QLineEdit;

    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_fieldResolution_sec);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_fieldResolution2_sec);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1_sec[0],change1_sec);
    f1->addRow(sensor_s1_sec[1],lineEdit_fieldRadio_sec);
    f1->addRow(sensor_s1_sec[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");

    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");

    lEdt_sec=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    sp_sec=new QSpinBox;
    sp2_sec=new QSpinBox;
    sp_sec->setRange(0,9999);
    sp2_sec->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l11,0,0,1,1);
    gl->addWidget(l14,0,1,1,1);
    gl->addWidget(l14,0,2,1,1);
    gl->addWidget(l12,0,3,1,1);
    gl->addWidget(l13,0,4,1,1);
    gl->addWidget(l14,0,5,1,1);
    gl->addWidget(lEdt_sec,1,0,1,1);
    gl->addWidget(l1d,1,1,1,1);
    gl->addWidget(l14,1,2,1,1);
    gl->addWidget(sp_sec,1,3,1,1);
    gl->addWidget(sp2_sec,1,4,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(change1_sec,SIGNAL(activated(int)),this,SLOT(tosersor_fix_sec(int)));
/*
    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_sec()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_sec()));
    connect(lineEdit_fieldRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot_sec()));
    connect(lineEdit_fieldResolution_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot_sec()));
    connect(lineEdit_fieldResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot_sec()));
    connect(lEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot_sec()));
    connect(sp_sec,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot_sec(int)));
    connect(sp2_sec,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot_sec(int)));
*/
    w_sersor1_sec->setLayout(v);
    w_sersor1_sec->resize(300,200);

    w_seitchField_sec->setWindowTitle("通道2可切换视场");
    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_s1Switch_default);
    v2->addWidget(btn_s1Switch_update);
    QLabel *label2=new QLabel;
    label2->setText("通道2可切换视场参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

    change2_sec=new QComboBox;
    change2_sec->addItem("可切换视场");
    change2_sec->addItem("固定视场");
    change2_sec->addItem("连续视场");
    lineEdit_switchRadio_sec=new QLineEdit;

    lineEdit_switchResolution_sec=new QLineEdit;
    lineEdit_switchResolution2_sec=new QLineEdit;
    lineEdit_switchResolution_sec->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2_sec->setValidator(new QIntValidator(100,10000,this));
    QLabel *l222=new  QLabel;
    l222->setText("*");
    QHBoxLayout *sensor_Resolution2=new QHBoxLayout;
    sensor_Resolution2->addWidget(lineEdit_switchResolution_sec);
    sensor_Resolution2->addWidget(l222);
    sensor_Resolution2->addWidget(lineEdit_switchResolution2_sec);

    fovclass_sec = new QComboBox;
    fovclass_sec->addItem("可切换视场1");
    fovclass_sec->addItem("可切换视场2");
    fovclass_sec->addItem("可切换视场3");
    fovclass_sec->addItem("可切换视场4");
    fovclass_sec->addItem("可切换视场5");

    QFormLayout *f2=new QFormLayout;
    f2->addRow(sensor_s1_sec[0],change2_sec);
    f2->addRow(sensor_s1_sec[1],lineEdit_switchRadio_sec);
    f2->addRow(sensor_s1_sec[2],sensor_Resolution2);
    f2->addRow("测试视场等级",fovclass_sec);

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");

    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l22,0,3,1,1);
    gl2->addWidget(l23,0,4,1,1);
    gl2->addWidget(l24,0,5,1,1);

    QLabel *fovclass_label1 = new QLabel;
    QLabel *fovclass_label2 = new QLabel;
    QLabel *fovclass_label3 = new QLabel;
    QLabel *fovclass_label4 = new QLabel;
    QLabel *fovclass_label5 = new QLabel;
    fovclass_label1->setText("可切换视场1");
    fovclass_label2->setText("可切换视场2");
    fovclass_label3->setText("可切换视场3");
    fovclass_label4->setText("可切换视场4");
    fovclass_label5->setText("可切换视场5");
    gl2->addWidget(fovclass_label1,1,0,1,1);
    gl2->addWidget(fovclass_label2,2,0,1,1);
    gl2->addWidget(fovclass_label3,3,0,1,1);
    gl2->addWidget(fovclass_label4,4,0,1,1);
    gl2->addWidget(fovclass_label5,5,0,1,1);
    lineEdit_s1_Fov0_sec=new QLineEdit;
    lineEdit_s1_Fov1_sec=new QLineEdit;
    lineEdit_s1_Fov2_sec=new QLineEdit;
    lineEdit_s1_Fov3_sec=new QLineEdit;
    lineEdit_s1_Fov4_sec=new QLineEdit;
    gl2->addWidget(lineEdit_s1_Fov0_sec,1,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov1_sec,2,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov2_sec,3,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov3_sec,4,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov4_sec,5,1,1,1);

    QLabel* l1d21=new QLabel;
    QLabel* l1d22=new QLabel;
    QLabel* l1d23=new QLabel;
    QLabel* l1d24=new QLabel;
    QLabel* l1d25=new QLabel;
    l1d21->setText("度");
    l1d22->setText("度");
    l1d23->setText("度");
    l1d24->setText("度");
    l1d25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    spbx_switch1_sec=new QSpinBox;
    spbx_switch2_sec=new QSpinBox;
    spbx_switch3_sec=new QSpinBox;
    spbx_switch4_sec=new QSpinBox;
    spbx_switch5_sec=new QSpinBox;
    spbx_switch1_sec->setRange(0,9999);
    spbx_switch2_sec->setRange(0,9999);
    spbx_switch3_sec->setRange(0,9999);
    spbx_switch4_sec->setRange(0,9999);
    spbx_switch5_sec->setRange(0,9999);
    gl2->addWidget(spbx_switch1_sec,1,3,1,1);
    gl2->addWidget(spbx_switch2_sec,2,3,1,1);
    gl2->addWidget(spbx_switch3_sec,3,3,1,1);
    gl2->addWidget(spbx_switch4_sec,4,3,1,1);
    gl2->addWidget(spbx_switch5_sec,5,3,1,1);

    spby_switch1_sec=new QSpinBox;
    spby_switch2_sec=new QSpinBox;
    spby_switch3_sec=new QSpinBox;
    spby_switch4_sec=new QSpinBox;
    spby_switch5_sec=new QSpinBox;
    spby_switch1_sec->setRange(0,9999);
    spby_switch2_sec->setRange(0,9999);
    spby_switch3_sec->setRange(0,9999);
    spby_switch4_sec->setRange(0,9999);
    spby_switch5_sec->setRange(0,9999);
    gl2->addWidget(spby_switch1_sec,1,4,1,1);
    gl2->addWidget(spby_switch2_sec,2,4,1,1);
    gl2->addWidget(spby_switch3_sec,3,4,1,1);
    gl2->addWidget(spby_switch4_sec,4,4,1,1);
    gl2->addWidget(spby_switch5_sec,5,4,1,1);

    g2->setLayout(gl2);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);
    v22->addWidget(g2);

    connect(change2_sec,SIGNAL(activated(int)),this,SLOT(toSensor_switch_sec(int)));
/*
    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_sec()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_sec()));
    connect(lineEdit_switchRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot_sec()));
    connect(lineEdit_switchResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot_sec()));
*/
    w_seitchField_sec->setLayout(v22);
    w_seitchField_sec->resize(300,200);

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_continue_default);
    v3->addWidget(btn_continue_update);
    QLabel *label3=new QLabel;
    label3->setText("通道2连续视场参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

    change3_sec=new QComboBox;
    change3_sec->addItem("连续视场");
    change3_sec->addItem("固定视场");
    change3_sec->addItem("可切换视场");

    lineEdit_continueRadio_sec=new QLineEdit;
    lineEdit_continueResolution_sec=new QLineEdit;
    lineEdit_continueResolution2_sec=new QLineEdit;
    lineEdit_continueResolution_sec->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2_sec->setValidator(new QIntValidator(100,10000,this));
    QLabel *l3=new  QLabel;
    l3->setText("*");
    QHBoxLayout *sensor_Resolution3=new QHBoxLayout;
    sensor_Resolution3->addWidget(lineEdit_continueResolution_sec);

    sensor_Resolution3->addWidget(l3);
    sensor_Resolution3->addWidget(lineEdit_continueResolution2_sec);

    testfov_sec = new QLineEdit;
    QFormLayout *f3=new QFormLayout;
    f3->addRow(sensor_s1_sec[0],change3_sec);
    f3->addRow(sensor_s1_sec[1],lineEdit_continueRadio_sec);
    f3->addRow(sensor_s1_sec[2],sensor_Resolution3);
    f3->addRow("测试视场",testfov_sec);

    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");

    QGridLayout *gl3=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的\n   反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    gl3->addWidget(l30,0,0,1,1);
    gl3->addWidget(l31,0,1,1,1);
    gl3->addWidget(l32,0,3,1,1);
    gl3->addWidget(l33,0,4,1,1);
    gl3->addWidget(l34,0,5,1,1);

    fEdt1_sec=new QLineEdit;
    fEdt2_sec=new QLineEdit;
    fEdt3_sec=new QLineEdit;
    fEdt4_sec=new QLineEdit;
    fEdt5_sec=new QLineEdit;
    fEdt6_sec=new QLineEdit;
    fEdt7_sec=new QLineEdit;
    fEdt8_sec=new QLineEdit;
    fEdt9_sec=new QLineEdit;
    fEdt10_sec=new QLineEdit;
    fEdt11_sec=new QLineEdit;
    fEdt12_sec=new QLineEdit;
    fEdt13_sec=new QLineEdit;
    gl3->addWidget(fEdt1_sec,1,0,1,1);
    gl3->addWidget(fEdt2_sec,2,0,1,1);
    gl3->addWidget(fEdt3_sec,3,0,1,1);
    gl3->addWidget(fEdt4_sec,4,0,1,1);
    gl3->addWidget(fEdt5_sec,5,0,1,1);
    gl3->addWidget(fEdt6_sec,6,0,1,1);
    gl3->addWidget(fEdt7_sec,7,0,1,1);
    gl3->addWidget(fEdt8_sec,8,0,1,1);
    gl3->addWidget(fEdt9_sec,9,0,1,1);
    gl3->addWidget(fEdt10_sec,10,0,1,1);
    gl3->addWidget(fEdt11_sec,11,0,1,1);
    gl3->addWidget(fEdt12_sec,12,0,1,1);
    gl3->addWidget(fEdt13_sec,13,0,1,1);

    lEdt1_sec=new QLineEdit;
    lEdt2_sec=new QLineEdit;
    lEdt3_sec=new QLineEdit;
    lEdt4_sec=new QLineEdit;
    lEdt5_sec=new QLineEdit;
    lEdt6_sec=new QLineEdit;
    lEdt7_sec=new QLineEdit;
    lEdt8_sec=new QLineEdit;
    lEdt9_sec=new QLineEdit;
    lEdt10_sec=new QLineEdit;
    lEdt11_sec=new QLineEdit;
    lEdt12_sec=new QLineEdit;
    lEdt13_sec=new QLineEdit;
    gl3->addWidget(lEdt1_sec,1,1,1,1);
    gl3->addWidget(lEdt2_sec,2,1,1,1);
    gl3->addWidget(lEdt3_sec,3,1,1,1);
    gl3->addWidget(lEdt4_sec,4,1,1,1);
    gl3->addWidget(lEdt5_sec,5,1,1,1);
    gl3->addWidget(lEdt6_sec,6,1,1,1);
    gl3->addWidget(lEdt7_sec,7,1,1,1);
    gl3->addWidget(lEdt8_sec,8,1,1,1);
    gl3->addWidget(lEdt9_sec,9,1,1,1);
    gl3->addWidget(lEdt10_sec,10,1,1,1);
    gl3->addWidget(lEdt11_sec,11,1,1,1);
    gl3->addWidget(lEdt12_sec,12,1,1,1);
    gl3->addWidget(lEdt13_sec,13,1,1,1);

    QLabel* l1d3_1=new QLabel;
    QLabel* l1d3_2=new QLabel;
    QLabel* l1d3_3=new QLabel;
    QLabel* l1d3_4=new QLabel;
    QLabel* l1d3_5=new QLabel;
    QLabel* l1d3_6=new QLabel;
    QLabel* l1d3_7=new QLabel;
    QLabel* l1d3_8=new QLabel;
    QLabel* l1d3_9=new QLabel;
    QLabel* l1d3_10=new QLabel;
    QLabel* l1d3_11=new QLabel;
    QLabel* l1d3_12=new QLabel;
    QLabel* l1d3_13=new QLabel;
    l1d3_1->setText("度");
    l1d3_2->setText("度");
    l1d3_3->setText("度");
    l1d3_4->setText("度");
    l1d3_5->setText("度");
    l1d3_6->setText("度");
    l1d3_7->setText("度");
    l1d3_8->setText("度");
    l1d3_9->setText("度");
    l1d3_10->setText("度");
    l1d3_11->setText("度");
    l1d3_12->setText("度");
    l1d3_13->setText("度");
    gl3->addWidget(l1d3_1,1,2,1,1);
    gl3->addWidget(l1d3_2,2,2,1,1);
    gl3->addWidget(l1d3_3,3,2,1,1);
    gl3->addWidget(l1d3_4,4,2,1,1);
    gl3->addWidget(l1d3_5,5,2,1,1);
    gl3->addWidget(l1d3_6,6,2,1,1);
    gl3->addWidget(l1d3_7,7,2,1,1);
    gl3->addWidget(l1d3_8,8,2,1,1);
    gl3->addWidget(l1d3_9,9,2,1,1);
    gl3->addWidget(l1d3_10,10,2,1,1);
    gl3->addWidget(l1d3_11,11,2,1,1);
    gl3->addWidget(l1d3_12,12,2,1,1);
    gl3->addWidget(l1d3_13,13,2,1,1);

    spbx1_sec=new QSpinBox;
    spbx2_sec=new QSpinBox;
    spbx3_sec=new QSpinBox;
    spbx4_sec=new QSpinBox;
    spbx5_sec=new QSpinBox;
    spbx6_sec=new QSpinBox;
    spbx7_sec=new QSpinBox;
    spbx8_sec=new QSpinBox;
    spbx9_sec=new QSpinBox;
    spbx10_sec=new QSpinBox;
    spbx11_sec=new QSpinBox;
    spbx12_sec=new QSpinBox;
    spbx13_sec=new QSpinBox;
    spbx1_sec->setRange(0,9999); //设置范围
    spbx2_sec->setRange(0,9999);
    spbx3_sec->setRange(0,9999);
    spbx4_sec->setRange(0,9999);
    spbx5_sec->setRange(0,9999);
    spbx6_sec->setRange(0,9999);
    spbx7_sec->setRange(0,9999);
    spbx8_sec->setRange(0,9999);
    spbx9_sec->setRange(0,9999);
    spbx10_sec->setRange(0,9999);
    spbx11_sec->setRange(0,9999);
    spbx12_sec->setRange(0,9999);
    spbx13_sec->setRange(0,9999);
    gl3->addWidget(spbx1_sec,1,3,1,1);
    gl3->addWidget(spbx2_sec,2,3,1,1);
    gl3->addWidget(spbx3_sec,3,3,1,1);
    gl3->addWidget(spbx4_sec,4,3,1,1);
    gl3->addWidget(spbx5_sec,5,3,1,1);
    gl3->addWidget(spbx6_sec,6,3,1,1);
    gl3->addWidget(spbx7_sec,7,3,1,1);
    gl3->addWidget(spbx8_sec,8,3,1,1);
    gl3->addWidget(spbx9_sec,9,3,1,1);
    gl3->addWidget(spbx10_sec,10,3,1,1);
    gl3->addWidget(spbx11_sec,11,3,1,1);
    gl3->addWidget(spbx12_sec,12,3,1,1);
    gl3->addWidget(spbx13_sec,13,3,1,1);

    spby1_sec=new QSpinBox;
    spby2_sec=new QSpinBox;
    spby3_sec=new QSpinBox;
    spby4_sec=new QSpinBox;
    spby5_sec=new QSpinBox;
    spby6_sec=new QSpinBox;
    spby7_sec=new QSpinBox;
    spby8_sec=new QSpinBox;
    spby9_sec=new QSpinBox;
    spby10_sec=new QSpinBox;
    spby11_sec=new QSpinBox;
    spby12_sec=new QSpinBox;
    spby13_sec=new QSpinBox;
    spby1_sec->setRange(0,9999);
    spby2_sec->setRange(0,9999);
    spby3_sec->setRange(0,9999);
    spby4_sec->setRange(0,9999);
    spby5_sec->setRange(0,9999);
    spby6_sec->setRange(0,9999);
    spby7_sec->setRange(0,9999);
    spby8_sec->setRange(0,9999);
    spby9_sec->setRange(0,9999);
    spby10_sec->setRange(0,9999);
    spby11_sec->setRange(0,9999);
    spby12_sec->setRange(0,9999);
    spby13_sec->setRange(0,9999);
    gl3->addWidget(spby1_sec,1,4,1,1);
    gl3->addWidget(spby2_sec,2,4,1,1);
    gl3->addWidget(spby3_sec,3,4,1,1);
    gl3->addWidget(spby4_sec,4,4,1,1);
    gl3->addWidget(spby5_sec,5,4,1,1);
    gl3->addWidget(spby6_sec,6,4,1,1);
    gl3->addWidget(spby7_sec,7,4,1,1);
    gl3->addWidget(spby8_sec,8,4,1,1);
    gl3->addWidget(spby9_sec,9,4,1,1);
    gl3->addWidget(spby10_sec,10,4,1,1);
    gl3->addWidget(spby11_sec,11,4,1,1);
    gl3->addWidget(spby12_sec,12,4,1,1);
    gl3->addWidget(spby13_sec,13,4,1,1);

    g3->setLayout(gl3);

    QVBoxLayout *v3b=new QVBoxLayout;
    v3b->addLayout(h3);
    v3b->addLayout(f3);
    v3b->addWidget(g3);

    connect(change3_sec,SIGNAL(activated(int)),this,SLOT(tosersor_continue_sec(int)));
/*
    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_sec()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_sec()));
    connect(lineEdit_continueRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot_sec()));
    connect(lineEdit_continueResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot_sec()));
*/
    w_ContinueField_sec->setLayout(v3b);
    w_ContinueField_sec->resize(300,500);
    w_ContinueField_sec->setWindowTitle("通道2连续视场");
}

void MainWindow::init_cameraCfg_thi()
{
    w_sersor1_thi=new MyWidget;
    w_seitchField_thi=new MyWidget;
    w_ContinueField_thi=new MyWidget;

    w_sersor1_thi->setWindowTitle("通道3固定视场");
    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道3固定视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    change1_thi=new QComboBox;
    change1_thi->addItem("固定视场");
    change1_thi->addItem("可切换视场");
    change1_thi->addItem("连续视场");

    lineEdit_fieldRadio_thi=new QLineEdit;
    QLabel *l=new  QLabel;
    l->setText("*");
    lineEdit_fieldResolution_thi=new QLineEdit;
    lineEdit_fieldResolution2_thi=new QLineEdit;

    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_fieldResolution_thi);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_fieldResolution2_thi);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1_thi[0],change1_thi);
    f1->addRow(sensor_s1_thi[1],lineEdit_fieldRadio_thi);
    f1->addRow(sensor_s1_thi[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");

    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");

    lEdt_thi=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    sp_thi=new QSpinBox;
    sp2_thi=new QSpinBox;
    sp_thi->setRange(0,9999);
    sp2_thi->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l11,0,0,1,1);
    gl->addWidget(l14,0,1,1,1);
    gl->addWidget(l14,0,2,1,1);
    gl->addWidget(l12,0,3,1,1);
    gl->addWidget(l13,0,4,1,1);
    gl->addWidget(l14,0,5,1,1);
    gl->addWidget(lEdt_thi,1,0,1,1);
    gl->addWidget(l1d,1,1,1,1);
    gl->addWidget(l14,1,2,1,1);
    gl->addWidget(sp_thi,1,3,1,1);
    gl->addWidget(sp2_thi,1,4,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(change1_thi,SIGNAL(activated(int)),this,SLOT(tosersor_fix_thi(int)));
/*
    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_thi()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_thi()));
    connect(lineEdit_fieldRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot_thi()));
    connect(lineEdit_fieldResolution_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot_thi()));
    connect(lineEdit_fieldResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot_thi()));
    connect(lEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot_thi()));
    connect(sp_thi,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot_thi(int)));
    connect(sp2_thi,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot_thi(int)));
*/
    w_sersor1_thi->setLayout(v);
    w_sersor1_thi->resize(300,200);

    w_seitchField_thi->setWindowTitle("通道3可切换视场");
    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_s1Switch_default);
    v2->addWidget(btn_s1Switch_update);
    QLabel *label2=new QLabel;
    label2->setText("通道3可切换视场参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

    change2_thi=new QComboBox;
    change2_thi->addItem("可切换视场");
    change2_thi->addItem("固定视场");
    change2_thi->addItem("连续视场");
    lineEdit_switchRadio_thi=new QLineEdit;

    lineEdit_switchResolution_thi=new QLineEdit;
    lineEdit_switchResolution2_thi=new QLineEdit;
    lineEdit_switchResolution_thi->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2_thi->setValidator(new QIntValidator(100,10000,this));
    QLabel *l222=new  QLabel;
    l222->setText("*");
    QHBoxLayout *sensor_Resolution2=new QHBoxLayout;
    sensor_Resolution2->addWidget(lineEdit_switchResolution_thi);
    sensor_Resolution2->addWidget(l222);
    sensor_Resolution2->addWidget(lineEdit_switchResolution2_thi);

    fovclass_thi = new QComboBox;
    fovclass_thi->addItem("可切换视场1");
    fovclass_thi->addItem("可切换视场2");
    fovclass_thi->addItem("可切换视场3");
    fovclass_thi->addItem("可切换视场4");
    fovclass_thi->addItem("可切换视场5");

    QFormLayout *f2=new QFormLayout;
    f2->addRow(sensor_s1_thi[0],change2_thi);
    f2->addRow(sensor_s1_thi[1],lineEdit_switchRadio_thi);
    f2->addRow(sensor_s1_thi[2],sensor_Resolution2);
    f2->addRow("测试视场等级",fovclass_thi);

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");

    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l22,0,3,1,1);
    gl2->addWidget(l23,0,4,1,1);
    gl2->addWidget(l24,0,5,1,1);

    QLabel *fovclass_label1 = new QLabel;
    QLabel *fovclass_label2 = new QLabel;
    QLabel *fovclass_label3 = new QLabel;
    QLabel *fovclass_label4 = new QLabel;
    QLabel *fovclass_label5 = new QLabel;
    fovclass_label1->setText("可切换视场1");
    fovclass_label2->setText("可切换视场2");
    fovclass_label3->setText("可切换视场3");
    fovclass_label4->setText("可切换视场4");
    fovclass_label5->setText("可切换视场5");
    gl2->addWidget(fovclass_label1,1,0,1,1);
    gl2->addWidget(fovclass_label2,2,0,1,1);
    gl2->addWidget(fovclass_label3,3,0,1,1);
    gl2->addWidget(fovclass_label4,4,0,1,1);
    gl2->addWidget(fovclass_label5,5,0,1,1);
    lineEdit_s1_Fov0_thi=new QLineEdit;
    lineEdit_s1_Fov1_thi=new QLineEdit;
    lineEdit_s1_Fov2_thi=new QLineEdit;
    lineEdit_s1_Fov3_thi=new QLineEdit;
    lineEdit_s1_Fov4_thi=new QLineEdit;
    gl2->addWidget(lineEdit_s1_Fov0_thi,1,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov1_thi,2,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov2_thi,3,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov3_thi,4,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov4_thi,5,1,1,1);

    QLabel* l1d21=new QLabel;
    QLabel* l1d22=new QLabel;
    QLabel* l1d23=new QLabel;
    QLabel* l1d24=new QLabel;
    QLabel* l1d25=new QLabel;
    l1d21->setText("度");
    l1d22->setText("度");
    l1d23->setText("度");
    l1d24->setText("度");
    l1d25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    spbx_switch1_thi=new QSpinBox;
    spbx_switch2_thi=new QSpinBox;
    spbx_switch3_thi=new QSpinBox;
    spbx_switch4_thi=new QSpinBox;
    spbx_switch5_thi=new QSpinBox;
    spbx_switch1_thi->setRange(0,9999);
    spbx_switch2_thi->setRange(0,9999);
    spbx_switch3_thi->setRange(0,9999);
    spbx_switch4_thi->setRange(0,9999);
    spbx_switch5_thi->setRange(0,9999);
    gl2->addWidget(spbx_switch1_thi,1,3,1,1);
    gl2->addWidget(spbx_switch2_thi,2,3,1,1);
    gl2->addWidget(spbx_switch3_thi,3,3,1,1);
    gl2->addWidget(spbx_switch4_thi,4,3,1,1);
    gl2->addWidget(spbx_switch5_thi,5,3,1,1);

    spby_switch1_thi=new QSpinBox;
    spby_switch2_thi=new QSpinBox;
    spby_switch3_thi=new QSpinBox;
    spby_switch4_thi=new QSpinBox;
    spby_switch5_thi=new QSpinBox;
    spby_switch1_thi->setRange(0,9999);
    spby_switch2_thi->setRange(0,9999);
    spby_switch3_thi->setRange(0,9999);
    spby_switch4_thi->setRange(0,9999);
    spby_switch5_thi->setRange(0,9999);
    gl2->addWidget(spby_switch1_thi,1,4,1,1);
    gl2->addWidget(spby_switch2_thi,2,4,1,1);
    gl2->addWidget(spby_switch3_thi,3,4,1,1);
    gl2->addWidget(spby_switch4_thi,4,4,1,1);
    gl2->addWidget(spby_switch5_thi,5,4,1,1);

    g2->setLayout(gl2);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);
    v22->addWidget(g2);

    connect(change2_thi,SIGNAL(activated(int)),this,SLOT(toSensor_switch_thi(int)));
/*
    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_thi()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_thi()));
    connect(lineEdit_switchRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot_thi()));
    connect(lineEdit_switchResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot_thi()));
*/
    w_seitchField_thi->setLayout(v22);
    w_seitchField_thi->resize(300,200);

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_continue_default);
    v3->addWidget(btn_continue_update);
    QLabel *label3=new QLabel;
    label3->setText("通道3连续视场参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

    change3_thi=new QComboBox;
    change3_thi->addItem("连续视场");
    change3_thi->addItem("固定视场");
    change3_thi->addItem("可切换视场");

    lineEdit_continueRadio_thi=new QLineEdit;
    lineEdit_continueResolution_thi=new QLineEdit;
    lineEdit_continueResolution2_thi=new QLineEdit;
    lineEdit_continueResolution_thi->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2_thi->setValidator(new QIntValidator(100,10000,this));
    QLabel *l3=new  QLabel;
    l3->setText("*");
    QHBoxLayout *sensor_Resolution3=new QHBoxLayout;
    sensor_Resolution3->addWidget(lineEdit_continueResolution_thi);

    sensor_Resolution3->addWidget(l3);
    sensor_Resolution3->addWidget(lineEdit_continueResolution2_thi);

    testfov_thi = new QLineEdit;
    QFormLayout *f3=new QFormLayout;
    f3->addRow(sensor_s1_thi[0],change3_thi);
    f3->addRow(sensor_s1_thi[1],lineEdit_continueRadio_thi);
    f3->addRow(sensor_s1_thi[2],sensor_Resolution3);
    f3->addRow("测试视场",testfov_thi);

    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");

    QGridLayout *gl3=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的\n   反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    gl3->addWidget(l30,0,0,1,1);
    gl3->addWidget(l31,0,1,1,1);
    gl3->addWidget(l32,0,3,1,1);
    gl3->addWidget(l33,0,4,1,1);
    gl3->addWidget(l34,0,5,1,1);

    fEdt1_thi=new QLineEdit;
    fEdt2_thi=new QLineEdit;
    fEdt3_thi=new QLineEdit;
    fEdt4_thi=new QLineEdit;
    fEdt5_thi=new QLineEdit;
    fEdt6_thi=new QLineEdit;
    fEdt7_thi=new QLineEdit;
    fEdt8_thi=new QLineEdit;
    fEdt9_thi=new QLineEdit;
    fEdt10_thi=new QLineEdit;
    fEdt11_thi=new QLineEdit;
    fEdt12_thi=new QLineEdit;
    fEdt13_thi=new QLineEdit;
    gl3->addWidget(fEdt1_thi,1,0,1,1);
    gl3->addWidget(fEdt2_thi,2,0,1,1);
    gl3->addWidget(fEdt3_thi,3,0,1,1);
    gl3->addWidget(fEdt4_thi,4,0,1,1);
    gl3->addWidget(fEdt5_thi,5,0,1,1);
    gl3->addWidget(fEdt6_thi,6,0,1,1);
    gl3->addWidget(fEdt7_thi,7,0,1,1);
    gl3->addWidget(fEdt8_thi,8,0,1,1);
    gl3->addWidget(fEdt9_thi,9,0,1,1);
    gl3->addWidget(fEdt10_thi,10,0,1,1);
    gl3->addWidget(fEdt11_thi,11,0,1,1);
    gl3->addWidget(fEdt12_thi,12,0,1,1);
    gl3->addWidget(fEdt13_thi,13,0,1,1);

    lEdt1_thi=new QLineEdit;
    lEdt2_thi=new QLineEdit;
    lEdt3_thi=new QLineEdit;
    lEdt4_thi=new QLineEdit;
    lEdt5_thi=new QLineEdit;
    lEdt6_thi=new QLineEdit;
    lEdt7_thi=new QLineEdit;
    lEdt8_thi=new QLineEdit;
    lEdt9_thi=new QLineEdit;
    lEdt10_thi=new QLineEdit;
    lEdt11_thi=new QLineEdit;
    lEdt12_thi=new QLineEdit;
    lEdt13_thi=new QLineEdit;
    gl3->addWidget(lEdt1_thi,1,1,1,1);
    gl3->addWidget(lEdt2_thi,2,1,1,1);
    gl3->addWidget(lEdt3_thi,3,1,1,1);
    gl3->addWidget(lEdt4_thi,4,1,1,1);
    gl3->addWidget(lEdt5_thi,5,1,1,1);
    gl3->addWidget(lEdt6_thi,6,1,1,1);
    gl3->addWidget(lEdt7_thi,7,1,1,1);
    gl3->addWidget(lEdt8_thi,8,1,1,1);
    gl3->addWidget(lEdt9_thi,9,1,1,1);
    gl3->addWidget(lEdt10_thi,10,1,1,1);
    gl3->addWidget(lEdt11_thi,11,1,1,1);
    gl3->addWidget(lEdt12_thi,12,1,1,1);
    gl3->addWidget(lEdt13_thi,13,1,1,1);

    QLabel* l1d3_1=new QLabel;
    QLabel* l1d3_2=new QLabel;
    QLabel* l1d3_3=new QLabel;
    QLabel* l1d3_4=new QLabel;
    QLabel* l1d3_5=new QLabel;
    QLabel* l1d3_6=new QLabel;
    QLabel* l1d3_7=new QLabel;
    QLabel* l1d3_8=new QLabel;
    QLabel* l1d3_9=new QLabel;
    QLabel* l1d3_10=new QLabel;
    QLabel* l1d3_11=new QLabel;
    QLabel* l1d3_12=new QLabel;
    QLabel* l1d3_13=new QLabel;
    l1d3_1->setText("度");
    l1d3_2->setText("度");
    l1d3_3->setText("度");
    l1d3_4->setText("度");
    l1d3_5->setText("度");
    l1d3_6->setText("度");
    l1d3_7->setText("度");
    l1d3_8->setText("度");
    l1d3_9->setText("度");
    l1d3_10->setText("度");
    l1d3_11->setText("度");
    l1d3_12->setText("度");
    l1d3_13->setText("度");
    gl3->addWidget(l1d3_1,1,2,1,1);
    gl3->addWidget(l1d3_2,2,2,1,1);
    gl3->addWidget(l1d3_3,3,2,1,1);
    gl3->addWidget(l1d3_4,4,2,1,1);
    gl3->addWidget(l1d3_5,5,2,1,1);
    gl3->addWidget(l1d3_6,6,2,1,1);
    gl3->addWidget(l1d3_7,7,2,1,1);
    gl3->addWidget(l1d3_8,8,2,1,1);
    gl3->addWidget(l1d3_9,9,2,1,1);
    gl3->addWidget(l1d3_10,10,2,1,1);
    gl3->addWidget(l1d3_11,11,2,1,1);
    gl3->addWidget(l1d3_12,12,2,1,1);
    gl3->addWidget(l1d3_13,13,2,1,1);

    spbx1_thi=new QSpinBox;
    spbx2_thi=new QSpinBox;
    spbx3_thi=new QSpinBox;
    spbx4_thi=new QSpinBox;
    spbx5_thi=new QSpinBox;
    spbx6_thi=new QSpinBox;
    spbx7_thi=new QSpinBox;
    spbx8_thi=new QSpinBox;
    spbx9_thi=new QSpinBox;
    spbx10_thi=new QSpinBox;
    spbx11_thi=new QSpinBox;
    spbx12_thi=new QSpinBox;
    spbx13_thi=new QSpinBox;
    spbx1_thi->setRange(0,9999); //设置范围
    spbx2_thi->setRange(0,9999);
    spbx3_thi->setRange(0,9999);
    spbx4_thi->setRange(0,9999);
    spbx5_thi->setRange(0,9999);
    spbx6_thi->setRange(0,9999);
    spbx7_thi->setRange(0,9999);
    spbx8_thi->setRange(0,9999);
    spbx9_thi->setRange(0,9999);
    spbx10_thi->setRange(0,9999);
    spbx11_thi->setRange(0,9999);
    spbx12_thi->setRange(0,9999);
    spbx13_thi->setRange(0,9999);
    gl3->addWidget(spbx1_thi,1,3,1,1);
    gl3->addWidget(spbx2_thi,2,3,1,1);
    gl3->addWidget(spbx3_thi,3,3,1,1);
    gl3->addWidget(spbx4_thi,4,3,1,1);
    gl3->addWidget(spbx5_thi,5,3,1,1);
    gl3->addWidget(spbx6_thi,6,3,1,1);
    gl3->addWidget(spbx7_thi,7,3,1,1);
    gl3->addWidget(spbx8_thi,8,3,1,1);
    gl3->addWidget(spbx9_thi,9,3,1,1);
    gl3->addWidget(spbx10_thi,10,3,1,1);
    gl3->addWidget(spbx11_thi,11,3,1,1);
    gl3->addWidget(spbx12_thi,12,3,1,1);
    gl3->addWidget(spbx13_thi,13,3,1,1);

    spby1_thi=new QSpinBox;
    spby2_thi=new QSpinBox;
    spby3_thi=new QSpinBox;
    spby4_thi=new QSpinBox;
    spby5_thi=new QSpinBox;
    spby6_thi=new QSpinBox;
    spby7_thi=new QSpinBox;
    spby8_thi=new QSpinBox;
    spby9_thi=new QSpinBox;
    spby10_thi=new QSpinBox;
    spby11_thi=new QSpinBox;
    spby12_thi=new QSpinBox;
    spby13_thi=new QSpinBox;
    spby1_thi->setRange(0,9999);
    spby2_thi->setRange(0,9999);
    spby3_thi->setRange(0,9999);
    spby4_thi->setRange(0,9999);
    spby5_thi->setRange(0,9999);
    spby6_thi->setRange(0,9999);
    spby7_thi->setRange(0,9999);
    spby8_thi->setRange(0,9999);
    spby9_thi->setRange(0,9999);
    spby10_thi->setRange(0,9999);
    spby11_thi->setRange(0,9999);
    spby12_thi->setRange(0,9999);
    spby13_thi->setRange(0,9999);
    gl3->addWidget(spby1_thi,1,4,1,1);
    gl3->addWidget(spby2_thi,2,4,1,1);
    gl3->addWidget(spby3_thi,3,4,1,1);
    gl3->addWidget(spby4_thi,4,4,1,1);
    gl3->addWidget(spby5_thi,5,4,1,1);
    gl3->addWidget(spby6_thi,6,4,1,1);
    gl3->addWidget(spby7_thi,7,4,1,1);
    gl3->addWidget(spby8_thi,8,4,1,1);
    gl3->addWidget(spby9_thi,9,4,1,1);
    gl3->addWidget(spby10_thi,10,4,1,1);
    gl3->addWidget(spby11_thi,11,4,1,1);
    gl3->addWidget(spby12_thi,12,4,1,1);
    gl3->addWidget(spby13_thi,13,4,1,1);

    g3->setLayout(gl3);

    QVBoxLayout *v3b=new QVBoxLayout;
    v3b->addLayout(h3);
    v3b->addLayout(f3);
    v3b->addWidget(g3);

    connect(change3_thi,SIGNAL(activated(int)),this,SLOT(tosersor_continue_thi(int)));
/*
    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_thi()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_thi()));
    connect(lineEdit_continueRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot_thi()));
    connect(lineEdit_continueResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot_thi()));
*/
    w_ContinueField_thi->setLayout(v3b);
    w_ContinueField_thi->resize(300,500);
    w_ContinueField_thi->setWindowTitle("通道3连续视场");
}

void MainWindow::init_cameraCfg_fou()
{
    w_sersor1_fou=new MyWidget;
    w_seitchField_fou=new MyWidget;
    w_ContinueField_fou=new MyWidget;

    w_sersor1_fou->setWindowTitle("通道4固定视场");
    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道4固定视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    change1_fou=new QComboBox;
    change1_fou->addItem("固定视场");
    change1_fou->addItem("可切换视场");
    change1_fou->addItem("连续视场");

    lineEdit_fieldRadio_fou=new QLineEdit;
    QLabel *l=new  QLabel;
    l->setText("*");
    lineEdit_fieldResolution_fou=new QLineEdit;
    lineEdit_fieldResolution2_fou=new QLineEdit;

    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_fieldResolution_fou);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_fieldResolution2_fou);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1_fou[0],change1_fou);
    f1->addRow(sensor_s1_fou[1],lineEdit_fieldRadio_fou);
    f1->addRow(sensor_s1_fou[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");

    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");

    lEdt_fou=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    sp_fou=new QSpinBox;
    sp2_fou=new QSpinBox;
    sp_fou->setRange(0,9999);
    sp2_fou->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l11,0,0,1,1);
    gl->addWidget(l14,0,1,1,1);
    gl->addWidget(l14,0,2,1,1);
    gl->addWidget(l12,0,3,1,1);
    gl->addWidget(l13,0,4,1,1);
    gl->addWidget(l14,0,5,1,1);
    gl->addWidget(lEdt_fou,1,0,1,1);
    gl->addWidget(l1d,1,1,1,1);
    gl->addWidget(l14,1,2,1,1);
    gl->addWidget(sp_fou,1,3,1,1);
    gl->addWidget(sp2_fou,1,4,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(change1_fou,SIGNAL(activated(int)),this,SLOT(tosersor_fix_fou(int)));
/*
    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_fou()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fou()));
    connect(lineEdit_fieldRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot_fou()));
    connect(lineEdit_fieldResolution_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot_fou()));
    connect(lineEdit_fieldResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot_fou()));
    connect(lEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot_fou()));
    connect(sp_fou,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot_fou(int)));
    connect(sp2_fou,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot_fou(int)));
*/
    w_sersor1_fou->setLayout(v);
    w_sersor1_fou->resize(300,200);

    w_seitchField_fou->setWindowTitle("通道4可切换视场");
    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_s1Switch_default);
    v2->addWidget(btn_s1Switch_update);
    QLabel *label2=new QLabel;
    label2->setText("通道4可切换视场参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

    change2_fou=new QComboBox;
    change2_fou->addItem("可切换视场");
    change2_fou->addItem("固定视场");
    change2_fou->addItem("连续视场");
    lineEdit_switchRadio_fou=new QLineEdit;

    lineEdit_switchResolution_fou=new QLineEdit;
    lineEdit_switchResolution2_fou=new QLineEdit;
    lineEdit_switchResolution_fou->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2_fou->setValidator(new QIntValidator(100,10000,this));
    QLabel *l222=new  QLabel;
    l222->setText("*");
    QHBoxLayout *sensor_Resolution2=new QHBoxLayout;
    sensor_Resolution2->addWidget(lineEdit_switchResolution_fou);
    sensor_Resolution2->addWidget(l222);
    sensor_Resolution2->addWidget(lineEdit_switchResolution2_fou);

    fovclass_fou = new QComboBox;
    fovclass_fou->addItem("可切换视场1");
    fovclass_fou->addItem("可切换视场2");
    fovclass_fou->addItem("可切换视场3");
    fovclass_fou->addItem("可切换视场4");
    fovclass_fou->addItem("可切换视场5");

    QFormLayout *f2=new QFormLayout;
    f2->addRow(sensor_s1_fou[0],change2_fou);
    f2->addRow(sensor_s1_fou[1],lineEdit_switchRadio_fou);
    f2->addRow(sensor_s1_fou[2],sensor_Resolution2);
    f2->addRow("测试视场等级",fovclass_fou);

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");

    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l22,0,3,1,1);
    gl2->addWidget(l23,0,4,1,1);
    gl2->addWidget(l24,0,5,1,1);

    QLabel *fovclass_label1 = new QLabel;
    QLabel *fovclass_label2 = new QLabel;
    QLabel *fovclass_label3 = new QLabel;
    QLabel *fovclass_label4 = new QLabel;
    QLabel *fovclass_label5 = new QLabel;
    fovclass_label1->setText("可切换视场1");
    fovclass_label2->setText("可切换视场2");
    fovclass_label3->setText("可切换视场3");
    fovclass_label4->setText("可切换视场4");
    fovclass_label5->setText("可切换视场5");
    gl2->addWidget(fovclass_label1,1,0,1,1);
    gl2->addWidget(fovclass_label2,2,0,1,1);
    gl2->addWidget(fovclass_label3,3,0,1,1);
    gl2->addWidget(fovclass_label4,4,0,1,1);
    gl2->addWidget(fovclass_label5,5,0,1,1);
    lineEdit_s1_Fov0_fou=new QLineEdit;
    lineEdit_s1_Fov1_fou=new QLineEdit;
    lineEdit_s1_Fov2_fou=new QLineEdit;
    lineEdit_s1_Fov3_fou=new QLineEdit;
    lineEdit_s1_Fov4_fou=new QLineEdit;
    gl2->addWidget(lineEdit_s1_Fov0_fou,1,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov1_fou,2,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov2_fou,3,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov3_fou,4,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov4_fou,5,1,1,1);

    QLabel* l1d21=new QLabel;
    QLabel* l1d22=new QLabel;
    QLabel* l1d23=new QLabel;
    QLabel* l1d24=new QLabel;
    QLabel* l1d25=new QLabel;
    l1d21->setText("度");
    l1d22->setText("度");
    l1d23->setText("度");
    l1d24->setText("度");
    l1d25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    spbx_switch1_fou=new QSpinBox;
    spbx_switch2_fou=new QSpinBox;
    spbx_switch3_fou=new QSpinBox;
    spbx_switch4_fou=new QSpinBox;
    spbx_switch5_fou=new QSpinBox;
    spbx_switch1_fou->setRange(0,9999);
    spbx_switch2_fou->setRange(0,9999);
    spbx_switch3_fou->setRange(0,9999);
    spbx_switch4_fou->setRange(0,9999);
    spbx_switch5_fou->setRange(0,9999);
    gl2->addWidget(spbx_switch1_fou,1,3,1,1);
    gl2->addWidget(spbx_switch2_fou,2,3,1,1);
    gl2->addWidget(spbx_switch3_fou,3,3,1,1);
    gl2->addWidget(spbx_switch4_fou,4,3,1,1);
    gl2->addWidget(spbx_switch5_fou,5,3,1,1);

    spby_switch1_fou=new QSpinBox;
    spby_switch2_fou=new QSpinBox;
    spby_switch3_fou=new QSpinBox;
    spby_switch4_fou=new QSpinBox;
    spby_switch5_fou=new QSpinBox;
    spby_switch1_fou->setRange(0,9999);
    spby_switch2_fou->setRange(0,9999);
    spby_switch3_fou->setRange(0,9999);
    spby_switch4_fou->setRange(0,9999);
    spby_switch5_fou->setRange(0,9999);
    gl2->addWidget(spby_switch1_fou,1,4,1,1);
    gl2->addWidget(spby_switch2_fou,2,4,1,1);
    gl2->addWidget(spby_switch3_fou,3,4,1,1);
    gl2->addWidget(spby_switch4_fou,4,4,1,1);
    gl2->addWidget(spby_switch5_fou,5,4,1,1);

    g2->setLayout(gl2);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);
    v22->addWidget(g2);

    connect(change2_fou,SIGNAL(activated(int)),this,SLOT(toSensor_switch_fou(int)));
/*
    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_fou()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fou()));
    connect(lineEdit_switchRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot_fou()));
    connect(lineEdit_switchResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot_fou()));
*/
    w_seitchField_fou->setLayout(v22);
    w_seitchField_fou->resize(300,200);

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_continue_default);
    v3->addWidget(btn_continue_update);
    QLabel *label3=new QLabel;
    label3->setText("通道4连续视场参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

    change3_fou=new QComboBox;
    change3_fou->addItem("连续视场");
    change3_fou->addItem("固定视场");
    change3_fou->addItem("可切换视场");

    lineEdit_continueRadio_fou=new QLineEdit;
    lineEdit_continueResolution_fou=new QLineEdit;
    lineEdit_continueResolution2_fou=new QLineEdit;
    lineEdit_continueResolution_fou->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2_fou->setValidator(new QIntValidator(100,10000,this));
    QLabel *l3=new  QLabel;
    l3->setText("*");
    QHBoxLayout *sensor_Resolution3=new QHBoxLayout;
    sensor_Resolution3->addWidget(lineEdit_continueResolution_fou);

    sensor_Resolution3->addWidget(l3);
    sensor_Resolution3->addWidget(lineEdit_continueResolution2_fou);

    testfov_fou = new QLineEdit;
    QFormLayout *f3=new QFormLayout;
    f3->addRow(sensor_s1_fou[0],change3_fou);
    f3->addRow(sensor_s1_fou[1],lineEdit_continueRadio_fou);
    f3->addRow(sensor_s1_fou[2],sensor_Resolution3);
    f3->addRow("测试视场",testfov_fou);

    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");

    QGridLayout *gl3=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的\n   反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    gl3->addWidget(l30,0,0,1,1);
    gl3->addWidget(l31,0,1,1,1);
    gl3->addWidget(l32,0,3,1,1);
    gl3->addWidget(l33,0,4,1,1);
    gl3->addWidget(l34,0,5,1,1);

    fEdt1_fou=new QLineEdit;
    fEdt2_fou=new QLineEdit;
    fEdt3_fou=new QLineEdit;
    fEdt4_fou=new QLineEdit;
    fEdt5_fou=new QLineEdit;
    fEdt6_fou=new QLineEdit;
    fEdt7_fou=new QLineEdit;
    fEdt8_fou=new QLineEdit;
    fEdt9_fou=new QLineEdit;
    fEdt10_fou=new QLineEdit;
    fEdt11_fou=new QLineEdit;
    fEdt12_fou=new QLineEdit;
    fEdt13_fou=new QLineEdit;
    gl3->addWidget(fEdt1_fou,1,0,1,1);
    gl3->addWidget(fEdt2_fou,2,0,1,1);
    gl3->addWidget(fEdt3_fou,3,0,1,1);
    gl3->addWidget(fEdt4_fou,4,0,1,1);
    gl3->addWidget(fEdt5_fou,5,0,1,1);
    gl3->addWidget(fEdt6_fou,6,0,1,1);
    gl3->addWidget(fEdt7_fou,7,0,1,1);
    gl3->addWidget(fEdt8_fou,8,0,1,1);
    gl3->addWidget(fEdt9_fou,9,0,1,1);
    gl3->addWidget(fEdt10_fou,10,0,1,1);
    gl3->addWidget(fEdt11_fou,11,0,1,1);
    gl3->addWidget(fEdt12_fou,12,0,1,1);
    gl3->addWidget(fEdt13_fou,13,0,1,1);

    lEdt1_fou=new QLineEdit;
    lEdt2_fou=new QLineEdit;
    lEdt3_fou=new QLineEdit;
    lEdt4_fou=new QLineEdit;
    lEdt5_fou=new QLineEdit;
    lEdt6_fou=new QLineEdit;
    lEdt7_fou=new QLineEdit;
    lEdt8_fou=new QLineEdit;
    lEdt9_fou=new QLineEdit;
    lEdt10_fou=new QLineEdit;
    lEdt11_fou=new QLineEdit;
    lEdt12_fou=new QLineEdit;
    lEdt13_fou=new QLineEdit;
    gl3->addWidget(lEdt1_fou,1,1,1,1);
    gl3->addWidget(lEdt2_fou,2,1,1,1);
    gl3->addWidget(lEdt3_fou,3,1,1,1);
    gl3->addWidget(lEdt4_fou,4,1,1,1);
    gl3->addWidget(lEdt5_fou,5,1,1,1);
    gl3->addWidget(lEdt6_fou,6,1,1,1);
    gl3->addWidget(lEdt7_fou,7,1,1,1);
    gl3->addWidget(lEdt8_fou,8,1,1,1);
    gl3->addWidget(lEdt9_fou,9,1,1,1);
    gl3->addWidget(lEdt10_fou,10,1,1,1);
    gl3->addWidget(lEdt11_fou,11,1,1,1);
    gl3->addWidget(lEdt12_fou,12,1,1,1);
    gl3->addWidget(lEdt13_fou,13,1,1,1);

    QLabel* l1d3_1=new QLabel;
    QLabel* l1d3_2=new QLabel;
    QLabel* l1d3_3=new QLabel;
    QLabel* l1d3_4=new QLabel;
    QLabel* l1d3_5=new QLabel;
    QLabel* l1d3_6=new QLabel;
    QLabel* l1d3_7=new QLabel;
    QLabel* l1d3_8=new QLabel;
    QLabel* l1d3_9=new QLabel;
    QLabel* l1d3_10=new QLabel;
    QLabel* l1d3_11=new QLabel;
    QLabel* l1d3_12=new QLabel;
    QLabel* l1d3_13=new QLabel;
    l1d3_1->setText("度");
    l1d3_2->setText("度");
    l1d3_3->setText("度");
    l1d3_4->setText("度");
    l1d3_5->setText("度");
    l1d3_6->setText("度");
    l1d3_7->setText("度");
    l1d3_8->setText("度");
    l1d3_9->setText("度");
    l1d3_10->setText("度");
    l1d3_11->setText("度");
    l1d3_12->setText("度");
    l1d3_13->setText("度");
    gl3->addWidget(l1d3_1,1,2,1,1);
    gl3->addWidget(l1d3_2,2,2,1,1);
    gl3->addWidget(l1d3_3,3,2,1,1);
    gl3->addWidget(l1d3_4,4,2,1,1);
    gl3->addWidget(l1d3_5,5,2,1,1);
    gl3->addWidget(l1d3_6,6,2,1,1);
    gl3->addWidget(l1d3_7,7,2,1,1);
    gl3->addWidget(l1d3_8,8,2,1,1);
    gl3->addWidget(l1d3_9,9,2,1,1);
    gl3->addWidget(l1d3_10,10,2,1,1);
    gl3->addWidget(l1d3_11,11,2,1,1);
    gl3->addWidget(l1d3_12,12,2,1,1);
    gl3->addWidget(l1d3_13,13,2,1,1);

    spbx1_fou=new QSpinBox;
    spbx2_fou=new QSpinBox;
    spbx3_fou=new QSpinBox;
    spbx4_fou=new QSpinBox;
    spbx5_fou=new QSpinBox;
    spbx6_fou=new QSpinBox;
    spbx7_fou=new QSpinBox;
    spbx8_fou=new QSpinBox;
    spbx9_fou=new QSpinBox;
    spbx10_fou=new QSpinBox;
    spbx11_fou=new QSpinBox;
    spbx12_fou=new QSpinBox;
    spbx13_fou=new QSpinBox;
    spbx1_fou->setRange(0,9999); //设置范围
    spbx2_fou->setRange(0,9999);
    spbx3_fou->setRange(0,9999);
    spbx4_fou->setRange(0,9999);
    spbx5_fou->setRange(0,9999);
    spbx6_fou->setRange(0,9999);
    spbx7_fou->setRange(0,9999);
    spbx8_fou->setRange(0,9999);
    spbx9_fou->setRange(0,9999);
    spbx10_fou->setRange(0,9999);
    spbx11_fou->setRange(0,9999);
    spbx12_fou->setRange(0,9999);
    spbx13_fou->setRange(0,9999);
    gl3->addWidget(spbx1_fou,1,3,1,1);
    gl3->addWidget(spbx2_fou,2,3,1,1);
    gl3->addWidget(spbx3_fou,3,3,1,1);
    gl3->addWidget(spbx4_fou,4,3,1,1);
    gl3->addWidget(spbx5_fou,5,3,1,1);
    gl3->addWidget(spbx6_fou,6,3,1,1);
    gl3->addWidget(spbx7_fou,7,3,1,1);
    gl3->addWidget(spbx8_fou,8,3,1,1);
    gl3->addWidget(spbx9_fou,9,3,1,1);
    gl3->addWidget(spbx10_fou,10,3,1,1);
    gl3->addWidget(spbx11_fou,11,3,1,1);
    gl3->addWidget(spbx12_fou,12,3,1,1);
    gl3->addWidget(spbx13_fou,13,3,1,1);

    spby1_fou=new QSpinBox;
    spby2_fou=new QSpinBox;
    spby3_fou=new QSpinBox;
    spby4_fou=new QSpinBox;
    spby5_fou=new QSpinBox;
    spby6_fou=new QSpinBox;
    spby7_fou=new QSpinBox;
    spby8_fou=new QSpinBox;
    spby9_fou=new QSpinBox;
    spby10_fou=new QSpinBox;
    spby11_fou=new QSpinBox;
    spby12_fou=new QSpinBox;
    spby13_fou=new QSpinBox;
    spby1_fou->setRange(0,9999);
    spby2_fou->setRange(0,9999);
    spby3_fou->setRange(0,9999);
    spby4_fou->setRange(0,9999);
    spby5_fou->setRange(0,9999);
    spby6_fou->setRange(0,9999);
    spby7_fou->setRange(0,9999);
    spby8_fou->setRange(0,9999);
    spby9_fou->setRange(0,9999);
    spby10_fou->setRange(0,9999);
    spby11_fou->setRange(0,9999);
    spby12_fou->setRange(0,9999);
    spby13_fou->setRange(0,9999);
    gl3->addWidget(spby1_fou,1,4,1,1);
    gl3->addWidget(spby2_fou,2,4,1,1);
    gl3->addWidget(spby3_fou,3,4,1,1);
    gl3->addWidget(spby4_fou,4,4,1,1);
    gl3->addWidget(spby5_fou,5,4,1,1);
    gl3->addWidget(spby6_fou,6,4,1,1);
    gl3->addWidget(spby7_fou,7,4,1,1);
    gl3->addWidget(spby8_fou,8,4,1,1);
    gl3->addWidget(spby9_fou,9,4,1,1);
    gl3->addWidget(spby10_fou,10,4,1,1);
    gl3->addWidget(spby11_fou,11,4,1,1);
    gl3->addWidget(spby12_fou,12,4,1,1);
    gl3->addWidget(spby13_fou,13,4,1,1);

    g3->setLayout(gl3);

    QVBoxLayout *v3b=new QVBoxLayout;
    v3b->addLayout(h3);
    v3b->addLayout(f3);
    v3b->addWidget(g3);

    connect(change3_fou,SIGNAL(activated(int)),this,SLOT(tosersor_continue_fou(int)));
/*
    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_fou()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fou()));
    connect(lineEdit_continueRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot_fou()));
    connect(lineEdit_continueResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot_fou()));
*/
    w_ContinueField_fou->setLayout(v3b);
    w_ContinueField_fou->resize(300,500);
    w_ContinueField_fou->setWindowTitle("通道4连续视场");
}

void MainWindow::init_cameraCfg_fif()
{
    w_sersor1_fif=new MyWidget;
    w_seitchField_fif=new MyWidget;
    w_ContinueField_fif=new MyWidget;

    w_sersor1_fif->setWindowTitle("通道5固定视场");
    QPushButton *btn_default=new QPushButton;
    QPushButton *btn_update=new QPushButton;
    btn_default->setText("默认");
    btn_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_default);
    v1->addWidget(btn_update);
    QLabel *label=new QLabel;
    label->setText("通道5固定视场参数设置");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    change1_fif=new QComboBox;
    change1_fif->addItem("固定视场");
    change1_fif->addItem("可切换视场");
    change1_fif->addItem("连续视场");

    lineEdit_fieldRadio_fif=new QLineEdit;
    QLabel *l=new  QLabel;
    l->setText("*");
    lineEdit_fieldResolution_fif=new QLineEdit;
    lineEdit_fieldResolution2_fif=new QLineEdit;

    QHBoxLayout *sensor_Resolution=new QHBoxLayout;
    sensor_Resolution->addWidget(lineEdit_fieldResolution_fif);
    sensor_Resolution->addWidget(l);
    sensor_Resolution->addWidget(lineEdit_fieldResolution2_fif);

    QFormLayout *f1=new QFormLayout;
    f1->addRow(sensor_s1_fif[0],change1_fif);
    f1->addRow(sensor_s1_fif[1],lineEdit_fieldRadio_fif);
    f1->addRow(sensor_s1_fif[2],sensor_Resolution);

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");

    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");

    lEdt_fif=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    sp_fif=new QSpinBox;
    sp2_fif=new QSpinBox;
    sp_fif->setRange(0,9999);
    sp2_fif->setRange(0,9999);

    QGridLayout *gl=new QGridLayout;
    gl->addWidget(l11,0,0,1,1);
    gl->addWidget(l14,0,1,1,1);
    gl->addWidget(l14,0,2,1,1);
    gl->addWidget(l12,0,3,1,1);
    gl->addWidget(l13,0,4,1,1);
    gl->addWidget(l14,0,5,1,1);
    gl->addWidget(lEdt_fif,1,0,1,1);
    gl->addWidget(l1d,1,1,1,1);
    gl->addWidget(l14,1,2,1,1);
    gl->addWidget(sp_fif,1,3,1,1);
    gl->addWidget(sp2_fif,1,4,1,1);

    g->setLayout(gl);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    v->addWidget(g);

    connect(change1_fif,SIGNAL(activated(int)),this,SLOT(tosersor_fix_fif(int)));
/*
    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_fif()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fif()));
    connect(lineEdit_fieldRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot_fif()));
    connect(lineEdit_fieldResolution_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot_fif()));
    connect(lineEdit_fieldResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot_fif()));
    connect(lEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot_fif()));
    connect(sp_fif,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot_fif(int)));
    connect(sp2_fif,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot_fif(int)));
*/
    w_sersor1_fif->setLayout(v);
    w_sersor1_fif->resize(300,200);

    w_seitchField_fif->setWindowTitle("通道5可切换视场");
    QPushButton* btn_s1Switch_default=new QPushButton;
    QPushButton* btn_s1Switch_update=new QPushButton;
    btn_s1Switch_default->setText("默认");
    btn_s1Switch_update->setText("保存");
    QVBoxLayout *v2=new QVBoxLayout;
    v2->addWidget(btn_s1Switch_default);
    v2->addWidget(btn_s1Switch_update);
    QLabel *label2=new QLabel;
    label2->setText("通道5可切换视场参数设置");
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addLayout(v2);
    h2->addWidget(label2);

    change2_fif=new QComboBox;
    change2_fif->addItem("可切换视场");
    change2_fif->addItem("固定视场");
    change2_fif->addItem("连续视场");
    lineEdit_switchRadio_fif=new QLineEdit;

    lineEdit_switchResolution_fif=new QLineEdit;
    lineEdit_switchResolution2_fif=new QLineEdit;
    lineEdit_switchResolution_fif->setValidator(new QIntValidator(100,10000,this));
    lineEdit_switchResolution2_fif->setValidator(new QIntValidator(100,10000,this));
    QLabel *l222=new  QLabel;
    l222->setText("*");
    QHBoxLayout *sensor_Resolution2=new QHBoxLayout;
    sensor_Resolution2->addWidget(lineEdit_switchResolution_fif);
    sensor_Resolution2->addWidget(l222);
    sensor_Resolution2->addWidget(lineEdit_switchResolution2_fif);

    fovclass_fif = new QComboBox;
    fovclass_fif->addItem("可切换视场1");
    fovclass_fif->addItem("可切换视场2");
    fovclass_fif->addItem("可切换视场3");
    fovclass_fif->addItem("可切换视场4");
    fovclass_fif->addItem("可切换视场5");

    QFormLayout *f2=new QFormLayout;
    f2->addRow(sensor_s1_fif[0],change2_fif);
    f2->addRow(sensor_s1_fif[1],lineEdit_switchRadio_fif);
    f2->addRow(sensor_s1_fif[2],sensor_Resolution2);
    f2->addRow("测试视场等级",fovclass_fif);

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");

    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l22,0,3,1,1);
    gl2->addWidget(l23,0,4,1,1);
    gl2->addWidget(l24,0,5,1,1);

    QLabel *fovclass_label1 = new QLabel;
    QLabel *fovclass_label2 = new QLabel;
    QLabel *fovclass_label3 = new QLabel;
    QLabel *fovclass_label4 = new QLabel;
    QLabel *fovclass_label5 = new QLabel;
    fovclass_label1->setText("可切换视场1");
    fovclass_label2->setText("可切换视场2");
    fovclass_label3->setText("可切换视场3");
    fovclass_label4->setText("可切换视场4");
    fovclass_label5->setText("可切换视场5");
    gl2->addWidget(fovclass_label1,1,0,1,1);
    gl2->addWidget(fovclass_label2,2,0,1,1);
    gl2->addWidget(fovclass_label3,3,0,1,1);
    gl2->addWidget(fovclass_label4,4,0,1,1);
    gl2->addWidget(fovclass_label5,5,0,1,1);
    lineEdit_s1_Fov0_fif=new QLineEdit;
    lineEdit_s1_Fov1_fif=new QLineEdit;
    lineEdit_s1_Fov2_fif=new QLineEdit;
    lineEdit_s1_Fov3_fif=new QLineEdit;
    lineEdit_s1_Fov4_fif=new QLineEdit;
    gl2->addWidget(lineEdit_s1_Fov0_fif,1,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov1_fif,2,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov2_fif,3,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov3_fif,4,1,1,1);
    gl2->addWidget(lineEdit_s1_Fov4_fif,5,1,1,1);

    QLabel* l1d21=new QLabel;
    QLabel* l1d22=new QLabel;
    QLabel* l1d23=new QLabel;
    QLabel* l1d24=new QLabel;
    QLabel* l1d25=new QLabel;
    l1d21->setText("度");
    l1d22->setText("度");
    l1d23->setText("度");
    l1d24->setText("度");
    l1d25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    spbx_switch1_fif=new QSpinBox;
    spbx_switch2_fif=new QSpinBox;
    spbx_switch3_fif=new QSpinBox;
    spbx_switch4_fif=new QSpinBox;
    spbx_switch5_fif=new QSpinBox;
    spbx_switch1_fif->setRange(0,9999);
    spbx_switch2_fif->setRange(0,9999);
    spbx_switch3_fif->setRange(0,9999);
    spbx_switch4_fif->setRange(0,9999);
    spbx_switch5_fif->setRange(0,9999);
    gl2->addWidget(spbx_switch1_fif,1,3,1,1);
    gl2->addWidget(spbx_switch2_fif,2,3,1,1);
    gl2->addWidget(spbx_switch3_fif,3,3,1,1);
    gl2->addWidget(spbx_switch4_fif,4,3,1,1);
    gl2->addWidget(spbx_switch5_fif,5,3,1,1);

    spby_switch1_fif=new QSpinBox;
    spby_switch2_fif=new QSpinBox;
    spby_switch3_fif=new QSpinBox;
    spby_switch4_fif=new QSpinBox;
    spby_switch5_fif=new QSpinBox;
    spby_switch1_fif->setRange(0,9999);
    spby_switch2_fif->setRange(0,9999);
    spby_switch3_fif->setRange(0,9999);
    spby_switch4_fif->setRange(0,9999);
    spby_switch5_fif->setRange(0,9999);
    gl2->addWidget(spby_switch1_fif,1,4,1,1);
    gl2->addWidget(spby_switch2_fif,2,4,1,1);
    gl2->addWidget(spby_switch3_fif,3,4,1,1);
    gl2->addWidget(spby_switch4_fif,4,4,1,1);
    gl2->addWidget(spby_switch5_fif,5,4,1,1);

    g2->setLayout(gl2);

    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(f2);
    v22->addWidget(g2);

    connect(change2_fif,SIGNAL(activated(int)),this,SLOT(toSensor_switch_fif(int)));
/*
    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_fif()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fif()));
    connect(lineEdit_switchRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot_fif()));
    connect(lineEdit_switchResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot_fif()));
*/
    w_seitchField_fif->setLayout(v22);
    w_seitchField_fif->resize(300,200);

    QPushButton* btn_continue_default=new QPushButton;
    QPushButton* btn_continue_update=new QPushButton;
    btn_continue_default->setText("默认");
    btn_continue_update->setText("保存");
    QVBoxLayout *v3=new QVBoxLayout;
    v3->addWidget(btn_continue_default);
    v3->addWidget(btn_continue_update);
    QLabel *label3=new QLabel;
    label3->setText("通道5连续视场参数设置");
    QHBoxLayout *h3=new QHBoxLayout;
    h3->addLayout(v3);
    h3->addWidget(label3);

    change3_fif=new QComboBox;
    change3_fif->addItem("连续视场");
    change3_fif->addItem("固定视场");
    change3_fif->addItem("可切换视场");

    lineEdit_continueRadio_fif=new QLineEdit;
    lineEdit_continueResolution_fif=new QLineEdit;
    lineEdit_continueResolution2_fif=new QLineEdit;
    lineEdit_continueResolution_fif->setValidator(new QIntValidator(100,10000,this));
    lineEdit_continueResolution2_fif->setValidator(new QIntValidator(100,10000,this));
    QLabel *l3=new  QLabel;
    l3->setText("*");
    QHBoxLayout *sensor_Resolution3=new QHBoxLayout;
    sensor_Resolution3->addWidget(lineEdit_continueResolution_fif);

    sensor_Resolution3->addWidget(l3);
    sensor_Resolution3->addWidget(lineEdit_continueResolution2_fif);

    testfov_fif = new QLineEdit;
    QFormLayout *f3=new QFormLayout;
    f3->addRow(sensor_s1_fif[0],change3_fif);
    f3->addRow(sensor_s1_fif[1],lineEdit_continueRadio_fif);
    f3->addRow(sensor_s1_fif[2],sensor_Resolution3);
    f3->addRow("测试视场",testfov_fif);

    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");

    QGridLayout *gl3=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的\n   反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    gl3->addWidget(l30,0,0,1,1);
    gl3->addWidget(l31,0,1,1,1);
    gl3->addWidget(l32,0,3,1,1);
    gl3->addWidget(l33,0,4,1,1);
    gl3->addWidget(l34,0,5,1,1);

    fEdt1_fif=new QLineEdit;
    fEdt2_fif=new QLineEdit;
    fEdt3_fif=new QLineEdit;
    fEdt4_fif=new QLineEdit;
    fEdt5_fif=new QLineEdit;
    fEdt6_fif=new QLineEdit;
    fEdt7_fif=new QLineEdit;
    fEdt8_fif=new QLineEdit;
    fEdt9_fif=new QLineEdit;
    fEdt10_fif=new QLineEdit;
    fEdt11_fif=new QLineEdit;
    fEdt12_fif=new QLineEdit;
    fEdt13_fif=new QLineEdit;
    gl3->addWidget(fEdt1_fif,1,0,1,1);
    gl3->addWidget(fEdt2_fif,2,0,1,1);
    gl3->addWidget(fEdt3_fif,3,0,1,1);
    gl3->addWidget(fEdt4_fif,4,0,1,1);
    gl3->addWidget(fEdt5_fif,5,0,1,1);
    gl3->addWidget(fEdt6_fif,6,0,1,1);
    gl3->addWidget(fEdt7_fif,7,0,1,1);
    gl3->addWidget(fEdt8_fif,8,0,1,1);
    gl3->addWidget(fEdt9_fif,9,0,1,1);
    gl3->addWidget(fEdt10_fif,10,0,1,1);
    gl3->addWidget(fEdt11_fif,11,0,1,1);
    gl3->addWidget(fEdt12_fif,12,0,1,1);
    gl3->addWidget(fEdt13_fif,13,0,1,1);

    lEdt1_fif=new QLineEdit;
    lEdt2_fif=new QLineEdit;
    lEdt3_fif=new QLineEdit;
    lEdt4_fif=new QLineEdit;
    lEdt5_fif=new QLineEdit;
    lEdt6_fif=new QLineEdit;
    lEdt7_fif=new QLineEdit;
    lEdt8_fif=new QLineEdit;
    lEdt9_fif=new QLineEdit;
    lEdt10_fif=new QLineEdit;
    lEdt11_fif=new QLineEdit;
    lEdt12_fif=new QLineEdit;
    lEdt13_fif=new QLineEdit;
    gl3->addWidget(lEdt1_fif,1,1,1,1);
    gl3->addWidget(lEdt2_fif,2,1,1,1);
    gl3->addWidget(lEdt3_fif,3,1,1,1);
    gl3->addWidget(lEdt4_fif,4,1,1,1);
    gl3->addWidget(lEdt5_fif,5,1,1,1);
    gl3->addWidget(lEdt6_fif,6,1,1,1);
    gl3->addWidget(lEdt7_fif,7,1,1,1);
    gl3->addWidget(lEdt8_fif,8,1,1,1);
    gl3->addWidget(lEdt9_fif,9,1,1,1);
    gl3->addWidget(lEdt10_fif,10,1,1,1);
    gl3->addWidget(lEdt11_fif,11,1,1,1);
    gl3->addWidget(lEdt12_fif,12,1,1,1);
    gl3->addWidget(lEdt13_fif,13,1,1,1);

    QLabel* l1d3_1=new QLabel;
    QLabel* l1d3_2=new QLabel;
    QLabel* l1d3_3=new QLabel;
    QLabel* l1d3_4=new QLabel;
    QLabel* l1d3_5=new QLabel;
    QLabel* l1d3_6=new QLabel;
    QLabel* l1d3_7=new QLabel;
    QLabel* l1d3_8=new QLabel;
    QLabel* l1d3_9=new QLabel;
    QLabel* l1d3_10=new QLabel;
    QLabel* l1d3_11=new QLabel;
    QLabel* l1d3_12=new QLabel;
    QLabel* l1d3_13=new QLabel;
    l1d3_1->setText("度");
    l1d3_2->setText("度");
    l1d3_3->setText("度");
    l1d3_4->setText("度");
    l1d3_5->setText("度");
    l1d3_6->setText("度");
    l1d3_7->setText("度");
    l1d3_8->setText("度");
    l1d3_9->setText("度");
    l1d3_10->setText("度");
    l1d3_11->setText("度");
    l1d3_12->setText("度");
    l1d3_13->setText("度");
    gl3->addWidget(l1d3_1,1,2,1,1);
    gl3->addWidget(l1d3_2,2,2,1,1);
    gl3->addWidget(l1d3_3,3,2,1,1);
    gl3->addWidget(l1d3_4,4,2,1,1);
    gl3->addWidget(l1d3_5,5,2,1,1);
    gl3->addWidget(l1d3_6,6,2,1,1);
    gl3->addWidget(l1d3_7,7,2,1,1);
    gl3->addWidget(l1d3_8,8,2,1,1);
    gl3->addWidget(l1d3_9,9,2,1,1);
    gl3->addWidget(l1d3_10,10,2,1,1);
    gl3->addWidget(l1d3_11,11,2,1,1);
    gl3->addWidget(l1d3_12,12,2,1,1);
    gl3->addWidget(l1d3_13,13,2,1,1);

    spbx1_fif=new QSpinBox;
    spbx2_fif=new QSpinBox;
    spbx3_fif=new QSpinBox;
    spbx4_fif=new QSpinBox;
    spbx5_fif=new QSpinBox;
    spbx6_fif=new QSpinBox;
    spbx7_fif=new QSpinBox;
    spbx8_fif=new QSpinBox;
    spbx9_fif=new QSpinBox;
    spbx10_fif=new QSpinBox;
    spbx11_fif=new QSpinBox;
    spbx12_fif=new QSpinBox;
    spbx13_fif=new QSpinBox;
    spbx1_fif->setRange(0,9999); //设置范围
    spbx2_fif->setRange(0,9999);
    spbx3_fif->setRange(0,9999);
    spbx4_fif->setRange(0,9999);
    spbx5_fif->setRange(0,9999);
    spbx6_fif->setRange(0,9999);
    spbx7_fif->setRange(0,9999);
    spbx8_fif->setRange(0,9999);
    spbx9_fif->setRange(0,9999);
    spbx10_fif->setRange(0,9999);
    spbx11_fif->setRange(0,9999);
    spbx12_fif->setRange(0,9999);
    spbx13_fif->setRange(0,9999);
    gl3->addWidget(spbx1_fif,1,3,1,1);
    gl3->addWidget(spbx2_fif,2,3,1,1);
    gl3->addWidget(spbx3_fif,3,3,1,1);
    gl3->addWidget(spbx4_fif,4,3,1,1);
    gl3->addWidget(spbx5_fif,5,3,1,1);
    gl3->addWidget(spbx6_fif,6,3,1,1);
    gl3->addWidget(spbx7_fif,7,3,1,1);
    gl3->addWidget(spbx8_fif,8,3,1,1);
    gl3->addWidget(spbx9_fif,9,3,1,1);
    gl3->addWidget(spbx10_fif,10,3,1,1);
    gl3->addWidget(spbx11_fif,11,3,1,1);
    gl3->addWidget(spbx12_fif,12,3,1,1);
    gl3->addWidget(spbx13_fif,13,3,1,1);

    spby1_fif=new QSpinBox;
    spby2_fif=new QSpinBox;
    spby3_fif=new QSpinBox;
    spby4_fif=new QSpinBox;
    spby5_fif=new QSpinBox;
    spby6_fif=new QSpinBox;
    spby7_fif=new QSpinBox;
    spby8_fif=new QSpinBox;
    spby9_fif=new QSpinBox;
    spby10_fif=new QSpinBox;
    spby11_fif=new QSpinBox;
    spby12_fif=new QSpinBox;
    spby13_fif=new QSpinBox;
    spby1_fif->setRange(0,9999);
    spby2_fif->setRange(0,9999);
    spby3_fif->setRange(0,9999);
    spby4_fif->setRange(0,9999);
    spby5_fif->setRange(0,9999);
    spby6_fif->setRange(0,9999);
    spby7_fif->setRange(0,9999);
    spby8_fif->setRange(0,9999);
    spby9_fif->setRange(0,9999);
    spby10_fif->setRange(0,9999);
    spby11_fif->setRange(0,9999);
    spby12_fif->setRange(0,9999);
    spby13_fif->setRange(0,9999);
    gl3->addWidget(spby1_fif,1,4,1,1);
    gl3->addWidget(spby2_fif,2,4,1,1);
    gl3->addWidget(spby3_fif,3,4,1,1);
    gl3->addWidget(spby4_fif,4,4,1,1);
    gl3->addWidget(spby5_fif,5,4,1,1);
    gl3->addWidget(spby6_fif,6,4,1,1);
    gl3->addWidget(spby7_fif,7,4,1,1);
    gl3->addWidget(spby8_fif,8,4,1,1);
    gl3->addWidget(spby9_fif,9,4,1,1);
    gl3->addWidget(spby10_fif,10,4,1,1);
    gl3->addWidget(spby11_fif,11,4,1,1);
    gl3->addWidget(spby12_fif,12,4,1,1);
    gl3->addWidget(spby13_fif,13,4,1,1);

    g3->setLayout(gl3);

    QVBoxLayout *v3b=new QVBoxLayout;
    v3b->addLayout(h3);
    v3b->addLayout(f3);
    v3b->addWidget(g3);

    connect(change3_fif,SIGNAL(activated(int)),this,SLOT(tosersor_continue_fif(int)));
/*
    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_fif()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_fif()));
    connect(lineEdit_continueRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot_fif()));
    connect(lineEdit_continueResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot_fif()));
*/
    w_ContinueField_fif->setLayout(v3b);
    w_ContinueField_fif->resize(300,500);
    w_ContinueField_fif->setWindowTitle("通道5连续视场");
}


void MainWindow::init_resl()
{
    w_choose=new MyWidget;
    w_choose->setWindowTitle(tr("分辨率选择"));

    QPushButton* btn_resolu_confirm=new QPushButton;
    btn_resolu_confirm->setText("确认");

    QLabel *labelspace = new QLabel;
    labelspace->setText("");

    QGridLayout *pLayout = new QGridLayout();
    pLayout->addWidget(labelspace, 0, 0, 1, 8);
    pLayout->addWidget(btn_resolu_confirm, 0, 9, 1, 1);

    //通道1
    rdBtn_aisle1_1=new QRadioButton;
    rdBtn_aisle1_2=new QRadioButton;
    rdBtn_aisle1_3=new QRadioButton;
    rdBtn_aisle1_4=new QRadioButton;

    BG1=new QButtonGroup;
    BG1->addButton(rdBtn_aisle1_1,1);
    BG1->addButton(rdBtn_aisle1_2,2);
    BG1->addButton(rdBtn_aisle1_3,3);
    BG1->addButton(rdBtn_aisle1_4,4);

    QFormLayout *F1=new QFormLayout;
    F1->addRow("1080P@25fps",rdBtn_aisle1_1);
    F1->addRow("1080P@30fps",rdBtn_aisle1_2);
    F1->addRow("720P@50fps",rdBtn_aisle1_3);
    F1->addRow("720P@60fps",rdBtn_aisle1_4);

    //通道2
    rdBtn_aisle2_1=new QRadioButton;
    rdBtn_aisle2_2=new QRadioButton;
    rdBtn_aisle2_3=new QRadioButton;
    rdBtn_aisle2_4=new QRadioButton;


    BG2=new QButtonGroup;
    BG2->addButton(rdBtn_aisle2_1,1);
    BG2->addButton(rdBtn_aisle2_2,2);
    BG2->addButton(rdBtn_aisle2_3,3);
    BG2->addButton(rdBtn_aisle2_4,4);

    QFormLayout *F2=new QFormLayout;
    F2->addRow("1080P@25fps",rdBtn_aisle2_1);
    F2->addRow("1080P@30fps",rdBtn_aisle2_2);
    F2->addRow("720P@50fps",rdBtn_aisle2_3);
    F2->addRow("720P@60fps",rdBtn_aisle2_4);

    //通道3
    rdBtn_aisle3_1=new QRadioButton;
    rdBtn_aisle3_2=new QRadioButton;
    rdBtn_aisle3_3=new QRadioButton;
    rdBtn_aisle3_4=new QRadioButton;

    BG3=new QButtonGroup;
    BG3->addButton(rdBtn_aisle3_1,1);
    BG3->addButton(rdBtn_aisle3_2,2);
    BG3->addButton(rdBtn_aisle3_3,3);
    BG3->addButton(rdBtn_aisle3_4,4);

    QFormLayout *F3=new QFormLayout;
    F3->addRow("1080P@25fps",rdBtn_aisle3_1);
    F3->addRow("1080P@30fps",rdBtn_aisle3_2);
    F3->addRow("720P@50fps",rdBtn_aisle3_3);
    F3->addRow("720P@60fps",rdBtn_aisle3_4);

    //通道4
    rdBtn_aisle4_1=new QRadioButton;
    rdBtn_aisle4_2=new QRadioButton;
    rdBtn_aisle4_3=new QRadioButton;
    rdBtn_aisle4_4=new QRadioButton;

    BG4=new QButtonGroup;
    BG4->addButton(rdBtn_aisle4_1,1);
    BG4->addButton(rdBtn_aisle4_2,2);
    BG4->addButton(rdBtn_aisle4_3,3);
    BG4->addButton(rdBtn_aisle4_4,4);


    QFormLayout *F4=new QFormLayout;
    F4->addRow("1080P@25fps",rdBtn_aisle4_1);
    F4->addRow("1080P@30fps",rdBtn_aisle4_2);
    F4->addRow("720P@50fps",rdBtn_aisle4_3);
    F4->addRow("720P@60fps",rdBtn_aisle4_4);
    //通道5
    rdBtn_aisle5_1=new QRadioButton;
    BG5=new QButtonGroup;
    BG5->addButton(rdBtn_aisle5_1,1);

    QFormLayout *F5=new QFormLayout;
    F5->addRow("720*576i/50Hz",rdBtn_aisle5_1);


    QGroupBox *G1=new QGroupBox;
    G1->setTitle("通道1");
    G1->setLayout(F1);
    QGroupBox *G2=new QGroupBox;
    G2->setTitle("通道2");
    G2->setLayout(F2);
    QGroupBox *G3=new QGroupBox;
    G3->setTitle("通道3");
    G3->setLayout(F3);
    QGroupBox *G4=new QGroupBox;
    G4->setTitle("通道4");
    G4->setLayout(F4);
    QGroupBox *G5=new QGroupBox;
    G5->setTitle("通道5");
    G5->setLayout(F5);


    //通道输出1
    rdBtn_out1_1=new QRadioButton;
    rdBtn_out1_2=new QRadioButton;

    BO1=new QButtonGroup;
    BO1->addButton(rdBtn_out1_1,1);
    BO1->addButton(rdBtn_out1_2,2);

    QFormLayout *FO1=new QFormLayout;
    FO1->addRow("1080P@25fps/30fps",rdBtn_out1_1);
    FO1->addRow("720P@50fps/60fps",rdBtn_out1_2);

    //通道输出2
    rdBtn_out2_1=new QRadioButton;
    rdBtn_out2_2=new QRadioButton;

    BO2=new QButtonGroup;
    BO2->addButton(rdBtn_out2_1,1);
    BO2->addButton(rdBtn_out2_2,2);

    QFormLayout *FO2=new QFormLayout;
    FO2->addRow("1080P@25fps/30fps",rdBtn_out2_1);
    FO2->addRow("720P@50fps/60fps",rdBtn_out2_2);

    //通道输出3
    rdBtn_out3_1=new QRadioButton;
    rdBtn_out3_2=new QRadioButton;

    BO3=new QButtonGroup;
    BO3->addButton(rdBtn_out3_1,1);
    BO3->addButton(rdBtn_out3_2,2);

    QFormLayout *FO3=new QFormLayout;
    FO3->addRow("1080P@25fps/30fps",rdBtn_out3_1);
    FO3->addRow("720P@50fps/60fps",rdBtn_out3_2);

    //通道输出4
    rdBtn_out4_1=new QRadioButton;
    rdBtn_out4_2=new QRadioButton;
    BO4=new QButtonGroup;
    BO4->addButton(rdBtn_out4_1,1);
    BO4->addButton(rdBtn_out4_2,2);

    QFormLayout *FO4=new QFormLayout;
    FO4->addRow("1080P@25fps/30fps",rdBtn_out4_1);
    FO4->addRow("720P@50fps/60fps",rdBtn_out4_2);

    //通道5
    rdBtn_out5_1=new QRadioButton;
    BO5=new QButtonGroup;
    BO5->addButton(rdBtn_out5_1,1);

    QFormLayout *FO5=new QFormLayout;
    FO5->addRow("720*576i/50Hz",rdBtn_out5_1);

    QGroupBox *O1=new QGroupBox;
    O1->setTitle("通道1");
    O1->setLayout(FO1);
    QGroupBox *O2=new QGroupBox;
    O2->setTitle("通道2");
    O2->setLayout(FO2);
    QGroupBox *O3=new QGroupBox;
    O3->setTitle("通道3");
    O3->setLayout(FO3);
    QGroupBox *O4=new QGroupBox;
    O4->setTitle("通道4");
    O4->setLayout(FO4);
    QGroupBox *O5=new QGroupBox;
    O5->setTitle("通道5");
    O5->setLayout(FO5);

    QHBoxLayout *h1=new QHBoxLayout;
    h1->addWidget(G1);
    h1->addWidget(G2);
    h1->addWidget(G3);
    h1->addWidget(G4);
    h1->addWidget(G5);
    QHBoxLayout *h2=new QHBoxLayout;
    h2->addWidget(O1);
    h2->addWidget(O2);
    h2->addWidget(O3);
    h2->addWidget(O4);
    h2->addWidget(O5);

    QGroupBox *G=new QGroupBox;
    G->setTitle("采集/输出分辨率");
    G->setLayout(h1);
//    QGroupBox *O=new QGroupBox;
//    O->setTitle("输出分辨率");
//    O->setLayout(h2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(pLayout);
    v->addWidget(G);
    //=v->addWidget(O);

    w_choose->setLayout(v);
/*
    connect(rdBtn_aisle1_1,SIGNAL(clicked(bool)),this,SLOT(btn_aisle1_Slot()));
    connect(rdBtn_aisle1_2,SIGNAL(clicked(bool)),this,SLOT(btn_aisle1_Slot()));
    connect(rdBtn_aisle1_3,SIGNAL(clicked(bool)),this,SLOT(btn_aisle1_Slot()));
    connect(rdBtn_aisle1_4,SIGNAL(clicked(bool)),this,SLOT(btn_aisle1_Slot()));

    connect(rdBtn_aisle2_1,SIGNAL(clicked(bool)),this,SLOT(btn_aisle2_Slot()));
    connect(rdBtn_aisle2_2,SIGNAL(clicked(bool)),this,SLOT(btn_aisle2_Slot()));
    connect(rdBtn_aisle2_3,SIGNAL(clicked(bool)),this,SLOT(btn_aisle2_Slot()));
    connect(rdBtn_aisle2_4,SIGNAL(clicked(bool)),this,SLOT(btn_aisle2_Slot()));

    connect(rdBtn_aisle3_1,SIGNAL(clicked(bool)),this,SLOT(btn_aisle3_Slot()));
    connect(rdBtn_aisle3_2,SIGNAL(clicked(bool)),this,SLOT(btn_aisle3_Slot()));
    connect(rdBtn_aisle3_3,SIGNAL(clicked(bool)),this,SLOT(btn_aisle3_Slot()));
    connect(rdBtn_aisle3_4,SIGNAL(clicked(bool)),this,SLOT(btn_aisle3_Slot()));

    connect(rdBtn_aisle4_1,SIGNAL(clicked(bool)),this,SLOT(btn_aisle4_Slot()));
    connect(rdBtn_aisle4_2,SIGNAL(clicked(bool)),this,SLOT(btn_aisle4_Slot()));
    connect(rdBtn_aisle4_3,SIGNAL(clicked(bool)),this,SLOT(btn_aisle4_Slot()));
    connect(rdBtn_aisle4_4,SIGNAL(clicked(bool)),this,SLOT(btn_aisle4_Slot()));

    connect(rdBtn_aisle5_1,SIGNAL(clicked(bool)),this,SLOT(btn_aisle5_Slot()));
*/
    connect(btn_resolu_confirm,SIGNAL(clicked(bool)),this,SLOT(btn_resolution_clicked()));
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
    for(int i=1;i<8;i++){
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
    for(int i=1;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x03;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x03;
    send_arr[6]=0x08;
    send_oneframe(3);
    send_mutex.unlock();


    w_plat->show();
    w_plat->show_stat = 1;
}

void MainWindow::showdbgcfg()
{
    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=48;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_dbg->show();
    w_dbg->show_stat = 1;

}

void MainWindow::showspeedconvcfg()
{
    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=49;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<2;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=50;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_speedconv->show();
    w_speedconv->show_stat = 1;
}

void MainWindow::showmtdcfg()
{
    w_mtd->show();
    w_mtd->show_stat = 1;
}

void MainWindow::showCamera()
{
    current_shichang = 0;
    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_sersor1->show();
    w_sersor1->show_stat = 1;

}
void MainWindow::showCamera_sec()
{
    current_shichang_sec = 0;
    /*
    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/
    w_sersor1_sec->show();
    w_sersor1_sec->show_stat = 1;
}
void MainWindow::showCamera_thi()
{
    current_shichang_thi = 0;
    /*
    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/
    w_sersor1_thi->show();
    w_sersor1_thi->show_stat = 1;
}

void MainWindow::showCamera_fou()
{
    current_shichang_fou = 0;
    /*
    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/
    w_sersor1_fou->show();
    w_sersor1_fou->show_stat = 1;
}

void MainWindow::showCamera_fif()
{
    current_shichang_fif = 0;
    /*
    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/
    w_sersor1_fif->show();
    w_sersor1_fif->show_stat = 1;
}

void MainWindow::showAlg()
{

    for(int i=0;i<16;i++){
       send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x04;
        send_arr[6]=i;
        send_oneframe(3);
       send_mutex.unlock();
    }

    utc1->show();
    utc1->show_stat = 1;
}

void MainWindow::showAlg2()
{
    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x05;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    utc2->show();
    utc2->show_stat = 1;
}
void MainWindow::showAlg3()
{
    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x06;
        send_arr[6]=i;
       send_oneframe(3);
        send_mutex.unlock();
    }

    utc3->show();
    utc3->show_stat = 1;
}



void MainWindow::showCapture1()
{
    for(int i=0;i<12;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x2D;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_capture1->show();
    w_capture1->show_stat = 1;

}

void MainWindow::showCapture2()
{
    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x2E;
        send_arr[6]=i;
       send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=6;i<12;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x2E;
        send_arr[6]=i;
       send_oneframe(3);
        send_mutex.unlock();
    }

    w_capture2->show();
    w_capture2->show_stat = 1;
}

void MainWindow::showCapture3()
{
    for(int i=0;i<1;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x2F;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_capture3->show();
    w_capture3->show_stat = 1;
}

void MainWindow::showOther()
{
    w_osd1->setWindowTitle("OSD参数配置");
   
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x00;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x01;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x02;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x03;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x05;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x07;
    send_arr[6]=0x06;
    send_oneframe(3);
    send_mutex.unlock();

    w_osd1->show();
    w_osd1->show_stat = 1;
}
void MainWindow::btnSensor1SwitchSlot()
{
    current_shichang = 1;

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x18;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_seitchField->show();
    w_seitchField->show_stat = 1;
}
void MainWindow::btnSensor1SwitchSlot_sec()
{
    current_shichang_sec = 1;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x18;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_seitchField_sec->show();
    w_seitchField_sec->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_thi()
{
    current_shichang_thi = 1;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x18;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_seitchField_thi->show();
    w_seitchField_thi->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_fou()
{
    current_shichang_fou = 1;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x18;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_seitchField_fou->show();
    w_seitchField_fou->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_fif()
{
    current_shichang_fif = 1;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x18;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_seitchField_fif->show();
    w_seitchField_fif->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot()
{
    current_shichang = 2;

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=25;j<27;j++){
        for(int i=0;i<16;i++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=j;
            send_arr[6]=i;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }

    for(int m=0;m<7;m++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=27;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField->show();
    w_ContinueField->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_sec()
{
    current_shichang_sec = 2;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=25;j<27;j++){
        for(int i=0;i<16;i++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=j;
            send_arr[6]=i;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }

    for(int m=0;m<7;m++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=27;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_ContinueField_sec->show();
    w_ContinueField_sec->show_stat = 1;
}
void MainWindow::btnSensor2ContinueSlot_thi()
{
    current_shichang_thi = 2;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=25;j<27;j++){
        for(int i=0;i<16;i++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=j;
            send_arr[6]=i;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }

    for(int m=0;m<7;m++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=27;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_ContinueField_thi->show();
    w_ContinueField_thi->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_fou()
{
    current_shichang_fou = 2;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=25;j<27;j++){
        for(int i=0;i<16;i++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=j;
            send_arr[6]=i;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }

    for(int m=0;m<7;m++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=27;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_ContinueField_fou->show();
    w_ContinueField_fou->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_fif()
{
    current_shichang_fif = 2;

    /*for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x17;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=25;j<27;j++){
        for(int i=0;i<16;i++){
            send_mutex.lock();
            send_arr[4]=0x31;
            send_arr[5]=j;
            send_arr[6]=i;
            send_oneframe(3);
            send_mutex.unlock();
        }
    }

    for(int m=0;m<7;m++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=27;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }*/

    w_ContinueField_fif->show();
    w_ContinueField_fif->show_stat = 1;
}

void MainWindow::tosersor_fix(int i)
{
    if(i==0)
    {
    }
    else if(i==1)
    {
        w_sersor1->close();
        btnSensor1SwitchSlot();
    }
    else if(i==2)
    {
        w_sersor1->close();
        btnSensor2ContinueSlot();
    }
}
void MainWindow::tosersor_fix_sec(int i)
{
    if(i==0)
    {
    }
    else if(i==1)
    {
        w_sersor1_sec->close();
        btnSensor1SwitchSlot_sec();
    }
    else if(i==2)
    {
        w_sersor1_sec->close();
        btnSensor2ContinueSlot_sec();
    }
}
void MainWindow::tosersor_fix_thi(int i)
{
    if(i==0)
    {
    }
    else if(i==1)
    {
        w_sersor1_thi->close();
        btnSensor1SwitchSlot_thi();
    }
    else if(i==2)
    {
        w_sersor1_thi->close();
        btnSensor2ContinueSlot_thi();
    }
}

void MainWindow::tosersor_fix_fou(int i)
{
    if(i==0)
    {
    }
    else if(i==1)
    {
        w_sersor1_fou->close();
        btnSensor1SwitchSlot_fou();
    }
    else if(i==2)
    {
        w_sersor1_fou->close();
        btnSensor2ContinueSlot_fou();
    }
}

void MainWindow::tosersor_fix_fif(int i)
{
    if(i==0)
    {
    }
    else if(i==1)
    {
        w_sersor1_fif->close();
        btnSensor1SwitchSlot_fif();
    }
    else if(i==2)
    {
        w_sersor1_fif->close();
        btnSensor2ContinueSlot_fif();
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

void MainWindow::toSensor_switch_sec(int i)
{
   if(i==1){
       w_seitchField_sec->close();
       showCamera_sec();

   }else if(i==2){
       w_seitchField_sec->close();;
       btnSensor2ContinueSlot_sec();
   }
}

void MainWindow::toSensor_switch_thi(int i)
{
   if(i==1){
       w_seitchField_thi->close();
       showCamera_thi();

   }else if(i==2){
       w_seitchField_thi->close();;
       btnSensor2ContinueSlot_thi();
   }
}

void MainWindow::toSensor_switch_fou(int i)
{
   if(i==1){
       w_seitchField_fou->close();
       showCamera_fou();

   }else if(i==2){
       w_seitchField_fou->close();;
       btnSensor2ContinueSlot_fou();
   }
}

void MainWindow::toSensor_switch_fif(int i)
{
   if(i==1){
       w_seitchField_fif->close();
       showCamera_fif();

   }else if(i==2){
       w_seitchField_fif->close();;
       btnSensor2ContinueSlot_fif();
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

void MainWindow::tosersor_continue_sec(int i)
{
    if(i==1){
        w_ContinueField_sec->close();
        showCamera_sec();
    }else if(i==2){
        w_ContinueField_sec->close();
        btnSensor1SwitchSlot_sec();
    }
}

void MainWindow::tosersor_continue_thi(int i)
{
    if(i==1){
        w_ContinueField_thi->close();
        showCamera_thi();
    }else if(i==2){
        w_ContinueField_thi->close();
        btnSensor1SwitchSlot_thi();
    }
}

void MainWindow::tosersor_continue_fou(int i)
{
    if(i==1){
        w_ContinueField_fou->close();
        showCamera_fou();
    }else if(i==2){
        w_ContinueField_fou->close();
        btnSensor1SwitchSlot_fou();
    }
}

void MainWindow::tosersor_continue_fif(int i)
{
    if(i==1){
        w_ContinueField_fif->close();
        showCamera_fif();
    }else if(i==2){
        w_ContinueField_fif->close();
        btnSensor1SwitchSlot_fif();
    }
}

void MainWindow::btn_choose_Slot()
{
    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=51;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_choose->show();
    w_choose->show_stat = 1;
}
