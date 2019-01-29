#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QEvent>
#include <QPainter>
#include "jos.h"
#include <QDialog>
#include <QPainter>
#include <QEvent>
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
#include<QVariant>
#include <QMessageBox>
#include<QDataStream>
#include "recserial.h"
#include "recvsocket.h"
#include <QtCore/qmath.h>
#include<QTime>
#include <QTimer>
#include<QTextEdit>
#include "recvusocket.h"
#include <QRadioButton>
#include "mywidget.h"
#include "myqspinbox.h"

#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767
#define POINTX 446 //圆心坐标x
#define POINTY 196 //圆鑫坐标Y
#define CENTER_B 96//大圆的半径
#define CENTER_S 10//小圆的半径
#define RATIO 10 //矩形框缩小比例

#define BUFFER_FULL          1
#define BUFFER_DATA          2
#define BUFFER_EMPTY         3
extern QMutex send_mutex;
extern QTcpSocket *usocket;
extern QTextEdit *upgrade_show;
extern QFile expfile;

namespace Ui {
class MainWindow;
}
static int net_port=0;
static QString net_ip=" ";

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*绘制事件*/
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void updatecircle_s(int x, int y);
    int InJoys(int x, int y);
    void sendjoyevent(int x, int y);

    /*初始化的配置*/
    void init_menu();
    void init_sysCfg();
    void init_platCfg();

    void init_pidCfg();
    void init_pidCfg2();
    void init_pidCfg3();
    void init_pidCfg4();
    void init_pidCfg5();
    void init_vedioCfg();
    void init_vedioCfg_sec();
    void init_vedioCfg_thi();
    void init_vedioCfg_fou();
    void init_vedioCfg_fif();
    void init_dbCfg();
    void init_speedconvCfg();
    void init_speedconvCfg_sec();
    void init_speedconvCfg_thi();
    void init_speedconvCfg_fou();
    void init_speedconvCfg_fif();
    void init_mtdCfg();
    void init_josCfg();
    void init_utcCfg();
    void init_captureCfg();
    void init_OSDCfg();
    void init_resl();
    void init_realtime_output();

    /*协议传输*/
    QByteArray string2hex(QString str,bool &flag);
    char convertHex2Char(char ch);
    void send_oneframe(int length);
    volatile qint32 sendNum =0;

    /*线程*/
    void output_to_label(int i);
    void socket_parse_bytearray();
    void usocket_parse_bytearray();
    //void socket_Read_Data();
    void upgrade_showtext(int i,int percent);
    void mystepby(int spid);

    void vedio_btnSensor1SwitchSlot();
    void vedio_btnSensor2ContinueSlot();

    void vedio_btnSensor1SwitchSlot_sec();
    void vedio_btnSensor2ContinueSlot_sec();

    void vedio_btnSensor1SwitchSlot_thi();
    void vedio_btnSensor2ContinueSlot_thi();

    void vedio_btnSensor1SwitchSlot_fou();
    void vedio_btnSensor2ContinueSlot_fou();

    void vedio_btnSensor1SwitchSlot_fif();
    void vedio_btnSensor2ContinueSlot_fif();

    /*发送0x31命令*/
    void read_config(int block);
    void send_read_config(int block,int start_field, int end_field);
    /*解析0x31命令*/
    void showblk23(int field, float value);
    void showblk24(int field, float value);
    void showblk25(int field, float value);
    void showblk26(int field, float value);
    void showblk27(int field, float value);
    void showblk56(int field, float value);
    void showblk57(int field, float value);
    void showblk58(int field, float value);
    void showblk59(int field, float value);
    void showblk60(int field, float value);
    void showblk61(int field, float value);
    void showblk62(int field, float value);
    void showblk63(int field, float value);
    void showblk64(int field, float value);
    void showblk65(int field, float value);
    void showblk66(int field, float value);
    void showblk67(int field, float value);
    void showblk68(int field, float value);
    void showblk69(int field, float value);
    void showblk70(int field, float value);
    void showblk71(int field, float value);
    void showblk72(int field, float value);
    void showblk73(int field, float value);
    void showblk74(int field, float value);
    void showblk75(int field, float value);
    void showblk76(int field, float value);
    void showblk77(int field, float value);
    void showblk78(int field, float value);
    void showblk79(int field, float value);
    void showblk80(int field, float value);
    void showblk81(int field, float value);
    void showblk82(int field, float value);
    void showblk83(int field, float value);
    void showblk84(int field, float value);
    void showblk85(int field, float value);
signals:
    void toNet(int port ,QString ip);
    void toSerial(QString port,qint32 baud,int check,int data,int stop);
    void copy_Done();
    void socket_copy_Done();
    void usocket_copy_Done();


public slots:

    /*定时器函数*/
    void timeoutSlot();
   	void socketTimeoutSlot();
    void clientDisconnected();
    /**/
    void btnToNet();
    void btnToSerial();
    void btnToClose();

    /**/
    void netReceiveMainSlot(int port, QString ip);
    void serialReceiveMainSlot(QString port, qint32 baud, int check, int data, int stop);
    /*界面显示*/
    void showJos();
    void showSysCfg();
    void showPlat();

    void showpidsysCfg1();
    void showpidsysCfg2();
    void showpidsysCfg3();
    void showpidsysCfg4();
    void showpidsysCfg5();
    void showvedioCfg1();
    void showvedioCfg2();
    void showvedioCfg3();
    void showvedioCfg4();
    void showvedioCfg5();

    void showAlg();
    void showAlg2();
    void showAlg3();
    void showCapture1();
    void showCapture2();
    void showCapture3();
    void showOther();
    void showdbgcfg();
    void showspeedconvcfg();
    void showspeedconvcfg_sec();
    void showspeedconvcfg_thi();
    void showspeedconvcfg_fou();
    void showspeedconvcfg_fif();
    void showmtdcfg();
    void showjoscfg();
    void show_realtime_output();

    void readfovmode1();
    void readfovmode2();
    void readfovmode3();
    void readfovmode4();
    void readfovmode5();
    /*系统配置槽函数*/
    void btnDownSlot();
    void btnUpSlot();
    void btnSaveSlot();
    void btnselectsw_clicked();
    void btnUpdate();
    void btnFPGA_clicked();

    /*摄像机槽函数*/
    void vedio_tosersor_fix(int i);
    void vedio_toSensor_switch(int i);
    void vedio_tosersor_continue(int i);

    void vedio_tosersor_fix_sec(int i);
    void vedio_toSensor_switch_sec(int i);
    void vedio_tosersor_continue_sec(int i);

    void vedio_tosersor_fix_thi(int i);
    void vedio_toSensor_switch_thi(int i);
    void vedio_tosersor_continue_thi(int i);

    void vedio_tosersor_fix_fou(int i);
    void vedio_toSensor_switch_fou(int i);
    void vedio_tosersor_continue_fou(int i);

    void vedio_tosersor_fix_fif(int i);
    void vedio_toSensor_switch_fif(int i);
    void vedio_tosersor_continue_fif(int i);


    /*相机配置槽函数*/
    void btn_default_Slot();
    void btn_default_Slot2();
    void btn_default_Slot3();
    void btn_default_Slot_sec();
    void btn_default_Slot2_sec();
    void btn_default_Slot3_sec();
    void btn_default_Slot_thi();
    void btn_default_Slot2_thi();
    void btn_default_Slot3_thi();
    void btn_default_Slot_fou();
    void btn_default_Slot2_fou();
    void btn_default_Slot3_fou();
    void btn_default_Slot_fif();
    void btn_default_Slot2_fif();
    void btn_default_Slot3_fif();

    /*槽函数*/
    void resetAction();

    void toCBox(int i);
    void toOSD1Slot();
    void toOSD2Slot();
    void toOSD3Slot();
    void toOSD4Slot();
    void toMainTest();//测试跳转

    /*线程*/
    void stop_thread_now();
    void parse_bytearray();
    void RcvData_SerialPort();


private slots:
    void on_btnTrack_clicked();

    void on_btnCapture_clicked();

    void on_btnSersorSwitch_clicked();


    /*系统配置槽函数*/
    void lEdt_sysCfg_Slot();
	void btn_choose_Slot();
    void CBox_sysCfg_Slot(int i);
    void checkBox_channel_Slot();

	/*通道分辨率*/
    void btn_aisle1_Slot();
    void btn_aisle2_Slot();
    void btn_aisle3_Slot();
    void btn_aisle4_Slot();
    void btn_aisle5_Slot();
    void btn_resolution_clicked();
    /*平台控制*/
    void btn_Jos_Default_Slot();
    void btn_Jos_Update_Slot();
    void lEdt_Jos1_Slot();
    void lEdt_Jos2_Slot();
    void lEdt_Jos3_Slot();
    void lEdt_Jos4_Slot();
    void lEdt_Jos5_Slot();
    void lEdt_Jos6_Slot();
    void lEdt_Jos7_Slot();
