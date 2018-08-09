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
    void usocket_Read_Data();

    /*计算圆边界值*/
    void calculationCircle(int center_a, int center_b, int x, int y);
    void btnSensor1SwitchSlot();
    void btnSensor2ContinueSlot();

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
    void showAlg();
    void showAlg2();
    void showAlg3();
    void showCapture1();
    void showCapture2();
    void showCapture3();
    void showOther();

    /*系统配置槽函数*/
    void btnSerialSlot();
    void btnNetSlot();
    void toNetSlot(int i);
    void btnDownSlot();
    void btnUpSlot();
    void btnSaveSlot();
    void btnUpdate();

    /*相机配置槽函数*/
    void btn_default_Slot();
    void btn_default_Slot2();
    void btn_default_Slot3();
    void tosersor_fix(int i);
    void toSensor_switch(int i);
    void tosersor_continue(int i);

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
    void CBox_sysCfg_Slot(int i);

    /*平台控制*/
    void btn_Jos_Default_Slot();
    void btn_Jos_Update_Slot();
    void lEdt_Jos1_Slot();
    void lEdt_Jos2_Slot();
    void lEdt_Jos3_Slot();
    void lEdt_Jos4_Slot();
    void lEdt_Jos5_Slot();
    void lEdt_Jos6_Slot();

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
    void CBox_View_Slot(int i);
    void CBox_osd_color_Slot(int i);
    void lEdt_transparency_Slot();

    /*捕获框设置*/
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

    void lEdt_drawLine_0();
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

    //

    void on_btn_ok_clicked();

    void on_btnAutoCheck_clicked();

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

private:
    Ui::MainWindow *ui;
    Jos j;
    int value_x=960;
    int value_y=540;
    int value_check=0;
    int value_search=0;



    /*定时器*/
    QTimer *time;

//    QPushButton *blank;
//    QPushButton *btn_sensor_fix;
//    QPushButton *btn_sensor_switch;
//    QPushButton *btn_sersor_continue;

        QLineEdit *lineEdit;
        int sersor_count=0;
    /**/
    QTcpSocket *socket;
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
    int a, b, m_dragging,b_center,a_center,old_x,old_y;
    int mousePress = 0;
   // QMutex send_mutex;
    unsigned char send_arr[1080];
    unsigned short sectrk_x = 0;
    unsigned short sectrk_y = 0;

    /*系统配置*/
    QWidget *w_config,w_config_serial,w_config_net;
    QStackedLayout *s;
    QComboBox *box_serial,*box_baud,*box_check,*box_data,*box_stop;
    QGroupBox *groupBox_trackboard;
    QPushButton *btn_serial_NO,*btn_serial_OK,*btn_net_OK,*btn_net_NO;
    QLineEdit *lineEdit_port,*lineEdit_ip;

    /*平台配置*/
    QWidget *w_plat;
    QGroupBox *gbox_Jos,*gbox_PID,*gbox_plat;
    QLineEdit *josDead_lineEdt,*josPoint_lineEdt,*josInputG_x,*josInputG_y,
              *josOutputG_x,*josOutputG_y;
    QComboBox *outMode;
    QLineEdit *kp1_pid,*ki1_pid,*kd1_pid,*k1,*kp2_pid,*ki2_pid,*kd2_pid,*k2;
    QLineEdit *bleedx_plat,*bleedy_plat,*mx_plat,*my_plat,*deadx_plat,*deady_plat,*a_plat;
     QString string_outMode[7]={"Zero","JoystickInput","ShapedAndGained","ShapedAndGainedAndIntegrated","DeterminedByPostion","ZeroInitFilter","DeterminedByIncomingPlatformData"};
    QString jos_s[6]={"手柄死区","手柄拐点","手柄x轴输入增益","手柄y轴输入增益","摇杆平台x输出增益","摇杆平台y轴输出增益"};
    QString pid_s[8]={"PIDx轴比例系数Kp","PIDx轴积分系数Ki","PIDx轴微分系数Kd","PIDx轴滤波系数k","PIDy比例系数Kp","PIDy积分系数Ki","PIDy微分系数Kd","PIDy轴滤波系数k"};
    QString plat_s[8]={"平台x轴Bleed率","平台y轴Bleed率","x轴最大速度","y轴最大速度","x方向死区","y方向死区","平台控制曲线化因子a","平台输出模式"};

    /*相机配置*/
    void on_btn_right_clicked();

    /*通道1*/
    QWidget *w_sersor1,*w_seitchField,*w_ContinueField;
    QStackedLayout *sta;
    QComboBox *change3,*change2,*change1,*change;
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
    //连续视场参数
    QLineEdit *lineEdit_continueRadio,*lineEdit_continueResolution,*lineEdit_continueResolution2;
    QSpinBox *spby1,*spby2,*spby3,*spby4,*spby5,*spby6,*spby7, *spby8,*spby9, *spby10,*spby11, *spby12,*spby13;
    QSpinBox *spbx1,*spbx2,*spbx3,*spbx4,*spbx5,*spbx6,*spbx7,*spbx8,*spbx9,*spbx10,*spbx11,*spbx12,*spbx13;
    QLineEdit *lEdt1,*lEdt2,*lEdt3,*lEdt4,*lEdt5,*lEdt6,*lEdt7,*lEdt8,*lEdt9,*lEdt10,*lEdt11,*lEdt12,*lEdt13;
    //    QLineEdit *lineEdit_c0,*lineEdit_c1,*lineEdit_c2,*lineEdit_c3,*lineEdit_c4,*lineEdit_c5,
