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

#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767
#define POINTX 350 //圆左上角坐标x
#define POINTY 100 //圆左上角坐标Y
#define CENTER 192//圆的半径
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

    /*初始化的配置*/
    void init_menu();
    void init_sysCfg();
    void init_platCfg();
    void init_dbCfg();
    void init_speedconvCfg();
    void init_mtdCfg();
    void init_utcCfg();
    void init_captureCfg();
    void init_OSDCfg();
    void init_cameraCfg();
    void init_cameraCfg_sec();
    void init_cameraCfg_thi();
    void init_cameraCfg_fou();
    void init_cameraCfg_fif();
    void init_resl();

    /*协议传输*/
    QByteArray string2hex(QString str,bool &flag);
    char convertHex2Char(char ch);
    void send_oneframe(int length);
    volatile qint32 sendNum =0;

    /*线程*/
    void output_to_label(int i);
    void socket_parse_bytearray();
    void usocket_parse_bytearray();
    void socket_Read_Data();
    void upgrade_showtext(int i,int percent);

    /*计算圆边界值*/
    void calculationCircle(int center_a, int center_b, int x, int y);

    void btnSensor1SwitchSlot();
    void btnSensor1SwitchSlot_sec();
    void btnSensor1SwitchSlot_thi();
    void btnSensor1SwitchSlot_fou();
    void btnSensor1SwitchSlot_fif();
    void btnSensor2ContinueSlot();
    void btnSensor2ContinueSlot_sec();
    void btnSensor2ContinueSlot_thi();
    void btnSensor2ContinueSlot_fou();
    void btnSensor2ContinueSlot_fif();

    /*发送0x31命令*/
    void read_config(int block);
    void send_read_config(int block,int start_field, int end_field);
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
    void showCamera();
    void showCamera_sec();
    void showCamera_thi();
    void showCamera_fou();
    void showCamera_fif();
    void showAlg();
    void showAlg2();
    void showAlg3();
    void showCapture1();
    void showCapture2();
    void showCapture3();
    void showOther();
    void showdbgcfg();
    void showspeedconvcfg();
    void showmtdcfg();

    /*系统配置槽函数*/
    void btnDownSlot();
    void btnUpSlot();
    void btnSaveSlot();
    void btnselectsw_clicked();
    void btnUpdate();
    void btnFPGA_clicked();

    /*相机配置槽函数*/
    void btn_default_Slot();
    void btn_default_Slot2();
    void btn_default_Slot3();
    void tosersor_fix(int i);
    void tosersor_fix_sec(int i);
    void tosersor_fix_thi(int i);
    void tosersor_fix_fou(int i);
    void tosersor_fix_fif(int i);
    void toSensor_switch(int i);
    void toSensor_switch_sec(int i);
    void toSensor_switch_thi(int i);
    void toSensor_switch_fou(int i);
    void toSensor_switch_fif(int i);
    void tosersor_continue(int i);
    void tosersor_continue_sec(int i);
    void tosersor_continue_thi(int i);
    void tosersor_continue_fou(int i);
    void tosersor_continue_fif(int i);

    /*槽函数*/
    void resetAction();

    void toCBox(int i);
    void toOSD1Slot();
    void toOSD2Slot();
    void toOSD3Slot();
    void toOSD4Slot();
    void toMainTest();//测试跳转

    /**/


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
    void checkBox_channel_Slot(int i);

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

    void lEdt_PID1_Slot();
    void lEdt_PID2_Slot();
    void lEdt_PID3_Slot();
    void lEdt_PID4_Slot();
    void lEdt_PID5_Slot();
    void lEdt_PID6_Slot();
    void lEdt_PID7_Slot();
    void lEdt_PID8_Slot();

    void lEdt_plat1_Slot();
    void lEdt_plat2_Slot();
    void lEdt_plat3_Slot();
    void lEdt_plat4_Slot();
    void lEdt_plat5_Slot();
    void lEdt_plat6_Slot();
    void lEdt_plat7_Slot();
    void outMode_Slot(int i);

    /*捕获配置配置*/
    void lEdt_kx_Slot();
    void lEdt_ky_Slot();
    void lEdt_errx_Slot();
    void lEdt_erry_Slot();
    void lEdt_time_Slot();
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

    /*转换表配置*/
    void lEdt_speedx1_Slot();
    void lEdt_speedx2_Slot();
    void lEdt_speedx3_Slot();
    void lEdt_speedx4_Slot();
    void lEdt_speedx5_Slot();
    void lEdt_speedx6_Slot();
    void lEdt_speedx7_Slot();
    void lEdt_speedx8_Slot();
    void lEdt_speedx9_Slot();
    void lEdt_speedy1_Slot();
    void lEdt_speedy2_Slot();
    void lEdt_speedy3_Slot();
    void lEdt_speedy4_Slot();
    void lEdt_speedy5_Slot();
    void lEdt_speedy6_Slot();
    void lEdt_speedy7_Slot();
    void lEdt_speedy8_Slot();
    void lEdt_speedy9_Slot();
    void btn_Speed_Default_Slot();
    void btn_Speed_Update_Slot();

    /*通道1固定视场*/
    void lEdt_fix_Radio_Slot();
    void lEdt_Resolution_Slot();
    void lEdt_Resolution2_Slot();
    void btn_fix_Slot();
    void lEdt_fix_view_Slot();
    void sp_fix_x_Slot(int i);
    void sp_fix_y_Slot(int i);
    void sp_test_Slot();

    /*通道1可切换视场*/
    void lEdt_switch_Radio_Slot();
    void lEdt_switch_Resolution_Slot();
    void btn_switch1_Slot();
    void btn_switch2_Slot();
    void btn_switch3_Slot();
    void btn_switch4_Slot();
    void btn_switch5_Slot();

    /*通道1连续视场*/
    void lEdt_continue_Radio_Slot();
    void lEdt_continue_Resolution_Slot();
    void btn_continue1_Slot();
    void btn_continue2_Slot();
    void btn_continue3_Slot();
    void btn_continue4_Slot();
    void btn_continue5_Slot();
    void btn_continue6_Slot();
    void btn_continue7_Slot();
    void btn_continue8_Slot();
    void btn_continue9_Slot();
    void btn_continue10_Slot();
    void btn_continue11_Slot();
    void btn_continue12_Slot();
    void btn_continue13_Slot();

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
    void lEdt_transparency_Slot();

    /*捕获框设置*/
    void checkBox_cross_Slot(int i);
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
    QTcpSocket *socket;
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
    int a, b, m_dragging,b_center,a_center,old_x,old_y;
    int mousePress = 0;
   // QMutex send_mutex;
    unsigned char send_arr[1080];
    unsigned short sectrk_x = 0;
    unsigned short sectrk_y = 0;

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
    QGroupBox *gbox_Jos,*gbox_PID,*gbox_plat;
    QLineEdit *josDead_lineEdt,*josPoint_lineEdt,*josInputG_x,*josInputG_y,*josPoint_lineEdt2,*josInputG_x2,*josInputG_y2,
              *josOutputG_x,*josOutputG_y;
    QComboBox *outMode;
    QLineEdit *kp1_pid,*ki1_pid,*kd1_pid,*k1,*kp2_pid,*ki2_pid,*kd2_pid,*k2;
    QLineEdit *bleedx_plat,*bleedy_plat,*mx_plat,*my_plat,*deadx_plat,*deady_plat,*a_plat;
     QString string_outMode[7]={"Zero","JoystickInput","ShapedAndGained","ShapedAndGainedAndIntegrated","DeterminedByPostion","ZeroInitFilter","DeterminedByIncomingPlatformData"};
    QString jos_s[9]={"手柄死区","手柄拐点1","手柄x轴输入增益1","手柄y轴输入增益1","手柄拐点2","手柄x轴输入增益2","手柄y轴输入增益2","摇杆平台x输出增益","摇杆平台y轴输出增益"};
    QString pid_s[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
    QString plat_s[8]={"x轴最大速度","y轴最大速度","x轴最大速度","y轴最大速度","x轴死区","y轴死区","惯性跟踪时间","平台输出模式"};

    /*捕获配置*/
    MyWidget *w_dbg;
    QLineEdit *kx_lineEdt,*ky_lineEdt,*errx_lineEdt,*erry_lineEdt,*time_lineEdt,*dbg5_lineEdt,*dbg6_lineEdt,*dbg7_lineEdt,*dbg8_lineEdt,*dbg9_lineEdt,*dbg10_lineEdt,
    *dbg11_lineEdt,*dbg12_lineEdt,*dbg13_lineEdt,*dbg14_lineEdt,*dbg15_lineEdt;
    QString dbg_s[16]={"x轴比例调节系数","y轴比例调节系数","x轴进PID偏差","y轴进PID偏差","进PID时间","debug5","debug6","debug7","debug8","debug9","debug10","debug11","debug12","debug13","debug14","debug15"};

    /*转换表配置*/
    MyWidget *w_speedconv;
    QGroupBox *gbox_speedx,*gbox_speedy;
    QLineEdit *speedx1_lineEdt,*speedx2_lineEdt,*speedx3_lineEdt,*speedx4_lineEdt,*speedx5_lineEdt,*speedx6_lineEdt,*speedx7_lineEdt,*speedx8_lineEdt,*speedx9_lineEdt;
    QLineEdit *speedy1_lineEdt,*speedy2_lineEdt,*speedy3_lineEdt,*speedy4_lineEdt,*speedy5_lineEdt,*speedy6_lineEdt,*speedy7_lineEdt,*speedy8_lineEdt,*speedy9_lineEdt;
    QString speed_s[9]={"等级1","等级2","等级3","等级4","等级5","等级6","等级7","等级8","等级9"};

    /*相机配置*/
    void on_btn_right_clicked();

    /*移动检测配置*/
    MyWidget *w_mtd;
    QPushButton *btn_mtd_default,*btn_mtd_update;
    QLineEdit *rigion,*maxnum,*uspeed,*maxpix,*minpix,*sensitive,*dspeed,*trktime,*polar;
    QComboBox *output;
    QString mtd_s[10]={"检测区域","最多检测个数","模板更新速度","目标像素最大值","目标像素最小值","灵敏度阈值","检测速度","最大跟踪时间","开关量输出","开关量输出极性"};

    /*通道1*/
    MyWidget *w_sersor1,*w_seitchField,*w_ContinueField;
    QStackedLayout *sta;
    QComboBox *change3,*change2,*change1;
    int current_shichang;

    //固定视场参数
    //QPushButton *ok;
    QSpinBox *sp,*sp2;
    QLineEdit *lineEdit_fieldRadio,*lineEdit_fieldResolution,*lineEdit_FOV_x,*lineEdit_FOV_y,*lineEdit_fieldResolution2,*lEdt;
    QString sensor_s1[7]={"视场模式选择","视场平均比例（y轴/x轴）","分辨率（水平*垂直）","FOV","FOV的靶心X","FOV的靶心Y"};
    //可切换视场参数
    QLineEdit *lineEdit_switchRadio,*lineEdit_switchResolution,*lineEdit_switchResolution2;
    QSpinBox *spby_switch1,*spby_switch2,*spby_switch3,*spby_switch4,*spby_switch5;
    QSpinBox *spbx_switch1,*spbx_switch2,*spbx_switch3,*spbx_switch4,*spbx_switch5;
    //QPushButton *btnSwitch1,*btnSwitch2,*btnSwitch3,*btnSwitch4,*btnSwitch5;
    QLineEdit *lineEdit_s1_Fov0,*lineEdit_s1_Fov1,*lineEdit_s1_Fov2,*lineEdit_s1_Fov3,*lineEdit_s1_Fov4,
              *lineEdit_s1_Fov5,*lineEdit_s1_Fov6,*lineEdit_s1_Fov7,*lineEdit_s1_Fov8,*lineEdit_s1_Fov9,
              *lineEdit_s1_Fov10,*lineEdit_s1_Fov11,*lineEdit_s1_Fov12,*lineEdit_s1_Fov13,*lineEdit_s1_Fov14;
    QString sensor_switch_s1[15]={"FOV1","FOV1的靶心x","FOV1的靶心y","FOV2","FOV2的靶心x","FOV2的靶心y","FOV3","FOV3的靶心x","FOV3的靶心y","FOV4","FOV4的靶心x","FOV4的靶心y","FOV5","FOV5的靶心x","FOV5的靶心y"};
    QComboBox *fovclass;
    //连续视场参数
    QLineEdit *lineEdit_continueRadio,*lineEdit_continueResolution,*lineEdit_continueResolution2;
    QSpinBox *spby1,*spby2,*spby3,*spby4,*spby5,*spby6,*spby7, *spby8,*spby9, *spby10,*spby11, *spby12,*spby13;
    QSpinBox *spbx1,*spbx2,*spbx3,*spbx4,*spbx5,*spbx6,*spbx7,*spbx8,*spbx9,*spbx10,*spbx11,*spbx12,*spbx13;
    QLineEdit *lEdt1,*lEdt2,*lEdt3,*lEdt4,*lEdt5,*lEdt6,*lEdt7,*lEdt8,*lEdt9,*lEdt10,*lEdt11,*lEdt12,*lEdt13;
    QLineEdit *testfov;
    QLineEdit *fEdt1,*fEdt2,*fEdt3,*fEdt4,*fEdt5,*fEdt6,*fEdt7,*fEdt8,*fEdt9,*fEdt10,*fEdt11,*fEdt12,*fEdt13;

    /*通道2*/
    MyWidget *w_sersor1_sec,*w_seitchField_sec,*w_ContinueField_sec;
    QComboBox *change3_sec,*change2_sec,*change1_sec;
    int current_shichang_sec;
    //固定视场参数
    QSpinBox *sp_sec,*sp2_sec;
    QLineEdit *lineEdit_fieldRadio_sec,*lineEdit_fieldResolution_sec,*lineEdit_FOV_x_sec,*lineEdit_FOV_y_sec,*lineEdit_fieldResolution2_sec,*lEdt_sec;
    QString sensor_s1_sec[7]={"视场模式选择","视场平均比例（y轴/x轴）","分辨率（水平*垂直）","FOV","FOV的靶心X","FOV的靶心Y"};
    //可切换视场参数
    QLineEdit *lineEdit_switchRadio_sec,*lineEdit_switchResolution_sec,*lineEdit_switchResolution2_sec;
    QSpinBox *spby_switch1_sec,*spby_switch2_sec,*spby_switch3_sec,*spby_switch4_sec,*spby_switch5_sec;
    QSpinBox *spbx_switch1_sec,*spbx_switch2_sec,*spbx_switch3_sec,*spbx_switch4_sec,*spbx_switch5_sec;
    QLineEdit *lineEdit_s1_Fov0_sec,*lineEdit_s1_Fov1_sec,*lineEdit_s1_Fov2_sec,*lineEdit_s1_Fov3_sec,*lineEdit_s1_Fov4_sec,
              *lineEdit_s1_Fov5_sec,*lineEdit_s1_Fov6_sec,*lineEdit_s1_Fov7_sec,*lineEdit_s1_Fov8_sec,*lineEdit_s1_Fov9_sec,
              *lineEdit_s1_Fov10_sec,*lineEdit_s1_Fov11_sec,*lineEdit_s1_Fov12_sec,*lineEdit_s1_Fov13_sec,*lineEdit_s1_Fov14_sec;
    QString sensor_switch_s1_sec[15]={"FOV1","FOV1的靶心x","FOV1的靶心y","FOV2","FOV2的靶心x","FOV2的靶心y","FOV3","FOV3的靶心x","FOV3的靶心y","FOV4","FOV4的靶心x","FOV4的靶心y","FOV5","FOV5的靶心x","FOV5的靶心y"};
    QComboBox *fovclass_sec;
    //连续视场参数
    QLineEdit *lineEdit_continueRadio_sec,*lineEdit_continueResolution_sec,*lineEdit_continueResolution2_sec;
    QSpinBox *spby1_sec,*spby2_sec,*spby3_sec,*spby4_sec,*spby5_sec,*spby6_sec,*spby7_sec, *spby8_sec,*spby9_sec, *spby10_sec,*spby11_sec, *spby12_sec,*spby13_sec;
    QSpinBox *spbx1_sec,*spbx2_sec,*spbx3_sec,*spbx4_sec,*spbx5_sec,*spbx6_sec,*spbx7_sec,*spbx8_sec,*spbx9_sec,*spbx10_sec,*spbx11_sec,*spbx12_sec,*spbx13_sec;
    QLineEdit *lEdt1_sec,*lEdt2_sec,*lEdt3_sec,*lEdt4_sec,*lEdt5_sec,*lEdt6_sec,*lEdt7_sec,*lEdt8_sec,*lEdt9_sec,*lEdt10_sec,*lEdt11_sec,*lEdt12_sec,*lEdt13_sec;
    QLineEdit *testfov_sec;
    QLineEdit *fEdt1_sec,*fEdt2_sec,*fEdt3_sec,*fEdt4_sec,*fEdt5_sec,*fEdt6_sec,*fEdt7_sec,*fEdt8_sec,*fEdt9_sec,*fEdt10_sec,*fEdt11_sec,*fEdt12_sec,*fEdt13_sec;

    /*通道3*/
    MyWidget *w_sersor1_thi,*w_seitchField_thi,*w_ContinueField_thi;
    QComboBox *change3_thi,*change2_thi,*change1_thi;
    int current_shichang_thi;
    //固定视场参数
    QSpinBox *sp_thi,*sp2_thi;
    QLineEdit *lineEdit_fieldRadio_thi,*lineEdit_fieldResolution_thi,*lineEdit_FOV_x_thi,*lineEdit_FOV_y_thi,*lineEdit_fieldResolution2_thi,*lEdt_thi;
    QString sensor_s1_thi[7]={"视场模式选择","视场平均比例（y轴/x轴）","分辨率（水平*垂直）","FOV","FOV的靶心X","FOV的靶心Y"};
    //可切换视场参数
    QLineEdit *lineEdit_switchRadio_thi,*lineEdit_switchResolution_thi,*lineEdit_switchResolution2_thi;
    QSpinBox *spby_switch1_thi,*spby_switch2_thi,*spby_switch3_thi,*spby_switch4_thi,*spby_switch5_thi;
    QSpinBox *spbx_switch1_thi,*spbx_switch2_thi,*spbx_switch3_thi,*spbx_switch4_thi,*spbx_switch5_thi;
    QLineEdit *lineEdit_s1_Fov0_thi,*lineEdit_s1_Fov1_thi,*lineEdit_s1_Fov2_thi,*lineEdit_s1_Fov3_thi,*lineEdit_s1_Fov4_thi,
              *lineEdit_s1_Fov5_thi,*lineEdit_s1_Fov6_thi,*lineEdit_s1_Fov7_thi,*lineEdit_s1_Fov8_thi,*lineEdit_s1_Fov9_thi,
              *lineEdit_s1_Fov10_thi,*lineEdit_s1_Fov11_thi,*lineEdit_s1_Fov12_thi,*lineEdit_s1_Fov13_thi,*lineEdit_s1_Fov14_thi;
    QString sensor_switch_s1_thi[15]={"FOV1","FOV1的靶心x","FOV1的靶心y","FOV2","FOV2的靶心x","FOV2的靶心y","FOV3","FOV3的靶心x","FOV3的靶心y","FOV4","FOV4的靶心x","FOV4的靶心y","FOV5","FOV5的靶心x","FOV5的靶心y"};
    QComboBox *fovclass_thi;
    //连续视场参数
    QLineEdit *lineEdit_continueRadio_thi,*lineEdit_continueResolution_thi,*lineEdit_continueResolution2_thi;
    QSpinBox *spby1_thi,*spby2_thi,*spby3_thi,*spby4_thi,*spby5_thi,*spby6_thi,*spby7_thi, *spby8_thi,*spby9_thi, *spby10_thi,*spby11_thi, *spby12_thi,*spby13_thi;
    QSpinBox *spbx1_thi,*spbx2_thi,*spbx3_thi,*spbx4_thi,*spbx5_thi,*spbx6_thi,*spbx7_thi,*spbx8_thi,*spbx9_thi,*spbx10_thi,*spbx11_thi,*spbx12_thi,*spbx13_thi;
    QLineEdit *lEdt1_thi,*lEdt2_thi,*lEdt3_thi,*lEdt4_thi,*lEdt5_thi,*lEdt6_thi,*lEdt7_thi,*lEdt8_thi,*lEdt9_thi,*lEdt10_thi,*lEdt11_thi,*lEdt12_thi,*lEdt13_thi;
    QLineEdit *testfov_thi;
    QLineEdit *fEdt1_thi,*fEdt2_thi,*fEdt3_thi,*fEdt4_thi,*fEdt5_thi,*fEdt6_thi,*fEdt7_thi,*fEdt8_thi,*fEdt9_thi,*fEdt10_thi,*fEdt11_thi,*fEdt12_thi,*fEdt13_thi;

    /*通道4*/
    MyWidget *w_sersor1_fou,*w_seitchField_fou,*w_ContinueField_fou;
    QComboBox *change3_fou,*change2_fou,*change1_fou;
    int current_shichang_fou;
    //固定视场参数
    QSpinBox *sp_fou,*sp2_fou;
    QLineEdit *lineEdit_fieldRadio_fou,*lineEdit_fieldResolution_fou,*lineEdit_FOV_x_fou,*lineEdit_FOV_y_fou,*lineEdit_fieldResolution2_fou,*lEdt_fou;
    QString sensor_s1_fou[7]={"视场模式选择","视场平均比例（y轴/x轴）","分辨率（水平*垂直）","FOV","FOV的靶心X","FOV的靶心Y"};
    //可切换视场参数
    QLineEdit *lineEdit_switchRadio_fou,*lineEdit_switchResolution_fou,*lineEdit_switchResolution2_fou;
    QSpinBox *spby_switch1_fou,*spby_switch2_fou,*spby_switch3_fou,*spby_switch4_fou,*spby_switch5_fou;
    QSpinBox *spbx_switch1_fou,*spbx_switch2_fou,*spbx_switch3_fou,*spbx_switch4_fou,*spbx_switch5_fou;
    QLineEdit *lineEdit_s1_Fov0_fou,*lineEdit_s1_Fov1_fou,*lineEdit_s1_Fov2_fou,*lineEdit_s1_Fov3_fou,*lineEdit_s1_Fov4_fou,
              *lineEdit_s1_Fov5_fou,*lineEdit_s1_Fov6_fou,*lineEdit_s1_Fov7_fou,*lineEdit_s1_Fov8_fou,*lineEdit_s1_Fov9_fou,
              *lineEdit_s1_Fov10_fou,*lineEdit_s1_Fov11_fou,*lineEdit_s1_Fov12_fou,*lineEdit_s1_Fov13_fou,*lineEdit_s1_Fov14_fou;
    QString sensor_switch_s1_fou[15]={"FOV1","FOV1的靶心x","FOV1的靶心y","FOV2","FOV2的靶心x","FOV2的靶心y","FOV3","FOV3的靶心x","FOV3的靶心y","FOV4","FOV4的靶心x","FOV4的靶心y","FOV5","FOV5的靶心x","FOV5的靶心y"};
    QComboBox *fovclass_fou;
    //连续视场参数
    QLineEdit *lineEdit_continueRadio_fou,*lineEdit_continueResolution_fou,*lineEdit_continueResolution2_fou;
    QSpinBox *spby1_fou,*spby2_fou,*spby3_fou,*spby4_fou,*spby5_fou,*spby6_fou,*spby7_fou, *spby8_fou,*spby9_fou, *spby10_fou,*spby11_fou, *spby12_fou,*spby13_fou;
    QSpinBox *spbx1_fou,*spbx2_fou,*spbx3_fou,*spbx4_fou,*spbx5_fou,*spbx6_fou,*spbx7_fou,*spbx8_fou,*spbx9_fou,*spbx10_fou,*spbx11_fou,*spbx12_fou,*spbx13_fou;
    QLineEdit *lEdt1_fou,*lEdt2_fou,*lEdt3_fou,*lEdt4_fou,*lEdt5_fou,*lEdt6_fou,*lEdt7_fou,*lEdt8_fou,*lEdt9_fou,*lEdt10_fou,*lEdt11_fou,*lEdt12_fou,*lEdt13_fou;
    QLineEdit *testfov_fou;
    QLineEdit *fEdt1_fou,*fEdt2_fou,*fEdt3_fou,*fEdt4_fou,*fEdt5_fou,*fEdt6_fou,*fEdt7_fou,*fEdt8_fou,*fEdt9_fou,*fEdt10_fou,*fEdt11_fou,*fEdt12_fou,*fEdt13_fou;

    /*通道5*/
    MyWidget *w_sersor1_fif,*w_seitchField_fif,*w_ContinueField_fif;
    QComboBox *change3_fif,*change2_fif,*change1_fif;
    int current_shichang_fif;
    //固定视场参数
    QSpinBox *sp_fif,*sp2_fif;
    QLineEdit *lineEdit_fieldRadio_fif,*lineEdit_fieldResolution_fif,*lineEdit_FOV_x_fif,*lineEdit_FOV_y_fif,*lineEdit_fieldResolution2_fif,*lEdt_fif;
    QString sensor_s1_fif[7]={"视场模式选择","视场平均比例（y轴/x轴）","分辨率（水平*垂直）","FOV","FOV的靶心X","FOV的靶心Y"};
    //可切换视场参数
    QLineEdit *lineEdit_switchRadio_fif,*lineEdit_switchResolution_fif,*lineEdit_switchResolution2_fif;
    QSpinBox *spby_switch1_fif,*spby_switch2_fif,*spby_switch3_fif,*spby_switch4_fif,*spby_switch5_fif;
    QSpinBox *spbx_switch1_fif,*spbx_switch2_fif,*spbx_switch3_fif,*spbx_switch4_fif,*spbx_switch5_fif;
    QLineEdit *lineEdit_s1_Fov0_fif,*lineEdit_s1_Fov1_fif,*lineEdit_s1_Fov2_fif,*lineEdit_s1_Fov3_fif,*lineEdit_s1_Fov4_fif,
              *lineEdit_s1_Fov5_fif,*lineEdit_s1_Fov6_fif,*lineEdit_s1_Fov7_fif,*lineEdit_s1_Fov8_fif,*lineEdit_s1_Fov9_fif,
              *lineEdit_s1_Fov10_fif,*lineEdit_s1_Fov11_fif,*lineEdit_s1_Fov12_fif,*lineEdit_s1_Fov13_fif,*lineEdit_s1_Fov14_fif;
    QString sensor_switch_s1_fif[15]={"FOV1","FOV1的靶心x","FOV1的靶心y","FOV2","FOV2的靶心x","FOV2的靶心y","FOV3","FOV3的靶心x","FOV3的靶心y","FOV4","FOV4的靶心x","FOV4的靶心y","FOV5","FOV5的靶心x","FOV5的靶心y"};
    QComboBox *fovclass_fif;
    //连续视场参数
    QLineEdit *lineEdit_continueRadio_fif,*lineEdit_continueResolution_fif,*lineEdit_continueResolution2_fif;
    QSpinBox *spby1_fif,*spby2_fif,*spby3_fif,*spby4_fif,*spby5_fif,*spby6_fif,*spby7_fif, *spby8_fif,*spby9_fif, *spby10_fif,*spby11_fif, *spby12_fif,*spby13_fif;
    QSpinBox *spbx1_fif,*spbx2_fif,*spbx3_fif,*spbx4_fif,*spbx5_fif,*spbx6_fif,*spbx7_fif,*spbx8_fif,*spbx9_fif,*spbx10_fif,*spbx11_fif,*spbx12_fif,*spbx13_fif;
    QLineEdit *lEdt1_fif,*lEdt2_fif,*lEdt3_fif,*lEdt4_fif,*lEdt5_fif,*lEdt6_fif,*lEdt7_fif,*lEdt8_fif,*lEdt9_fif,*lEdt10_fif,*lEdt11_fif,*lEdt12_fif,*lEdt13_fif;
    QLineEdit *testfov_fif;
    QLineEdit *fEdt1_fif,*fEdt2_fif,*fEdt3_fif,*fEdt4_fif,*fEdt5_fif,*fEdt6_fif,*fEdt7_fif,*fEdt8_fif,*fEdt9_fif,*fEdt10_fif,*fEdt11_fif,*fEdt12_fif,*fEdt13_fif;

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
    QComboBox *c,*CBox_color,*CBox_font,*CBox_font_size;
    QPushButton *btn_osd1_default,*btn_osd1_update;
    MyWidget *w_osd1;
    QCheckBox *checkBox;
    QLineEdit *osd1_pos_x,*osd1_pos_y,*osd1_lineEdit_label,*osd1_lineEdit_context,*osd1_lineEdit_font,*osd1_lineEdit_color,*osd1_lineEdit_transparency;
    QString osd_s[9]={"使能","x位置","y位置","标签","内容","字体","字体大小","颜色","透明度"};

    /*软件升级*/
    RcvUSocketdata  *thread_usocket;
    QLineEdit *upgrade_ip;
    QLineEdit *upgrade_port;
    QFile  file,fpgafile;  // 文件对象
    QString fileName,fpgafileName; //文件名字
    qint64 filesize,fpgafilesize; // 文件大小
    qint64 sendsize,fpgasendsize;  // 已经发送的数据大小
	bool socketIsconnect=false;
};
extern MainWindow *pthis;
#endif // MAINWINDOW_H