/*
    void lEdt_PID1_Slot();
    void lEdt_PID2_Slot();
    void lEdt_PID3_Slot();
    void lEdt_PID4_Slot();
    void lEdt_PID5_Slot();
    void lEdt_PID6_Slot();
    void lEdt_PID7_Slot();
    void lEdt_PID8_Slot();
    */

    void lEdt_plat1_Slot();
    void lEdt_plat2_Slot();
    void lEdt_plat3_Slot();
    void lEdt_plat4_Slot();
    void lEdt_plat5_Slot();
    void lEdt_plat6_Slot();
    void lEdt_plat7_Slot();
    void outMode_Slot(int i);

    /*PID1配置*/
       void lEdt_kx_Slot();
       void lEdt_ky_Slot();
       void x_ratio_control_Slot();
       void y_ratio_control_Slot();
       void lEdt_errx_Slot();
       void lEdt_erry_Slot();
       void lEdt_time_Slot();
       void lEdt_PID1_Slot();
       void lEdt_PID2_Slot();
       void lEdt_PID3_Slot();
       void lEdt_PID4_Slot();
       void lEdt_PID5_Slot();
       void lEdt_PID6_Slot();
       void lEdt_PID7_Slot();
       void lEdt_PID8_Slot();
       void btn_pid_Default_Slot();
       void btn_pid_Updata_Slot();

       /*PID2配置*/
       void lEdt_kx_Slot2();
       void lEdt_ky_Slot2();
       void x_ratio_control_Slot2();
       void y_ratio_control_Slot2();
       void lEdt_errx_Slot2();
       void lEdt_erry_Slot2();
       void lEdt_time_Slot2();
       void lEdt_PID1_Slot2();
       void lEdt_PID2_Slot2();
       void lEdt_PID3_Slot2();
       void lEdt_PID4_Slot2();
       void lEdt_PID5_Slot2();
       void lEdt_PID6_Slot2();
       void lEdt_PID7_Slot2();
       void lEdt_PID8_Slot2();
       void btn_pid_Default_Slot2();
       void btn_pid_Updata_Slot2();

       /*PID3配置*/
       void lEdt_kx_Slot3();
       void lEdt_ky_Slot3();
       void x_ratio_control_Slot3();
       void y_ratio_control_Slot3();
       void lEdt_errx_Slot3();
       void lEdt_erry_Slot3();
       void lEdt_time_Slot3();
       void lEdt_PID1_Slot3();
       void lEdt_PID2_Slot3();
       void lEdt_PID3_Slot3();
       void lEdt_PID4_Slot3();
       void lEdt_PID5_Slot3();
       void lEdt_PID6_Slot3();
       void lEdt_PID7_Slot3();
       void lEdt_PID8_Slot3();
       void btn_pid_Default_Slot3();
       void btn_pid_Updata_Slot3();

       /*PID4配置*/
       void lEdt_kx_Slot4();
       void lEdt_ky_Slot4();
       void x_ratio_control_Slot4();
       void y_ratio_control_Slot4();
       void lEdt_errx_Slot4();
       void lEdt_erry_Slot4();
       void lEdt_time_Slot4();
       void lEdt_PID1_Slot4();
       void lEdt_PID2_Slot4();
       void lEdt_PID3_Slot4();
       void lEdt_PID4_Slot4();
       void lEdt_PID5_Slot4();
       void lEdt_PID6_Slot4();
       void lEdt_PID7_Slot4();
       void lEdt_PID8_Slot4();
       void btn_pid_Default_Slot4();
       void btn_pid_Updata_Slot4();
       /*PID5配置*/
       void lEdt_kx_Slot5();
       void lEdt_ky_Slot5();
       void x_ratio_control_Slot5();
       void y_ratio_control_Slot5();
       void lEdt_errx_Slot5();
       void lEdt_erry_Slot5();
       void lEdt_time_Slot5();
       void lEdt_PID1_Slot5();
       void lEdt_PID2_Slot5();
       void lEdt_PID3_Slot5();
       void lEdt_PID4_Slot5();
       void lEdt_PID5_Slot5();
       void lEdt_PID6_Slot5();
       void lEdt_PID7_Slot5();
       void lEdt_PID8_Slot5();
       void btn_pid_Default_Slot5();
       void btn_pid_Updata_Slot5();

    /*捕获配置配置*/
       /*
    void lEdt_kx_Slot();
    void lEdt_ky_Slot();
    void lEdt_errx_Slot();
    void lEdt_erry_Slot();
    void lEdt_time_Slot();
    */
    void lEdt_dbg5_Slot();
    void lEdt_dbg6_Slot();
    void lEdt_dbg7_Slot();
    void lEdt_dbg8_Slot();
    void lEdt_dbg9_Slot();
    void lEdt_dbg10_Slot();
    void lEdt_dbg11_Slot();
    void lEdt_dbg12_Slot();
    void lEdt_dbg13_Slot();
    void lEdt_dbg14_Slot();
    void lEdt_dbg15_Slot();

    /*转台配置通道1*/
    void lEdt_speedx1_Slot();
    void lEdt_speedx2_Slot();
    void lEdt_speedx3_Slot();
    void lEdt_speedx4_Slot();
    void lEdt_speedx5_Slot();
    void lEdt_speedx6_Slot();
    void lEdt_speedx7_Slot();
    void lEdt_speedx8_Slot();
    void lEdt_speedx9_Slot();
    void lEdt_speedx10_Slot();
    void lEdt_speedy1_Slot();
    void lEdt_speedy2_Slot();
    void lEdt_speedy3_Slot();
    void lEdt_speedy4_Slot();
    void lEdt_speedy5_Slot();
    void lEdt_speedy6_Slot();
    void lEdt_speedy7_Slot();
    void lEdt_speedy8_Slot();
    void lEdt_speedy9_Slot();
    void lEdt_speedy10_Slot();
    void btn_Speed_Default_Slot();
    void btn_Speed_Update_Slot();

    void lEdt_maxspeedx_Slot();
    void lEdt_maxspeedy_Slot();
    void lEdt_deadx_Slot();
    void lEdt_deady_Slot();
    void lEdt_out_address_Slot();
    void combox_output_d_type_Slot(int index);
    void combox_baud_rate_type_Slot(int index);
    void combox_data_bit_type_Slot(int index);
    void combox_stop_bit_type_Slot(int index);
    void combox_parity_bit_type_Slot(int index);
    void combox_flow_control_type_Slot(int index);

     /*转台配置通道2*/
    void lEdt_speedx1_Slot_sec();
    void lEdt_speedx2_Slot_sec();
    void lEdt_speedx3_Slot_sec();
    void lEdt_speedx4_Slot_sec();
    void lEdt_speedx5_Slot_sec();
    void lEdt_speedx6_Slot_sec();
    void lEdt_speedx7_Slot_sec();
    void lEdt_speedx8_Slot_sec();
    void lEdt_speedx9_Slot_sec();
    void lEdt_speedx10_Slot_sec();
    void lEdt_speedy1_Slot_sec();
    void lEdt_speedy2_Slot_sec();
    void lEdt_speedy3_Slot_sec();
    void lEdt_speedy4_Slot_sec();
    void lEdt_speedy5_Slot_sec();
    void lEdt_speedy6_Slot_sec();
    void lEdt_speedy7_Slot_sec();
    void lEdt_speedy8_Slot_sec();
    void lEdt_speedy9_Slot_sec();
    void lEdt_speedy10_Slot_sec();
    void btn_Speed_Default_Slot_sec();
    void btn_Speed_Update_Slot_sec();

    void lEdt_maxspeedx_Slot_sec();
    void lEdt_maxspeedy_Slot_sec();
    void lEdt_deadx_Slot_sec();
    void lEdt_deady_Slot_sec();

    void lEdt_out_address_Slot_sec();
    void combox_output_d_type_Slot_sec(int index);
    void combox_baud_rate_type_Slot_sec(int index);
    void combox_data_bit_type_Slot_sec(int index);
    void combox_stop_bit_type_Slot_sec(int index);
    void combox_parity_bit_type_Slot_sec(int index);
    void combox_flow_control_type_Slot_sec(int index);

     /*转台配置通道3*/
    void lEdt_speedx1_Slot_thi();
    void lEdt_speedx2_Slot_thi();
    void lEdt_speedx3_Slot_thi();
    void lEdt_speedx4_Slot_thi();
    void lEdt_speedx5_Slot_thi();
    void lEdt_speedx6_Slot_thi();
    void lEdt_speedx7_Slot_thi();
    void lEdt_speedx8_Slot_thi();
    void lEdt_speedx9_Slot_thi();
    void lEdt_speedx10_Slot_thi();
    void lEdt_speedy1_Slot_thi();
    void lEdt_speedy2_Slot_thi();
    void lEdt_speedy3_Slot_thi();
    void lEdt_speedy4_Slot_thi();
    void lEdt_speedy5_Slot_thi();
    void lEdt_speedy6_Slot_thi();
    void lEdt_speedy7_Slot_thi();
    void lEdt_speedy8_Slot_thi();
    void lEdt_speedy9_Slot_thi();
    void lEdt_speedy10_Slot_thi();
    void btn_Speed_Default_Slot_thi();
    void btn_Speed_Update_Slot_thi();

    void lEdt_maxspeedx_Slot_thi();
    void lEdt_maxspeedy_Slot_thi();
    void lEdt_deadx_Slot_thi();
    void lEdt_deady_Slot_thi();

    void lEdt_out_address_Slot_thi();
    void combox_output_d_type_Slot_thi(int index);
    void combox_baud_rate_type_Slot_thi(int index);
    void combox_data_bit_type_Slot_thi(int index);
    void combox_stop_bit_type_Slot_thi(int index);
    void combox_parity_bit_type_Slot_thi(int index);
    void combox_flow_control_type_Slot_thi(int index);


     /*转台配置通道4*/
    void lEdt_speedx1_Slot_fou();
    void lEdt_speedx2_Slot_fou();
    void lEdt_speedx3_Slot_fou();
    void lEdt_speedx4_Slot_fou();
    void lEdt_speedx5_Slot_fou();
    void lEdt_speedx6_Slot_fou();
    void lEdt_speedx7_Slot_fou();
    void lEdt_speedx8_Slot_fou();
    void lEdt_speedx9_Slot_fou();
    void lEdt_speedx10_Slot_fou();
    void lEdt_speedy1_Slot_fou();
    void lEdt_speedy2_Slot_fou();
    void lEdt_speedy3_Slot_fou();
    void lEdt_speedy4_Slot_fou();
    void lEdt_speedy5_Slot_fou();
    void lEdt_speedy6_Slot_fou();
    void lEdt_speedy7_Slot_fou();
    void lEdt_speedy8_Slot_fou();
    void lEdt_speedy9_Slot_fou();
    void lEdt_speedy10_Slot_fou();
    void btn_Speed_Default_Slot_fou();
    void btn_Speed_Update_Slot_fou();

    void lEdt_maxspeedx_Slot_fou();
    void lEdt_maxspeedy_Slot_fou();
    void lEdt_deadx_Slot_fou();
    void lEdt_deady_Slot_fou();

    void lEdt_out_address_Slot_fou();
    void combox_output_d_type_Slot_fou(int index);
    void combox_baud_rate_type_Slot_fou(int index);
    void combox_data_bit_type_Slot_fou(int index);
    void combox_stop_bit_type_Slot_fou(int index);
    void combox_parity_bit_type_Slot_fou(int index);
    void combox_flow_control_type_Slot_fou(int index);

     /*转台配置通道5*/
    void lEdt_speedx1_Slot_fif();
    void lEdt_speedx2_Slot_fif();
    void lEdt_speedx3_Slot_fif();
    void lEdt_speedx4_Slot_fif();
    void lEdt_speedx5_Slot_fif();
    void lEdt_speedx6_Slot_fif();
    void lEdt_speedx7_Slot_fif();
    void lEdt_speedx8_Slot_fif();
    void lEdt_speedx9_Slot_fif();
    void lEdt_speedx10_Slot_fif();
    void lEdt_speedy1_Slot_fif();
    void lEdt_speedy2_Slot_fif();
    void lEdt_speedy3_Slot_fif();
    void lEdt_speedy4_Slot_fif();
    void lEdt_speedy5_Slot_fif();
    void lEdt_speedy6_Slot_fif();
    void lEdt_speedy7_Slot_fif();
    void lEdt_speedy8_Slot_fif();
    void lEdt_speedy9_Slot_fif();
    void lEdt_speedy10_Slot_fif();
    void btn_Speed_Default_Slot_fif();
    void btn_Speed_Update_Slot_fif();

    void lEdt_maxspeedx_Slot_fif();
    void lEdt_maxspeedy_Slot_fif();
    void lEdt_deadx_Slot_fif();
    void lEdt_deady_Slot_fif();

    void lEdt_out_address_Slot_fif();
    void combox_output_d_type_Slot_fif(int index);
    void combox_baud_rate_type_Slot_fif(int index);
    void combox_data_bit_type_Slot_fif(int index);
    void combox_stop_bit_type_Slot_fif(int index);
    void combox_parity_bit_type_Slot_fif(int index);
    void combox_flow_control_type_Slot_fif(int index);


    //摄像机通道一
    //固定视场
    void btn_vediosersor_fix_default_Slot();
    void btn_vediosersor_fix_update_Slot();
    void fixChanelNum_Slot();
    void fixchanel_enable_Slot();
    void fix_vediohaveornot_Slot();
    void fix_vedio_dpi_Slot(int index);
    void fix_gateshow_Slot();
    void fix_bullshow_Slot();
    void fix_autogate_Slot();
    void fix_gate_sizex_Slot();
    void fix_gate_sizey_Slot();
    void fix_gatelocationx_Slot();
    void fix_gatelocationy_Slot();
    void set_azimuth_Slot();
    void set_pitch_Slot();
    void set_zoom_Slot();
    void search_azimuth_Slot();
    void search_pitch_Slot();
    void search_zoom_Slot();
    void fix_lEdt_Slot();
    void fix_vertical_Slot();
    void fix_sp_Slot();
    void fix_sp2_Slot();


    //可切换视场
    void btn_vediosersor_default_Slot();
    void change_ChanelNum_Slot();
    void change_chanel_enable_Slot();
    void change_vediohaveornot_Slot();
    void change_gateshow_Slot();
    void change_bullshow_Slot();
    void change_autogate_Slot();
    void vedio_fovclass_Slot(int i);
    void vedio_s1_Fov0_Slot();
    void vedio_s1_Fov1_Slot();
    void vedio_s1_Fov2_Slot();
    void vedio_s1_Fov3_Slot();
    void vedio_s1_Fov4_Slot();
    void Change_vertical1_Slot();
    void Change_vertical2_Slot();
    void Change_vertical3_Slot();
    void Change_vertical4_Slot();
    void Change_vertical5_Slot();
    void vedio_spbx_switch1_Slot();
    void vedio_spbx_switch2_Slot();
    void vedio_spbx_switch3_Slot();
    void vedio_spbx_switch4_Slot();
    void vedio_spbx_switch5_Slot();
    void vedio_spby_switch1_Slot();
    void vedio_spby_switch2_Slot();
    void vedio_spby_switch3_Slot();
    void vedio_spby_switch4_Slot();
    void vedio_spby_switch5_Slot();
    void gatelocationx_Slot();
    void gatelocationy_Slot();
    void gate_sizex_Slot();
    void gate_sizey_Slot();
    void change_set_azimuth_Slot();
    void change_set_pitch_Slot();
    void change_set_zoom_Slot();

    //连续视场
    void btn_vediosersor_continue_default_Slot();
    void continue_ChanelNum_Slot();
    void continue_chanel_enable_Slot();
    void continue_vediohaveornot_Slot();
    void continue_gateshow_Slot();
    void continue_bullshow_Slot();
    void continue_autogate_Slot();
    void continue_gate_sizex_Slot();
    void continue_gate_sizey_Slot();
    void continue_gatelocationx_Slot();
    void continue_gatelocationy_Slot();
    void continue_set_azimuth_Slot();
    void continue_set_pitch_Slot();
    void continue_set_zoom_Slot();

    void test_1_Slot();
    void vedio_l1_continue_Slot();
    void vedio_l2_continue_Slot();
    void vedio_l3_continue_Slot();
    void vedio_l4_continue_Slot();
    void vedio_l5_continue_Slot();
    void vedio_l6_continue_Slot();
    void vedio_l7_continue_Slot();
    void vedio_continue_Fov0_Slot();
    void vedio_continue_Fov1_Slot();
    void vedio_continue_Fov2_Slot();
    void vedio_continue_Fov3_Slot();
    void vedio_continue_Fov4_Slot();
    void vedio_continue_Fov5_Slot();
    void vedio_continue_Fov6_Slot();
    void vedio_continue_Fov7_Slot();
    void continue_vertical1_Slot();
    void continue_vertical2_Slot();
    void continue_vertical3_Slot();
    void continue_vertical4_Slot();
    void continue_vertical5_Slot();
    void continue_vertical6_Slot();
    void continue_vertical7_Slot();
    void vedio_spbx_continue1_Slot();
    void vedio_spbx_continue2_Slot();
    void vedio_spbx_continue3_Slot();
    void vedio_spbx_continue4_Slot();
    void vedio_spbx_continue5_Slot();
    void vedio_spbx_continue6_Slot();
    void vedio_spbx_continue7_Slot();

    void vedio_spby_continue1_Slot();
    void vedio_spby_continue2_Slot();
    void vedio_spby_continue3_Slot();
    void vedio_spby_continue4_Slot();
    void vedio_spby_continue5_Slot();
    void vedio_spby_continue6_Slot();
    void vedio_spby_continue7_Slot();



    //摄像机通道二
    void btn_vediosersor_fix_default_Slot_sec();
    void fixChanelNum_Slot_sec();
    void fixchanelname_Slot_sec();
    void fix_vediohaveornot_Slot_sec();
    void fix_vedio_dpi_Slot_sec(int index);
    void fix_gateshow_Slot_sec();
    void fix_bullshow_Slot_sec();
    void fix_autogate_Slot_sec();
    void fix_gate_sizex_Slot_sec();
    void fix_gate_sizey_Slot_sec();
    void fix_gatelocationx_Slot_sec();
    void fix_gatelocationy_Slot_sec();
    void set_azimuth_Slot_sec();
    void set_pitch_Slot_sec();
    void set_zoom_Slot_sec();
    void fix_lEdt_Slot_sec();
    void fix_vertical_Slot_sec();
    void fix_sp_Slot_sec();
    void fix_sp2_Slot_sec();


    //可切换视场
    void btn_vediosersor_default_Slot_sec();
    void change_ChanelNum_Slot_sec();
    void change_chanelname_Slot_sec();
    void change_vediohaveornot_Slot_sec();
    void change_gateshow_Slot_sec();
    void change_bullshow_Slot_sec();
    void change_autogate_Slot_sec();
    void vedio_fovclass_Slot_sec(int i);
    void vedio_s1_Fov0_Slot_sec();
    void vedio_s1_Fov1_Slot_sec();
    void vedio_s1_Fov2_Slot_sec();
    void vedio_s1_Fov3_Slot_sec();
    void vedio_s1_Fov4_Slot_sec();
    void Change_vertical1_Slot_sec();
    void Change_vertical2_Slot_sec();
    void Change_vertical3_Slot_sec();
    void Change_vertical4_Slot_sec();
    void Change_vertical5_Slot_sec();
    void vedio_spbx_switch1_Slot_sec();
    void vedio_spbx_switch2_Slot_sec();
    void vedio_spbx_switch3_Slot_sec();
    void vedio_spbx_switch4_Slot_sec();
    void vedio_spbx_switch5_Slot_sec();
    void vedio_spby_switch1_Slot_sec();
    void vedio_spby_switch2_Slot_sec();
    void vedio_spby_switch3_Slot_sec();
    void vedio_spby_switch4_Slot_sec();
    void vedio_spby_switch5_Slot_sec();
    void fix_gate_sizex_change_Slot_sec();
    void fix_gate_sizey_change_Slot_sec();
    void fix_gatelocationx_change_Slot_sec();
    void fix_gatelocationy_change_Slot_sec();
    void set_azimuth_change_Slot_sec();
    void set_pitch_change_Slot_sec();
    void set_zoom_change_Slot_sec();


    //连续视场
    void btn_vediosersor_continue_default_Slot_sec();
    void continue_ChanelNum_Slot_sec();
    void continue_chanelname_Slot_sec();
    void continue_vediohaveornot_Slot_sec();
    void continue_gateshow_Slot_sec();
    void continue_bullshow_Slot_sec();
    void continue_autogate_Slot_sec();
    void continue_gate_sizex_Slot_sec();
    void continue_gate_sizey_Slot_sec();
    void continue_gatelocationx_Slot_sec();
    void continue_gatelocationy_Slot_sec();
    void continue_set_azimuth_Slot_sec();
    void continue_set_pitch_Slot_sec();
    void continue_set_zoom_Slot_sec();

    void test_1_Slot_sec();
    void vedio_l1_continue_Slot_sec();
    void vedio_l2_continue_Slot_sec();
    void vedio_l3_continue_Slot_sec();
    void vedio_l4_continue_Slot_sec();
    void vedio_l5_continue_Slot_sec();
    void vedio_l6_continue_Slot_sec();
    void vedio_l7_continue_Slot_sec();
    void vedio_continue_Fov0_Slot_sec();
    void vedio_continue_Fov1_Slot_sec();
    void vedio_continue_Fov2_Slot_sec();
    void vedio_continue_Fov3_Slot_sec();
    void vedio_continue_Fov4_Slot_sec();
    void vedio_continue_Fov5_Slot_sec();
    void vedio_continue_Fov6_Slot_sec();
    void continue_vertical1_Slot_sec();
    void continue_vertical2_Slot_sec();
    void continue_vertical3_Slot_sec();
    void continue_vertical4_Slot_sec();
    void continue_vertical5_Slot_sec();
    void continue_vertical6_Slot_sec();
    void continue_vertical7_Slot_sec();
    void vedio_spbx_continue1_Slot_sec();
    void vedio_spbx_continue2_Slot_sec();
    void vedio_spbx_continue3_Slot_sec();
    void vedio_spbx_continue4_Slot_sec();
    void vedio_spbx_continue5_Slot_sec();
    void vedio_spbx_continue6_Slot_sec();
    void vedio_spbx_continue7_Slot_sec();

    void vedio_spby_continue1_Slot_sec();
    void vedio_spby_continue2_Slot_sec();
    void vedio_spby_continue3_Slot_sec();
    void vedio_spby_continue4_Slot_sec();
    void vedio_spby_continue5_Slot_sec();
    void vedio_spby_continue6_Slot_sec();
    void vedio_spby_continue7_Slot_sec();


    //摄像机通道三
    void btn_vediosersor_fix_default_Slot_thi();
    void fixChanelNum_Slot_thi();
    void fixchanelname_Slot_thi();
    void fix_vediohaveornot_Slot_thi();
    void fix_vedio_dpi_Slot_thi(int index);
    void fix_gateshow_Slot_thi();
    void fix_bullshow_Slot_thi();
    void fix_autogate_Slot_thi();
    void fix_gate_sizex_Slot_thi();
    void fix_gate_sizey_Slot_thi();
    void fix_gatelocationx_Slot_thi();
    void fix_gatelocationy_Slot_thi();
    void set_azimuth_Slot_thi();
    void set_pitch_Slot_thi();
    void set_zoom_Slot_thi();
    void fix_lEdt_Slot_thi();
    void fix_vertical_Slot_thi();
    void fix_sp_Slot_thi();
    void fix_sp2_Slot_thi();


    //可切换视场
    void btn_vediosersor_default_Slot_thi();
    void change_ChanelNum_Slot_thi();
    void change_chanelname_Slot_thi();
    void change_vediohaveornot_Slot_thi();
    void change_gateshow_Slot_thi();
    void change_bullshow_Slot_thi();
    void change_autogate_Slot_thi();
    void change_fix_gate_sizex_Slot_thi();
    void change_fix_gate_sizey_Slot_thi();
    void change_fix_gatelocationx_Slot_thi();
    void change_fix_gatelocationy_Slot_thi();
    void change_set_azimuth_Slot_thi();
    void change_set_pitch_Slot_thi();
    void change_set_zoom_Slot_thi();
    void vedio_fovclass_Slot_thi(int i);
    void vedio_s1_Fov0_Slot_thi();
    void vedio_s1_Fov1_Slot_thi();
    void vedio_s1_Fov2_Slot_thi();
    void vedio_s1_Fov3_Slot_thi();
    void vedio_s1_Fov4_Slot_thi();
    void Change_vertical1_Slot_thi();
    void Change_vertical2_Slot_thi();
    void Change_vertical3_Slot_thi();
    void Change_vertical4_Slot_thi();
    void Change_vertical5_Slot_thi();
    void vedio_spbx_switch1_Slot_thi();
    void vedio_spbx_switch2_Slot_thi();
    void vedio_spbx_switch3_Slot_thi();
    void vedio_spbx_switch4_Slot_thi();
    void vedio_spbx_switch5_Slot_thi();
    void vedio_spby_switch1_Slot_thi();
    void vedio_spby_switch2_Slot_thi();
    void vedio_spby_switch3_Slot_thi();
    void vedio_spby_switch4_Slot_thi();
    void vedio_spby_switch5_Slot_thi();

    //连续视场
    void btn_vediosersor_continue_default_Slot_thi();
    void continue_ChanelNum_Slot_thi();
    void continue_chanelname_Slot_thi();
    void continue_vediohaveornot_Slot_thi();
    void continue_gateshow_Slot_thi();
    void continue_bullshow_Slot_thi();
    void continue_autogate_Slot_thi();
    void continue_fix_gate_sizex_Slot_thi();
    void continue_fix_gate_sizey_Slot_thi();
    void continue_fix_gatelocationx_Slot_thi();
    void continue_fix_gatelocationy_Slot_thi();
    void continue_set_azimuth_Slot_thi();
    void continue_set_pitch_Slot_thi();
    void continue_set_zoom_Slot_thi();
    void test_1_Slot_thi();
    void vedio_l1_continue_Slot_thi();
    void vedio_l2_continue_Slot_thi();
    void vedio_l3_continue_Slot_thi();
    void vedio_l4_continue_Slot_thi();
    void vedio_l5_continue_Slot_thi();
    void vedio_l6_continue_Slot_thi();
    void vedio_l7_continue_Slot_thi();
    void vedio_continue_Fov0_Slot_thi();
    void vedio_continue_Fov1_Slot_thi();
    void vedio_continue_Fov2_Slot_thi();
    void vedio_continue_Fov3_Slot_thi();
    void vedio_continue_Fov4_Slot_thi();
    void vedio_continue_Fov5_Slot_thi();
    void vedio_continue_Fov6_Slot_thi();
    void continue_vertical1_Slot_thi();
    void continue_vertical2_Slot_thi();
    void continue_vertical3_Slot_thi();
    void continue_vertical4_Slot_thi();
    void continue_vertical5_Slot_thi();
    void continue_vertical6_Slot_thi();
    void continue_vertical7_Slot_thi();
    void vedio_spbx_continue1_Slot_thi();
    void vedio_spbx_continue2_Slot_thi();
    void vedio_spbx_continue3_Slot_thi();
    void vedio_spbx_continue4_Slot_thi();
    void vedio_spbx_continue5_Slot_thi();
    void vedio_spbx_continue6_Slot_thi();
    void vedio_spbx_continue7_Slot_thi();

    void vedio_spby_continue1_Slot_thi();
    void vedio_spby_continue2_Slot_thi();
    void vedio_spby_continue3_Slot_thi();
    void vedio_spby_continue4_Slot_thi();
    void vedio_spby_continue5_Slot_thi();
    void vedio_spby_continue6_Slot_thi();
    void vedio_spby_continue7_Slot_thi();


    //摄像机通道四
    void btn_vediosersor_fix_default_Slot_fou();
    void fixChanelNum_Slot_fou();
    void fixchanelname_Slot_fou();
    void fix_vediohaveornot_Slot_fou();
    void fix_vedio_dpi_Slot_fou(int index);
    void fix_gateshow_Slot_fou();
    void fix_bullshow_Slot_fou();
    void fix_autogate_Slot_fou();
    void fix_gate_sizex_Slot_fou();
    void fix_gate_sizey_Slot_fou();
    void fix_gatelocationx_Slot_fou();
    void fix_gatelocationy_Slot_fou();
    void set_azimuth_Slot_fou();
    void set_pitch_Slot_fou();
    void set_zoom_Slot_fou();
    void fix_lEdt_Slot_fou();
    void fix_vertical_Slot_fou();
    void fix_sp_Slot_fou();
    void fix_sp2_Slot_fou();


    //可切换视场
    void btn_vediosersor_default_Slot_fou();
    void change_ChanelNum_Slot_fou();
    void change_chanelname_Slot_fou();
    void change_vediohaveornot_Slot_fou();
    void change_gateshow_Slot_fou();
    void change_bullshow_Slot_fou();
    void change_autogate_Slot_fou();
    void change_gate_sizex_Slot_fou();
    void change_gate_sizey_Slot_fou();
    void change_gatelocationx_Slot_fou();
    void change_gatelocationy_Slot_fou();
    void change_set_azimuth_Slot_fou();
    void change_set_pitch_Slot_fou();
    void change_set_zoom_Slot_fou();
    void vedio_fovclass_Slot_fou(int i);
    void vedio_s1_Fov0_Slot_fou();
    void vedio_s1_Fov1_Slot_fou();
    void vedio_s1_Fov2_Slot_fou();
    void vedio_s1_Fov3_Slot_fou();
    void vedio_s1_Fov4_Slot_fou();
    void Change_vertical1_Slot_fou();
    void Change_vertical2_Slot_fou();
    void Change_vertical3_Slot_fou();
    void Change_vertical4_Slot_fou();
    void Change_vertical5_Slot_fou();
    void vedio_spbx_switch1_Slot_fou();
    void vedio_spbx_switch2_Slot_fou();
    void vedio_spbx_switch3_Slot_fou();
    void vedio_spbx_switch4_Slot_fou();
    void vedio_spbx_switch5_Slot_fou();
    void vedio_spby_switch1_Slot_fou();
    void vedio_spby_switch2_Slot_fou();
    void vedio_spby_switch3_Slot_fou();
    void vedio_spby_switch4_Slot_fou();
    void vedio_spby_switch5_Slot_fou();

    //连续视场
    void btn_vediosersor_continue_default_Slot_fou();
    void test_1_Slot_fou();
    void continue_ChanelNum_Slot_fou();
    void continue_chanelname_Slot_fou();
    void continue_vediohaveornot_Slot_fou();
    void continue_gateshow_Slot_fou();
    void continue_bullshow_Slot_fou();
    void continue_autogate_Slot_fou();
    void continue_gate_sizex_Slot_fou();
    void continue_gate_sizey_Slot_fou();
    void continue_gatelocationx_Slot_fou();
    void continue_gatelocationy_Slot_fou();
    void continue_set_azimuth_Slot_fou();
    void continue_set_pitch_Slot_fou();
    void continue_set_zoom_Slot_fou();
    void vedio_l1_continue_Slot_fou();
    void vedio_l2_continue_Slot_fou();
    void vedio_l3_continue_Slot_fou();
    void vedio_l4_continue_Slot_fou();
    void vedio_l5_continue_Slot_fou();
    void vedio_l6_continue_Slot_fou();
    void vedio_l7_continue_Slot_fou();
    void vedio_continue_Fov0_Slot_fou();
    void vedio_continue_Fov1_Slot_fou();
    void vedio_continue_Fov2_Slot_fou();
    void vedio_continue_Fov3_Slot_fou();
    void vedio_continue_Fov4_Slot_fou();
    void vedio_continue_Fov5_Slot_fou();
    void vedio_continue_Fov6_Slot_fou();
    void continue_vertical1_Slot_fou();
    void continue_vertical2_Slot_fou();
    void continue_vertical3_Slot_fou();
    void continue_vertical4_Slot_fou();
    void continue_vertical5_Slot_fou();
    void continue_vertical6_Slot_fou();
    void continue_vertical7_Slot_fou();
    void vedio_spbx_continue1_Slot_fou();
    void vedio_spbx_continue2_Slot_fou();
    void vedio_spbx_continue3_Slot_fou();
    void vedio_spbx_continue4_Slot_fou();
    void vedio_spbx_continue5_Slot_fou();
    void vedio_spbx_continue6_Slot_fou();
    void vedio_spbx_continue7_Slot_fou();

    void vedio_spby_continue1_Slot_fou();
    void vedio_spby_continue2_Slot_fou();
    void vedio_spby_continue3_Slot_fou();
    void vedio_spby_continue4_Slot_fou();
    void vedio_spby_continue5_Slot_fou();
    void vedio_spby_continue6_Slot_fou();
    void vedio_spby_continue7_Slot_fou();


    //摄像机通道五
    void btn_vediosersor_fix_default_Slot_fif();
    void fixChanelNum_Slot_fif();
    void fixchanelname_Slot_fif();
    void fix_vediohaveornot_Slot_fif();
    void fix_vedio_dpi_Slot_fif(int index);
    void fix_gateshow_Slot_fif();
    void fix_bullshow_Slot_fif();
    void fix_autogate_Slot_fif();
    void fix_gate_sizex_Slot_fif();
    void fix_gate_sizey_Slot_fif();
    void fix_gatelocationx_Slot_fif();
    void fix_gatelocationy_Slot_fif();
    void set_azimuth_Slot_fif();
    void set_pitch_Slot_fif();
    void set_zoom_Slot_fif();
    void fix_lEdt_Slot_fif();
    void fix_vertical_Slot_fif();
    void fix_sp_Slot_fif();
    void fix_sp2_Slot_fif();


    //可切换视场
    void btn_vediosersor_default_Slot_fif();
    void change_gateshow_Slot_fif();
    void change_bullshow_Slot_fif();
    void change_autogate_Slot_fif();
    void change_gate_sizex_Slot_fif();
    void change_gate_sizey_Slot_fif();
    void change_gatelocationx_Slot_fif();
    void change_gatelocationy_Slot_fif();
    void change_set_azimuth_Slot_fif();
    void change_set_pitch_Slot_fif();
    void change_set_zoom_Slot_fif();
    void vedio_fovclass_Slot_fif(int i);
    void vedio_s1_Fov0_Slot_fif();
    void vedio_s1_Fov1_Slot_fif();
    void vedio_s1_Fov2_Slot_fif();
    void vedio_s1_Fov3_Slot_fif();
    void vedio_s1_Fov4_Slot_fif();
    void Change_vertical1_Slot_fif();
    void Change_vertical2_Slot_fif();
    void Change_vertical3_Slot_fif();
    void Change_vertical4_Slot_fif();
    void Change_vertical5_Slot_fif();
    void vedio_spbx_switch1_Slot_fif();
    void vedio_spbx_switch2_Slot_fif();
    void vedio_spbx_switch3_Slot_fif();
    void vedio_spbx_switch4_Slot_fif();
    void vedio_spbx_switch5_Slot_fif();
    void vedio_spby_switch1_Slot_fif();
    void vedio_spby_switch2_Slot_fif();
    void vedio_spby_switch3_Slot_fif();
    void vedio_spby_switch4_Slot_fif();
    void vedio_spby_switch5_Slot_fif();





    //连续视场
    void btn_vediosersor_continue_default_Slot_fif();
    void continue_ChanelNum_Slot_fif();
    void continue_chanelname_Slot_fif();
    void continue_vediohaveornot_Slot_fif();
    void continue_gateshow_Slot_fif();
    void continue_bullshow_Slot_fif();
    void continue_autogate_Slot_fif();
    void continue_gate_sizex_Slot_fif();
    void continue_gate_sizey_Slot_fif();
    void continue_gatelocationx_Slot_fif();
    void continue_gatelocationy_Slot_fif();
    void continue_set_azimuth_Slot_fif();
    void continue_set_pitch_Slot_fif();
    void continue_set_zoom_Slot_fif();
    void test_1_Slot_fif();
    void vedio_l1_continue_Slot_fif();
    void vedio_l2_continue_Slot_fif();
    void vedio_l3_continue_Slot_fif();
    void vedio_l4_continue_Slot_fif();
    void vedio_l5_continue_Slot_fif();
    void vedio_l6_continue_Slot_fif();
    void vedio_l7_continue_Slot_fif();
    void vedio_continue_Fov0_Slot_fif();
    void vedio_continue_Fov1_Slot_fif();
    void vedio_continue_Fov2_Slot_fif();
    void vedio_continue_Fov3_Slot_fif();
    void vedio_continue_Fov4_Slot_fif();
    void vedio_continue_Fov5_Slot_fif();
    void vedio_continue_Fov6_Slot_fif();
    void continue_vertical1_Slot_fif();
    void continue_vertical2_Slot_fif();
    void continue_vertical3_Slot_fif();
    void continue_vertical4_Slot_fif();
    void continue_vertical5_Slot_fif();
    void continue_vertical6_Slot_fif();
    void continue_vertical7_Slot_fif();
    void vedio_spbx_continue1_Slot_fif();
    void vedio_spbx_continue2_Slot_fif();
    void vedio_spbx_continue3_Slot_fif();
    void vedio_spbx_continue4_Slot_fif();
    void vedio_spbx_continue5_Slot_fif();
    void vedio_spbx_continue6_Slot_fif();
    void vedio_spbx_continue7_Slot_fif();

    void vedio_spby_continue1_Slot_fif();
    void vedio_spby_continue2_Slot_fif();
    void vedio_spby_continue3_Slot_fif();
    void vedio_spby_continue4_Slot_fif();
    void vedio_spby_continue5_Slot_fif();
    void vedio_spby_continue6_Slot_fif();
    void vedio_spby_continue7_Slot_fif();





    /*UTC1参数配置*/
    void btn_utc1_default_Slot();
    void btn_utc1_update_Slot();
    void lEdt_utc1_l0_Slot();
    void lEdt_utc1_l1_Slot();
    void lEdt_utc1_l2_Slot();
    void lEdt_utc1_l3_Slot();
    void lEdt_utc1_l4_Slot();
    void lEdt_utc1_l5_Slot();
    void lEdt_utc1_l6_Slot();
    void lEdt_utc1_l7_Slot();
    void lEdt_utc1_l8_Slot();
    void lEdt_utc1_l9_Slot();
    void lEdt_utc1_l10_Slot();
    void lEdt_utc1_l11_Slot();
    void lEdt_utc1_l12_Slot();
    void lEdt_utc1_l13_Slot();
    void lEdt_utc1_l14_Slot();
    void lEdt_utc1_l15_Slot();

    /*UTC2参数配置*/
    void btn_utc2_default_Slot();
    void btn_utc2_update_Slot();
    void lEdt_utc2_l0_Slot();
    void lEdt_utc2_l1_Slot();
    void lEdt_utc2_l2_Slot();
    void lEdt_utc2_l3_Slot();
    void lEdt_utc2_l4_Slot();
    void lEdt_utc2_l5_Slot();
    void lEdt_utc2_l6_Slot();
    void lEdt_utc2_l7_Slot();
    void lEdt_utc2_l8_Slot();
    void lEdt_utc2_l9_Slot();
    void lEdt_utc2_l10_Slot();
    void lEdt_utc2_l11_Slot();
    void lEdt_utc2_l12_Slot();
    void lEdt_utc2_l13_Slot();
    void lEdt_utc2_l14_Slot();
    void lEdt_utc2_l15_Slot();

    /*UTC3参数配置*/
    void btn_utc3_default_Slot();
    void btn_utc3_update_Slot();
    void lEdt_utc3_l0_Slot();
    void lEdt_utc3_l1_Slot();
    void lEdt_utc3_l2_Slot();
    void lEdt_utc3_l3_Slot();
    void lEdt_utc3_l4_Slot();
    void lEdt_utc3_l5_Slot();
    void lEdt_utc3_l6_Slot();
    void lEdt_utc3_l7_Slot();
    void lEdt_utc3_l8_Slot();
    void lEdt_utc3_l9_Slot();
    void lEdt_utc3_l10_Slot();
    void lEdt_utc3_l11_Slot();
    void lEdt_utc3_l12_Slot();
    void lEdt_utc3_l13_Slot();
    void lEdt_utc3_l14_Slot();
    void lEdt_utc3_l15_Slot();

    /*OSD参数设置*/
    void btn_osd_default_Slot();
    void btn_keep1_Slot();
    void btn_osd_update_Slot();
    void CBox_osd_choose_Slot(int i);
    void checkBox_Slot(int i);
    void lEdt_osd_x_Slot();
    void lEdt_osd_y_Slot();
    void lEdt_osd_context_Slot();
    void CBox_osd_font_Slot(int i);
    void CBox_osd_font_size_Slot(int i);
    //void CBox_View_Slot(int i);
    void CBox_osd_color_Slot(int i);
    void CBox_transparency_Slot();
   // void lEdt_transparency_Slot();

    /*捕获框设置*/
    void checkBox_cross_Slot();
    void lEdt_capture_0();
    void lEdt_capture_1();
    void lEdt_capture_2();
    void lEdt_capture_3();
    void lEdt_capture_4();
    void lEdt_capture_5();
    void lEdt_capture_6();
    void lEdt_capture_7();
    void lEdt_capture_8();
    void lEdt_capture_9();
    void lEdt_capture_10();
    void lEdt_capture_11();
    void callback_autobomen(int arg1);
    void lEdt_bomen_0();
    void lEdt_bomen_1();
    void lEdt_bomen_2();
    void lEdt_bomen_3();
    void lEdt_bomen_4();
    void lEdt_bomen_5();
    void lEdt_bomen_6();
    void lEdt_bomen_7();
    void lEdt_bomen_8();
    void lEdt_bomen_9();
    void lEdt_bomen_10();
    void lEdt_bomen_11();

    //移动检测配置
    void btn_mtd_Default_Slot();
    void btn_mtd_Update_Slot();
    void zone_setting_Slot();
    void lEdt_rigion_Slot();
    void lEdt_rigion_Cen_x_Slot();
    void lEdt_rigion_Cen_y_Slot();
    void lEdt_rigion_Cen_w_Slot();
    void lEdt_rigion_Cen_h_Slot();
    void lEdt_maxnum_Slot();
    void lEdt_uspeed_Slot();
    void lEdt_maxpix_Slot();
    void lEdt_minpix_Slot();
    void lEdt_sensitive_Slot();
    void lEdt_dspeed_Slot();
    void lEdt_trktime_Slot();
    void combox_Priority_judgment_Slot(int index);
    void combox_output_Slot(int index);
    void combox_polar_Slot(int index);
    void lEdt_Alarm_delay_Slot();


    void lEdt_drawLine_1();
    void lEdt_drawLine_2();
    void lEdt_drawLine_3();
    void lEdt_drawLine_4();
    void lEdt_drawLine_5();

    void btn_capture_default_Slot();
    void btn_capture_update_Slot();
    void btn_capture2_default_SLot();
    void btn_capture2_update_Slot();
    void btn_capture3_default_Slot();
    void btn_capture3_update_Slot();

    void on_btn_ok_clicked();

    void on_btnViewPlus_released();

    void on_btnViewMinus_pressed();

    void on_btnViewMinus_released();

    void on_btnForcePlus_pressed();

    void on_btnForceMinus_released();

    void on_btnForcePlus_released();

    void on_btnForceMinus_pressed();

    void on_btnAperturePlus_pressed();

    void on_btnAperturePlus_released();

    void on_btnApertureMinus_pressed();

    void on_btnApertureMinus_released();
    void on_btnViewPlus_pressed();

    void on_btn_up_2_clicked();

    void on_btn_down_2_clicked();

    void on_btn_left_2_clicked();

    void on_btn_right_2_clicked();

    void on_btn_up_pressed();

    void on_btn_up_released();

    void on_btn_right_pressed();

    void on_btn_right_released();

    void on_btn_left_pressed();

    void on_btn_left_released();

    void on_btn_down_pressed();

    void on_btn_down_released();

    void on_comboBox_acqmode_currentIndexChanged(int index);

    void on_radioButton_workmode_clicked(bool checked);

    void on_radioButton_2_workmode_clicked(bool checked);

    void on_radioButton_3_workmode_clicked(bool checked);

    void on_radioButton_acqmode_clicked(bool checked);

    void on_radioButton_2_acqmode_clicked(bool checked);

    void on_radioButton_3_acqmode_clicked(bool checked);

    void on_call_preset_bit_clicked();


