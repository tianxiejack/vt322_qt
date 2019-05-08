#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QTcpSocket *socket;

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
extern QSerialPort * serialPort_command;

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
    int value_inte;
    QString msg;
    QByteArray   ba;
    bool osd_judgment=(output_array[1] == 0x07) || (output_array[1] == 0x08)|| (output_array[1] == 0x09)||(output_array[1] == 0x0a)\
                      ||(output_array[1] == 0x0b) || (output_array[1] == 0x0c)|| (output_array[1] == 0x0d)||(output_array[1] == 0x0e)\
                      ||(output_array[1] == 0x0f) || (output_array[1] == 0x10)|| (output_array[1] == 0x11)||(output_array[1] == 0x12)\
                      ||(output_array[1] == 0x13) || (output_array[1] == 0x14)|| (output_array[1] == 0x15)||(output_array[1] == 0x16)\
                      ||(output_array[1] == 0x1D) || (output_array[1] == 0x1e)|| (output_array[1] == 0x1f)||(output_array[1] == 0x20)\
                      ||(output_array[1] == 0x21) || (output_array[1] == 0x22)|| (output_array[1] == 0x23)||(output_array[1] == 0x24)\
                      ||(output_array[1] == 0x25) || (output_array[1] == 0x26)|| (output_array[1] == 0x27)||(output_array[1] == 0x28)\
                      ||(output_array[1] == 0x29) || (output_array[1] == 0x2a)|| (output_array[1] == 0x2b)||(output_array[1] == 0x2c);
    if(osd_judgment && (output_array[2]==0x04)){
      QByteArray dd((char*)output_array+3, data_length-3);
      ba=dd;

    }else{
        memcpy(&value_i,output_array+3,4);
    }
    value_inte = value_i;

    if(0x43 == i)
    {
        int curstat = output_array[1];
        int outputtype = output_array[2];
        short errorx = (output_array_6[3] | (output_array_6[4]<<8));
        short errory = (output_array_6[5] | (output_array_6[6]<<8));

        switch(curstat)
        {
            case 0x00:
                rto_currstat->setText("目标捕获");
                break;
            case 0x01:
                rto_currstat->setText("自动跟踪");
                break;
            case 0x02:
                rto_currstat->setText("惯性跟踪");
                break;
            default:
                break;
        }
        switch(outputtype)
        {
            case 0x01:
                rto_trkerrorx_l->setText("X方向像素偏差");
                rto_trkerrory_l->setText("Y方向像素偏差");
                break;
            case 0x02:
                rto_trkerrorx_l->setText("X方向速度需求");
                rto_trkerrory_l->setText("Y方向速度需求");
                break;
            default:
                break;
        }

        rto_trkerrorx->setText(QString::number(errorx));
        rto_trkerrory->setText(QString::number(errory));
    }
    else if(0x52 == i){
        switch (output_array[1]) {
            case 1:
                if(w_plat->show_stat)
                {
                    if(output_array[2]==0x00){
                        if(0 == value_inte)
                            comb_jostype->setCurrentIndex(0);
                        else if(1 == value_inte)
                            comb_jostype->setCurrentIndex(1);
                    }else if(output_array[2]==1){
                        josDeadx_lineEdt->setText(QString::number(value_i));
                    }else if(output_array[2]==2){
                        josDeady_lineEdt->setText(QString::number(value_i));
                    }else if(output_array[2]==3){
                        josInputG_x->setText(QString::number(value_i));
                    }else if(output_array[2]==4){
                        josInputG_y->setText(QString::number(value_i));
                    }else if(output_array[2]==5){
                        josInputG_x2->setText(QString::number(value_i));
                    }else if(output_array[2]==6){
                        josInputG_y2->setText(QString::number(value_i));
                    }else if(output_array[2]==9){
                        josPointx_lineEdt->setText(QString::number(value_i));
                    }else if(output_array[2]==10){
                        josPointy_lineEdt->setText(QString::number(value_i));
                    }else if(output_array[2]==11){
                        josPointx_lineEdt2->setText(QString::number(value_i));
                    }else if(output_array[2]==12){
                        josPointy_lineEdt2->setText(QString::number(value_i));
                    }
                }
                break;
            case 4:
                if(utc1->show_stat)
                {
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
                            utc1_ltrktime->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 5:
                if(utc2->show_stat)
                {
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
                }
                break;
            case 6:
                if(utc3->show_stat)
                {
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
                }
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
                if(w_osd1->show_stat)
                {
                    if(output_array[1] < 23)
                        c->setCurrentIndex(output_array[1] - 7);
                    else
                        c->setCurrentIndex(output_array[1] - 13);
                    switch(output_array[2])
                    {
                        case 1:
                             osd1_pos_x->setText(QString::number(value_i));
                            break;
                        case 2:
                             osd1_pos_y->setText(QString::number(value_i));
                            break;
                        case 3:
                            if(0x01 == value_inte)
                                CBox_datatype->setCurrentIndex(0);
                            break;
                        case 4:
                             osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                            break;
                        case 6:
                            CBox_color->setCurrentIndex(value_inte-1);
                            break;
                        case 7:
                           CBox_transparency->setCurrentIndex(value_inte);
                            break;
                        case 8:
                            CBox_font->setCurrentIndex(value_inte-1);
                            break;
                        case 9:
                           CBox_font_size->setCurrentIndex(value_inte - 1);
                            break;
                    }
                }
                break;
            case 23:
                showblk23(output_array[2],value_i);
                break;
            case 24:
                showblk24(output_array[2],value_i);
                break;
            case 25:
                showblk25(output_array[2],value_i);
                break;
            case 26:
                showblk26(output_array[2],value_i);
                break;
            case 27:
                showblk27(output_array[2],value_i);
                break;
            case 28:
                break;
            case 45:
                if(w_capture1->show_stat)
                {
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
                }
                break;
            case 46:
                if(w_capture2->show_stat)
                {
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
                }
                break;
            case 47:
                if(w_capture3->show_stat)
                {
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
                }
                break;
                //比例调节器通道1//
            case 48:
                if(w_pid->show_stat){
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
                    }else if(output_array[2]==0x05){
                        x_ratio_control->setText(QString::number(value_i));
                    }else if(output_array[2]==0x06){
                        y_ratio_control->setText(QString::number(value_i));
                    }
                }
                break;
            case 49:
                if(w_speedconv->show_stat)
                {
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
                }
                break;
            case 50:
                if(w_speedconv->show_stat)
                {
                    if(0x00 == output_array[2])
                    {
                        speedy8_lineEdt->setText(QString::number(value_i));
                    }
                    else if(0x01 == output_array[2])
                    {
                        speedy9_lineEdt->setText(QString::number(value_i));
                    } else if(0x02 == output_array[2])
                    {
                        speedx10_lineEdt->setText(QString::number(value_i));
                    } else if(0x03 == output_array[2])
                    {
                        speedy10_lineEdt->setText(QString::number(value_i));
                    }
                }
                break;
            case 51:
                if(0x05 == output_array[2])
                {
                    int index = (int)value_i;
                    if(index >= 5)
                        index--;
                    box_outresol->setCurrentIndex(index);
                }
                break;
            case 52:
                if(0x01 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 2400:
                            baud_rate->setCurrentIndex(0);
                            break;
                        case 4800:
                            baud_rate->setCurrentIndex(1);
                            break;
                        case 9600:
                            baud_rate->setCurrentIndex(2);
                            break;
                        case 19200:
                            baud_rate->setCurrentIndex(3);
                            break;
                        case 38400:
                            baud_rate->setCurrentIndex(4);
                            break;
                        case 57600:
                            baud_rate->setCurrentIndex(5);
                            break;
                        case 115200:
                            baud_rate->setCurrentIndex(6);
                            break;
                        default:
                            break;
                    }
                }
                else if(0x02 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 5:
                            data_bit->setCurrentIndex(0);
                            break;
                        case 6:
                            data_bit->setCurrentIndex(1);
                            break;
                        case 7:
                            data_bit->setCurrentIndex(2);
                            break;
                        case 8:
                            data_bit->setCurrentIndex(3);
                            break;
                        default:
                            break;
                     }
                }
                else if (0x03 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 0:
                            parity_bit->setCurrentIndex(0);
                            break;
                        case 1:
                            parity_bit->setCurrentIndex(1);
                            break;
                        case 2:
                            parity_bit->setCurrentIndex(2);
                            break;
                        default:
                            break;
                     }
                }
                else if (0x04 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit->setCurrentIndex(0);
                    }else if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit->setCurrentIndex(1);
                    }else if(value_i > 1.5)
                    {
                        stop_bit->setCurrentIndex(2);
                    }
                }
                else if (0x05 == output_array[2])
                {
                    if((int)value_i==1)
                    {
                        flow_control->setCurrentIndex(0);
                    }else if((int)value_i==2)
                    {
                        flow_control->setCurrentIndex(1);
                    }else if((int)value_i==3)
                    {
                        flow_control->setCurrentIndex(2);
                    }
                }
                else if(0x06 == output_array[2])
                {
                    out_address->setText(QString::number(value_i));
                }
                break;
            case 53:
                if(w_osd1->show_stat)
                {
                    if(1 == output_array[2])
                    {
                        sysosd_state = value_i;
                        int i = c_sysosd->currentIndex();
                        checkBox_sysosd->setChecked(sysosd_state & (1 << i));

                    }
                    else if(2 == output_array[2])
                    {
                        cusosd_state = value_i;
                        int i = c_cusosd->currentIndex();
                        checkBox2->setChecked(cusosd_state & (1 << i));
                    }
                }
                break;
            case 54:
                if(0x00 == output_array[2])
                {
                    switch((int)value_i)
                    {
                     case 0:
                        zone_setting->setChecked(false);
                        break;
                    case 1:
                        zone_setting->setChecked(true);
                        break;
                    default:
                        break;
                    }
                }
                else if(0x01 == output_array[2])
                {
                    maxnum->setText(QString::number(value_i));
                }
                else if(0x02 == output_array[2])
                {
                       uspeed->setText(QString::number(value_i));
                }
                else if(0x03 == output_array[2])
                {
                    maxpix->setText(QString::number(value_i));
                }
                else if(0x04 == output_array[2])
                {
                    minpix->setText(QString::number(value_i));
                }
                else if(0x05 == output_array[2])
                {
                    sensitive->setText(QString::number(value_i));
                }
                else if(0x06 == output_array[2])
                {
                    dspeed->setText(QString::number(value_i));
                }
                else if(0x07 == output_array[2])
                {
                    trktime->setText(QString::number(value_i));
                }
                else if(0x08 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 1:
                            output->setCurrentIndex(0);
                            break;
                        case 2:
                            output->setCurrentIndex(1);
                            break;
                        default:
                            break;
                    }
                }
                else if(0x09 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 1:
                            polar->setCurrentIndex(0);
                            break;
                        case 2:
                         polar->setCurrentIndex(1);
                            break;
                        default:
                            break;
                    }
                }
                else if(10 == output_array[2])
                {
                    rigion_Cen_x->setText(QString::number(value_i));
                }
                else if(11 == output_array[2])
                {
                    rigion_Cen_y->setText(QString::number(value_i));
                }
                else if(12 == output_array[2])
                {
                    rigion_Cen_w->setText(QString::number(value_i));
                }
                else if(13 == output_array[2])
                {
                    rigion_Cen_h->setText(QString::number(value_i));
                }
                else if(14 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 1:
                        Priority_judgment->setCurrentIndex(0);
                        break;
                        case 2:
                            Priority_judgment->setCurrentIndex(1);
                            break;
                        case 3:
                            Priority_judgment->setCurrentIndex(2);
                            break;
                        case 4:
                            Priority_judgment->setCurrentIndex(3);
                            break;
                        case 5:
                            Priority_judgment->setCurrentIndex(4);
                            break;
                        case 6:
                            Priority_judgment->setCurrentIndex(5);
                            break;
                        default:
                            break;
                     }
                }
                else if(15 == output_array[2])
                {
                    Alarm_delay->setText(QString::number(value_i));
                }
                break;
            case 55:
                break;
            case 56:
                showblk56(output_array[2],value_i);
                break;
            case 57:
                showblk57(output_array[2],value_i);
                break;
            case 58:
                showblk58(output_array[2],value_i);
                break;
            case 59:
                showblk59(output_array[2],value_i);
                break;
            case 60:
                showblk60(output_array[2],value_i);
                break;
            case 61:
                showblk61(output_array[2],value_i);
                break;
            case 62:
                showblk62(output_array[2],value_i);
                break;
            case 63:
                showblk63(output_array[2],value_i);
                break;
            case 64:
                showblk64(output_array[2],value_i);
                break;
            case 65:
                showblk65(output_array[2],value_i);
                break;
            case 66:
                showblk66(output_array[2],value_i);
                break;
            case 67:
                showblk67(output_array[2],value_i);
                break;
            case 68:
                showblk68(output_array[2],value_i);
                break;
            case 69:
                showblk69(output_array[2],value_i);
                break;
            case 70:
                showblk70(output_array[2],value_i);
                break;
            case 71:
                showblk71(output_array[2],value_i);
                break;
            case 72:
                showblk72(output_array[2],value_i);
                break;
            case 73:
                showblk73(output_array[2],value_i);
                break;
            case 74:
                showblk74(output_array[2],value_i);
                break;
            case 75:
                showblk75(output_array[2],value_i);
                break;
            case 76:
                showblk76(output_array[2],value_i);
                break;
            case 77:
                showblk77(output_array[2],value_i);
                break;
            case 78:
                showblk78(output_array[2],value_i);
                break;
            case 79:
                showblk79(output_array[2],value_i);
                break;
            case 80:
                showblk80(output_array[2],value_i);
                break;
            case 81:
                showblk81(output_array[2],value_i);
                break;
            case 82:
                showblk82(output_array[2],value_i);
                break;
            case 83:
                showblk83(output_array[2],value_i);
                break;
            case 84:
                showblk84(output_array[2],value_i);
                break;
            case 85:
                showblk85(output_array[2],value_i);
                break;
            case 91:
                if(w_pid2->show_stat)
                {
                    switch (output_array[2]){
                        case 0x01:
                            kp1_pid2->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            ki1_pid2->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            kd1_pid2->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            k12->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            kp2_pid2->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            ki2_pid2->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            kd2_pid2->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            k22->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 92:
                if(w_pid2->show_stat)
                {
                    switch (output_array[2]){
                        case 0x00:
                            kx_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 0x01:
                            ky_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            errx_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            erry_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            time_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            x_ratio_control2->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            y_ratio_control2->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 93:
                if(w_pid3->show_stat)
                {
                    switch (output_array[2]){
                        case 0x01:
                            kp1_pid3->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            ki1_pid3->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            kd1_pid3->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            k13->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            kp2_pid3->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            ki2_pid3->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            kd2_pid3->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            k23->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 94:
                if(w_pid3->show_stat)
                {
                    switch (output_array[2]){
                        case 0x00:
                            kx_lineEdt3->setText(QString::number(value_i));
                            break;
                        case 0x01:
                            ky_lineEdt3->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            errx_lineEdt3->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            erry_lineEdt3->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            time_lineEdt3->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            x_ratio_control3->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            y_ratio_control3->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 95:
                if(w_pid4->show_stat)
                {
                    switch (output_array[2]){
                        case 0x01:
                            kp1_pid4->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            ki1_pid4->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            kd1_pid4->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            k14->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            kp2_pid4->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            ki2_pid4->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            kd2_pid4->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            k24->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 96:
                if(w_pid4->show_stat)
                {
                    switch (output_array[2]){
                        case 0x00:
                            kx_lineEdt4->setText(QString::number(value_i));
                            break;
                        case 0x01:
                            ky_lineEdt4->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            errx_lineEdt4->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            erry_lineEdt4->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            time_lineEdt4->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            x_ratio_control4->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            y_ratio_control4->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 97:
                if(w_pid5->show_stat)
                {
                    switch (output_array[2]){
                        case 0x01:
                            kp1_pid5->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            ki1_pid5->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            kd1_pid5->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            k15->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            kp2_pid5->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            ki2_pid5->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            kd2_pid5->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            k25->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 98:
                if(w_pid5->show_stat)
                {
                    switch (output_array[2]){
                        case 0x00:
                            kx_lineEdt5->setText(QString::number(value_i));
                            break;
                        case 0x01:
                            ky_lineEdt5->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            errx_lineEdt5->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            erry_lineEdt5->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            time_lineEdt5->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            x_ratio_control5->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            y_ratio_control5->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
            case 99:
                if(w_speedconv_sec->show_stat)
               {
                   if(0x00 == output_array[2]){
                       speedx1_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x01 == output_array[2]){
                       speedx2_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x02 == output_array[2]){
                       speedx3_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x03 == output_array[2]){
                       speedx4_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x04 == output_array[2]){
                       speedx5_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x05 == output_array[2]){
                       speedx6_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x06 == output_array[2]){
                       speedx7_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x07 == output_array[2]){
                       speedx8_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x08 == output_array[2]){
                       speedx9_lineEdt_sec->setText(QString::number(value_i));
                   }else if(0x09 == output_array[2]){
                       speedy1_lineEdt_sec->setText(QString::number(value_i));
                   }else if(10 == output_array[2]){
                       speedy2_lineEdt_sec->setText(QString::number(value_i));
                   }else if(11 == output_array[2]){
                       speedy3_lineEdt_sec->setText(QString::number(value_i));
                   }else if(12 == output_array[2]){
                       speedy4_lineEdt_sec->setText(QString::number(value_i));
                   }else if(13 == output_array[2]){
                       speedy5_lineEdt_sec->setText(QString::number(value_i));
                   }else if(14 == output_array[2]){
                       speedy6_lineEdt_sec->setText(QString::number(value_i));
                   }else if(15 == output_array[2]){
                       speedy7_lineEdt_sec->setText(QString::number(value_i));
                   }
               }
                break;
            case 100:
                if(w_speedconv_sec->show_stat)
                {
                    switch (output_array[2]){

                         case 0x00:
                           speedy8_lineEdt_sec->setText(QString::number(value_i));
                            break;
                         case 0x01:
                           speedy9_lineEdt_sec->setText(QString::number(value_i));
                            break;
                        case 0x02:
                           speedx10_lineEdt_sec->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            speedy10_lineEdt_sec->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            maxspeedx_sec->setText(QString::number(value_i));
                            break;
                        case 0x05:
                           maxspeedy_sec->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            deadx_sec->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            deady_sec->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            if((int)value_i == 1)
                                output_d_type_sec->setCurrentIndex(0);
                            else if((int)value_i == 2)
                                output_d_type_sec->setCurrentIndex(1);
                            else if((int)value_i == 3)
                                output_d_type_sec->setCurrentIndex(2);
                             break;
                    }
                }
                break;
            case 101:
                if(w_speedconv_thi->show_stat)
               {
                   if(0x00 == output_array[2]){
                       speedx1_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x01 == output_array[2]){
                       speedx2_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x02 == output_array[2]){
                       speedx3_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x03 == output_array[2]){
                       speedx4_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x04 == output_array[2]){
                       speedx5_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x05 == output_array[2]){
                       speedx6_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x06 == output_array[2]){
                       speedx7_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x07 == output_array[2]){
                       speedx8_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x08 == output_array[2]){
                       speedx9_lineEdt_thi->setText(QString::number(value_i));
                   }else if(0x09 == output_array[2]){
                       speedy1_lineEdt_thi->setText(QString::number(value_i));
                   }else if(10 == output_array[2]){
                       speedy2_lineEdt_thi->setText(QString::number(value_i));
                   }else if(11 == output_array[2]){
                       speedy3_lineEdt_thi->setText(QString::number(value_i));
                   }else if(12 == output_array[2]){
                       speedy4_lineEdt_thi->setText(QString::number(value_i));
                   }else if(13 == output_array[2]){
                       speedy5_lineEdt_thi->setText(QString::number(value_i));
                   }else if(14 == output_array[2]){
                       speedy6_lineEdt_thi->setText(QString::number(value_i));
                   }else if(15 == output_array[2]){
                       speedy7_lineEdt_thi->setText(QString::number(value_i));
                   }
               }
                break;
            case 102:
                if(w_speedconv_thi->show_stat)
                {
                    switch (output_array[2]){
                        case 0x00:
                            speedy8_lineEdt_thi->setText(QString::number(value_i));
                            break;
                        case 0x01:
                            speedy9_lineEdt_thi->setText(QString::number(value_i));
                            break;
                        case 0x02:
                            speedx10_lineEdt_thi->setText(QString::number(value_i));
                            break;
                        case 0x03:
                            speedy10_lineEdt_thi->setText(QString::number(value_i));
                            break;
                        case 0x04:
                            maxspeedx_thi->setText(QString::number(value_i));
                            break;
                        case 0x05:
                            maxspeedy_thi->setText(QString::number(value_i));
                            break;
                        case 0x06:
                            deadx_thi->setText(QString::number(value_i));
                            break;
                        case 0x07:
                            deady_thi->setText(QString::number(value_i));
                            break;
                        case 0x08:
                            if((int)value_i == 1)
                                output_d_type_thi->setCurrentIndex(0);
                            else if((int)value_i == 2)
                                output_d_type_thi->setCurrentIndex(1);
                            else if((int)value_i == 3)
                                output_d_type_thi->setCurrentIndex(2);
                            break;
                    }
                }
                break;
            case 103:
                if(w_speedconv_fou->show_stat)
               {
                   if(0x00 == output_array[2]){
                       speedx1_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x01 == output_array[2]){
                       speedx2_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x02 == output_array[2]){
                       speedx3_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x03 == output_array[2]){
                       speedx4_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x04 == output_array[2]){
                       speedx5_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x05 == output_array[2]){
                       speedx6_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x06 == output_array[2]){
                       speedx7_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x07 == output_array[2]){
                       speedx8_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x08 == output_array[2]){
                       speedx9_lineEdt_fou->setText(QString::number(value_i));
                   }else if(0x09 == output_array[2]){
                       speedy1_lineEdt_fou->setText(QString::number(value_i));
                   }else if(10 == output_array[2]){
                       speedy2_lineEdt_fou->setText(QString::number(value_i));
                   }else if(11 == output_array[2]){
                       speedy3_lineEdt_fou->setText(QString::number(value_i));
                   }else if(12 == output_array[2]){
                       speedy4_lineEdt_fou->setText(QString::number(value_i));
                   }else if(13 == output_array[2]){
                       speedy5_lineEdt_fou->setText(QString::number(value_i));
                   }else if(14 == output_array[2]){
                       speedy6_lineEdt_fou->setText(QString::number(value_i));
                   }else if(15 == output_array[2]){
                       speedy7_lineEdt_fou->setText(QString::number(value_i));
                   }
               }
                break;
            case 104:
                if(w_speedconv_fou->show_stat)
                {
                    switch (output_array[2]){

                    case 0x00:
                      speedy8_lineEdt_fou->setText(QString::number(value_i));
                       break;
                    case 0x01:
                      speedy9_lineEdt_fou->setText(QString::number(value_i));
                       break;
                   case 0x02:
                      speedx10_lineEdt_fou->setText(QString::number(value_i));
                       break;
                   case 0x03:
                       speedy10_lineEdt_fou->setText(QString::number(value_i));
                       break;
                   case 0x04:
                       maxspeedx_fou->setText(QString::number(value_i));
                       break;
                   case 0x05:
                      maxspeedy_fou->setText(QString::number(value_i));
                       break;
                   case 0x06:
                       deadx_fou->setText(QString::number(value_i));
                       break;
                   case 0x07:
                       deady_fou->setText(QString::number(value_i));
                       break;
                   case 0x09:
                   deadx_fou->setText(QString::number(value_i));
                   break;
                   case 13:
                   deady_fou->setText(QString::number(value_i));
                   break;
                    }
                }
                break;
            case 105:
                if(w_speedconv_fif->show_stat)
                {
                    if(0x00 == output_array[2]){
                        speedx1_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x01 == output_array[2]){
                        speedx2_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x02 == output_array[2]){
                        speedx3_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x03 == output_array[2]){
                        speedx4_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x04 == output_array[2]){
                        speedx5_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x05 == output_array[2]){
                        speedx6_lineEdt_fou->setText(QString::number(value_i));
                    }else if(0x06 == output_array[2]){
                        speedx7_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x07 == output_array[2]){
                        speedx8_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x08 == output_array[2]){
                        speedx9_lineEdt_fif->setText(QString::number(value_i));
                    }else if(0x09 == output_array[2]){
                        speedy1_lineEdt_fif->setText(QString::number(value_i));
                    }else if(10 == output_array[2]){
                        speedy2_lineEdt_fif->setText(QString::number(value_i));
                    }else if(11 == output_array[2]){
                        speedy3_lineEdt_fif->setText(QString::number(value_i));
                    }else if(12 == output_array[2]){
                        speedy4_lineEdt_fif->setText(QString::number(value_i));
                    }else if(13 == output_array[2]){
                        speedy5_lineEdt_fif->setText(QString::number(value_i));
                    }else if(14 == output_array[2]){
                        speedy6_lineEdt_fif->setText(QString::number(value_i));
                    }else if(15 == output_array[2]){
                        speedy7_lineEdt_fif->setText(QString::number(value_i));
                    }
                }
                break;
            case 106:
                if(w_speedconv_fif->show_stat)
                {
                    switch (output_array[2]){

                    case 0x00:
                      speedy8_lineEdt_fif->setText(QString::number(value_i));
                       break;
                    case 0x01:
                      speedy9_lineEdt_fif->setText(QString::number(value_i));
                       break;
                   case 0x02:
                      speedx10_lineEdt_fif->setText(QString::number(value_i));
                       break;
                   case 0x03:
                       speedy10_lineEdt_fif->setText(QString::number(value_i));
                       break;
                   case 0x04:
                       maxspeedx_fif->setText(QString::number(value_i));
                       break;
                   case 0x05:
                      maxspeedy_fif->setText(QString::number(value_i));
                       break;
                   case 0x06:
                       deadx_fif->setText(QString::number(value_i));
                       break;
                   case 0x07:
                       deady_fif->setText(QString::number(value_i));
                       break;
                   case 0x09:
                   deady_fif->setText(QString::number(value_i));
                   break;
                   case 13:
                   deady_fif->setText(QString::number(value_i));
                   break;
                    }
                }
                break;
            case 107:
                if(0x01 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 2400:
                            baud_rate_sec->setCurrentIndex(0);
                            break;
                        case 4800:
                            baud_rate_sec->setCurrentIndex(1);
                            break;
                        case 9600:
                            baud_rate_sec->setCurrentIndex(2);
                            break;
                        case 19200:
                            baud_rate_sec->setCurrentIndex(3);
                            break;
                        case 38400:
                            baud_rate_sec->setCurrentIndex(4);
                            break;
                        case 57600:
                            baud_rate_sec->setCurrentIndex(5);
                            break;
                        case 115200:
                            baud_rate_sec->setCurrentIndex(6);
                            break;
                        default:
                                break;
                    }

                }
                else if(0x02 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 5:
                            data_bit_sec->setCurrentIndex(0);
                            break;
                        case 6:
                            data_bit_sec->setCurrentIndex(1);
                            break;
                        case 7:
                            data_bit_sec->setCurrentIndex(2);
                            break;
                        case 8:
                            data_bit_sec->setCurrentIndex(3);
                            break;
                    default:
                        break;
                     }
                }
                else if(0x03 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 0:
                            parity_bit_sec->setCurrentIndex(0);
                            break;
                        case 1:
                            parity_bit_sec->setCurrentIndex(1);
                            break;
                        case 2:
                            parity_bit_sec->setCurrentIndex(2);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x04 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit_sec->setCurrentIndex(0);
                    }else if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit_sec->setCurrentIndex(1);
                    }else if(value_i > 1.5)
                    {
                        stop_bit_sec->setCurrentIndex(2);
                    }
                }
                else if(0x05 == output_array[2])
                {
                    if((int)value_i==1)
                    {
                        flow_control_sec->setCurrentIndex(0);
                    }else if((int)value_i==2)
                    {
                        flow_control_sec->setCurrentIndex(1);
                    }else if((int)value_i==3)
                    {
                        flow_control_sec->setCurrentIndex(2);
                    }
                }
                else if(0x06 == output_array[2])
                {
                    out_address_sec->setText(QString::number(value_i));
                }
                break;
            case 108:
                if(0x01 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 2400:
                            baud_rate_thi->setCurrentIndex(0);
                            break;
                        case 4800:
                            baud_rate_thi->setCurrentIndex(1);
                            break;
                        case 9600:
                            baud_rate_thi->setCurrentIndex(2);
                            break;
                        case 19200:
                            baud_rate_thi->setCurrentIndex(3);
                            break;
                        case 38400:
                            baud_rate_thi->setCurrentIndex(4);
                            break;
                        case 57600:
                            baud_rate_thi->setCurrentIndex(5);
                            break;
                        case 115200:
                            baud_rate_thi->setCurrentIndex(6);
                            break;
                        default:
                            break;
                    }
                }
                else if(0x02 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 5:
                            data_bit_thi->setCurrentIndex(0);
                            break;
                        case 6:
                            data_bit_thi->setCurrentIndex(1);
                            break;
                        case 7:
                            data_bit_thi->setCurrentIndex(2);
                            break;
                        case 8:
                            data_bit_thi->setCurrentIndex(3);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x03 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 0:
                            parity_bit_thi->setCurrentIndex(0);
                            break;
                        case 1:
                            parity_bit_thi->setCurrentIndex(1);
                            break;
                        case 2:
                            parity_bit_thi->setCurrentIndex(2);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x04 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit_thi->setCurrentIndex(0);
                    }else if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit_thi->setCurrentIndex(1);
                    }else if(value_i > 1.5)
                    {
                        stop_bit_thi->setCurrentIndex(2);
                    }
                }
                else if(0x05 == output_array[2])
                {
                    if((int)value_i==1)
                    {
                        flow_control_thi->setCurrentIndex(0);
                    }else if((int)value_i==2)
                    {
                        flow_control_thi->setCurrentIndex(1);
                    }else if((int)value_i==3)
                    {
                        flow_control_thi->setCurrentIndex(2);
                    }
                }
                else if(0x06 == output_array[2])
                {
                    out_address_thi->setText(QString::number(value_i));
                }
                break;
            case 109:
                if(0x01 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 2400:
                            baud_rate_fou->setCurrentIndex(0);
                            break;
                        case 4800:
                            baud_rate_fou->setCurrentIndex(1);
                            break;
                        case 9600:
                            baud_rate_fou->setCurrentIndex(2);
                            break;
                        case 19200:
                            baud_rate_fou->setCurrentIndex(3);
                            break;
                        case 38400:
                            baud_rate_fou->setCurrentIndex(4);
                            break;
                        case 57600:
                            baud_rate_fou->setCurrentIndex(5);
                            break;
                        case 115200:
                            baud_rate_fou->setCurrentIndex(6);
                            break;
                        default:
                            break;
                    }

                }
                else if(0x02 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 5:
                            data_bit_fou->setCurrentIndex(0);
                            break;
                        case 6:
                            data_bit_fou->setCurrentIndex(1);
                            break;
                        case 7:
                            data_bit_fou->setCurrentIndex(2);
                            break;
                        case 8:
                            data_bit_fou->setCurrentIndex(3);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x03 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 0:
                            parity_bit_fou->setCurrentIndex(0);
                            break;
                        case 1:
                            parity_bit_fou->setCurrentIndex(1);
                            break;
                        case 2:
                            parity_bit_fou->setCurrentIndex(2);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x04 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit_fou->setCurrentIndex(0);
                    }else if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit_fou->setCurrentIndex(1);
                    }else if(value_i > 1.5)
                    {
                        stop_bit_fou->setCurrentIndex(2);
                    }
                }
                else if(0x05 == output_array[2])
                {
                    if((int)value_i==1)
                    {
                        flow_control_fou->setCurrentIndex(0);
                    }else if((int)value_i==2)
                    {
                        flow_control_fou->setCurrentIndex(1);
                    }else if((int)value_i==3)
                    {
                        flow_control_fou->setCurrentIndex(2);
                    }
                }
                else if(0x06 == output_array[2])
                {
                    out_address_fou->setText(QString::number(value_i));
                }
                break;
            case 110:
                if(0x01 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 2400:
                            baud_rate_fif->setCurrentIndex(0);
                            break;
                        case 4800:
                            baud_rate_fif->setCurrentIndex(1);
                            break;
                        case 9600:
                            baud_rate_fif->setCurrentIndex(2);
                            break;
                        case 19200:
                            baud_rate_fif->setCurrentIndex(3);
                            break;
                        case 38400:
                            baud_rate_fif->setCurrentIndex(4);
                            break;
                        case 57600:
                            baud_rate_fif->setCurrentIndex(5);
                            break;
                        case 115200:
                            baud_rate_fif->setCurrentIndex(6);
                            break;
                        default:
                            break;
                    }

                }
                else if(0x02 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 5:
                            data_bit_fif->setCurrentIndex(0);
                            break;
                        case 6:
                            data_bit_fif->setCurrentIndex(1);
                            break;
                        case 7:
                            data_bit_fif->setCurrentIndex(2);
                            break;
                        case 8:
                            data_bit_fif->setCurrentIndex(3);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x03 == output_array[2])
                {
                    switch((int)value_i)
                    {
                        case 0:
                            parity_bit_fif->setCurrentIndex(0);
                            break;
                        case 1:
                            parity_bit_fif->setCurrentIndex(1);
                            break;
                        case 2:
                            parity_bit_fif->setCurrentIndex(2);
                            break;
                        default:
                            break;
                     }
                }
                else if(0x04 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit_fif->setCurrentIndex(0);
                    }else if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit_fif->setCurrentIndex(1);
                    }else if(value_i > 1.5)
                    {
                        stop_bit_fif->setCurrentIndex(2);
                    }
                }
                else if(0x05 == output_array[2])
                {
                    if((int)value_i==1)
                    {
                        flow_control_fif->setCurrentIndex(0);
                    }else if((int)value_i==2)
                    {
                        flow_control_fif->setCurrentIndex(1);
                    }else if((int)value_i==3)
                    {
                        flow_control_fif->setCurrentIndex(2);
                    }
                }
                else if(0x06 == output_array[2])
                {
                    out_address_fif->setText(QString::number(value_i));
                }
                break;
            case 111:
                showblk111(output_array[2],value_i);
                break;
            case 112:
                showblk112(output_array[2],value_i);
                break;
            case 113:
                showblk113(output_array[2],value_i);
                break;
            case 114:
                showblk114(output_array[2],value_i);
                break;
            case 115:
                showblk115(output_array[2],value_i);
                break;
            case 116:
                showblk116(output_array[2],value_i);
                break;
            case 117:
                showblk117(output_array[2],value_i);
                break;
            case 118:
                showblk118(output_array[2],value_i);
                break;
            case 119:
                showblk119(output_array[2],value_i);
                break;
            case 120:
                showblk120(output_array[2],value_i);
                break;
            default:
                break;
        }
    }
    else if(0x0d == i)
    {
       if(output_array[1] != 0xff)
           read_config(output_array[1]);
       else
       {
           if(w_plat->show_stat)
           {
                read_config(1);
                read_config(2);
                read_config(3);
           }
           if(utc1->show_stat)
           {
                read_config(4);
           }
           if(utc2->show_stat)
           {
                read_config(5);
           }
           if(utc3->show_stat)
           {
                read_config(6);
           }
           if(w_osd1->show_stat)
           {
                int count = c->currentIndex();
                if(count < 16)
                    count += 7;
                else
                    count += 13;
                read_config(count);
           }
           if(w_capture2->show_stat)
           {
                read_config(46);
           }
           if(w_capture3->show_stat)
           {
                read_config(47);
           }
           if(w_speedconv->show_stat)
           {
                read_config(49);
                read_config(50);
                read_config(52);
                read_config(3);
           }
           if(w_mtd->show_stat)
           {
               read_config(54);
           }
           if(w_speedconv_sec->show_stat)
           {
               read_config(99);
               read_config(100);
               read_config(107);
           }
           if(w_speedconv_thi->show_stat)
           {
               read_config(101);
               read_config(102);
               read_config(108);
           }
           if(w_speedconv_fou->show_stat)
           {
               read_config(103);
               read_config(104);
               read_config(109);
           }
           if(w_speedconv_fif->show_stat)
           {
               read_config(105);
               read_config(106);
               read_config(110);

           }
           if(w_pid->show_stat)
           {
                read_config(2);
                read_config(48);
           }
           if(w_pid2->show_stat)
           {
               read_config(91);
               read_config(92);
           }
           if(w_pid3->show_stat)
           {
               read_config(93);
               read_config(94);

           }
           if(w_pid4->show_stat)
           {
               read_config(95);
               read_config(96);
           }
           if(w_pid5->show_stat)
           {
               read_config(97);
               read_config(98);
           }
           if(w_sersor_1->show_stat)
           {
                read_config(23);
                read_config(24);
           }
           if(w_seitchField_1->show_stat)
           {
               read_config(23);
               read_config(25);
               read_config(26);
           }
           if(w_ContinueField_1->show_stat)
           {
                read_config(23);
                read_config(27);
                read_config(56);
                read_config(57);
           }
           if(w_sersor_1_sec->show_stat)
           {
                read_config(58);
                read_config(59);
           }
           if(w_seitchField_1_sec->show_stat)
           {
               read_config(58);
               read_config(60);
               read_config(61);
           }
           if(w_ContinueField_1_sec->show_stat)
           {
               read_config(58);
               read_config(62);
               read_config(63);
               read_config(64);
           }
           if(w_sersor_1_thi->show_stat)
           {
                read_config(65);
                read_config(66);
           }
           if(w_seitchField_1_thi->show_stat)
           {
               read_config(65);
               read_config(67);
               read_config(68);
           }
           if(w_ContinueField_1_thi->show_stat)
           {
               read_config(65);
               read_config(69);
               read_config(70);
               read_config(71);
           }
           if(w_sersor_1_fou->show_stat)
           {
                read_config(72);
                read_config(73);
           }
           if(w_seitchField_1_fou->show_stat)
           {
               read_config(72);
               read_config(74);
               read_config(75);
           }
           if(w_ContinueField_1_fou->show_stat)
           {
               read_config(72);
               read_config(76);
               read_config(77);
               read_config(78);
           }
           if(w_sersor_1_fif->show_stat)
           {
                read_config(79);
                read_config(80);
           }
           if(w_seitchField_1_fif->show_stat)
           {
               read_config(79);
               read_config(81);
               read_config(82);
           }
           if(w_ContinueField_1_fif->show_stat)
           {
               read_config(79);
               read_config(83);
               read_config(84);
               read_config(85);
           }
       }
    }
    else if(0x41 == i)
    {
        unsigned short value_int = (output_array[1] | (output_array[2]<<8));
        unsigned short value_int2 = (output_array[3] | (output_array[4]<<8));
        if(w_sersor_1->show_stat)
        {
            ledt_search_azimuth->setText(QString::number(value_int));
            ledt_search_pitch->setText(QString::number(value_int2));
        }
        if(w_seitchField_1->show_stat)
        {
            Change_ledt_search_azimuth->setText(QString::number(value_int));
            Change_ledt_search_pitch->setText(QString::number(value_int2));
        }
        if(w_ContinueField_1->show_stat)
        {
            continue_ledt_search_azimuth->setText(QString::number(value_int));
            continue_ledt_search_pitch->setText(QString::number(value_int2));
        }

        if(w_sersor_1_sec->show_stat)
        {
            ledt_search_azimuth_sec->setText(QString::number(value_int));
            ledt_search_pitch_sec->setText(QString::number(value_int2));
        }
        if(w_seitchField_1_sec->show_stat)
        {
            Change_ledt_search_azimuth_sec->setText(QString::number(value_int));
            Change_ledt_search_pitch_sec->setText(QString::number(value_int2));
        }
        if(w_ContinueField_1_sec->show_stat)
        {
            continue_ledt_search_azimuth_sec->setText(QString::number(value_int));
            continue_ledt_search_pitch_sec->setText(QString::number(value_int2));
        }

        if(w_sersor_1_thi->show_stat)
        {
            ledt_search_azimuth_thi->setText(QString::number(value_int));
            ledt_search_pitch_thi->setText(QString::number(value_int2));
        }
        if(w_seitchField_1_thi->show_stat)
        {
            Change_ledt_search_azimuth_thi->setText(QString::number(value_int));
            Change_ledt_search_pitch_thi->setText(QString::number(value_int2));
        }
        if(w_ContinueField_1_thi->show_stat)
        {
            continue_ledt_search_azimuth_thi->setText(QString::number(value_int));
            continue_ledt_search_pitch_thi->setText(QString::number(value_int2));
        }

        if(w_sersor_1_fou->show_stat)
        {
            ledt_search_azimuth_fou->setText(QString::number(value_int));
            ledt_search_pitch_fou->setText(QString::number(value_int2));
        }
        if(w_seitchField_1_fou->show_stat)
        {
            Change_ledt_search_azimuth_fou->setText(QString::number(value_int));
            Change_ledt_search_pitch_fou->setText(QString::number(value_int2));
        }
        if(w_ContinueField_1_fou->show_stat)
        {
            continue_ledt_search_azimuth_fou->setText(QString::number(value_int));
            continue_ledt_search_pitch_fou->setText(QString::number(value_int2));
        }

        if(w_sersor_1_fif->show_stat)
        {
            ledt_search_azimuth_fif->setText(QString::number(value_int));
            ledt_search_pitch_fif->setText(QString::number(value_int2));
        }
        if(w_seitchField_1_fif->show_stat)
        {
            Change_ledt_search_azimuth_fif->setText(QString::number(value_int));
            Change_ledt_search_pitch_fif->setText(QString::number(value_int2));
        }
        if(w_ContinueField_1_fif->show_stat)
        {
            continue_ledt_search_azimuth_fif->setText(QString::number(value_int));
            continue_ledt_search_pitch_fif->setText(QString::number(value_int2));
        }
    }
    else if(0x42 == i)
    {
        unsigned short value_int = (output_array[1] | (output_array[2]<<8));
        if(w_sersor_1->show_stat)
            ledt_search_zoom->setText(QString::number(value_int));
        if(w_seitchField_1->show_stat)
            Change_ledt_search_zoom->setText(QString::number(value_int));
        if(w_ContinueField_1->show_stat)
            continue_ledt_search_zoom->setText(QString::number(value_int));

        if(w_sersor_1_sec->show_stat)
            ledt_search_zoom_sec->setText(QString::number(value_int));
        if(w_seitchField_1_sec->show_stat)
            Change_ledt_search_zoom_sec->setText(QString::number(value_int));
        if(w_ContinueField_1_sec->show_stat)
            continue_ledt_search_zoom_sec->setText(QString::number(value_int));

        if(w_sersor_1_thi->show_stat)
            ledt_search_zoom_thi->setText(QString::number(value_int));
        if(w_seitchField_1_thi->show_stat)
            Change_ledt_search_zoom_thi->setText(QString::number(value_int));
        if(w_ContinueField_1_thi->show_stat)
            continue_ledt_search_zoom_thi->setText(QString::number(value_int));

        if(w_sersor_1_fou->show_stat)
            ledt_search_zoom_fou->setText(QString::number(value_int));
        if(w_seitchField_1_fou->show_stat)
            Change_ledt_search_zoom_fou->setText(QString::number(value_int));
        if(w_ContinueField_1_fou->show_stat)
            continue_ledt_search_zoom_fou->setText(QString::number(value_int));

        if(w_sersor_1_fif->show_stat)
            ledt_search_zoom_fif->setText(QString::number(value_int));
        if(w_seitchField_1_fif->show_stat)
            Change_ledt_search_zoom_fif->setText(QString::number(value_int));
        if(w_ContinueField_1_fif->show_stat)
            continue_ledt_search_zoom_fif->setText(QString::number(value_int));
    }
    memset(output_array,0,sizeof(output_array));
}