//              *lineEdit_c6,*lineEdit_c7,*lineEdit_c8,*lineEdit_c9,*lineEdit_c10,*lineEdit_c11,
//              *lineEdit_c12,*lineEdit_c13,*lineEdit_c14,*lineEdit_c15,*lineEdit_c16,*lineEdit_c17,
//              *lineEdit_c18,*lineEdit_c19,*lineEdit_c20,*lineEdit_c21,*lineEdit_c22,*lineEdit_c23,
//              *lineEdit_c24,*lineEdit_c25,*lineEdit_c26;
//    QString sensor_Continue_s1[26]={"第1个采样点靶心x","第1个采样点靶心y","第2个采样点靶心x","第2个采样点靶心y","第3个采样点靶心x","第3个采样点靶心y","第4个采样点靶心x","第4个采样点靶心y","第5个采样点靶心x","第5个采样点靶心y","第6个采样点靶心x","第6个采样点靶心y",
//                                   "第7个采样点靶心x","第7个采样点靶心y","第8个采样点靶心x","第8个采样点靶心y","第9个采样点靶心x","第9个采样点靶心y","第10个采样点靶心x","第10个采样点靶心y","第11个采样点靶心x","第11个采样点靶心y","第12个采样点靶心x","第12个采样点靶心y",
//                                   "第13个采样点靶心x","第13个采样点靶心y"};


    /*UTC*/
    QPushButton *btn_utc1_default,*btn_utc1_update,*btn_utc2_default,*btn_utc2_update,*btn_utc3_default,*btn_utc3_update;
    QWidget *utc1,*utc2,*utc3;
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
    QString utc_s1[16]={"occlusion_thred","retry_acq_thred","up_factor","res_distance","res_area","gapframe","enhEnable","cliplimit","dictEnable","moveX","moveY","moveX2","moveY2","segPixelX","segPixelY","algOsdRect Enable"};
    QString utc_s2[16]={"ScalerLarge","ScalerMid","ScalerSmall","Scatter","ratio","FilterEnable","BigSecEnable","SalientThred","ScalerEnable","DynamicRatioEnable","acqSize.width","acqSize.height","TrkAim 4:3 Enable","SceneMVEnable","BackTrackEnable","bAveTrkPos"};
    QString utc_s3[16]={"fTau","buildFrms","LostFrmThred","histMvThred","detectFrms","stillFrms","stillThred","bKalmanFilter","xMVThred","yMVThred","xStillThred","yStillThred","slopeThred","kalmanHistThred","kalmanCoefQ","kalmanCoefR"};

    /*捕获框配置*/
    QWidget *w_capture1,*w_capture2,*w_capture3;
    QPushButton *btn_capture_default,*btn_capture_update,*btn_capture2_default,*btn_capture2_update,*btn_capture3_default,*btn_capture3_update;
    QLineEdit *cap_0_w,*cap_1_w,*cap_2_w,*cap_3_w,*cap_4_w,*cap_5_w,*cap_0_h,*cap_1_h,*cap_2_h,*cap_3_h,*cap_4_h,*cap_5_h;
    QLineEdit *bomen_0_w,*bomen_1_w,*bomen_2_w,*bomen_3_w,*bomen_4_w,*bomen_5_w,*bomen_0_h,*bomen_1_h,*bomen_2_h,*bomen_3_h,*bomen_4_h,*bomen_5_h;
    QLineEdit *drawLine_0,*drawLine_1,*drawLine_2,*drawLine_3,*drawLine_4,*drawLine_5;
    QString string_cap[12]={"通道0捕获框宽","通道1捕获框宽","通道2捕获框宽","通道3捕获框宽","通道4捕获框宽","通道5捕获框宽","通道0捕获框高","通道1捕获框高","通道2捕获框高","通道3捕获框高","通道4捕获框高","通道5捕获框高"};
    QString string_bomen[12]={"通道0波门宽","通道1波门宽","通道2波门宽","通道3波门宽","通道4波门宽","通道5波门宽","通道0波门高","通道1波门高","通道2波门高","通道3波门高","通道4波门高","通道5波门高"};
    QString string_drawLine[6]={"画线显示否","画线的颜色","十字宽","十字高","画中画十字宽","画中画十字高"};
    /*OSD*/
    QComboBox *c,*CBox_color,*CBox_font,*CBox_font_size;
    QPushButton *btn_osd1_default,*btn_osd1_update;
    QWidget *w_osd1;
    QCheckBox *checkBox;
    QLineEdit *osd1_pos_x,*osd1_pos_y,*osd1_lineEdit_label,*osd1_lineEdit_context,*osd1_lineEdit_font,*osd1_lineEdit_color,*osd1_lineEdit_transparency;
    QString osd_s[9]={"使能","x位置","y位置","标签","内容","字体","字体大小","颜色","透明度"};

    /*软件升级*/
    RcvUSocketdata  *thread_usocket;
    QLineEdit *upgrade_ip;
    QLineEdit *upgrade_port;
    QFile  file;  // 文件对象
    QString fileName; //文件名字
    qint64 filesize; // 文件大小
    qint64 sendsize;  // 已经发送的数据大小
    QByteArray usocketRcvData;

};
extern MainWindow *pthis;
#endif // MAINWINDOW_H