private:
    Ui::MainWindow *ui;
    Jos j;
    int value_x=960;
    int value_y=540;
    int value_check=0;
    int value_search=0;



    /*定时器*/
    QTimer *time;
	QTimer *socket_time;

//    QPushButton *blank;
//    QPushButton *btn_sensor_fix;
//    QPushButton *btn_sensor_switch;
//    QPushButton *btn_sersor_continue;

        QLineEdit *lineEdit;
        int sersor_count=0;
    /**/
    QSerialPort * serialPort_command;
    QStackedLayout *btnStack;
    QByteArray sndData_02;
    int connect_flag = 0;
    recSerial *thread_01;
    RcvSocketdata  *thread_socket;
    QByteArray  socketRcvData,RcvData;

    /**/
    //int judgment;//用于判断是否进入跟踪微调，0不进入，1进入
    int jud_area=0;

    QMenu* menu[10];
    /*界面手柄*/
    int a, b;
    int mousePress = 0;
   // QMutex send_mutex;
    unsigned char send_arr[1080];

    /*系统配置*/
    QWidget *w_config,*w_config_serial,*w_config_net;
    MyWidget *w_choose;
    QStackedLayout *s;
    QComboBox *box_serial,*box_baud,*box_check,*box_data,*box_stop;
    QGroupBox *groupBox_trackboard;
    QPushButton *btn_serial_NO,*btn_serial_OK,*btn_net_OK,*btn_net_NO;
    QLineEdit *lineEdit_port,*lineEdit_ip;
    QCheckBox *checkBox_channel1,*checkBox_channel2,*checkBox_channel3,*checkBox_channel4,*checkBox_channel5;
    //QComboBox *box1;
    QButtonGroup *BG1,*BG2,*BG3,*BG4,*BG5;
    QButtonGroup *BO1,*BO2,*BO3,*BO4,*BO5;
    QRadioButton *rdBtn_aisle1_1,*rdBtn_aisle1_2,*rdBtn_aisle1_3,*rdBtn_aisle1_4,*rdBtn_aisle2_1,*rdBtn_aisle2_2,*rdBtn_aisle2_3,*rdBtn_aisle2_4,*rdBtn_aisle3_1,*rdBtn_aisle3_2,*rdBtn_aisle3_3,*rdBtn_aisle3_4,*rdBtn_aisle4_1,*rdBtn_aisle4_2,*rdBtn_aisle4_3,*rdBtn_aisle4_4,*rdBtn_aisle5_1;
    QRadioButton *rdBtn_out1_1,*rdBtn_out1_2,*rdBtn_out2_1,*rdBtn_out2_2,*rdBtn_out3_1,*rdBtn_out3_2,*rdBtn_out4_1,*rdBtn_out4_2,*rdBtn_out5_1;
    QString filePath_updatesw;
    QLineEdit *editsw;
    /*平台配置*/
    MyWidget *w_plat;
      QGroupBox *gbox_Jos,*gbox_plat;
      QLineEdit *josDead_lineEdt,*josPoint_lineEdt,*josInputG_x,*josInputG_y,*josPoint_lineEdt2,*josInputG_x2,*josInputG_y2,
                *josOutputG_x,*josOutputG_y;
      QComboBox *outMode;
      //QLineEdit *kp1_pid,*ki1_pid,*kd1_pid,*k1,*kp2_pid,*ki2_pid,*kd2_pid,*k2;
      QLineEdit *bleedx_plat,*bleedy_plat,*mx_plat,*my_plat,*deadx_plat,*deady_plat,*a_plat;
       QString string_outMode[7]={"Zero","JoystickInput","ShapedAndGained","ShapedAndGainedAndIntegrated","DeterminedByPostion","ZeroInitFilter","DeterminedByIncomingPlatformData"};
      QString jos_s[9]={"手柄死区","手柄拐点1","手柄x轴输入增益1","手柄y轴输入增益1","手柄拐点2","手柄x轴输入增益2","手柄y轴输入增益2","摇杆平台x输出增益","摇杆平台y轴输出增益"};
     // QString pid_s[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
      QString plat_s[8]={"x轴最大速度","y轴最大速度","x轴最大速度","y轴最大速度","x轴死区","y轴死区","惯性跟踪时间","平台输出模式"};

      /*pid配置 通道1*/
          MyWidget *w_pid,*w_pid3,*w_pid4,*w_pid5;
          MyWidget *w_pid2;
          QGroupBox *gbox_PID,*regulator_pid;
          QPushButton *btn_pid_default,*btn_pid_update;
          QLineEdit *kp1_pid,*ki1_pid,*kd1_pid,*k1,*kp2_pid,*ki2_pid,*kd2_pid,*k2;
          QLineEdit *kx_lineEdt,*ky_lineEdt,*errx_lineEdt,*erry_lineEdt,*time_lineEdt,*x_ratio_control,*y_ratio_control;
          QString pid_s[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
          QString dbg_s1[7]={"x轴比例调节系数","y轴比例调节系数","x轴比例调节限幅","y轴比例调节限幅","x轴进PID偏差","y轴进PID偏差","进PID时间"};
          int current_1 = 0;
          /*pid配置 通道2*/
          QGroupBox *gbox_PID2,*regulator_pid2;
          QPushButton *btn_pid_default2,*btn_pid_update2;
          QLineEdit *kp1_pid2,*ki1_pid2,*kd1_pid2,*k12,*kp2_pid2,*ki2_pid2,*kd2_pid2,*k22;
          QLineEdit *kx_lineEdt2,*ky_lineEdt2,*errx_lineEdt2,*erry_lineEdt2,*time_lineEdt2,*x_ratio_control2,*y_ratio_control2;
          QString pid_s2[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
          QString dbg_s2[7]={"x轴比例调节系数","y轴比例调节系数","x轴比例调节限幅","y轴比例调节限幅","x轴进PID偏差","y轴进PID偏差","进PID时间"};

          /*pid配置 通道3*/
          QGroupBox *gbox_PID3,*regulator_pid3;
          QPushButton *btn_pid_default3,*btn_pid_update3;
          QLineEdit *kp1_pid3,*ki1_pid3,*kd1_pid3,*k13,*kp2_pid3,*ki2_pid3,*kd2_pid3,*k23;
          QLineEdit *kx_lineEdt3,*ky_lineEdt3,*errx_lineEdt3,*erry_lineEdt3,*time_lineEdt3,*x_ratio_control3,*y_ratio_control3;
          QString pid_s3[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
          QString dbg_s3[7]={"x轴比例调节系数","y轴比例调节系数","x轴比例调节限幅","y轴比例调节限幅","x轴进PID偏差","y轴进PID偏差","进PID时间"};

          /*pid配置 通道4*/
          QGroupBox *gbox_PID4,*regulator_pid4;
          QPushButton *btn_pid_default4,*btn_pid_update4;
          QLineEdit *kp1_pid4,*ki1_pid4,*kd1_pid4,*k14,*kp2_pid4,*ki2_pid4,*kd2_pid4,*k24;
          QLineEdit *kx_lineEdt4,*ky_lineEdt4,*errx_lineEdt4,*erry_lineEdt4,*time_lineEdt4,*x_ratio_control4,*y_ratio_control4;
          QString pid_s4[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
          QString dbg_s4[7]={"x轴比例调节系数","y轴比例调节系数","x轴比例调节限幅","y轴比例调节限幅","x轴进PID偏差","y轴进PID偏差","进PID时间"};

          /*pid配置 通道5*/
          QGroupBox *gbox_PID5,*regulator_pid5;
          QPushButton *btn_pid_default5,*btn_pid_update5;
          QLineEdit *kp1_pid5,*ki1_pid5,*kd1_pid5,*k15,*kp2_pid5,*ki2_pid5,*kd2_pid5,*k25;
          QLineEdit *kx_lineEdt5,*ky_lineEdt5,*errx_lineEdt5,*erry_lineEdt5,*time_lineEdt5,*x_ratio_control5,*y_ratio_control5;
          QString pid_s5[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
          QString dbg_s5[7]={"x轴比例调节系数","y轴比例调节系数","x轴比例调节限幅","y轴比例调节限幅","x轴进PID偏差","y轴进PID偏差","进PID时间"};

    /*捕获配置*/
    MyWidget *w_dbg;
    QLineEdit *dbg5_lineEdt,*dbg6_lineEdt,*dbg7_lineEdt,*dbg8_lineEdt,*dbg9_lineEdt,*dbg10_lineEdt,
    *dbg11_lineEdt,*dbg12_lineEdt,*dbg13_lineEdt,*dbg14_lineEdt,*dbg15_lineEdt;
    QString dbg_s[16]={"x轴比例调节系数","y轴比例调节系数","x轴进PID偏差","y轴进PID偏差","进PID时间","debug5","debug6","debug7","debug8","debug9","debug10","debug11","debug12","debug13","debug14","debug15"};

    /*转台配置通道一*/
    MyWidget *w_speedconv;
    QGroupBox *gbox_speedx,*gbox_speedy;
    QLineEdit *speedx1_lineEdt,*speedx2_lineEdt,*speedx3_lineEdt,*speedx4_lineEdt,*speedx5_lineEdt,*speedx6_lineEdt,*speedx7_lineEdt,*speedx8_lineEdt,*speedx9_lineEdt,*speedx10_lineEdt;
    QLineEdit *speedy1_lineEdt,*speedy2_lineEdt,*speedy3_lineEdt,*speedy4_lineEdt,*speedy5_lineEdt,*speedy6_lineEdt,*speedy7_lineEdt,*speedy8_lineEdt,*speedy9_lineEdt,*speedy10_lineEdt;
    QLineEdit *maxspeedx,*maxspeedy,*deadx,*deady,*out_address;
    QComboBox *output_d_type,*baud_rate,* data_bit,*stop_bit,*parity_bit,*flow_control;
    QString speed_s[10]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9","等级10"};
    QString speed_q[13]={"x轴最大速度","y轴最大速度","x方向死区","y方向死区","输出偏差类型设置","地址","波特率","数据位","停止位","校验位","流控制","平台x轴Bleed速率","平台y轴Bleed速率"};

    /*转台配置通道二*/
    MyWidget *w_speedconv_sec;
    QGroupBox *gbox_speedx_sec,*gbox_speedy_sec;
    QLineEdit *speedx1_lineEdt_sec,*speedx2_lineEdt_sec,*speedx3_lineEdt_sec,*speedx4_lineEdt_sec,*speedx5_lineEdt_sec,*speedx6_lineEdt_sec,*speedx7_lineEdt_sec,*speedx8_lineEdt_sec,*speedx9_lineEdt_sec,*speedx10_lineEdt_sec;
    QLineEdit *speedy1_lineEdt_sec,*speedy2_lineEdt_sec,*speedy3_lineEdt_sec,*speedy4_lineEdt_sec,*speedy5_lineEdt_sec,*speedy6_lineEdt_sec,*speedy7_lineEdt_sec,*speedy8_lineEdt_sec,*speedy9_lineEdt_sec,*speedy10_lineEdt_sec;
    QLineEdit *maxspeedx_sec,*maxspeedy_sec,*deadx_sec,*deady_sec,*out_address_sec;
    QComboBox *output_d_type_sec,*baud_rate_sec,* data_bit_sec,*stop_bit_sec,*parity_bit_sec,*flow_control_sec;
    QString speed_s_sec[10]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9","等级10"};
    QString speed_q_sec[13]={"x轴最大速度","y轴最大速度","x方向死区","y方向死区","输出偏差类型设置","地址","波特率","数据位","停止位","校验位","流控制","平台x轴Bleed速率","平台y轴Bleed速率"};

    /*转台配置通道三*/
    MyWidget *w_speedconv_thi;
    QGroupBox *gbox_speedx_thi,*gbox_speedy_thi;
    QLineEdit *speedx1_lineEdt_thi,*speedx2_lineEdt_thi,*speedx3_lineEdt_thi,*speedx4_lineEdt_thi,*speedx5_lineEdt_thi,*speedx6_lineEdt_thi,*speedx7_lineEdt_thi,*speedx8_lineEdt_thi,*speedx9_lineEdt_thi,*speedx10_lineEdt_thi;
    QLineEdit *speedy1_lineEdt_thi,*speedy2_lineEdt_thi,*speedy3_lineEdt_thi,*speedy4_lineEdt_thi,*speedy5_lineEdt_thi,*speedy6_lineEdt_thi,*speedy7_lineEdt_thi,*speedy8_lineEdt_thi,*speedy9_lineEdt_thi,*speedy10_lineEdt_thi;
    QLineEdit *maxspeedx_thi,*maxspeedy_thi,*deadx_thi,*deady_thi,*out_address_thi;
    QComboBox *output_d_type_thi,*baud_rate_thi,* data_bit_thi,*stop_bit_thi,*parity_bit_thi,*flow_control_thi;
    QString speed_s_thi[10]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9","等级10"};
    QString speed_q_thi[13]={"x轴最大速度","y轴最大速度","x方向死区","y方向死区","输出偏差类型设置","地址","波特率","数据位","停止位","校验位","流控制","平台x轴Bleed速率","平台y轴Bleed速率"};

    /*转台配置通道四*/
    MyWidget *w_speedconv_fou;
    QGroupBox *gbox_speedx_fou,*gbox_speedy_fou;
    QLineEdit *speedx1_lineEdt_fou,*speedx2_lineEdt_fou,*speedx3_lineEdt_fou,*speedx4_lineEdt_fou,*speedx5_lineEdt_fou,*speedx6_lineEdt_fou,*speedx7_lineEdt_fou,*speedx8_lineEdt_fou,*speedx9_lineEdt_fou,*speedx10_lineEdt_fou;
    QLineEdit *speedy1_lineEdt_fou,*speedy2_lineEdt_fou,*speedy3_lineEdt_fou,*speedy4_lineEdt_fou,*speedy5_lineEdt_fou,*speedy6_lineEdt_fou,*speedy7_lineEdt_fou,*speedy8_lineEdt_fou,*speedy9_lineEdt_fou,*speedy10_lineEdt_fou;
    QLineEdit *maxspeedx_fou,*maxspeedy_fou,*deadx_fou,*deady_fou,*out_address_fou;
    QComboBox *output_d_type_fou,*baud_rate_fou,* data_bit_fou,*stop_bit_fou,*parity_bit_fou,*flow_control_fou;
    QString speed_s_fou[10]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9","等级10"};
    QString speed_q_fou[13]={"x轴最大速度","y轴最大速度","x方向死区","y方向死区","输出偏差类型设置","地址","波特率","数据位","停止位","校验位","流控制","平台x轴Bleed速率","平台y轴Bleed速率"};

    /*转台配置通道五*/
    MyWidget *w_speedconv_fif;
    QGroupBox *gbox_speedx_fif,*gbox_speedy_fif;
    QLineEdit *speedx1_lineEdt_fif,*speedx2_lineEdt_fif,*speedx3_lineEdt_fif,*speedx4_lineEdt_fif,*speedx5_lineEdt_fif,*speedx6_lineEdt_fif,*speedx7_lineEdt_fif,*speedx8_lineEdt_fif,*speedx9_lineEdt_fif,*speedx10_lineEdt_fif;
    QLineEdit *speedy1_lineEdt_fif,*speedy2_lineEdt_fif,*speedy3_lineEdt_fif,*speedy4_lineEdt_fif,*speedy5_lineEdt_fif,*speedy6_lineEdt_fif,*speedy7_lineEdt_fif,*speedy8_lineEdt_fif,*speedy9_lineEdt_fif,*speedy10_lineEdt_fif;
    QLineEdit *maxspeedx_fif,*maxspeedy_fif,*deadx_fif,*deady_fif,*out_address_fif;
    QComboBox *output_d_type_fif,*baud_rate_fif,* data_bit_fif,*stop_bit_fif,*parity_bit_fif,*flow_control_fif;
    QString speed_s_fif[10]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9","等级10"};
    QString speed_q_fif[13]={"x轴最大速度","y轴最大速度","x方向死区","y方向死区","输出偏差类型设置","地址","波特率","数据位","停止位","校验位","流控制","平台x轴Bleed速率","平台y轴Bleed速率"};

    /*相机配置*/
    void on_btn_right_clicked();



    /*摄像机配置通道1*/
        int vedio_current_shichang;
        MyWidget *w_sersor_1,*w_seitchField_1,*w_ContinueField_1;
       /*固定视场*/
       QPushButton *btn_vediosersor_fix_default,*btn_vediosersor_fix_update;
       QLineEdit *fix_gate_sizex,*fix_gate_sizey,*fix_gatelocationx,*fix_gatelocationy,*fix_lEdt,*fix_vertical;
       QCheckBox *fixChanelNum,*fixenable,*fix_vediohaveornot,*fix_gateshow,*fix_bullshow,*fix_autogate;
       QGroupBox *fix_vediochoose;
       QComboBox *fix_vedio_dpi;
       QPushButton *set_azimuth,*set_pitch,*set_zoom,*search_azimuth,*search_pitch,*search_zoom;
       QLineEdit  *ledt_set_azimuth,*ledt_set_pitch,*ledt_set_zoom,*ledt_search_azimuth,*ledt_search_pitch,*ledt_search_zoom;
       /*可切换视场*/    
       QPushButton *btn_vediosersor_default,*btn_vediosersor_update;
       QComboBox *vedio_dpi,*vedio_change1,*vedio_fovclass,*vedio_QGroupBox,*vedio_change2,*vedio_change3;
       QCheckBox *ChanelNum,*enable,*gateshow,*bullshow,*autogate,*vediohaveornot;
       QLineEdit *gate_sizex,*gate_sizey,*gatelocationx,*gatelocationy,*vedio_s1_Fov0,*vedio_s1_Fov1,*vedio_s1_Fov2,*vedio_s1_Fov3,*vedio_s1_Fov4;
       QGroupBox *vediochoose;
       QString vedio_s[4]={"是否接有摄像头","摄像机分辨率帧率","视场模式选择","视场平均比例(y轴/x轴)"};
       QSpinBox *vedio_spbx_switch1,*vedio_spbx_switch2,*vedio_spbx_switch3,*vedio_spbx_switch4,*vedio_spbx_switch5,*vedio_spby_switch1,*vedio_spby_switch2,*vedio_spby_switch3,*vedio_spby_switch4,*vedio_spby_switch5;
       MyQSpinBox *fix_sp,*fix_sp2;
       QPushButton *Change_set_azimuth,*Change_set_pitch,*Change_set_zoom,*Change_search_azimuth,*Change_search_pitch,*Change_search_zoom;
       QLineEdit  *Change_ledt_set_azimuth,*Change_ledt_set_pitch,*Change_ledt_set_zoom,*Change_ledt_search_azimuth,*Change_ledt_search_pitch,*Change_ledt_search_zoom,*Change_vertical1,*Change_vertical2,*Change_vertical3,*Change_vertical4,*Change_vertical5;
       /*连续视场*/
       QPushButton *btn_vediosersor_continue_default,*btn_vediosersor_continue_update;
       QLineEdit *continue_gate_sizex,*continue_gate_sizey,*continue_gatelocationx,*continue_gatelocationy,*test_1;
       QCheckBox *continueChanelNum,*continueenable,*continue_vediohaveornot,*continue_gateshow,*continue_bullshow,*continue_autogate;
       QComboBox *continue_vedio_dpi;
       QGroupBox *continue_vediochoose;
       MyQSpinBox *vedio_spbx_continue1,*vedio_spbx_continue2,*vedio_spbx_continue3,*vedio_spbx_continue4,*vedio_spbx_continue5,*vedio_spbx_continue6,*vedio_spbx_continue7,*vedio_spby_continue1,*vedio_spby_continue2,*vedio_spby_continue3,*vedio_spby_continue4,*vedio_spby_continue5,*vedio_spby_continue6,*vedio_spby_continue7;
       QLineEdit *vedio_l1_continue,*vedio_l2_continue,*vedio_l3_continue,*vedio_l4_continue,*vedio_l5_continue,*vedio_l6_continue,*vedio_l7_continue;
       QLineEdit *vedio_continue_Fov0,*vedio_continue_Fov1,*vedio_continue_Fov2,*vedio_continue_Fov3,*vedio_continue_Fov4,*vedio_continue_Fov5,*vedio_continue_Fov6;
       QPushButton *continue_set_azimuth,*continue_set_pitch,*continue_set_zoom,*continue_search_azimuth,*continue_search_pitch,*continue_search_zoom;
       QLineEdit  *continue_ledt_set_azimuth,*continue_ledt_set_pitch,*continue_ledt_set_zoom,*continue_ledt_search_azimuth,*continue_ledt_search_pitch,*continue_ledt_search_zoom,*continue_vertical;
       QLineEdit *continue_vertical1,*continue_vertical2,*continue_vertical3,*continue_vertical4,*continue_vertical5,*continue_vertical6,*continue_vertical7;



       /*摄像机配置通道2*/

          int vedio_current_shichang_sec;
          MyWidget *w_sersor_1_sec,*w_seitchField_1_sec,*w_ContinueField_1_sec;
          /*固定视场*/
          QPushButton  *btn_vediosersor_fix_default_sec,*btn_vediosersor_fix_update_sec;
          QLineEdit *fix_gate_sizex_sec,*fix_gate_sizey_sec,*fix_gatelocationx_sec,*fix_gatelocationy_sec,*fix_lEdt_sec,*fix_vertical_sec;
          QCheckBox *fixChanelNum_sec,*fixenable_sec,*fix_vediohaveornot_sec,*fix_gateshow_sec,*fix_bullshow_sec,*fix_autogate_sec;
          QGroupBox *fix_vediochoose_sec;
          QComboBox *fix_vedio_dpi_sec;
          QPushButton *set_azimuth_sec,*set_pitch_sec,*set_zoom_sec,*search_azimuth_sec,*search_pitch_sec,*search_zoom_sec;
          QLineEdit  *ledt_set_azimuth_sec,*ledt_set_pitch_sec,*ledt_set_zoom_sec,*ledt_search_azimuth_sec,*ledt_search_pitch_sec,*ledt_search_zoom_sec;
          /*可切换视场*/
          QPushButton  *btn_vediosersor_default_sec,*btn_vediosersor_update_sec;
          QComboBox *vedio_dpi_sec,*vedio_change1_sec,*vedio_fovclass_sec,*vedio_QGroupBox_sec,*vedio_change2_sec,*vedio_change3_sec;
          QCheckBox *ChanelNum_sec,*enable_sec,*gateshow_sec,*bullshow_sec,*autogate_sec,*vediohaveornot_sec;
          QLineEdit *gate_sizex_sec,*gate_sizey_sec,*gatelocationx_sec,*gatelocationy_sec,*vedio_s1_Fov0_sec,*vedio_s1_Fov1_sec,*vedio_s1_Fov2_sec,*vedio_s1_Fov3_sec,*vedio_s1_Fov4_sec;
          QGroupBox *vediochoose_sec;
          QString vedio_s_sec[4]={"是否接有摄像头","摄像机分辨率帧率","视场模式选择","视场平均比例(y轴/x轴)"};
          MyQSpinBox *vedio_spbx_switch1_sec,*vedio_spbx_switch2_sec,*vedio_spbx_switch3_sec,*vedio_spbx_switch4_sec,*vedio_spbx_switch5_sec,*vedio_spby_switch1_sec,*vedio_spby_switch2_sec,*vedio_spby_switch3_sec,*vedio_spby_switch4_sec,*vedio_spby_switch5_sec;
          MyQSpinBox *fix_sp_sec, *fix_sp2_sec;
          QPushButton *Change_set_azimuth_sec,*Change_set_pitch_sec,*Change_set_zoom_sec,*Change_search_azimuth_sec,*Change_search_pitch_sec,*Change_search_zoom_sec;
          QLineEdit  *Change_ledt_set_azimuth_sec,*Change_ledt_set_pitch_sec,*Change_ledt_set_zoom_sec,*Change_ledt_search_azimuth_sec,*Change_ledt_search_pitch_sec,*Change_ledt_search_zoom_sec,*Change_vertical1_sec,*Change_vertical2_sec,*Change_vertical3_sec,*Change_vertical4_sec,*Change_vertical5_sec;
          /*连续视场*/
          QPushButton *btn_vediosersor_continue_default_sec,*btn_vediosersor_continue_update_sec;
          QLineEdit *continue_gate_sizex_sec,*continue_gate_sizey_sec,*continue_gatelocationx_sec,*continue_gatelocationy_sec,*test_1_sec;
          QCheckBox *continueChanelNum_sec,*continueenable_sec,*continue_vediohaveornot_sec,*continue_gateshow_sec,*continue_bullshow_sec,*continue_autogate_sec;
          QComboBox *continue_vedio_dpi_sec;
          QGroupBox *continue_vediochoose_sec;
          MyQSpinBox *vedio_spbx_continue1_sec,*vedio_spbx_continue2_sec,*vedio_spbx_continue3_sec,*vedio_spbx_continue4_sec,*vedio_spbx_continue5_sec,*vedio_spbx_continue6_sec,*vedio_spbx_continue7_sec,*vedio_spby_continue1_sec,*vedio_spby_continue2_sec,*vedio_spby_continue3_sec,*vedio_spby_continue4_sec,*vedio_spby_continue5_sec,*vedio_spby_continue6_sec,*vedio_spby_continue7_sec;
          QLineEdit *vedio_l1_continue_sec,*vedio_l2_continue_sec,*vedio_l3_continue_sec,*vedio_l4_continue_sec,*vedio_l5_continue_sec,*vedio_l6_continue_sec,*vedio_l7_continue_sec;
          QLineEdit *vedio_continue_Fov0_sec,*vedio_continue_Fov1_sec,*vedio_continue_Fov2_sec,*vedio_continue_Fov3_sec,*vedio_continue_Fov4_sec,*vedio_continue_Fov5_sec,*vedio_continue_Fov6_sec;
          QPushButton *continue_set_azimuth_sec,*continue_set_pitch_sec,*continue_set_zoom_sec,*continue_search_azimuth_sec,*continue_search_pitch_sec,*continue_search_zoom_sec;
          QLineEdit  *continue_ledt_set_azimuth_sec,*continue_ledt_set_pitch_sec,*continue_ledt_set_zoom_sec,*continue_ledt_search_azimuth_sec,*continue_ledt_search_pitch_sec,*continue_ledt_search_zoom_sec,*continue_vertical_sec;
          QLineEdit *continue_vertical1_sec,*continue_vertical2_sec,*continue_vertical3_sec,*continue_vertical4_sec,*continue_vertical5_sec,*continue_vertical6_sec,*continue_vertical7_sec;



          /*摄像机配置通道3*/
             int vedio_current_shichang_thi;
             MyWidget *w_sersor_1_thi,*w_seitchField_1_thi,*w_ContinueField_1_thi;
             /*固定视场*/
             QPushButton  *btn_vediosersor_fix_default_thi,*btn_vediosersor_fix_update_thi;
             QLineEdit *fix_gate_sizex_thi,*fix_gate_sizey_thi,*fix_gatelocationx_thi,*fix_gatelocationy_thi,*fix_lEdt_thi,*fix_vertical_thi;
             QCheckBox *fixChanelNum_thi,*fixenable_thi,*fix_vediohaveornot_thi,*fix_gateshow_thi,*fix_bullshow_thi,*fix_autogate_thi;
             QGroupBox *fix_vediochoose_thi;
             QComboBox *fix_vedio_dpi_thi;
             QPushButton *set_azimuth_thi,*set_pitch_thi,*set_zoom_thi,*search_azimuth_thi,*search_pitch_thi,*search_zoom_thi;
             QLineEdit  *ledt_set_azimuth_thi,*ledt_set_pitch_thi,*ledt_set_zoom_thi,*ledt_search_azimuth_thi,*ledt_search_pitch_thi,*ledt_search_zoom_thi;
             MyQSpinBox *fix_sp_thi,*fix_sp2_thi;
             /*可切换视场*/
             QPushButton  *btn_vediosersor_default_thi,*btn_vediosersor_update_thi;
             QComboBox *vedio_dpi_thi,*vedio_change1_thi,*vedio_fovclass_thi,*vedio_QGroupBox_thi,*vedio_change2_thi,*vedio_change3_thi;
             QCheckBox *ChanelNum_thi,*enable_thi,*gateshow_thi,*bullshow_thi,*autogate_thi,*vediohaveornot_thi;
             QLineEdit *gate_sizex_thi,*gate_sizey_thi,*gatelocationx_thi,*gatelocationy_thi,*vedio_s1_Fov0_thi,*vedio_s1_Fov1_thi,*vedio_s1_Fov2_thi,*vedio_s1_Fov3_thi,*vedio_s1_Fov4_thi;
             QGroupBox *vediochoose_thi;
             QString vedio_s_thi[4]={"是否接有摄像头","摄像机分辨率帧率","视场模式选择","视场平均比例(y轴/x轴)"};
             MyQSpinBox *vedio_spbx_switch1_thi,*vedio_spbx_switch2_thi,*vedio_spbx_switch3_thi,*vedio_spbx_switch4_thi,*vedio_spbx_switch5_thi,*vedio_spby_switch1_thi,*vedio_spby_switch2_thi,*vedio_spby_switch3_thi,*vedio_spby_switch4_thi,*vedio_spby_switch5_thi;
             QPushButton *Change_set_azimuth_thi,*Change_set_pitch_thi,*Change_set_zoom_thi,*Change_search_azimuth_thi,*Change_search_pitch_thi,*Change_search_zoom_thi;
             QLineEdit  *Change_ledt_set_azimuth_thi,*Change_ledt_set_pitch_thi,*Change_ledt_set_zoom_thi,*Change_ledt_search_azimuth_thi,*Change_ledt_search_pitch_thi,*Change_ledt_search_zoom_thi,*Change_vertical1_thi,*Change_vertical2_thi,*Change_vertical3_thi,*Change_vertical4_thi,*Change_vertical5_thi;
             /*连续视场*/
             QPushButton *btn_vediosersor_continue_default_thi,*btn_vediosersor_continue_update_thi;
             QLineEdit *continue_gate_sizex_thi,*continue_gate_sizey_thi,*continue_gatelocationx_thi,*continue_gatelocationy_thi,*test_1_thi;
             QCheckBox *continueChanelNum_thi,*continueenable_thi,*continue_vediohaveornot_thi,*continue_gateshow_thi,*continue_bullshow_thi,*continue_autogate_thi;
             QComboBox *continue_vedio_dpi_thi;
             QGroupBox *continue_vediochoose_thi;
             MyQSpinBox *vedio_spbx_continue1_thi,*vedio_spbx_continue2_thi,*vedio_spbx_continue3_thi,*vedio_spbx_continue4_thi,*vedio_spbx_continue5_thi,*vedio_spbx_continue6_thi,*vedio_spbx_continue7_thi,*vedio_spby_continue1_thi,*vedio_spby_continue2_thi,*vedio_spby_continue3_thi,*vedio_spby_continue4_thi,*vedio_spby_continue5_thi,*vedio_spby_continue6_thi,*vedio_spby_continue7_thi;
             QLineEdit *vedio_l1_continue_thi,*vedio_l2_continue_thi,*vedio_l3_continue_thi,*vedio_l4_continue_thi,*vedio_l5_continue_thi,*vedio_l6_continue_thi,*vedio_l7_continue_thi;
             QLineEdit *vedio_continue_Fov0_thi,*vedio_continue_Fov1_thi,*vedio_continue_Fov2_thi,*vedio_continue_Fov3_thi,*vedio_continue_Fov4_thi,*vedio_continue_Fov5_thi,*vedio_continue_Fov6_thi;
             QPushButton *continue_set_azimuth_thi,*continue_set_pitch_thi,*continue_set_zoom_thi,*continue_search_azimuth_thi,*continue_search_pitch_thi,*continue_search_zoom_thi;
             QLineEdit  *continue_ledt_set_azimuth_thi,*continue_ledt_set_pitch_thi,*continue_ledt_set_zoom_thi,*continue_ledt_search_azimuth_thi,*continue_ledt_search_pitch_thi,*continue_ledt_search_zoom_thi,*continue_vertical_thi;
             QLineEdit *continue_vertical1_thi,*continue_vertical2_thi,*continue_vertical3_thi,*continue_vertical4_thi,*continue_vertical5_thi,*continue_vertical6_thi,*continue_vertical7_thi;


             /*摄像机配置通道4*/
                /*固定视场*/
                QPushButton  *btn_vediosersor_fix_default_fou,*btn_vediosersor_fix_update_fou;
                QLineEdit *fix_gate_sizex_fou,*fix_gate_sizey_fou,*fix_gatelocationx_fou,*fix_gatelocationy_fou,*fix_lEdt_fou,*fix_vertical_fou;
                QCheckBox *fixChanelNum_fou,*fixenable_fou,*fix_vediohaveornot_fou,*fix_gateshow_fou,*fix_bullshow_fou,*fix_autogate_fou;
                QGroupBox *fix_vediochoose_fou;
                QComboBox *fix_vedio_dpi_fou;
                QPushButton *set_azimuth_fou,*set_pitch_fou,*set_zoom_fou,*search_azimuth_fou,*search_pitch_fou,*search_zoom_fou;
                QLineEdit  *ledt_set_azimuth_fou,*ledt_set_pitch_fou,*ledt_set_zoom_fou,*ledt_search_azimuth_fou,*ledt_search_pitch_fou,*ledt_search_zoom_fou;
                MyQSpinBox *fix_sp_fou,*fix_sp2_fou;
                /*可切换视场*/
                int vedio_current_shichang_fou;
                MyWidget *w_sersor_1_fou,*w_seitchField_1_fou,*w_ContinueField_1_fou;
                QPushButton  *btn_vediosersor_default_fou,*btn_vediosersor_update_fou;
                QComboBox *vedio_dpi_fou,*vedio_change1_fou,*vedio_fovclass_fou,*vedio_QGroupBox_fou,*vedio_change2_fou,*vedio_change3_fou;
                QCheckBox *ChanelNum_fou,*enable_fou,*gateshow_fou,*bullshow_fou,*autogate_fou,*vediohaveornot_fou;
                QLineEdit *gate_sizex_fou,*gate_sizey_fou,*gatelocationx_fou,*gatelocationy_fou,*vedio_s1_Fov0_fou,*vedio_s1_Fov1_fou,*vedio_s1_Fov2_fou,*vedio_s1_Fov3_fou,*vedio_s1_Fov4_fou;
                QGroupBox *vediochoose_fou;
                QString vedio_s_fou[4]={"是否接有摄像头","摄像机分辨率帧率","视场模式选择","视场平均比例(y轴/x轴)"};
                MyQSpinBox *vedio_spbx_switch1_fou,*vedio_spbx_switch2_fou,*vedio_spbx_switch3_fou,*vedio_spbx_switch4_fou,*vedio_spbx_switch5_fou,*vedio_spby_switch1_fou,*vedio_spby_switch2_fou,*vedio_spby_switch3_fou,*vedio_spby_switch4_fou,*vedio_spby_switch5_fou;
                QPushButton *Change_set_azimuth_fou,*Change_set_pitch_fou,*Change_set_zoom_fou,*Change_search_azimuth_fou,*Change_search_pitch_fou,*Change_search_zoom_fou;
                QLineEdit  *Change_ledt_set_azimuth_fou,*Change_ledt_set_pitch_fou,*Change_ledt_set_zoom_fou,*Change_ledt_search_azimuth_fou,*Change_ledt_search_pitch_fou,*Change_ledt_search_zoom_fou,*Change_vertical1_fou,*Change_vertical2_fou,*Change_vertical3_fou,*Change_vertical4_fou,*Change_vertical5_fou;
                /*连续视场*/
                QPushButton *btn_vediosersor_continue_default_fou,*btn_vediosersor_continue_update_fou;
                QLineEdit *continue_gate_sizex_fou,*continue_gate_sizey_fou,*continue_gatelocationx_fou,*continue_gatelocationy_fou,*test_1_fou;
                QCheckBox *continueChanelNum_fou,*continueenable_fou,*continue_vediohaveornot_fou,*continue_gateshow_fou,*continue_bullshow_fou,*continue_autogate_fou;
                QComboBox *continue_vedio_dpi_fou;
                QGroupBox *continue_vediochoose_fou;
                MyQSpinBox *vedio_spbx_continue1_fou,*vedio_spbx_continue2_fou,*vedio_spbx_continue3_fou,*vedio_spbx_continue4_fou,*vedio_spbx_continue5_fou,*vedio_spbx_continue6_fou,*vedio_spbx_continue7_fou,*vedio_spby_continue1_fou,*vedio_spby_continue2_fou,*vedio_spby_continue3_fou,*vedio_spby_continue4_fou,*vedio_spby_continue5_fou,*vedio_spby_continue6_fou,*vedio_spby_continue7_fou;
                QLineEdit *vedio_l1_continue_fou,*vedio_l2_continue_fou,*vedio_l3_continue_fou,*vedio_l4_continue_fou,*vedio_l5_continue_fou,*vedio_l6_continue_fou,*vedio_l7_continue_fou;
                QLineEdit *vedio_continue_Fov0_fou,*vedio_continue_Fov1_fou,*vedio_continue_Fov2_fou,*vedio_continue_Fov3_fou,*vedio_continue_Fov4_fou,*vedio_continue_Fov5_fou,*vedio_continue_Fov6_fou;
                QPushButton *continue_set_azimuth_fou,*continue_set_pitch_fou,*continue_set_zoom_fou,*continue_search_azimuth_fou,*continue_search_pitch_fou,*continue_search_zoom_fou;
                QLineEdit  *continue_ledt_set_azimuth_fou,*continue_ledt_set_pitch_fou,*continue_ledt_set_zoom_fou,*continue_ledt_search_azimuth_fou,*continue_ledt_search_pitch_fou,*continue_ledt_search_zoom_fou,*continue_vertical_fou;
                QLineEdit *continue_vertical1_fou,*continue_vertical2_fou,*continue_vertical3_fou,*continue_vertical4_fou,*continue_vertical5_fou,*continue_vertical6_fou,*continue_vertical7_fou;

                /*摄像机配置通道5*/
                   /*固定视场*/
                   QPushButton  *btn_vediosersor_fix_default_fif,*btn_vediosersor_fix_update_fif;
                   QLineEdit *fix_gate_sizex_fif,*fix_gate_sizey_fif,*fix_gatelocationx_fif,*fix_gatelocationy_fif,*fix_lEdt_fif,*fix_vertical_fif;
                   QCheckBox *fixChanelNum_fif,*fixenable_fif,*fix_vediohaveornot_fif,*fix_gateshow_fif,*fix_bullshow_fif,*fix_autogate_fif;
                   QGroupBox *fix_vediochoose_fif;
                   QComboBox *fix_vedio_dpi_fif;
                   QPushButton *set_azimuth_fif,*set_pitch_fif,*set_zoom_fif,*search_azimuth_fif,*search_pitch_fif,*search_zoom_fif;
                   QLineEdit  *ledt_set_azimuth_fif,*ledt_set_pitch_fif,*ledt_set_zoom_fif,*ledt_search_azimuth_fif,*ledt_search_pitch_fif,*ledt_search_zoom_fif;
                   MyQSpinBox *fix_sp_fif,*fix_sp2_fif;
                   /*可切换视场*/
                   int vedio_current_shichang_fif;
                   MyWidget *w_sersor_1_fif,*w_seitchField_1_fif,*w_ContinueField_1_fif;
                   QPushButton  *btn_vediosersor_default_fif,*btn_vediosersor_update_fif;
                   QComboBox *vedio_dpi_fif,*vedio_change1_fif,*vedio_fovclass_fif,*vedio_QGroupBox_fif,*vedio_change2_fif,*vedio_change3_fif;
                   QCheckBox *ChanelNum_fif,*enable_fif,*gateshow_fif,*bullshow_fif,*autogate_fif,*vediohaveornot_fif;
                   QLineEdit *gate_sizex_fif,*gate_sizey_fif,*gatelocationx_fif,*gatelocationy_fif,*vedio_s1_Fov0_fif,*vedio_s1_Fov1_fif,*vedio_s1_Fov2_fif,*vedio_s1_Fov3_fif,*vedio_s1_Fov4_fif;
                   QGroupBox *vediochoose_fif;
                   QString vedio_s_fif[4]={"是否接有摄像头","摄像机分辨率帧率","视场模式选择","视场平均比例(y轴/x轴)"};
                   MyQSpinBox *vedio_spbx_switch1_fif,*vedio_spbx_switch2_fif,*vedio_spbx_switch3_fif,*vedio_spbx_switch4_fif,*vedio_spbx_switch5_fif,*vedio_spby_switch1_fif,*vedio_spby_switch2_fif,*vedio_spby_switch3_fif,*vedio_spby_switch4_fif,*vedio_spby_switch5_fif;
                   QPushButton *Change_set_azimuth_fif,*Change_set_pitch_fif,*Change_set_zoom_fif,*Change_search_azimuth_fif,*Change_search_pitch_fif,*Change_search_zoom_fif;
                   QLineEdit  *Change_ledt_set_azimuth_fif,*Change_ledt_set_pitch_fif,*Change_ledt_set_zoom_fif,*Change_ledt_search_azimuth_fif,*Change_ledt_search_pitch_fif,*Change_ledt_search_zoom_fif,*Change_vertical1_fif,*Change_vertical2_fif,*Change_vertical3_fif,*Change_vertical4_fif,*Change_vertical5_fif;
                   /*连续视场*/
                   QPushButton *btn_vediosersor_continue_default_fif,*btn_vediosersor_continue_update_fif;
                   QLineEdit *continue_gate_sizex_fif,*continue_gate_sizey_fif,*continue_gatelocationx_fif,*continue_gatelocationy_fif,*test_1_fif;
                   QCheckBox *continueChanelNum_fif,*continueenable_fif,*continue_vediohaveornot_fif,*continue_gateshow_fif,*continue_bullshow_fif,*continue_autogate_fif;
                   QComboBox *continue_vedio_dpi_fif;
                   QGroupBox *continue_vediochoose_fif;
                   MyQSpinBox *vedio_spbx_continue1_fif,*vedio_spbx_continue2_fif,*vedio_spbx_continue3_fif,*vedio_spbx_continue4_fif,*vedio_spbx_continue5_fif,*vedio_spbx_continue6_fif,*vedio_spbx_continue7_fif,*vedio_spby_continue1_fif,*vedio_spby_continue2_fif,*vedio_spby_continue3_fif,*vedio_spby_continue4_fif,*vedio_spby_continue5_fif,*vedio_spby_continue6_fif,*vedio_spby_continue7_fif;
                   QLineEdit *vedio_l1_continue_fif,*vedio_l2_continue_fif,*vedio_l3_continue_fif,*vedio_l4_continue_fif,*vedio_l5_continue_fif,*vedio_l6_continue_fif,*vedio_l7_continue_fif;
                   QLineEdit *vedio_continue_Fov0_fif,*vedio_continue_Fov1_fif,*vedio_continue_Fov2_fif,*vedio_continue_Fov3_fif,*vedio_continue_Fov4_fif,*vedio_continue_Fov5_fif,*vedio_continue_Fov6_fif;
                   QPushButton *continue_set_azimuth_fif,*continue_set_pitch_fif,*continue_set_zoom_fif,*continue_search_azimuth_fif,*continue_search_pitch_fif,*continue_search_zoom_fif;
                   QLineEdit  *continue_ledt_set_azimuth_fif,*continue_ledt_set_pitch_fif,*continue_ledt_set_zoom_fif,*continue_ledt_search_azimuth_fif,*continue_ledt_search_pitch_fif,*continue_ledt_search_zoom_fif,*continue_vertical_fif;
                   QLineEdit *continue_vertical1_fif,*continue_vertical2_fif,*continue_vertical3_fif,*continue_vertical4_fif,*continue_vertical5_fif,*continue_vertical6_fif,*continue_vertical7_fif;
    /*移动检测配置*/
    MyWidget *w_mtd;
    QPushButton *btn_mtd_default,*btn_mtd_update;
    QLineEdit *rigion_Cen_x,*rigion_Cen_y,*rigion_Cen_w,*rigion_Cen_h,*maxnum,*uspeed,*maxpix,*minpix,*sensitive,*dspeed,*trktime,*Alarm_delay;
    QComboBox *output,*polar,*Priority_judgment;
    QString mtd_s[14]={"检测区域中心坐标","检测区域宽高","最多检测个数","模板更新速度","目标面积最大值","目标面积最小值","灵敏度阈值","检测速度","最大跟踪时间","优先级判断","开关量输出","开关量输出极性","报警延时时间","区域设置提示框"};
    QCheckBox  *zone_setting;

    /*UTC*/
    QPushButton *btn_utc1_default,*btn_utc1_update,*btn_utc2_default,*btn_utc2_update,*btn_utc3_default,*btn_utc3_update;
    MyWidget *utc1,*utc2,*utc3;
    QGroupBox *gbox_utc1,*gbox_utc2,*gbox_utc3;
    QLineEdit *utc1_l0,*utc1_l1,*utc1_l2,*utc1_l3,*utc1_l4,*utc1_l5,
              *utc1_l6,*utc1_l7,*utc1_l8,*utc1_l9,*utc1_l10,*utc1_l11,
              *utc1_l12,*utc1_l13,*utc1_l14,*utc1_l15;
    QLineEdit *utc2_l0,*utc2_l1,*utc2_l2,*utc2_l3,*utc2_l4,*utc2_l5,
              *utc2_l6,*utc2_l7,*utc2_l8,*utc2_l9,*utc2_l10,*utc2_l11,
              *utc2_l12,*utc2_l13,*utc2_l14,*utc2_l15;
    QLineEdit *utc3_l0,*utc3_l1,*utc3_l2,*utc3_l3,*utc3_l4,*utc3_l5,
              *utc3_l6,*utc3_l7,*utc3_l8,*utc3_l9,*utc3_l10,*utc3_l11,
              *utc3_l12,*utc3_l13,*utc3_l14,*utc3_l15;
    QString utc_s1[16]={"丢失阈值","重捕获阈值","模板更新比例","res_distance","res_area","gapframe","enhEnable","cliplimit","dictEnable","moveX","moveY","moveX2","moveY2","segPixelX","segPixelY","algOsdRect Enable"};
    QString utc_s2[16]={"ScalerLarge","ScalerMid","ScalerSmall","Scatter","ratio","FilterEnable","BigSecEnable","SalientThred","ScalerEnable","DynamicRatioEnable","acqSize.width","acqSize.height","TrkAim 4:3 Enable","SceneMVEnable","BackTrackEnable","bAveTrkPos"};
    QString utc_s3[16]={"fTau","buildFrms","LostFrmThred","histMvThred","detectFrms","stillFrms","stillThred","bKalmanFilter","xMVThred","yMVThred","xStillThred","yStillThred","slopeThred","kalmanHistThred","kalmanCoefQ","kalmanCoefR"};

    /*捕获框配置*/
    MyWidget *w_capture1,*w_capture2,*w_capture3;
    QPushButton *btn_capture_default,*btn_capture_update,*btn_capture2_default,*btn_capture2_update,*btn_capture3_default,*btn_capture3_update;
    QLineEdit *cap_0_w,*cap_1_w,*cap_2_w,*cap_3_w,*cap_4_w,*cap_5_w,*cap_0_h,*cap_1_h,*cap_2_h,*cap_3_h,*cap_4_h,*cap_5_h;
    QLineEdit *bomen_0_w,*bomen_1_w,*bomen_2_w,*bomen_3_w,*bomen_4_w,*bomen_5_w,*bomen_0_h,*bomen_1_h,*bomen_2_h,*bomen_3_h,*bomen_4_h,*bomen_5_h;
    QCheckBox *autobomen_checkbox;
    QLineEdit *drawLine_1,*drawLine_2,*drawLine_3,*drawLine_4,*drawLine_5;
    QString string_cap[12]={"通道0捕获框宽","通道1捕获框宽","通道2捕获框宽","通道3捕获框宽","通道4捕获框宽","通道5捕获框宽","通道0捕获框高","通道1捕获框高","通道2捕获框高","通道3捕获框高","通道4捕获框高","通道5捕获框高"};
    QString string_bomen[10]={"通道1波门宽","通道2波门宽","通道3波门宽","通道4波门宽","通道5波门宽","通道1波门高","通道2波门高","通道3波门高","通道4波门高","通道5波门高"};
    QString string_drawLine[6]={"画线显示否","画线的颜色","十字宽","十字高","画中画十字宽","画中画十字高"};
    QCheckBox *checkBox_cross;
    /*OSD*/
    QComboBox *c,*CBox_color,*CBox_font,*CBox_font_size,*CBox_transparency;
    QPushButton *btn_osd1_default,*btn_osd1_update,*btn_keep1;
    MyWidget *w_osd1;
    QCheckBox *checkBox,*checkBox2;
    QGroupBox *Custom;
    QLineEdit *osd1_pos_x,*osd1_pos_y,*osd1_lineEdit_label,*osd1_lineEdit_context,*osd1_lineEdit_font,*osd1_lineEdit_color;
    QString osd_s[14]={"用户自定义字符显示","显示","x位置","y位置","内容","颜色","透明度","字体大小"};

    /*软件升级*/
    RcvUSocketdata  *thread_usocket;
    QLineEdit *upgrade_ip;
    QLineEdit *upgrade_port;
    QFile  file,fpgafile;  // 文件对象
    QString fileName,fpgafileName; //文件名字
    qint64 filesize,fpgafilesize; // 文件大小
    qint64 sendsize,fpgasendsize;  // 已经发送的数据大小
	bool socketIsconnect=false;


    QButtonGroup  *workcheckbox;
    QButtonGroup  *acqcheckbox;

    /*实时输出界面*/
    MyWidget *w_realtime_output;
    QLineEdit *rto_currstat, *rto_trkerrorx, *rto_trkerrory, *rto_speedneedx, *rto_speedneedy, *rto_speedclassx, *rto_speedclassy;
};
extern MainWindow *pthis;
#endif // MAINWINDOW_H
