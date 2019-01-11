#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSize>



void MainWindow::init_menu()
{
    menu[0]=new QMenu("配置");
    QAction* real_time_output=new QAction("实时输出",this);
    menu[0]->addAction(real_time_output);

    QAction* act_platCfg=new QAction("手柄配置",this);
    menu[0]->addAction(act_platCfg);

    QMenu* videoCfg=new QMenu("摄像机配置");
    QAction* avt_videoCfg1=new QAction("通道1");
    QAction* avt_videoCfg2=new QAction("通道2");
    QAction* avt_videoCfg3=new QAction("通道3");
    QAction* avt_videoCfg4=new QAction("通道4");
    QAction* avt_videoCfg5=new QAction("通道5");
    videoCfg->addAction(avt_videoCfg1);
    videoCfg->addAction(avt_videoCfg2);
    videoCfg->addAction(avt_videoCfg3);
    videoCfg->addAction(avt_videoCfg4);
    videoCfg->addAction(avt_videoCfg5);
    menu[0]->addMenu(videoCfg);
    QMenu* pidsysCfg=new QMenu("PID配置");
        QAction* act_pidCfg1=new QAction("通道1");
        QAction* act_pidCfg2=new QAction("通道2");
        QAction* act_pidCfg3=new QAction("通道3");
        QAction* act_pidCfg4=new QAction("通道4");
        QAction* act_pidCfg5=new QAction("通道5");
        pidsysCfg->addAction(act_pidCfg1);
        pidsysCfg->addAction(act_pidCfg2);
        pidsysCfg->addAction(act_pidCfg3);
        pidsysCfg->addAction(act_pidCfg4);
        pidsysCfg->addAction(act_pidCfg5);
        menu[0]->addMenu(pidsysCfg);

    QMenu* speedconv_sysCfg=new QMenu("转台配置");
        QAction* speedconv=new QAction("通道1",this);
        QAction* speedconv_sec=new QAction("通道2",this);
        QAction* speedconv_thi=new QAction("通道3",this);
        QAction* speedconv_fou=new QAction("通道4",this);
        QAction* speedconv_fif=new QAction("通道5",this);
        speedconv_sysCfg->addAction(speedconv);
        speedconv_sysCfg->addAction(speedconv_sec);
        speedconv_sysCfg->addAction(speedconv_thi);
        speedconv_sysCfg->addAction(speedconv_fou);
        speedconv_sysCfg->addAction(speedconv_fif);
        menu[0]->addMenu(speedconv_sysCfg);

    QMenu* cameracfg=new QMenu("相机配置");
    QAction* act_cmrCfg1=new QAction("通道1",this);
    QAction* act_cmrCfg2=new QAction("通道2",this);
    QAction* act_cmrCfg3=new QAction("通道3",this);
    QAction* act_cmrCfg4=new QAction("通道4",this);
    QAction* act_cmrCfg5=new QAction("通道5",this);
    cameracfg->addAction(act_cmrCfg1);
    cameracfg->addAction(act_cmrCfg2);
    cameracfg->addAction(act_cmrCfg3);
    cameracfg->addAction(act_cmrCfg4);
    cameracfg->addAction(act_cmrCfg5);
    //menu[0]->addMenu(cameracfg);

//    QAction* act_algCfg=new QAction("算法配置");
//    menu[0]->addAction(act_algCfg);
    QMenu *utc=new QMenu("算法配置");
    QAction* act_algCfg1=new QAction("UTC1",this);
    utc->addAction(act_algCfg1);
    QAction* act_algCfg2=new QAction("UTC2",this);
    utc->addAction(act_algCfg2);
    QAction* act_algCfg3=new QAction("UTC3",this);
    utc->addAction(act_algCfg3);
    menu[0]->addMenu(utc);

    QAction* act_othCfg=new QAction("字符叠加",this);
    menu[0]->addAction(act_othCfg);
//    QMenu *osd=new QMenu("OSD配置");
//    QAction* act_othCfg1=new QAction("OSD1");
//    osd->addAction(act_othCfg1);
//    QAction* act_othCfg2=new QAction("OSD2");
//    osd->addAction(act_othCfg2);
//    QAction* act_othCfg3=new QAction("OSD3");
//    osd->addAction(act_othCfg3);
//    menu[0]->addMenu(osd);

   // QMenu* capture=new QMenu("波门配置");
    QAction* act_cap1=new QAction("捕获框",this);
    //capture->addAction(act_cap1);
    QAction* act_cap2=new QAction("波门",this);
    //capture->addAction(act_cap2);
    QAction* act_cap3=new QAction("画线",this);
    //capture->addAction(act_cap3);
    //menu[0]->addMenu(capture);

     QAction* dbg_sysCfg=new QAction("捕获配置",this);
     //menu[0]->addAction(dbg_sysCfg);


     QAction* mtd_sysCfg=new QAction("移动检测配置",this);
     menu[0]->addAction(mtd_sysCfg);

     QAction* act_sysCfg=new QAction("系统配置",this);
     menu[0]->addAction(act_sysCfg);

    QAction* act_rstCfg=new QAction("恢复默认",this);
    menu[0]->addAction(act_rstCfg);

    ui->menuBar->addMenu(menu[0]);

    connect(avt_videoCfg1,SIGNAL(triggered(bool)),this,SLOT(showvedioCfg1()));
    connect(avt_videoCfg2,SIGNAL(triggered(bool)),this,SLOT(showvedioCfg2()));
    connect(avt_videoCfg3,SIGNAL(triggered(bool)),this,SLOT(showvedioCfg3()));
    connect(avt_videoCfg4,SIGNAL(triggered(bool)),this,SLOT(showvedioCfg4()));
    connect(avt_videoCfg5,SIGNAL(triggered(bool)),this,SLOT(showvedioCfg5()));
    connect(act_pidCfg1,SIGNAL(triggered(bool)),this,SLOT(showpidsysCfg1()));
    connect(act_pidCfg2,SIGNAL(triggered(bool)),this,SLOT(showpidsysCfg2()));
    connect(act_pidCfg3,SIGNAL(triggered(bool)),this,SLOT(showpidsysCfg3()));
    connect(act_pidCfg4,SIGNAL(triggered(bool)),this,SLOT(showpidsysCfg4()));
    connect(act_pidCfg5,SIGNAL(triggered(bool)),this,SLOT(showpidsysCfg5()));
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
    connect(speedconv,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg()));
    connect(speedconv_sec,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg_sec()));
    connect(speedconv_thi,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg_thi()));
    connect(speedconv_fou,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg_fou()));
    connect(speedconv_fif,SIGNAL(triggered(bool)),this,SLOT(showspeedconvcfg_fif()));
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

    editsw = new QLineEdit();
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
    pLayout->addRow("软件升级",vlayout1);
    //pLayout->addRow("FPGA升级", vlayout2);
    //pLayout->addRow("导入配置文件", vlayout3);
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
    connect(btnselectsw,SIGNAL(clicked(bool)),this,SLOT(btnselectsw_clicked()));
    w_config->setLayout(pLayout);
}
void MainWindow::init_platCfg()
{
        w_plat=new MyWidget;
        w_plat->setWindowTitle("手柄配置");
        QPushButton* btn_jos_default=new QPushButton;
        QPushButton* btn_jos_update=new QPushButton;
        btn_jos_default->setText("默认");
        btn_jos_update->setText("保存");
        QVBoxLayout *v1=new QVBoxLayout;
        v1->addWidget(btn_jos_default);
        v1->addWidget(btn_jos_update);
        QLabel *label=new QLabel;
        label->setText("手柄配置");
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

       //v->addWidget(gbox_PID);

        //v->addWidget(gbox_plat);

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

void MainWindow::init_pidCfg()
{
    w_pid=new MyWidget;
    w_pid->setWindowTitle("PID配置");
    btn_pid_default=new QPushButton;
    btn_pid_update=new QPushButton;
    btn_pid_default->setText("默认");
    btn_pid_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_pid_default);
    v1->addWidget(btn_pid_update);
    QLabel *label=new QLabel;
    label->setText("通道1");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    kp1_pid=new QLineEdit;
    ki1_pid=new QLineEdit;
    kd1_pid=new QLineEdit;
    k1=new QLineEdit;
    kp2_pid=new QLineEdit;
    ki2_pid=new QLineEdit;
    kd2_pid=new QLineEdit;
    k2=new QLineEdit;

    gbox_PID = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s[0],kp1_pid);
    f2->addRow(pid_s[1],ki1_pid);
    f2->addRow(pid_s[2],kd1_pid);
    f2->addRow(pid_s[3],k1);
    f2->addRow(pid_s[4],kp2_pid);
    f2->addRow(pid_s[5],ki2_pid);
    f2->addRow(pid_s[6],kd2_pid);
    f2->addRow(pid_s[7],k2);
    gbox_PID->setTitle("PID");
    gbox_PID->setLayout(f2);

    regulator_pid=new QGroupBox();
    regulator_pid->setTitle("比例调节器");
    kx_lineEdt=new QLineEdit;
    ky_lineEdt=new QLineEdit;
    x_ratio_control =new QLineEdit;
    y_ratio_control =new QLineEdit;
    errx_lineEdt=new QLineEdit;
    erry_lineEdt=new QLineEdit;
    time_lineEdt=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s1[0],kx_lineEdt);
    f3->addRow(dbg_s1[1],ky_lineEdt);
    f3->addRow(dbg_s1[2],x_ratio_control);
    f3->addRow(dbg_s1[3],y_ratio_control);
    f3->addRow(dbg_s1[4],errx_lineEdt);
    f3->addRow(dbg_s1[5],erry_lineEdt);
    f3->addRow(dbg_s1[6],time_lineEdt);
    regulator_pid->setLayout(f3);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_PID);
    v->addWidget(regulator_pid);
    w_pid->setLayout(v);

    connect(btn_pid_default,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Default_Slot()));
    connect(btn_pid_update,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Updata_Slot()));
    connect(kp1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot()));
    connect(ki1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot()));
    connect(kd1_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot()));
    connect(k1,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot()));
    connect(kp2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot()));
    connect(ki2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot()));
    connect(kd2_pid,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot()));
    connect(k2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot()));

   // connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
   // connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(kx_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot()));
    connect(ky_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot()));
    connect(x_ratio_control,SIGNAL(returnPressed()),this,SLOT(x_ratio_control_Slot()));
    connect(y_ratio_control,SIGNAL(returnPressed()),this,SLOT(y_ratio_control_Slot()));

    connect(errx_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot()));
    connect(erry_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot()));
    connect(time_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot()));
}
void MainWindow::init_pidCfg2()
{
    w_pid2=new MyWidget;
    w_pid2->setWindowTitle("PID配置");
    btn_pid_default2=new QPushButton;
    btn_pid_update2=new QPushButton;
    btn_pid_default2->setText("默认");
    btn_pid_update2->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_pid_default2);
    v1->addWidget(btn_pid_update2);
    QLabel *label=new QLabel;
    label->setText("通道2");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    kp1_pid2=new QLineEdit;
    ki1_pid2=new QLineEdit;
    kd1_pid2=new QLineEdit;
    k12=new QLineEdit;
    kp2_pid2=new QLineEdit;
    ki2_pid2=new QLineEdit;
    kd2_pid2=new QLineEdit;
    k22=new QLineEdit;

    gbox_PID2 = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s2[0],kp1_pid2);
    f2->addRow(pid_s2[1],ki1_pid2);
    f2->addRow(pid_s2[2],kd1_pid2);
    f2->addRow(pid_s2[3],k12);
    f2->addRow(pid_s2[4],kp2_pid2);
    f2->addRow(pid_s2[5],ki2_pid2);
    f2->addRow(pid_s2[6],kd2_pid2);
    f2->addRow(pid_s2[7],k22);
    gbox_PID2->setTitle("PID");
    gbox_PID2->setLayout(f2);

    regulator_pid2=new QGroupBox();
    regulator_pid2->setTitle("比例调节器");
    kx_lineEdt2=new QLineEdit;
    ky_lineEdt2=new QLineEdit;
    x_ratio_control2 =new QLineEdit;
    y_ratio_control2 =new QLineEdit;
    errx_lineEdt2=new QLineEdit;
    erry_lineEdt2=new QLineEdit;
    time_lineEdt2=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s2[0],kx_lineEdt2);
    f3->addRow(dbg_s2[1],ky_lineEdt2);
    f3->addRow(dbg_s2[2],x_ratio_control2);
    f3->addRow(dbg_s2[3],y_ratio_control2);
    f3->addRow(dbg_s2[4],errx_lineEdt2);
    f3->addRow(dbg_s2[5],erry_lineEdt2);
    f3->addRow(dbg_s2[6],time_lineEdt2);
    regulator_pid2->setLayout(f3);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_PID2);
    v->addWidget(regulator_pid2);
    w_pid2->setLayout(v);

    connect(btn_pid_default2,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Default_Slot2()));
    connect(btn_pid_update2,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Updata_Slot2()));
    connect(kp1_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot2()));
    connect(ki1_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot2()));
    connect(kd1_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot2()));
    connect(k12,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot2()));
    connect(kp2_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot2()));
    connect(ki2_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot2()));
    connect(kd2_pid2,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot2()));
    connect(k22,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot2()));

   // connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
   // connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(x_ratio_control2,SIGNAL(returnPressed()),this,SLOT(x_ratio_control_Slot2()));
    connect(y_ratio_control2,SIGNAL(returnPressed()),this,SLOT(y_ratio_control_Slot2()));
    connect(kx_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot2()));
    connect(ky_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot2()));
    connect(errx_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot2()));
    connect(erry_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot2()));
    connect(time_lineEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot2()));
}
void MainWindow::init_pidCfg3()
{
    w_pid3=new MyWidget;
    w_pid3->setWindowTitle("PID配置");
    btn_pid_default3=new QPushButton;
    btn_pid_update3=new QPushButton;
    btn_pid_default3->setText("默认");
    btn_pid_update3->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_pid_default3);
    v1->addWidget(btn_pid_update3);
    QLabel *label=new QLabel;
    label->setText("通道3");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    kp1_pid3=new QLineEdit;
    ki1_pid3=new QLineEdit;
    kd1_pid3=new QLineEdit;
    k13=new QLineEdit;
    kp2_pid3=new QLineEdit;
    ki2_pid3=new QLineEdit;
    kd2_pid3=new QLineEdit;
    k23=new QLineEdit;

    gbox_PID3 = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s3[0],kp1_pid3);
    f2->addRow(pid_s3[1],ki1_pid3);
    f2->addRow(pid_s3[2],kd1_pid3);
    f2->addRow(pid_s3[3],k13);
    f2->addRow(pid_s3[4],kp2_pid3);
    f2->addRow(pid_s3[5],ki2_pid3);
    f2->addRow(pid_s3[6],kd2_pid3);
    f2->addRow(pid_s3[7],k23);
    gbox_PID3->setTitle("PID");
    gbox_PID3->setLayout(f2);

    regulator_pid3=new QGroupBox();
    regulator_pid3->setTitle("比例调节器");
    kx_lineEdt3=new QLineEdit;
    ky_lineEdt3=new QLineEdit;
    x_ratio_control3 =new QLineEdit;
    y_ratio_control3 =new QLineEdit;
    errx_lineEdt3=new QLineEdit;
    erry_lineEdt3=new QLineEdit;
    time_lineEdt3=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s3[0],kx_lineEdt3);
    f3->addRow(dbg_s3[1],ky_lineEdt3);
    f3->addRow(dbg_s3[2],x_ratio_control3);
    f3->addRow(dbg_s3[3],y_ratio_control3);
    f3->addRow(dbg_s3[4],errx_lineEdt3);
    f3->addRow(dbg_s3[5],erry_lineEdt3);
    f3->addRow(dbg_s3[6],time_lineEdt3);
    regulator_pid3->setLayout(f3);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_PID3);
    v->addWidget(regulator_pid3);
    w_pid3->setLayout(v);

    connect(btn_pid_default3,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Default_Slot3()));
    connect(btn_pid_update3,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Updata_Slot3()));
    connect(kp1_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot3()));
    connect(ki1_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot3()));
    connect(kd1_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot3()));
    connect(k13,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot3()));
    connect(kp2_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot3()));
    connect(ki2_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot3()));
    connect(kd2_pid3,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot3()));
    connect(k23,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot3()));

   // connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
   // connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(x_ratio_control3,SIGNAL(returnPressed()),this,SLOT(x_ratio_control_Slot3()));
    connect(y_ratio_control3,SIGNAL(returnPressed()),this,SLOT(y_ratio_control_Slot3()));
    connect(kx_lineEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot3()));
    connect(ky_lineEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot3()));
    connect(errx_lineEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot3()));
    connect(erry_lineEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot3()));
    connect(time_lineEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot3()));
}
void MainWindow::init_pidCfg4()
{
    w_pid4=new MyWidget;
    w_pid4->setWindowTitle("PID配置");
    btn_pid_default4=new QPushButton;
    btn_pid_update4=new QPushButton;
    btn_pid_default4->setText("默认");
    btn_pid_update4->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_pid_default4);
    v1->addWidget(btn_pid_update4);
    QLabel *label=new QLabel;
    label->setText("通道4");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    kp1_pid4=new QLineEdit;
    ki1_pid4=new QLineEdit;
    kd1_pid4=new QLineEdit;
    k14=new QLineEdit;
    kp2_pid4=new QLineEdit;
    ki2_pid4=new QLineEdit;
    kd2_pid4=new QLineEdit;
    k24=new QLineEdit;

    gbox_PID4 = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s4[0],kp1_pid4);
    f2->addRow(pid_s4[1],ki1_pid4);
    f2->addRow(pid_s4[2],kd1_pid4);
    f2->addRow(pid_s4[3],k14);
    f2->addRow(pid_s4[4],kp2_pid4);
    f2->addRow(pid_s4[5],ki2_pid4);
    f2->addRow(pid_s4[6],kd2_pid4);
    f2->addRow(pid_s4[7],k24);
    gbox_PID4->setTitle("PID");
    gbox_PID4->setLayout(f2);

    regulator_pid4=new QGroupBox();
    regulator_pid4->setTitle("比例调节器");
    kx_lineEdt4=new QLineEdit;
    ky_lineEdt4=new QLineEdit;
    x_ratio_control4 =new QLineEdit;
    y_ratio_control4 =new QLineEdit;
    errx_lineEdt4=new QLineEdit;
    erry_lineEdt4=new QLineEdit;
    time_lineEdt4=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s4[0],kx_lineEdt4);
    f3->addRow(dbg_s4[1],ky_lineEdt4);
    f3->addRow(dbg_s4[2],x_ratio_control4);
    f3->addRow(dbg_s4[3],y_ratio_control4);
    f3->addRow(dbg_s4[4],errx_lineEdt4);
    f3->addRow(dbg_s4[5],erry_lineEdt4);
    f3->addRow(dbg_s4[6],time_lineEdt4);
    regulator_pid4->setLayout(f3);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_PID4);
    v->addWidget(regulator_pid4);
    w_pid4->setLayout(v);

    connect(btn_pid_default4,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Default_Slot4()));
    connect(btn_pid_update4,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Updata_Slot4()));
    connect(kp1_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot4()));
    connect(ki1_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot4()));
    connect(kd1_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot4()));
    connect(k14,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot4()));
    connect(kp2_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot4()));
    connect(ki2_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot4()));
    connect(kd2_pid4,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot4()));
    connect(k24,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot4()));

   // connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
   // connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(x_ratio_control4,SIGNAL(returnPressed()),this,SLOT(x_ratio_control_Slot4()));
    connect(y_ratio_control4,SIGNAL(returnPressed()),this,SLOT(y_ratio_control_Slot4()));
    connect(kx_lineEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot4()));
    connect(ky_lineEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot4()));
    connect(errx_lineEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot4()));
    connect(erry_lineEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot4()));
    connect(time_lineEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot4()));
}
void MainWindow::init_pidCfg5()
{
    w_pid5=new MyWidget;
    w_pid5->setWindowTitle("PID配置");
    btn_pid_default5=new QPushButton;
    btn_pid_update5=new QPushButton;
    btn_pid_default5->setText("默认");
    btn_pid_update5->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_pid_default5);
    v1->addWidget(btn_pid_update5);
    QLabel *label=new QLabel;
    label->setText("通道5");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);
    kp1_pid5=new QLineEdit;
    ki1_pid5=new QLineEdit;
    kd1_pid5=new QLineEdit;
    k15=new QLineEdit;
    kp2_pid5=new QLineEdit;
    ki2_pid5=new QLineEdit;
    kd2_pid5=new QLineEdit;
    k25=new QLineEdit;

    gbox_PID5 = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(pid_s5[0],kp1_pid5);
    f2->addRow(pid_s5[1],ki1_pid5);
    f2->addRow(pid_s5[2],kd1_pid5);
    f2->addRow(pid_s5[3],k15);
    f2->addRow(pid_s5[4],kp2_pid5);
    f2->addRow(pid_s5[5],ki2_pid5);
    f2->addRow(pid_s5[6],kd2_pid5);
    f2->addRow(pid_s5[7],k25);
    gbox_PID5->setTitle("PID");
    gbox_PID5->setLayout(f2);

    regulator_pid5=new QGroupBox();
    regulator_pid5->setTitle("比例调节器");
    kx_lineEdt5=new QLineEdit;
    ky_lineEdt5=new QLineEdit;
    x_ratio_control5 =new QLineEdit;
    y_ratio_control5 =new QLineEdit;
    errx_lineEdt5=new QLineEdit;
    erry_lineEdt5=new QLineEdit;
    time_lineEdt5=new QLineEdit;
    QFormLayout *f3=new QFormLayout();
    f3->addRow(dbg_s5[0],kx_lineEdt5);
    f3->addRow(dbg_s5[1],ky_lineEdt5);
    f3->addRow(dbg_s5[2],x_ratio_control5);
    f3->addRow(dbg_s5[3],y_ratio_control5);
    f3->addRow(dbg_s5[4],errx_lineEdt5);
    f3->addRow(dbg_s5[5],erry_lineEdt5);
    f3->addRow(dbg_s5[6],time_lineEdt5);
    regulator_pid5->setLayout(f3);


    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addWidget(gbox_PID5);
    v->addWidget(regulator_pid5);
    w_pid5->setLayout(v);

    connect(btn_pid_default5,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Default_Slot5()));
    connect(btn_pid_update5,SIGNAL(clicked(bool)),this,SLOT(btn_pid_Updata_Slot5()));
    connect(kp1_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID1_Slot5()));
    connect(ki1_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID2_Slot5()));
    connect(kd1_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID3_Slot5()));
    connect(k15,SIGNAL(returnPressed()),this,SLOT(lEdt_PID4_Slot5()));
    connect(kp2_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID5_Slot5()));
    connect(ki2_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID6_Slot5()));
    connect(kd2_pid5,SIGNAL(returnPressed()),this,SLOT(lEdt_PID7_Slot5()));
    connect(k25,SIGNAL(returnPressed()),this,SLOT(lEdt_PID8_Slot5()));

   // connect(bleedx_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat1_Slot()));
   // connect(bleedy_plat,SIGNAL(returnPressed()),this,SLOT(lEdt_plat2_Slot()));
    connect(x_ratio_control5,SIGNAL(returnPressed()),this,SLOT(x_ratio_control_Slot5()));
    connect(y_ratio_control5,SIGNAL(returnPressed()),this,SLOT(y_ratio_control_Slot5()));
    connect(kx_lineEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_kx_Slot5()));
    connect(ky_lineEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_ky_Slot5()));
    connect(errx_lineEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_errx_Slot5()));
    connect(erry_lineEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_erry_Slot5()));
    connect(time_lineEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_time_Slot5()));
}

void MainWindow::init_vedioCfg()
{
    /*固定视场*/
    w_sersor_1 = new MyWidget;
    w_seitchField_1 = new MyWidget;
    w_ContinueField_1=new MyWidget;
    w_sersor_1->setWindowTitle("摄像机配置");
    btn_vediosersor_fix_default=new QPushButton;
    btn_vediosersor_fix_update=new QPushButton;
    btn_vediosersor_fix_default->setText("默认");
    btn_vediosersor_fix_update->setText("保存");
    QVBoxLayout *v11=new QVBoxLayout;
    v11->addWidget(btn_vediosersor_fix_default);
    v11->addWidget(btn_vediosersor_fix_update);
    QLabel *label30=new QLabel;
    label30->setText("通道1");
    QHBoxLayout *h11=new QHBoxLayout;
    h11->addLayout(v11);
    h11->addWidget(label30);

    fixChanelNum = new  QCheckBox();
    fixChanelNum->setText("通道号");
    fixchanelname = new QLineEdit;
    fixenable = new  QCheckBox();
    fixenable->setText("使能");
    QLabel *label40=new QLabel;
    label40->setText("通道名称");
    QHBoxLayout *v21=new QHBoxLayout;
    v21->addWidget(fixChanelNum);
    v21->addWidget(label40);
    v21->addWidget(fixchanelname);
    v21->addWidget(fixenable);

    fix_vediohaveornot = new  QCheckBox();
    fix_vedio_dpi = new QComboBox;
    fix_xy_ratio = new QLineEdit;
    fix_vedio_dpi->addItem("1080P@25HZ");
    fix_vedio_dpi->addItem("1080P@30HZ");
    //fix_vedio_dpi->addItem("1080P@60HZ");
    fix_vedio_dpi->addItem("720P@50HZ");
    fix_vedio_dpi->addItem("720P@60HZ");
    vedio_change1 = new QComboBox;
    vedio_change1->addItem("固定视场");
    vedio_change1->addItem("可切换视场");
    vedio_change1->addItem("连续视场");
    fix_vediochoose = new QGroupBox();
    QFormLayout *f4=new QFormLayout();
    f4->addRow(vedio_s[0],fix_vediohaveornot);
    f4->addRow(vedio_s[1],fix_vedio_dpi);
    f4->addRow(vedio_s[2],vedio_change1);
    f4->addRow(vedio_s[3],fix_xy_ratio);
    fix_vediochoose->setLayout(f4);

    fix_gateshow = new  QCheckBox();
    fix_bullshow = new  QCheckBox();
    fix_gateshow->setText("波门显示");
    fix_bullshow->setText("靶心显示");
    QHBoxLayout *v6=new QHBoxLayout;
    v6->addWidget(fix_gateshow);
    v6->addWidget(fix_bullshow);

    fix_autogate = new  QCheckBox();
    fix_autogate->setText("自动波门");

    QLabel *label51=new QLabel;
    label51->setText("波门尺寸X");
    QLabel *label52=new QLabel;
    label52->setText("波门尺寸Y");
    QLabel *label53=new QLabel;
    label53->setText("波门位置X");
    QLabel *label54=new QLabel;
    label54->setText("波门位置Y");
    fix_gate_sizex=new QLineEdit;
    fix_gate_sizey=new QLineEdit;
    fix_gatelocationx=new QLineEdit;
    fix_gatelocationy=new QLineEdit;
    QGridLayout *gl1=new QGridLayout;
    gl1->addWidget(label51,0,0);
    gl1->addWidget(fix_gate_sizex,0,1);
    gl1->addWidget(label52,0,3);
    gl1->addWidget(fix_gate_sizey,0,4);
    gl1->addWidget(label53,1,0);
    gl1->addWidget(fix_gatelocationx,1,1);
    gl1->addWidget(label54,1,3);
    gl1->addWidget(fix_gatelocationy,1,4);
    //2.10新增
     QGridLayout *gl12=new QGridLayout;
    set_azimuth =new QPushButton;
    set_pitch =new QPushButton;
    set_zoom  =new QPushButton;
    search_azimuth=new QPushButton;
    search_pitch=new QPushButton;
    search_zoom=new QPushButton;
    set_azimuth->setText("设置");
    set_pitch->setText("设置");
    set_zoom->setText("设置");
    search_azimuth->setText("查询");
    search_pitch->setText("查询");
    search_zoom->setText("查询");

    QLabel *labela=new QLabel;
    labela->setText("方位角");
    QLabel *labelp=new QLabel;
    labelp->setText("俯仰角");
    QLabel *labelz=new QLabel;
    labelz->setText("zoom位置");
    ledt_set_azimuth=new QLineEdit;
    ledt_set_pitch=new QLineEdit;
    ledt_set_zoom=new QLineEdit;

    ledt_search_azimuth=new QLineEdit;
    ledt_search_pitch=new QLineEdit;
    ledt_search_zoom=new QLineEdit;

    gl12->addWidget(labela,1,0,1,1);
    gl12->addWidget(labelp,2,0,1,1);
    gl12->addWidget(labelz,3,0,1,1);


    gl12->addWidget(ledt_set_azimuth,1,2,1,1);
    gl12->addWidget(ledt_set_pitch,2,2,1,1);
    gl12->addWidget(ledt_set_zoom,3,2,1,1);

    gl12->addWidget(set_azimuth,1,3,1,1);
    gl12->addWidget(set_pitch,2,3,1,1);
    gl12->addWidget(set_zoom,3,3,1,1);
    gl12->addWidget(ledt_search_azimuth,1,4,1,1);
    gl12->addWidget(ledt_search_pitch,2,4,1,1);
    gl12->addWidget(ledt_search_zoom,3,4,1,1);

    gl12->addWidget(search_azimuth,1,5,1,1);
    gl12->addWidget(search_pitch,2,5,1,1);
    gl12->addWidget(search_zoom,3,5,1,1);
//

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");
    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l15=new QLabel;
    l15->setText("垂直视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");
    fix_lEdt=new QLineEdit;
    fix_vertical=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    QLabel* l1v=new QLabel;
    l1v->setText("度");
    fix_sp=new QSpinBox;
    fix_sp2=new QSpinBox;
    fix_sp->setRange(0,9999);
    fix_sp2->setRange(0,9999);
    QGridLayout *gl3=new QGridLayout;
    gl3->addWidget(l11,0,0,1,1);
    gl3->addWidget(l14,0,1,1,1);

    gl3->addWidget(l15,0,2,1,1);
    gl3->addWidget(l14,0,3,1,1);

    gl3->addWidget(l14,0,4,1,1);
    gl3->addWidget(l12,0,5,1,1);
    gl3->addWidget(l13,0,6,1,1);
    gl3->addWidget(l14,0,7,1,1);
    gl3->addWidget(fix_lEdt,1,0,1,1);
    gl3->addWidget(l1d,1,1,1,1);
    gl3->addWidget(fix_vertical,1,2,1,1);
    gl3->addWidget(l1v,1,3,1,1);
    gl3->addWidget(l14,1,4,1,1);
    gl3->addWidget(fix_sp,1,5,1,1);
    gl3->addWidget(fix_sp2,1,6,1,1);
    g->setLayout(gl3);

    QVBoxLayout *v0=new QVBoxLayout;
    v0->addLayout(h11);
    v0->addLayout(v21);
    v0->addWidget(fix_vediochoose);
    v0->addLayout(v6);
    v0->addWidget(fix_autogate);
    v0->addLayout(gl1);
    v0->addLayout(gl12);
    v0->addWidget(g);
    w_sersor_1->setLayout(v0);

    connect(vedio_change1,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix(int)));
    connect(btn_vediosersor_fix_default,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot()));
    connect(btn_vediosersor_fix_update,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot()));
    connect(fixChanelNum,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot(int)));
    connect(fixchanelname,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot(int)));
    connect(fixenable,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot(int)));
    connect(fix_vediohaveornot,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot(int)));
    connect(fix_vedio_dpi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot(int)));
    connect(fix_xy_ratio,SIGNAL(returnPressed()),this,SLOT(fix_xy_ratio_Slot()));
    connect(fix_gateshow,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot(int)));
    connect(fix_bullshow,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot(int)));
    connect(fix_autogate,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot(int)));
    connect(fix_gate_sizex,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot()));
    connect(fix_gate_sizey,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot()));
    connect(fix_gatelocationx,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot()));
    connect(fix_gatelocationy,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot()));
    connect(set_azimuth,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot()));
    connect(set_pitch,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot()));
    connect(set_zoom,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot()));
    connect(search_azimuth,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot()));
    connect(search_pitch ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot()));
    connect(search_zoom,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot()));
   // connect(ledt_set_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_set_azimuth_Slot()));
   // connect(ledt_set_pitch,SIGNAL(activated(int)),this,SLOT(ledt_set_pitch_Slot()));
   // connect(ledt_set_zoom,SIGNAL(activated(int)),this,SLOT(ledt_set_zoom_Slot()));
   // connect(ledt_search_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_search_azimuth_Slot()));
   // connect(ledt_search_pitch,SIGNAL(activated(int)),this,SLOT(ledt_search_pitch_Slot()));
   // connect(ledt_search_zoom,SIGNAL(activated(int)),this,SLOT(ledt_search_zoom_Slot()));
    connect(fix_lEdt,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(fix_vertical,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(fix_sp,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(fix_sp2,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));

    /*可切换视场*/
    w_seitchField_1->setWindowTitle("摄像机配置");
    btn_vediosersor_default=new QPushButton;
    btn_vediosersor_update=new QPushButton;
    btn_vediosersor_default->setText("默认");
    btn_vediosersor_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_vediosersor_default);
    v1->addWidget(btn_vediosersor_update);
    QLabel *label1=new QLabel;
    label1->setText("通道1");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label1);

    ChanelNum = new  QCheckBox();
    ChanelNum->setText("通道号");
    chanelname = new QLineEdit;
    enable = new  QCheckBox();
    enable->setText("使能");

    QLabel *label2=new QLabel;
    label2->setText("通道名称");
    QHBoxLayout *v2=new QHBoxLayout;
    v2->addWidget(ChanelNum);
    v2->addWidget(label2);
    v2->addWidget(chanelname);
    v2->addWidget(enable);

    vediohaveornot = new  QCheckBox();
    vedio_dpi = new QComboBox;
    xy_ratio = new QLineEdit;
    vedio_dpi->addItem("1080P@25HZ");
    vedio_dpi->addItem("1080P@30HZ");
    vedio_dpi->addItem("1080P@60HZ");
    vedio_dpi->addItem("720P@50HZ");
    vedio_dpi->addItem("720P@60HZ");
    vedio_change2 = new QComboBox;
    vedio_change2->addItem("可切换视场");
    vedio_change2->addItem("固定视场");
    vedio_change2->addItem("连续视场");

    vediochoose = new QGroupBox();
    QFormLayout *f3=new QFormLayout();
    f3->addRow(vedio_s[0],vediohaveornot);
    f3->addRow(vedio_s[1],vedio_dpi);
    f3->addRow(vedio_s[2],vedio_change2);
    f3->addRow(vedio_s[3],xy_ratio);
    vediochoose->setLayout(f3);

    connect(vedio_change2,SIGNAL(activated(int)),this,SLOT(vedio_toSensor_switch(int)));
    gateshow = new  QCheckBox();
    bullshow = new  QCheckBox();
    gateshow->setText("波门显示");
    bullshow->setText("靶心显示");
    QHBoxLayout *v3=new QHBoxLayout;
    v3->addWidget(gateshow);
    v3->addWidget(bullshow);

    autogate = new  QCheckBox();
    autogate->setText("自动波门");

    QLabel *label3=new QLabel;
    label3->setText("波门尺寸X");
    QLabel *label4=new QLabel;
    label4->setText("波门尺寸Y");
    QLabel *label5=new QLabel;
    label5->setText("波门位置X");
    QLabel *label6=new QLabel;
    label6->setText("波门位置Y");
    gate_sizex=new QLineEdit;
    gate_sizey=new QLineEdit;
    gatelocationx=new QLineEdit;
    gatelocationy=new QLineEdit;
    QGridLayout *gl=new QGridLayout;
    gl->addWidget(label3,0,0);
    gl->addWidget(gate_sizex,0,1);
    gl->addWidget(label4,0,3);
    gl->addWidget(gate_sizey,0,4);
    gl->addWidget(label5,1,0);
    gl->addWidget(gatelocationx,1,1);
    gl->addWidget(label6,1,3);
    gl->addWidget(gatelocationy,1,4);

    QHBoxLayout *h2=new QHBoxLayout;
    QLabel *label7=new QLabel;
    label7->setText("测试现场等级");
    vedio_fovclass = new QComboBox;
    vedio_fovclass->addItem("可切换视场1");
    vedio_fovclass->addItem("可切换视场2");
    vedio_fovclass->addItem("可切换视场3");
    vedio_fovclass->addItem("可切换视场4");
    vedio_fovclass->addItem("可切换视场5");
    h2->addWidget(label7);
    h2->addWidget(vedio_fovclass);
    //

    QGridLayout *glc2=new QGridLayout;
   Change_set_azimuth =new QPushButton;
   Change_set_pitch =new QPushButton;
   Change_set_zoom  =new QPushButton;
   Change_search_azimuth=new QPushButton;
   Change_search_pitch=new QPushButton;
   Change_search_zoom=new QPushButton;
   Change_set_azimuth->setText("设置");
   Change_set_pitch->setText("设置");
   Change_set_zoom->setText("设置");
   Change_search_azimuth->setText("查询");
   Change_search_pitch->setText("查询");
   Change_search_zoom->setText("查询");

   Change_ledt_set_azimuth=new QLineEdit;
   Change_ledt_set_pitch=new QLineEdit;
   Change_ledt_set_zoom=new QLineEdit;

   Change_ledt_search_azimuth=new QLineEdit;
   Change_ledt_search_pitch=new QLineEdit;
   Change_ledt_search_zoom=new QLineEdit;

   QLabel *labelac=new QLabel;
   labelac->setText("方位角");
   QLabel *labelpc=new QLabel;
   labelpc->setText("俯仰角");
   QLabel *labelzc=new QLabel;
   labelzc->setText("zoom位置");

   glc2->addWidget(labelac,1,0,1,1);
   glc2->addWidget(labelpc,2,0,1,1);
   glc2->addWidget(labelzc,3,0,1,1);


   glc2->addWidget(Change_ledt_set_azimuth,1,2,1,1);
   glc2->addWidget(Change_ledt_set_pitch,2,2,1,1);
   glc2->addWidget(Change_ledt_set_zoom,3,2,1,1);

   glc2->addWidget(Change_set_azimuth,1,3,1,1);
   glc2->addWidget(Change_set_pitch,2,3,1,1);
   glc2->addWidget(Change_set_zoom,3,3,1,1);
   glc2->addWidget(Change_ledt_search_azimuth,1,4,1,1);
   glc2->addWidget(Change_ledt_search_pitch,2,4,1,1);
   glc2->addWidget(Change_ledt_search_zoom,3,4,1,1);

   glc2->addWidget(Change_search_azimuth,1,5,1,1);
   glc2->addWidget(Change_search_pitch,2,5,1,1);
   glc2->addWidget(Change_search_zoom,3,5,1,1);


    //

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");
    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l25=new QLabel;
    l25->setText("垂直视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l25,0,3,1,1);
    gl2->addWidget(l22,0,5,1,1);
    gl2->addWidget(l23,0,6,1,1);
    gl2->addWidget(l24,0,7,1,1);

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
    vedio_s1_Fov0=new QLineEdit;
    vedio_s1_Fov1=new QLineEdit;
    vedio_s1_Fov2=new QLineEdit;
    vedio_s1_Fov3=new QLineEdit;
    vedio_s1_Fov4=new QLineEdit;
    gl2->addWidget(vedio_s1_Fov0,1,1,1,1);
    gl2->addWidget(vedio_s1_Fov1,2,1,1,1);
    gl2->addWidget(vedio_s1_Fov2,3,1,1,1);
    gl2->addWidget(vedio_s1_Fov3,4,1,1,1);
    gl2->addWidget(vedio_s1_Fov4,5,1,1,1);

    Change_vertical1=new QLineEdit;
    Change_vertical2=new QLineEdit;
    Change_vertical3=new QLineEdit;
    Change_vertical4=new QLineEdit;
    Change_vertical5=new QLineEdit;
    gl2->addWidget(Change_vertical1,1,3,1,1);
    gl2->addWidget(Change_vertical2,2,3,1,1);
    gl2->addWidget(Change_vertical3,3,3,1,1);
    gl2->addWidget(Change_vertical4,4,3,1,1);
    gl2->addWidget(Change_vertical5,5,3,1,1);

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

    QLabel* l1c21=new QLabel;
    QLabel* l1c22=new QLabel;
    QLabel* l1c23=new QLabel;
    QLabel* l1c24=new QLabel;
    QLabel* l1c25=new QLabel;
    l1c21->setText("度");
    l1c22->setText("度");
    l1c23->setText("度");
    l1c24->setText("度");
    l1c25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    gl2->addWidget(l1c21,1,4,1,1);
    gl2->addWidget(l1c22,2,4,1,1);
    gl2->addWidget(l1c23,3,4,1,1);
    gl2->addWidget(l1c24,4,4,1,1);
    gl2->addWidget(l1c25,5,4,1,1);


    vedio_spbx_switch1=new QSpinBox;
    vedio_spbx_switch2=new QSpinBox;
    vedio_spbx_switch3=new QSpinBox;
    vedio_spbx_switch4=new QSpinBox;
    vedio_spbx_switch5=new QSpinBox;
    vedio_spbx_switch1->setRange(0,9999);
    vedio_spbx_switch2->setRange(0,9999);
    vedio_spbx_switch3->setRange(0,9999);
    vedio_spbx_switch4->setRange(0,9999);
    vedio_spbx_switch5->setRange(0,9999);
    gl2->addWidget(vedio_spbx_switch1,1,5,1,1);
    gl2->addWidget(vedio_spbx_switch2,2,5,1,1);
    gl2->addWidget(vedio_spbx_switch3,3,5,1,1);
    gl2->addWidget(vedio_spbx_switch4,4,5,1,1);
    gl2->addWidget(vedio_spbx_switch5,5,5,1,1);

    vedio_spby_switch1=new QSpinBox;
    vedio_spby_switch2=new QSpinBox;
    vedio_spby_switch3=new QSpinBox;
    vedio_spby_switch4=new QSpinBox;
    vedio_spby_switch5=new QSpinBox;
    vedio_spby_switch1->setRange(0,9999);
    vedio_spby_switch2->setRange(0,9999);
    vedio_spby_switch3->setRange(0,9999);
    vedio_spby_switch4->setRange(0,9999);
    vedio_spby_switch5->setRange(0,9999);
    gl2->addWidget(vedio_spby_switch1,1,6,1,1);
    gl2->addWidget(vedio_spby_switch2,2,6,1,1);
    gl2->addWidget(vedio_spby_switch3,3,6,1,1);
    gl2->addWidget(vedio_spby_switch4,4,6,1,1);
    gl2->addWidget(vedio_spby_switch5,5,6,1,1);

    g2->setLayout(gl2);
    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(glc2);
    v22->addWidget(g2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(v1);

    v->addLayout(h1);

    v->addLayout(v2);
    v->addWidget(vediochoose);
    v->addLayout(v3);
    v->addWidget(autogate);
    v->addLayout(gl);
  //v->addLayout(h2);
    v->addLayout(v22);
    w_seitchField_1->setLayout(v);
    connect(btn_vediosersor_default,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot()));
    connect(btn_vediosersor_update,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot()));
    connect(ChanelNum,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(enable,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(chanelname,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot(int)));//
    connect(vediohaveornot,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(vedio_dpi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(gateshow,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot(int)));
    connect(bullshow,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot(int)));
    connect(xy_ratio,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot()));
    connect(gateshow,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot()));
    connect(bullshow,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot()));
    connect(autogate,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot(int)));
    connect(gate_sizex,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot()));
    connect(gate_sizey,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot()));
    connect(gatelocationx,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot()));
    connect(gatelocationy,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot()));
    connect(Change_set_azimuth,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot()));
    connect(Change_set_pitch,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot()));
    connect(Change_set_zoom,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot()));
    connect(Change_search_azimuth,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot()));
    connect(Change_search_pitch ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot()));
    connect(Change_search_zoom,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot()));
    connect( vedio_fovclass,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot()));

    connect(vedio_s1_Fov0,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical1,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(vedio_spbx_switch1,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_spby_switch1,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_s1_Fov1,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical2,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(vedio_spbx_switch2,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_spby_switch2,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_s1_Fov2,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical3,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(vedio_spbx_switch3,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_spby_switch3,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_s1_Fov3,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical4,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(vedio_spbx_switch4,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_spby_switch4,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_s1_Fov4,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical5,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot()));
    connect(vedio_spbx_switch5,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));
    connect(vedio_spby_switch5,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot()));

    /*连续视场*/
    w_ContinueField_1->setWindowTitle("摄像机配置");
    btn_vediosersor_continue_default=new QPushButton;
    btn_vediosersor_continue_update=new QPushButton;
    btn_vediosersor_continue_default->setText("默认");
    btn_vediosersor_continue_update->setText("保存");
    QVBoxLayout *v8=new QVBoxLayout;
    v8->addWidget(btn_vediosersor_continue_default);
    v8->addWidget(btn_vediosersor_continue_update);
    QLabel *label60=new QLabel;
    label60->setText("通道1");
    QHBoxLayout *h5=new QHBoxLayout;
    h5->addLayout(v8);
    h5->addWidget(label60);

    continueChanelNum = new  QCheckBox();
    continueChanelNum->setText("通道号");
    continuechanelname = new QLineEdit;
    continueenable = new  QCheckBox();
    continueenable->setText("使能");
    QLabel *label61=new QLabel;
    label61->setText("通道名称");
    QHBoxLayout *v9=new QHBoxLayout;
    v9->addWidget(continueChanelNum);
    v9->addWidget(label61);
    v9->addWidget(continuechanelname);
    v9->addWidget(continueenable);

    continue_vediohaveornot = new  QCheckBox();
    continue_vedio_dpi = new QComboBox;
    continue_xy_ratio = new QLineEdit;
    continue_vedio_dpi->addItem("1080P@25HZ");
    continue_vedio_dpi->addItem("1080P@30HZ");
    continue_vedio_dpi->addItem("1080P@60HZ");
    continue_vedio_dpi->addItem("720P@50HZ");
    continue_vedio_dpi->addItem("720P@60HZ");
    vedio_change3 = new QComboBox;
    vedio_change3->addItem("连续视场");
    vedio_change3->addItem("固定视场");
    vedio_change3->addItem("可切换视场");
    continue_vediochoose = new QGroupBox();
    QFormLayout *f5=new QFormLayout();
    f5->addRow(vedio_s[0],continue_vediohaveornot);
    f5->addRow(vedio_s[1],continue_vedio_dpi);
    f5->addRow(vedio_s[2],vedio_change3);
    f5->addRow(vedio_s[3],continue_xy_ratio);
    continue_vediochoose->setLayout(f5);

    continue_gateshow = new  QCheckBox();
    continue_bullshow = new  QCheckBox();
    continue_gateshow->setText("波门显示");
    continue_bullshow->setText("靶心显示");
    QHBoxLayout *v7=new QHBoxLayout;
    v7->addWidget(continue_gateshow);
    v7->addWidget(continue_bullshow);

    continue_autogate = new  QCheckBox();
    continue_autogate->setText("自动波门");

    QLabel *label55=new QLabel;
    label55->setText("波门尺寸X");
    QLabel *label56=new QLabel;
    label56->setText("波门尺寸Y");
    QLabel *label57=new QLabel;
    label57->setText("波门位置X");
    QLabel *label58=new QLabel;
    label58->setText("波门位置Y");
    continue_gate_sizex=new QLineEdit;
    continue_gate_sizey=new QLineEdit;
    continue_gatelocationx=new QLineEdit;
    continue_gatelocationy=new QLineEdit;
    QGridLayout *gl4=new QGridLayout;
    gl4->addWidget(label55,0,0);
    gl4->addWidget(continue_gate_sizex,0,1);
    gl4->addWidget(label56,0,3);
    gl4->addWidget(continue_gate_sizey,0,4);
    gl4->addWidget(label57,1,0);
    gl4->addWidget(continue_gatelocationx,1,1);
    gl4->addWidget(label58,1,3);
    gl4->addWidget(continue_gatelocationy,1,4);

    QHBoxLayout *v31=new QHBoxLayout;
    QLabel *label70=new QLabel;
    label70->setText("测试视场");
    test_1 = new QLineEdit;
    v31->addWidget(label70);
    v31->addWidget(test_1);
//
    QGridLayout *glct2=new QGridLayout;
   continue_set_azimuth =new QPushButton;
   continue_set_pitch =new QPushButton;
   continue_set_zoom  =new QPushButton;
   continue_search_azimuth=new QPushButton;
   continue_search_pitch=new QPushButton;
   continue_search_zoom=new QPushButton;
   continue_set_azimuth->setText("设置");
   continue_set_pitch->setText("设置");
   continue_set_zoom->setText("设置");
   continue_search_azimuth->setText("查询");
   continue_search_pitch->setText("查询");
   continue_search_zoom->setText("查询");

   continue_ledt_set_azimuth=new QLineEdit;
   continue_ledt_set_pitch=new QLineEdit;
   continue_ledt_set_zoom=new QLineEdit;

   continue_ledt_search_azimuth=new QLineEdit;
   continue_ledt_search_pitch=new QLineEdit;
   continue_ledt_search_zoom=new QLineEdit;

   QLabel *labelact=new QLabel;
   labelact->setText("方位角");
   QLabel *labelpct=new QLabel;
   labelpct->setText("俯仰角");
   QLabel *labelzct=new QLabel;
   labelzct->setText("zoom位置");

   glct2->addWidget(labelact,1,0,1,1);
   glct2->addWidget(labelpct,2,0,1,1);
   glct2->addWidget(labelzct,3,0,1,1);


   glct2->addWidget(continue_ledt_set_azimuth,1,2,1,1);
   glct2->addWidget(continue_ledt_set_pitch,2,2,1,1);
   glct2->addWidget(continue_ledt_set_zoom,3,2,1,1);

   glct2->addWidget(continue_set_azimuth,1,3,1,1);
   glct2->addWidget(continue_set_pitch,2,3,1,1);
   glct2->addWidget(continue_set_zoom,3,3,1,1);
   glct2->addWidget(continue_ledt_search_azimuth,1,4,1,1);
   glct2->addWidget(continue_ledt_search_pitch,2,4,1,1);
   glct2->addWidget(continue_ledt_search_zoom,3,4,1,1);

   glct2->addWidget(continue_search_azimuth,1,5,1,1);
   glct2->addWidget(continue_search_pitch,2,5,1,1);
   glct2->addWidget(continue_search_zoom,3,5,1,1);

   //


    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");
    QGridLayout *glc=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l35=new QLabel;
    l35->setText("垂直视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    QLabel* l36=new QLabel;
    l36->setText(" ");
    glc->addWidget(l30,0,1,1,1);
    glc->addWidget(l31,0,2,1,1);
    glc->addWidget(l35,0,4,1,1);
    glc->addWidget(l36,0,5,1,1);
    glc->addWidget(l32,0,6,1,1);
    glc->addWidget(l33,0,7,1,1);
    glc->addWidget(l34,0,8,1,1);


    vedio_l1_continue=new QLineEdit;
    vedio_l2_continue=new QLineEdit;
    vedio_l3_continue=new QLineEdit;
    vedio_l4_continue=new QLineEdit;
    vedio_l5_continue=new QLineEdit;
    vedio_l6_continue=new QLineEdit;
    vedio_l7_continue=new QLineEdit;
    glc->addWidget(vedio_l1_continue,1,1,1,1);
    glc->addWidget(vedio_l2_continue,2,1,1,1);
    glc->addWidget(vedio_l3_continue,3,1,1,1);
    glc->addWidget(vedio_l4_continue,4,1,1,1);
    glc->addWidget(vedio_l5_continue,5,1,1,1);
    glc->addWidget(vedio_l6_continue,6,1,1,1);
    glc->addWidget(vedio_l7_continue,7,1,1,1);

    vedio_continue_Fov0 = new QLineEdit;
    vedio_continue_Fov1 = new QLineEdit;
    vedio_continue_Fov2 = new QLineEdit;
    vedio_continue_Fov3 = new QLineEdit;
    vedio_continue_Fov4 = new QLineEdit;
    vedio_continue_Fov5 = new QLineEdit;
    vedio_continue_Fov6 = new QLineEdit;
    glc->addWidget(vedio_continue_Fov0,1,2,1,1);
    glc->addWidget(vedio_continue_Fov1,2,2,1,1);
    glc->addWidget(vedio_continue_Fov2,3,2,1,1);
    glc->addWidget(vedio_continue_Fov3,4,2,1,1);
    glc->addWidget(vedio_continue_Fov4,5,2,1,1);
    glc->addWidget(vedio_continue_Fov5,6,2,1,1);
    glc->addWidget(vedio_continue_Fov6,7,2,1,1);

    continue_vertical1 = new QLineEdit;
    continue_vertical2 = new QLineEdit;
    continue_vertical3 = new QLineEdit;
    continue_vertical4 = new QLineEdit;
    continue_vertical5 = new QLineEdit;
    continue_vertical6 = new QLineEdit;
    continue_vertical7 = new QLineEdit;
    glc->addWidget(continue_vertical1,1,4,1,1);
    glc->addWidget(continue_vertical2,2,4,1,1);
    glc->addWidget(continue_vertical3,3,4,1,1);
    glc->addWidget(continue_vertical4,4,4,1,1);
    glc->addWidget(continue_vertical5,5,4,1,1);
    glc->addWidget(continue_vertical6,6,4,1,1);
    glc->addWidget(continue_vertical7,7,4,1,1);

    QLabel* l1dv31=new QLabel;
    QLabel* l1dv32=new QLabel;
    QLabel* l1dv33=new QLabel;
    QLabel* l1dv34=new QLabel;
    QLabel* l1dv35=new QLabel;
    QLabel* l1dv36=new QLabel;
    QLabel* l1dv37=new QLabel;
    l1dv31->setText("度");
    l1dv32->setText("度");
    l1dv33->setText("度");
    l1dv34->setText("度");
    l1dv35->setText("度");
    l1dv36->setText("度");
    l1dv37->setText("度");

    glc->addWidget(l1dv31,1,5,1,1);
    glc->addWidget(l1dv32,2,5,1,1);
    glc->addWidget(l1dv33,3,5,1,1);
    glc->addWidget(l1dv34,4,5,1,1);
    glc->addWidget(l1dv35,5,5,1,1);
    glc->addWidget(l1dv36,6,5,1,1);
    glc->addWidget(l1dv37,7,5,1,1);

    QLabel* l1d31=new QLabel;
    QLabel* l1d32=new QLabel;
    QLabel* l1d33=new QLabel;
    QLabel* l1d34=new QLabel;
    QLabel* l1d35=new QLabel;
    QLabel* l1d36=new QLabel;
    QLabel* l1d37=new QLabel;
    l1d31->setText("度");
    l1d32->setText("度");
    l1d33->setText("度");
    l1d34->setText("度");
    l1d35->setText("度");
    l1d36->setText("度");
    l1d37->setText("度");

    glc->addWidget(l1d31,1,3,1,1);
    glc->addWidget(l1d32,2,3,1,1);
    glc->addWidget(l1d33,3,3,1,1);
    glc->addWidget(l1d34,4,3,1,1);
    glc->addWidget(l1d35,5,3,1,1);
    glc->addWidget(l1d36,6,3,1,1);
    glc->addWidget(l1d37,7,3,1,1);


    vedio_spbx_continue1=new QSpinBox;
    vedio_spbx_continue2=new QSpinBox;
    vedio_spbx_continue3=new QSpinBox;
    vedio_spbx_continue4=new QSpinBox;
    vedio_spbx_continue5=new QSpinBox;
    vedio_spbx_continue6=new QSpinBox;
    vedio_spbx_continue7=new QSpinBox;

    vedio_spbx_continue1->setRange(0,9999);
    vedio_spbx_continue2->setRange(0,9999);
    vedio_spbx_continue3->setRange(0,9999);
    vedio_spbx_continue4->setRange(0,9999);
    vedio_spbx_continue5->setRange(0,9999);
    vedio_spbx_continue6->setRange(0,9999);
    vedio_spbx_continue7->setRange(0,9999);

    glc->addWidget(vedio_spbx_continue1,1,6,1,1);
    glc->addWidget(vedio_spbx_continue2,2,6,1,1);
    glc->addWidget(vedio_spbx_continue3,3,6,1,1);
    glc->addWidget(vedio_spbx_continue4,4,6,1,1);
    glc->addWidget(vedio_spbx_continue5,5,6,1,1);
    glc->addWidget(vedio_spbx_continue6,6,6,1,1);
    glc->addWidget(vedio_spbx_continue7,7,6,1,1);


    vedio_spby_continue1=new QSpinBox;
    vedio_spby_continue2=new QSpinBox;
    vedio_spby_continue3=new QSpinBox;
    vedio_spby_continue4=new QSpinBox;
    vedio_spby_continue5=new QSpinBox;
    vedio_spby_continue6=new QSpinBox;
    vedio_spby_continue7=new QSpinBox;

    vedio_spby_continue1->setRange(0,9999);
    vedio_spby_continue2->setRange(0,9999);
    vedio_spby_continue3->setRange(0,9999);
    vedio_spby_continue4->setRange(0,9999);
    vedio_spby_continue5->setRange(0,9999);
    vedio_spby_continue6->setRange(0,9999);
    vedio_spby_continue7->setRange(0,9999);

    glc->addWidget(vedio_spby_continue1,1,7,1,1);
    glc->addWidget(vedio_spby_continue2,2,7,1,1);
    glc->addWidget(vedio_spby_continue3,3,7,1,1);
    glc->addWidget(vedio_spby_continue4,4,7,1,1);
    glc->addWidget(vedio_spby_continue5,5,7,1,1);
    glc->addWidget(vedio_spby_continue6,6,7,1,1);
    glc->addWidget(vedio_spby_continue7,7,7,1,1);
    g3->setLayout(glc);

    QVBoxLayout *v10=new QVBoxLayout;
    v10->addLayout(h5);
    v10->addLayout(v9);
    v10->addWidget(continue_vediochoose);
    v10->addLayout(v7);
    v10->addWidget(continue_autogate);
    v10->addLayout(gl4);
    v10->addLayout(v31);
    v10->addLayout(glct2);
    v10->addWidget(g3);

    //

    w_ContinueField_1->setLayout(v10);

    connect(vedio_change3,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_continue(int)));

    connect(btn_vediosersor_default,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot()));
    connect(btn_vediosersor_update,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot()));
    connect(continueChanelNum,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(continueenable,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(continuechanelname,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot(int)));//
    connect(continue_vediohaveornot,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(continue_vedio_dpi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(continue_gateshow,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot(int)));
    connect(continue_bullshow,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot(int)));
    connect(continue_xy_ratio,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot()));
    connect(continue_gateshow,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot()));
    connect(continue_bullshow,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot()));
    connect(continue_autogate,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot(int)));
    connect(continue_gate_sizex,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot()));
    connect(continue_gate_sizey,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot()));
    connect(continue_gatelocationx,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot()));
    connect(continue_gatelocationy,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot()));
    connect(continue_set_azimuth,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot()));
    connect(continue_set_pitch,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot()));
    connect(continue_set_zoom,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot()));
    connect(continue_search_azimuth,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot()));
    connect(continue_search_pitch ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot()));
    connect(continue_search_zoom,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot()));
    connect(continue_vediohaveornot,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot()));
    connect(test_1,SIGNAL(activated(int)),this,SLOT(test_1_Slot()));
    connect(vedio_l1_continue,SIGNAL(activated(int)),this,SLOT(vedio_l1_continue_Slot()));
     connect(vedio_l2_continue,SIGNAL(activated(int)),this,SLOT(vedio_l2_continue_Slot()));
      connect(vedio_l3_continue,SIGNAL(activated(int)),this,SLOT(vedio_l3_continue_Slot()));
       connect(vedio_l4_continue,SIGNAL(activated(int)),this,SLOT(vedio_l4_continue_Slot()));
        connect(vedio_l5_continue,SIGNAL(activated(int)),this,SLOT(vedio_l5_continue_Slot()));
         connect(vedio_l6_continue,SIGNAL(activated(int)),this,SLOT(vedio_l6_continue_Slot()));
          connect(vedio_l7_continue,SIGNAL(activated(int)),this,SLOT(vedio_l7_continue_Slot()));

    connect( vedio_continue_Fov0,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov0_Slot()));
    connect( vedio_continue_Fov1,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov1_Slot()));
    connect( vedio_continue_Fov2,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov2_Slot()));
    connect( vedio_continue_Fov3,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov3_Slot()));
    connect( vedio_continue_Fov4,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov4_Slot()));
    connect( vedio_continue_Fov5,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov5_Slot()));
    connect( vedio_continue_Fov6,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov6_Slot()));
     connect( continue_vertical1,SIGNAL(returnPressed()),this,SLOT(continue_vertical1_Slot()));
     connect( continue_vertical2,SIGNAL(returnPressed()),this,SLOT(continue_vertical2_Slot()));
     connect( continue_vertical3,SIGNAL(returnPressed()),this,SLOT(continue_vertical3_Slot()));
     connect( continue_vertical4,SIGNAL(returnPressed()),this,SLOT(continue_vertical4_Slot()));
     connect( continue_vertical5,SIGNAL(returnPressed()),this,SLOT(continue_vertical5_Slot()));
     connect( continue_vertical6,SIGNAL(returnPressed()),this,SLOT(continue_vertical6_Slot()));
     connect( continue_vertical7,SIGNAL(returnPressed()),this,SLOT(continue_vertical7_Slot()));

      connect( vedio_spbx_continue1,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot()));
      connect( vedio_spbx_continue2,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue2_Slot()));
      connect( vedio_spbx_continue3,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue3_Slot()));
      connect( vedio_spbx_continue4,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue4_Slot()));
      connect( vedio_spbx_continue5,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue5_Slot()));
      connect( vedio_spbx_continue6,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue6_Slot()));
      connect( vedio_spbx_continue7,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue7_Slot()));

      connect( vedio_spby_continue1,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue1_Slot()));
      connect( vedio_spby_continue2,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue2_Slot()));
      connect( vedio_spby_continue3,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue3_Slot()));
      connect( vedio_spby_continue4,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue4_Slot()));
      connect( vedio_spby_continue5,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue5_Slot()));
      connect( vedio_spby_continue6,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue6_Slot()));
      connect( vedio_spby_continue7,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue7_Slot()));



}

void MainWindow::init_vedioCfg_sec(){


    /*固定视场*/
    w_sersor_1_sec = new MyWidget;
    w_seitchField_1_sec = new MyWidget;
    w_ContinueField_1_sec=new MyWidget;
    w_sersor_1_sec->setWindowTitle("摄像机配置");
    btn_vediosersor_fix_default_sec=new QPushButton;
    btn_vediosersor_fix_update_sec=new QPushButton;
    btn_vediosersor_fix_default_sec->setText("默认");
    btn_vediosersor_fix_update_sec->setText("保存");
    QVBoxLayout *v11=new QVBoxLayout;
    v11->addWidget(btn_vediosersor_fix_default_sec);
    v11->addWidget(btn_vediosersor_fix_update_sec);
    QLabel *label30=new QLabel;
    label30->setText("通道2");
    QHBoxLayout *h11=new QHBoxLayout;
    h11->addLayout(v11);
    h11->addWidget(label30);

    fixChanelNum_sec = new  QCheckBox();
    fixChanelNum_sec->setText("通道号");
    fixchanelname_sec = new QLineEdit;
    fixenable_sec = new  QCheckBox();
    fixenable_sec->setText("使能");
    QLabel *label40=new QLabel;
    label40->setText("通道名称");
    QHBoxLayout *v21=new QHBoxLayout;
    v21->addWidget(fixChanelNum_sec);
    v21->addWidget(label40);
    v21->addWidget(fixchanelname_sec);
    v21->addWidget(fixenable_sec);

    fix_vediohaveornot_sec = new  QCheckBox();
    fix_vedio_dpi_sec = new QComboBox;
    fix_xy_ratio_sec = new QLineEdit;
    fix_vedio_dpi_sec->addItem("1080P@25HZ");
    fix_vedio_dpi_sec->addItem("1080P@30HZ");
    fix_vedio_dpi_sec->addItem("1080P@60HZ");
    fix_vedio_dpi_sec->addItem("720P@50HZ");
    fix_vedio_dpi_sec->addItem("720P@60HZ");
    vedio_change1_sec = new QComboBox;
    vedio_change1_sec->addItem("固定视场");
    vedio_change1_sec->addItem("可切换视场");
    vedio_change1_sec->addItem("连续视场");
    fix_vediochoose_sec = new QGroupBox();
    QFormLayout *f4=new QFormLayout();
    f4->addRow(vedio_s_sec[0],fix_vediohaveornot_sec);
    f4->addRow(vedio_s_sec[1],fix_vedio_dpi_sec);
    f4->addRow(vedio_s_sec[2],vedio_change1_sec);
    f4->addRow(vedio_s_sec[3],fix_xy_ratio_sec);
    fix_vediochoose_sec->setLayout(f4);

    fix_gateshow_sec = new  QCheckBox();
    fix_bullshow_sec = new  QCheckBox();
    fix_gateshow_sec->setText("波门显示");
    fix_bullshow_sec->setText("靶心显示");
    QHBoxLayout *v6=new QHBoxLayout;
    v6->addWidget(fix_gateshow_sec);
    v6->addWidget(fix_bullshow_sec);

    fix_autogate_sec = new  QCheckBox();
    fix_autogate_sec->setText("自动波门");

    QLabel *label51=new QLabel;
    label51->setText("波门尺寸X");
    QLabel *label52=new QLabel;
    label52->setText("波门尺寸Y");
    QLabel *label53=new QLabel;
    label53->setText("波门位置X");
    QLabel *label54=new QLabel;
    label54->setText("波门位置Y");
    fix_gate_sizex_sec=new QLineEdit;
    fix_gate_sizey_sec=new QLineEdit;
    fix_gatelocationx_sec=new QLineEdit;
    fix_gatelocationy_sec=new QLineEdit;
    QGridLayout *gl1=new QGridLayout;
    gl1->addWidget(label51,0,0);
    gl1->addWidget(fix_gate_sizex_sec,0,1);
    gl1->addWidget(label52,0,3);
    gl1->addWidget(fix_gate_sizey_sec,0,4);
    gl1->addWidget(label53,1,0);
    gl1->addWidget(fix_gatelocationx_sec,1,1);
    gl1->addWidget(label54,1,3);
    gl1->addWidget(fix_gatelocationy_sec,1,4);
    //2.10新增
     QGridLayout *gl12=new QGridLayout;
    set_azimuth_sec =new QPushButton;
    set_pitch_sec =new QPushButton;
    set_zoom_sec  =new QPushButton;
    search_azimuth_sec=new QPushButton;
    search_pitch_sec=new QPushButton;
    search_zoom_sec=new QPushButton;
    set_azimuth_sec->setText("设置");
    set_pitch_sec->setText("设置");
    set_zoom_sec->setText("设置");
    search_azimuth_sec->setText("查询");
    search_pitch_sec->setText("查询");
    search_zoom_sec->setText("查询");

    QLabel *labela=new QLabel;
    labela->setText("方位角");
    QLabel *labelp=new QLabel;
    labelp->setText("俯仰角");
    QLabel *labelz=new QLabel;
    labelz->setText("zoom位置");
    ledt_set_azimuth_sec=new QLineEdit;
    ledt_set_pitch_sec=new QLineEdit;
    ledt_set_zoom_sec=new QLineEdit;

    ledt_search_azimuth_sec=new QLineEdit;
    ledt_search_pitch_sec=new QLineEdit;
    ledt_search_zoom_sec=new QLineEdit;

    gl12->addWidget(labela,1,0,1,1);
    gl12->addWidget(labelp,2,0,1,1);
    gl12->addWidget(labelz,3,0,1,1);


    gl12->addWidget(ledt_set_azimuth_sec,1,2,1,1);
    gl12->addWidget(ledt_set_pitch_sec,2,2,1,1);
    gl12->addWidget(ledt_set_zoom_sec,3,2,1,1);

    gl12->addWidget(set_azimuth_sec,1,3,1,1);
    gl12->addWidget(set_pitch_sec,2,3,1,1);
    gl12->addWidget(set_zoom_sec,3,3,1,1);
    gl12->addWidget(ledt_search_azimuth_sec,1,4,1,1);
    gl12->addWidget(ledt_search_pitch_sec,2,4,1,1);
    gl12->addWidget(ledt_search_zoom_sec,3,4,1,1);

    gl12->addWidget(search_azimuth_sec,1,5,1,1);
    gl12->addWidget(search_pitch_sec,2,5,1,1);
    gl12->addWidget(search_zoom_sec,3,5,1,1);
//

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");
    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l15=new QLabel;
    l15->setText("垂直视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");
    fix_lEdt_sec=new QLineEdit;
    fix_vertical_sec=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    QLabel* l1v=new QLabel;
    l1v->setText("度");
    fix_sp_sec=new QSpinBox;
    fix_sp2_sec=new QSpinBox;
    fix_sp_sec->setRange(0,9999);
    fix_sp2_sec->setRange(0,9999);
    QGridLayout *gl3=new QGridLayout;
    gl3->addWidget(l11,0,0,1,1);
    gl3->addWidget(l14,0,1,1,1);

    gl3->addWidget(l15,0,2,1,1);
    gl3->addWidget(l14,0,3,1,1);

    gl3->addWidget(l14,0,4,1,1);
    gl3->addWidget(l12,0,5,1,1);
    gl3->addWidget(l13,0,6,1,1);
    gl3->addWidget(l14,0,7,1,1);
    gl3->addWidget(fix_lEdt_sec,1,0,1,1);
    gl3->addWidget(l1d,1,1,1,1);
    gl3->addWidget(fix_vertical_sec,1,2,1,1);
    gl3->addWidget(l1v,1,3,1,1);
    gl3->addWidget(l14,1,4,1,1);
    gl3->addWidget(fix_sp_sec,1,5,1,1);
    gl3->addWidget(fix_sp2_sec,1,6,1,1);
    g->setLayout(gl3);

    QVBoxLayout *v0=new QVBoxLayout;
    v0->addLayout(h11);
    v0->addLayout(v21);
    v0->addWidget(fix_vediochoose_sec);
    v0->addLayout(v6);
    v0->addWidget(fix_autogate_sec);
    v0->addLayout(gl1);
    v0->addLayout(gl12);
    v0->addWidget(g);
    w_sersor_1_sec->setLayout(v0);


    connect(vedio_change1_sec,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix_sec(int)));
/*
    connect(btn_vediosersor_fix_default_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_sec()));
    connect(btn_vediosersor_fix_update_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_sec()));
    connect(fixChanelNum_sec,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_sec(int)));
    connect(fixchanelname_sec,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_sec(int)));
    connect(fixenable_sec,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_sec(int)));
    connect(fix_vediohaveornot_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_sec(int)));
    connect(fix_vedio_dpi_sec,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_sec(int)));
    connect(fix_xy_ratio_sec,SIGNAL(returnPressed()),this,SLOT(fix_xy_ratio_Slot_sec()));
    connect(fix_gateshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_sec(int)));
    connect(fix_bullshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_sec(int)));
    connect(fix_autogate_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_sec(int)));
    connect(fix_gate_sizex_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_sec()));
    connect(fix_gate_sizey_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_sec()));
    connect(fix_gatelocationx_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_sec()));
    connect(fix_gatelocationy_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_sec()));
    connect(set_azimuth_sec,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_sec()));
    connect(set_pitch_sec,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_sec()));
    connect(set_zoom_sec,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_sec()));
    connect(search_azimuth_sec,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_sec()));
    connect(search_pitch_sec,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_sec()));
    connect(search_zoom_sec,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_sec()));
   // connect(ledt_set_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_set_azimuth_Slot()));
   // connect(ledt_set_pitch,SIGNAL(activated(int)),this,SLOT(ledt_set_pitch_Slot()));
   // connect(ledt_set_zoom,SIGNAL(activated(int)),this,SLOT(ledt_set_zoom_Slot()));
   // connect(ledt_search_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_search_azimuth_Slot()));
   // connect(ledt_search_pitch,SIGNAL(activated(int)),this,SLOT(ledt_search_pitch_Slot()));
   // connect(ledt_search_zoom,SIGNAL(activated(int)),this,SLOT(ledt_search_zoom_Slot()));
    connect(fix_lEdt_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_sec()));
    connect(fix_vertical_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(fix_sp_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(fix_sp2_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    */

    /*可切换视场*/

    w_seitchField_1_sec->setWindowTitle("摄像机配置");
    btn_vediosersor_default_sec=new QPushButton;
    btn_vediosersor_update_sec=new QPushButton;
    btn_vediosersor_default_sec->setText("默认");
    btn_vediosersor_update_sec->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_vediosersor_default_sec);
    v1->addWidget(btn_vediosersor_update_sec);
    QLabel *label1=new QLabel;
    label1->setText("通道2");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label1);

    ChanelNum_sec = new  QCheckBox();
    ChanelNum_sec->setText("通道号");
    chanelname_sec = new QLineEdit;
    enable_sec = new  QCheckBox();
    enable_sec->setText("使能");

    QLabel *label2=new QLabel;
    label2->setText("通道名称");
    QHBoxLayout *v2=new QHBoxLayout;
    v2->addWidget(ChanelNum_sec);
    v2->addWidget(label2);
    v2->addWidget(chanelname_sec);
    v2->addWidget(enable_sec);

    vediohaveornot_sec = new  QCheckBox();
    vedio_dpi_sec = new QComboBox;
    xy_ratio_sec = new QLineEdit;
    vedio_dpi_sec->addItem("1080P@25HZ");
    vedio_dpi_sec->addItem("1080P@30HZ");
    vedio_dpi_sec->addItem("1080P@60HZ");
    vedio_dpi_sec->addItem("720P@50HZ");
    vedio_dpi_sec->addItem("720P@60HZ");
    vedio_change2_sec = new QComboBox;
    vedio_change2_sec->addItem("可切换视场");
    vedio_change2_sec->addItem("固定视场");
    vedio_change2_sec->addItem("连续视场");

    vediochoose_sec = new QGroupBox();
    QFormLayout *f3=new QFormLayout();
    f3->addRow(vedio_s_sec[0],vediohaveornot_sec);
    f3->addRow(vedio_s_sec[1],vedio_dpi_sec);
    f3->addRow(vedio_s_sec[2],vedio_change2_sec);
    f3->addRow(vedio_s_sec[3],xy_ratio_sec);
    vediochoose_sec->setLayout(f3);

    connect(vedio_change2_sec,SIGNAL(activated(int)),this,SLOT(vedio_toSensor_switch_sec(int)));
    gateshow_sec = new  QCheckBox();
    bullshow_sec = new  QCheckBox();
    gateshow_sec->setText("波门显示");
    bullshow_sec->setText("靶心显示");
    QHBoxLayout *v3=new QHBoxLayout;
    v3->addWidget(gateshow_sec);
    v3->addWidget(bullshow_sec);

    autogate_sec = new  QCheckBox();
    autogate_sec->setText("自动波门");

    QLabel *label3=new QLabel;
    label3->setText("波门尺寸X");
    QLabel *label4=new QLabel;
    label4->setText("波门尺寸Y");
    QLabel *label5=new QLabel;
    label5->setText("波门位置X");
    QLabel *label6=new QLabel;
    label6->setText("波门位置Y");
    gate_sizex_sec=new QLineEdit;
    gate_sizey_sec=new QLineEdit;
    gatelocationx_sec=new QLineEdit;
    gatelocationy_sec=new QLineEdit;
    QGridLayout *gl=new QGridLayout;
    gl->addWidget(label3,0,0);
    gl->addWidget(gate_sizex_sec,0,1);
    gl->addWidget(label4,0,3);
    gl->addWidget(gate_sizey_sec,0,4);
    gl->addWidget(label5,1,0);
    gl->addWidget(gatelocationx_sec,1,1);
    gl->addWidget(label6,1,3);
    gl->addWidget(gatelocationy_sec,1,4);

    QHBoxLayout *h2=new QHBoxLayout;
    QLabel *label7=new QLabel;
    label7->setText("测试现场等级");
    vedio_fovclass_sec = new QComboBox;
    vedio_fovclass_sec->addItem("可切换视场1");
    vedio_fovclass_sec->addItem("可切换视场2");
    vedio_fovclass_sec->addItem("可切换视场3");
    vedio_fovclass_sec->addItem("可切换视场4");
    vedio_fovclass_sec->addItem("可切换视场5");
    h2->addWidget(label7);
    h2->addWidget(vedio_fovclass_sec);
    //

    QGridLayout *glc2=new QGridLayout;
   Change_set_azimuth_sec =new QPushButton;
   Change_set_pitch_sec =new QPushButton;
   Change_set_zoom_sec  =new QPushButton;
   Change_search_azimuth_sec=new QPushButton;
   Change_search_pitch_sec=new QPushButton;
   Change_search_zoom_sec=new QPushButton;
   Change_set_azimuth_sec->setText("设置");
   Change_set_pitch_sec->setText("设置");
   Change_set_zoom_sec->setText("设置");
   Change_search_azimuth_sec->setText("查询");
   Change_search_pitch_sec->setText("查询");
   Change_search_zoom_sec->setText("查询");

   Change_ledt_set_azimuth_sec=new QLineEdit;
   Change_ledt_set_pitch_sec=new QLineEdit;
   Change_ledt_set_zoom_sec=new QLineEdit;

   Change_ledt_search_azimuth_sec=new QLineEdit;
   Change_ledt_search_pitch_sec=new QLineEdit;
   Change_ledt_search_zoom_sec=new QLineEdit;

   QLabel *labelac=new QLabel;
   labelac->setText("方位角");
   QLabel *labelpc=new QLabel;
   labelpc->setText("俯仰角");
   QLabel *labelzc=new QLabel;
   labelzc->setText("zoom位置");

   glc2->addWidget(labelac,1,0,1,1);
   glc2->addWidget(labelpc,2,0,1,1);
   glc2->addWidget(labelzc,3,0,1,1);


   glc2->addWidget(Change_ledt_set_azimuth_sec,1,2,1,1);
   glc2->addWidget(Change_ledt_set_pitch_sec,2,2,1,1);
   glc2->addWidget(Change_ledt_set_zoom_sec,3,2,1,1);

   glc2->addWidget(Change_set_azimuth_sec,1,3,1,1);
   glc2->addWidget(Change_set_pitch_sec,2,3,1,1);
   glc2->addWidget(Change_set_zoom_sec,3,3,1,1);
   glc2->addWidget(Change_ledt_search_azimuth_sec,1,4,1,1);
   glc2->addWidget(Change_ledt_search_pitch_sec,2,4,1,1);
   glc2->addWidget(Change_ledt_search_zoom_sec,3,4,1,1);

   glc2->addWidget(Change_search_azimuth_sec,1,5,1,1);
   glc2->addWidget(Change_search_pitch_sec,2,5,1,1);
   glc2->addWidget(Change_search_zoom_sec,3,5,1,1);


    //

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");
    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l25=new QLabel;
    l25->setText("垂直视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l25,0,3,1,1);
    gl2->addWidget(l22,0,5,1,1);
    gl2->addWidget(l23,0,6,1,1);
    gl2->addWidget(l24,0,7,1,1);

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
    vedio_s1_Fov0_sec=new QLineEdit;
    vedio_s1_Fov1_sec=new QLineEdit;
    vedio_s1_Fov2_sec=new QLineEdit;
    vedio_s1_Fov3_sec=new QLineEdit;
    vedio_s1_Fov4_sec=new QLineEdit;
    gl2->addWidget(vedio_s1_Fov0_sec,1,1,1,1);
    gl2->addWidget(vedio_s1_Fov1_sec,2,1,1,1);
    gl2->addWidget(vedio_s1_Fov2_sec,3,1,1,1);
    gl2->addWidget(vedio_s1_Fov3_sec,4,1,1,1);
    gl2->addWidget(vedio_s1_Fov4_sec,5,1,1,1);

    Change_vertical1_sec=new QLineEdit;
    Change_vertical2_sec=new QLineEdit;
    Change_vertical3_sec=new QLineEdit;
    Change_vertical4_sec=new QLineEdit;
    Change_vertical5_sec=new QLineEdit;
    gl2->addWidget(Change_vertical1_sec,1,3,1,1);
    gl2->addWidget(Change_vertical2_sec,2,3,1,1);
    gl2->addWidget(Change_vertical3_sec,3,3,1,1);
    gl2->addWidget(Change_vertical4_sec,4,3,1,1);
    gl2->addWidget(Change_vertical5_sec,5,3,1,1);

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

    QLabel* l1c21=new QLabel;
    QLabel* l1c22=new QLabel;
    QLabel* l1c23=new QLabel;
    QLabel* l1c24=new QLabel;
    QLabel* l1c25=new QLabel;
    l1c21->setText("度");
    l1c22->setText("度");
    l1c23->setText("度");
    l1c24->setText("度");
    l1c25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    gl2->addWidget(l1c21,1,4,1,1);
    gl2->addWidget(l1c22,2,4,1,1);
    gl2->addWidget(l1c23,3,4,1,1);
    gl2->addWidget(l1c24,4,4,1,1);
    gl2->addWidget(l1c25,5,4,1,1);


    vedio_spbx_switch1_sec=new QSpinBox;
    vedio_spbx_switch2_sec=new QSpinBox;
    vedio_spbx_switch3_sec=new QSpinBox;
    vedio_spbx_switch4_sec=new QSpinBox;
    vedio_spbx_switch5_sec=new QSpinBox;
    vedio_spbx_switch1_sec->setRange(0,9999);
    vedio_spbx_switch2_sec->setRange(0,9999);
    vedio_spbx_switch3_sec->setRange(0,9999);
    vedio_spbx_switch4_sec->setRange(0,9999);
    vedio_spbx_switch5_sec->setRange(0,9999);
    gl2->addWidget(vedio_spbx_switch1_sec,1,5,1,1);
    gl2->addWidget(vedio_spbx_switch2_sec,2,5,1,1);
    gl2->addWidget(vedio_spbx_switch3_sec,3,5,1,1);
    gl2->addWidget(vedio_spbx_switch4_sec,4,5,1,1);
    gl2->addWidget(vedio_spbx_switch5_sec,5,5,1,1);

    vedio_spby_switch1_sec=new QSpinBox;
    vedio_spby_switch2_sec=new QSpinBox;
    vedio_spby_switch3_sec=new QSpinBox;
    vedio_spby_switch4_sec=new QSpinBox;
    vedio_spby_switch5_sec=new QSpinBox;
    vedio_spby_switch1_sec->setRange(0,9999);
    vedio_spby_switch2_sec->setRange(0,9999);
    vedio_spby_switch3_sec->setRange(0,9999);
    vedio_spby_switch4_sec->setRange(0,9999);
    vedio_spby_switch5_sec->setRange(0,9999);
    gl2->addWidget(vedio_spby_switch1_sec,1,6,1,1);
    gl2->addWidget(vedio_spby_switch2_sec,2,6,1,1);
    gl2->addWidget(vedio_spby_switch3_sec,3,6,1,1);
    gl2->addWidget(vedio_spby_switch4_sec,4,6,1,1);
    gl2->addWidget(vedio_spby_switch5_sec,5,6,1,1);

    g2->setLayout(gl2);
    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(glc2);
    v22->addWidget(g2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(v1);

    v->addLayout(h1);

    v->addLayout(v2);
    v->addWidget(vediochoose_sec);
    v->addLayout(v3);
    v->addWidget(autogate_sec);
    v->addLayout(gl);
  //v->addLayout(h2);
    v->addLayout(v22);
    w_seitchField_1_sec->setLayout(v);
    /*
    connect(btn_vediosersor_default_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_sec()));
    connect(btn_vediosersor_update_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_sec()));
    connect(ChanelNum_sec,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(enable_sec,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_sec(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(chanelname_sec,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_sec(int)));//
    connect(vediohaveornot_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_sec(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(vedio_dpi_sec,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_sec(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(gateshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_sec(int)));
    connect(bullshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_sec(int)));
    connect(xy_ratio_sec,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_sec()));
    connect(gateshow_sec,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_sec()));
    connect(bullshow_sec,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_sec()));
    connect(autogate_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_sec(int)));
    connect(gate_sizex_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_sec()));
    connect(gate_sizey_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_sec()));
    connect(gatelocationx_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_sec()));
    connect(gatelocationy_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_sec()));
    connect(Change_set_azimuth_sec,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_sec()));
    connect(Change_set_pitch_sec,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_sec()));
    connect(Change_set_zoom_sec,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_sec()));
    connect(Change_search_azimuth_sec,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_sec()));
    connect(Change_search_pitch_sec ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_sec()));
    connect(Change_search_zoom_sec,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_sec()));
    connect( vedio_fovclass_sec,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_sec()));

    connect(vedio_s1_Fov0_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot()));
    connect(Change_vertical1_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(vedio_spbx_switch1_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_spby_switch1_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_s1_Fov1_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_sec()));
    connect(Change_vertical2_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(vedio_spbx_switch2_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_spby_switch2_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_s1_Fov2_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_sec()));
    connect(Change_vertical3_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(vedio_spbx_switch3_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slo_sect()));
    connect(vedio_spby_switch3_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_s1_Fov3_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_sec()));
    connect(Change_vertical4_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(vedio_spbx_switch4_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_spby_switch4_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_s1_Fov4_sec,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_sec()));
    connect(Change_vertical5_sec,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_sec()));
    connect(vedio_spbx_switch5_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
    connect(vedio_spby_switch5_sec,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_sec()));
*/

    /*连续视场*/

    w_ContinueField_1_sec->setWindowTitle("摄像机配置");
    btn_vediosersor_continue_default_sec=new QPushButton;
    btn_vediosersor_continue_update_sec=new QPushButton;
    btn_vediosersor_continue_default_sec->setText("默认");
    btn_vediosersor_continue_update_sec->setText("保存");
    QVBoxLayout *v8=new QVBoxLayout;
    v8->addWidget(btn_vediosersor_continue_default_sec);
    v8->addWidget(btn_vediosersor_continue_update_sec);
    QLabel *label60=new QLabel;
    label60->setText("通道2");
    QHBoxLayout *h5=new QHBoxLayout;
    h5->addLayout(v8);
    h5->addWidget(label60);

    continueChanelNum_sec = new  QCheckBox();
    continueChanelNum_sec->setText("通道号");
    continuechanelname_sec = new QLineEdit;
    continueenable_sec = new  QCheckBox();
    continueenable_sec->setText("使能");
    QLabel *label61=new QLabel;
    label61->setText("通道名称");
    QHBoxLayout *v9=new QHBoxLayout;
    v9->addWidget(continueChanelNum_sec);
    v9->addWidget(label61);
    v9->addWidget(continuechanelname_sec);
    v9->addWidget(continueenable_sec);

    continue_vediohaveornot_sec = new  QCheckBox();
    continue_vedio_dpi_sec = new QComboBox;
    continue_xy_ratio_sec = new QLineEdit;
   // continue_vedio_dpi_sec->addItem("1080P@25HZ");
    continue_vedio_dpi_sec->addItem("1080P@30HZ");
    continue_vedio_dpi_sec->addItem("1080P@60HZ");
    continue_vedio_dpi_sec->addItem("720P@50HZ");
    continue_vedio_dpi_sec->addItem("720P@60HZ");
    vedio_change3_sec = new QComboBox;
    vedio_change3_sec->addItem("连续视场");
    vedio_change3_sec->addItem("固定视场");
    vedio_change3_sec->addItem("可切换视场");
    continue_vediochoose_sec = new QGroupBox();
    QFormLayout *f5=new QFormLayout();
    f5->addRow(vedio_s_sec[0],continue_vediohaveornot_sec);
    f5->addRow(vedio_s_sec[1],continue_vedio_dpi_sec);
    f5->addRow(vedio_s_sec[2],vedio_change3_sec);
    f5->addRow(vedio_s_sec[3],continue_xy_ratio_sec);
    continue_vediochoose_sec->setLayout(f5);

    continue_gateshow_sec = new  QCheckBox();
    continue_bullshow_sec = new  QCheckBox();
    continue_gateshow_sec->setText("波门显示");
    continue_bullshow_sec->setText("靶心显示");
    QHBoxLayout *v7=new QHBoxLayout;
    v7->addWidget(continue_gateshow_sec);
    v7->addWidget(continue_bullshow_sec);

    continue_autogate_sec = new  QCheckBox();
    continue_autogate_sec->setText("自动波门");

    QLabel *label55=new QLabel;
    label55->setText("波门尺寸X");
    QLabel *label56=new QLabel;
    label56->setText("波门尺寸Y");
    QLabel *label57=new QLabel;
    label57->setText("波门位置X");
    QLabel *label58=new QLabel;
    label58->setText("波门位置Y");
    continue_gate_sizex_sec=new QLineEdit;
    continue_gate_sizey_sec=new QLineEdit;
    continue_gatelocationx_sec=new QLineEdit;
    continue_gatelocationy_sec=new QLineEdit;
    QGridLayout *gl4=new QGridLayout;
    gl4->addWidget(label55,0,0);
    gl4->addWidget(continue_gate_sizex_sec,0,1);
    gl4->addWidget(label56,0,3);
    gl4->addWidget(continue_gate_sizey_sec,0,4);
    gl4->addWidget(label57,1,0);
    gl4->addWidget(continue_gatelocationx_sec,1,1);
    gl4->addWidget(label58,1,3);
    gl4->addWidget(continue_gatelocationy_sec,1,4);

    QHBoxLayout *v31=new QHBoxLayout;
    QLabel *label70=new QLabel;
    label70->setText("测试视场");
    test_1 = new QLineEdit;
    v31->addWidget(label70);
    v31->addWidget(test_1);
//
    QGridLayout *glct2=new QGridLayout;
   continue_set_azimuth_sec =new QPushButton;
   continue_set_pitch_sec =new QPushButton;
   continue_set_zoom_sec  =new QPushButton;
   continue_search_azimuth_sec=new QPushButton;
   continue_search_pitch_sec=new QPushButton;
   continue_search_zoom_sec=new QPushButton;
   continue_set_azimuth_sec->setText("设置");
   continue_set_pitch_sec->setText("设置");
   continue_set_zoom_sec->setText("设置");
   continue_search_azimuth_sec->setText("查询");
   continue_search_pitch_sec->setText("查询");
   continue_search_zoom_sec->setText("查询");

   continue_ledt_set_azimuth_sec=new QLineEdit;
   continue_ledt_set_pitch_sec=new QLineEdit;
   continue_ledt_set_zoom_sec=new QLineEdit;

   continue_ledt_search_azimuth_sec=new QLineEdit;
   continue_ledt_search_pitch_sec=new QLineEdit;
   continue_ledt_search_zoom_sec=new QLineEdit;

   QLabel *labelact=new QLabel;
   labelact->setText("方位角");
   QLabel *labelpct=new QLabel;
   labelpct->setText("俯仰角");
   QLabel *labelzct=new QLabel;
   labelzct->setText("zoom位置");

   glct2->addWidget(labelact,1,0,1,1);
   glct2->addWidget(labelpct,2,0,1,1);
   glct2->addWidget(labelzct,3,0,1,1);


   glct2->addWidget(continue_ledt_set_azimuth_sec,1,2,1,1);
   glct2->addWidget(continue_ledt_set_pitch_sec,2,2,1,1);
   glct2->addWidget(continue_ledt_set_zoom_sec,3,2,1,1);

   glct2->addWidget(continue_set_azimuth_sec,1,3,1,1);
   glct2->addWidget(continue_set_pitch_sec,2,3,1,1);
   glct2->addWidget(continue_set_zoom_sec,3,3,1,1);
   glct2->addWidget(continue_ledt_search_azimuth_sec,1,4,1,1);
   glct2->addWidget(continue_ledt_search_pitch_sec,2,4,1,1);
   glct2->addWidget(continue_ledt_search_zoom_sec,3,4,1,1);

   glct2->addWidget(continue_search_azimuth_sec,1,5,1,1);
   glct2->addWidget(continue_search_pitch_sec,2,5,1,1);
   glct2->addWidget(continue_search_zoom_sec,3,5,1,1);

   //


    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");
    QGridLayout *glc=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l35=new QLabel;
    l35->setText("垂直视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    QLabel* l36=new QLabel;
    l36->setText(" ");
    glc->addWidget(l30,0,1,1,1);
    glc->addWidget(l31,0,2,1,1);
    glc->addWidget(l35,0,4,1,1);
    glc->addWidget(l36,0,5,1,1);
    glc->addWidget(l32,0,6,1,1);
    glc->addWidget(l33,0,7,1,1);
    glc->addWidget(l34,0,8,1,1);


    vedio_l1_continue_sec=new QLineEdit;
    vedio_l2_continue_sec=new QLineEdit;
    vedio_l3_continue_sec=new QLineEdit;
    vedio_l4_continue_sec=new QLineEdit;
    vedio_l5_continue_sec=new QLineEdit;
    vedio_l6_continue_sec=new QLineEdit;
    vedio_l7_continue_sec=new QLineEdit;
    glc->addWidget(vedio_l1_continue_sec,1,1,1,1);
    glc->addWidget(vedio_l2_continue_sec,2,1,1,1);
    glc->addWidget(vedio_l3_continue_sec,3,1,1,1);
    glc->addWidget(vedio_l4_continue_sec,4,1,1,1);
    glc->addWidget(vedio_l5_continue_sec,5,1,1,1);
    glc->addWidget(vedio_l6_continue_sec,6,1,1,1);
    glc->addWidget(vedio_l7_continue_sec,7,1,1,1);

    vedio_continue_Fov0_sec = new QLineEdit;
    vedio_continue_Fov1_sec = new QLineEdit;
    vedio_continue_Fov2_sec = new QLineEdit;
    vedio_continue_Fov3_sec = new QLineEdit;
    vedio_continue_Fov4_sec = new QLineEdit;
    vedio_continue_Fov5_sec = new QLineEdit;
    vedio_continue_Fov6_sec = new QLineEdit;
    glc->addWidget(vedio_continue_Fov0_sec,1,2,1,1);
    glc->addWidget(vedio_continue_Fov1_sec,2,2,1,1);
    glc->addWidget(vedio_continue_Fov2_sec,3,2,1,1);
    glc->addWidget(vedio_continue_Fov3_sec,4,2,1,1);
    glc->addWidget(vedio_continue_Fov4_sec,5,2,1,1);
    glc->addWidget(vedio_continue_Fov5_sec,6,2,1,1);
    glc->addWidget(vedio_continue_Fov6_sec,7,2,1,1);

    continue_vertical1_sec = new QLineEdit;
    continue_vertical2_sec = new QLineEdit;
    continue_vertical3_sec = new QLineEdit;
    continue_vertical4_sec = new QLineEdit;
    continue_vertical5_sec= new QLineEdit;
    continue_vertical6_sec = new QLineEdit;
    continue_vertical7_sec = new QLineEdit;
    glc->addWidget(continue_vertical1_sec,1,4,1,1);
    glc->addWidget(continue_vertical2_sec,2,4,1,1);
    glc->addWidget(continue_vertical3_sec,3,4,1,1);
    glc->addWidget(continue_vertical4_sec,4,4,1,1);
    glc->addWidget(continue_vertical5_sec,5,4,1,1);
    glc->addWidget(continue_vertical6_sec,6,4,1,1);
    glc->addWidget(continue_vertical7_sec,7,4,1,1);

    QLabel* l1dv31=new QLabel;
    QLabel* l1dv32=new QLabel;
    QLabel* l1dv33=new QLabel;
    QLabel* l1dv34=new QLabel;
    QLabel* l1dv35=new QLabel;
    QLabel* l1dv36=new QLabel;
    QLabel* l1dv37=new QLabel;
    l1dv31->setText("度");
    l1dv32->setText("度");
    l1dv33->setText("度");
    l1dv34->setText("度");
    l1dv35->setText("度");
    l1dv36->setText("度");
    l1dv37->setText("度");

    glc->addWidget(l1dv31,1,5,1,1);
    glc->addWidget(l1dv32,2,5,1,1);
    glc->addWidget(l1dv33,3,5,1,1);
    glc->addWidget(l1dv34,4,5,1,1);
    glc->addWidget(l1dv35,5,5,1,1);
    glc->addWidget(l1dv36,6,5,1,1);
    glc->addWidget(l1dv37,7,5,1,1);

    QLabel* l1d31=new QLabel;
    QLabel* l1d32=new QLabel;
    QLabel* l1d33=new QLabel;
    QLabel* l1d34=new QLabel;
    QLabel* l1d35=new QLabel;
    QLabel* l1d36=new QLabel;
    QLabel* l1d37=new QLabel;
    l1d31->setText("度");
    l1d32->setText("度");
    l1d33->setText("度");
    l1d34->setText("度");
    l1d35->setText("度");
    l1d36->setText("度");
    l1d37->setText("度");

    glc->addWidget(l1d31,1,3,1,1);
    glc->addWidget(l1d32,2,3,1,1);
    glc->addWidget(l1d33,3,3,1,1);
    glc->addWidget(l1d34,4,3,1,1);
    glc->addWidget(l1d35,5,3,1,1);
    glc->addWidget(l1d36,6,3,1,1);
    glc->addWidget(l1d37,7,3,1,1);


    vedio_spbx_continue1_sec=new QSpinBox;
    vedio_spbx_continue2_sec=new QSpinBox;
    vedio_spbx_continue3_sec=new QSpinBox;
    vedio_spbx_continue4_sec=new QSpinBox;
    vedio_spbx_continue5_sec=new QSpinBox;
    vedio_spbx_continue6_sec=new QSpinBox;
    vedio_spbx_continue7_sec=new QSpinBox;

    vedio_spbx_continue1_sec->setRange(0,9999);
    vedio_spbx_continue2_sec->setRange(0,9999);
    vedio_spbx_continue3_sec->setRange(0,9999);
    vedio_spbx_continue4_sec->setRange(0,9999);
    vedio_spbx_continue5_sec->setRange(0,9999);
    vedio_spbx_continue6_sec->setRange(0,9999);
    vedio_spbx_continue7_sec->setRange(0,9999);

    glc->addWidget(vedio_spbx_continue1_sec,1,6,1,1);
    glc->addWidget(vedio_spbx_continue2_sec,2,6,1,1);
    glc->addWidget(vedio_spbx_continue3_sec,3,6,1,1);
    glc->addWidget(vedio_spbx_continue4_sec,4,6,1,1);
    glc->addWidget(vedio_spbx_continue5_sec,5,6,1,1);
    glc->addWidget(vedio_spbx_continue6_sec,6,6,1,1);
    glc->addWidget(vedio_spbx_continue7_sec,7,6,1,1);


    vedio_spby_continue1_sec=new QSpinBox;
    vedio_spby_continue2_sec=new QSpinBox;
    vedio_spby_continue3_sec=new QSpinBox;
    vedio_spby_continue4_sec=new QSpinBox;
    vedio_spby_continue5_sec=new QSpinBox;
    vedio_spby_continue6_sec=new QSpinBox;
    vedio_spby_continue7_sec=new QSpinBox;

    vedio_spby_continue1_sec->setRange(0,9999);
    vedio_spby_continue2_sec->setRange(0,9999);
    vedio_spby_continue3_sec->setRange(0,9999);
    vedio_spby_continue4_sec->setRange(0,9999);
    vedio_spby_continue5_sec->setRange(0,9999);
    vedio_spby_continue6_sec->setRange(0,9999);
    vedio_spby_continue7_sec->setRange(0,9999);

    glc->addWidget(vedio_spby_continue1_sec,1,7,1,1);
    glc->addWidget(vedio_spby_continue2_sec,2,7,1,1);
    glc->addWidget(vedio_spby_continue3_sec,3,7,1,1);
    glc->addWidget(vedio_spby_continue4_sec,4,7,1,1);
    glc->addWidget(vedio_spby_continue5_sec,5,7,1,1);
    glc->addWidget(vedio_spby_continue6_sec,6,7,1,1);
    glc->addWidget(vedio_spby_continue7_sec,7,7,1,1);
    g3->setLayout(glc);

    QVBoxLayout *v10=new QVBoxLayout;
    v10->addLayout(h5);
    v10->addLayout(v9);
    v10->addWidget(continue_vediochoose_sec);
    v10->addLayout(v7);
    v10->addWidget(continue_autogate_sec);
    v10->addLayout(gl4);
    v10->addLayout(v31);
    v10->addLayout(glct2);
    v10->addWidget(g3);

    //

    w_ContinueField_1_sec->setLayout(v10);

    connect(vedio_change3_sec,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_continue_sec(int)));
/*
    connect(btn_vediosersor_default_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_sec()));
    connect(btn_vediosersor_update_sec,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_sec()));
    connect(continueChanelNum_sec,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_sec(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(continueenable_sec,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slo_sect_sec(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(continuechanelname_sec,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_sec_sec(int)));//
    connect(continue_vediohaveornot_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_sec_sec(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(continue_vedio_dpi_sec,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_sec(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(continue_gateshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_sec(int)));
    connect(continue_bullshow_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_sec(int)));
    connect(continue_xy_ratio_sec,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_sec()));
    connect(continue_gateshow_sec,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_sec()));
    connect(continue_bullshow_sec,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_sec()));
    connect(continue_autogate_sec,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_sec(int)));
    connect(continue_gate_sizex_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_sec()));
    connect(continue_gate_sizey_sec,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_sec()));
    connect(continue_gatelocationx_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_sec()));
    connect(continue_gatelocationy_sec,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_sec()));
    connect(continue_set_azimuth_sec,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_sec()));
    connect(continue_set_pitch_sec,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_sec()));
    connect(continue_set_zoom_sec,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_sec()));
    connect(continue_search_azimuth_sec,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_sec()));
    connect(continue_search_pitch_sec ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_sec()));
    connect(continue_search_zoom_sec,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_sec()));
    connect(continue_vediohaveornot_sec,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_sec()));
    connect(test_1_sec,SIGNAL(activated(int)),this,SLOT(test_1_Slot_sec()));
    connect(vedio_l1_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l1_continue_Slot_sec()));
    connect(vedio_l2_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l2_continue_Slot_sec()));
    connect(vedio_l3_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l3_continue_Slot_sec()));
    connect(vedio_l4_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l4_continue_Slot_sec()));
    connect(vedio_l5_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l5_continue_Slot_sec()));
    connect(vedio_l6_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l6_continue_Slot_sec()));
    connect(vedio_l7_continue_sec,SIGNAL(activated(int)),this,SLOT(vedio_l7_continue_Slot_sec()));

    connect( vedio_continue_Fov0_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov0_Slot_sec()));
    connect( vedio_continue_Fov1_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov1_Slot_sec()));
    connect( vedio_continue_Fov2_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov2_Slot_sec()));
    connect( vedio_continue_Fov3_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov3_Slot_sec()));
    connect( vedio_continue_Fov4_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov4_Slot_sec()));
    connect( vedio_continue_Fov5_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov5_Slot_sec()));
    connect( vedio_continue_Fov6_sec,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov6_Slot_sec()));
     connect( continue_vertical1_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical1_Slot_sec()));
     connect( continue_vertical2_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical2_Slot_sec()));
     connect( continue_vertical3_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical3_Slot_sec()));
     connect( continue_vertical4_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical4_Slot_sec()));
     connect( continue_vertical5_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical5_Slot_sec()));
     connect( continue_vertical6_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical6_Slot_sec()));
     connect( continue_vertical7_sec,SIGNAL(returnPressed()),this,SLOT(continue_vertical7_Slot_sec()));

      connect( vedio_spbx_continue1_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_sec()));
      connect( vedio_spbx_continue2_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue2_Slot_sec()));
      connect( vedio_spbx_continue3_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue3_Slot_sec()));
      connect( vedio_spbx_continue4_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue4_Slot_sec()));
      connect( vedio_spbx_continue5_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue5_Slot_sec()));
      connect( vedio_spbx_continue6_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue6_Slot_sec()));
      connect( vedio_spbx_continue7_sec,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue7_Slot_sec()));

      connect( vedio_spby_continue1_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue1_Slot_sec()));
      connect( vedio_spby_continue2_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue2_Slot_sec()));
      connect( vedio_spby_continue3_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue3_Slot_sec()));
      connect( vedio_spby_continue4_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue4_Slot_sec()));
      connect( vedio_spby_continue5_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue5_Slot_sec()));
      connect( vedio_spby_continue6_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue6_Slot_sec()));
      connect( vedio_spby_continue7_sec,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue7_Slot_sec()));
      */

}

void MainWindow::init_vedioCfg_thi(){

    w_sersor_1_thi = new MyWidget;
    w_seitchField_1_thi = new MyWidget;
    w_ContinueField_1_thi=new MyWidget;
    w_sersor_1_thi->setWindowTitle("摄像机配置");
    btn_vediosersor_fix_default_thi=new QPushButton;
    btn_vediosersor_fix_update_thi=new QPushButton;
    btn_vediosersor_fix_default_thi->setText("默认");
    btn_vediosersor_fix_update_thi->setText("保存");
    QVBoxLayout *v11=new QVBoxLayout;
    v11->addWidget(btn_vediosersor_fix_default_thi);
    v11->addWidget(btn_vediosersor_fix_update_thi);
    QLabel *label30=new QLabel;
    label30->setText("通道3");
    QHBoxLayout *h11=new QHBoxLayout;
    h11->addLayout(v11);
    h11->addWidget(label30);

    fixChanelNum_thi = new  QCheckBox();
    fixChanelNum_thi->setText("通道号");
    fixchanelname_thi = new QLineEdit;
    fixenable_thi = new  QCheckBox();
    fixenable_thi->setText("使能");
    QLabel *label40=new QLabel;
    label40->setText("通道名称");
    QHBoxLayout *v21=new QHBoxLayout;
    v21->addWidget(fixChanelNum_thi);
    v21->addWidget(label40);
    v21->addWidget(fixchanelname_thi);
    v21->addWidget(fixenable_thi);

    fix_vediohaveornot_thi = new  QCheckBox();
    fix_vedio_dpi_thi = new QComboBox;
    fix_xy_ratio_thi = new QLineEdit;
    fix_vedio_dpi_thi->addItem("1080P@25HZ");
    fix_vedio_dpi_thi->addItem("1080P@30HZ");
    fix_vedio_dpi_thi->addItem("1080P@60HZ");
    fix_vedio_dpi_thi->addItem("720P@60HZ");
    fix_vedio_dpi_thi->addItem("720P@50HZ");
    vedio_change1_thi = new QComboBox;
    vedio_change1_thi->addItem("固定视场");
    vedio_change1_thi->addItem("可切换视场");
    vedio_change1_thi->addItem("连续视场");
    fix_vediochoose_thi = new QGroupBox();
    QFormLayout *f4=new QFormLayout();
    f4->addRow(vedio_s_thi[0],fix_vediohaveornot_thi);
    f4->addRow(vedio_s_thi[1],fix_vedio_dpi_thi);
    f4->addRow(vedio_s_thi[2],vedio_change1_thi);
    f4->addRow(vedio_s_thi[3],fix_xy_ratio_thi);
    fix_vediochoose_thi->setLayout(f4);

    fix_gateshow_thi = new  QCheckBox();
    fix_bullshow_thi = new  QCheckBox();
    fix_gateshow_thi->setText("波门显示");
    fix_bullshow_thi->setText("靶心显示");
    QHBoxLayout *v6=new QHBoxLayout;
    v6->addWidget(fix_gateshow_thi);
    v6->addWidget(fix_bullshow_thi);

    fix_autogate_thi = new  QCheckBox();
    fix_autogate_thi->setText("自动波门");

    QLabel *label51=new QLabel;
    label51->setText("波门尺寸X");
    QLabel *label52=new QLabel;
    label52->setText("波门尺寸Y");
    QLabel *label53=new QLabel;
    label53->setText("波门位置X");
    QLabel *label54=new QLabel;
    label54->setText("波门位置Y");
    fix_gate_sizex_thi=new QLineEdit;
    fix_gate_sizey_thi=new QLineEdit;
    fix_gatelocationx_thi=new QLineEdit;
    fix_gatelocationy_thi=new QLineEdit;
    QGridLayout *gl1=new QGridLayout;
    gl1->addWidget(label51,0,0);
    gl1->addWidget(fix_gate_sizex_thi,0,1);
    gl1->addWidget(label52,0,3);
    gl1->addWidget(fix_gate_sizey_thi,0,4);
    gl1->addWidget(label53,1,0);
    gl1->addWidget(fix_gatelocationx_thi,1,1);
    gl1->addWidget(label54,1,3);
    gl1->addWidget(fix_gatelocationy_thi,1,4);
    //2.10新增
     QGridLayout *gl12=new QGridLayout;
    set_azimuth_thi =new QPushButton;
    set_pitch_thi =new QPushButton;
    set_zoom_thi  =new QPushButton;
    search_azimuth_thi=new QPushButton;
    search_pitch_thi=new QPushButton;
    search_zoom_thi=new QPushButton;
    set_azimuth_thi->setText("设置");
    set_pitch_thi->setText("设置");
    set_zoom_thi->setText("设置");
    search_azimuth_thi->setText("查询");
    search_pitch_thi->setText("查询");
    search_zoom_thi->setText("查询");

    QLabel *labela=new QLabel;
    labela->setText("方位角");
    QLabel *labelp=new QLabel;
    labelp->setText("俯仰角");
    QLabel *labelz=new QLabel;
    labelz->setText("zoom位置");
    ledt_set_azimuth_thi=new QLineEdit;
    ledt_set_pitch_thi=new QLineEdit;
    ledt_set_zoom_thi=new QLineEdit;

    ledt_search_azimuth_thi=new QLineEdit;
    ledt_search_pitch_thi=new QLineEdit;
    ledt_search_zoom_thi=new QLineEdit;

    gl12->addWidget(labela,1,0,1,1);
    gl12->addWidget(labelp,2,0,1,1);
    gl12->addWidget(labelz,3,0,1,1);


    gl12->addWidget(ledt_set_azimuth_thi,1,2,1,1);
    gl12->addWidget(ledt_set_pitch_thi,2,2,1,1);
    gl12->addWidget(ledt_set_zoom_thi,3,2,1,1);

    gl12->addWidget(set_azimuth_thi,1,3,1,1);
    gl12->addWidget(set_pitch_thi,2,3,1,1);
    gl12->addWidget(set_zoom_thi,3,3,1,1);
    gl12->addWidget(ledt_search_azimuth_thi,1,4,1,1);
    gl12->addWidget(ledt_search_pitch_thi,2,4,1,1);
    gl12->addWidget(ledt_search_zoom_thi,3,4,1,1);

    gl12->addWidget(search_azimuth_thi,1,5,1,1);
    gl12->addWidget(search_pitch_thi,2,5,1,1);
    gl12->addWidget(search_zoom_thi,3,5,1,1);
//

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");
    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l15=new QLabel;
    l15->setText("垂直视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");
    fix_lEdt_thi=new QLineEdit;
    fix_vertical_thi=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    QLabel* l1v=new QLabel;
    l1v->setText("度");
    fix_sp_thi=new QSpinBox;
    fix_sp2_thi=new QSpinBox;
    fix_sp_thi->setRange(0,9999);
    fix_sp2_thi->setRange(0,9999);
    QGridLayout *gl3=new QGridLayout;
    gl3->addWidget(l11,0,0,1,1);
    gl3->addWidget(l14,0,1,1,1);

    gl3->addWidget(l15,0,2,1,1);
    gl3->addWidget(l14,0,3,1,1);

    gl3->addWidget(l14,0,4,1,1);
    gl3->addWidget(l12,0,5,1,1);
    gl3->addWidget(l13,0,6,1,1);
    gl3->addWidget(l14,0,7,1,1);
    gl3->addWidget(fix_lEdt_thi,1,0,1,1);
    gl3->addWidget(l1d,1,1,1,1);
    gl3->addWidget(fix_vertical_thi,1,2,1,1);
    gl3->addWidget(l1v,1,3,1,1);
    gl3->addWidget(l14,1,4,1,1);
    gl3->addWidget(fix_sp_thi,1,5,1,1);
    gl3->addWidget(fix_sp2_thi,1,6,1,1);
    g->setLayout(gl3);

    QVBoxLayout *v0=new QVBoxLayout;
    v0->addLayout(h11);
    v0->addLayout(v21);
    v0->addWidget(fix_vediochoose_thi);
    v0->addLayout(v6);
    v0->addWidget(fix_autogate_thi);
    v0->addLayout(gl1);
    v0->addLayout(gl12);
    v0->addWidget(g);
    w_sersor_1_thi->setLayout(v0);
    connect(vedio_change1_thi,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix_thi(int)));

    connect(btn_vediosersor_fix_default_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_thi()));
    connect(btn_vediosersor_fix_update_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_thi()));
    connect(fixChanelNum_thi,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_thi(int)));
    connect(fixchanelname_thi,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_thi(int)));
    connect(fixenable_thi,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_thi(int)));
    connect(fix_vediohaveornot_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_thi(int)));
    connect(fix_vedio_dpi_thi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_thi(int)));
    connect(fix_xy_ratio_thi,SIGNAL(returnPressed()),this,SLOT(fix_xy_ratio_Slot_thi()));
    connect(fix_gateshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_thi(int)));
    connect(fix_bullshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_thi(int)));
    connect(fix_autogate_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_thi(int)));
    connect(fix_gate_sizex_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_thi()));
    connect(fix_gate_sizey_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_thi()));
    connect(fix_gatelocationx_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_thi()));
    connect(fix_gatelocationy_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_thi()));
    connect(set_azimuth_thi,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_thi()));
    connect(set_pitch_thi,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_thi()));
    connect(set_zoom_thi,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_thi()));
    connect(search_azimuth_thi,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_thi()));
    connect(search_pitch_thi,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_thi()));
    connect(search_zoom_thi,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_thi()));
   // connect(ledt_set_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_set_azimuth_Slot()));
   // connect(ledt_set_pitch,SIGNAL(activated(int)),this,SLOT(ledt_set_pitch_Slot()));
   // connect(ledt_set_zoom,SIGNAL(activated(int)),this,SLOT(ledt_set_zoom_Slot()));
   // connect(ledt_search_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_search_azimuth_Slot()));
   // connect(ledt_search_pitch,SIGNAL(activated(int)),this,SLOT(ledt_search_pitch_Slot()));
   // connect(ledt_search_zoom,SIGNAL(activated(int)),this,SLOT(ledt_search_zoom_Slot()));
    connect(fix_lEdt_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(fix_vertical_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(fix_sp_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(fix_sp2_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));

    /*可切换视场*/

    w_seitchField_1_thi->setWindowTitle("摄像机配置");
    btn_vediosersor_default_thi=new QPushButton;
    btn_vediosersor_update_thi=new QPushButton;
    btn_vediosersor_default_thi->setText("默认");
    btn_vediosersor_update_thi->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_vediosersor_default_thi);
    v1->addWidget(btn_vediosersor_update_thi);
    QLabel *label1=new QLabel;
    label1->setText("通道3");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label1);

    ChanelNum_thi = new  QCheckBox();
    ChanelNum_thi->setText("通道号");
    chanelname_thi = new QLineEdit;
    enable_thi = new  QCheckBox();
    enable_thi->setText("使能");

    QLabel *label2=new QLabel;
    label2->setText("通道名称");
    QHBoxLayout *v2=new QHBoxLayout;
    v2->addWidget(ChanelNum_thi);
    v2->addWidget(label2);
    v2->addWidget(chanelname_thi);
    v2->addWidget(enable_thi);

    vediohaveornot_thi = new  QCheckBox();
    vedio_dpi_thi = new QComboBox;
    xy_ratio_thi = new QLineEdit;
    vedio_dpi_thi->addItem("1080P@25HZ");
    vedio_dpi_thi->addItem("1080P@30HZ");
    vedio_dpi_thi->addItem("1080P@60HZ");
    vedio_dpi_thi->addItem("720P@60HZ");
    vedio_dpi_thi->addItem("720P@50HZ");
    vedio_change2_thi = new QComboBox;
    vedio_change2_thi->addItem("可切换视场");
    vedio_change2_thi->addItem("固定视场");
    vedio_change2_thi->addItem("连续视场");

    vediochoose_thi = new QGroupBox();
    QFormLayout *f3=new QFormLayout();
    f3->addRow(vedio_s_thi[0],vediohaveornot_thi);
    f3->addRow(vedio_s_thi[1],vedio_dpi_thi);
    f3->addRow(vedio_s_thi[2],vedio_change2_thi);
    f3->addRow(vedio_s_thi[3],xy_ratio_thi);
    vediochoose_thi->setLayout(f3);

    connect(vedio_change2_thi,SIGNAL(activated(int)),this,SLOT(vedio_toSensor_switch_thi(int)));
    gateshow_thi = new  QCheckBox();
    bullshow_thi = new  QCheckBox();
    gateshow_thi->setText("波门显示");
    bullshow_thi->setText("靶心显示");
    QHBoxLayout *v3=new QHBoxLayout;
    v3->addWidget(gateshow_thi);
    v3->addWidget(bullshow_thi);

    autogate_thi = new  QCheckBox();
    autogate_thi->setText("自动波门");

    QLabel *label3=new QLabel;
    label3->setText("波门尺寸X");
    QLabel *label4=new QLabel;
    label4->setText("波门尺寸Y");
    QLabel *label5=new QLabel;
    label5->setText("波门位置X");
    QLabel *label6=new QLabel;
    label6->setText("波门位置Y");
    gate_sizex_thi=new QLineEdit;
    gate_sizey_thi=new QLineEdit;
    gatelocationx_thi=new QLineEdit;
    gatelocationy_thi=new QLineEdit;
    QGridLayout *gl=new QGridLayout;
    gl->addWidget(label3,0,0);
    gl->addWidget(gate_sizex_thi,0,1);
    gl->addWidget(label4,0,3);
    gl->addWidget(gate_sizey_thi,0,4);
    gl->addWidget(label5,1,0);
    gl->addWidget(gatelocationx_thi,1,1);
    gl->addWidget(label6,1,3);
    gl->addWidget(gatelocationy_thi,1,4);

    QHBoxLayout *h2=new QHBoxLayout;
    QLabel *label7=new QLabel;
    label7->setText("测试现场等级");
    vedio_fovclass_thi = new QComboBox;
    vedio_fovclass_thi->addItem("可切换视场1");
    vedio_fovclass_thi->addItem("可切换视场2");
    vedio_fovclass_thi->addItem("可切换视场3");
    vedio_fovclass_thi->addItem("可切换视场4");
    vedio_fovclass_thi->addItem("可切换视场5");
    h2->addWidget(label7);
    h2->addWidget(vedio_fovclass_thi);
    //

    QGridLayout *glc2=new QGridLayout;
   Change_set_azimuth_thi =new QPushButton;
   Change_set_pitch_thi =new QPushButton;
   Change_set_zoom_thi  =new QPushButton;
   Change_search_azimuth_thi=new QPushButton;
   Change_search_pitch_thi=new QPushButton;
   Change_search_zoom_thi=new QPushButton;
   Change_set_azimuth_thi->setText("设置");
   Change_set_pitch_thi->setText("设置");
   Change_set_zoom_thi->setText("设置");
   Change_search_azimuth_thi->setText("查询");
   Change_search_pitch_thi->setText("查询");
   Change_search_zoom_thi->setText("查询");

   Change_ledt_set_azimuth_thi=new QLineEdit;
   Change_ledt_set_pitch_thi=new QLineEdit;
   Change_ledt_set_zoom_thi=new QLineEdit;

   Change_ledt_search_azimuth_thi=new QLineEdit;
   Change_ledt_search_pitch_thi=new QLineEdit;
   Change_ledt_search_zoom_thi=new QLineEdit;

   QLabel *labelac=new QLabel;
   labelac->setText("方位角");
   QLabel *labelpc=new QLabel;
   labelpc->setText("俯仰角");
   QLabel *labelzc=new QLabel;
   labelzc->setText("zoom位置");

   glc2->addWidget(labelac,1,0,1,1);
   glc2->addWidget(labelpc,2,0,1,1);
   glc2->addWidget(labelzc,3,0,1,1);


   glc2->addWidget(Change_ledt_set_azimuth_thi,1,2,1,1);
   glc2->addWidget(Change_ledt_set_pitch_thi,2,2,1,1);
   glc2->addWidget(Change_ledt_set_zoom_thi,3,2,1,1);

   glc2->addWidget(Change_set_azimuth_thi,1,3,1,1);
   glc2->addWidget(Change_set_pitch_thi,2,3,1,1);
   glc2->addWidget(Change_set_zoom_thi,3,3,1,1);
   glc2->addWidget(Change_ledt_search_azimuth_thi,1,4,1,1);
   glc2->addWidget(Change_ledt_search_pitch_thi,2,4,1,1);
   glc2->addWidget(Change_ledt_search_zoom_thi,3,4,1,1);

   glc2->addWidget(Change_search_azimuth_thi,1,5,1,1);
   glc2->addWidget(Change_search_pitch_thi,2,5,1,1);
   glc2->addWidget(Change_search_zoom_thi,3,5,1,1);


    //

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");
    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l25=new QLabel;
    l25->setText("垂直视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l25,0,3,1,1);
    gl2->addWidget(l22,0,5,1,1);
    gl2->addWidget(l23,0,6,1,1);
    gl2->addWidget(l24,0,7,1,1);

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
    vedio_s1_Fov0_thi=new QLineEdit;
    vedio_s1_Fov1_thi=new QLineEdit;
    vedio_s1_Fov2_thi=new QLineEdit;
    vedio_s1_Fov3_thi=new QLineEdit;
    vedio_s1_Fov4_thi=new QLineEdit;
    gl2->addWidget(vedio_s1_Fov0_thi,1,1,1,1);
    gl2->addWidget(vedio_s1_Fov1_thi,2,1,1,1);
    gl2->addWidget(vedio_s1_Fov2_thi,3,1,1,1);
    gl2->addWidget(vedio_s1_Fov3_thi,4,1,1,1);
    gl2->addWidget(vedio_s1_Fov4_thi,5,1,1,1);

    Change_vertical1_thi=new QLineEdit;
    Change_vertical2_thi=new QLineEdit;
    Change_vertical3_thi=new QLineEdit;
    Change_vertical4_thi=new QLineEdit;
    Change_vertical5_thi=new QLineEdit;
    gl2->addWidget(Change_vertical1_thi,1,3,1,1);
    gl2->addWidget(Change_vertical2_thi,2,3,1,1);
    gl2->addWidget(Change_vertical3_thi,3,3,1,1);
    gl2->addWidget(Change_vertical4_thi,4,3,1,1);
    gl2->addWidget(Change_vertical5_thi,5,3,1,1);

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

    QLabel* l1c21=new QLabel;
    QLabel* l1c22=new QLabel;
    QLabel* l1c23=new QLabel;
    QLabel* l1c24=new QLabel;
    QLabel* l1c25=new QLabel;
    l1c21->setText("度");
    l1c22->setText("度");
    l1c23->setText("度");
    l1c24->setText("度");
    l1c25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    gl2->addWidget(l1c21,1,4,1,1);
    gl2->addWidget(l1c22,2,4,1,1);
    gl2->addWidget(l1c23,3,4,1,1);
    gl2->addWidget(l1c24,4,4,1,1);
    gl2->addWidget(l1c25,5,4,1,1);


    vedio_spbx_switch1_thi=new QSpinBox;
    vedio_spbx_switch2_thi=new QSpinBox;
    vedio_spbx_switch3_thi=new QSpinBox;
    vedio_spbx_switch4_thi=new QSpinBox;
    vedio_spbx_switch5_thi=new QSpinBox;
    vedio_spbx_switch1_thi->setRange(0,9999);
    vedio_spbx_switch2_thi->setRange(0,9999);
    vedio_spbx_switch3_thi->setRange(0,9999);
    vedio_spbx_switch4_thi->setRange(0,9999);
    vedio_spbx_switch5_thi->setRange(0,9999);
    gl2->addWidget(vedio_spbx_switch1_thi,1,5,1,1);
    gl2->addWidget(vedio_spbx_switch2_thi,2,5,1,1);
    gl2->addWidget(vedio_spbx_switch3_thi,3,5,1,1);
    gl2->addWidget(vedio_spbx_switch4_thi,4,5,1,1);
    gl2->addWidget(vedio_spbx_switch5_thi,5,5,1,1);

    vedio_spby_switch1_thi=new QSpinBox;
    vedio_spby_switch2_thi=new QSpinBox;
    vedio_spby_switch3_thi=new QSpinBox;
    vedio_spby_switch4_thi=new QSpinBox;
    vedio_spby_switch5_thi=new QSpinBox;
    vedio_spby_switch1_thi->setRange(0,9999);
    vedio_spby_switch2_thi->setRange(0,9999);
    vedio_spby_switch3_thi->setRange(0,9999);
    vedio_spby_switch4_thi->setRange(0,9999);
    vedio_spby_switch5_thi->setRange(0,9999);
    gl2->addWidget(vedio_spby_switch1_thi,1,6,1,1);
    gl2->addWidget(vedio_spby_switch2_thi,2,6,1,1);
    gl2->addWidget(vedio_spby_switch3_thi,3,6,1,1);
    gl2->addWidget(vedio_spby_switch4_thi,4,6,1,1);
    gl2->addWidget(vedio_spby_switch5_thi,5,6,1,1);

    g2->setLayout(gl2);
    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(glc2);
    v22->addWidget(g2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(v1);

    v->addLayout(h1);

    v->addLayout(v2);
    v->addWidget(vediochoose_thi);
    v->addLayout(v3);
    v->addWidget(autogate_thi);
    v->addLayout(gl);
  //v->addLayout(h2);
    v->addLayout(v22);
    w_seitchField_1_thi->setLayout(v);
    connect(btn_vediosersor_default_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_thi()));
    connect(btn_vediosersor_update_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_thi()));
    connect(ChanelNum_thi,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_thi(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(enable_thi,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_thi(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(chanelname_thi,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_thi(int)));//
    connect(vediohaveornot_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_thi(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(vedio_dpi_thi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_thi(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(gateshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_thi(int)));
    connect(bullshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_thi(int)));
    connect(xy_ratio_thi,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_thi()));
    connect(gateshow_thi,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_thi()));
    connect(bullshow_thi,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_thi()));
    connect(autogate_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_thi(int)));
    connect(gate_sizex_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_thi()));
    connect(gate_sizey_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_thi()));
    connect(gatelocationx_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_thi()));
    connect(gatelocationy_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_thi()));
    connect(Change_set_azimuth_thi,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_thi()));
    connect(Change_set_pitch_thi,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_thi()));
    connect(Change_set_zoom_thi,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_thi()));
    connect(Change_search_azimuth_thi,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_thi()));
    connect(Change_search_pitch_thi ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_thi()));
    connect(Change_search_zoom_thi,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_thi()));
    connect( vedio_fovclass_thi,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_thi()));

    connect(vedio_s1_Fov0_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(Change_vertical1_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(vedio_spbx_switch1_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_spby_switch1_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_s1_Fov1_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(Change_vertical2_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(vedio_spbx_switch2_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_spby_switch2_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_s1_Fov2_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(Change_vertical3_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(vedio_spbx_switch3_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_spby_switch3_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_s1_Fov3_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(Change_vertical4_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(vedio_spbx_switch4_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_spby_switch4_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_s1_Fov4_thi,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_thi()));
    connect(Change_vertical5_thi,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_thi()));
    connect(vedio_spbx_switch5_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));
    connect(vedio_spby_switch5_thi,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_thi()));


    /*连续视场*/

    w_ContinueField_1_thi->setWindowTitle("摄像机配置");
    btn_vediosersor_continue_default_thi=new QPushButton;
    btn_vediosersor_continue_update_thi=new QPushButton;
    btn_vediosersor_continue_default_thi->setText("默认");
    btn_vediosersor_continue_update_thi->setText("保存");
    QVBoxLayout *v8=new QVBoxLayout;
    v8->addWidget(btn_vediosersor_continue_default_thi);
    v8->addWidget(btn_vediosersor_continue_update_thi);
    QLabel *label60=new QLabel;
    label60->setText("通道3");
    QHBoxLayout *h5=new QHBoxLayout;
    h5->addLayout(v8);
    h5->addWidget(label60);

    continueChanelNum_thi = new  QCheckBox();
    continueChanelNum_thi->setText("通道号");
    continuechanelname_thi = new QLineEdit;
    continueenable_thi = new  QCheckBox();
    continueenable_thi->setText("使能");
    QLabel *label61=new QLabel;
    label61->setText("通道名称");
    QHBoxLayout *v9=new QHBoxLayout;
    v9->addWidget(continueChanelNum_thi);
    v9->addWidget(label61);
    v9->addWidget(continuechanelname_thi);
    v9->addWidget(continueenable_thi);

    continue_vediohaveornot_thi = new  QCheckBox();
    continue_vedio_dpi_thi = new QComboBox;
    continue_xy_ratio_thi = new QLineEdit;
    continue_vedio_dpi_thi->addItem("1080P@25HZ");
    continue_vedio_dpi_thi->addItem("1080P@30HZ");
    continue_vedio_dpi_thi->addItem("1080P@60HZ");
    continue_vedio_dpi_thi->addItem("720P@60HZ");
    continue_vedio_dpi_thi->addItem("720P@50HZ");
    vedio_change3_thi = new QComboBox;
    vedio_change3_thi->addItem("连续视场");
    vedio_change3_thi->addItem("固定视场");
    vedio_change3_thi->addItem("可切换视场");
    continue_vediochoose_thi = new QGroupBox();
    QFormLayout *f5=new QFormLayout();
    f5->addRow(vedio_s_thi[0],continue_vediohaveornot_thi);
    f5->addRow(vedio_s_thi[1],continue_vedio_dpi_thi);
    f5->addRow(vedio_s_thi[2],vedio_change3_thi);
    f5->addRow(vedio_s_thi[3],continue_xy_ratio_thi);
    continue_vediochoose_thi->setLayout(f5);

    continue_gateshow_thi = new  QCheckBox();
    continue_bullshow_thi = new  QCheckBox();
    continue_gateshow_thi->setText("波门显示");
    continue_bullshow_thi->setText("靶心显示");
    QHBoxLayout *v7=new QHBoxLayout;
    v7->addWidget(continue_gateshow_thi);
    v7->addWidget(continue_bullshow_thi);

    continue_autogate_thi = new  QCheckBox();
    continue_autogate_thi->setText("自动波门");

    QLabel *label55=new QLabel;
    label55->setText("波门尺寸X");
    QLabel *label56=new QLabel;
    label56->setText("波门尺寸Y");
    QLabel *label57=new QLabel;
    label57->setText("波门位置X");
    QLabel *label58=new QLabel;
    label58->setText("波门位置Y");
    continue_gate_sizex_thi=new QLineEdit;
    continue_gate_sizey_thi=new QLineEdit;
    continue_gatelocationx_thi=new QLineEdit;
    continue_gatelocationy_thi=new QLineEdit;
    QGridLayout *gl4=new QGridLayout;
    gl4->addWidget(label55,0,0);
    gl4->addWidget(continue_gate_sizex_thi,0,1);
    gl4->addWidget(label56,0,3);
    gl4->addWidget(continue_gate_sizey_thi,0,4);
    gl4->addWidget(label57,1,0);
    gl4->addWidget(continue_gatelocationx_thi,1,1);
    gl4->addWidget(label58,1,3);
    gl4->addWidget(continue_gatelocationy_thi,1,4);

    QHBoxLayout *v31=new QHBoxLayout;
    QLabel *label70=new QLabel;
    label70->setText("测试视场");
    test_1_thi = new QLineEdit;
    v31->addWidget(label70);
    v31->addWidget(test_1_thi);
//
    QGridLayout *glct2=new QGridLayout;
   continue_set_azimuth_thi =new QPushButton;
   continue_set_pitch_thi =new QPushButton;
   continue_set_zoom_thi  =new QPushButton;
   continue_search_azimuth_thi=new QPushButton;
   continue_search_pitch_thi=new QPushButton;
   continue_search_zoom_thi=new QPushButton;
   continue_set_azimuth_thi->setText("设置");
   continue_set_pitch_thi->setText("设置");
   continue_set_zoom_thi->setText("设置");
   continue_search_azimuth_thi->setText("查询");
   continue_search_pitch_thi->setText("查询");
   continue_search_zoom_thi->setText("查询");

   continue_ledt_set_azimuth_thi=new QLineEdit;
   continue_ledt_set_pitch_thi=new QLineEdit;
   continue_ledt_set_zoom_thi=new QLineEdit;

   continue_ledt_search_azimuth_thi=new QLineEdit;
   continue_ledt_search_pitch_thi=new QLineEdit;
   continue_ledt_search_zoom_thi=new QLineEdit;

   QLabel *labelact=new QLabel;
   labelact->setText("方位角");
   QLabel *labelpct=new QLabel;
   labelpct->setText("俯仰角");
   QLabel *labelzct=new QLabel;
   labelzct->setText("zoom位置");

   glct2->addWidget(labelact,1,0,1,1);
   glct2->addWidget(labelpct,2,0,1,1);
   glct2->addWidget(labelzct,3,0,1,1);


   glct2->addWidget(continue_ledt_set_azimuth_thi,1,2,1,1);
   glct2->addWidget(continue_ledt_set_pitch_thi,2,2,1,1);
   glct2->addWidget(continue_ledt_set_zoom_thi,3,2,1,1);

   glct2->addWidget(continue_set_azimuth_thi,1,3,1,1);
   glct2->addWidget(continue_set_pitch_thi,2,3,1,1);
   glct2->addWidget(continue_set_zoom_thi,3,3,1,1);
   glct2->addWidget(continue_ledt_search_azimuth_thi,1,4,1,1);
   glct2->addWidget(continue_ledt_search_pitch_thi,2,4,1,1);
   glct2->addWidget(continue_ledt_search_zoom_thi,3,4,1,1);

   glct2->addWidget(continue_search_azimuth_thi,1,5,1,1);
   glct2->addWidget(continue_search_pitch_thi,2,5,1,1);
   glct2->addWidget(continue_search_zoom_thi,3,5,1,1);

   //


    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");
    QGridLayout *glc=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l35=new QLabel;
    l35->setText("垂直视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    QLabel* l36=new QLabel;
    l36->setText(" ");
    glc->addWidget(l30,0,1,1,1);
    glc->addWidget(l31,0,2,1,1);
    glc->addWidget(l35,0,4,1,1);
    glc->addWidget(l36,0,5,1,1);
    glc->addWidget(l32,0,6,1,1);
    glc->addWidget(l33,0,7,1,1);
    glc->addWidget(l34,0,8,1,1);


    vedio_l1_continue_thi=new QLineEdit;
    vedio_l2_continue_thi=new QLineEdit;
    vedio_l3_continue_thi=new QLineEdit;
    vedio_l4_continue_thi=new QLineEdit;
    vedio_l5_continue_thi=new QLineEdit;
    vedio_l6_continue_thi=new QLineEdit;
    vedio_l7_continue_thi=new QLineEdit;
    glc->addWidget(vedio_l1_continue_thi,1,1,1,1);
    glc->addWidget(vedio_l2_continue_thi,2,1,1,1);
    glc->addWidget(vedio_l3_continue_thi,3,1,1,1);
    glc->addWidget(vedio_l4_continue_thi,4,1,1,1);
    glc->addWidget(vedio_l5_continue_thi,5,1,1,1);
    glc->addWidget(vedio_l6_continue_thi,6,1,1,1);
    glc->addWidget(vedio_l7_continue_thi,7,1,1,1);

    vedio_continue_Fov0_thi = new QLineEdit;
    vedio_continue_Fov1_thi = new QLineEdit;
    vedio_continue_Fov2_thi = new QLineEdit;
    vedio_continue_Fov3_thi = new QLineEdit;
    vedio_continue_Fov4_thi = new QLineEdit;
    vedio_continue_Fov5_thi = new QLineEdit;
    vedio_continue_Fov6_thi = new QLineEdit;
    glc->addWidget(vedio_continue_Fov0_thi,1,2,1,1);
    glc->addWidget(vedio_continue_Fov1_thi,2,2,1,1);
    glc->addWidget(vedio_continue_Fov2_thi,3,2,1,1);
    glc->addWidget(vedio_continue_Fov3_thi,4,2,1,1);
    glc->addWidget(vedio_continue_Fov4_thi,5,2,1,1);
    glc->addWidget(vedio_continue_Fov5_thi,6,2,1,1);
    glc->addWidget(vedio_continue_Fov6_thi,7,2,1,1);

    continue_vertical1_thi = new QLineEdit;
    continue_vertical2_thi = new QLineEdit;
    continue_vertical3_thi = new QLineEdit;
    continue_vertical4_thi = new QLineEdit;
    continue_vertical5_thi = new QLineEdit;
    continue_vertical6_thi = new QLineEdit;
    continue_vertical7_thi = new QLineEdit;
    glc->addWidget(continue_vertical1_thi,1,4,1,1);
    glc->addWidget(continue_vertical2_thi,2,4,1,1);
    glc->addWidget(continue_vertical3_thi,3,4,1,1);
    glc->addWidget(continue_vertical4_thi,4,4,1,1);
    glc->addWidget(continue_vertical5_thi,5,4,1,1);
    glc->addWidget(continue_vertical6_thi,6,4,1,1);
    glc->addWidget(continue_vertical7_thi,7,4,1,1);

    QLabel* l1dv31=new QLabel;
    QLabel* l1dv32=new QLabel;
    QLabel* l1dv33=new QLabel;
    QLabel* l1dv34=new QLabel;
    QLabel* l1dv35=new QLabel;
    QLabel* l1dv36=new QLabel;
    QLabel* l1dv37=new QLabel;
    l1dv31->setText("度");
    l1dv32->setText("度");
    l1dv33->setText("度");
    l1dv34->setText("度");
    l1dv35->setText("度");
    l1dv36->setText("度");
    l1dv37->setText("度");

    glc->addWidget(l1dv31,1,5,1,1);
    glc->addWidget(l1dv32,2,5,1,1);
    glc->addWidget(l1dv33,3,5,1,1);
    glc->addWidget(l1dv34,4,5,1,1);
    glc->addWidget(l1dv35,5,5,1,1);
    glc->addWidget(l1dv36,6,5,1,1);
    glc->addWidget(l1dv37,7,5,1,1);

    QLabel* l1d31=new QLabel;
    QLabel* l1d32=new QLabel;
    QLabel* l1d33=new QLabel;
    QLabel* l1d34=new QLabel;
    QLabel* l1d35=new QLabel;
    QLabel* l1d36=new QLabel;
    QLabel* l1d37=new QLabel;
    l1d31->setText("度");
    l1d32->setText("度");
    l1d33->setText("度");
    l1d34->setText("度");
    l1d35->setText("度");
    l1d36->setText("度");
    l1d37->setText("度");

    glc->addWidget(l1d31,1,3,1,1);
    glc->addWidget(l1d32,2,3,1,1);
    glc->addWidget(l1d33,3,3,1,1);
    glc->addWidget(l1d34,4,3,1,1);
    glc->addWidget(l1d35,5,3,1,1);
    glc->addWidget(l1d36,6,3,1,1);
    glc->addWidget(l1d37,7,3,1,1);


    vedio_spbx_continue1_thi=new QSpinBox;
    vedio_spbx_continue2_thi=new QSpinBox;
    vedio_spbx_continue3_thi=new QSpinBox;
    vedio_spbx_continue4_thi=new QSpinBox;
    vedio_spbx_continue5_thi=new QSpinBox;
    vedio_spbx_continue6_thi=new QSpinBox;
    vedio_spbx_continue7_thi=new QSpinBox;

    vedio_spbx_continue1_thi->setRange(0,9999);
    vedio_spbx_continue2_thi->setRange(0,9999);
    vedio_spbx_continue3_thi->setRange(0,9999);
    vedio_spbx_continue4_thi->setRange(0,9999);
    vedio_spbx_continue5_thi->setRange(0,9999);
    vedio_spbx_continue6_thi->setRange(0,9999);
    vedio_spbx_continue7_thi->setRange(0,9999);

    glc->addWidget(vedio_spbx_continue1_thi,1,6,1,1);
    glc->addWidget(vedio_spbx_continue2_thi,2,6,1,1);
    glc->addWidget(vedio_spbx_continue3_thi,3,6,1,1);
    glc->addWidget(vedio_spbx_continue4_thi,4,6,1,1);
    glc->addWidget(vedio_spbx_continue5_thi,5,6,1,1);
    glc->addWidget(vedio_spbx_continue6_thi,6,6,1,1);
    glc->addWidget(vedio_spbx_continue7_thi,7,6,1,1);


    vedio_spby_continue1_thi=new QSpinBox;
    vedio_spby_continue2_thi=new QSpinBox;
    vedio_spby_continue3_thi=new QSpinBox;
    vedio_spby_continue4_thi=new QSpinBox;
    vedio_spby_continue5_thi=new QSpinBox;
    vedio_spby_continue6_thi=new QSpinBox;
    vedio_spby_continue7_thi=new QSpinBox;

    vedio_spby_continue1_thi->setRange(0,9999);
    vedio_spby_continue2_thi->setRange(0,9999);
    vedio_spby_continue3_thi->setRange(0,9999);
    vedio_spby_continue4_thi->setRange(0,9999);
    vedio_spby_continue5_thi->setRange(0,9999);
    vedio_spby_continue6_thi->setRange(0,9999);
    vedio_spby_continue7_thi->setRange(0,9999);

    glc->addWidget(vedio_spby_continue1_thi,1,7,1,1);
    glc->addWidget(vedio_spby_continue2_thi,2,7,1,1);
    glc->addWidget(vedio_spby_continue3_thi,3,7,1,1);
    glc->addWidget(vedio_spby_continue4_thi,4,7,1,1);
    glc->addWidget(vedio_spby_continue5_thi,5,7,1,1);
    glc->addWidget(vedio_spby_continue6_thi,6,7,1,1);
    glc->addWidget(vedio_spby_continue7_thi,7,7,1,1);
    g3->setLayout(glc);

    QVBoxLayout *v10=new QVBoxLayout;
    v10->addLayout(h5);
    v10->addLayout(v9);
    v10->addWidget(continue_vediochoose_thi);
    v10->addLayout(v7);
    v10->addWidget(continue_autogate_thi);
    v10->addLayout(gl4);
    v10->addLayout(v31);
    v10->addLayout(glct2);
    v10->addWidget(g3);

    //

    w_ContinueField_1_thi->setLayout(v10);

    connect(vedio_change3_thi,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_continue_thi(int)));

    connect(btn_vediosersor_default_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_thi()));
    connect(btn_vediosersor_update_thi,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_thi()));
    connect(continueChanelNum_thi,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_thi(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(continueenable_thi,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_thi(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(continuechanelname_thi,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_thi(int)));//
    connect(continue_vediohaveornot_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_thi(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(continue_vedio_dpi_thi,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_thi(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(continue_gateshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_thi(int)));
    connect(continue_bullshow_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_thi(int)));
    connect(continue_xy_ratio_thi,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_thi()));
    connect(continue_gateshow_thi,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_thi()));
    connect(continue_bullshow_thi,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_thi()));
    connect(continue_autogate_thi,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_thi(int)));
    connect(continue_gate_sizex_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_thi()));
    connect(continue_gate_sizey_thi,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_thi()));
    connect(continue_gatelocationx_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_thi()));
    connect(continue_gatelocationy_thi,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_thi()));
    connect(continue_set_azimuth_thi,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_thi()));
    connect(continue_set_pitch_thi,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_thi()));
    connect(continue_set_zoom_thi,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_thi()));
    connect(continue_search_azimuth_thi,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_thi()));
    connect(continue_search_pitch_thi ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_thi()));
    connect(continue_search_zoom_thi,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_thi()));
    connect(continue_vediohaveornot_thi,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_thi()));
    connect(test_1_thi,SIGNAL(activated(int)),this,SLOT(test_1_Slot_thi()));
    connect(vedio_l1_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l1_continue_Slot_thi()));
     connect(vedio_l2_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l2_continue_Slot_thi()));
      connect(vedio_l3_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l3_continue_Slot_thi()));
       connect(vedio_l4_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l4_continue_Slot_thi()));
        connect(vedio_l5_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l5_continue_Slot_thi()));
         connect(vedio_l6_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l6_continue_Slot_thi()));
          connect(vedio_l7_continue_thi,SIGNAL(activated(int)),this,SLOT(vedio_l7_continue_Slot_thi()));

    connect( vedio_continue_Fov0_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov0_Slot_thi()));
    connect( vedio_continue_Fov1_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov1_Slot_thi()));
    connect( vedio_continue_Fov2_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov2_Slot_thi()));
    connect( vedio_continue_Fov3_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov3_Slot_thi()));
    connect( vedio_continue_Fov4_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov4_Slot_thi()));
    connect( vedio_continue_Fov5_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov5_Slot_thi()));
    connect( vedio_continue_Fov6_thi,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov6_Slot_thi()));
     connect( continue_vertical1_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical1_Slot_thi()));
     connect( continue_vertical2_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical2_Slot_thi()));
     connect( continue_vertical3_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical3_Slot_thi()));
     connect( continue_vertical4_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical4_Slot_thi()));
     connect( continue_vertical5_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical5_Slot_thi()));
     connect( continue_vertical6_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical6_Slot_thi()));
     connect( continue_vertical7_thi,SIGNAL(returnPressed()),this,SLOT(continue_vertical7_Slot_thi()));

      connect( vedio_spbx_continue1_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_thi()));
       connect( vedio_spbx_continue2_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue2_Slot_thi()));
      connect( vedio_spbx_continue3_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue3_Slot_thi()));
      connect( vedio_spbx_continue4_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue4_Slot_thi()));
       connect( vedio_spbx_continue5_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue5_Slot_thi()));
       connect( vedio_spbx_continue6_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue6_Slot_thi()));
       connect( vedio_spbx_continue7_thi,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue7_Slot_thi()));

       connect( vedio_spby_continue1,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue1_Slot()));
       connect( vedio_spby_continue2,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue2_Slot()));
       connect( vedio_spby_continue3,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue3_Slot()));
       connect( vedio_spby_continue4,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue4_Slot()));
       connect( vedio_spby_continue5,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue5_Slot()));
       connect( vedio_spby_continue6,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue6_Slot()));
       connect( vedio_spby_continue7,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue7_Slot()));


}

void MainWindow::init_vedioCfg_fou(){

    /*固定视场*/

    w_sersor_1_fou = new MyWidget;
    w_seitchField_1_fou = new MyWidget;
    w_ContinueField_1_fou=new MyWidget;
    w_sersor_1_fou->setWindowTitle("摄像机配置");
    btn_vediosersor_fix_default_fou=new QPushButton;
    btn_vediosersor_fix_update_fou=new QPushButton;
    btn_vediosersor_fix_default_fou->setText("默认");
    btn_vediosersor_fix_update_fou->setText("保存");
    QVBoxLayout *v11=new QVBoxLayout;
    v11->addWidget(btn_vediosersor_fix_default_fou);
    v11->addWidget(btn_vediosersor_fix_update_fou);
    QLabel *label30=new QLabel;
    label30->setText("通道4");
    QHBoxLayout *h11=new QHBoxLayout;
    h11->addLayout(v11);
    h11->addWidget(label30);

    fixChanelNum_fou = new  QCheckBox();
    fixChanelNum_fou->setText("通道号");
    fixchanelname_fou = new QLineEdit;
    fixenable_fou = new  QCheckBox();
    fixenable_fou->setText("使能");
    QLabel *label40=new QLabel;
    label40->setText("通道名称");
    QHBoxLayout *v21=new QHBoxLayout;
    v21->addWidget(fixChanelNum_fou);
    v21->addWidget(label40);
    v21->addWidget(fixchanelname_fou);
    v21->addWidget(fixenable_fou);

    fix_vediohaveornot_fou = new  QCheckBox();
    fix_vedio_dpi_fou = new QComboBox;
    fix_xy_ratio_fou = new QLineEdit;
    fix_vedio_dpi_fou->addItem("1080P@25HZ");
    fix_vedio_dpi_fou->addItem("1080P@30HZ");
    fix_vedio_dpi_fou->addItem("1080P@60HZ");
    fix_vedio_dpi_fou->addItem("720P@50HZ");
    fix_vedio_dpi_fou->addItem("720P@60HZ");
    vedio_change1_fou = new QComboBox;
    vedio_change1_fou->addItem("固定视场");
    vedio_change1_fou->addItem("可切换视场");
    vedio_change1_fou->addItem("连续视场");
    fix_vediochoose_fou = new QGroupBox();
    QFormLayout *f4=new QFormLayout();
    f4->addRow(vedio_s_fou[0],fix_vediohaveornot_fou);
    f4->addRow(vedio_s_fou[1],fix_vedio_dpi_fou);
    f4->addRow(vedio_s_fou[2],vedio_change1_fou);
    f4->addRow(vedio_s_fou[3],fix_xy_ratio_fou);
    fix_vediochoose_fou->setLayout(f4);

    fix_gateshow_fou = new  QCheckBox();
    fix_bullshow_fou = new  QCheckBox();
    fix_gateshow_fou->setText("波门显示");
    fix_bullshow_fou->setText("靶心显示");
    QHBoxLayout *v6=new QHBoxLayout;
    v6->addWidget(fix_gateshow_fou);
    v6->addWidget(fix_bullshow_fou);

    fix_autogate_fou = new  QCheckBox();
    fix_autogate_fou->setText("自动波门");

    QLabel *label51=new QLabel;
    label51->setText("波门尺寸X");
    QLabel *label52=new QLabel;
    label52->setText("波门尺寸Y");
    QLabel *label53=new QLabel;
    label53->setText("波门位置X");
    QLabel *label54=new QLabel;
    label54->setText("波门位置Y");
    fix_gate_sizex_fou=new QLineEdit;
    fix_gate_sizey_fou=new QLineEdit;
    fix_gatelocationx_fou=new QLineEdit;
    fix_gatelocationy_fou=new QLineEdit;
    QGridLayout *gl1=new QGridLayout;
    gl1->addWidget(label51,0,0);
    gl1->addWidget(fix_gate_sizex_fou,0,1);
    gl1->addWidget(label52,0,3);
    gl1->addWidget(fix_gate_sizey_fou,0,4);
    gl1->addWidget(label53,1,0);
    gl1->addWidget(fix_gatelocationx_fou,1,1);
    gl1->addWidget(label54,1,3);
    gl1->addWidget(fix_gatelocationy_fou,1,4);
    //2.10新增
     QGridLayout *gl12=new QGridLayout;
    set_azimuth_fou =new QPushButton;
    set_pitch_fou =new QPushButton;
    set_zoom_fou  =new QPushButton;
    search_azimuth_fou=new QPushButton;
    search_pitch_fou=new QPushButton;
    search_zoom_fou=new QPushButton;
    set_azimuth_fou->setText("设置");
    set_pitch_fou->setText("设置");
    set_zoom_fou->setText("设置");
    search_azimuth_fou->setText("查询");
    search_pitch_fou->setText("查询");
    search_zoom_fou->setText("查询");

    QLabel *labela=new QLabel;
    labela->setText("方位角");
    QLabel *labelp=new QLabel;
    labelp->setText("俯仰角");
    QLabel *labelz=new QLabel;
    labelz->setText("zoom位置");
    ledt_set_azimuth_fou=new QLineEdit;
    ledt_set_pitch_fou=new QLineEdit;
    ledt_set_zoom_fou=new QLineEdit;

    ledt_search_azimuth_fou=new QLineEdit;
    ledt_search_pitch_fou=new QLineEdit;
    ledt_search_zoom_fou=new QLineEdit;

    gl12->addWidget(labela,1,0,1,1);
    gl12->addWidget(labelp,2,0,1,1);
    gl12->addWidget(labelz,3,0,1,1);


    gl12->addWidget(ledt_set_azimuth_fou,1,2,1,1);
    gl12->addWidget(ledt_set_pitch_fou,2,2,1,1);
    gl12->addWidget(ledt_set_zoom_fou,3,2,1,1);

    gl12->addWidget(set_azimuth_fou,1,3,1,1);
    gl12->addWidget(set_pitch_fou,2,3,1,1);
    gl12->addWidget(set_zoom_fou,3,3,1,1);
    gl12->addWidget(ledt_search_azimuth_fou,1,4,1,1);
    gl12->addWidget(ledt_search_pitch_fou,2,4,1,1);
    gl12->addWidget(ledt_search_zoom_fou,3,4,1,1);

    gl12->addWidget(search_azimuth_fou,1,5,1,1);
    gl12->addWidget(search_pitch_fou,2,5,1,1);
    gl12->addWidget(search_zoom_fou,3,5,1,1);
//

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");
    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l15=new QLabel;
    l15->setText("垂直视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");
    fix_lEdt_fou=new QLineEdit;
    fix_vertical_fou=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    QLabel* l1v=new QLabel;
    l1v->setText("度");
    fix_sp_fou=new QSpinBox;
    fix_sp2_fou=new QSpinBox;
    fix_sp_fou->setRange(0,9999);
    fix_sp2_fou->setRange(0,9999);
    QGridLayout *gl3=new QGridLayout;
    gl3->addWidget(l11,0,0,1,1);
    gl3->addWidget(l14,0,1,1,1);

    gl3->addWidget(l15,0,2,1,1);
    gl3->addWidget(l14,0,3,1,1);

    gl3->addWidget(l14,0,4,1,1);
    gl3->addWidget(l12,0,5,1,1);
    gl3->addWidget(l13,0,6,1,1);
    gl3->addWidget(l14,0,7,1,1);
    gl3->addWidget(fix_lEdt_fou,1,0,1,1);
    gl3->addWidget(l1d,1,1,1,1);
    gl3->addWidget(fix_vertical_fou,1,2,1,1);
    gl3->addWidget(l1v,1,3,1,1);
    gl3->addWidget(l14,1,4,1,1);
    gl3->addWidget(fix_sp_fou,1,5,1,1);
    gl3->addWidget(fix_sp2_fou,1,6,1,1);
    g->setLayout(gl3);

    QVBoxLayout *v0=new QVBoxLayout;
    v0->addLayout(h11);
    v0->addLayout(v21);
    v0->addWidget(fix_vediochoose_fou);
    v0->addLayout(v6);
    v0->addWidget(fix_autogate_fou);
    v0->addLayout(gl1);
    v0->addLayout(gl12);
    v0->addWidget(g);
    w_sersor_1_fou->setLayout(v0);
    connect(vedio_change1_fou,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix_fou(int)));

    connect(btn_vediosersor_fix_default_fou,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fou()));
    connect(btn_vediosersor_fix_update_fou,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fou()));
    connect(fixChanelNum_fou,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fou(int)));
    connect(fixchanelname_fou,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fou(int)));
    connect(fixenable_fou,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fou(int)));
    connect(fix_vediohaveornot_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fou(int)));
    connect(fix_vedio_dpi_fou,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fou(int)));
    connect(fix_xy_ratio_fou,SIGNAL(returnPressed()),this,SLOT(fix_xy_ratio_Slot_fou()));
    connect(fix_gateshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fou(int)));
    connect(fix_bullshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fou(int)));
    connect(fix_autogate_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fou(int)));
    connect(fix_gate_sizex_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fou()));
    connect(fix_gate_sizey_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fou()));
    connect(fix_gatelocationx_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fou()));
    connect(fix_gatelocationy_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fou()));
    connect(set_azimuth_fou,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fou()));
    connect(set_pitch_fou,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fou()));
    connect(set_zoom_fou,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fou()));
    connect(search_azimuth_fou,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fou()));
    connect(search_pitch_fou ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fou()));
    connect(search_zoom_fou,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fou()));
   // connect(ledt_set_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_set_azimuth_Slot()));
   // connect(ledt_set_pitch,SIGNAL(activated(int)),this,SLOT(ledt_set_pitch_Slot()));
   // connect(ledt_set_zoom,SIGNAL(activated(int)),this,SLOT(ledt_set_zoom_Slot()));
   // connect(ledt_search_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_search_azimuth_Slot()));
   // connect(ledt_search_pitch,SIGNAL(activated(int)),this,SLOT(ledt_search_pitch_Slot()));
   // connect(ledt_search_zoom,SIGNAL(activated(int)),this,SLOT(ledt_search_zoom_Slot()));
    connect(fix_lEdt_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(fix_vertical_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(fix_sp_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(fix_sp2_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));

    /*可切换视场*/

    w_seitchField_1_fou->setWindowTitle("摄像机配置");
    btn_vediosersor_default_fou=new QPushButton;
    btn_vediosersor_update_fou=new QPushButton;
    btn_vediosersor_default_fou->setText("默认");
    btn_vediosersor_update_fou->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_vediosersor_default_fou);
    v1->addWidget(btn_vediosersor_update_fou);
    QLabel *label1=new QLabel;
    label1->setText("通道4");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label1);

    ChanelNum_fou = new  QCheckBox();
    ChanelNum_fou->setText("通道号");
    chanelname_fou = new QLineEdit;
    enable_fou = new  QCheckBox();
    enable_fou->setText("使能");

    QLabel *label2=new QLabel;
    label2->setText("通道名称");
    QHBoxLayout *v2=new QHBoxLayout;
    v2->addWidget(ChanelNum_fou);
    v2->addWidget(label2);
    v2->addWidget(chanelname_fou);
    v2->addWidget(enable_fou);

    vediohaveornot_fou = new  QCheckBox();
    vedio_dpi_fou = new QComboBox;
    xy_ratio_fou = new QLineEdit;
    vedio_dpi_fou->addItem("1080P@25HZ");
    vedio_dpi_fou->addItem("1080P@30HZ");
    vedio_dpi_fou->addItem("1080P@60HZ");
    vedio_dpi_fou->addItem("720P@50HZ");
    vedio_dpi_fou->addItem("720P@60HZ");
    vedio_change2_fou = new QComboBox;
    vedio_change2_fou->addItem("可切换视场");
    vedio_change2_fou->addItem("固定视场");
    vedio_change2_fou->addItem("连续视场");

    vediochoose_fou = new QGroupBox();
    QFormLayout *f3=new QFormLayout();
    f3->addRow(vedio_s_fou[0],vediohaveornot_fou);
    f3->addRow(vedio_s_fou[1],vedio_dpi_fou);
    f3->addRow(vedio_s_fou[2],vedio_change2_fou);
    f3->addRow(vedio_s_fou[3],xy_ratio_fou);
    vediochoose_fou->setLayout(f3);

    connect(vedio_change2_fou,SIGNAL(activated(int)),this,SLOT(vedio_toSensor_switch_fou(int)));
    gateshow_fou = new  QCheckBox();
    bullshow_fou = new  QCheckBox();
    gateshow_fou->setText("波门显示");
    bullshow_fou->setText("靶心显示");
    QHBoxLayout *v3=new QHBoxLayout;
    v3->addWidget(gateshow_fou);
    v3->addWidget(bullshow_fou);

    autogate_fou = new  QCheckBox();
    autogate_fou->setText("自动波门");

    QLabel *label3=new QLabel;
    label3->setText("波门尺寸X");
    QLabel *label4=new QLabel;
    label4->setText("波门尺寸Y");
    QLabel *label5=new QLabel;
    label5->setText("波门位置X");
    QLabel *label6=new QLabel;
    label6->setText("波门位置Y");
    gate_sizex_fou=new QLineEdit;
    gate_sizey_fou=new QLineEdit;
    gatelocationx_fou=new QLineEdit;
    gatelocationy_fou=new QLineEdit;
    QGridLayout *gl=new QGridLayout;
    gl->addWidget(label3,0,0);
    gl->addWidget(gate_sizex_fou,0,1);
    gl->addWidget(label4,0,3);
    gl->addWidget(gate_sizey_fou,0,4);
    gl->addWidget(label5,1,0);
    gl->addWidget(gatelocationx_fou,1,1);
    gl->addWidget(label6,1,3);
    gl->addWidget(gatelocationy_fou,1,4);

    QHBoxLayout *h2=new QHBoxLayout;
    QLabel *label7=new QLabel;
    label7->setText("测试现场等级");
    vedio_fovclass_fou = new QComboBox;
    vedio_fovclass_fou->addItem("可切换视场1");
    vedio_fovclass_fou->addItem("可切换视场2");
    vedio_fovclass_fou->addItem("可切换视场3");
    vedio_fovclass_fou->addItem("可切换视场4");
    vedio_fovclass_fou->addItem("可切换视场5");
    h2->addWidget(label7);
    h2->addWidget(vedio_fovclass_fou);
    //

    QGridLayout *glc2=new QGridLayout;
   Change_set_azimuth_fou =new QPushButton;
   Change_set_pitch_fou =new QPushButton;
   Change_set_zoom_fou  =new QPushButton;
   Change_search_azimuth_fou=new QPushButton;
   Change_search_pitch_fou=new QPushButton;
   Change_search_zoom_fou=new QPushButton;
   Change_set_azimuth_fou->setText("设置");
   Change_set_pitch_fou->setText("设置");
   Change_set_zoom_fou->setText("设置");
   Change_search_azimuth_fou->setText("查询");
   Change_search_pitch_fou->setText("查询");
   Change_search_zoom_fou->setText("查询");

   Change_ledt_set_azimuth_fou=new QLineEdit;
   Change_ledt_set_pitch_fou=new QLineEdit;
   Change_ledt_set_zoom_fou=new QLineEdit;

   Change_ledt_search_azimuth_fou=new QLineEdit;
   Change_ledt_search_pitch_fou=new QLineEdit;
   Change_ledt_search_zoom_fou=new QLineEdit;

   QLabel *labelac=new QLabel;
   labelac->setText("方位角");
   QLabel *labelpc=new QLabel;
   labelpc->setText("俯仰角");
   QLabel *labelzc=new QLabel;
   labelzc->setText("zoom位置");

   glc2->addWidget(labelac,1,0,1,1);
   glc2->addWidget(labelpc,2,0,1,1);
   glc2->addWidget(labelzc,3,0,1,1);


   glc2->addWidget(Change_ledt_set_azimuth_fou,1,2,1,1);
   glc2->addWidget(Change_ledt_set_pitch_fou,2,2,1,1);
   glc2->addWidget(Change_ledt_set_zoom_fou,3,2,1,1);

   glc2->addWidget(Change_set_azimuth_fou,1,3,1,1);
   glc2->addWidget(Change_set_pitch_fou,2,3,1,1);
   glc2->addWidget(Change_set_zoom_fou,3,3,1,1);
   glc2->addWidget(Change_ledt_search_azimuth_fou,1,4,1,1);
   glc2->addWidget(Change_ledt_search_pitch_fou,2,4,1,1);
   glc2->addWidget(Change_ledt_search_zoom_fou,3,4,1,1);

   glc2->addWidget(Change_search_azimuth_fou,1,5,1,1);
   glc2->addWidget(Change_search_pitch_fou,2,5,1,1);
   glc2->addWidget(Change_search_zoom_fou,3,5,1,1);


    //

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");
    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l25=new QLabel;
    l25->setText("垂直视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l25,0,3,1,1);
    gl2->addWidget(l22,0,5,1,1);
    gl2->addWidget(l23,0,6,1,1);
    gl2->addWidget(l24,0,7,1,1);

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
    vedio_s1_Fov0_fou=new QLineEdit;
    vedio_s1_Fov1_fou=new QLineEdit;
    vedio_s1_Fov2_fou=new QLineEdit;
    vedio_s1_Fov3_fou=new QLineEdit;
    vedio_s1_Fov4_fou=new QLineEdit;
    gl2->addWidget(vedio_s1_Fov0_fou,1,1,1,1);
    gl2->addWidget(vedio_s1_Fov1_fou,2,1,1,1);
    gl2->addWidget(vedio_s1_Fov2_fou,3,1,1,1);
    gl2->addWidget(vedio_s1_Fov3_fou,4,1,1,1);
    gl2->addWidget(vedio_s1_Fov4_fou,5,1,1,1);

    Change_vertical1_fou=new QLineEdit;
    Change_vertical2_fou=new QLineEdit;
    Change_vertical3_fou=new QLineEdit;
    Change_vertical4_fou=new QLineEdit;
    Change_vertical5_fou=new QLineEdit;
    gl2->addWidget(Change_vertical1_fou,1,3,1,1);
    gl2->addWidget(Change_vertical2_fou,2,3,1,1);
    gl2->addWidget(Change_vertical3_fou,3,3,1,1);
    gl2->addWidget(Change_vertical4_fou,4,3,1,1);
    gl2->addWidget(Change_vertical5_fou,5,3,1,1);

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

    QLabel* l1c21=new QLabel;
    QLabel* l1c22=new QLabel;
    QLabel* l1c23=new QLabel;
    QLabel* l1c24=new QLabel;
    QLabel* l1c25=new QLabel;
    l1c21->setText("度");
    l1c22->setText("度");
    l1c23->setText("度");
    l1c24->setText("度");
    l1c25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    gl2->addWidget(l1c21,1,4,1,1);
    gl2->addWidget(l1c22,2,4,1,1);
    gl2->addWidget(l1c23,3,4,1,1);
    gl2->addWidget(l1c24,4,4,1,1);
    gl2->addWidget(l1c25,5,4,1,1);


    vedio_spbx_switch1_fou=new QSpinBox;
    vedio_spbx_switch2_fou=new QSpinBox;
    vedio_spbx_switch3_fou=new QSpinBox;
    vedio_spbx_switch4_fou=new QSpinBox;
    vedio_spbx_switch5_fou=new QSpinBox;
    vedio_spbx_switch1_fou->setRange(0,9999);
    vedio_spbx_switch2_fou->setRange(0,9999);
    vedio_spbx_switch3_fou->setRange(0,9999);
    vedio_spbx_switch4_fou->setRange(0,9999);
    vedio_spbx_switch5_fou->setRange(0,9999);
    gl2->addWidget(vedio_spbx_switch1_fou,1,5,1,1);
    gl2->addWidget(vedio_spbx_switch2_fou,2,5,1,1);
    gl2->addWidget(vedio_spbx_switch3_fou,3,5,1,1);
    gl2->addWidget(vedio_spbx_switch4_fou,4,5,1,1);
    gl2->addWidget(vedio_spbx_switch5_fou,5,5,1,1);

    vedio_spby_switch1_fou=new QSpinBox;
    vedio_spby_switch2_fou=new QSpinBox;
    vedio_spby_switch3_fou=new QSpinBox;
    vedio_spby_switch4_fou=new QSpinBox;
    vedio_spby_switch5_fou=new QSpinBox;
    vedio_spby_switch1_fou->setRange(0,9999);
    vedio_spby_switch2_fou->setRange(0,9999);
    vedio_spby_switch3_fou->setRange(0,9999);
    vedio_spby_switch4_fou->setRange(0,9999);
    vedio_spby_switch5_fou->setRange(0,9999);
    gl2->addWidget(vedio_spby_switch1_fou,1,6,1,1);
    gl2->addWidget(vedio_spby_switch2_fou,2,6,1,1);
    gl2->addWidget(vedio_spby_switch3_fou,3,6,1,1);
    gl2->addWidget(vedio_spby_switch4_fou,4,6,1,1);
    gl2->addWidget(vedio_spby_switch5_fou,5,6,1,1);

    g2->setLayout(gl2);
    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(glc2);
    v22->addWidget(g2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(v1);

    v->addLayout(h1);

    v->addLayout(v2);
    v->addWidget(vediochoose_fou);
    v->addLayout(v3);
    v->addWidget(autogate_fou);
    v->addLayout(gl);
  //v->addLayout(h2);
    v->addLayout(v22);
    w_seitchField_1_fou->setLayout(v);
    connect(btn_vediosersor_default_fou,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fou()));
    connect(btn_vediosersor_update,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fou()));
    connect(ChanelNum_fou,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fou(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(enable_fou,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fou(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(chanelname_fou,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fou(int)));//
    connect(vediohaveornot_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fou(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(vedio_dpi_fou,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fou(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(gateshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fou(int)));
    connect(bullshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fou(int)));
    connect(xy_ratio_fou,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_fou()));
    connect(gateshow_fou,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_fou()));
    connect(bullshow_fou,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_fou()));
    connect(autogate_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fou(int)));
    connect(gate_sizex_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fou()));
    connect(gate_sizey_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fou()));
    connect(gatelocationx_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fou()));
    connect(gatelocationy_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fou()));
    connect(Change_set_azimuth_fou,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fou()));
    connect(Change_set_pitch_fou,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fou()));
    connect(Change_set_zoom_fou,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fou()));
    connect(Change_search_azimuth_fou,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fou()));
    connect(Change_search_pitch_fou ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fou()));
    connect(Change_search_zoom_fou,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fou()));
    connect( vedio_fovclass_fou,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_fou()));

    connect(vedio_s1_Fov0_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(Change_vertical1_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(vedio_spbx_switch1_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_spby_switch1_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_s1_Fov1_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(Change_vertical2_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(vedio_spbx_switch2_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_spby_switch2_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_s1_Fov2_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(Change_vertical3_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(vedio_spbx_switch3_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_spby_switch3_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_s1_Fov3_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(Change_vertical4_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(vedio_spbx_switch4_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_spby_switch4_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_s1_Fov4_fou,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fou()));
    connect(Change_vertical5_fou,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fou()));
    connect(vedio_spbx_switch5_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));
    connect(vedio_spby_switch5_fou,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fou()));


    /*连续视场*/

    w_ContinueField_1_fou->setWindowTitle("摄像机配置");
    btn_vediosersor_continue_default_fou=new QPushButton;
    btn_vediosersor_continue_update_fou=new QPushButton;
    btn_vediosersor_continue_default_fou->setText("默认");
    btn_vediosersor_continue_update_fou->setText("保存");
    QVBoxLayout *v8=new QVBoxLayout;
    v8->addWidget(btn_vediosersor_continue_default_fou);
    v8->addWidget(btn_vediosersor_continue_update_fou);
    QLabel *label60=new QLabel;
    label60->setText("通道4");
    QHBoxLayout *h5=new QHBoxLayout;
    h5->addLayout(v8);
    h5->addWidget(label60);

    continueChanelNum_fou = new  QCheckBox();
    continueChanelNum_fou->setText("通道号");
    continuechanelname_fou = new QLineEdit;
    continueenable_fou = new  QCheckBox();
    continueenable_fou->setText("使能");
    QLabel *label61=new QLabel;
    label61->setText("通道名称");
    QHBoxLayout *v9=new QHBoxLayout;
    v9->addWidget(continueChanelNum_fou);
    v9->addWidget(label61);
    v9->addWidget(continuechanelname_fou);
    v9->addWidget(continueenable_fou);

    continue_vediohaveornot_fou = new  QCheckBox();
    continue_vedio_dpi_fou = new QComboBox;
    continue_xy_ratio_fou = new QLineEdit;
    continue_vedio_dpi_fou->addItem("1080P@25HZ");
    continue_vedio_dpi_fou->addItem("1080P@30HZ");
    continue_vedio_dpi_fou->addItem("1080P@60HZ");
    continue_vedio_dpi_fou->addItem("720P@50HZ");
    continue_vedio_dpi_fou->addItem("720P@60HZ");
    vedio_change3_fou= new QComboBox;
    vedio_change3_fou->addItem("连续视场");
    vedio_change3_fou->addItem("固定视场");
    vedio_change3_fou->addItem("可切换视场");
    continue_vediochoose_fou = new QGroupBox();
    QFormLayout *f5=new QFormLayout();
    f5->addRow(vedio_s_fou[0],continue_vediohaveornot_fou);
    f5->addRow(vedio_s_fou[1],continue_vedio_dpi_fou);
    f5->addRow(vedio_s_fou[2],vedio_change3_fou);
    f5->addRow(vedio_s_fou[3],continue_xy_ratio_fou);
    continue_vediochoose_fou->setLayout(f5);

    continue_gateshow_fou = new  QCheckBox();
    continue_bullshow_fou = new  QCheckBox();
    continue_gateshow_fou->setText("波门显示");
    continue_bullshow_fou->setText("靶心显示");
    QHBoxLayout *v7=new QHBoxLayout;
    v7->addWidget(continue_gateshow_fou);
    v7->addWidget(continue_bullshow_fou);

    continue_autogate_fou = new  QCheckBox();
    continue_autogate_fou->setText("自动波门");

    QLabel *label55=new QLabel;
    label55->setText("波门尺寸X");
    QLabel *label56=new QLabel;
    label56->setText("波门尺寸Y");
    QLabel *label57=new QLabel;
    label57->setText("波门位置X");
    QLabel *label58=new QLabel;
    label58->setText("波门位置Y");
    continue_gate_sizex_fou=new QLineEdit;
    continue_gate_sizey_fou=new QLineEdit;
    continue_gatelocationx_fou=new QLineEdit;
    continue_gatelocationy_fou=new QLineEdit;
    QGridLayout *gl4=new QGridLayout;
    gl4->addWidget(label55,0,0);
    gl4->addWidget(continue_gate_sizex_fou,0,1);
    gl4->addWidget(label56,0,3);
    gl4->addWidget(continue_gate_sizey_fou,0,4);
    gl4->addWidget(label57,1,0);
    gl4->addWidget(continue_gatelocationx_fou,1,1);
    gl4->addWidget(label58,1,3);
    gl4->addWidget(continue_gatelocationy_fou,1,4);

    QHBoxLayout *v31=new QHBoxLayout;
    QLabel *label70=new QLabel;
    label70->setText("测试视场");
    test_1_fou = new QLineEdit;
    v31->addWidget(label70);
    v31->addWidget(test_1_fou);
//
    QGridLayout *glct2=new QGridLayout;
   continue_set_azimuth_fou =new QPushButton;
   continue_set_pitch_fou =new QPushButton;
   continue_set_zoom_fou  =new QPushButton;
   continue_search_azimuth_fou=new QPushButton;
   continue_search_pitch_fou=new QPushButton;
   continue_search_zoom_fou=new QPushButton;
   continue_set_azimuth_fou->setText("设置");
   continue_set_pitch_fou->setText("设置");
   continue_set_zoom_fou->setText("设置");
   continue_search_azimuth_fou->setText("查询");
   continue_search_pitch_fou->setText("查询");
   continue_search_zoom_fou->setText("查询");

   continue_ledt_set_azimuth_fou=new QLineEdit;
   continue_ledt_set_pitch_fou=new QLineEdit;
   continue_ledt_set_zoom_fou=new QLineEdit;

   continue_ledt_search_azimuth_fou=new QLineEdit;
   continue_ledt_search_pitch_fou=new QLineEdit;
   continue_ledt_search_zoom_fou=new QLineEdit;

   QLabel *labelact=new QLabel;
   labelact->setText("方位角");
   QLabel *labelpct=new QLabel;
   labelpct->setText("俯仰角");
   QLabel *labelzct=new QLabel;
   labelzct->setText("zoom位置");

   glct2->addWidget(labelact,1,0,1,1);
   glct2->addWidget(labelpct,2,0,1,1);
   glct2->addWidget(labelzct,3,0,1,1);


   glct2->addWidget(continue_ledt_set_azimuth_fou,1,2,1,1);
   glct2->addWidget(continue_ledt_set_pitch_fou,2,2,1,1);
   glct2->addWidget(continue_ledt_set_zoom_fou,3,2,1,1);

   glct2->addWidget(continue_set_azimuth_fou,1,3,1,1);
   glct2->addWidget(continue_set_pitch_fou,2,3,1,1);
   glct2->addWidget(continue_set_zoom_fou,3,3,1,1);
   glct2->addWidget(continue_ledt_search_azimuth_fou,1,4,1,1);
   glct2->addWidget(continue_ledt_search_pitch_fou,2,4,1,1);
   glct2->addWidget(continue_ledt_search_zoom_fou,3,4,1,1);

   glct2->addWidget(continue_search_azimuth_fou,1,5,1,1);
   glct2->addWidget(continue_search_pitch_fou,2,5,1,1);
   glct2->addWidget(continue_search_zoom_fou,3,5,1,1);

   //


    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");
    QGridLayout *glc=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l35=new QLabel;
    l35->setText("垂直视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    QLabel* l36=new QLabel;
    l36->setText(" ");
    glc->addWidget(l30,0,1,1,1);
    glc->addWidget(l31,0,2,1,1);
    glc->addWidget(l35,0,4,1,1);
    glc->addWidget(l36,0,5,1,1);
    glc->addWidget(l32,0,6,1,1);
    glc->addWidget(l33,0,7,1,1);
    glc->addWidget(l34,0,8,1,1);


    vedio_l1_continue_fou=new QLineEdit;
    vedio_l2_continue_fou=new QLineEdit;
    vedio_l3_continue_fou=new QLineEdit;
    vedio_l4_continue_fou=new QLineEdit;
    vedio_l5_continue_fou=new QLineEdit;
    vedio_l6_continue_fou=new QLineEdit;
    vedio_l7_continue_fou=new QLineEdit;
    glc->addWidget(vedio_l1_continue_fou,1,1,1,1);
    glc->addWidget(vedio_l2_continue_fou,2,1,1,1);
    glc->addWidget(vedio_l3_continue_fou,3,1,1,1);
    glc->addWidget(vedio_l4_continue_fou,4,1,1,1);
    glc->addWidget(vedio_l5_continue_fou,5,1,1,1);
    glc->addWidget(vedio_l6_continue_fou,6,1,1,1);
    glc->addWidget(vedio_l7_continue_fou,7,1,1,1);

    vedio_continue_Fov0_fou = new QLineEdit;
    vedio_continue_Fov1_fou = new QLineEdit;
    vedio_continue_Fov2_fou = new QLineEdit;
    vedio_continue_Fov3_fou = new QLineEdit;
    vedio_continue_Fov4_fou = new QLineEdit;
    vedio_continue_Fov5_fou= new QLineEdit;
    vedio_continue_Fov6_fou = new QLineEdit;
    glc->addWidget(vedio_continue_Fov0_fou,1,2,1,1);
    glc->addWidget(vedio_continue_Fov1_fou,2,2,1,1);
    glc->addWidget(vedio_continue_Fov2_fou,3,2,1,1);
    glc->addWidget(vedio_continue_Fov3_fou,4,2,1,1);
    glc->addWidget(vedio_continue_Fov4_fou,5,2,1,1);
    glc->addWidget(vedio_continue_Fov5_fou,6,2,1,1);
    glc->addWidget(vedio_continue_Fov6_fou,7,2,1,1);

    continue_vertical1_fou = new QLineEdit;
    continue_vertical2_fou = new QLineEdit;
    continue_vertical3_fou = new QLineEdit;
    continue_vertical4_fou = new QLineEdit;
    continue_vertical5_fou = new QLineEdit;
    continue_vertical6_fou = new QLineEdit;
    continue_vertical7_fou = new QLineEdit;
    glc->addWidget(continue_vertical1_fou,1,4,1,1);
    glc->addWidget(continue_vertical2_fou,2,4,1,1);
    glc->addWidget(continue_vertical3_fou,3,4,1,1);
    glc->addWidget(continue_vertical4_fou,4,4,1,1);
    glc->addWidget(continue_vertical5_fou,5,4,1,1);
    glc->addWidget(continue_vertical6_fou,6,4,1,1);
    glc->addWidget(continue_vertical7_fou,7,4,1,1);

    QLabel* l1dv31=new QLabel;
    QLabel* l1dv32=new QLabel;
    QLabel* l1dv33=new QLabel;
    QLabel* l1dv34=new QLabel;
    QLabel* l1dv35=new QLabel;
    QLabel* l1dv36=new QLabel;
    QLabel* l1dv37=new QLabel;
    l1dv31->setText("度");
    l1dv32->setText("度");
    l1dv33->setText("度");
    l1dv34->setText("度");
    l1dv35->setText("度");
    l1dv36->setText("度");
    l1dv37->setText("度");

    glc->addWidget(l1dv31,1,5,1,1);
    glc->addWidget(l1dv32,2,5,1,1);
    glc->addWidget(l1dv33,3,5,1,1);
    glc->addWidget(l1dv34,4,5,1,1);
    glc->addWidget(l1dv35,5,5,1,1);
    glc->addWidget(l1dv36,6,5,1,1);
    glc->addWidget(l1dv37,7,5,1,1);

    QLabel* l1d31=new QLabel;
    QLabel* l1d32=new QLabel;
    QLabel* l1d33=new QLabel;
    QLabel* l1d34=new QLabel;
    QLabel* l1d35=new QLabel;
    QLabel* l1d36=new QLabel;
    QLabel* l1d37=new QLabel;
    l1d31->setText("度");
    l1d32->setText("度");
    l1d33->setText("度");
    l1d34->setText("度");
    l1d35->setText("度");
    l1d36->setText("度");
    l1d37->setText("度");

    glc->addWidget(l1d31,1,3,1,1);
    glc->addWidget(l1d32,2,3,1,1);
    glc->addWidget(l1d33,3,3,1,1);
    glc->addWidget(l1d34,4,3,1,1);
    glc->addWidget(l1d35,5,3,1,1);
    glc->addWidget(l1d36,6,3,1,1);
    glc->addWidget(l1d37,7,3,1,1);


    vedio_spbx_continue1_fou=new QSpinBox;
    vedio_spbx_continue2_fou=new QSpinBox;
    vedio_spbx_continue3_fou=new QSpinBox;
    vedio_spbx_continue4_fou=new QSpinBox;
    vedio_spbx_continue5_fou=new QSpinBox;
    vedio_spbx_continue6_fou=new QSpinBox;
    vedio_spbx_continue7_fou=new QSpinBox;

    vedio_spbx_continue1_fou->setRange(0,9999);
    vedio_spbx_continue2_fou->setRange(0,9999);
    vedio_spbx_continue3_fou->setRange(0,9999);
    vedio_spbx_continue4_fou->setRange(0,9999);
    vedio_spbx_continue5_fou->setRange(0,9999);
    vedio_spbx_continue6_fou->setRange(0,9999);
    vedio_spbx_continue7_fou->setRange(0,9999);

    glc->addWidget(vedio_spbx_continue1_fou,1,6,1,1);
    glc->addWidget(vedio_spbx_continue2_fou,2,6,1,1);
    glc->addWidget(vedio_spbx_continue3_fou,3,6,1,1);
    glc->addWidget(vedio_spbx_continue4_fou,4,6,1,1);
    glc->addWidget(vedio_spbx_continue5_fou,5,6,1,1);
    glc->addWidget(vedio_spbx_continue6_fou,6,6,1,1);
    glc->addWidget(vedio_spbx_continue7_fou,7,6,1,1);


    vedio_spby_continue1_fou=new QSpinBox;
    vedio_spby_continue2_fou=new QSpinBox;
    vedio_spby_continue3_fou=new QSpinBox;
    vedio_spby_continue4_fou=new QSpinBox;
    vedio_spby_continue5_fou=new QSpinBox;
    vedio_spby_continue6_fou=new QSpinBox;
    vedio_spby_continue7_fou=new QSpinBox;

    vedio_spby_continue1_fou->setRange(0,9999);
    vedio_spby_continue2_fou->setRange(0,9999);
    vedio_spby_continue3_fou->setRange(0,9999);
    vedio_spby_continue4_fou->setRange(0,9999);
    vedio_spby_continue5_fou->setRange(0,9999);
    vedio_spby_continue6_fou->setRange(0,9999);
    vedio_spby_continue7_fou->setRange(0,9999);

    glc->addWidget(vedio_spby_continue1_fou,1,7,1,1);
    glc->addWidget(vedio_spby_continue2_fou,2,7,1,1);
    glc->addWidget(vedio_spby_continue3_fou,3,7,1,1);
    glc->addWidget(vedio_spby_continue4_fou,4,7,1,1);
    glc->addWidget(vedio_spby_continue5_fou,5,7,1,1);
    glc->addWidget(vedio_spby_continue6_fou,6,7,1,1);
    glc->addWidget(vedio_spby_continue7_fou,7,7,1,1);
    g3->setLayout(glc);

    QVBoxLayout *v10=new QVBoxLayout;
    v10->addLayout(h5);
    v10->addLayout(v9);
    v10->addWidget(continue_vediochoose_fou);
    v10->addLayout(v7);
    v10->addWidget(continue_autogate_fou);
    v10->addLayout(gl4);
    v10->addLayout(v31);
    v10->addLayout(glct2);
    v10->addWidget(g3);

    //

    w_ContinueField_1_fou->setLayout(v10);

    connect(vedio_change3_fou,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_continue_fou(int)));

    connect(btn_vediosersor_default_fou,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fou()));
    connect(btn_vediosersor_update_fou,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fou()));
    connect(continueChanelNum_fou,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fou(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(continueenable_fou,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fou(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(continuechanelname_fou,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fou(int)));//
    connect(continue_vediohaveornot_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fou(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(continue_vedio_dpi_fou,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fou(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(continue_gateshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fou(int)));
    connect(continue_bullshow_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fou(int)));
    connect(continue_xy_ratio_fou,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_fou()));
    connect(continue_gateshow_fou,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_fou()));
    connect(continue_bullshow_fou,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_fou()));
    connect(continue_autogate_fou,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fou(int)));
    connect(continue_gate_sizex_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fou()));
    connect(continue_gate_sizey_fou,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fou()));
    connect(continue_gatelocationx_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fou()));
    connect(continue_gatelocationy_fou,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fou()));
    connect(continue_set_azimuth_fou,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fou()));
    connect(continue_set_pitch_fou,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fou()));
    connect(continue_set_zoom_fou,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fou()));
    connect(continue_search_azimuth_fou,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fou()));
    connect(continue_search_pitch_fou ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fou()));
    connect(continue_search_zoom_fou,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fou()));
    connect(continue_vediohaveornot_fou,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_fou()));
    connect(test_1_fou,SIGNAL(activated(int)),this,SLOT(test_1_Slot_fou()));
    connect(vedio_l1_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l1_continue_Slot_fou()));
     connect(vedio_l2_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l2_continue_Slot_fou()));
      connect(vedio_l3_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l3_continue_Slot_fou()));
       connect(vedio_l4_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l4_continue_Slot_fou()));
        connect(vedio_l5_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l5_continue_Slot_fou()));
         connect(vedio_l6_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l6_continue_Slot_fou()));
          connect(vedio_l7_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l7_continue_Slot_fou()));

    connect( vedio_continue_Fov0_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov0_Slot_fou()));
    connect( vedio_continue_Fov1_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov1_Slot_fou()));
    connect( vedio_continue_Fov2_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov2_Slot_fou()));
    connect( vedio_continue_Fov3_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov3_Slot_fou()));
    connect( vedio_continue_Fov4_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov4_Slot_fou()));
    connect( vedio_continue_Fov5_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov5_Slot_fou()));
    connect( vedio_continue_Fov6_fou,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov6_Slot_fou()));
     connect( continue_vertical1_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical1_Slot_fou()));
     connect( continue_vertical2_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical2_Slot_fou()));
     connect( continue_vertical3_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical3_Slot_fou()));
     connect( continue_vertical4_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical4_Slot_fou()));
     connect( continue_vertical5_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical5_Slot_fou()));
     connect( continue_vertical6_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical6_Slot_fou()));
     connect( continue_vertical7_fou,SIGNAL(returnPressed()),this,SLOT(continue_vertical7_Slot_fou()));

      connect( vedio_spbx_continue1_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fou()));
       connect( vedio_spbx_continue2_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue2_Slot_fou()));
        connect( vedio_spbx_continue3_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue3_Slot_fou()));
         connect( vedio_spbx_continue4_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue4_Slot_fou()));
       connect( vedio_spbx_continue5_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue5_Slot_fou()));
        connect( vedio_spbx_continue6_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue6_Slot_fou()));
         connect( vedio_spbx_continue7_fou,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue7_Slot_fou()));

       connect( vedio_spby_continue1_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue1_Slot_fou()));
         connect( vedio_spby_continue2_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue2_Slot_fou()));
         connect( vedio_spby_continue3_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue3_Slot_fou()));
         connect( vedio_spby_continue4_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue4_Slot_fou()));
         connect( vedio_spby_continue5_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue5_Slot_fou()));
         connect( vedio_spby_continue6_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue6_Slot_fou()));
         connect( vedio_spby_continue7_fou,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue7_Slot_fou()));


}

void MainWindow::init_vedioCfg_fif(){
    /*固定视场*/

    w_sersor_1_fif = new MyWidget;
    w_seitchField_1_fif = new MyWidget;
    w_ContinueField_1_fif=new MyWidget;

    w_sersor_1_fif->setWindowTitle("摄像机配置");

    btn_vediosersor_fix_default_fif=new QPushButton;
    btn_vediosersor_fix_update_fif=new QPushButton;
    btn_vediosersor_fix_default_fif->setText("默认");
    btn_vediosersor_fix_update_fif->setText("保存");
    QVBoxLayout *v11=new QVBoxLayout;
    v11->addWidget(btn_vediosersor_fix_default_fif);
    v11->addWidget(btn_vediosersor_fix_update_fif);

    QLabel *label30=new QLabel;
    label30->setText("通道5");
    QHBoxLayout *h11=new QHBoxLayout;
    h11->addLayout(v11);
    h11->addWidget(label30);

    fixChanelNum_fif = new  QCheckBox();
    fixChanelNum_fif->setText("通道号");
    fixchanelname_fif = new QLineEdit;
    fixenable_fif = new  QCheckBox();
    fixenable_fif->setText("使能");
    QLabel *label40=new QLabel;
    label40->setText("通道名称");
    QHBoxLayout *v21=new QHBoxLayout;
    v21->addWidget(fixChanelNum_fif);
    v21->addWidget(label40);
    v21->addWidget(fixchanelname_fif);
    v21->addWidget(fixenable_fif);

    fix_vediohaveornot_fif = new  QCheckBox();
    fix_vedio_dpi_fif = new QComboBox;
    fix_xy_ratio_fif = new QLineEdit;
    fix_vedio_dpi_fif->addItem("1080P@25HZ");
    fix_vedio_dpi_fif->addItem("1080P@30HZ");
    fix_vedio_dpi_fif->addItem("1080P@60HZ");
    fix_vedio_dpi_fif->addItem("720P@50HZ");
    fix_vedio_dpi_fif->addItem("720P@60HZ");
    vedio_change1_fif = new QComboBox;
    vedio_change1_fif->addItem("固定视场");
    vedio_change1_fif->addItem("可切换视场");
    vedio_change1_fif->addItem("连续视场");
    fix_vediochoose_fif = new QGroupBox();

    QFormLayout *f4=new QFormLayout();
    f4->addRow(vedio_s_fif[0],fix_vediohaveornot_fif);
    f4->addRow(vedio_s_fif[1],fix_vedio_dpi_fif);
    f4->addRow(vedio_s_fif[2],vedio_change1_fif);
    f4->addRow(vedio_s_fif[3],fix_xy_ratio_fif);
    fix_vediochoose_fif->setLayout(f4);

    fix_gateshow_fif = new  QCheckBox();
    fix_bullshow_fif = new  QCheckBox();
    fix_gateshow_fif->setText("波门显示");
    fix_bullshow_fif->setText("靶心显示");
    QHBoxLayout *v6=new QHBoxLayout;
    v6->addWidget(fix_gateshow_fif);
    v6->addWidget(fix_bullshow_fif);

    fix_autogate_fif = new  QCheckBox();
    fix_autogate_fif->setText("自动波门");

    QLabel *label51=new QLabel;
    label51->setText("波门尺寸X");
    QLabel *label52=new QLabel;
    label52->setText("波门尺寸Y");
    QLabel *label53=new QLabel;
    label53->setText("波门位置X");
    QLabel *label54=new QLabel;
    label54->setText("波门位置Y");
    fix_gate_sizex_fif=new QLineEdit;
    fix_gate_sizey_fif=new QLineEdit;
    fix_gatelocationx_fif=new QLineEdit;
    fix_gatelocationy_fif=new QLineEdit;
    QGridLayout *gl1=new QGridLayout;
    gl1->addWidget(label51,0,0);
    gl1->addWidget(fix_gate_sizex_fif,0,1);
    gl1->addWidget(label52,0,3);
    gl1->addWidget(fix_gate_sizey_fif,0,4);
    gl1->addWidget(label53,1,0);
    gl1->addWidget(fix_gatelocationx_fif,1,1);
    gl1->addWidget(label54,1,3);
    gl1->addWidget(fix_gatelocationy_fif,1,4);

    //2.10新增
     QGridLayout *gl12=new QGridLayout;
    set_azimuth_fif =new QPushButton;
    set_pitch_fif =new QPushButton;
    set_zoom_fif  =new QPushButton;
    search_azimuth_fif=new QPushButton;
    search_pitch_fif=new QPushButton;
    search_zoom_fif=new QPushButton;
    set_azimuth_fif->setText("设置");
    set_pitch_fif->setText("设置");
    set_zoom_fif->setText("设置");
    search_azimuth_fif->setText("查询");
    search_pitch_fif->setText("查询");
    search_zoom_fif->setText("查询");

    QLabel *labela=new QLabel;
    labela->setText("方位角");
    QLabel *labelp=new QLabel;
    labelp->setText("俯仰角");
    QLabel *labelz=new QLabel;
    labelz->setText("zoom位置");
    ledt_set_azimuth_fif=new QLineEdit;
    ledt_set_pitch_fif=new QLineEdit;
    ledt_set_zoom_fif=new QLineEdit;

    ledt_search_azimuth_fif=new QLineEdit;
    ledt_search_pitch_fif=new QLineEdit;
    ledt_search_zoom_fif=new QLineEdit;

    gl12->addWidget(labela,1,0,1,1);
    gl12->addWidget(labelp,2,0,1,1);
    gl12->addWidget(labelz,3,0,1,1);


    gl12->addWidget(ledt_set_azimuth_fif,1,2,1,1);
    gl12->addWidget(ledt_set_pitch_fif,2,2,1,1);
    gl12->addWidget(ledt_set_zoom_fif,3,2,1,1);

    gl12->addWidget(set_azimuth_fif,1,3,1,1);
    gl12->addWidget(set_pitch_fif,2,3,1,1);
    gl12->addWidget(set_zoom_fif,3,3,1,1);
    gl12->addWidget(ledt_search_azimuth_fif,1,4,1,1);
    gl12->addWidget(ledt_search_pitch_fif,2,4,1,1);
    gl12->addWidget(ledt_search_zoom_fif,3,4,1,1);

    gl12->addWidget(search_azimuth_fif,1,5,1,1);
    gl12->addWidget(search_pitch_fif,2,5,1,1);
    gl12->addWidget(search_zoom_fif,3,5,1,1);
//

    QGroupBox *g=new QGroupBox;
    g->setTitle("固定视场");
    QLabel* l11=new QLabel;
    l11->setText("水平视场");
    QLabel* l15=new QLabel;
    l15->setText("垂直视场");
    QLabel* l12=new QLabel;
    l12->setText("靶心X位置");
    QLabel* l13=new QLabel;
    l13->setText("靶心Y位置");
    QLabel* l14=new QLabel;
    l14->setText(" ");
    fix_lEdt_fif=new QLineEdit;
    fix_vertical_fif=new QLineEdit;
    QLabel* l1d=new QLabel;
    l1d->setText("度");
    QLabel* l1v=new QLabel;
    l1v->setText("度");
    fix_sp_fif=new QSpinBox;
    fix_sp2_fif=new QSpinBox;
    fix_sp_fif->setRange(0,9999);
    fix_sp2_fif->setRange(0,9999);

    QGridLayout *gl3=new QGridLayout;
    gl3->addWidget(l11,0,0,1,1);
    gl3->addWidget(l14,0,1,1,1);
    gl3->addWidget(l15,0,2,1,1);
    gl3->addWidget(l14,0,3,1,1);
    gl3->addWidget(l14,0,4,1,1);
    gl3->addWidget(l12,0,5,1,1);
    gl3->addWidget(l13,0,6,1,1);
    gl3->addWidget(l14,0,7,1,1);


        gl3->addWidget(fix_lEdt_fif,1,0,1,1);

                 gl3->addWidget(l1d,1,1,1,1);
    gl3->addWidget(fix_vertical_fif,1,2,1,1);
                 gl3->addWidget(l1v,1,3,1,1);
                 gl3->addWidget(l14,1,4,1,1);
          gl3->addWidget(fix_sp_fif,1,5,1,1);
         gl3->addWidget(fix_sp2_fif,1,6,1,1);




                           g->setLayout(gl3);

    QVBoxLayout *v0=new QVBoxLayout;
    v0->addLayout(h11);
    v0->addLayout(v21);
    v0->addWidget(fix_vediochoose_fif);
    v0->addLayout(v6);
    v0->addWidget(fix_autogate_fif);
    v0->addLayout(gl1);
    v0->addLayout(gl12);
    v0->addWidget(g);
    w_sersor_1_fif->setLayout(v0);
   connect(vedio_change1_fif,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix_fif(int)));
   connect(vedio_change1_fif,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_fix_fif(int)));
   connect(btn_vediosersor_fix_default_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fif()));
   connect(btn_vediosersor_fix_update_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fif()));
   connect(fixChanelNum_fif,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fif(int)));
   connect(fixchanelname_fif,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fif(int)));
   connect(fixenable_fif,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fif(int)));
   connect(fix_vediohaveornot_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fif(int)));
   connect(fix_vedio_dpi_fif,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fif(int)));
   connect(fix_xy_ratio_fif,SIGNAL(returnPressed()),this,SLOT(fix_xy_ratio_Slot_fif()));
   connect(fix_gateshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fif(int)));
   connect(fix_bullshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fif(int)));
   connect(fix_autogate_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fif(int)));
   connect(fix_gate_sizex_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fif()));
   connect(fix_gate_sizey_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fif()));
   connect(fix_gatelocationx_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fif()));
   connect(fix_gatelocationy_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fif()));
   connect(set_azimuth_fif,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fif()));
   connect(set_pitch_fif,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fif()));
   connect(set_zoom_fif,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fif()));
   connect(search_azimuth_fif,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fif()));
   connect(search_pitch_fif ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fif()));
   connect(search_zoom_fif,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fif()));
  // connect(ledt_set_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_set_azimuth_Slot()));
  // connect(ledt_set_pitch,SIGNAL(activated(int)),this,SLOT(ledt_set_pitch_Slot()));
  // connect(ledt_set_zoom,SIGNAL(activated(int)),this,SLOT(ledt_set_zoom_Slot()));
  // connect(ledt_search_azimuth,SIGNAL(activated(int)),this,SLOT(ledt_search_azimuth_Slot()));
  // connect(ledt_search_pitch,SIGNAL(activated(int)),this,SLOT(ledt_search_pitch_Slot()));
  // connect(ledt_search_zoom,SIGNAL(activated(int)),this,SLOT(ledt_search_zoom_Slot()));
   connect(fix_lEdt_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
   connect(fix_vertical_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
   connect(fix_sp_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
   connect(fix_sp2_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));

    /*可切换视场*/

    w_seitchField_1_fif->setWindowTitle("摄像机配置");
    btn_vediosersor_default_fif=new QPushButton;
    btn_vediosersor_update_fif=new QPushButton;
    btn_vediosersor_default_fif->setText("默认");
    btn_vediosersor_update_fif->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_vediosersor_default_fif);
    v1->addWidget(btn_vediosersor_update_fif);
    QLabel *label1=new QLabel;
    label1->setText("通道1");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label1);

    ChanelNum_fif = new  QCheckBox();
    ChanelNum_fif->setText("通道号");
    chanelname_fif = new QLineEdit;
    enable_fif = new  QCheckBox();
    enable_fif->setText("使能");

    QLabel *label2=new QLabel;
    label2->setText("通道名称");
    QHBoxLayout *v2=new QHBoxLayout;
    v2->addWidget(ChanelNum_fif);
    v2->addWidget(label2);
    v2->addWidget(chanelname_fif);
    v2->addWidget(enable_fif);

    vediohaveornot_fif = new  QCheckBox();
    vedio_dpi_fif = new QComboBox;
    xy_ratio_fif = new QLineEdit;
    vedio_dpi_fif->addItem("1080P@25HZ");
    vedio_dpi_fif->addItem("1080P@30HZ");
    vedio_dpi_fif->addItem("1080P@60HZ");
    vedio_dpi_fif->addItem("720P@50HZ");
    vedio_dpi_fif->addItem("720P@60HZ");
    vedio_change2_fif = new QComboBox;
    vedio_change2_fif->addItem("可切换视场");
    vedio_change2_fif->addItem("固定视场");
    vedio_change2_fif->addItem("连续视场");

    vediochoose_fif = new QGroupBox();
    QFormLayout *f3=new QFormLayout();
    f3->addRow(vedio_s_fif[0],vediohaveornot_fif);
    f3->addRow(vedio_s_fif[1],vedio_dpi);
    f3->addRow(vedio_s_fif[2],vedio_change2);
    f3->addRow(vedio_s_fif[3],xy_ratio);
    vediochoose_fif->setLayout(f3);

    connect(vedio_change2_fif,SIGNAL(activated(int)),this,SLOT(vedio_toSensor_switch(int)));
    gateshow_fif = new  QCheckBox();
    bullshow_fif = new  QCheckBox();
    gateshow_fif->setText("波门显示");
    bullshow_fif->setText("靶心显示");
    QHBoxLayout *v3=new QHBoxLayout;
    v3->addWidget(gateshow_fif);
    v3->addWidget(bullshow_fif);

    autogate_fif = new  QCheckBox();
    autogate_fif->setText("自动波门");

    QLabel *label3=new QLabel;
    label3->setText("波门尺寸X");
    QLabel *label4=new QLabel;
    label4->setText("波门尺寸Y");
    QLabel *label5=new QLabel;
    label5->setText("波门位置X");
    QLabel *label6=new QLabel;
    label6->setText("波门位置Y");
    gate_sizex_fif=new QLineEdit;
    gate_sizey_fif=new QLineEdit;
    gatelocationx_fif=new QLineEdit;
    gatelocationy_fif=new QLineEdit;
    QGridLayout *gl=new QGridLayout;
    gl->addWidget(label3,0,0);
    gl->addWidget(gate_sizex_fif,0,1);
    gl->addWidget(label4,0,3);
    gl->addWidget(gate_sizey_fif,0,4);
    gl->addWidget(label5,1,0);
    gl->addWidget(gatelocationx_fif,1,1);
    gl->addWidget(label6,1,3);
    gl->addWidget(gatelocationy_fif,1,4);

    QHBoxLayout *h2=new QHBoxLayout;
    QLabel *label7=new QLabel;
    label7->setText("测试现场等级");
    vedio_fovclass_fif= new QComboBox;
    vedio_fovclass_fif->addItem("可切换视场1");
    vedio_fovclass_fif->addItem("可切换视场2");
    vedio_fovclass_fif->addItem("可切换视场3");
    vedio_fovclass_fif->addItem("可切换视场4");
    vedio_fovclass_fif->addItem("可切换视场5");
    h2->addWidget(label7);
    h2->addWidget(vedio_fovclass_fif);
    //

    QGridLayout *glc2=new QGridLayout;
   Change_set_azimuth_fif =new QPushButton;
   Change_set_pitch_fif =new QPushButton;
   Change_set_zoom_fif  =new QPushButton;
   Change_search_azimuth_fif=new QPushButton;
   Change_search_pitch_fif=new QPushButton;
   Change_search_zoom_fif=new QPushButton;
   Change_set_azimuth_fif->setText("设置");
   Change_set_pitch_fif->setText("设置");
   Change_set_zoom_fif->setText("设置");
   Change_search_azimuth_fif->setText("查询");
   Change_search_pitch_fif->setText("查询");
   Change_search_zoom_fif->setText("查询");

   Change_ledt_set_azimuth_fif=new QLineEdit;
   Change_ledt_set_pitch_fif=new QLineEdit;
   Change_ledt_set_zoom_fif=new QLineEdit;

   Change_ledt_search_azimuth_fif=new QLineEdit;
   Change_ledt_search_pitch_fif=new QLineEdit;
   Change_ledt_search_zoom_fif=new QLineEdit;

   QLabel *labelac=new QLabel;
   labelac->setText("方位角");
   QLabel *labelpc=new QLabel;
   labelpc->setText("俯仰角");
   QLabel *labelzc=new QLabel;
   labelzc->setText("zoom位置");

   glc2->addWidget(labelac,1,0,1,1);
   glc2->addWidget(labelpc,2,0,1,1);
   glc2->addWidget(labelzc,3,0,1,1);


   glc2->addWidget(Change_ledt_set_azimuth_fif,1,2,1,1);
   glc2->addWidget(Change_ledt_set_pitch_fif,2,2,1,1);
   glc2->addWidget(Change_ledt_set_zoom_fif,3,2,1,1);

   glc2->addWidget(Change_set_azimuth_fif,1,3,1,1);
   glc2->addWidget(Change_set_pitch_fif,2,3,1,1);
   glc2->addWidget(Change_set_zoom_fif,3,3,1,1);
   glc2->addWidget(Change_ledt_search_azimuth_fif,1,4,1,1);
   glc2->addWidget(Change_ledt_search_pitch_fif,2,4,1,1);
   glc2->addWidget(Change_ledt_search_zoom_fif,3,4,1,1);

   glc2->addWidget(Change_search_azimuth_fif,1,5,1,1);
   glc2->addWidget(Change_search_pitch_fif,2,5,1,1);
   glc2->addWidget(Change_search_zoom_fif,3,5,1,1);


    //

    QGroupBox *g2=new QGroupBox;
    g2->setTitle("视场靶心补偿表");
    QGridLayout *gl2=new QGridLayout;
    QLabel* l21=new QLabel;
    l21->setText("水平视场");
    QLabel* l25=new QLabel;
    l25->setText("垂直视场");
    QLabel* l22=new QLabel;
    l22->setText("靶心X位置");
    QLabel* l23=new QLabel;
    l23->setText("靶心Y位置");
    QLabel* l24=new QLabel;
    l24->setText(" ");
    gl2->addWidget(l21,0,1,1,1);
    gl2->addWidget(l25,0,3,1,1);
    gl2->addWidget(l22,0,5,1,1);
    gl2->addWidget(l23,0,6,1,1);
    gl2->addWidget(l24,0,7,1,1);

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
    vedio_s1_Fov0_fif=new QLineEdit;
    vedio_s1_Fov1_fif=new QLineEdit;
    vedio_s1_Fov2_fif=new QLineEdit;
    vedio_s1_Fov3_fif=new QLineEdit;
    vedio_s1_Fov4_fif=new QLineEdit;
    gl2->addWidget(vedio_s1_Fov0_fif,1,1,1,1);
    gl2->addWidget(vedio_s1_Fov1_fif,2,1,1,1);
    gl2->addWidget(vedio_s1_Fov2_fif,3,1,1,1);
    gl2->addWidget(vedio_s1_Fov3_fif,4,1,1,1);
    gl2->addWidget(vedio_s1_Fov4_fif,5,1,1,1);

    Change_vertical1_fif=new QLineEdit;
    Change_vertical2_fif=new QLineEdit;
    Change_vertical3_fif=new QLineEdit;
    Change_vertical4_fif=new QLineEdit;
    Change_vertical5_fif=new QLineEdit;
    gl2->addWidget(Change_vertical1_fif,1,3,1,1);
    gl2->addWidget(Change_vertical2_fif,2,3,1,1);
    gl2->addWidget(Change_vertical3_fif,3,3,1,1);
    gl2->addWidget(Change_vertical4_fif,4,3,1,1);
    gl2->addWidget(Change_vertical5_fif,5,3,1,1);

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

    QLabel* l1c21=new QLabel;
    QLabel* l1c22=new QLabel;
    QLabel* l1c23=new QLabel;
    QLabel* l1c24=new QLabel;
    QLabel* l1c25=new QLabel;
    l1c21->setText("度");
    l1c22->setText("度");
    l1c23->setText("度");
    l1c24->setText("度");
    l1c25->setText("度");

    gl2->addWidget(l1d21,1,2,1,1);
    gl2->addWidget(l1d22,2,2,1,1);
    gl2->addWidget(l1d23,3,2,1,1);
    gl2->addWidget(l1d24,4,2,1,1);
    gl2->addWidget(l1d25,5,2,1,1);

    gl2->addWidget(l1c21,1,4,1,1);
    gl2->addWidget(l1c22,2,4,1,1);
    gl2->addWidget(l1c23,3,4,1,1);
    gl2->addWidget(l1c24,4,4,1,1);
    gl2->addWidget(l1c25,5,4,1,1);


    vedio_spbx_switch1_fif=new QSpinBox;
    vedio_spbx_switch2_fif=new QSpinBox;
    vedio_spbx_switch3_fif=new QSpinBox;
    vedio_spbx_switch4_fif=new QSpinBox;
    vedio_spbx_switch5_fif=new QSpinBox;
    vedio_spbx_switch1_fif->setRange(0,9999);
    vedio_spbx_switch2_fif->setRange(0,9999);
    vedio_spbx_switch3_fif->setRange(0,9999);
    vedio_spbx_switch4_fif->setRange(0,9999);
    vedio_spbx_switch5_fif->setRange(0,9999);
    gl2->addWidget(vedio_spbx_switch1_fif,1,5,1,1);
    gl2->addWidget(vedio_spbx_switch2_fif,2,5,1,1);
    gl2->addWidget(vedio_spbx_switch3_fif,3,5,1,1);
    gl2->addWidget(vedio_spbx_switch4_fif,4,5,1,1);
    gl2->addWidget(vedio_spbx_switch5_fif,5,5,1,1);

    vedio_spby_switch1_fif=new QSpinBox;
    vedio_spby_switch2_fif=new QSpinBox;
    vedio_spby_switch3_fif=new QSpinBox;
    vedio_spby_switch4_fif=new QSpinBox;
    vedio_spby_switch5_fif=new QSpinBox;
    vedio_spby_switch1_fif->setRange(0,9999);
    vedio_spby_switch2_fif->setRange(0,9999);
    vedio_spby_switch3_fif->setRange(0,9999);
    vedio_spby_switch4_fif->setRange(0,9999);
    vedio_spby_switch5_fif->setRange(0,9999);
    gl2->addWidget(vedio_spby_switch1_fif,1,6,1,1);
    gl2->addWidget(vedio_spby_switch2_fif,2,6,1,1);
    gl2->addWidget(vedio_spby_switch3_fif,3,6,1,1);
    gl2->addWidget(vedio_spby_switch4_fif,4,6,1,1);
    gl2->addWidget(vedio_spby_switch5_fif,5,6,1,1);

    g2->setLayout(gl2);
    QVBoxLayout *v22=new QVBoxLayout;
    v22->addLayout(h2);
    v22->addLayout(glc2);
    v22->addWidget(g2);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(v1);

    v->addLayout(h1);

    v->addLayout(v2);
    v->addWidget(vediochoose_fif);
    v->addLayout(v3);
    v->addWidget(autogate_fif);
    v->addLayout(gl);
  //v->addLayout(h2);
    v->addLayout(v22);
    w_seitchField_1_fif->setLayout(v);
    connect(btn_vediosersor_default_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fif()));
    connect(btn_vediosersor_update_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fif()));
    connect(ChanelNum_fif,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fif(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(enable_fif,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fif(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(chanelname_fif,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fif(int)));//
    connect(vediohaveornot_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fif(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(vedio_dpi_fif,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fif(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(gateshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fif(int)));
    connect(bullshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fif(int)));
    connect(xy_ratio_fif,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_fif()));
    connect(gateshow_fif,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_fif()));
    connect(bullshow_fif,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_fif()));
    connect(autogate_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fif(int)));
    connect(gate_sizex_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fif()));
    connect(gate_sizey_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fif()));
    connect(gatelocationx_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fif()));
    connect(gatelocationy_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fif()));
    connect(Change_set_azimuth_fif,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fif()));
    connect(Change_set_pitch_fif,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fif()));
    connect(Change_set_zoom_fif,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fif()));
    connect(Change_search_azimuth_fif,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fif()));
    connect(Change_search_pitch_fif ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fif()));
    connect(Change_search_zoom_fif,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fif()));
    connect( vedio_fovclass_fif,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_fif()));

    connect(vedio_s1_Fov0_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
    connect(Change_vertical1_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
    connect(vedio_spbx_switch1_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_spby_switch1_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_s1_Fov1_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
    connect(Change_vertical2_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
    connect(vedio_spbx_switch2_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_spby_switch2_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_s1_Fov2_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
    connect(Change_vertical3_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
    connect(vedio_spbx_switch3_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_spby_switch3_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_s1_Fov3_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
    connect(Change_vertical4_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
    connect(vedio_spbx_switch4_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_spby_switch4_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_s1_Fov4_fif,SIGNAL(returnPressed()),this,SLOT(fix_lEdt_Slot_fif()));
    connect(Change_vertical5_fif,SIGNAL(returnPressed()),this,SLOT(fix_vertical_Slot_fif()));
    connect(vedio_spbx_switch5_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));
    connect(vedio_spby_switch5_fif,SIGNAL(returnPressed()),this,SLOT(fix_sp_Slot_fif()));


    /*连续视场*/
    w_ContinueField_1_fif->setWindowTitle("摄像机配置");
    btn_vediosersor_continue_default_fif=new QPushButton;
    btn_vediosersor_continue_update_fif=new QPushButton;
    btn_vediosersor_continue_default_fif->setText("默认");
    btn_vediosersor_continue_update_fif->setText("保存");
    QVBoxLayout *v8=new QVBoxLayout;
    v8->addWidget(btn_vediosersor_continue_default_fif);
    v8->addWidget(btn_vediosersor_continue_update_fif);
    QLabel *label60=new QLabel;
    label60->setText("通道1");
    QHBoxLayout *h5=new QHBoxLayout;
    h5->addLayout(v8);
    h5->addWidget(label60);

    continueChanelNum_fif = new  QCheckBox();
    continueChanelNum_fif->setText("通道号");
    continuechanelname_fif = new QLineEdit;
    continueenable_fif = new  QCheckBox();
    continueenable_fif->setText("使能");
    QLabel *label61=new QLabel;
    label61->setText("通道名称");
    QHBoxLayout *v9=new QHBoxLayout;
    v9->addWidget(continueChanelNum_fif);
    v9->addWidget(label61);
    v9->addWidget(continuechanelname_fif);
    v9->addWidget(continueenable_fif);

    continue_vediohaveornot_fif = new  QCheckBox();
    continue_vedio_dpi_fif = new QComboBox;
    continue_xy_ratio_fif = new QLineEdit;
    continue_vedio_dpi_fif->addItem("1080P@25HZ");
    continue_vedio_dpi_fif->addItem("1080P@30HZ");
    continue_vedio_dpi_fif->addItem("1080P@60HZ");
    continue_vedio_dpi_fif->addItem("720P@50HZ");
    continue_vedio_dpi_fif->addItem("720P@60HZ");
    vedio_change3_fif = new QComboBox;
    vedio_change3_fif->addItem("连续视场");
    vedio_change3_fif->addItem("固定视场");
    vedio_change3_fif->addItem("可切换视场");
    continue_vediochoose_fif = new QGroupBox();
    QFormLayout *f5=new QFormLayout();
    f5->addRow(vedio_s_fif[0],continue_vediohaveornot_fif);
    f5->addRow(vedio_s_fif[1],continue_vedio_dpi_fif);
    f5->addRow(vedio_s_fif[2],vedio_change3_fif);
    f5->addRow(vedio_s_fif[3],continue_xy_ratio_fif);
    continue_vediochoose_fif->setLayout(f5);

    continue_gateshow_fif = new  QCheckBox();
    continue_bullshow_fif = new  QCheckBox();
    continue_gateshow_fif->setText("波门显示");
    continue_bullshow_fif->setText("靶心显示");
    QHBoxLayout *v7=new QHBoxLayout;
    v7->addWidget(continue_gateshow_fif);
    v7->addWidget(continue_bullshow_fif);

    continue_autogate_fif = new  QCheckBox();
    continue_autogate_fif->setText("自动波门");

    QLabel *label55=new QLabel;
    label55->setText("波门尺寸X");
    QLabel *label56=new QLabel;
    label56->setText("波门尺寸Y");
    QLabel *label57=new QLabel;
    label57->setText("波门位置X");
    QLabel *label58=new QLabel;
    label58->setText("波门位置Y");
    continue_gate_sizex_fif=new QLineEdit;
    continue_gate_sizey_fif=new QLineEdit;
    continue_gatelocationx_fif=new QLineEdit;
    continue_gatelocationy_fif=new QLineEdit;
    QGridLayout *gl4=new QGridLayout;
    gl4->addWidget(label55,0,0);
    gl4->addWidget(continue_gate_sizex_fif,0,1);
    gl4->addWidget(label56,0,3);
    gl4->addWidget(continue_gate_sizey_fif,0,4);
    gl4->addWidget(label57,1,0);
    gl4->addWidget(continue_gatelocationx_fif,1,1);
    gl4->addWidget(label58,1,3);
    gl4->addWidget(continue_gatelocationy_fif,1,4);

    QHBoxLayout *v31=new QHBoxLayout;
    QLabel *label70=new QLabel;
    label70->setText("测试视场");
    test_1 = new QLineEdit;
    v31->addWidget(label70);
    v31->addWidget(test_1);
//
    QGridLayout *glct2=new QGridLayout;
   continue_set_azimuth_fif =new QPushButton;
   continue_set_pitch_fif =new QPushButton;
   continue_set_zoom_fif =new QPushButton;
   continue_search_azimuth_fif=new QPushButton;
   continue_search_pitch_fif=new QPushButton;
   continue_search_zoom_fif=new QPushButton;
   continue_set_azimuth_fif->setText("设置");
   continue_set_pitch_fif->setText("设置");
   continue_set_zoom_fif->setText("设置");
   continue_search_azimuth_fif->setText("查询");
   continue_search_pitch_fif->setText("查询");
   continue_search_zoom_fif->setText("查询");

   continue_ledt_set_azimuth_fif=new QLineEdit;
   continue_ledt_set_pitch_fif=new QLineEdit;
   continue_ledt_set_zoom_fif=new QLineEdit;

   continue_ledt_search_azimuth_fif=new QLineEdit;
   continue_ledt_search_pitch_fif=new QLineEdit;
   continue_ledt_search_zoom_fif=new QLineEdit;

   QLabel *labelact=new QLabel;
   labelact->setText("方位角");
   QLabel *labelpct=new QLabel;
   labelpct->setText("俯仰角");
   QLabel *labelzct=new QLabel;
   labelzct->setText("zoom位置");

   glct2->addWidget(labelact,1,0,1,1);
   glct2->addWidget(labelpct,2,0,1,1);
   glct2->addWidget(labelzct,3,0,1,1);


   glct2->addWidget(continue_ledt_set_azimuth_fif,1,2,1,1);
   glct2->addWidget(continue_ledt_set_pitch_fif,2,2,1,1);
   glct2->addWidget(continue_ledt_set_zoom_fif,3,2,1,1);

   glct2->addWidget(continue_set_azimuth_fif,1,3,1,1);
   glct2->addWidget(continue_set_pitch_fif,2,3,1,1);
   glct2->addWidget(continue_set_zoom_fif,3,3,1,1);
   glct2->addWidget(continue_ledt_search_azimuth_fif,1,4,1,1);
   glct2->addWidget(continue_ledt_search_pitch_fif,2,4,1,1);
   glct2->addWidget(continue_ledt_search_zoom_fif,3,4,1,1);

   glct2->addWidget(continue_search_azimuth_fif,1,5,1,1);
   glct2->addWidget(continue_search_pitch_fif,2,5,1,1);
   glct2->addWidget(continue_search_zoom_fif,3,5,1,1);

   //


    QGroupBox *g3=new QGroupBox;
    g3->setTitle("视场靶心补偿表");
    QGridLayout *glc=new QGridLayout;
    QLabel* l30=new QLabel;
    l30->setText("与视场相关的反馈值");
    QLabel* l31=new QLabel;
    l31->setText("水平视场");
    QLabel* l35=new QLabel;
    l35->setText("垂直视场");
    QLabel* l32=new QLabel;
    l32->setText("靶心X位置");
    QLabel* l33=new QLabel;
    l33->setText("靶心Y位置");
    QLabel* l34=new QLabel;
    l34->setText(" ");
    QLabel* l36=new QLabel;
    l36->setText(" ");
    glc->addWidget(l30,0,1,1,1);
    glc->addWidget(l31,0,2,1,1);
    glc->addWidget(l35,0,4,1,1);
    glc->addWidget(l36,0,5,1,1);
    glc->addWidget(l32,0,6,1,1);
    glc->addWidget(l33,0,7,1,1);
    glc->addWidget(l34,0,8,1,1);


    vedio_l1_continue_fif=new QLineEdit;
    vedio_l2_continue_fif=new QLineEdit;
    vedio_l3_continue_fif=new QLineEdit;
    vedio_l4_continue_fif=new QLineEdit;
    vedio_l5_continue_fif=new QLineEdit;
    vedio_l6_continue_fif=new QLineEdit;
    vedio_l7_continue_fif=new QLineEdit;
    glc->addWidget(vedio_l1_continue_fif,1,1,1,1);
    glc->addWidget(vedio_l2_continue_fif,2,1,1,1);
    glc->addWidget(vedio_l3_continue_fif,3,1,1,1);
    glc->addWidget(vedio_l4_continue_fif,4,1,1,1);
    glc->addWidget(vedio_l5_continue_fif,5,1,1,1);
    glc->addWidget(vedio_l6_continue_fif,6,1,1,1);
    glc->addWidget(vedio_l7_continue_fif,7,1,1,1);

    vedio_continue_Fov0_fif = new QLineEdit;
    vedio_continue_Fov1_fif = new QLineEdit;
    vedio_continue_Fov2_fif = new QLineEdit;
    vedio_continue_Fov3_fif = new QLineEdit;
    vedio_continue_Fov4_fif = new QLineEdit;
    vedio_continue_Fov5_fif = new QLineEdit;
    vedio_continue_Fov6_fif = new QLineEdit;
    glc->addWidget(vedio_continue_Fov0_fif,1,2,1,1);
    glc->addWidget(vedio_continue_Fov1_fif,2,2,1,1);
    glc->addWidget(vedio_continue_Fov2_fif,3,2,1,1);
    glc->addWidget(vedio_continue_Fov3_fif,4,2,1,1);
    glc->addWidget(vedio_continue_Fov4_fif,5,2,1,1);
    glc->addWidget(vedio_continue_Fov5_fif,6,2,1,1);
    glc->addWidget(vedio_continue_Fov6_fif,7,2,1,1);

    continue_vertical1_fif = new QLineEdit;
    continue_vertical2_fif = new QLineEdit;
    continue_vertical3_fif = new QLineEdit;
    continue_vertical4_fif = new QLineEdit;
    continue_vertical5_fif = new QLineEdit;
    continue_vertical6_fif = new QLineEdit;
    continue_vertical7_fif = new QLineEdit;
    glc->addWidget(continue_vertical1_fif,1,4,1,1);
    glc->addWidget(continue_vertical2_fif,2,4,1,1);
    glc->addWidget(continue_vertical3_fif,3,4,1,1);
    glc->addWidget(continue_vertical4_fif,4,4,1,1);
    glc->addWidget(continue_vertical5_fif,5,4,1,1);
    glc->addWidget(continue_vertical6_fif,6,4,1,1);
    glc->addWidget(continue_vertical7_fif,7,4,1,1);

    QLabel* l1dv31=new QLabel;
    QLabel* l1dv32=new QLabel;
    QLabel* l1dv33=new QLabel;
    QLabel* l1dv34=new QLabel;
    QLabel* l1dv35=new QLabel;
    QLabel* l1dv36=new QLabel;
    QLabel* l1dv37=new QLabel;
    l1dv31->setText("度");
    l1dv32->setText("度");
    l1dv33->setText("度");
    l1dv34->setText("度");
    l1dv35->setText("度");
    l1dv36->setText("度");
    l1dv37->setText("度");

    glc->addWidget(l1dv31,1,5,1,1);
    glc->addWidget(l1dv32,2,5,1,1);
    glc->addWidget(l1dv33,3,5,1,1);
    glc->addWidget(l1dv34,4,5,1,1);
    glc->addWidget(l1dv35,5,5,1,1);
    glc->addWidget(l1dv36,6,5,1,1);
    glc->addWidget(l1dv37,7,5,1,1);

    QLabel* l1d31=new QLabel;
    QLabel* l1d32=new QLabel;
    QLabel* l1d33=new QLabel;
    QLabel* l1d34=new QLabel;
    QLabel* l1d35=new QLabel;
    QLabel* l1d36=new QLabel;
    QLabel* l1d37=new QLabel;
    l1d31->setText("度");
    l1d32->setText("度");
    l1d33->setText("度");
    l1d34->setText("度");
    l1d35->setText("度");
    l1d36->setText("度");
    l1d37->setText("度");

    glc->addWidget(l1d31,1,3,1,1);
    glc->addWidget(l1d32,2,3,1,1);
    glc->addWidget(l1d33,3,3,1,1);
    glc->addWidget(l1d34,4,3,1,1);
    glc->addWidget(l1d35,5,3,1,1);
    glc->addWidget(l1d36,6,3,1,1);
    glc->addWidget(l1d37,7,3,1,1);


    vedio_spbx_continue1_fif=new QSpinBox;
    vedio_spbx_continue2_fif=new QSpinBox;
    vedio_spbx_continue3_fif=new QSpinBox;
    vedio_spbx_continue4_fif=new QSpinBox;
    vedio_spbx_continue5_fif=new QSpinBox;
    vedio_spbx_continue6_fif=new QSpinBox;
    vedio_spbx_continue7_fif=new QSpinBox;

    vedio_spbx_continue1_fif->setRange(0,9999);
    vedio_spbx_continue2_fif->setRange(0,9999);
    vedio_spbx_continue3_fif->setRange(0,9999);
    vedio_spbx_continue4_fif->setRange(0,9999);
    vedio_spbx_continue5_fif->setRange(0,9999);
    vedio_spbx_continue6_fif->setRange(0,9999);
    vedio_spbx_continue7_fif->setRange(0,9999);

    glc->addWidget(vedio_spbx_continue1_fif,1,6,1,1);
    glc->addWidget(vedio_spbx_continue2_fif,2,6,1,1);
    glc->addWidget(vedio_spbx_continue3_fif,3,6,1,1);
    glc->addWidget(vedio_spbx_continue4_fif,4,6,1,1);
    glc->addWidget(vedio_spbx_continue5_fif,5,6,1,1);
    glc->addWidget(vedio_spbx_continue6_fif,6,6,1,1);
    glc->addWidget(vedio_spbx_continue7_fif,7,6,1,1);


    vedio_spby_continue1_fif=new QSpinBox;
    vedio_spby_continue2_fif=new QSpinBox;
    vedio_spby_continue3_fif=new QSpinBox;
    vedio_spby_continue4_fif=new QSpinBox;
    vedio_spby_continue5_fif=new QSpinBox;
    vedio_spby_continue6_fif=new QSpinBox;
    vedio_spby_continue7_fif=new QSpinBox;

    vedio_spby_continue1_fif->setRange(0,9999);
    vedio_spby_continue2_fif->setRange(0,9999);
    vedio_spby_continue3_fif->setRange(0,9999);
    vedio_spby_continue4_fif->setRange(0,9999);
    vedio_spby_continue5_fif->setRange(0,9999);
    vedio_spby_continue6_fif->setRange(0,9999);
    vedio_spby_continue7_fif->setRange(0,9999);

    glc->addWidget(vedio_spby_continue1_fif,1,7,1,1);
    glc->addWidget(vedio_spby_continue2_fif,2,7,1,1);
    glc->addWidget(vedio_spby_continue3_fif,3,7,1,1);
    glc->addWidget(vedio_spby_continue4_fif,4,7,1,1);
    glc->addWidget(vedio_spby_continue5_fif,5,7,1,1);
    glc->addWidget(vedio_spby_continue6_fif,6,7,1,1);
    glc->addWidget(vedio_spby_continue7_fif,7,7,1,1);
    g3->setLayout(glc);

    QVBoxLayout *v10=new QVBoxLayout;
    v10->addLayout(h5);
    v10->addLayout(v9);
    v10->addWidget(continue_vediochoose_fif);
    v10->addLayout(v7);
    v10->addWidget(continue_autogate_fif);
    v10->addLayout(gl4);
    v10->addLayout(v31);
    v10->addLayout(glct2);
    v10->addWidget(g3);

    //

    w_ContinueField_1_fif->setLayout(v10);

    connect(vedio_change3_fif,SIGNAL(activated(int)),this,SLOT(vedio_tosersor_continue_fif(int)));


    connect(btn_vediosersor_default_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_default_Slot_fif()));
    connect(btn_vediosersor_update_fif,SIGNAL(activated(int)),this,SLOT(btn_vediosersor_fix_update_Slot_fif()));
    connect(continueChanelNum_fif,SIGNAL(stateChanged(int)),this,SLOT(fixChanelNum_Slot_fif(int)));//1、 通道号：如果勾选使能，则HDMI输出是显示的视频的左上角显示通道号；
    connect(continueenable_fif,SIGNAL(stateChanged(int)),this,SLOT(fixchanelname_Slot_fif(int)));//2、 通道名称：如果勾选使能，则HDMI输出是显示的视频的左上角显示填写的通道名称；
    connect(continuechanelname_fif,SIGNAL(activated(int)),this,SLOT(fixchanelname_Slot_fif(int)));//
    connect(continue_vediohaveornot_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_vediohaveornot_Slot_fif(int)));//3、 是否有摄像机：如果勾选使能则此通道输入被使能；
    connect(continue_vedio_dpi_fif,SIGNAL(currentIndexChanged(int)),this,SLOT(fix_vedio_dpi_Slot_fif(int)));//4、 摄像机分辨率帧率：选择此通道的输入的视频信号的分辨率和帧率；
    connect(continue_gateshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_gateshow_Slot_fif(int)));
    connect(continue_bullshow_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_bullshow_Slot_fif(int)));
    connect(continue_xy_ratio_fif,SIGNAL(activated(int)),this,SLOT(fix_xy_ratio_Slot_fif()));
    connect(continue_gateshow_fif,SIGNAL(activated(int)),this,SLOT(fix_gateshow_Slot_fif()));
    connect(continue_bullshow_fif,SIGNAL(activated(int)),this,SLOT(fix_bullshow_Slot_fif()));
    connect(continue_autogate_fif,SIGNAL(stateChanged(int)),this,SLOT(fix_autogate_Slot_fif(int)));
    connect(continue_gate_sizex_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizex_Slot_fif()));
    connect(continue_gate_sizey_fif,SIGNAL(returnPressed()),this,SLOT(fix_gate_sizey_Slot_fif()));
    connect(continue_gatelocationx_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationx_Slot_fif()));
    connect(continue_gatelocationy_fif,SIGNAL(returnPressed()),this,SLOT(fix_gatelocationy_Slot_fif()));
    connect(continue_set_azimuth_fif,SIGNAL(activated(int)),this,SLOT(set_azimuth_Slot_fif()));
    connect(continue_set_pitch_fif,SIGNAL(activated(int)),this,SLOT(set_pitch_Slot_fif()));
    connect(continue_set_zoom_fif,SIGNAL(activated(int)),this,SLOT(set_zoom_Slot_fif()));
    connect(continue_search_azimuth_fif,SIGNAL(activated(int)),this,SLOT(search_azimuth_Slot_fif()));
    connect(continue_search_pitch_fif ,SIGNAL(activated(int)),this,SLOT(search_pitch_Slot_fif()));
    connect(continue_search_zoom_fif,SIGNAL(activated(int)),this,SLOT(search_zoom_Slot_fif()));
    connect(continue_vediohaveornot_fif,SIGNAL(activated(int)),this,SLOT(vedio_fovclass_Slot_fif()));
    connect(test_1_fif,SIGNAL(activated(int)),this,SLOT(test_1_Slot_fif()));
    connect(vedio_l1_continue_fou,SIGNAL(activated(int)),this,SLOT(vedio_l1_continue_Slot_fif()));
     connect(vedio_l2_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l2_continue_Slot_fif()));
      connect(vedio_l3_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l3_continue_Slot_fif()));
       connect(vedio_l4_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l4_continue_Slot_fif()));
        connect(vedio_l5_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l5_continue_Slot_fif()));
         connect(vedio_l6_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l6_continue_Slot_fif()));
          connect(vedio_l7_continue_fif,SIGNAL(activated(int)),this,SLOT(vedio_l7_continue_Slot_fif()));

    connect( vedio_continue_Fov0_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov0_Slot_fif()));
    connect( vedio_continue_Fov1_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov1_Slot_fif()));
    connect( vedio_continue_Fov2_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov2_Slot_fif()));
    connect( vedio_continue_Fov3_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov3_Slot_fif()));
    connect( vedio_continue_Fov4_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov4_Slot_fif()));
    connect( vedio_continue_Fov5_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov5_Slot_fif()));
    connect( vedio_continue_Fov6_fif,SIGNAL(returnPressed()),this,SLOT(vedio_continue_Fov6_Slot_fif()));
     connect( continue_vertical1_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical1_Slot_fif()));
     connect( continue_vertical2_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical2_Slot_fif()));
     connect( continue_vertical3_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical3_Slot_fif()));
     connect( continue_vertical4_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical4_Slot_fif()));
     connect( continue_vertical5_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical5_Slot_fif()));
     connect( continue_vertical6_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical6_Slot_fif()));
     connect( continue_vertical7_fif,SIGNAL(returnPressed()),this,SLOT(continue_vertical7_Slot_fif()));

      connect( vedio_spbx_continue1_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
       connect( vedio_spbx_continue2_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
        connect( vedio_spbx_continue3_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
         connect( vedio_spbx_continue4_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
       connect( vedio_spbx_continue5_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
        connect( vedio_spbx_continue6_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));
         connect( vedio_spbx_continue7_fif,SIGNAL(activated(int)),this,SLOT(vedio_spbx_continue1_Slot_fif()));

       connect( vedio_spby_continue1_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue1_Slot_fif()));
        connect( vedio_spby_continue2_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue2_Slot_fif()));
         connect( vedio_spby_continue3_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue3_Slot_fif()));
          connect( vedio_spby_continue4_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue4_Slot_fif()));
           connect( vedio_spby_continue5_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue5_Slot_fif()));
            connect( vedio_spby_continue6_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue6_Slot_fif()));
             connect( vedio_spby_continue7_fif,SIGNAL(activated(int)),this,SLOT(vedio_spby_continue7_Slot_fif()));

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
    w_speedconv->setWindowTitle("转台配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("通道1");
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
    speedx10_lineEdt=new QLineEdit;

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
    f1->addRow(speed_s[9],speedx10_lineEdt);
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
    speedy10_lineEdt=new QLineEdit;

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
     f2->addRow(speed_s[9],speedy10_lineEdt);
    gbox_speedy->setLayout(f2);

    QHBoxLayout *sensor_speed=new QHBoxLayout;
    sensor_speed->addWidget(gbox_speedx);
    sensor_speed->addWidget(gbox_speedy);


    x_Bleed_rate= new QLineEdit;
    y_Bleed_rate= new QLineEdit;
    maxspeedx = new QLineEdit;
    maxspeedy = new QLineEdit;
    deadx     = new QLineEdit;
    deady    = new QLineEdit;
    output_d_type =new QComboBox;
    output_d_type->addItem("像素偏差");
    output_d_type->addItem("Pid控制算法结果输出");
    output_d_type->addItem("转台命令输出");
    out_address =new QLineEdit;
    baud_rate =new QComboBox;
    baud_rate->addItem("0");
    baud_rate->addItem("110");
    baud_rate->addItem("300");
    baud_rate->addItem("600");
    baud_rate->addItem("1200");
    baud_rate->addItem("2400");
    baud_rate->addItem("4800");
    baud_rate->addItem("9600");
    baud_rate->addItem("14400");
    baud_rate->addItem("19200");
    baud_rate->addItem("38400");
    baud_rate->addItem("56000");
    baud_rate->addItem("57600");
    baud_rate->addItem("115200");
    baud_rate->addItem("128000");
    baud_rate->addItem("230400");
    baud_rate->addItem("256000");
    baud_rate->addItem("460800");
    baud_rate->addItem("500000");
    baud_rate->addItem("600000");
    baud_rate->addItem("750000");
    baud_rate->addItem("921600");
    baud_rate->addItem("1000000");
    baud_rate->addItem("1500000");
    baud_rate->addItem("2000000");
    baud_rate->setCurrentIndex(13);
    data_bit =new QComboBox;
    data_bit->addItem("5");
    data_bit->addItem("6");
    data_bit->addItem("7");
    data_bit->addItem("8");
    data_bit->setCurrentIndex(3);
    stop_bit =new QComboBox;
    stop_bit->addItem("1.5");
    stop_bit->addItem("2");
    stop_bit->setCurrentIndex(1);

    parity_bit =new QComboBox;
    parity_bit->addItem("None");
    parity_bit->addItem("Odd");
    parity_bit->addItem("Even");
    parity_bit->addItem("Mark");
    parity_bit->addItem("Space");

    flow_control=new QComboBox;
    flow_control->addItem("Hardware");
    flow_control->addItem("Software");
    flow_control->addItem("None");
    flow_control->addItem("Custom");
    flow_control->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
    //f3->addRow(speed_q[11],x_Bleed_rate);
    //f3->addRow(speed_q[12],y_Bleed_rate);
    f3->addRow(speed_q[0],maxspeedx);
    f3->addRow(speed_q[1],maxspeedy);
    f3->addRow(speed_q[2],deadx);
    f3->addRow(speed_q[3],deady);
    f3->addRow(speed_q[4],output_d_type);
    f3->addRow(speed_q[5],out_address);
    f3->addRow(speed_q[6],baud_rate);
    f3->addRow(speed_q[7],data_bit);
    f3->addRow(speed_q[8],stop_bit);
    f3->addRow(speed_q[9],parity_bit);
    f3->addRow(speed_q[10],flow_control);





    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(sensor_speed);
    v->addLayout(f3);
    //v->addWidget(gbox_speedy);
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
    connect(speedx10_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx10_Slot()));
    connect(speedy1_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot()));
    connect(speedy2_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot()));
    connect(speedy3_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot()));
    connect(speedy4_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot()));
    connect(speedy5_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot()));
    connect(speedy6_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot()));
    connect(speedy7_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot()));
    connect(speedy8_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot()));
    connect(speedy9_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot()));
    connect(speedy10_lineEdt,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy10_Slot()));
    connect(x_Bleed_rate,SIGNAL(returnPressed()),this,SLOT(x_Bleed_rate_Slot()));
    connect(y_Bleed_rate,SIGNAL(returnPressed()),this,SLOT(y_Bleed_rate_Slot()));
    connect(maxspeedx,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedx_Slot()));
    connect(maxspeedy,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedy_Slot()));
    connect(deadx,SIGNAL(returnPressed()),this,SLOT(lEdt_deadx_Slot()));
    connect(deady,SIGNAL(returnPressed()),this,SLOT(lEdt_deady_Slot()));
    connect(output_d_type,SIGNAL(activated(int)),this,SLOT(combox_output_d_type_Slot(int)));
    connect(out_address,SIGNAL(returnPressed()),this,SLOT(lEdt_out_address_Slot()));
    connect(baud_rate,SIGNAL(activated(int)),this,SLOT(combox_baud_rate_Slot(int)));
    connect(data_bit,SIGNAL(activated(int)),this,SLOT(combox_data_bit_Slot(int)));
    connect(stop_bit,SIGNAL(activated(int)),this,SLOT(combox_stop_bit_Slot(int)));
    connect(flow_control,SIGNAL(activated(int)),this,SLOT(combox_flow_control_Slot(int)));
    connect(parity_bit,SIGNAL(activated(int)),this,SLOT(combox_parity_bit_Slot(int)));
}


void MainWindow::init_speedconvCfg_sec()
{
    w_speedconv_sec=new MyWidget;
    w_speedconv_sec->setWindowTitle("转台配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("通道2");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_speedx_sec=new QGroupBox();
    gbox_speedx_sec->setTitle("x轴");
    speedx1_lineEdt_sec=new QLineEdit;
    speedx2_lineEdt_sec=new QLineEdit;
    speedx3_lineEdt_sec=new QLineEdit;
    speedx4_lineEdt_sec=new QLineEdit;
    speedx5_lineEdt_sec=new QLineEdit;
    speedx6_lineEdt_sec=new QLineEdit;
    speedx7_lineEdt_sec=new QLineEdit;
    speedx8_lineEdt_sec=new QLineEdit;
    speedx9_lineEdt_sec=new QLineEdit;
    speedx10_lineEdt_sec=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(speed_s_sec[0],speedx1_lineEdt_sec);
    f1->addRow(speed_s_sec[1],speedx2_lineEdt_sec);
    f1->addRow(speed_s_sec[2],speedx3_lineEdt_sec);
    f1->addRow(speed_s_sec[3],speedx4_lineEdt_sec);
    f1->addRow(speed_s_sec[4],speedx5_lineEdt_sec);
    f1->addRow(speed_s_sec[5],speedx6_lineEdt_sec);
    f1->addRow(speed_s_sec[6],speedx7_lineEdt_sec);
    f1->addRow(speed_s_sec[7],speedx8_lineEdt_sec);
    f1->addRow(speed_s_sec[8],speedx9_lineEdt_sec);
    f1->addRow(speed_s_sec[9],speedx10_lineEdt_sec);
    gbox_speedx_sec->setLayout(f1);

    gbox_speedy_sec=new QGroupBox();
    gbox_speedy_sec->setTitle("y轴");
    speedy1_lineEdt_sec=new QLineEdit;
    speedy2_lineEdt_sec=new QLineEdit;
    speedy3_lineEdt_sec=new QLineEdit;
    speedy4_lineEdt_sec=new QLineEdit;
    speedy5_lineEdt_sec=new QLineEdit;
    speedy6_lineEdt_sec=new QLineEdit;
    speedy7_lineEdt_sec=new QLineEdit;
    speedy8_lineEdt_sec=new QLineEdit;
    speedy9_lineEdt_sec=new QLineEdit;
    speedy10_lineEdt_sec=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(speed_s_sec[0],speedy1_lineEdt_sec);
    f2->addRow(speed_s_sec[1],speedy2_lineEdt_sec);
    f2->addRow(speed_s_sec[2],speedy3_lineEdt_sec);
    f2->addRow(speed_s_sec[3],speedy4_lineEdt_sec);
    f2->addRow(speed_s_sec[4],speedy5_lineEdt_sec);
    f2->addRow(speed_s_sec[5],speedy6_lineEdt_sec);
    f2->addRow(speed_s_sec[6],speedy7_lineEdt_sec);
    f2->addRow(speed_s_sec[7],speedy8_lineEdt_sec);
    f2->addRow(speed_s_sec[8],speedy9_lineEdt_sec);
    f2->addRow(speed_s_sec[9],speedy10_lineEdt_sec);
    gbox_speedy_sec->setLayout(f2);

    QHBoxLayout *sensor_speed=new QHBoxLayout;
    sensor_speed->addWidget(gbox_speedx_sec);
    sensor_speed->addWidget(gbox_speedy_sec);


    x_Bleed_rate_sec= new QLineEdit;
    y_Bleed_rate_sec= new QLineEdit;
    maxspeedx_sec = new QLineEdit;
    maxspeedy_sec = new QLineEdit;
    deadx_sec     = new QLineEdit;
    deady_sec     = new QLineEdit;
    output_d_type_sec =new QComboBox;
    output_d_type_sec->addItem("像素偏差");
    output_d_type_sec->addItem("Pid控制算法结果输出");
    output_d_type_sec->addItem("转台命令输出");
    out_address_sec =new QLineEdit;
    baud_rate_sec =new QComboBox;
    baud_rate_sec->addItem("0");
    baud_rate_sec->addItem("110");
    baud_rate_sec->addItem("300");
    baud_rate_sec->addItem("600");
    baud_rate_sec->addItem("1200");
    baud_rate_sec->addItem("2400");
    baud_rate_sec->addItem("4800");
    baud_rate_sec->addItem("9600");
    baud_rate_sec->addItem("14400");
    baud_rate_sec->addItem("19200");
    baud_rate_sec->addItem("38400");
    baud_rate_sec->addItem("56000");
    baud_rate_sec->addItem("57600");
    baud_rate_sec->addItem("115200");
    baud_rate_sec->addItem("128000");
    baud_rate_sec->addItem("230400");
    baud_rate_sec->addItem("256000");
    baud_rate_sec->addItem("460800");
    baud_rate_sec->addItem("500000");
    baud_rate_sec->addItem("600000");
    baud_rate_sec->addItem("750000");
    baud_rate_sec->addItem("921600");
    baud_rate_sec->addItem("1000000");
    baud_rate_sec->addItem("1500000");
    baud_rate_sec->addItem("2000000");
    baud_rate_sec->setCurrentIndex(13);
    data_bit_sec =new QComboBox;
    data_bit_sec->addItem("5");
    data_bit_sec->addItem("6");
    data_bit_sec->addItem("7");
    data_bit_sec->addItem("8");
    data_bit_sec->setCurrentIndex(3);
    stop_bit_sec =new QComboBox;
    stop_bit_sec->addItem("1.5");
    stop_bit_sec->addItem("2");
    stop_bit_sec->setCurrentIndex(1);

    parity_bit_sec =new QComboBox;
    parity_bit_sec->addItem("None");
    parity_bit_sec->addItem("Odd");
    parity_bit_sec->addItem("Even");
    parity_bit_sec->addItem("Mark");
    parity_bit_sec->addItem("Space");

    flow_control_sec=new QComboBox;
    flow_control_sec->addItem("Hardware");
    flow_control_sec->addItem("Software");
    flow_control_sec->addItem("None");
    flow_control_sec->addItem("Custom");
    flow_control_sec->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
    //f3->addRow(speed_q[11],x_Bleed_rate_sec);
    //f3->addRow(speed_q[12],y_Bleed_rate_sec);
    f3->addRow(speed_q_sec[0],maxspeedx_sec);
    f3->addRow(speed_q_sec[1],maxspeedy_sec);
    f3->addRow(speed_q_sec[2],deadx_sec);
    f3->addRow(speed_q_sec[3],deady_sec);
    f3->addRow(speed_q_sec[4],output_d_type_sec);
    f3->addRow(speed_q_sec[5],out_address_sec);
    f3->addRow(speed_q_sec[6],baud_rate_sec);
    f3->addRow(speed_q_sec[7],data_bit_sec);
    f3->addRow(speed_q_sec[8],stop_bit_sec);
    f3->addRow(speed_q_sec[9],parity_bit_sec);
    f3->addRow(speed_q_sec[10],flow_control_sec);





    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(sensor_speed);
    v->addLayout(f3);
    //v->addWidget(gbox_speedy);
    w_speedconv_sec->setLayout(v);

    connect(btn_speed_default,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Default_Slot_sec()));
    connect(btn_speed_update,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Update_Slot_sec()));
    connect(speedx1_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx1_Slot_sec()));
    connect(speedx2_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx2_Slot_sec()));
    connect(speedx3_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx3_Slot_sec()));
    connect(speedx4_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx4_Slot_sec()));
    connect(speedx5_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx5_Slot_sec()));
    connect(speedx6_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx6_Slot_sec()));
    connect(speedx7_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx7_Slot_sec()));
    connect(speedx8_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx8_Slot_sec()));
    connect(speedx9_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx9_Slot_sec()));
    connect(speedx10_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx10_Slot_sec()));
    connect(speedy1_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot_sec()));
    connect(speedy2_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot_sec()));
    connect(speedy3_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot_sec()));
    connect(speedy4_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot_sec()));
    connect(speedy5_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot_sec()));
    connect(speedy6_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot_sec()));
    connect(speedy7_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot_sec()));
    connect(speedy8_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot_sec()));
    connect(speedy9_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot_sec()));
    connect(speedy10_lineEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy10_Slot_sec()));

    connect(x_Bleed_rate_sec,SIGNAL(returnPressed()),this,SLOT(x_Bleed_rate_Slot_sec()));
    connect(y_Bleed_rate_sec,SIGNAL(returnPressed()),this,SLOT(y_Bleed_rate_Slot_sec()));
    connect(maxspeedx_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedx_Slot_sec()));
    connect(maxspeedy_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedy_Slot_sec()));
    connect(deadx_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_deadx_Slot_sec()));
    connect(deady_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_deady_Slot_sec()));
    connect(output_d_type_sec,SIGNAL(activated(int)),this,SLOT(combox_output_d_type_Slot_sec(int)));
    connect(out_address_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_out_address_Slot_sec()));
    connect(baud_rate_sec,SIGNAL(activated(int)),this,SLOT(combox_baud_rate_Slot_sec(int)));
    connect(data_bit_sec,SIGNAL(activated(int)),this,SLOT(combox_data_bit_Slot_sec(int)));
    connect(stop_bit_sec,SIGNAL(activated(int)),this,SLOT(combox_stop_bit_Slot_sec(int)));
    connect(flow_control_sec,SIGNAL(activated(int)),this,SLOT(combox_flow_control_Slot_sec(int)));
    connect(parity_bit_sec,SIGNAL(activated(int)),this,SLOT(combox_parity_bit_Slot_sec(int)));


}

void MainWindow::init_speedconvCfg_thi()
{
    w_speedconv_thi=new MyWidget;
    w_speedconv_thi->setWindowTitle("转台配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("通道3");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_speedx_thi=new QGroupBox();
    gbox_speedx_thi->setTitle("x轴");
    speedx1_lineEdt_thi=new QLineEdit;
    speedx2_lineEdt_thi=new QLineEdit;
    speedx3_lineEdt_thi=new QLineEdit;
    speedx4_lineEdt_thi=new QLineEdit;
    speedx5_lineEdt_thi=new QLineEdit;
    speedx6_lineEdt_thi=new QLineEdit;
    speedx7_lineEdt_thi=new QLineEdit;
    speedx8_lineEdt_thi=new QLineEdit;
    speedx9_lineEdt_thi=new QLineEdit;
    speedx10_lineEdt_thi=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(speed_s_thi[0],speedx1_lineEdt_thi);
    f1->addRow(speed_s_thi[1],speedx2_lineEdt_thi);
    f1->addRow(speed_s_thi[2],speedx3_lineEdt_thi);
    f1->addRow(speed_s_thi[3],speedx4_lineEdt_thi);
    f1->addRow(speed_s_thi[4],speedx5_lineEdt_thi);
    f1->addRow(speed_s_thi[5],speedx6_lineEdt_thi);
    f1->addRow(speed_s_thi[6],speedx7_lineEdt_thi);
    f1->addRow(speed_s_thi[7],speedx8_lineEdt_thi);
    f1->addRow(speed_s_thi[8],speedx9_lineEdt_thi);
    f1->addRow(speed_s_thi[9],speedx10_lineEdt_thi);
    gbox_speedx_thi->setLayout(f1);

    gbox_speedy_thi=new QGroupBox();
    gbox_speedy_thi->setTitle("y轴");
    speedy1_lineEdt_thi=new QLineEdit;
    speedy2_lineEdt_thi=new QLineEdit;
    speedy3_lineEdt_thi=new QLineEdit;
    speedy4_lineEdt_thi=new QLineEdit;
    speedy5_lineEdt_thi=new QLineEdit;
    speedy6_lineEdt_thi=new QLineEdit;
    speedy7_lineEdt_thi=new QLineEdit;
    speedy8_lineEdt_thi=new QLineEdit;
    speedy9_lineEdt_thi=new QLineEdit;
    speedy10_lineEdt_thi=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(speed_s_thi[0],speedy1_lineEdt_thi);
    f2->addRow(speed_s_thi[1],speedy2_lineEdt_thi);
    f2->addRow(speed_s_thi[2],speedy3_lineEdt_thi);
    f2->addRow(speed_s_thi[3],speedy4_lineEdt_thi);
    f2->addRow(speed_s_thi[4],speedy5_lineEdt_thi);
    f2->addRow(speed_s_thi[5],speedy6_lineEdt_thi);
    f2->addRow(speed_s_thi[6],speedy7_lineEdt_thi);
    f2->addRow(speed_s_thi[7],speedy8_lineEdt_thi);
    f2->addRow(speed_s_thi[8],speedy9_lineEdt_thi);
    f2->addRow(speed_s_thi[9],speedy10_lineEdt_thi);
    gbox_speedy_thi->setLayout(f2);

    QHBoxLayout *sensor_speed=new QHBoxLayout;
    sensor_speed->addWidget(gbox_speedx_thi);
    sensor_speed->addWidget(gbox_speedy_thi);


    x_Bleed_rate_thi= new QLineEdit;
    y_Bleed_rate_thi= new QLineEdit;
    maxspeedx_thi = new QLineEdit;
    maxspeedy_thi = new QLineEdit;
    deadx_thi     = new QLineEdit;
    deady_thi     = new QLineEdit;
    output_d_type_thi =new QComboBox;
    output_d_type_thi->addItem("像素偏差");
    output_d_type_thi->addItem("Pid控制算法结果输出");
    output_d_type_thi->addItem("转台命令输出");
    out_address_thi =new QLineEdit;
    baud_rate_thi =new QComboBox;
    baud_rate_thi->addItem("0");
    baud_rate_thi->addItem("110");
    baud_rate_thi->addItem("300");
    baud_rate_thi->addItem("600");
    baud_rate_thi->addItem("1200");
    baud_rate_thi->addItem("2400");
    baud_rate_thi->addItem("4800");
    baud_rate_thi->addItem("9600");
    baud_rate_thi->addItem("14400");
    baud_rate_thi->addItem("19200");
    baud_rate_thi->addItem("38400");
    baud_rate_thi->addItem("56000");
    baud_rate_thi->addItem("57600");
    baud_rate_thi->addItem("115200");
    baud_rate_thi->addItem("128000");
    baud_rate_thi->addItem("230400");
    baud_rate_thi->addItem("256000");
    baud_rate_thi->addItem("460800");
    baud_rate_thi->addItem("500000");
    baud_rate_thi->addItem("600000");
    baud_rate_thi->addItem("750000");
    baud_rate_thi->addItem("921600");
    baud_rate_thi->addItem("1000000");
    baud_rate_thi->addItem("1500000");
    baud_rate_thi->addItem("2000000");
    baud_rate_thi->setCurrentIndex(13);
    data_bit_thi =new QComboBox;
    data_bit_thi->addItem("5");
    data_bit_thi->addItem("6");
    data_bit_thi->addItem("7");
    data_bit_thi->addItem("8");
    data_bit_thi->setCurrentIndex(3);
    stop_bit_thi =new QComboBox;
    stop_bit_thi->addItem("1.5");
    stop_bit_thi->addItem("2");
    stop_bit_thi->setCurrentIndex(1);

    parity_bit_thi =new QComboBox;
    parity_bit_thi->addItem("None");
    parity_bit_thi->addItem("Odd");
    parity_bit_thi->addItem("Even");
    parity_bit_thi->addItem("Mark");
    parity_bit_thi->addItem("Space");

    flow_control_thi=new QComboBox;
    flow_control_thi->addItem("Hardware");
    flow_control_thi->addItem("Software");
    flow_control_thi->addItem("None");
    flow_control_thi->addItem("Custom");
    flow_control_thi->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
    //f3->addRow(speed_q[11],x_Bleed_rate_thi);
    //f3->addRow(speed_q[12],y_Bleed_rate_thi);
    f3->addRow(speed_q_thi[0],maxspeedx_thi);
    f3->addRow(speed_q_thi[1],maxspeedy_thi);
    f3->addRow(speed_q_thi[2],deadx_thi);
    f3->addRow(speed_q_thi[3],deady_thi);
    f3->addRow(speed_q_thi[4],output_d_type_thi);
    f3->addRow(speed_q_thi[5],out_address_thi);
    f3->addRow(speed_q_thi[6],baud_rate_thi);
    f3->addRow(speed_q_thi[7],data_bit_thi);
    f3->addRow(speed_q_thi[8],stop_bit_thi);
    f3->addRow(speed_q_thi[9],parity_bit_thi);
    f3->addRow(speed_q_thi[10],flow_control_thi);





    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(sensor_speed);
    v->addLayout(f3);
    //v->addWidget(gbox_speedy);
    w_speedconv_thi->setLayout(v);

    connect(btn_speed_default,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Default_Slot_thi()));
    connect(btn_speed_update,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Update_Slot_thi()));
    connect(speedx1_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx1_Slot_thi()));
    connect(speedx2_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx2_Slot_thi()));
    connect(speedx3_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx3_Slot_thi()));
    connect(speedx4_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx4_Slot_thi()));
    connect(speedx5_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx5_Slot_thi()));
    connect(speedx6_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx6_Slot_thi()));
    connect(speedx7_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx7_Slot_thi()));
    connect(speedx8_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx8_Slot_thi()));
    connect(speedx9_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx9_Slot_thi()));
    connect(speedx10_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx10_Slot_thi()));
    connect(speedy1_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot_thi()));
    connect(speedy2_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot_thi()));
    connect(speedy3_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot_thi()));
    connect(speedy4_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot_thi()));
    connect(speedy5_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot_thi()));
    connect(speedy6_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot_thi()));
    connect(speedy7_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot_thi()));
    connect(speedy8_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot_thi()));
    connect(speedy9_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot_thi()));
    connect(speedy10_lineEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy10_Slot_thi()));
    connect(x_Bleed_rate_thi,SIGNAL(returnPressed()),this,SLOT(x_Bleed_rate_Slot_thi()));
    connect(y_Bleed_rate_thi,SIGNAL(returnPressed()),this,SLOT(y_Bleed_rate_Slot_thi()));
    connect(maxspeedx_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedx_Slot_thi()));
    connect(maxspeedy_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedy_Slot_thi()));
    connect(deadx_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_deadx_Slot_thi()));
    connect(deady_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_deady_Slot_thi()));
    connect(output_d_type_thi,SIGNAL(activated(int)),this,SLOT(combox_output_d_type_Slot_thi(int)));
    connect(out_address_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_out_address_Slot_thi()));
    connect(baud_rate_thi,SIGNAL(activated(int)),this,SLOT(combox_baud_rate_Slot_thi(int)));
    connect(data_bit_thi,SIGNAL(activated(int)),this,SLOT(combox_data_bit_Slot_thi(int)));
    connect(stop_bit_thi,SIGNAL(activated(int)),this,SLOT(combox_stop_bit_Slot_thi(int)));
    connect(flow_control_thi,SIGNAL(activated(int)),this,SLOT(combox_flow_control_Slot_thi(int)));
    connect(parity_bit_thi,SIGNAL(activated(int)),this,SLOT(combox_parity_bit_Slot_thi(int)));
}

void MainWindow::init_speedconvCfg_fou()
{
    w_speedconv_fou=new MyWidget;
    w_speedconv_fou->setWindowTitle("转台配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("通道4");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_speedx_fou=new QGroupBox();
    gbox_speedx_fou->setTitle("x轴");
    speedx1_lineEdt_fou=new QLineEdit;
    speedx2_lineEdt_fou=new QLineEdit;
    speedx3_lineEdt_fou=new QLineEdit;
    speedx4_lineEdt_fou=new QLineEdit;
    speedx5_lineEdt_fou=new QLineEdit;
    speedx6_lineEdt_fou=new QLineEdit;
    speedx7_lineEdt_fou=new QLineEdit;
    speedx8_lineEdt_fou=new QLineEdit;
    speedx9_lineEdt_fou=new QLineEdit;
    speedx10_lineEdt_fou=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(speed_s_fou[0],speedx1_lineEdt_fou);
    f1->addRow(speed_s_fou[1],speedx2_lineEdt_fou);
    f1->addRow(speed_s_fou[2],speedx3_lineEdt_fou);
    f1->addRow(speed_s_fou[3],speedx4_lineEdt_fou);
    f1->addRow(speed_s_fou[4],speedx5_lineEdt_fou);
    f1->addRow(speed_s_fou[5],speedx6_lineEdt_fou);
    f1->addRow(speed_s_fou[6],speedx7_lineEdt_fou);
    f1->addRow(speed_s_fou[7],speedx8_lineEdt_fou);
    f1->addRow(speed_s_fou[8],speedx9_lineEdt_fou);
    f1->addRow(speed_s_fou[9],speedx10_lineEdt_fou);
    gbox_speedx_fou->setLayout(f1);

    gbox_speedy_fou=new QGroupBox();
    gbox_speedy_fou->setTitle("y轴");
    speedy1_lineEdt_fou=new QLineEdit;
    speedy2_lineEdt_fou=new QLineEdit;
    speedy3_lineEdt_fou=new QLineEdit;
    speedy4_lineEdt_fou=new QLineEdit;
    speedy5_lineEdt_fou=new QLineEdit;
    speedy6_lineEdt_fou=new QLineEdit;
    speedy7_lineEdt_fou=new QLineEdit;
    speedy8_lineEdt_fou=new QLineEdit;
    speedy9_lineEdt_fou=new QLineEdit;
    speedy10_lineEdt_fou=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(speed_s_fou[0],speedy1_lineEdt_fou);
    f2->addRow(speed_s_fou[1],speedy2_lineEdt_fou);
    f2->addRow(speed_s_fou[2],speedy3_lineEdt_fou);
    f2->addRow(speed_s_fou[3],speedy4_lineEdt_fou);
    f2->addRow(speed_s_fou[4],speedy5_lineEdt_fou);
    f2->addRow(speed_s_fou[5],speedy6_lineEdt_fou);
    f2->addRow(speed_s_fou[6],speedy7_lineEdt_fou);
    f2->addRow(speed_s_fou[7],speedy8_lineEdt_fou);
    f2->addRow(speed_s_fou[8],speedy9_lineEdt_fou);
    f2->addRow(speed_s_fou[9],speedy10_lineEdt_fou);
    gbox_speedy_fou->setLayout(f2);

    QHBoxLayout *sensor_speed=new QHBoxLayout;
    sensor_speed->addWidget(gbox_speedx_fou);
    sensor_speed->addWidget(gbox_speedy_fou);


    x_Bleed_rate_fou= new QLineEdit;
    y_Bleed_rate_fou= new QLineEdit;
    maxspeedx_fou = new QLineEdit;
    maxspeedy_fou = new QLineEdit;
    deadx_fou     = new QLineEdit;
    deady_fou     = new QLineEdit;
    output_d_type_fou =new QComboBox;
    output_d_type_fou->addItem("像素偏差");
    output_d_type_fou->addItem("Pid控制算法结果输出");
    output_d_type_fou->addItem("转台命令输出");
    out_address_fou =new QLineEdit;
    baud_rate_fou =new QComboBox;
    baud_rate_fou->addItem("0");
    baud_rate_fou->addItem("110");
    baud_rate_fou->addItem("300");
    baud_rate_fou->addItem("600");
    baud_rate_fou->addItem("1200");
    baud_rate_fou->addItem("2400");
    baud_rate_fou->addItem("4800");
    baud_rate_fou->addItem("9600");
    baud_rate_fou->addItem("14400");
    baud_rate_fou->addItem("19200");
    baud_rate_fou->addItem("38400");
    baud_rate_fou->addItem("56000");
    baud_rate_fou->addItem("57600");
    baud_rate_fou->addItem("115200");
    baud_rate_fou->addItem("128000");
    baud_rate_fou->addItem("230400");
    baud_rate_fou->addItem("256000");
    baud_rate_fou->addItem("460800");
    baud_rate_fou->addItem("500000");
    baud_rate_fou->addItem("600000");
    baud_rate_fou->addItem("750000");
    baud_rate_fou->addItem("921600");
    baud_rate_fou->addItem("1000000");
    baud_rate_fou->addItem("1500000");
    baud_rate_fou->addItem("2000000");
    baud_rate_fou->setCurrentIndex(13);
    data_bit_fou =new QComboBox;
    data_bit_fou->addItem("5");
    data_bit_fou->addItem("6");
    data_bit_fou->addItem("7");
    data_bit_fou->addItem("8");
    data_bit_fou->setCurrentIndex(3);
    stop_bit_fou =new QComboBox;
    stop_bit_fou->addItem("1.5");
    stop_bit_fou->addItem("2");
    stop_bit_fou->setCurrentIndex(1);

    parity_bit_fou =new QComboBox;
    parity_bit_fou->addItem("None");
    parity_bit_fou->addItem("Odd");
    parity_bit_fou->addItem("Even");
    parity_bit_fou->addItem("Mark");
    parity_bit_fou->addItem("Space");

    flow_control_fou=new QComboBox;
    flow_control_fou->addItem("Hardware");
    flow_control_fou->addItem("Software");
    flow_control_fou->addItem("None");
    flow_control_fou->addItem("Custom");
    flow_control_fou->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
   // f3->addRow(speed_q[11],x_Bleed_rate_fou);
    //f3->addRow(speed_q[12],y_Bleed_rate_fou);
    f3->addRow(speed_q_fou[0],maxspeedx_fou);
    f3->addRow(speed_q_fou[1],maxspeedy_fou);
    f3->addRow(speed_q_fou[2],deadx_fou);
    f3->addRow(speed_q_fou[3],deady_fou);
    f3->addRow(speed_q_fou[4],output_d_type_fou);
    f3->addRow(speed_q_fou[5],out_address_fou);
    f3->addRow(speed_q_fou[6],baud_rate_fou);
    f3->addRow(speed_q_fou[7],data_bit_fou);
    f3->addRow(speed_q_fou[8],stop_bit_fou);
    f3->addRow(speed_q_fou[9],parity_bit_fou);
    f3->addRow(speed_q_fou[10],flow_control_fou);





    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(sensor_speed);
    v->addLayout(f3);
    //v->addWidget(gbox_speedy);
    w_speedconv_fou->setLayout(v);

    connect(btn_speed_default,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Default_Slot_fou()));
    connect(btn_speed_update,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Update_Slot_fou()));
    connect(speedx1_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx1_Slot_fou()));
    connect(speedx2_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx2_Slot_fou()));
    connect(speedx3_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx3_Slot_fou()));
    connect(speedx4_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx4_Slot_fou()));
    connect(speedx5_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx5_Slot_fou()));
    connect(speedx6_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx6_Slot_fou()));
    connect(speedx7_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx7_Slot_fou()));
    connect(speedx8_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx8_Slot_fou()));
    connect(speedx9_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx9_Slot_fou()));
    connect(speedx10_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx10_Slot_fou()));
    connect(speedy1_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot_fou()));
    connect(speedy2_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot_fou()));
    connect(speedy3_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot_fou()));
    connect(speedy4_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot_fou()));
    connect(speedy5_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot_fou()));
    connect(speedy6_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot_fou()));
    connect(speedy7_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot_fou()));
    connect(speedy8_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot_fou()));
    connect(speedy9_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot_fou()));
    connect(speedy10_lineEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy10_Slot_fou()));
    connect(x_Bleed_rate_fou,SIGNAL(returnPressed()),this,SLOT(x_Bleed_rate_Slot_fou()));
    connect(y_Bleed_rate_fou,SIGNAL(returnPressed()),this,SLOT(y_Bleed_rate_Slot_fou()));
    connect(maxspeedx_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedx_Slot_fou()));
    connect(maxspeedy_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedy_Slot_fou()));
    connect(deadx_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_deadx_Slot_fou()));
    connect(deady_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_deady_Slot_fou()));
    connect(output_d_type_fou,SIGNAL(activated(int)),this,SLOT(combox_output_d_type_Slot_fou(int)));
    connect(out_address_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_out_address_Slot_fou()));
    connect(baud_rate_fou,SIGNAL(activated(int)),this,SLOT(combox_baud_rate_Slot_fou(int)));
    connect(data_bit_fou,SIGNAL(activated(int)),this,SLOT(combox_data_bit_Slot_fou(int)));
    connect(stop_bit_fou,SIGNAL(activated(int)),this,SLOT(combox_stop_bit_Slot_fou(int)));
    connect(flow_control_fou,SIGNAL(activated(int)),this,SLOT(combox_flow_control_Slot_fou(int)));
    connect(parity_bit_fou,SIGNAL(activated(int)),this,SLOT(combox_parity_bit_Slot_fou(int)));
}

void MainWindow::init_speedconvCfg_fif()
{
    w_speedconv_fif=new MyWidget;
    w_speedconv_fif->setWindowTitle("转台配置");
    QPushButton* btn_speed_default=new QPushButton;
    QPushButton* btn_speed_update=new QPushButton;
    btn_speed_default->setText("默认");
    btn_speed_update->setText("保存");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_speed_default);
    v1->addWidget(btn_speed_update);
    QLabel *label=new QLabel;
    label->setText("通道5");
    QHBoxLayout *h1=new QHBoxLayout;
    h1->addLayout(v1);
    h1->addWidget(label);

    gbox_speedx_fif=new QGroupBox();
    gbox_speedx_fif->setTitle("x轴");
    speedx1_lineEdt_fif=new QLineEdit;
    speedx2_lineEdt_fif=new QLineEdit;
    speedx3_lineEdt_fif=new QLineEdit;
    speedx4_lineEdt_fif=new QLineEdit;
    speedx5_lineEdt_fif=new QLineEdit;
    speedx6_lineEdt_fif=new QLineEdit;
    speedx7_lineEdt_fif=new QLineEdit;
    speedx8_lineEdt_fif=new QLineEdit;
    speedx9_lineEdt_fif=new QLineEdit;
    speedx10_lineEdt_fif=new QLineEdit;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(speed_s_fif[0],speedx1_lineEdt_fif);
    f1->addRow(speed_s_fif[1],speedx2_lineEdt_fif);
    f1->addRow(speed_s_fif[2],speedx3_lineEdt_fif);
    f1->addRow(speed_s_fif[3],speedx4_lineEdt_fif);
    f1->addRow(speed_s_fif[4],speedx5_lineEdt_fif);
    f1->addRow(speed_s_fif[5],speedx6_lineEdt_fif);
    f1->addRow(speed_s_fif[6],speedx7_lineEdt_fif);
    f1->addRow(speed_s_fif[7],speedx8_lineEdt_fif);
    f1->addRow(speed_s_fif[8],speedx9_lineEdt_fif);
    f1->addRow(speed_s_fif[9],speedx10_lineEdt_fif);
    gbox_speedx_fif->setLayout(f1);

    gbox_speedy_fif=new QGroupBox();
    gbox_speedy_fif->setTitle("y轴");
    speedy1_lineEdt_fif=new QLineEdit;
    speedy2_lineEdt_fif=new QLineEdit;
    speedy3_lineEdt_fif=new QLineEdit;
    speedy4_lineEdt_fif=new QLineEdit;
    speedy5_lineEdt_fif=new QLineEdit;
    speedy6_lineEdt_fif=new QLineEdit;
    speedy7_lineEdt_fif=new QLineEdit;
    speedy8_lineEdt_fif=new QLineEdit;
    speedy9_lineEdt_fif=new QLineEdit;
    speedy10_lineEdt_fif=new QLineEdit;

    QFormLayout *f2=new QFormLayout();
    f2->addRow(speed_s_fif[0],speedy1_lineEdt_fif);
    f2->addRow(speed_s_fif[1],speedy2_lineEdt_fif);
    f2->addRow(speed_s_fif[2],speedy3_lineEdt_fif);
    f2->addRow(speed_s_fif[3],speedy4_lineEdt_fif);
    f2->addRow(speed_s_fif[4],speedy5_lineEdt_fif);
    f2->addRow(speed_s_fif[5],speedy6_lineEdt_fif);
    f2->addRow(speed_s_fif[6],speedy7_lineEdt_fif);
    f2->addRow(speed_s_fif[7],speedy8_lineEdt_fif);
    f2->addRow(speed_s_fif[8],speedy9_lineEdt_fif);
    f2->addRow(speed_s_fif[9],speedy10_lineEdt_fif);
    gbox_speedy_fif->setLayout(f2);

    QHBoxLayout *sensor_speed=new QHBoxLayout;
    sensor_speed->addWidget(gbox_speedx_fif);
    sensor_speed->addWidget(gbox_speedy_fif);


    x_Bleed_rate_fif= new QLineEdit;
    y_Bleed_rate_fif= new QLineEdit;
    maxspeedx_fif = new QLineEdit;
    maxspeedy_fif = new QLineEdit;
    deadx_fif     = new QLineEdit;
    deady_fif     = new QLineEdit;
    output_d_type_fif =new QComboBox;
    output_d_type_fif->addItem("像素偏差");
    output_d_type_fif->addItem("Pid控制算法结果输出");
    output_d_type_fif->addItem("转台命令输出");
    out_address_fif =new QLineEdit;
    baud_rate_fif =new QComboBox;
    baud_rate_fif->addItem("0");
    baud_rate_fif->addItem("110");
    baud_rate_fif->addItem("300");
    baud_rate_fif->addItem("600");
    baud_rate_fif->addItem("1200");
    baud_rate_fif->addItem("2400");
    baud_rate_fif->addItem("4800");
    baud_rate_fif->addItem("9600");
    baud_rate_fif->addItem("14400");
    baud_rate_fif->addItem("19200");
    baud_rate_fif->addItem("38400");
    baud_rate_fif->addItem("56000");
    baud_rate_fif->addItem("57600");
    baud_rate_fif->addItem("115200");
    baud_rate_fif->addItem("128000");
    baud_rate_fif->addItem("230400");
    baud_rate_fif->addItem("256000");
    baud_rate_fif->addItem("460800");
    baud_rate_fif->addItem("500000");
    baud_rate_fif->addItem("600000");
    baud_rate_fif->addItem("750000");
    baud_rate_fif->addItem("921600");
    baud_rate_fif->addItem("1000000");
    baud_rate_fif->addItem("1500000");
    baud_rate_fif->addItem("2000000");
    baud_rate_fif->setCurrentIndex(13);
    data_bit_fif =new QComboBox;
    data_bit_fif->addItem("5");
    data_bit_fif->addItem("6");
    data_bit_fif->addItem("7");
    data_bit_fif->addItem("8");
    data_bit_fif->setCurrentIndex(3);
    stop_bit_fif =new QComboBox;
    stop_bit_fif->addItem("1.5");
    stop_bit_fif->addItem("2");
    stop_bit_fif->setCurrentIndex(1);

    parity_bit_fif =new QComboBox;
    parity_bit_fif->addItem("None");
    parity_bit_fif->addItem("Odd");
    parity_bit_fif->addItem("Even");
    parity_bit_fif->addItem("Mark");
    parity_bit_fif->addItem("Space");

    flow_control_fif=new QComboBox;
    flow_control_fif->addItem("Hardware");
    flow_control_fif->addItem("Software");
    flow_control_fif->addItem("None");
    flow_control_fif->addItem("Custom");
    flow_control_fif->setCurrentIndex(2);

    QFormLayout *f3=new QFormLayout();
    //f3->addRow(speed_q[11],x_Bleed_rate_fif);
   // f3->addRow(speed_q[12],y_Bleed_rate_fif);
    f3->addRow(speed_q_fif[0],maxspeedx_fif);
    f3->addRow(speed_q_fif[1],maxspeedy_fif);
    f3->addRow(speed_q_fif[2],deadx_fif);
    f3->addRow(speed_q_fif[3],deady_fif);
    f3->addRow(speed_q_fif[4],output_d_type_fif);
    f3->addRow(speed_q_fif[5],out_address_fif);
    f3->addRow(speed_q_fif[6],baud_rate_fif);
    f3->addRow(speed_q_fif[7],data_bit_fif);
    f3->addRow(speed_q_fif[8],stop_bit_fif);
    f3->addRow(speed_q_fif[9],parity_bit_fif);
    f3->addRow(speed_q_fif[10],flow_control_fif);





    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(sensor_speed);
    v->addLayout(f3);
    //v->addWidget(gbox_speedy);
    w_speedconv_fif->setLayout(v);

    connect(btn_speed_default,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Default_Slot_fif()));
    connect(btn_speed_update,SIGNAL(clicked(bool)),this,SLOT(btn_Speed_Update_Slot_fif()));
    connect(speedx1_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx1_Slot_fif()));
    connect(speedx2_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx2_Slot_fif()));
    connect(speedx3_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx3_Slot_fif()));
    connect(speedx4_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx4_Slot_fif()));
    connect(speedx5_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx5_Slot_fif()));
    connect(speedx6_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx6_Slot_fif()));
    connect(speedx7_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx7_Slot_fif()));
    connect(speedx8_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx8_Slot_fif()));
    connect(speedx9_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx9_Slot_fif()));
    connect(speedx10_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedx10_Slot_fif()));
    connect(speedy1_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy1_Slot_fif()));
    connect(speedy2_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy2_Slot_fif()));
    connect(speedy3_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy3_Slot_fif()));
    connect(speedy4_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy4_Slot_fif()));
    connect(speedy5_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy5_Slot_fif()));
    connect(speedy6_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy6_Slot_fif()));
    connect(speedy7_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy7_Slot_fif()));
    connect(speedy8_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy8_Slot_fif()));
    connect(speedy9_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy9_Slot_fif()));
    connect(speedy10_lineEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_speedy10_Slot_fif()));
    connect(x_Bleed_rate_fif,SIGNAL(returnPressed()),this,SLOT(x_Bleed_rate_Slot_fif()));
    connect(y_Bleed_rate_fif,SIGNAL(returnPressed()),this,SLOT(y_Bleed_rate_Slot_fif()));
    connect(maxspeedx_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedx_Slot_fif()));
    connect(maxspeedy_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_maxspeedy_Slot_fif()));
    connect(deadx_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_deadx_Slot_fif()));
    connect(deady_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_deady_Slot_fif()));
    connect(output_d_type_fif,SIGNAL(activated(int)),this,SLOT(combox_output_d_type_Slot_fif(int)));
    connect(out_address_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_out_address_Slot_fif()));
    connect(baud_rate_fif,SIGNAL(activated(int)),this,SLOT(combox_baud_rate_Slot_fif(int)));
    connect(data_bit_fif,SIGNAL(activated(int)),this,SLOT(combox_data_bit_Slot_fif(int)));
    connect(stop_bit_fif,SIGNAL(activated(int)),this,SLOT(combox_stop_bit_Slot_fif(int)));
    connect(flow_control_fif,SIGNAL(activated(int)),this,SLOT(combox_flow_control_Slot_fif(int)));
    connect(parity_bit_fif,SIGNAL(activated(int)),this,SLOT(combox_parity_bit_Slot_fif(int)));
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

    zone_setting =new  QCheckBox;




    QLabel *l=new  QLabel;
    l->setText(",");
    QLabel *n=new  QLabel;
    n->setText("*");
    rigion_Cen_x=new QLineEdit;
    rigion_Cen_y=new QLineEdit;
    rigion_Cen_w=new QLineEdit;
    rigion_Cen_h=new QLineEdit;

//    lineEdit_fieldResolution->setValidator(new QIntValidator(100,10000,this));
//    lineEdit_fieldResolution2->setValidator(new QIntValidator(100,10000,this));

    QHBoxLayout *sensor_rigion_Cen_xy=new QHBoxLayout;
    sensor_rigion_Cen_xy->addWidget(rigion_Cen_x);
    sensor_rigion_Cen_xy->addWidget(l);
    sensor_rigion_Cen_xy->addWidget(rigion_Cen_y);

    QHBoxLayout *sensor_rigion_Cen_wh=new QHBoxLayout;
    sensor_rigion_Cen_wh->addWidget(rigion_Cen_w);
    sensor_rigion_Cen_wh->addWidget(n);
    sensor_rigion_Cen_wh->addWidget(rigion_Cen_h);

    maxnum=new QLineEdit;
    uspeed=new QLineEdit;
    maxpix=new QLineEdit;
    minpix=new QLineEdit;
    sensitive=new QLineEdit;
    dspeed=new QLineEdit;
    trktime=new QLineEdit;
    Priority_judgment =new QComboBox;
    Priority_judgment->addItem("距离中心位置最大");
    Priority_judgment->addItem("距离中心位置最近");
    Priority_judgment->addItem("亮度最大");
    Priority_judgment->addItem("亮度最小");
    Priority_judgment->addItem("面积最大");
    Priority_judgment->addItem("面积最小");
    output = new QComboBox;
    output->addItem("使能");
    output->addItem("禁止");
    polar=new QComboBox;
    polar->addItem("常开");
    polar->addItem("关闭");

    QLabel *d=new  QLabel;
    d->setText("秒");
    QLabel *s=new  QLabel;
    s->setText(" ");
    Alarm_delay = new QLineEdit;
    QHBoxLayout *sensor_Ad=new QHBoxLayout;
    sensor_Ad->addWidget(Alarm_delay);
    sensor_Ad->addWidget(d);
    sensor_Ad->addWidget(s);

    QFormLayout *f1=new QFormLayout();
    f1->addRow(mtd_s[13],zone_setting);
    f1->addRow(mtd_s[0],sensor_rigion_Cen_xy);
    f1->addRow(mtd_s[1],sensor_rigion_Cen_wh);
    f1->addRow(mtd_s[2],maxnum);
    f1->addRow(mtd_s[3],uspeed);
    f1->addRow(mtd_s[4],maxpix);
    f1->addRow(mtd_s[5],minpix);
    f1->addRow(mtd_s[6],sensitive);
    f1->addRow(mtd_s[7],dspeed);
    f1->addRow(mtd_s[8],trktime);
    f1->addRow(mtd_s[9],Priority_judgment);
    f1->addRow(mtd_s[10],output);
    f1->addRow(mtd_s[11],polar);
    f1->addRow(mtd_s[12],sensor_Ad);

    QVBoxLayout *v=new QVBoxLayout;
    v->addLayout(h1);
    v->addLayout(f1);
    w_mtd->setLayout(v);
    w_mtd->resize(300,450);

    connect(btn_mtd_default,SIGNAL(clicked(bool)),this,SLOT(btn_mtd_Default_Slot()));
    connect(btn_mtd_update,SIGNAL(clicked(bool)),this,SLOT(btn_mtd_Update_Slot()));
    connect(zone_setting,SIGNAL(checked(bool)),this,SLOT(zone_setting_Slot()));
    connect(rigion_Cen_x,SIGNAL(returnPressed()),this,SLOT(lEdt_rigion_Cen_x_Slot()));
    connect(rigion_Cen_y,SIGNAL(returnPressed()),this,SLOT(lEdt_rigion_Cen_y_Slot()));
    connect(rigion_Cen_w,SIGNAL(returnPressed()),this,SLOT(lEdt_rigion_Cen_w_Slot()));
    connect(rigion_Cen_h,SIGNAL(returnPressed()),this,SLOT(lEdt_rigion_Cen_h_Slot()));
    connect(maxnum,SIGNAL(returnPressed()),this,SLOT(lEdt_maxnum_Slot()));
    connect(uspeed,SIGNAL(returnPressed()),this,SLOT(lEdt_uspeed_Slot()));
    connect(maxpix,SIGNAL(returnPressed()),this,SLOT(lEdt_maxpix_Slot()));
    connect(minpix,SIGNAL(returnPressed()),this,SLOT(lEdt_minpix_Slot()));
    connect(sensitive,SIGNAL(returnPressed()),this,SLOT(lEdt_sensitive_Slot()));
    connect(dspeed,SIGNAL(returnPressed()),this,SLOT(lEdt_dspeed_Slot()));
    connect(trktime,SIGNAL(returnPressed()),this,SLOT(lEdt_trktime_Slot()));
      // connect(output,SIGNAL(currentIndexChanged(int)),this,SLOT(combox_output_Slot(int index)));
    connect(Priority_judgment,SIGNAL(activated(int)),this,SLOT(combox_Priority_judgment_Slot(int)));
    connect(output,SIGNAL(activated(int)),this,SLOT(combox_output_Slot(int)));
    connect(polar,SIGNAL(activated(int)),this,SLOT(combox_polar_Slot(int)));
    connect(Alarm_delay,SIGNAL(returnPressed()),this,SLOT(lEdt_Alarm_delay_Slot()));

}
void MainWindow::init_josCfg()
{

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
    checkBox2=new QCheckBox;
    osd1_pos_x=new QLineEdit;
    osd1_pos_y=new QLineEdit;
    osd1_lineEdit_label=new QLineEdit;
    osd1_lineEdit_context=new QLineEdit;
    CBox_color=new QComboBox;
    CBox_transparency=new QComboBox;

    btn_osd1_default=new QPushButton;
    btn_osd1_update=new QPushButton;
    btn_keep1 = new QPushButton;
    btn_keep1->setText("保存");
    btn_osd1_default->setText("默认");
    btn_osd1_update->setText("设置");
    QVBoxLayout *v1=new QVBoxLayout;
    v1->addWidget(btn_osd1_default);
    v1->addWidget(btn_keep1);
    QLabel *label=new QLabel;
    label->setText("     ");
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


    CBox_transparency->addItem("0%");
    CBox_transparency->addItem("10%");
    CBox_transparency->addItem("20%");
    CBox_transparency->addItem("30%");
    CBox_transparency->addItem("40%");
    CBox_transparency->addItem("50%");
    CBox_transparency->addItem("60%");
    CBox_transparency->addItem("70%");
    CBox_transparency->addItem("80%");
    CBox_transparency->addItem("90%");
    CBox_transparency->addItem("100%");


//    osd1_lineEdit_font=new QLineEdit;
//    osd1_lineEdit_color=new QLineEdit;
     QHBoxLayout *hf=new QHBoxLayout;

    QFormLayout *f1=new QFormLayout();
    f1->addRow(osd_s[0],checkBox);
    hf->addLayout(f1);
    hf->addWidget(btn_osd1_update);




    Custom =new QGroupBox();
    Custom->setTitle("用户自定义");



    QFormLayout *f=new QFormLayout();
    f->addRow(osd_s[1],checkBox2);
    f->addRow(osd_s[2],osd1_pos_x);
    f->addRow(osd_s[3],osd1_pos_y);
    //f->addRow(osd_s[3],osd1_lineEdit_label);
    f->addRow(osd_s[4],osd1_lineEdit_context);

    f->addRow(osd_s[5],CBox_color);
    f->addRow(osd_s[6],CBox_transparency);
    f->addRow(osd_s[7],CBox_font_size);


    //connect(c,SIGNAL(activated(int)),this,SLOT(toCBox(int)));

    QVBoxLayout *v=new QVBoxLayout;


    v->addLayout(h1);
     v->addLayout(hf);
    v->addWidget(c);
    v->addLayout(f);


    connect(btn_osd1_default,SIGNAL(clicked(bool)),this,SLOT(btn_osd_default_Slot()));
    connect(btn_keep1,SIGNAL(clicked(bool)),this,SLOT(btn_keep1_Slot()));
    connect(btn_osd1_update,SIGNAL(clicked(bool)),this,SLOT(btn_osd_update_Slot()));

    connect(c,SIGNAL(activated(int)),this,SLOT(CBox_osd_choose_Slot(int)));
    connect(CBox_font,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_Slot(int)));
    connect(CBox_font_size,SIGNAL(currentIndexChanged(int)),this,SLOT(CBox_osd_font_size_Slot(int)));
    connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(checkBox_Slot(int)));
    //connect(osd1_pos_x,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_x_Slot()));
   // connect(osd1_pos_y,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_y_Slot()));
   // connect(osd1_lineEdit_context,SIGNAL(returnPressed()),this,SLOT(lEdt_osd_context_Slot()));

   //connect(CBox_color,SIGNAL(activated(int)),this,SLOT(CBox_osd_color_Slot(int)));
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
    connect(lineEdit_s1_Fov0,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV0_Slot()));
    connect(spbx_switch1,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch1_Slot()));
    connect(spby_switch1,SIGNAL(valueChanged(int)),this,SLOT(spby_switch1_Slot()));
    connect(lineEdit_s1_Fov1,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV1_Slot()));
    connect(spbx_switch2,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch2_Slot()));
    connect(spby_switch2,SIGNAL(valueChanged(int)),this,SLOT(spby_switch2_Slot()));
    connect(lineEdit_s1_Fov2,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV2_Slot()));
    connect(spbx_switch3,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch3_Slot()));
    connect(spby_switch3,SIGNAL(valueChanged(int)),this,SLOT(spby_switch3_Slot()));
    connect(lineEdit_s1_Fov3,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV3_Slot()));
    connect(spbx_switch4,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch4_Slot()));
    connect(spby_switch4,SIGNAL(valueChanged(int)),this,SLOT(spby_switch4_Slot()));
    connect(lineEdit_s1_Fov4,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV4_Slot()));
    connect(spbx_switch5,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch5_Slot()));
    connect(spby_switch5,SIGNAL(valueChanged(int)),this,SLOT(spby_switch5_Slot()));



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
    connect(testfov,SIGNAL(returnPressed()),this,SLOT(spby1_Slot()));
    connect(fEdt1,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt1_Slot()));
    connect(lEdt1,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt1_Slot()));
    connect(spbx1,SIGNAL(valueChanged(int)),this,SLOT(spbx1_Slot()));
    connect(spby1,SIGNAL(valueChanged(int)),this,SLOT(spby1_Slot()));
    connect(fEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt2_Slot()));
    connect(lEdt2,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt2_Slot()));
    connect(spbx2,SIGNAL(valueChanged(int)),this,SLOT(spbx2_Slot()));
    connect(spby2,SIGNAL(valueChanged(int)),this,SLOT(spby2_Slot()));
    connect(fEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt3_Slot()));
    connect(lEdt3,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt3_Slot()));
    connect(spbx3,SIGNAL(valueChanged(int)),this,SLOT(spbx3_Slot()));
    connect(spby3,SIGNAL(valueChanged(int)),this,SLOT(spby3_Slot()));
    connect(fEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt4_Slot()));
    connect(lEdt4,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt4_Slot()));
    connect(spbx4,SIGNAL(valueChanged(int)),this,SLOT(spbx4_Slot()));
    connect(spby4,SIGNAL(valueChanged(int)),this,SLOT(spby4_Slot()));
    connect(fEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt5_Slot()));
    connect(lEdt5,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt5_Slot()));
    connect(spbx5,SIGNAL(valueChanged(int)),this,SLOT(spbx5_Slot()));
    connect(spby5,SIGNAL(valueChanged(int)),this,SLOT(spby5_Slot()));
    connect(fEdt6,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt6_Slot()));
    connect(lEdt6,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt6_Slot()));
    connect(spbx6,SIGNAL(valueChanged(int)),this,SLOT(spbx6_Slot()));
    connect(spby6,SIGNAL(valueChanged(int)),this,SLOT(spby6_Slot()));
    connect(fEdt7,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt7_Slot()));
    connect(lEdt7,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt7_Slot()));
    connect(spbx7,SIGNAL(valueChanged(int)),this,SLOT(spbx7_Slot()));
    connect(spby7,SIGNAL(valueChanged(int)),this,SLOT(spby7_Slot()));
    connect(fEdt8,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt8_Slot()));
    connect(lEdt8,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt8_Slot()));
    connect(spbx8,SIGNAL(valueChanged(int)),this,SLOT(spbx8_Slot()));
    connect(spby8,SIGNAL(valueChanged(int)),this,SLOT(spby8_Slot()));
    connect(fEdt9,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt9_Slot()));
    connect(lEdt9,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt9_Slot()));
    connect(spbx9,SIGNAL(valueChanged(int)),this,SLOT(spbx9_Slot()));
    connect(spby9,SIGNAL(valueChanged(int)),this,SLOT(spby9_Slot()));
    connect(fEdt10,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt10_Slot()));
    connect(lEdt10,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt10_Slot()));
    connect(spbx10,SIGNAL(valueChanged(int)),this,SLOT(spbx10_Slot()));
    connect(spby10,SIGNAL(valueChanged(int)),this,SLOT(spby10_Slot()));
    connect(fEdt11,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt11_Slot()));
    connect(lEdt11,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt11_Slot()));
    connect(spbx11,SIGNAL(valueChanged(int)),this,SLOT(spbx11_Slot()));
    connect(spby11,SIGNAL(valueChanged(int)),this,SLOT(spby11_Slot()));
    connect(fEdt12,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt12_Slot()));
    connect(lEdt12,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt12_Slot()));
    connect(spbx12,SIGNAL(valueChanged(int)),this,SLOT(spbx12_Slot()));
    connect(spby12,SIGNAL(valueChanged(int)),this,SLOT(spby12_Slot()));
    connect(fEdt13,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt13_Slot()));
    connect(lEdt13,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt13_Slot()));
    connect(spbx13,SIGNAL(valueChanged(int)),this,SLOT(spbx13_Slot()));
    connect(spby13,SIGNAL(valueChanged(int)),this,SLOT(spby13_Slot()));
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
    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_sec()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_fieldRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot2()));
    connect(lineEdit_fieldResolution_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot2()));
    connect(lineEdit_fieldResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot2()));
    connect(lEdt_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot2()));
    connect(sp_sec,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot2(int)));
    connect(sp2_sec,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot2(int)));


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

    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_sec()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_switchRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot2()));
    connect(lineEdit_switchResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot2()));
    connect(spbx_switch1_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch1_Slot2()));
    connect(spby_switch1_sec,SIGNAL(valueChanged(int)),this,SLOT(spby_switch1_Slot2()));
    connect(lineEdit_s1_Fov1_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV1_Slot2()));
    connect(spbx_switch2_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch2_Slot2()));
    connect(spby_switch2_sec,SIGNAL(valueChanged(int)),this,SLOT(spby_switch2_Slot2()));
    connect(lineEdit_s1_Fov2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV2_Slot2()));
    connect(spbx_switch3_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch3_Slot2()));
    connect(spby_switch3_sec,SIGNAL(valueChanged(int)),this,SLOT(spby_switch3_Slot2()));
    connect(lineEdit_s1_Fov3_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV3_Slot2()));
    connect(spbx_switch4_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch4_Slot2()));
    connect(spby_switch4_sec,SIGNAL(valueChanged(int)),this,SLOT(spby_switch4_Slot2()));
    connect(lineEdit_s1_Fov4_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV4_Slot2()));
    connect(spbx_switch5_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch5_Slot2()));
    connect(spby_switch5_sec,SIGNAL(valueChanged(int)),this,SLOT(spby_switch5_Slot2()));

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

    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_sec()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_continueRadio_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot2()));
    connect(lineEdit_continueResolution2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot2()));

    connect(testfov_sec,SIGNAL(returnPressed()),this,SLOT(spby1_Slot2()));
    connect(fEdt1_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt1_Slot2()));
    connect(lEdt1_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt1_Slot2()));
    connect(spbx1_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx1_Slot2()));
    connect(spby1_sec,SIGNAL(valueChanged(int)),this,SLOT(spby1_Slot2()));
    connect(fEdt2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt2_Slot2()));
    connect(lEdt2_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt2_Slot2()));
    connect(spbx2_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx2_Slot2()));
    connect(spby2_sec,SIGNAL(valueChanged(int)),this,SLOT(spby2_Slot2()));
    connect(fEdt3_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt3_Slot2()));
    connect(lEdt3_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt3_Slot2()));
    connect(spbx3_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx3_Slot2()));
    connect(spby3_sec,SIGNAL(valueChanged(int)),this,SLOT(spby3_Slot2()));
    connect(fEdt4_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt4_Slot2()));
    connect(lEdt4_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt4_Slot2()));
    connect(spbx4_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx4_Slot2()));
    connect(spby4_sec,SIGNAL(valueChanged(int)),this,SLOT(spby4_Slot2()));
    connect(fEdt5_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt5_Slot2()));
    connect(lEdt5_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt5_Slot2()));
    connect(spbx5_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx5_Slot2()));
    connect(spby5_sec,SIGNAL(valueChanged(int)),this,SLOT(spby5_Slot2()));
    connect(fEdt6_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt6_Slot2()));
    connect(lEdt6_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt6_Slot2()));
    connect(spbx6_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx6_Slot2()));
    connect(spby6_sec,SIGNAL(valueChanged(int)),this,SLOT(spby6_Slot2()));
    connect(fEdt7_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt7_Slot2()));
    connect(lEdt7_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt7_Slot2()));
    connect(spbx7_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx7_Slot2()));
    connect(spby7_sec,SIGNAL(valueChanged(int)),this,SLOT(spby7_Slot2()));
    connect(fEdt8_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt8_Slot2()));
    connect(lEdt8_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt8_Slot2()));
    connect(spbx8_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx8_Slot2()));
    connect(spby8_sec,SIGNAL(valueChanged(int)),this,SLOT(spby8_Slot2()));
    connect(fEdt9_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt9_Slot2()));
    connect(lEdt9_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt9_Slot2()));
    connect(spbx9_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx9_Slot2()));
    connect(spby9_sec,SIGNAL(valueChanged(int)),this,SLOT(spby9_Slot2()));
    connect(fEdt10_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt10_Slot2()));
    connect(lEdt10_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt10_Slot2()));
    connect(spbx10_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx10_Slot2()));
    connect(spby10_sec,SIGNAL(valueChanged(int)),this,SLOT(spby10_Slot2()));
    connect(fEdt11_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt11_Slot2()));
    connect(lEdt11_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt11_Slot2()));
    connect(spbx11_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx11_Slot2()));
    connect(spby11_sec,SIGNAL(valueChanged(int)),this,SLOT(spby11_Slot2()));
    connect(fEdt12_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt12_Slot2()));
    connect(lEdt12_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt12_Slot2()));
    connect(spbx12_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx12_Slot2()));
    connect(spby12_sec,SIGNAL(valueChanged(int)),this,SLOT(spby12_Slot2()));
    connect(fEdt13_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt13_Slot2()));
    connect(lEdt13_sec,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt13_Slot2()));
    connect(spbx13_sec,SIGNAL(valueChanged(int)),this,SLOT(spbx13_Slot2()));
    connect(spby13_sec,SIGNAL(valueChanged(int)),this,SLOT(spby13_Slot2()));

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

    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_thi()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_thi()));
    connect(lineEdit_fieldRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot()));
    connect(lineEdit_fieldResolution_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot3()));
    connect(lineEdit_fieldResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot3()));
    connect(lEdt_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot3()));
    connect(sp_thi,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot3(int)));
    connect(sp2_thi,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot3(int)));

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

    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_thi()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot_thi()));
    connect(lineEdit_switchRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot_thi()));
    connect(lineEdit_switchResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot_thi()));

    connect(spbx_switch1_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch1_Slot3()));
    connect(spby_switch1_thi,SIGNAL(valueChanged(int)),this,SLOT(spby_switch1_Slot3()));
    connect(lineEdit_s1_Fov1_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV1_Slot3()));
    connect(spbx_switch2_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch2_Slot3()));
    connect(spby_switch2_thi,SIGNAL(valueChanged(int)),this,SLOT(spby_switch2_Slot3()));
    connect(lineEdit_s1_Fov2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV2_Slot3()));
    connect(spbx_switch3_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch3_Slot3()));
    connect(spby_switch3_thi,SIGNAL(valueChanged(int)),this,SLOT(spby_switch3_Slot3()));
    connect(lineEdit_s1_Fov3_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV3_Slot3()));
    connect(spbx_switch4_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch4_Slot3()));
    connect(spby_switch4_thi,SIGNAL(valueChanged(int)),this,SLOT(spby_switch4_Slot3()));
    connect(lineEdit_s1_Fov4_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV4_Slot3()));
    connect(spbx_switch5_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch5_Slot3()));
    connect(spby_switch5_thi,SIGNAL(valueChanged(int)),this,SLOT(spby_switch5_Slot3()));



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

    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_thi()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_continueRadio_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot3()));
    connect(lineEdit_continueResolution2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot_thi()));

    connect(testfov_thi,SIGNAL(returnPressed()),this,SLOT(spby1_Slot3()));
    connect(fEdt1_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt1_Slot3()));
    connect(lEdt1_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt1_Slot3()));
    connect(spbx1_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx1_Slot3()));
    connect(spby1_thi,SIGNAL(valueChanged(int)),this,SLOT(spby1_Slot3()));
    connect(fEdt2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt2_Slot3()));
    connect(lEdt2_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt2_Slot3()));
    connect(spbx2_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx2_Slot3()));
    connect(spby2_thi,SIGNAL(valueChanged(int)),this,SLOT(spby2_Slot3()));
    connect(fEdt3_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt3_Slot3()));
    connect(lEdt3_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt3_Slot3()));
    connect(spbx3_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx3_Slot3()));
    connect(spby3_thi,SIGNAL(valueChanged(int)),this,SLOT(spby3_Slot3()));
    connect(fEdt4_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt4_Slot3()));
    connect(lEdt4_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt4_Slot3()));
    connect(spbx4_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx4_Slot3()));
    connect(spby4_thi,SIGNAL(valueChanged(int)),this,SLOT(spby4_Slot3()));
    connect(fEdt5_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt5_Slot3()));
    connect(lEdt5_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt5_Slot3()));
    connect(spbx5_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx5_Slot3()));
    connect(spby5_thi,SIGNAL(valueChanged(int)),this,SLOT(spby5_Slot3()));
    connect(fEdt6_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt6_Slot3()));
    connect(lEdt6_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt6_Slot3()));
    connect(spbx6_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx6_Slot3()));
    connect(spby6_thi,SIGNAL(valueChanged(int)),this,SLOT(spby6_Slot3()));
    connect(fEdt7_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt7_Slot3()));
    connect(lEdt7_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt7_Slot3()));
    connect(spbx7_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx7_Slot3()));
    connect(spby7_thi,SIGNAL(valueChanged(int)),this,SLOT(spby7_Slot3()));
    connect(fEdt8_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt8_Slot3()));
    connect(lEdt8_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt8_Slot3()));
    connect(spbx8_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx8_Slot3()));
    connect(spby8_thi,SIGNAL(valueChanged(int)),this,SLOT(spby8_Slot3()));
    connect(fEdt9_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt9_Slot3()));
    connect(lEdt9_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt9_Slot3()));
    connect(spbx9_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx9_Slot3()));
    connect(spby9_thi,SIGNAL(valueChanged(int)),this,SLOT(spby9_Slot3()));
    connect(fEdt10_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt10_Slot3()));
    connect(lEdt10_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt10_Slot3()));
    connect(spbx10_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx10_Slot3()));
    connect(spby10_thi,SIGNAL(valueChanged(int)),this,SLOT(spby10_Slot3()));
    connect(fEdt11_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt11_Slot3()));
    connect(lEdt11_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt11_Slot3()));
    connect(spbx11_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx11_Slot3()));
    connect(spby11_thi,SIGNAL(valueChanged(int)),this,SLOT(spby11_Slot3()));
    connect(fEdt12_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt12_Slot3()));
    connect(lEdt12_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt12_Slot3()));
    connect(spbx12_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx12_Slot3()));
    connect(spby12_thi,SIGNAL(valueChanged(int)),this,SLOT(spby12_Slot3()));
    connect(fEdt13_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt13_Slot3()));
    connect(lEdt13_thi,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt13_Slot3()));
    connect(spbx13_thi,SIGNAL(valueChanged(int)),this,SLOT(spbx13_Slot3()));
    connect(spby13_thi,SIGNAL(valueChanged(int)),this,SLOT(spby13_Slot3()));

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

    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_fou()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_fieldRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot4()));
    connect(lineEdit_fieldResolution_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot4()));
    connect(lineEdit_fieldResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot4()));
    connect(lEdt_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot4()));
    connect(sp_fou,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot4(int)));
    connect(sp2_fou,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot4(int)));

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

    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_fou()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_switchRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot4()));
    connect(lineEdit_switchResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot4()));

    connect(spbx_switch1_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch1_Slot4()));
    connect(spby_switch1_fou,SIGNAL(valueChanged(int)),this,SLOT(spby_switch1_Slot4()));
    connect(lineEdit_s1_Fov1_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV1_Slot4()));
    connect(spbx_switch2_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch2_Slot4()));
    connect(spby_switch2_fou,SIGNAL(valueChanged(int)),this,SLOT(spby_switch2_Slot4()));
    connect(lineEdit_s1_Fov2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV2_Slot4()));
    connect(spbx_switch3_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch3_Slot4()));
    connect(spby_switch3_fou,SIGNAL(valueChanged(int)),this,SLOT(spby_switch3_Slot4()));
    connect(lineEdit_s1_Fov3_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV3_Slot4()));
    connect(spbx_switch4_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch4_Slot4()));
    connect(spby_switch4_fou,SIGNAL(valueChanged(int)),this,SLOT(spby_switch4_Slot4()));
    connect(lineEdit_s1_Fov4_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV4_Slot4()));
    connect(spbx_switch5_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch5_Slot4()));
    connect(spby_switch5_fou,SIGNAL(valueChanged(int)),this,SLOT(spby_switch5_Slot4()));


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

    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_fou()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_continueRadio_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot4()));
    connect(lineEdit_continueResolution2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot4()));

    connect(testfov_fou,SIGNAL(returnPressed()),this,SLOT(spby1_Slot4()));
    connect(fEdt1_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt1_Slot4()));
    connect(lEdt1_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt1_Slot4()));
    connect(spbx1_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx1_Slot4()));
    connect(spby1_fou,SIGNAL(valueChanged(int)),this,SLOT(spby1_Slot4()));
    connect(fEdt2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt2_Slot4()));
    connect(lEdt2_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt2_Slot4()));
    connect(spbx2_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx2_Slot4()));
    connect(spby2_fou,SIGNAL(valueChanged(int)),this,SLOT(spby2_Slot4()));
    connect(fEdt3_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt3_Slot4()));
    connect(lEdt3_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt3_Slot4()));
    connect(spbx3_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx3_Slot4()));
    connect(spby3_fou,SIGNAL(valueChanged(int)),this,SLOT(spby3_Slot4()));
    connect(fEdt4_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt4_Slot4()));
    connect(lEdt4_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt4_Slot4()));
    connect(spbx4_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx4_Slot4()));
    connect(spby4_fou,SIGNAL(valueChanged(int)),this,SLOT(spby4_Slot4()));
    connect(fEdt5_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt5_Slot4()));
    connect(lEdt5_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt5_Slot4()));
    connect(spbx5_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx5_Slot4()));
    connect(spby5_fou,SIGNAL(valueChanged(int)),this,SLOT(spby5_Slot4()));
    connect(fEdt6_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt6_Slot4()));
    connect(lEdt6_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt6_Slot4()));
    connect(spbx6_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx6_Slot4()));
    connect(spby6_fou,SIGNAL(valueChanged(int)),this,SLOT(spby6_Slot4()));
    connect(fEdt7_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt7_Slot4()));
    connect(lEdt7_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt7_Slot4()));
    connect(spbx7_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx7_Slot4()));
    connect(spby7_fou,SIGNAL(valueChanged(int)),this,SLOT(spby7_Slot4()));
    connect(fEdt8_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt8_Slot4()));
    connect(lEdt8_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt8_Slot4()));
    connect(spbx8_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx8_Slot4()));
    connect(spby8_fou,SIGNAL(valueChanged(int)),this,SLOT(spby8_Slot4()));
    connect(fEdt9_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt9_Slot4()));
    connect(lEdt9_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt9_Slot4()));
    connect(spbx9_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx9_Slot4()));
    connect(spby9_fou,SIGNAL(valueChanged(int)),this,SLOT(spby9_Slot4()));
    connect(fEdt10_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt10_Slot4()));
    connect(lEdt10_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt10_Slot4()));
    connect(spbx10_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx10_Slot4()));
    connect(spby10_fou,SIGNAL(valueChanged(int)),this,SLOT(spby10_Slot4()));
    connect(fEdt11_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt11_Slot4()));
    connect(lEdt11_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt11_Slot4()));
    connect(spbx11_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx11_Slot4()));
    connect(spby11_fou,SIGNAL(valueChanged(int)),this,SLOT(spby11_Slot4()));
    connect(fEdt12_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt12_Slot4()));
    connect(lEdt12_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt12_Slot4()));
    connect(spbx12_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx12_Slot4()));
    connect(spby12_fou,SIGNAL(valueChanged(int)),this,SLOT(spby12_Slot4()));
    connect(fEdt13_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt13_Slot4()));
    connect(lEdt13_fou,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt13_Slot4()));
    connect(spbx13_fou,SIGNAL(valueChanged(int)),this,SLOT(spbx13_Slot4()));
    connect(spby13_fou,SIGNAL(valueChanged(int)),this,SLOT(spby13_Slot4()));
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

    connect(btn_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot_fif()));
    connect(btn_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_fieldRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_Radio_Slot5()));
    connect(lineEdit_fieldResolution_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution_Slot5()));
    connect(lineEdit_fieldResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_Resolution2_Slot5()));
    connect(lEdt_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fix_view_Slot5()));
    connect(sp_fif,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_x_Slot5(int)));
    connect(sp2_fif,SIGNAL(valueChanged(int)),this,SLOT(sp_fix_y_Slot5(int)));

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

    connect(btn_s1Switch_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot2_fif()));
    connect(btn_s1Switch_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_switchRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Radio_Slot5()));
    connect(lineEdit_switchResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_Resolution_Slot5()));

    connect(spbx_switch1_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch1_Slot5()));
    connect(spby_switch1_fif,SIGNAL(valueChanged(int)),this,SLOT(spby_switch1_Slot5()));
    connect(lineEdit_s1_Fov1_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV1_Slot5()));
    connect(spbx_switch2_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch2_Slot5()));
    connect(spby_switch2_fif,SIGNAL(valueChanged(int)),this,SLOT(spby_switch2_Slot5()));
    connect(lineEdit_s1_Fov2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV2_Slot5()));
    connect(spbx_switch3_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch3_Slot5()));
    connect(spby_switch3_fif,SIGNAL(valueChanged(int)),this,SLOT(spby_switch3_Slot5()));
    connect(lineEdit_s1_Fov3_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV3_Slot5()));
    connect(spbx_switch4_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch4_Slot5()));
    connect(spby_switch4_fif,SIGNAL(valueChanged(int)),this,SLOT(spby_switch4_Slot5()));
    connect(lineEdit_s1_Fov4_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_switch_s1_FOV4_Slot5()));
    connect(spbx_switch5_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx_switch5_Slot5()));
    connect(spby_switch5_fif,SIGNAL(valueChanged(int)),this,SLOT(spby_switch5_Slot5()));


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

    connect(btn_continue_default,SIGNAL(clicked(bool)),this,SLOT(btn_default_Slot3_fif()));
    connect(btn_continue_update,SIGNAL(clicked(bool)),this,SLOT(btn_capture2_update_Slot()));
    connect(lineEdit_continueRadio_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Radio_Slot5()));
    connect(lineEdit_continueResolution2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_continue_Resolution_Slot5()));

    connect(testfov_fif,SIGNAL(returnPressed()),this,SLOT(spby1_Slot5()));
    connect(fEdt1_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt1_Slot5()));
    connect(lEdt1_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt1_Slot5()));
    connect(spbx1_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx1_Slot5()));
    connect(spby1_fif,SIGNAL(valueChanged(int)),this,SLOT(spby1_Slot5()));
    connect(fEdt2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt2_Slot5()));
    connect(lEdt2_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt2_Slot5()));
    connect(spbx2_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx2_Slot5()));
    connect(spby2_fif,SIGNAL(valueChanged(int)),this,SLOT(spby2_Slot5()));
    connect(fEdt3_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt3_Slot5()));
    connect(lEdt3_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt3_Slot5()));
    connect(spbx3_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx3_Slot5()));
    connect(spby3_fif,SIGNAL(valueChanged(int)),this,SLOT(spby3_Slot5()));
    connect(fEdt4_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt4_Slot5()));
    connect(lEdt4_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt4_Slot5()));
    connect(spbx4_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx4_Slot5()));
    connect(spby4_fif,SIGNAL(valueChanged(int)),this,SLOT(spby4_Slot5()));
    connect(fEdt5_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt5_Slot5()));
    connect(lEdt5_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt5_Slot5()));
    connect(spbx5_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx5_Slot5()));
    connect(spby5_fif,SIGNAL(valueChanged(int)),this,SLOT(spby5_Slot5()));
    connect(fEdt6_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt6_Slot5()));
    connect(lEdt6_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt6_Slot5()));
    connect(spbx6_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx6_Slot5()));
    connect(spby6_fif,SIGNAL(valueChanged(int)),this,SLOT(spby6_Slot5()));
    connect(fEdt7_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt7_Slot5()));
    connect(lEdt7_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt7_Slot5()));
    connect(spbx7_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx7_Slot5()));
    connect(spby7_fif,SIGNAL(valueChanged(int)),this,SLOT(spby7_Slot5()));
    connect(fEdt8_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt8_Slot5()));
    connect(lEdt8_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt8_Slot5()));
    connect(spbx8_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx8_Slot5()));
    connect(spby8_fif,SIGNAL(valueChanged(int)),this,SLOT(spby8_Slot5()));
    connect(fEdt9_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt9_Slot5()));
    connect(lEdt9_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt9_Slot5()));
    connect(spbx9_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx9_Slot5()));
    connect(spby9_fif,SIGNAL(valueChanged(int)),this,SLOT(spby9_Slot5()));
    connect(fEdt10_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt10_Slot5()));
    connect(lEdt10_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt10_Slot5()));
    connect(spbx10_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx10_Slot5()));
    connect(spby10_fif,SIGNAL(valueChanged(int)),this,SLOT(spby10_Slot5()));
    connect(fEdt11_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt11_Slot5()));
    connect(lEdt11_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt11_Slot5()));
    connect(spbx11_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx11_Slot5()));
    connect(spby11_fif,SIGNAL(valueChanged(int)),this,SLOT(spby11_Slot5()));
    connect(fEdt12_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt12_Slot5()));
    connect(lEdt12_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt12_Slot5()));
    connect(spbx12_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx12_Slot5()));
    connect(spby12_fif,SIGNAL(valueChanged(int)),this,SLOT(spby12_Slot5()));
    connect(fEdt13_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_fEdt13_Slot5()));
    connect(lEdt13_fif,SIGNAL(returnPressed()),this,SLOT(lEdt_lEdt13_Slot5()));
    connect(spbx13_fif,SIGNAL(valueChanged(int)),this,SLOT(spbx13_Slot5()));
    connect(spby13_fif,SIGNAL(valueChanged(int)),this,SLOT(spby13_Slot5()));

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


    /*
    for(int i=1;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x03;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }*/
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=0x03;
    send_arr[6]=0x08;
    send_oneframe(3);
    send_mutex.unlock();


    w_plat->show();
    w_plat->show_stat = 1;
}

void MainWindow::showvedioCfg1()
{
    send_mutex.lock();
    send_arr[4]=0x63;
    send_arr[5]=0x01;
    send_oneframe(2);
    send_mutex.unlock();
    vedio_current_shichang = 0;
    w_sersor_1->show();
    w_sersor_1->show_stat = 1;
}

void MainWindow::showvedioCfg2()
{
    vedio_current_shichang_sec = 0;
    send_mutex.lock();
    send_arr[4]=0x63;
    send_arr[5]=0x02;
    send_oneframe(2);
    send_mutex.unlock();
    w_sersor_1_sec->show();
    w_sersor_1_sec->show_stat = 1;
}

void MainWindow::showvedioCfg3()
{
    send_mutex.lock();
    send_arr[4]=0x63;
    send_arr[5]=0x03;
    send_oneframe(2);
    send_mutex.unlock();
    vedio_current_shichang_thi = 0;
    w_sersor_1_thi->show();
    w_sersor_1_thi->show_stat = 1;
}

void MainWindow::showvedioCfg4()
{
    send_mutex.lock();
    send_arr[4]=0x63;
    send_arr[5]=0x04;
    send_oneframe(2);
    send_mutex.unlock();
    vedio_current_shichang_fou = 0;
    w_sersor_1_fou->show();
    w_sersor_1_fou->show_stat = 1;
}

void MainWindow::showvedioCfg5()
{
    send_mutex.lock();
    send_arr[4]=0x63;
    send_arr[5]=0x05;
    send_oneframe(2);
    send_mutex.unlock();
    vedio_current_shichang_fif= 0;
    w_sersor_1_fif->show();
    w_sersor_1_fif->show_stat = 1;
}
void MainWindow::showpidsysCfg1()
{

        send_mutex.lock();
        send_arr[4]=0x46;
        send_arr[5]=1;
        send_oneframe(2);
        send_mutex.unlock();

    for(int i=1;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x02;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=48;
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

    w_pid->show();
    w_pid->show_stat = 1;
}

void MainWindow::showpidsysCfg2()
{
    send_mutex.lock();
    send_arr[4]=0x46;
    send_arr[5]=2;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=1;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=91;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=92;
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
    w_pid2->show();
    w_pid2->show_stat = 1;
}

void MainWindow::showpidsysCfg3()
{
    send_mutex.lock();
    send_arr[4]=0x46;
    send_arr[5]=3;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=1;i<7;i++){
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=93;
    send_arr[6]=i;
    send_oneframe(3);
    send_mutex.unlock();
    }
    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=94;
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
     w_pid3->show();
     w_pid3->show_stat = 1;
}
void MainWindow::showpidsysCfg4()
{
    send_mutex.lock();
    send_arr[4]=0x46;
    send_arr[5]=4;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=1;i<7;i++){
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=95;
    send_arr[6]=i;
    send_oneframe(3);
    send_mutex.unlock();
    }
    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=96;
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
    w_pid4->show();
    w_pid4->show_stat = 1;
}
void MainWindow::showpidsysCfg5()
{
    send_mutex.lock();
    send_arr[4]=0x46;
    send_arr[5]=5;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=1;i<7;i++){
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=97;
    send_arr[6]=i;
    send_oneframe(3);
    send_mutex.unlock();
    }
    for(int i=1;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=98;
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
    w_pid5->show();
    w_pid5->show_stat = 1;
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

    send_mutex.lock();
    send_arr[4] = 0x45;
    send_arr[5] = 1;
    send_oneframe(7);
    send_mutex.unlock();



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




        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=50;
        send_arr[6]=10;
        send_oneframe(3);
        send_mutex.unlock();

        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=50;
        send_arr[6]=13;
        send_oneframe(3);
        send_mutex.unlock();

    for(int i=1;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=3;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_speedconv->show();
    w_speedconv->show_stat = 1;
}

void MainWindow::showspeedconvcfg_sec()
{

    send_mutex.lock();
    send_arr[4]=0x45;
    send_arr[5]=2;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=99;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<8;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=100;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=100;
        send_arr[6]=10;
        send_oneframe(3);
        send_mutex.unlock();

        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=100;
        send_arr[6]=13;
        send_oneframe(3);
        send_mutex.unlock();

    w_speedconv_sec->show();
    w_speedconv_sec->show_stat = 1;

}

void MainWindow::showspeedconvcfg_thi()
{
    send_mutex.lock();
    send_arr[4]=0x45;
    send_arr[5]=3;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=101;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<8;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=102;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=102;
    send_arr[6]=10;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=102;
    send_arr[6]=13;
    send_oneframe(3);
    send_mutex.unlock();

    w_speedconv_thi->show();
    w_speedconv_thi->show_stat = 1;
}

void MainWindow::showspeedconvcfg_fou()
{
    send_mutex.lock();
    send_arr[4]=0x45;
    send_arr[5]=4;
    send_oneframe(2);
    send_mutex.unlock();

    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=103;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<10;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=104;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=104;
    send_arr[6]=10;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=104;
    send_arr[6]=13;
    send_oneframe(3);
    send_mutex.unlock();


    w_speedconv_fou->show();
    w_speedconv_fou->show_stat = 1;
}

void MainWindow::showspeedconvcfg_fif()
{
    send_mutex.lock();
    send_arr[4]=0x45;
    send_arr[5]=5;
    send_oneframe(2);
    send_mutex.unlock();


    for(int i=0;i<16;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=105;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<10;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=106;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=106;
    send_arr[6]=10;
    send_oneframe(3);
    send_mutex.unlock();

    send_mutex.lock();
    send_arr[4]=0x31;
    send_arr[5]=106;
    send_arr[6]=13;
    send_oneframe(3);
    send_mutex.unlock();


    w_speedconv_fif->show();
    w_speedconv_fif->show_stat = 1;
}

void MainWindow:: showmtdcfg()
{
    w_mtd->show();
    w_mtd->show_stat = 1;
}

void MainWindow::showjoscfg()
{
    /*
    for(int i=1;i<8;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x01;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_jos->show();
    w_jos->show_stat=1;
    */
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

    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x3b;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_sersor1_sec->show();
    w_sersor1_sec->show_stat = 1;
}
void MainWindow::showCamera_thi()
{
    current_shichang_thi = 0;

    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x43;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_sersor1_thi->show();
    w_sersor1_thi->show_stat = 1;
}

void MainWindow::showCamera_fou()
{
    current_shichang_fou = 0;

    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x4b;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    w_sersor1_fou->show();
    w_sersor1_fou->show_stat = 1;
}

void MainWindow::showCamera_fif()
{
    current_shichang_fif = 0;

    for(int i=0;i<7;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x53;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
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
    w_osd1->setWindowTitle("字符叠加");
   
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

    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x39;
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

    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x41;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x3c;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_seitchField_sec->show();
    w_seitchField_sec->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_thi()
{
    current_shichang_thi = 1;

    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x49;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x44;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_seitchField_thi->show();
    w_seitchField_thi->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_fou()
{
    current_shichang_fou = 1;

    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x51;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x4c;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_seitchField_fou->show();
    w_seitchField_fou->show_stat = 1;
}

void MainWindow::btnSensor1SwitchSlot_fif()
{
    current_shichang_fif = 1;

    for(int i=0;i<5;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x59;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<15;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x54;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_seitchField_fif->show();
    w_seitchField_fif->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot()
{
    current_shichang = 2;

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=58;
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
    for(int i=0;i<14;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x3c;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField->show();
    w_ContinueField->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_sec()
{
    current_shichang_sec = 2;

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x42;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=61;j<63;j++){
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
        send_arr[5]=63;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int i=0;i<14;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=64;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField_sec->show();
    w_ContinueField_sec->show_stat = 1;
}
void MainWindow::btnSensor2ContinueSlot_thi()
{
    current_shichang_thi = 2;
    for(int i=0;i<14;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=72;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=74;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=69;j<71;j++){
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
        send_arr[5]=71;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField_thi->show();
    w_ContinueField_thi->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_fou()
{
    current_shichang_fou = 2;

    for(int i=0;i<14;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=0x80;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=82;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=77;j<79;j++){
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
        send_arr[5]=79;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField_fou->show();
    w_ContinueField_fou->show_stat = 1;
}

void MainWindow::btnSensor2ContinueSlot_fif()
{
    current_shichang_fif = 2;

    for(int i=0;i<14;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=88;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }

    for(int i=0;i<4;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=90;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
    for(int j=85;j<87;j++){
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
        send_arr[5]=87;
        send_arr[6]=m;
        send_oneframe(3);
        send_mutex.unlock();
    }

    w_ContinueField_fif->show();
    w_ContinueField_fif->show_stat = 1;
}

void MainWindow::vedio_btnSensor1SwitchSlot()
{
    vedio_current_shichang = 1;
    w_seitchField_1->show();
    w_seitchField_1->show_stat = 1;
}

void MainWindow::vedio_btnSensor2ContinueSlot()
{
    vedio_current_shichang = 2;
    w_ContinueField_1->show();
    w_ContinueField_1->show_stat = 1;
}

void MainWindow::vedio_btnSensor1SwitchSlot_sec()
{
    vedio_current_shichang_sec = 1;
    w_seitchField_1_sec->show();
    w_seitchField_1_sec->show_stat = 1;
}

void MainWindow::vedio_btnSensor2ContinueSlot_sec()
{
    vedio_current_shichang_sec = 2;

    w_ContinueField_1_sec->show();
    w_ContinueField_1_sec->show_stat = 1;
}

void MainWindow::vedio_btnSensor1SwitchSlot_thi()
{
    vedio_current_shichang_thi = 1;
    w_seitchField_1_thi->show();
    w_seitchField_1_thi->show_stat = 1;

}

void MainWindow::vedio_btnSensor2ContinueSlot_thi()
{
    vedio_current_shichang_thi = 2;

    w_ContinueField_1_thi->show();
    w_ContinueField_1_thi->show_stat = 1;

}

void MainWindow::vedio_btnSensor1SwitchSlot_fou()
{
    vedio_current_shichang_fou = 1;

    w_seitchField_1_fou->show();
    w_seitchField_1_fou->show_stat = 1;


}

void MainWindow::vedio_btnSensor2ContinueSlot_fou()
{
    vedio_current_shichang_fou = 2;

    w_ContinueField_1_fou->show();
    w_ContinueField_1_fou->show_stat = 1;

}

void MainWindow::vedio_btnSensor1SwitchSlot_fif()
{
    vedio_current_shichang_fif = 1;

    w_seitchField_1_fif->show();
    w_seitchField_1_fif->show_stat = 1;

}

void MainWindow::vedio_btnSensor2ContinueSlot_fif()
{
    vedio_current_shichang_fif = 2;

    w_ContinueField_1_fif->show();
    w_ContinueField_1_fif->show_stat = 1;

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
