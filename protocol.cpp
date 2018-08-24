#include "mainwindow.h"
#include "ui_mainwindow.h"

typedef struct resp
{
    unsigned char autocheck;
    unsigned char sensor;
    unsigned char sensor_bind;
    unsigned char trk;
    unsigned char mmt;
    unsigned char mmtselect;
    unsigned char enh;
    unsigned char posmove;
    unsigned char axismove;
    unsigned char zoom;
    unsigned char sectrk;
    unsigned char mtd;
    unsigned char pinp;
    unsigned char sensor_trans;
    unsigned char vframerate;
    unsigned char vquality;
    unsigned char osdcolor;
    unsigned char osdfont;
    unsigned char osdsize;
    unsigned char setconfig;
    unsigned char getconfig;
    unsigned char downconfig;
    unsigned char saveconfig;
    unsigned char joyskeyboard;

}resp_t;
resp_t respstat = {0};
extern  unsigned char output_array[1024];
extern  unsigned char output_array_6[1024];
extern  unsigned char output_array_7[1024];
extern  unsigned char output_array_8[1024];
extern int data_length;

QByteArray MainWindow::string2hex(QString str, bool &flag)
{
    QByteArray senddata;
    int hexdata,lowHexdata;
    int hexdatalen=0;
    int len=str.length();
    char lstr,hstr;
    senddata.resize(len/2);
    for(int i=0;i<len;i++){
        hstr=str[i].toLatin1();
        if(hstr==' '){
            continue;
        }
        i++;
        lstr=str[i].toLatin1();
        if(lstr==' '|| i>=len){
            hexdata=0;
            lowHexdata=convertHex2Char(hstr);
        }else{
            hexdata=convertHex2Char(hstr);
            lowHexdata=convertHex2Char(lstr);
        }
        if((hexdata== -1) || (lowHexdata== -1)){
            flag=false;
            senddata.resize(hexdatalen);
            return senddata;
        }else{
            hexdata=hexdata*16+lowHexdata;

        }
        senddata[hexdatalen]=(char)hexdata;
         hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

char MainWindow::convertHex2Char(char ch)
{
    if((ch>='0')&& (ch<='9')){
        return ch-0x30;
    }else if((ch>='A') && (ch<='F')){
        return ch-'A'+10;
    }else if((ch>='a') && (ch<='f')){
        return ch-'a'+10;
    }else{
        return (-1);
    }
}

void MainWindow::send_oneframe(int length)
{
    int len=length+5;
    send_arr[0] = 0xEB;
    send_arr[1] = 0x53;
    send_arr[2] = length&0xff;
    send_arr[3] = (length>>8)&0xff;
    unsigned char sum=0;
    for(int n = 1; n<len-1; n++) {
        sum ^= send_arr[n];
     }
    send_arr[len-1] = sum;

    QString str1;
    for(int m = 0; m< len; m++){
        str1 += QString("%1").arg(send_arr[m]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
    }
    bool checkf = true;
    sndData_02 = string2hex(str1,checkf);
    sendNum += sndData_02.length();
    memset(&respstat, 0, sizeof(respstat));
    if(checkf == true){
        if(1 == connect_flag)
        {
            serialPort_command->write(sndData_02);
        }
        else if(2 == connect_flag)
        {
            socket->write(sndData_02);//通过网口发送数据
            socket->flush();
        }
    }
    //ui->textEdit_2->append(str1);
}
void MainWindow::output_to_label(int i)//解析下位机的反馈信息,从串口读到正确的一帧数据的时候执行此函数。
{
    float value_i;
 QString msg;
     QByteArray ba;
    bool osd_judgment=(output_array[1] == 0x07) || (output_array[1] == 0x08)|| (output_array[1] == 0x09)||(output_array[1] == 0x0a)\
                      ||(output_array[1] == 0x0b) || (output_array[1] == 0x0c)|| (output_array[1] == 0x0d)||(output_array[1] == 0x0e)\
                      ||(output_array[1] == 0x0f) || (output_array[1] == 0x10)|| (output_array[1] == 0x11)||(output_array[1] == 0x12)\
                      ||(output_array[1] == 0x13) || (output_array[1] == 0x14)|| (output_array[1] == 0x15)||(output_array[1] == 0x16)\
                      ||(output_array[1] == 0x1D) || (output_array[1] == 0x1e)|| (output_array[1] == 0x1f)||(output_array[1] == 0x20)\
                      ||(output_array[1] == 0x21) || (output_array[1] == 0x22)|| (output_array[1] == 0x23)||(output_array[1] == 0x24)\
                      ||(output_array[1] == 0x25) || (output_array[1] == 0x26)|| (output_array[1] == 0x27)||(output_array[1] == 0x28)\
                      ||(output_array[1] == 0x29) || (output_array[1] == 0x2a)|| (output_array[1] == 0x2b)||(output_array[1] == 0x2c);
    if(osd_judgment && (output_array[2]==0x03)){
      QByteArray dd((char*)output_array+3, data_length-3);
      ba=dd;

    }else{
        memcpy(&value_i,output_array+3,4);
    }


    if(i==0x31){
        switch (output_array[1]) {

            case 0x01:
                if(output_array[2]==0x01){
                    josDead_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x02){
                    josPoint_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x03){
                    josInputG_x->setText(QString::number(value_i));
                }else if(output_array[2]==0x04){
                    josInputG_y->setText(QString::number(value_i));
                } else if(output_array[2]==0x05){
                    josPoint_lineEdt2->setText(QString::number(value_i));
                }else if(output_array[2]==0x06){
                    josInputG_x2->setText(QString::number(value_i));
                }else if(output_array[2]==0x07){
                    josInputG_y2->setText(QString::number(value_i));
                }
                break;
            case 0x02:
                switch (output_array[2]){
                    case 0x01:
                        kp1_pid->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        ki1_pid->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        kd1_pid->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        k1->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        kp2_pid->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        ki2_pid->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        kd2_pid->setText(QString::number(value_i));
                        break;
                    case 0x08:
                        k2->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x03:
                switch (output_array[2]){
                    case 0x01:
                        bleedx_plat->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        bleedy_plat->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        mx_plat->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        my_plat->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        deadx_plat->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        deady_plat->setText(QString::number(value_i));
                        break;
                    case 0x08:
                        a_plat->setText(QString::number(value_i));
                         break;
                }
                break;
            case 0x04:
            switch (output_array[2]){
                case 0x00:
                    utc1_l0->setText(QString::number(value_i));
                    break;
                case 0x01:
                    utc1_l1->setText(QString::number(value_i));
                    break;
                case 0x02:
                    utc1_l2->setText(QString::number(value_i));
                    break;
                case 0x03:
                    utc1_l3->setText(QString::number(value_i));
                    break;
                case 0x04:
                    utc1_l4->setText(QString::number(value_i));
                    break;
                case 0x05:
                    utc1_l5->setText(QString::number(value_i));
                    break;
                case 0x06:
                    utc1_l6->setText(QString::number(value_i));
                    break;
                case 0x07:
                    utc1_l7->setText(QString::number(value_i));
                     break;
                case 0x08:
                    utc1_l8->setText(QString::number(value_i));
                    break;
                case 0x09:
                    utc1_l9->setText(QString::number(value_i));
                    break;
                case 0x0a:
                    utc1_l10->setText(QString::number(value_i));
                    break;
                case 0x0b:
                    utc1_l11->setText(QString::number(value_i));
                    break;
                case 0x0c:
                    utc1_l12->setText(QString::number(value_i));
                    break;
                case 0x0d:
                    utc1_l13->setText(QString::number(value_i));
                    break;
                case 0x0e:
                    utc1_l14->setText(QString::number(value_i));
                     break;
                case 0x0f:
                    utc1_l15->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x05:
                 switch (output_array[2]){
                    case 0x00:
                        utc2_l0->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        utc2_l1->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        utc2_l2->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        utc2_l3->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        utc2_l4->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        utc2_l5->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        utc2_l6->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        utc2_l7->setText(QString::number(value_i));
                         break;
                    case 0x08:
                        utc2_l8->setText(QString::number(value_i));
                        break;
                    case 0x09:
                        utc2_l9->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        utc2_l10->setText(QString::number(value_i));
                        break;
                    case 0x0b:
                        utc2_l11->setText(QString::number(value_i));
                        break;
                    case 0x0c:
                        utc2_l12->setText(QString::number(value_i));
                        break;
                    case 0x0d:
                        utc2_l13->setText(QString::number(value_i));
                        break;
                    case 0x0e:
                        utc2_l14->setText(QString::number(value_i));
                         break;
                    case 0x0f:
                        utc2_l15->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x06:
                switch (output_array[2]){
                    case 0x00:
                        utc3_l0->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        utc3_l1->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        utc3_l2->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        utc3_l3->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        utc3_l4->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        utc3_l5->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        utc3_l6->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        utc3_l7->setText(QString::number(value_i));
                         break;
                    case 0x08:
                        utc3_l8->setText(QString::number(value_i));
                        break;
                    case 0x09:
                        utc3_l9->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        utc3_l10->setText(QString::number(value_i));
                        break;
                    case 0x0b:
                        utc3_l11->setText(QString::number(value_i));
                        break;
                    case 0x0c:
                        utc3_l12->setText(QString::number(value_i));
                        break;
                    case 0x0d:
                        utc3_l13->setText(QString::number(value_i));
                        break;
                    case 0x0e:
                        utc3_l14->setText(QString::number(value_i));
                         break;
                    case 0x0f:
                        utc3_l15->setText(QString::number(value_i));
                        break;
                }
                break;

            case 0x07:
                c->setCurrentIndex(0);
                switch (output_array[2]){
                    case 0x00:
                         if(value_i==0x00){
                           checkBox->setChecked(true);
                        }else{
                           checkBox->setChecked(false);
                         }
                        break;
                    case 0x01:
                         osd1_pos_x->setText(QString::number(value_i));
                        break;
                    case 0x02:
                         osd1_pos_y->setText(QString::number(value_i));
                        break;
					case 0x03:
                         osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                        break;
                    case 0x05:
                        CBox_color->setCurrentIndex(value_i-1);
                        break;
                    case 0x06:
                       osd1_lineEdit_transparency->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x08:
                c->setCurrentIndex(1);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x09:
                c->setCurrentIndex(2);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x0a:
                c->setCurrentIndex(3);
                switch (output_array[2]){
                    case 0x00:
                         if(value_i==0x00){
                           checkBox->setChecked(true);
                        }else{
                           checkBox->setChecked(false);
                         }
                        break;
                    case 0x01:
                         osd1_pos_x->setText(QString::number(value_i));
                        break;
                    case 0x02:
                         osd1_pos_y->setText(QString::number(value_i));
                        break;
                    case 0x03:
                         osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                        break;
                    case 0x05:
                        CBox_color->setCurrentIndex(value_i);
                        break;
                    case 0x06:
                       osd1_lineEdit_transparency->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x0b:
                c->setCurrentIndex(4);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x0c:
                c->setCurrentIndex(5);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x0d:
                c->setCurrentIndex(6);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x0e:
                c->setCurrentIndex(7);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x0f:
                c->setCurrentIndex(8);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x10:
                c->setCurrentIndex(9);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;

            case 0x11:
                c->setCurrentIndex(10);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x12:
                c->setCurrentIndex(11);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x13:
                c->setCurrentIndex(12);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x14:
                c->setCurrentIndex(13);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x15:
                c->setCurrentIndex(14);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x16:
                c->setCurrentIndex(15);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x17:
                    switch(output_array[2]){
                        case 0x00:
                            if(0 == current_shichang)
                                change1->setCurrentIndex(value_i);
                            else if(1 == current_shichang)
                                change2->setCurrentIndex(value_i);
                            else if(2 == current_shichang)
                                change3->setCurrentIndex(value_i);
                            break;
                        case 0x01:
                            if(0 == current_shichang)
                                lineEdit_fieldRadio->setText(QString::number(value_i));
                            else if(1 == current_shichang)
                                lineEdit_switchRadio->setText(QString::number(value_i));
                            else if(2 == current_shichang)
                                lineEdit_continueRadio->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            if(0 == current_shichang)
                                lineEdit_fieldResolution->setText(QString::number(value_i));
                            else if(1 == current_shichang)
                                lineEdit_switchResolution->setText(QString::number(value_i));
                            else if(2 == current_shichang)
                                lineEdit_continueResolution->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            if(0 == current_shichang)
                                lineEdit_fieldResolution2->setText(QString::number(value_i));
                            else if(1 == current_shichang)
                                lineEdit_switchResolution2->setText(QString::number(value_i));
                            else if(2 == current_shichang)
                                lineEdit_continueResolution2->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            lEdt->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            sp->setValue(value_i);
                            break;
                        case 0x06:
                            sp2->setValue(value_i);
                            break;
                    }
                break;
            case 0x18:
                switch(output_array[2]){
                    case 0x00:
                        lineEdit_s1_Fov0->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        spbx_switch1->setValue(value_i);
                        break;
                    case 0x02:
                        spby_switch1->setValue(value_i);
                        break;
                    case 0x03:
                        lineEdit_s1_Fov1->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        spbx_switch2->setValue(value_i);
                        break;
                    case 0x05:
                        spby_switch2->setValue(value_i);
                        break;
                    case 0x06:
                        lineEdit_s1_Fov2->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        spbx_switch3->setValue(value_i);
                        break;
                    case 0x08:
                        spby_switch3->setValue(value_i);
                        break;
                    case 0x09:
                        lineEdit_s1_Fov3->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        spbx_switch4->setValue(value_i);
                        break;
                    case 0x0b:
                        spby_switch4->setValue(value_i);
                        break;
                    case 0x0c:
                        lineEdit_s1_Fov4->setText(QString::number(value_i));
                        break;
                    case 0x0d:
                        spbx_switch5->setValue(value_i);
                        break;
                    case 0x0e:
                        spby_switch5->setValue(value_i);
                        break;
                }
                break;
            case 0x19:
                switch(output_array[2]){
                    case 0x00:
                        lEdt1->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        spbx1->setValue(value_i);
                        break;
                    case 0x02:
                        spby1->setValue(value_i);
                        break;
                    case 0x03:
                        lEdt2->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        spbx2->setValue(value_i);
                        break;
                    case 0x05:
                        spby2->setValue(value_i);
                        break;
                    case 0x06:
                        lEdt3->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        spbx3->setValue(value_i);
                        break;
                    case 0x08:
                        spby3->setValue(value_i);
                        break;
                    case 0x09:
                        lEdt4->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        spbx4->setValue(value_i);
                        break;
                    case 0x0b:
                        spby4->setValue(value_i);
                        break;
                    case 0x0c:
                        lEdt5->setText(QString::number(value_i));
                        break;
                    case 0x0d:
                        spbx5->setValue(value_i);
                        break;
                    case 0x0e:
                        spby5->setValue(value_i);
                        break;
                    case 0x0f:
                        lEdt6->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x1a:
                switch(output_array[2]){
                    case 0x00:
                        spbx6->setValue(value_i);
                        break;
                    case 0x01:
                        spby6->setValue(value_i);
                        break;
                    case 0x02:
                        lEdt7->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        spbx7->setValue(value_i);
                        break;
                    case 0x04:
                        spby7->setValue(value_i);
                        break;
                    case 0x05:
                        lEdt8->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        spbx8->setValue(value_i);
                        break;
                    case 0x07:
                        spby8->setValue(value_i);
                        break;
                    case 0x08:
                        lEdt9->setText(QString::number(value_i));
                        break;
                    case 0x09:
                        spbx9->setValue(value_i);
                        break;
                    case 0x0a:
                        spby9->setValue(value_i);
                        break;
                    case 0x0b:
                        lEdt10->setText(QString::number(value_i));
                        break;
                    case 0x0c:
                        spbx10->setValue(value_i);
                        break;
                    case 0x0d:
                        spby10->setValue(value_i);
                        break;
                    case 0x0e:
                        lEdt11->setText(QString::number(value_i));
                        break;
                    case 0x0f:
                        spbx11->setValue(value_i);
                        break;
                }
                break;
            case 0x1b:
                switch(output_array[2]){
                    case 0x00:
                        spby11->setValue(value_i);
                        break;
                    case 0x01:
                        lEdt12->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        spbx12->setValue(value_i);
                        break;
                    case 0x03:
                        spby12->setValue(value_i);
                        break;
                    case 0x04:
                        lEdt13->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        spbx13->setValue(value_i);
                        break;
                    case 0x06:
                        spby13->setValue(value_i);
                        break;
                }
                break;
            case 0x1c:

                break;
            case 0x1d:
                c->setCurrentIndex(16);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x1e:
                c->setCurrentIndex(17);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x1f:
                c->setCurrentIndex(18);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x20:
                 c->setCurrentIndex(19);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x21:
                c->setCurrentIndex(20);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x22:
                c->setCurrentIndex(21);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x23:
                c->setCurrentIndex(22);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x24:
                c->setCurrentIndex(23);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x25:
                c->setCurrentIndex(24);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x26:
                c->setCurrentIndex(25);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x27:
                c->setCurrentIndex(26);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x28:
                c->setCurrentIndex(27);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x29:
                c->setCurrentIndex(28);
                switch (output_array[2]){
            case 0x00:
                 if(value_i==0x00){
                   checkBox->setChecked(true);
                }else{
                   checkBox->setChecked(false);
                 }
                break;
            case 0x01:
                 osd1_pos_x->setText(QString::number(value_i));
                break;
            case 0x02:
                 osd1_pos_y->setText(QString::number(value_i));
                break;
            case 0x03:
                osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                break;
            case 0x05:
                CBox_color->setCurrentIndex(value_i);
                break;
            case 0x06:
               osd1_lineEdit_transparency->setText(QString::number(value_i));
                break;
        }
                break;
            case 0x2a:
                c->setCurrentIndex(29);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x2b:
                c->setCurrentIndex(30);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x2c:
                c->setCurrentIndex(31);
                switch (output_array[2]){
                case 0x00:
                     if(value_i==0x00){
                       checkBox->setChecked(true);
                    }else{
                       checkBox->setChecked(false);
                     }
                    break;
                case 0x01:
                     osd1_pos_x->setText(QString::number(value_i));
                    break;
                case 0x02:
                     osd1_pos_y->setText(QString::number(value_i));
                    break;
                case 0x03:
                     osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                    break;
                case 0x05:
                    CBox_color->setCurrentIndex(value_i);
                    break;
                case 0x06:
                   osd1_lineEdit_transparency->setText(QString::number(value_i));
                    break;
            }
                break;
            case 0x2d:
                switch(output_array[2]){
                    case 0x00:
                        cap_0_w->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        cap_1_w->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        cap_2_w->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        cap_3_w->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        cap_4_w->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        cap_5_w->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        cap_0_h->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        cap_1_h->setText(QString::number(value_i));
                        break;
                    case 0x08:
                        cap_2_h->setText(QString::number(value_i));
                        break;
                    case 0x09:
                        cap_3_h->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        cap_4_h->setText(QString::number(value_i));
                        break;
                    case 0x0b:
                        cap_5_h->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x2e:
                switch(output_array[2]){
                    case 0x00:
                        bomen_0_w->setText(QString::number(value_i));
                        break;
                    case 0x01:
                        bomen_1_w->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        bomen_2_w->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        bomen_3_w->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        bomen_4_w->setText(QString::number(value_i));
                        break;
                    case 0x06:
                        bomen_0_h->setText(QString::number(value_i));
                        break;
                    case 0x07:
                        bomen_1_h->setText(QString::number(value_i));
                        break;
                    case 0x08:
                        bomen_2_h->setText(QString::number(value_i));
                        break;
                    case 0x09:
                        bomen_3_h->setText(QString::number(value_i));
                        break;
                    case 0x0a:
                        bomen_4_h->setText(QString::number(value_i));
                        break;
                }
                break;
            case 0x2f:
                switch(output_array[2]){
                    case 0x00:
                        if(value_i==0x00)
                        {
                          checkBox_cross->setChecked(false);
                        }
                        else
                        {
                          checkBox_cross->setChecked(true);
                        }
                        break;
                    case 0x01:
                        drawLine_1->setText(QString::number(value_i));
                        break;
                    case 0x02:
                        drawLine_2->setText(QString::number(value_i));
                        break;
                    case 0x03:
                        drawLine_3->setText(QString::number(value_i));
                        break;
                    case 0x04:
                        drawLine_4->setText(QString::number(value_i));
                        break;
                    case 0x05:
                        drawLine_5->setText(QString::number(value_i));
                        break;
                }
                break;
        case 0x30:
                if(output_array[2]==0x00){
                    kx_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x01){
                    ky_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x02){
                    errx_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x03){
                    erry_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x04){
                    time_lineEdt->setText(QString::number(value_i));
                } /*else if(output_array[2]==0x05){
                    dbg5_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x06){
                    dbg6_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x07){
                    dbg7_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x08){
                    dbg8_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==0x09){
                    dbg9_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==10){
                    dbg10_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==11){
                    dbg11_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==12){
                    dbg12_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==13){
                    dbg13_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==14){
                    dbg14_lineEdt->setText(QString::number(value_i));
                }else if(output_array[2]==15){
                    dbg15_lineEdt->setText(QString::number(value_i));
                }*/
                break;
        case 49:
            if(0x00 == output_array[2]){
                speedx1_lineEdt->setText(QString::number(value_i));
            }else if(0x01 == output_array[2]){
                speedx2_lineEdt->setText(QString::number(value_i));
            }else if(0x02 == output_array[2]){
                speedx3_lineEdt->setText(QString::number(value_i));
            }else if(0x03 == output_array[2]){
                speedx4_lineEdt->setText(QString::number(value_i));
            }else if(0x04 == output_array[2]){
                speedx5_lineEdt->setText(QString::number(value_i));
            }else if(0x05 == output_array[2]){
                speedx6_lineEdt->setText(QString::number(value_i));
            }else if(0x06 == output_array[2]){
                speedx7_lineEdt->setText(QString::number(value_i));
            }else if(0x07 == output_array[2]){
                speedx8_lineEdt->setText(QString::number(value_i));
            }else if(0x08 == output_array[2]){
                speedx9_lineEdt->setText(QString::number(value_i));
            }else if(0x09 == output_array[2]){
                speedy1_lineEdt->setText(QString::number(value_i));
            }else if(10 == output_array[2]){
                speedy2_lineEdt->setText(QString::number(value_i));
            }else if(11 == output_array[2]){
                speedy3_lineEdt->setText(QString::number(value_i));
            }else if(12 == output_array[2]){
                speedy4_lineEdt->setText(QString::number(value_i));
            }else if(13 == output_array[2]){
                speedy5_lineEdt->setText(QString::number(value_i));
            }else if(14 == output_array[2]){
                speedy6_lineEdt->setText(QString::number(value_i));
            }else if(15 == output_array[2]){
                speedy7_lineEdt->setText(QString::number(value_i));
            }
            break;
        case 50:
            if(0x00 == output_array[2]){
                speedy8_lineEdt->setText(QString::number(value_i));
            }else if(0x01 == output_array[2]){
                speedy9_lineEdt->setText(QString::number(value_i));
            }
            break;
        default:
                break;
        }
    }
    else if(0x0d == i)
    {
       if(output_array[1] != 0xff)
           read_config(output_array[1]);
    }

      memset(output_array,0,sizeof(output_array));
}
void MainWindow::read_config(int block)
{
    int i = 0;
    switch(block)
    {
        case 1:
            send_read_config(block,1,7);
            break;
        case 2:
            send_read_config(block,1,8);
            break;
        case 3:
            send_read_config(block,1,6);
            send_read_config(block,8,8);
            break;
        case 4:
            send_read_config(block,0,15);
            break;
        case 5:
            send_read_config(block,0,15);
            break;
        case 6:
            send_read_config(block,0,15);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
            send_read_config(block,0,3);
            send_read_config(block,5,6);
            break;
        case 23:
            send_read_config(block,0,6);
            break;
        case 24:
            send_read_config(23,0,3);
            send_read_config(block,0,14);
            break;
        case 25:
            send_read_config(23,0,3);
            send_read_config(block,0,15);
            break;
        case 26:
            send_read_config(23,0,3);
            send_read_config(block,0,15);
            break;
        case 27:
            send_read_config(23,0,3);
            send_read_config(block,0,6);
            break;
        case 28:
            send_read_config(block,0,5);
            break;
        case 46:
            send_read_config(block,0,4);
            send_read_config(block,6,11);
            break;
        case 47:
            send_read_config(block,0,0);
            break;
        case 49:
            send_read_config(block,0,15);
            break;
        case 50:
            send_read_config(block,0,1);
            break;
        default:
            break;
    }
}
void MainWindow::send_read_config(int block,int start_field, int end_field)
{
    for(int i=start_field;i<=end_field;i++){
        send_mutex.lock();
        send_arr[4]=0x31;
        send_arr[5]=block;
        send_arr[6]=i;
        send_oneframe(3);
        send_mutex.unlock();
    }
}
void MainWindow::upgrade_showtext(int i, int percent)
{
    switch(i)
    {
        case 0:
            upgrade_show->setText(tr("文件发送中...%")+QString("%1").arg(percent&0xFF,2,10));
            break;
        case 1:
            upgrade_show->setText("文件发送中...%100");
            upgrade_show->append("升级成功");
            break;
        case 2:
            upgrade_show->append("升级失败");
            break;
        default:
            break;
    }
}