void MainWindow::read_config(int block)
{
    switch(block)
    {
        case 1:
            send_read_config(block,1,6);
            send_read_config(block,9,12);
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
            send_read_config(block,1,8);
            break;
        case 23:
            send_read_config(block,0,13);
            break;
        case 24:
            send_read_config(block,0,3);
            break;
        case 25:
            send_read_config(block,0,15);
            break;
        case 26:
            send_read_config(block,0,4);
            break;
        case 27:
            send_read_config(block,0,15);
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
            send_read_config(block,0,3);
            break;
        case 52:
            send_read_config(block,1,6);
            break;
        case 53:
            send_read_config(block,1,2);
            break;
        case 54:
            send_read_config(block,0,15);
        break;
        case 56:
            send_read_config(block,0,15);
            break;
        case 57:
            send_read_config(block,0,3);
            break;
        case 58:
            send_read_config(block,0,13);
            break;
        case 59:
            send_read_config(block,0,3);
            break;
        case 60:
            send_read_config(block,0,15);
            break;
        case 61:
            send_read_config(block,0,4);
            break;
        case 62:
            send_read_config(block,0,15);
            break;
        case 63:
            send_read_config(block,0,15);
            break;
        case 64:
            send_read_config(block,0,3);
            break;
        case 65:
            send_read_config(block,0,13);
            break;
        case 66:
            send_read_config(block,0,3);
            break;
        case 67:
            send_read_config(block,0,15);
            break;
        case 68:
            send_read_config(block,0,4);
            break;
        case 69:
            send_read_config(block,0,15);
            break;
        case 70:
            send_read_config(block,0,15);
            break;
        case 71:
            send_read_config(block,0,3);
            break;
        case 72:
            send_read_config(block,0,13);
            break;
        case 73:
            send_read_config(block,0,3);
            break;
        case 74:
            send_read_config(block,0,15);
            break;
        case 75:
            send_read_config(block,0,4);
            break;
        case 76:
            send_read_config(block,0,15);
            break;
        case 77:
            send_read_config(block,0,15);
            break;
        case 78:
            send_read_config(block,0,3);
            break;
        case 79:
            send_read_config(block,0,13);
            break;
        case 80:
            send_read_config(block,0,3);
            break;
        case 81:
            send_read_config(block,0,15);
            break;
        case 82:
            send_read_config(block,0,4);
            break;
        case 83:
            send_read_config(block,0,15);
            break;
        case 84:
            send_read_config(block,0,15);
             break;
        case 85:
            send_read_config(block,0,3);
            break;
        case 86:
            send_read_config(block,0,3);
            break;
        case 87:
            send_read_config(90,0,3);
            send_read_config(block,0,6);
            break;
        case 88:
            send_read_config(90,0,3);
            send_read_config(block,0,13);
            break;
        case 89:
            send_read_config(block,0,4);
            break;
        case 90:
            send_read_config(block,0,3);
            break;
        case 91:
            send_read_config(block,1,8);
            break;
        case 92:
            send_read_config(block,0,6);
            break;
        case 93:
            send_read_config(block,1,8);
            break;
         case 94:
            send_read_config(block,0,6);
            break;
         case 95:
            send_read_config(block,1,8);
            break;
         case 96:
            send_read_config(block,0,6);
            break;
         case 97:
            send_read_config(block,1,8);
             break;
         case 98:
            send_read_config(block,0,6);
             break;

         case 99:
            send_read_config(block,0,15);
            break;
         case 100:
            send_read_config(block,0,8);
            break;
         case 101:
            send_read_config(block,0,15);
            break;
         case 102:
            send_read_config(block,0,8);
            break;
         case 103:
            send_read_config(block,0,15);
            break;
        case 104:
            send_read_config(block,0,8);
            break;
        case 105:
            send_read_config(block,0,15);
            break;
        case 106:
            send_read_config(block,0,8);
            break;
        case 107:
            send_read_config(block,1,6);
            break;
        case 108:
            send_read_config(block,1,6);
            break;
        case 109:
            send_read_config(block,1,6);
            break;
        case 110:
            send_read_config(block,1,6);
            break;
        default:
            break;
    }
}
void MainWindow::send_read_config(int block,int start_field, int end_field)
{
    for(int i=start_field;i<=end_field;i++){
        send_mutex.lock();
        send_arr[4]=0x52;
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

void MainWindow::showblk23(int field, float value)
{
    int valuei = (int)value;
    if(5 == field)
    {
        if(0 == valuei)
            showvedioCfg1();
        else if(1 == valuei)
            vedio_btnSensor1SwitchSlot();
        else if(2 == valuei)
            vedio_btnSensor2ContinueSlot();
    }

    if(vedio_current_shichang == 0)
    {
        switch(field)
        {
            case 0:
                fixChanelNum->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                fixenable->setChecked(valuei);
                break;
            case 3:
                fix_vediohaveornot->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    fix_vedio_dpi->setCurrentIndex(0);
                if(valuei == 1)
                    fix_vedio_dpi->setCurrentIndex(1);
                if(valuei == 2)
                    fix_vedio_dpi->setCurrentIndex(2);
                if(valuei == 3)
                    fix_vedio_dpi->setCurrentIndex(3);
                if(valuei == 5)
                    fix_vedio_dpi->setCurrentIndex(4);
                break;
            case 6:
                break;
            case 7:
                fix_gateshow->setChecked(valuei);
                break;
            case 8:
                fix_bullshow->setChecked(valuei);
                break;
            case 9:
                fix_autogate->setChecked(valuei);
                break;
            case 10:
                fix_gate_sizex->setText(QString::number(value));
                break;
            case 11:
                fix_gate_sizey->setText(QString::number(value));
                break;
            case 12:
                fix_gatelocationx->setText(QString::number(value));
                break;
            case 13:
                fix_gatelocationy->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang == 1)
    {
        switch(field)
        {
            case 0:
                ChanelNum->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                enable->setChecked(valuei);
                break;
            case 3:
                vediohaveornot->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    vedio_dpi->setCurrentIndex(0);
                if(valuei == 1)
                    vedio_dpi->setCurrentIndex(1);
                if(valuei == 2)
                    vedio_dpi->setCurrentIndex(2);
                if(valuei == 3)
                    vedio_dpi->setCurrentIndex(3);
                if(valuei == 5)
                    vedio_dpi->setCurrentIndex(4);
                break;
            case 6:
                break;
            case 7:
                gateshow->setChecked(valuei);
                break;
            case 8:
                bullshow->setChecked(valuei);
                break;
            case 9:
                autogate->setChecked(valuei);
                break;
            case 10:
                gate_sizex->setText(QString::number(value));
                break;
            case 11:
                gate_sizey->setText(QString::number(value));
                break;
            case 12:
                gatelocationx->setText(QString::number(value));
                break;
            case 13:
                gatelocationy->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang == 2)
    {
        switch(field)
        {
            case 0:
                continueChanelNum->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                continueenable->setChecked(valuei);
                break;
            case 3:
                continue_vediohaveornot->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    continue_vedio_dpi->setCurrentIndex(0);
                if(valuei == 1)
                    continue_vedio_dpi->setCurrentIndex(1);
                if(valuei == 2)
                    continue_vedio_dpi->setCurrentIndex(2);
                if(valuei == 3)
                    continue_vedio_dpi->setCurrentIndex(3);
                if(valuei == 5)
                    continue_vedio_dpi->setCurrentIndex(4);
                break;
            case 6:
                break;
            case 7:
                continue_gateshow->setChecked(valuei);
                break;
            case 8:
                continue_bullshow->setChecked(valuei);
                break;
            case 9:
                continue_autogate->setChecked(valuei);
                break;
            case 10:
                continue_gate_sizex->setText(QString::number(value));
                break;
            case 11:
                continue_gate_sizey->setText(QString::number(value));
                break;
            case 12:
                continue_gatelocationx->setText(QString::number(value));
                break;
            case 13:
                continue_gatelocationy->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
}

void MainWindow::showblk24(int field, float value)
{
    switch(field)
    {
        case 0:
            fix_lEdt->setText(QString::number(value));
            break;
        case 1:
            fix_vertical->setText(QString::number(value));
            break;
        case 2:
            fix_sp->setValue(value);
            break;
        case 3:
            fix_sp2->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk25(int field, float value)
{
    int valuei = (int)value;
    switch(field)
    {
        case 0:
            vedio_fovclass->setCurrentIndex(valuei);
            break;
        case 1:
            vedio_s1_Fov0->setText(QString::number(value));
            break;
        case 2:
            Change_vertical1->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch1->setValue(value);
            break;
        case 4:
            vedio_spby_switch1->setValue(value);
            break;
        case 5:
            vedio_s1_Fov1->setText(QString::number(value));
            break;
        case 6:
            Change_vertical2->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_switch2->setValue(value);
            break;
        case 8:
            vedio_spby_switch2->setValue(value);
            break;
        case 9:
            vedio_s1_Fov2->setText(QString::number(value));
            break;
        case 10:
            Change_vertical3->setText(QString::number(value));
            break;
        case 11:
            vedio_spbx_switch3->setValue(value);
            break;
        case 12:
            vedio_spby_switch3->setValue(value);
            break;
        case 13:
            vedio_s1_Fov3->setText(QString::number(value));
            break;
        case 14:
            Change_vertical4->setText(QString::number(value));
            break;
        case 15:
            vedio_spbx_switch4->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk26(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spby_switch4->setValue(value);
            break;
        case 1:
            vedio_s1_Fov4->setText(QString::number(value));
            break;
        case 2:
            Change_vertical5->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch5->setValue(value);
            break;
        case 4:
            vedio_spby_switch5->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk27(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l1_continue->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov0->setText(QString::number(value));
            break;
        case 2:
            continue_vertical1->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue1->setValue(value);
            break;
        case 4:
            vedio_spby_continue1->setValue(value);
            break;
        case 5:
            vedio_l2_continue->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov1->setText(QString::number(value));
            break;
        case 7:
            continue_vertical2->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue2->setValue(value);
            break;
        case 9:
            vedio_spby_continue2->setValue(value);
            break;
        case 10:
            vedio_l3_continue->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov2->setText(QString::number(value));
            break;
        case 12:
            continue_vertical3->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue3->setValue(value);
            break;
        case 14:
            vedio_spby_continue3->setValue(value);
            break;
        case 15:
            vedio_l4_continue->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk56(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov3->setText(QString::number(value));
            break;
        case 1:
            continue_vertical4->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue4->setValue(value);
            break;
        case 3:
            vedio_spby_continue4->setValue(value);
            break;
        case 4:
            vedio_l5_continue->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov4->setText(QString::number(value));
            break;
        case 6:
            continue_vertical5->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue5->setValue(value);
            break;
        case 8:
            vedio_spby_continue5->setValue(value);
            break;
        case 9:
            vedio_l6_continue->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov5->setText(QString::number(value));
            break;
        case 11:
            continue_vertical6->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue6->setValue(value);
            break;
        case 13:
            vedio_spby_continue6->setValue(value);
            break;
        case 14:
            vedio_l7_continue->setText(QString::number(value));
            break;
        case 15:
            vedio_continue_Fov6->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk57(int field, float value)
{
    switch(field)
    {
        case 0:
            continue_vertical7->setText(QString::number(value));
            break;
        case 1:
            vedio_spbx_continue7->setValue(value);
            break;
        case 2:
            vedio_spby_continue7->setValue(value);
            break;
        case 3:
            test_1->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk58(int field, float value)
{
    int valuei = (int)value;

    if(5 == field)
    {
        if(0 == valuei)
            showvedioCfg2();
        else if(1 == valuei)
            vedio_btnSensor1SwitchSlot_sec();
        else if(2 == valuei)
            vedio_btnSensor2ContinueSlot_sec();
    }

    if(vedio_current_shichang_sec == 0)
    {
        switch(field)
        {
            case 0:
                fixChanelNum_sec->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                fixenable_sec->setChecked(valuei);
                break;
            case 3:
                fix_vediohaveornot_sec->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    fix_vedio_dpi_sec->setCurrentIndex(0);
                if(valuei == 1)
                    fix_vedio_dpi_sec->setCurrentIndex(1);
                if(valuei == 2)
                    fix_vedio_dpi_sec->setCurrentIndex(2);
                if(valuei == 3)
                    fix_vedio_dpi_sec->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                fix_gateshow_sec->setChecked(valuei);
                break;
            case 8:
                fix_bullshow_sec->setChecked(valuei);
                break;
            case 9:
                fix_autogate_sec->setChecked(valuei);
                break;
            case 10:
                fix_gate_sizex_sec->setText(QString::number(value));
                break;
            case 11:
                fix_gate_sizey_sec->setText(QString::number(value));
                break;
            case 12:
                fix_gatelocationx_sec->setText(QString::number(value));
                break;
            case 13:
                fix_gatelocationy_sec->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_sec == 1)
    {
        switch(field)
        {
            case 0:
                ChanelNum_sec->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                enable_sec->setChecked(valuei);
                break;
            case 3:
                vediohaveornot_sec->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    vedio_dpi_sec->setCurrentIndex(0);
                if(valuei == 1)
                    vedio_dpi_sec->setCurrentIndex(1);
                if(valuei == 2)
                    vedio_dpi_sec->setCurrentIndex(2);
                if(valuei == 3)
                    vedio_dpi_sec->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                gateshow_sec->setChecked(valuei);
                break;
            case 8:
                bullshow_sec->setChecked(valuei);
                break;
            case 9:
                autogate_sec->setChecked(valuei);
                break;
            case 10:
                gate_sizex_sec->setText(QString::number(value));
                break;
            case 11:
                gate_sizey_sec->setText(QString::number(value));
                break;
            case 12:
                gatelocationx_sec->setText(QString::number(value));
                break;
            case 13:
                gatelocationy_sec->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_sec == 2)
    {
        switch(field)
        {
            case 0:
                continueChanelNum_sec->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                continueenable_sec->setChecked(valuei);
                break;
            case 3:
                continue_vediohaveornot_sec->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    continue_vedio_dpi_sec->setCurrentIndex(0);
                if(valuei == 1)
                    continue_vedio_dpi_sec->setCurrentIndex(1);
                if(valuei == 2)
                    continue_vedio_dpi_sec->setCurrentIndex(2);
                if(valuei == 3)
                    continue_vedio_dpi_sec->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                continue_gateshow_sec->setChecked(valuei);
                break;
            case 8:
                continue_bullshow_sec->setChecked(valuei);
                break;
            case 9:
                continue_autogate_sec->setChecked(valuei);
                break;
            case 10:
                continue_gate_sizex_sec->setText(QString::number(value));
                break;
            case 11:
                continue_gate_sizey_sec->setText(QString::number(value));
                break;
            case 12:
                continue_gatelocationx_sec->setText(QString::number(value));
                break;
            case 13:
                continue_gatelocationy_sec->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
}

void MainWindow::showblk59(int field, float value)
{
    switch(field)
    {
        case 0:
            fix_lEdt_sec->setText(QString::number(value));
            break;
        case 1:
            fix_vertical_sec->setText(QString::number(value));
            break;
        case 2:
            fix_sp_sec->setValue(value);
            break;
        case 3:
            fix_sp2_sec->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk60(int field, float value)
{
    int valuei = (int)value;
    switch(field)
    {
        case 0:
            vedio_fovclass_sec->setCurrentIndex(valuei);
            break;
        case 1:
            vedio_s1_Fov0_sec->setText(QString::number(value));
            break;
        case 2:
            Change_vertical1_sec->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch1_sec->setValue(value);
            break;
        case 4:
            vedio_spby_switch1_sec->setValue(value);
            break;
        case 5:
            vedio_s1_Fov1_sec->setText(QString::number(value));
            break;
        case 6:
            Change_vertical2_sec->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_switch2_sec->setValue(value);
            break;
        case 8:
            vedio_spby_switch2_sec->setValue(value);
            break;
        case 9:
            vedio_s1_Fov2_sec->setText(QString::number(value));
            break;
        case 10:
            Change_vertical3_sec->setText(QString::number(value));
            break;
        case 11:
            vedio_spbx_switch3_sec->setValue(value);
            break;
        case 12:
            vedio_spby_switch3_sec->setValue(value);
            break;
        case 13:
            vedio_s1_Fov3_sec->setText(QString::number(value));
            break;
        case 14:
            Change_vertical4_sec->setText(QString::number(value));
            break;
        case 15:
            vedio_spbx_switch4_sec->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk61(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spby_switch4_sec->setValue(value);
            break;
        case 1:
            vedio_s1_Fov4_sec->setText(QString::number(value));
            break;
        case 2:
            Change_vertical5_sec->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch5_sec->setValue(value);
            break;
        case 4:
            vedio_spby_switch5_sec->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk62(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l1_continue_sec->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov0_sec->setText(QString::number(value));
            break;
        case 2:
            continue_vertical1_sec->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue1_sec->setValue(value);
            break;
        case 4:
            vedio_spby_continue1_sec->setValue(value);
            break;
        case 5:
            vedio_l2_continue_sec->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov1_sec->setText(QString::number(value));
            break;
        case 7:
            continue_vertical2_sec->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue2_sec->setValue(value);
            break;
        case 9:
            vedio_spby_continue2_sec->setValue(value);
            break;
        case 10:
            vedio_l3_continue_sec->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov2_sec->setText(QString::number(value));
            break;
        case 12:
            continue_vertical3_sec->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue3_sec->setValue(value);
            break;
        case 14:
            vedio_spby_continue3_sec->setValue(value);
            break;
        case 15:
            vedio_l4_continue_sec->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk63(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov3_sec->setText(QString::number(value));
            break;
        case 1:
            continue_vertical4_sec->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue4_sec->setValue(value);
            break;
        case 3:
            vedio_spby_continue4_sec->setValue(value);
            break;
        case 4:
            vedio_l5_continue_sec->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov4_sec->setText(QString::number(value));
            break;
        case 6:
            continue_vertical5_sec->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue5_sec->setValue(value);
            break;
        case 8:
            vedio_spby_continue5_sec->setValue(value);
            break;
        case 9:
            vedio_l6_continue_sec->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov5_sec->setText(QString::number(value));
            break;
        case 11:
            continue_vertical6_sec->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue6_sec->setValue(value);
            break;
        case 13:
            vedio_spby_continue6_sec->setValue(value);
            break;
        case 14:
            vedio_l7_continue_sec->setText(QString::number(value));
            break;
        case 15:
            vedio_continue_Fov6_sec->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk64(int field, float value)
{
    switch(field)
    {
        case 0:
            continue_vertical7_sec->setText(QString::number(value));
            break;
        case 1:
            vedio_spbx_continue7_sec->setValue(value);
            break;
        case 2:
            vedio_spby_continue7_sec->setValue(value);
            break;
        case 3:
            test_1_sec->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk65(int field, float value)
{
    int valuei = (int)value;

    if(5 == field)
    {
        if(0 == valuei)
            showvedioCfg3();
        else if(1 == valuei)
            vedio_btnSensor1SwitchSlot_thi();
        else if(2 == valuei)
            vedio_btnSensor2ContinueSlot_thi();
    }

    if(vedio_current_shichang_thi == 0)
    {
        switch(field)
        {
            case 0:
                fixChanelNum_thi->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                fixenable_thi->setChecked(valuei);
                break;
            case 3:
                fix_vediohaveornot_thi->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    fix_vedio_dpi_thi->setCurrentIndex(0);
                if(valuei == 1)
                    fix_vedio_dpi_thi->setCurrentIndex(1);
                if(valuei == 2)
                    fix_vedio_dpi_thi->setCurrentIndex(2);
                if(valuei == 3)
                    fix_vedio_dpi_thi->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                fix_gateshow_thi->setChecked(valuei);
                break;
            case 8:
                fix_bullshow_thi->setChecked(valuei);
                break;
            case 9:
                fix_autogate_thi->setChecked(valuei);
                break;
            case 10:
                fix_gate_sizex_thi->setText(QString::number(value));
                break;
            case 11:
                fix_gate_sizey_thi->setText(QString::number(value));
                break;
            case 12:
                fix_gatelocationx_thi->setText(QString::number(value));
                break;
            case 13:
                fix_gatelocationy_thi->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_thi == 1)
    {
        switch(field)
        {
            case 0:
                ChanelNum_thi->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                enable_thi->setChecked(valuei);
                break;
            case 3:
                vediohaveornot_thi->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    vedio_dpi_thi->setCurrentIndex(0);
                if(valuei == 1)
                    vedio_dpi_thi->setCurrentIndex(1);
                if(valuei == 2)
                    vedio_dpi_thi->setCurrentIndex(2);
                if(valuei == 3)
                    vedio_dpi_thi->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                gateshow_thi->setChecked(valuei);
                break;
            case 8:
                bullshow_thi->setChecked(valuei);
                break;
            case 9:
                autogate_thi->setChecked(valuei);
                break;
            case 10:
                gate_sizex_thi->setText(QString::number(value));
                break;
            case 11:
                gate_sizey_thi->setText(QString::number(value));
                break;
            case 12:
                gatelocationx_thi->setText(QString::number(value));
                break;
            case 13:
                gatelocationy_thi->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_thi == 2)
    {
        switch(field)
        {
            case 0:
                continueChanelNum_thi->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                continueenable_thi->setChecked(valuei);
                break;
            case 3:
                continue_vediohaveornot_thi->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    continue_vedio_dpi_thi->setCurrentIndex(0);
                if(valuei == 1)
                    continue_vedio_dpi_thi->setCurrentIndex(1);
                if(valuei == 2)
                    continue_vedio_dpi_thi->setCurrentIndex(2);
                if(valuei == 3)
                    continue_vedio_dpi_thi->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                continue_gateshow_thi->setChecked(valuei);
                break;
            case 8:
                continue_bullshow_thi->setChecked(valuei);
                break;
            case 9:
                continue_autogate_thi->setChecked(valuei);
                break;
            case 10:
                continue_gate_sizex_thi->setText(QString::number(value));
                break;
            case 11:
                continue_gate_sizey_thi->setText(QString::number(value));
                break;
            case 12:
                continue_gatelocationx_thi->setText(QString::number(value));
                break;
            case 13:
                continue_gatelocationy_thi->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
}

void MainWindow::showblk66(int field, float value)
{
    switch(field)
    {
        case 0:
            fix_lEdt_thi->setText(QString::number(value));
            break;
        case 1:
            fix_vertical_thi->setText(QString::number(value));
            break;
        case 2:
            fix_sp_thi->setValue(value);
            break;
        case 3:
            fix_sp2_thi->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk67(int field, float value)
{
    int valuei = (int)value;
    switch(field)
    {
        case 0:
            vedio_fovclass_thi->setCurrentIndex(valuei);
            break;
        case 1:
            vedio_s1_Fov0_thi->setText(QString::number(value));
            break;
        case 2:
            Change_vertical1_thi->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch1_thi->setValue(value);
            break;
        case 4:
            vedio_spby_switch1_thi->setValue(value);
            break;
        case 5:
            vedio_s1_Fov1_thi->setText(QString::number(value));
            break;
        case 6:
            Change_vertical2_thi->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_switch2_thi->setValue(value);
            break;
        case 8:
            vedio_spby_switch2_thi->setValue(value);
            break;
        case 9:
            vedio_s1_Fov2_thi->setText(QString::number(value));
            break;
        case 10:
            Change_vertical3_thi->setText(QString::number(value));
            break;
        case 11:
            vedio_spbx_switch3_thi->setValue(value);
            break;
        case 12:
            vedio_spby_switch3_thi->setValue(value);
            break;
        case 13:
            vedio_s1_Fov3_thi->setText(QString::number(value));
            break;
        case 14:
            Change_vertical4_thi->setText(QString::number(value));
            break;
        case 15:
            vedio_spbx_switch4_thi->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk68(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spby_switch4_thi->setValue(value);
            break;
        case 1:
            vedio_s1_Fov4_thi->setText(QString::number(value));
            break;
        case 2:
            Change_vertical5_thi->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch5_thi->setValue(value);
            break;
        case 4:
            vedio_spby_switch5_thi->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk69(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l1_continue_thi->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov0_thi->setText(QString::number(value));
            break;
        case 2:
            continue_vertical1_thi->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue1_thi->setValue(value);
            break;
        case 4:
            vedio_spby_continue1_thi->setValue(value);
            break;
        case 5:
            vedio_l2_continue_thi->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov1_thi->setText(QString::number(value));
            break;
        case 7:
            continue_vertical2_thi->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue2_thi->setValue(value);
            break;
        case 9:
            vedio_spby_continue2_thi->setValue(value);
            break;
        case 10:
            vedio_l3_continue_thi->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov2_thi->setText(QString::number(value));
            break;
        case 12:
            continue_vertical3_thi->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue3_thi->setValue(value);
            break;
        case 14:
            vedio_spby_continue3_thi->setValue(value);
            break;
        case 15:
            vedio_l4_continue_thi->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk70(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov3_thi->setText(QString::number(value));
            break;
        case 1:
            continue_vertical4_thi->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue4_thi->setValue(value);
            break;
        case 3:
            vedio_spby_continue4_thi->setValue(value);
            break;
        case 4:
            vedio_l5_continue_thi->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov4_thi->setText(QString::number(value));
            break;
        case 6:
            continue_vertical5_thi->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue5_thi->setValue(value);
            break;
        case 8:
            vedio_spby_continue5_thi->setValue(value);
            break;
        case 9:
            vedio_l6_continue_thi->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov5_thi->setText(QString::number(value));
            break;
        case 11:
            continue_vertical6_thi->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue6_thi->setValue(value);
            break;
        case 13:
            vedio_spby_continue6_thi->setValue(value);
            break;
        case 14:
            vedio_l7_continue_thi->setText(QString::number(value));
            break;
        case 15:
            vedio_continue_Fov6_thi->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk71(int field, float value)
{
    switch(field)
    {
        case 0:
            continue_vertical7_thi->setText(QString::number(value));
            break;
        case 1:
            vedio_spbx_continue7_thi->setValue(value);
            break;
        case 2:
            vedio_spby_continue7_thi->setValue(value);
            break;
        case 3:
            test_1_thi->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk72(int field, float value)
{
    int valuei = (int)value;

    if(5 == field)
    {
        if(0 == valuei)
            showvedioCfg4();
        else if(1 == valuei)
            vedio_btnSensor1SwitchSlot_fou();
        else if(2 == valuei)
            vedio_btnSensor2ContinueSlot_fou();
    }

    if(vedio_current_shichang_fou == 0)
    {
        switch(field)
        {
            case 0:
                fixChanelNum_fou->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                fixenable_fou->setChecked(valuei);
                break;
            case 3:
                fix_vediohaveornot_fou->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    fix_vedio_dpi_fou->setCurrentIndex(0);
                if(valuei == 1)
                    fix_vedio_dpi_fou->setCurrentIndex(1);
                if(valuei == 2)
                    fix_vedio_dpi_fou->setCurrentIndex(2);
                if(valuei == 3)
                    fix_vedio_dpi_fou->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                fix_gateshow_fou->setChecked(valuei);
                break;
            case 8:
                fix_bullshow_fou->setChecked(valuei);
                break;
            case 9:
                fix_autogate_fou->setChecked(valuei);
                break;
            case 10:
                fix_gate_sizex_fou->setText(QString::number(value));
                break;
            case 11:
                fix_gate_sizey_fou->setText(QString::number(value));
                break;
            case 12:
                fix_gatelocationx_fou->setText(QString::number(value));
                break;
            case 13:
                fix_gatelocationy_fou->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_fou == 1)
    {
        switch(field)
        {
            case 0:
                ChanelNum_fou->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                enable_fou->setChecked(valuei);
                break;
            case 3:
                vediohaveornot_fou->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    vedio_dpi_fou->setCurrentIndex(0);
                if(valuei == 1)
                    vedio_dpi_fou->setCurrentIndex(1);
                if(valuei == 2)
                    vedio_dpi_fou->setCurrentIndex(2);
                if(valuei == 3)
                    vedio_dpi_fou->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                gateshow_fou->setChecked(valuei);
                break;
            case 8:
                bullshow_fou->setChecked(valuei);
                break;
            case 9:
                autogate_fou->setChecked(valuei);
                break;
            case 10:
                gate_sizex_fou->setText(QString::number(value));
                break;
            case 11:
                gate_sizey_fou->setText(QString::number(value));
                break;
            case 12:
                gatelocationx_fou->setText(QString::number(value));
                break;
            case 13:
                gatelocationy_fou->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_fou == 2)
    {
        switch(field)
        {
            case 0:
                continueChanelNum_fou->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                continueenable_fou->setChecked(valuei);
                break;
            case 3:
                continue_vediohaveornot_fou->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    continue_vedio_dpi_fou->setCurrentIndex(0);
                if(valuei == 1)
                    continue_vedio_dpi_fou->setCurrentIndex(1);
                if(valuei == 2)
                    continue_vedio_dpi_fou->setCurrentIndex(2);
                if(valuei == 3)
                    continue_vedio_dpi_fou->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                continue_gateshow_fou->setChecked(valuei);
                break;
            case 8:
                continue_bullshow_fou->setChecked(valuei);
                break;
            case 9:
                continue_autogate_fou->setChecked(valuei);
                break;
            case 10:
                continue_gate_sizex_fou->setText(QString::number(value));
                break;
            case 11:
                continue_gate_sizey_fou->setText(QString::number(value));
                break;
            case 12:
                continue_gatelocationx_fou->setText(QString::number(value));
                break;
            case 13:
                continue_gatelocationy_fou->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
}

void MainWindow::showblk73(int field, float value)
{
    switch(field)
    {
        case 0:
            fix_lEdt_fou->setText(QString::number(value));
            break;
        case 1:
            fix_vertical_fou->setText(QString::number(value));
            break;
        case 2:
            fix_sp_fou->setValue(value);
            break;
        case 3:
            fix_sp2_fou->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk74(int field, float value)
{
    int valuei = (int)value;
    switch(field)
    {
        case 0:
            vedio_fovclass_fou->setCurrentIndex(valuei);
            break;
        case 1:
            vedio_s1_Fov0_fou->setText(QString::number(value));
            break;
        case 2:
            Change_vertical1_fou->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch1_fou->setValue(value);
            break;
        case 4:
            vedio_spby_switch1_fou->setValue(value);
            break;
        case 5:
            vedio_s1_Fov1_fou->setText(QString::number(value));
            break;
        case 6:
            Change_vertical2_fou->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_switch2_fou->setValue(value);
            break;
        case 8:
            vedio_spby_switch2_fou->setValue(value);
            break;
        case 9:
            vedio_s1_Fov2_fou->setText(QString::number(value));
            break;
        case 10:
            Change_vertical3_fou->setText(QString::number(value));
            break;
        case 11:
            vedio_spbx_switch3_fou->setValue(value);
            break;
        case 12:
            vedio_spby_switch3_fou->setValue(value);
            break;
        case 13:
            vedio_s1_Fov3_fou->setText(QString::number(value));
            break;
        case 14:
            Change_vertical4_fou->setText(QString::number(value));
            break;
        case 15:
            vedio_spbx_switch4_fou->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk75(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spby_switch4_fou->setValue(value);
            break;
        case 1:
            vedio_s1_Fov4_fou->setText(QString::number(value));
            break;
        case 2:
            Change_vertical5_fou->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch5_fou->setValue(value);
            break;
        case 4:
            vedio_spby_switch5_fou->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk76(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l1_continue_fou->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov0_fou->setText(QString::number(value));
            break;
        case 2:
            continue_vertical1_fou->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue1_fou->setValue(value);
            break;
        case 4:
            vedio_spby_continue1_fou->setValue(value);
            break;
        case 5:
            vedio_l2_continue_fou->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov1_fou->setText(QString::number(value));
            break;
        case 7:
            continue_vertical2_fou->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue2_fou->setValue(value);
            break;
        case 9:
            vedio_spby_continue2_fou->setValue(value);
            break;
        case 10:
            vedio_l3_continue_fou->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov2_fou->setText(QString::number(value));
            break;
        case 12:
            continue_vertical3_fou->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue3_fou->setValue(value);
            break;
        case 14:
            vedio_spby_continue3_fou->setValue(value);
            break;
        case 15:
            vedio_l4_continue_fou->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk77(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov3_fou->setText(QString::number(value));
            break;
        case 1:
            continue_vertical4_fou->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue4_fou->setValue(value);
            break;
        case 3:
            vedio_spby_continue4_fou->setValue(value);
            break;
        case 4:
            vedio_l5_continue_fou->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov4_fou->setText(QString::number(value));
            break;
        case 6:
            continue_vertical5_fou->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue5_fou->setValue(value);
            break;
        case 8:
            vedio_spby_continue5_fou->setValue(value);
            break;
        case 9:
            vedio_l6_continue_fou->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov5_fou->setText(QString::number(value));
            break;
        case 11:
            continue_vertical6_fou->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue6_fou->setValue(value);
            break;
        case 13:
            vedio_spby_continue6_fou->setValue(value);
            break;
        case 14:
            vedio_l7_continue_fou->setText(QString::number(value));
            break;
        case 15:
            vedio_continue_Fov6_fou->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk78(int field, float value)
{
    switch(field)
    {
        case 0:
            continue_vertical7_fou->setText(QString::number(value));
            break;
        case 1:
            vedio_spbx_continue7_fou->setValue(value);
            break;
        case 2:
            vedio_spby_continue7_fou->setValue(value);
            break;
        case 3:
            test_1_fou->setText(QString::number(value));
            break;
        default:
            break;
    }
}

void MainWindow::showblk79(int field, float value)
{
    int valuei = (int)value;

    if(5 == field)
    {
        if(0 == valuei)
            showvedioCfg5();
        else if(1 == valuei)
            vedio_btnSensor1SwitchSlot_fif();
        else if(2 == valuei)
            vedio_btnSensor2ContinueSlot_fif();
    }

    if(vedio_current_shichang_fif == 0)
    {
        switch(field)
        {
            case 0:
                fixChanelNum_fif->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                fixenable_fif->setChecked(valuei);
                break;
            case 3:
                fix_vediohaveornot_fif->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    fix_vedio_dpi_fif->setCurrentIndex(0);
                if(valuei == 1)
                    fix_vedio_dpi_fif->setCurrentIndex(1);
                if(valuei == 2)
                    fix_vedio_dpi_fif->setCurrentIndex(2);
                if(valuei == 3)
                    fix_vedio_dpi_fif->setCurrentIndex(3);
                if(valuei == 4)
                    fix_vedio_dpi_fif->setCurrentIndex(4);
                break;
            case 6:
                break;
            case 7:
                fix_gateshow_fif->setChecked(valuei);
                break;
            case 8:
                fix_bullshow_fif->setChecked(valuei);
                break;
            case 9:
                fix_autogate_fif->setChecked(valuei);
                break;
            case 10:
                fix_gate_sizex_fif->setText(QString::number(value));
                break;
            case 11:
                fix_gate_sizey_fif->setText(QString::number(value));
                break;
            case 12:
                fix_gatelocationx_fif->setText(QString::number(value));
                break;
            case 13:
                fix_gatelocationy_fif->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_fif == 1)
    {
        switch(field)
        {
            case 0:
                ChanelNum_fif->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                enable_fif->setChecked(valuei);
                break;
            case 3:
                vediohaveornot_fif->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    vedio_dpi_fif->setCurrentIndex(0);
                if(valuei == 1)
                    vedio_dpi_fif->setCurrentIndex(1);
                if(valuei == 2)
                    vedio_dpi_fif->setCurrentIndex(2);
                if(valuei == 3)
                    vedio_dpi_fif->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                gateshow_fif->setChecked(valuei);
                break;
            case 8:
                bullshow_fif->setChecked(valuei);
                break;
            case 9:
                autogate_fif->setChecked(valuei);
                break;
            case 10:
                gate_sizex_fif->setText(QString::number(value));
                break;
            case 11:
                gate_sizey_fif->setText(QString::number(value));
                break;
            case 12:
                gatelocationx_fif->setText(QString::number(value));
                break;
            case 13:
                gatelocationy_fif->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
    if(vedio_current_shichang_fif == 2)
    {
        switch(field)
        {
            case 0:
                continueChanelNum_fif->setChecked(valuei);
                break;
            case 1:
                break;
            case 2:
                continueenable_fif->setChecked(valuei);
                break;
            case 3:
                continue_vediohaveornot_fif->setChecked(valuei);
                break;
            case 4:
                if(valuei == 0)
                    continue_vedio_dpi_fif->setCurrentIndex(0);
                if(valuei == 1)
                    continue_vedio_dpi_fif->setCurrentIndex(1);
                if(valuei == 2)
                    continue_vedio_dpi_fif->setCurrentIndex(2);
                if(valuei == 3)
                    continue_vedio_dpi_fif->setCurrentIndex(3);
                break;
            case 6:
                break;
            case 7:
                continue_gateshow_fif->setChecked(valuei);
                break;
            case 8:
                continue_bullshow_fif->setChecked(valuei);
                break;
            case 9:
                continue_autogate_fif->setChecked(valuei);
                break;
            case 10:
                continue_gate_sizex_fif->setText(QString::number(value));
                break;
            case 11:
                continue_gate_sizey_fif->setText(QString::number(value));
                break;
            case 12:
                continue_gatelocationx_fif->setText(QString::number(value));
                break;
            case 13:
                continue_gatelocationy_fif->setText(QString::number(value));
                break;
            default:
                break;
        }
    }
}

void MainWindow::showblk80(int field, float value)
{
    switch(field)
    {
        case 0:
            fix_lEdt_fif->setText(QString::number(value));
            break;
        case 1:
            fix_vertical_fif->setText(QString::number(value));
            break;
        case 2:
            fix_sp_fif->setValue(value);
            break;
        case 3:
            fix_sp2_fif->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk81(int field, float value)
{
    int valuei = (int)value;
    switch(field)
    {
        case 0:
            vedio_fovclass_fif->setCurrentIndex(valuei);
            break;
        case 1:
            vedio_s1_Fov0_fif->setText(QString::number(value));
            break;
        case 2:
            Change_vertical1_fif->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch1_fif->setValue(value);
            break;
        case 4:
            vedio_spby_switch1_fif->setValue(value);
            break;
        case 5:
            vedio_s1_Fov1_fif->setText(QString::number(value));
            break;
        case 6:
            Change_vertical2_fif->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_switch2_fif->setValue(value);
            break;
        case 8:
            vedio_spby_switch2_fif->setValue(value);
            break;
        case 9:
            vedio_s1_Fov2_fif->setText(QString::number(value));
            break;
        case 10:
            Change_vertical3_fif->setText(QString::number(value));
            break;
        case 11:
            vedio_spbx_switch3_fif->setValue(value);
            break;
        case 12:
            vedio_spby_switch3_fif->setValue(value);
            break;
        case 13:
            vedio_s1_Fov3_fif->setText(QString::number(value));
            break;
        case 14:
            Change_vertical4_fif->setText(QString::number(value));
            break;
        case 15:
            vedio_spbx_switch4_fif->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk82(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spby_switch4_fif->setValue(value);
            break;
        case 1:
            vedio_s1_Fov4_fif->setText(QString::number(value));
            break;
        case 2:
            Change_vertical5_fif->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_switch5_fif->setValue(value);
            break;
        case 4:
            vedio_spby_switch5_fif->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::showblk83(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l1_continue_fif->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov0_fif->setText(QString::number(value));
            break;
        case 2:
            continue_vertical1_fif->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue1_fif->setValue(value);
            break;
        case 4:
            vedio_spby_continue1_fif->setValue(value);
            break;
        case 5:
            vedio_l2_continue_fif->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov1_fif->setText(QString::number(value));
            break;
        case 7:
            continue_vertical2_fif->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue2_fif->setValue(value);
            break;
        case 9:
            vedio_spby_continue2_fif->setValue(value);
            break;
        case 10:
            vedio_l3_continue_fif->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov2_fif->setText(QString::number(value));
            break;
        case 12:
            continue_vertical3_fif->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue3_fif->setValue(value);
            break;
        case 14:
            vedio_spby_continue3_fif->setValue(value);
            break;
        case 15:
            vedio_l4_continue_fif->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk84(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov3_fif->setText(QString::number(value));
            break;
        case 1:
            continue_vertical4_fif->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue4_fif->setValue(value);
            break;
        case 3:
            vedio_spby_continue4_fif->setValue(value);
            break;
        case 4:
            vedio_l5_continue_fif->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov4_fif->setText(QString::number(value));
            break;
        case 6:
            continue_vertical5_fif->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue5_fif->setValue(value);
            break;
        case 8:
            vedio_spby_continue5_fif->setValue(value);
            break;
        case 9:
            vedio_l6_continue_fif->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov5_fif->setText(QString::number(value));
            break;
        case 11:
            continue_vertical6_fif->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue6_fif->setValue(value);
            break;
        case 13:
            vedio_spby_continue6_fif->setValue(value);
            break;
        case 14:
            vedio_l7_continue_fif->setText(QString::number(value));
            break;
        case 15:
            vedio_continue_Fov6_fif->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk85(int field, float value)
{
    switch(field)
    {
        case 0:
            continue_vertical7_fif->setText(QString::number(value));
            break;
        case 1:
            vedio_spbx_continue7_fif->setValue(value);
            break;
        case 2:
            vedio_spby_continue7_fif->setValue(value);
            break;
        case 3:
            test_1_fif->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk111(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l8_continue->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov7->setText(QString::number(value));
            break;
        case 2:
            continue_vertical8->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue8->setValue(value);
            break;
        case 4:
            vedio_spby_continue8->setValue(value);
            break;
        case 5:
            vedio_l9_continue->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov8->setText(QString::number(value));
            break;
        case 7:
            continue_vertical9->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue9->setValue(value);
            break;
        case 9:
            vedio_spby_continue9->setValue(value);
            break;
        case 10:
            vedio_l10_continue->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov9->setText(QString::number(value));
            break;
        case 12:
            continue_vertical10->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue10->setValue(value);
            break;
        case 14:
            vedio_spby_continue10->setValue(value);
            break;
        case 15:
            vedio_l11_continue->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk112(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov10->setText(QString::number(value));
            break;
        case 1:
            continue_vertical11->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue11->setValue(value);
            break;
        case 3:
            vedio_spby_continue11->setValue(value);
            break;
        case 4:
            vedio_l12_continue->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov11->setText(QString::number(value));
            break;
        case 6:
            continue_vertical12->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue12->setValue(value);
            break;
        case 8:
            vedio_spby_continue12->setValue(value);
            break;
        case 9:
            vedio_l13_continue->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov12->setText(QString::number(value));
            break;
        case 11:
            continue_vertical13->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue13->setValue(value);
            break;
        case 13:
            vedio_spby_continue13->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk113(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l8_continue_sec->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov7_sec->setText(QString::number(value));
            break;
        case 2:
            continue_vertical8_sec->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue8_sec->setValue(value);
            break;
        case 4:
            vedio_spby_continue8_sec->setValue(value);
            break;
        case 5:
            vedio_l9_continue_sec->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov8_sec->setText(QString::number(value));
            break;
        case 7:
            continue_vertical9_sec->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue9_sec->setValue(value);
            break;
        case 9:
            vedio_spby_continue9_sec->setValue(value);
            break;
        case 10:
            vedio_l10_continue_sec->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov9_sec->setText(QString::number(value));
            break;
        case 12:
            continue_vertical10_sec->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue10_sec->setValue(value);
            break;
        case 14:
            vedio_spby_continue10_sec->setValue(value);
            break;
        case 15:
            vedio_l11_continue_sec->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk114(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov10_sec->setText(QString::number(value));
            break;
        case 1:
            continue_vertical11_sec->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue11_sec->setValue(value);
            break;
        case 3:
            vedio_spby_continue11_sec->setValue(value);
            break;
        case 4:
            vedio_l12_continue_sec->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov11_sec->setText(QString::number(value));
            break;
        case 6:
            continue_vertical12_sec->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue12_sec->setValue(value);
            break;
        case 8:
            vedio_spby_continue12_sec->setValue(value);
            break;
        case 9:
            vedio_l13_continue_sec->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov12_sec->setText(QString::number(value));
            break;
        case 11:
            continue_vertical13_sec->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue13_sec->setValue(value);
            break;
        case 13:
            vedio_spby_continue13_sec->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk115(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l8_continue_thi->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov7_thi->setText(QString::number(value));
            break;
        case 2:
            continue_vertical8_thi->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue8_thi->setValue(value);
            break;
        case 4:
            vedio_spby_continue8_thi->setValue(value);
            break;
        case 5:
            vedio_l9_continue_thi->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov8_thi->setText(QString::number(value));
            break;
        case 7:
            continue_vertical9_thi->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue9_thi->setValue(value);
            break;
        case 9:
            vedio_spby_continue9_thi->setValue(value);
            break;
        case 10:
            vedio_l10_continue_thi->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov9_thi->setText(QString::number(value));
            break;
        case 12:
            continue_vertical10_thi->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue10_thi->setValue(value);
            break;
        case 14:
            vedio_spby_continue10_thi->setValue(value);
            break;
        case 15:
            vedio_l11_continue_thi->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk116(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov10_thi->setText(QString::number(value));
            break;
        case 1:
            continue_vertical11_thi->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue11_thi->setValue(value);
            break;
        case 3:
            vedio_spby_continue11_thi->setValue(value);
            break;
        case 4:
            vedio_l12_continue_thi->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov11_thi->setText(QString::number(value));
            break;
        case 6:
            continue_vertical12_thi->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue12_thi->setValue(value);
            break;
        case 8:
            vedio_spby_continue12_thi->setValue(value);
            break;
        case 9:
            vedio_l13_continue_thi->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov12_thi->setText(QString::number(value));
            break;
        case 11:
            continue_vertical13_thi->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue13_thi->setValue(value);
            break;
        case 13:
            vedio_spby_continue13_thi->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk117(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l8_continue_fou->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov7_fou->setText(QString::number(value));
            break;
        case 2:
            continue_vertical8_fou->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue8_fou->setValue(value);
            break;
        case 4:
            vedio_spby_continue8_fou->setValue(value);
            break;
        case 5:
            vedio_l9_continue_fou->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov8_fou->setText(QString::number(value));
            break;
        case 7:
            continue_vertical9_fou->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue9_fou->setValue(value);
            break;
        case 9:
            vedio_spby_continue9_fou->setValue(value);
            break;
        case 10:
            vedio_l10_continue_fou->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov9_fou->setText(QString::number(value));
            break;
        case 12:
            continue_vertical10_fou->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue10_fou->setValue(value);
            break;
        case 14:
            vedio_spby_continue10_fou->setValue(value);
            break;
        case 15:
            vedio_l11_continue_fou->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk118(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov10_fou->setText(QString::number(value));
            break;
        case 1:
            continue_vertical11_fou->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue11_fou->setValue(value);
            break;
        case 3:
            vedio_spby_continue11_fou->setValue(value);
            break;
        case 4:
            vedio_l12_continue_fou->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov11_fou->setText(QString::number(value));
            break;
        case 6:
            continue_vertical12_fou->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue12_fou->setValue(value);
            break;
        case 8:
            vedio_spby_continue12_fou->setValue(value);
            break;
        case 9:
            vedio_l13_continue_fou->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov12_fou->setText(QString::number(value));
            break;
        case 11:
            continue_vertical13_fou->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue13_fou->setValue(value);
            break;
        case 13:
            vedio_spby_continue13_fou->setValue(value);
            break;
        default:
            break;
    }
}

void MainWindow::showblk119(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_l8_continue_fif->setText(QString::number(value));
            break;
        case 1:
            vedio_continue_Fov7_fif->setText(QString::number(value));
            break;
        case 2:
            continue_vertical8_fif->setText(QString::number(value));
            break;
        case 3:
            vedio_spbx_continue8_fif->setValue(value);
            break;
        case 4:
            vedio_spby_continue8_fif->setValue(value);
            break;
        case 5:
            vedio_l9_continue_fif->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov8_fif->setText(QString::number(value));
            break;
        case 7:
            continue_vertical9_fif->setText(QString::number(value));
            break;
        case 8:
            vedio_spbx_continue9_fif->setValue(value);
            break;
        case 9:
            vedio_spby_continue9_fif->setValue(value);
            break;
        case 10:
            vedio_l10_continue_fif->setText(QString::number(value));
            break;
        case 11:
            vedio_continue_Fov9_fif->setText(QString::number(value));
            break;
        case 12:
            continue_vertical10_fif->setText(QString::number(value));
            break;
        case 13:
            vedio_spbx_continue10_fif->setValue(value);
            break;
        case 14:
            vedio_spby_continue10_fif->setValue(value);
            break;
        case 15:
            vedio_l11_continue_fif->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::showblk120(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov10_fif->setText(QString::number(value));
            break;
        case 1:
            continue_vertical11_fif->setText(QString::number(value));
            break;
        case 2:
            vedio_spbx_continue11_fif->setValue(value);
            break;
        case 3:
            vedio_spby_continue11_fif->setValue(value);
            break;
        case 4:
            vedio_l12_continue_fif->setText(QString::number(value));
            break;
        case 5:
            vedio_continue_Fov11_fif->setText(QString::number(value));
            break;
        case 6:
            continue_vertical12_fif->setText(QString::number(value));
            break;
        case 7:
            vedio_spbx_continue12_fif->setValue(value);
            break;
        case 8:
            vedio_spby_continue12_fif->setValue(value);
            break;
        case 9:
            vedio_l13_continue_fif->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov12_fif->setText(QString::number(value));
            break;
        case 11:
            continue_vertical13_fif->setText(QString::number(value));
            break;
        case 12:
            vedio_spbx_continue13_fif->setValue(value);
            break;
        case 13:
            vedio_spby_continue13_fif->setValue(value);
            break;
        default:
            break;
    }
}

