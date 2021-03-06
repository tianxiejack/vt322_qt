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
    for(int n = 4; n<len-1; n++) {
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

extern QString ShowHex(QByteArray str);
void MainWindow::setrecvbytes(QByteArray datagram)
{
    QString rcvBuf;
    rcvBuf = ShowHex(datagram);
    //ui->textEdit->setTextColor(QColor(Qt::blue));
    //ui->textEdit->append(rcvBuf);
}

void MainWindow::output_to_label(int i)//解析下位机的反馈信息,从串口读到正确的一帧数据的时候执行此函数。
{
    float value_i;
    int value_inte;
    QString msg;
    QByteArray   ba;
    bool osd_judgment=(output_array[1] == 7) || (output_array[1] == 8)|| (output_array[1] == 9)||(output_array[1] == 10)\
                      ||(output_array[1] == 11) || (output_array[1] == 12)|| (output_array[1] == 13)||(output_array[1] == 14)\
                      ||(output_array[1] == 15) || (output_array[1] == 16)|| (output_array[1] == 17)||(output_array[1] == 18)\
                      ||(output_array[1] == 19) || (output_array[1] == 20)|| (output_array[1] == 21)||(output_array[1] == 22)\
                      ||(output_array[1] == 30) || (output_array[1] == 31)|| (output_array[1] == 32)||(output_array[1] == 33)\
                      ||(output_array[1] == 34) || (output_array[1] == 35)|| (output_array[1] == 36)||(output_array[1] == 37)\
                      ||(output_array[1] == 38) || (output_array[1] == 39)|| (output_array[1] == 40)||(output_array[1] == 41)\
                      ||(output_array[1] == 42) || (output_array[1] == 43)|| (output_array[1] == 44)||(output_array[1] == 45);
    if(osd_judgment && (output_array[2]==0x04)){
      QByteArray dd((char*)output_array+3, data_length-3);
      ba=dd;

    }else{
        memcpy(&value_i,output_array+3,4);
        memcpy(&value_inte,output_array+3,4);
    }

    if((0x41 == i) || (0x10 == i))
    {
        unsigned short value_int = (output_array[1] | (output_array[2]<<8));
        unsigned short value_int2 = (output_array[3] | (output_array[4]<<8));
        if(w_input->show_stat)
        {
            ledt_search_azimuth->setText(QString::number(value_int));
            ledt_search_pitch->setText(QString::number(value_int2));
        }
    }
    else if((0x42 == i) || (0x12 == i))
    {
        unsigned short value_int = (output_array[1] | (output_array[2]<<8));
        if(w_input->show_stat)
            ledt_search_zoom->setText(QString::number(value_int));
    }
    else if(0x43 == i)
    {
        int curstat = output_array[1];
        int outputtype = output_array[2];
        float errorx, errory;
        memcpy(&errorx, output_array + 3, 4);
        memcpy(&errory, output_array + 7, 4);
        //short errorx = (output_array_6[3] | (output_array_6[4]<<8));
        //short errory = (output_array_6[5] | (output_array_6[6]<<8));

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
            case 0x03:
                rto_currstat->setText("目标丢失");
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
    else if((0x52 == i) || (0x51 == i)){
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
            case 2:
                if(0 == output_array[2])
                {
                    switch(value_inte)
                    {
                        case 0:
                            commway->setCurrentIndex(0);
                            break;
                        case 1:
                            commway->setCurrentIndex(1);
                            break;
                        case 2:
                            commway->setCurrentIndex(2);
                            break;
                        default:
                            break;
                    }
                }
                else if(1 == output_array[2])
                {
                    switch(value_inte)
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
                else if(2 == output_array[2])
                {
                    switch(value_inte)
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
                else if(3 == output_array[2])
                {
                    switch(value_inte)
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
                            /*
                        case 3:
                            parity_bit_sec->setCurrentIndex(3);
                            break;
                            */
                        case 4:
                            parity_bit_sec->setCurrentIndex(3);
                            break;
                        default:
                            break;
                     }
                }
                else if(4 == output_array[2])
                {
                    if(value_i < 1.5)
                    {
                        stop_bit_sec->setCurrentIndex(0);
                    }else //if((value_i > 1) && (value_i < 2))
                    {
                        stop_bit_sec->setCurrentIndex(1);
                    }/*else if(value_i > 1.5)
                    {
                        stop_bit_sec->setCurrentIndex(2);
                    }*/
                }
                else if(5 == output_array[2])
                {
                    if(value_inte==1)
                    {
                        flow_control_sec->setCurrentIndex(0);
                    }else if(value_inte==2)
                    {
                        flow_control_sec->setCurrentIndex(1);
                    }else if(value_inte==3)
                    {
                        flow_control_sec->setCurrentIndex(2);
                    }/*else if(value_inte==4)
                    {
                        flow_control_sec->setCurrentIndex(3);
                    }*/
                }
                else if(6 == output_array[2])
                {
                    unsigned int value_uinte = value_inte;//= (unsigned int)value_inte;
                    QString str = intip2string(value_uinte);
                    netip->setText(str);
                }
                else if(7 == output_array[2])
                {
                    netport->setText(QString::number(value_inte));
                }
                else if(8 == output_array[2])
                {
                    if(value_inte==0)
                    {
                        platprotocol->setCurrentIndex(0);
                    }else if(value_inte==1)
                    {
                        platprotocol->setCurrentIndex(1);
                    }
                }
                else if(9 == output_array[2])
                {
                    out_address_sec->setText(QString::number(value_inte));
                }
                else if(10 == output_array[2])
                {
                    platparam2->setText(QString::number(value_inte));
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
            case 45:
                if(w_osd1->show_stat)
                {
                    if(output_array[1] < 23)
                        c->setCurrentIndex(output_array[1] - 7);
                    else
                        c->setCurrentIndex(output_array[1] - 14);
                    switch(output_array[2])
                    {
                        case 0:
                            checkBox_osdshow->setChecked(value_inte);
                            break;
                        case 1:
                             osd1_pos_x->setText(QString::number(value_inte));
                            break;
                        case 2:
                             osd1_pos_y->setText(QString::number(value_inte));
                            break;
                        case 3:
                            if(0x01 == value_inte)
                                CBox_datatype->setCurrentIndex(0);
                            break;
                        case 4:
                             osd1_lineEdit_context->setText(msg.fromUtf8(ba));
                            break;
                        case 5:
                            CBox_color->setCurrentIndex(value_inte-1);
                            break;
                        case 6:
                           CBox_transparency->setCurrentIndex(value_inte);
                            break;
                        case 7:
                            CBox_font->setCurrentIndex(value_inte-1);
                            break;
                        case 8:
                           CBox_font_size->setCurrentIndex(value_inte - 1);
                            break;
                    }
                }
                break;
            case 23:
            case 56:
            case 63:
            case 70:
            case 77:
                show_blk_input1(output_array[2],value_i,value_inte);
                break;
            case 24:
            case 57:
            case 64:
            case 71:
            case 78:
                show_blk_input2(output_array[2],value_i,value_inte);
                break;
            case 25:
            case 58:
            case 65:
            case 72:
            case 79:
                show_blk_input3(output_array[2],value_i);
                break;
            case 26:
            case 59:
            case 66:
            case 73:
            case 80:
                show_blk_input4(output_array[2],value_i);
                break;
            case 27:
            case 60:
            case 67:
            case 74:
            case 81:
                show_blk_input5(output_array[2],value_i);
                break;
            case 28:
            case 61:
            case 68:
            case 75:
            case 82:
                show_blk_input6(output_array[2],value_i);
                break;
            case 29:
            case 62:
            case 69:
            case 76:
            case 83:
                show_blk_input7(output_array[2],value_i, value_inte);
                break;



            case 51:
                if(2 == output_array[2])
                {
                    int index = value_inte;
                    if((index >= 0) && (index <= 4))
                        box_defaultcapchid->setCurrentIndex(index);
                }
                else if(4 == output_array[2])
                {
                    int index = value_inte;
                    if((index >= 0) && (index <= 3))
                        box_outresol->setCurrentIndex(index);
                    else if((index >= 5) && (index <= 9))
                        box_outresol->setCurrentIndex(index - 1);
                }
                else if(5 == output_array[2])
                {
                    int index = value_inte;
                    if((index >= 0) && (index <= 3))
                        box_outresol2->setCurrentIndex(index);
                    else if((index >= 5) && (index <= 9))
                        box_outresol2->setCurrentIndex(index - 1);
                }
                else if(6 == output_array[2])
                {
                    if(value_inte)
                        compress_enable->setChecked(true);
                    else
                        compress_enable->setChecked(false);
                    break;
                }
                else if(7 == output_array[2])
                {
                    int index = value_inte;
                    if(index == 1)
                        box_outresol2->setCurrentIndex(0);
                }
                else if(8 == output_array[2])
                {
                    unsigned int value_uinte = value_inte;//= (unsigned int)value_inte;
                    QString str = intip2string(value_uinte);
                    compress_ip->setText(str);
                }
                else if(9 == output_array[2])
                {
                    compress_port->setText(QString::number(value_inte));
                }
                break;

            case 52:
                if(w_osd1->show_stat)
                {
                    if(1 == output_array[2])
                    {
                        sysosd_state = value_inte;
                        int i = c_sysosd->currentIndex();
                        checkBox_sysosd->setChecked(sysosd_state & (1 << i));

                    }

                    else if(2 == output_array[2])
                    {
                        if(value_inte)
                            cusosd_open->setChecked(true);
                        else
                            cusosd_close->setChecked(true);
                    }

                }
                break;
            case 54:
                if(0 == output_array[2])
                {
                    switch(value_inte)
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
                else if(1 == output_array[2])
                {
                    maxnum->setText(QString::number(value_inte));
                }
                else if(2 == output_array[2])
                {
                       uspeed->setText(QString::number(value_inte));
                }
                else if(3 == output_array[2])
                {
                    maxpix->setText(QString::number(value_inte));
                }
                else if(4 == output_array[2])
                {
                    minpix->setText(QString::number(value_inte));
                }
                else if(5 == output_array[2])
                {
                    //sensitive->setText(QString::number(value_inte));
                }
                else if(6 == output_array[2])
                {
                    dspeed->setText(QString::number(value_inte));
                }
                else if(7 == output_array[2])
                {
                    trktime->setText(QString::number(value_inte));
                }
                else if(8 == output_array[2])
                {
                    switch(value_inte)
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
                break;
            case 55:
                if(0 == output_array[2])
                    presetx->setText(QString::number(value_inte));
                else if(1 == output_array[2])
                    presety->setText(QString::number(value_inte));
                else if(2 == output_array[2])
                    presetzoom->setText(QString::number(value_inte));
                else if(3 == output_array[2])
                    presetid->setText(QString::number(value_inte));
                else if(4 == output_array[2])
                {
                    switch(value_inte)
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
                else if(5 == output_array[2])
                {
                    switch(value_inte)
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
                else if(6 == output_array[2])
                    Alarm_delay->setText(QString::number(value_inte));
                break;

            case 101:
                if(w_pid2->show_stat)
                {
                    switch (output_array[2]){
                        case 1:
                            kp1_pid2->setText(QString::number(value_i));
                            break;
                        case 2:
                            ki1_pid2->setText(QString::number(value_i));
                            break;
                        case 3:
                            kd1_pid2->setText(QString::number(value_i));
                            break;
                        case 4:
                            k12->setText(QString::number(value_i));
                            break;
                        case 5:
                            kp2_pid2->setText(QString::number(value_i));
                            break;
                        case 6:
                            ki2_pid2->setText(QString::number(value_i));
                            break;
                        case 7:
                            kd2_pid2->setText(QString::number(value_i));
                            break;
                        case 8:
                            k22->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
 /*
            case 102:
                if(w_pid2->show_stat)
                {
                    switch (output_array[2]){
                        case 0:
                            kx_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 1:
                            ky_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 2:
                            errx_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 3:
                            erry_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 4:
                            time_lineEdt2->setText(QString::number(value_i));
                            break;
                        case 5:
                            x_ratio_control2->setText(QString::number(value_i));
                            break;
                        case 6:
                            y_ratio_control2->setText(QString::number(value_i));
                            break;
                    }
                }
                break;
*/
            default:
                break;
        }
    }
    else if(0x54 == i)
    {
       if(output_array[1] != 0)
           read_config(output_array[1]);
       else
       {
           if(w_plat->show_stat)
           {
                read_config(1);
           }
           if(w_speedconv_sec->show_stat)
           {
               read_config(2);
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
                read_config(get_osd_blk(c));
                read_config(52);
           }
           if(w_input->show_stat)
           {
                int startblock = -1;
                if(1 == cur_channel)
                    startblock = 23;
                else if(2 == startblock)
                    startblock = 56;
                else if(3 == startblock)
                    startblock = 63;
                else if(4 == startblock)
                    startblock = 70;
                else if(5 == startblock)
                    startblock = 77;

                if(startblock > 0)
                {
                    for(int i = startblock; i < startblock + 7; i++)
                        read_config(i);
                }

           }
           if(w_mtd->show_stat)
           {
               read_config(54);
               read_config(55);
           }
           if(w_pid2->show_stat)
           {
               read_config(101);
               read_config(102);
           }      
       }
    }
    memset(output_array,0,sizeof(output_array));
}

void MainWindow::read_config(int block)
{
    switch(block)
    {
        case 1:
            send_read_config(block,0,6);
            send_read_config(block,9,12);
            break;
        case 2:
            send_read_config(block,0,10);
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
        case 45:
            send_read_config(block,0,8);
            break;
        case 23:
        case 56:
        case 63:
        case 70:
        case 77:
            send_read_config(block,6,6);
            send_read_config(block,1,5);
            send_read_config(block,7,13);
            break;
        case 24:
        case 57:
        case 64:
        case 71:
        case 78:
            send_read_config(block,0,0);
            send_read_config(block,2,15);
            break;
        case 25:
        case 58:
        case 65:
        case 72:
        case 79:
            send_read_config(block,0,11);
            break;
        case 26:
        case 59:
        case 66:
        case 73:
        case 80:
            send_read_config(block,3,15);
            break;
        case 27:
        case 60:
        case 67:
        case 74:
        case 81:
            send_read_config(block,0,15);
            break;
        case 28:
        case 61:
        case 68:
        case 75:
        case 82:
            send_read_config(block,0,9);
        case 29:
        case 62:
        case 69:
        case 76:
        case 83:
            send_read_config(block,0,0);
            send_read_config(block,2,9);
            break;
        case 51:
            send_read_config(block,2,2);
            send_read_config(block,4,9);
            break;
        case 52:
            send_read_config(block,1,2);
            break;
        case 54:
            send_read_config(block,0,4);
            send_read_config(block,6,8);
            break;
        case 55:
            send_read_config(block,0,6);
            break;
        case 101:
            send_read_config(block,1,8);
            break;
        case 102:
            send_read_config(block,0,6);
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

void MainWindow::show_blk_input1(int field, float value, int value_inte)
{
    switch(field)
    {
        case 1:
            if((value_inte >= 0) && (value_inte <= 31))
            input_osdid->setCurrentIndex(value_inte);
            break;
        case 2:
            if((0 == value_inte) || (1 == value_inte))
                input_chroma->setCurrentIndex(value_inte);
            break;
        case 3:
            if(value_inte)
                input_vediohaveornot->setChecked(true);
            else
                input_vediohaveornot->setChecked(false);
            break;
        case 4:
            if(0 == value_inte)
                input_vedio_dpi->setCurrentIndex(0);
            else if(1 == value_inte)
                input_vedio_dpi->setCurrentIndex(1);
            else if(5 == value_inte)
                input_vedio_dpi->setCurrentIndex(2);
            else if(2 == value_inte)
                input_vedio_dpi->setCurrentIndex(3);
            else if(3 == value_inte)
                input_vedio_dpi->setCurrentIndex(4);
            else if(6 == value_inte)
                input_vedio_dpi->setCurrentIndex(5);
            break;
        case 5:
            if((value_inte >= 0) && (value_inte <= 2))
            {
                input_fovmode->setCurrentIndex(value_inte);
                input_set_fov_display(value_inte);
            }
            break;
        case 6:
            input_max_fovclass->setText(QString::number(value_inte));
            break;
        case 7:
            if((value_inte >= 0) && (value_inte <= 2))
                input_boxsize->setCurrentIndex(value_inte);
            break;
        case 8:
            input_max_boxsize->setText(QString::number(value_inte));
            input_set_boxsize_display();
            break;
        case 9:
            input_mtd_sensi->setText(QString::number(value_inte));
            break;
        case 10:
            input_mtd_rigionx->setText(QString::number(value_inte));
            break;
        case 11:
            input_mtd_rigiony->setText(QString::number(value_inte));
            break;
        case 12:
            input_mtd_rigionw->setText(QString::number(value_inte));
            break;
        case 13:
            input_mtd_rigionh->setText(QString::number(value_inte));
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input2(int field, float value, int value_inte)
{
    switch(field)
    {
        case 0:
            input_cur_fovclass->setText(QString::number(value_inte));
            break;
        case 2:
            vedio_continue_Fov[0]->setText(QString::number(value));
            break;
        case 3:
            continue_verticall[0]->setText(QString::number(value));
            break;
        case 4:
            vedio_continue_Fov[1]->setText(QString::number(value));
           break;
        case 5:
            continue_verticall[1]->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov[2]->setText(QString::number(value));
            break;
        case 7:
            continue_verticall[2]->setText(QString::number(value));
           break;
        case 8:
            vedio_continue_Fov[3]->setText(QString::number(value));
            break;
        case 9:
            continue_verticall[3]->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov[4]->setText(QString::number(value));
           break;
        case 11:
            continue_verticall[4]->setText(QString::number(value));
            break;
        case 12:
            vedio_continue_Fov[5]->setText(QString::number(value));
            break;
        case 13:
            continue_verticall[5]->setText(QString::number(value));
           break;
        case 14:
            vedio_continue_Fov[6]->setText(QString::number(value));
            break;
        case 15:
            continue_verticall[6]->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input3(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_continue_Fov[7]->setText(QString::number(value));
            break;
        case 1:
            continue_verticall[7]->setText(QString::number(value));
            break;
        case 2:
            vedio_continue_Fov[8]->setText(QString::number(value));
            break;
        case 3:
            continue_verticall[8]->setText(QString::number(value));
            break;
        case 4:
            vedio_continue_Fov[9]->setText(QString::number(value));
           break;
        case 5:
            continue_verticall[9]->setText(QString::number(value));
            break;
        case 6:
            vedio_continue_Fov[10]->setText(QString::number(value));
            break;
        case 7:
            continue_verticall[10]->setText(QString::number(value));
           break;
        case 8:
            vedio_continue_Fov[11]->setText(QString::number(value));
            break;
        case 9:
            continue_verticall[11]->setText(QString::number(value));
            break;
        case 10:
            vedio_continue_Fov[12]->setText(QString::number(value));
           break;
        case 11:
            continue_verticall[12]->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input4(int field, float value)
{
    switch(field)
    {
        case 3:
            vedio_continue[0]->setText(QString::number(value));
            break;
        case 4:
            vedio_continue[1]->setText(QString::number(value));
            break;
        case 5:
            vedio_continue[2]->setText(QString::number(value));
            break;
        case 6:
            vedio_continue[3]->setText(QString::number(value));
            break;
        case 7:
            vedio_continue[4]->setText(QString::number(value));
            break;
        case 8:
            vedio_continue[5]->setText(QString::number(value));
            break;
        case 9:
            vedio_continue[6]->setText(QString::number(value));
            break;
        case 10:
            vedio_continue[7]->setText(QString::number(value));
            break;
        case 11:
            vedio_continue[8]->setText(QString::number(value));
            break;
        case 12:
            vedio_continue[9]->setText(QString::number(value));
            break;
        case 13:
            vedio_continue[10]->setText(QString::number(value));
            break;
        case 14:
            vedio_continue[11]->setText(QString::number(value));
            break;
        case 15:
            vedio_continue[12]->setText(QString::number(value));
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input5(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spbx_continue[0]->setValue(value);
            break;
        case 1:
            vedio_spby_continue[0]->setValue(value);
            break;
        case 2:
            vedio_spbx_continue[1]->setValue(value);
            break;
        case 3:
            vedio_spby_continue[1]->setValue(value);
            break;
        case 4:
            vedio_spbx_continue[2]->setValue(value);
           break;
        case 5:
            vedio_spby_continue[2]->setValue(value);
            break;
        case 6:
            vedio_spbx_continue[3]->setValue(value);
            break;
        case 7:
            vedio_spby_continue[3]->setValue(value);
           break;
        case 8:
            vedio_spbx_continue[4]->setValue(value);
            break;
        case 9:
            vedio_spby_continue[4]->setValue(value);
            break;
        case 10:
            vedio_spbx_continue[5]->setValue(value);
           break;
        case 11:
            vedio_spby_continue[5]->setValue(value);
            break;
        case 12:
            vedio_spbx_continue[6]->setValue(value);
           break;
        case 13:
            vedio_spby_continue[6]->setValue(value);
            break;
        case 14:
            vedio_spbx_continue[7]->setValue(value);
           break;
        case 15:
            vedio_spby_continue[7]->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input6(int field, float value)
{
    switch(field)
    {
        case 0:
            vedio_spbx_continue[8]->setValue(value);
            break;
        case 1:
            vedio_spby_continue[8]->setValue(value);
            break;
        case 2:
            vedio_spbx_continue[9]->setValue(value);
            break;
        case 3:
            vedio_spby_continue[9]->setValue(value);
            break;
        case 4:
            vedio_spbx_continue[10]->setValue(value);
           break;
        case 5:
            vedio_spby_continue[10]->setValue(value);
            break;
        case 6:
            vedio_spbx_continue[11]->setValue(value);
            break;
        case 7:
            vedio_spby_continue[11]->setValue(value);
           break;
        case 8:
            vedio_spbx_continue[12]->setValue(value);
            break;
        case 9:
            vedio_spby_continue[12]->setValue(value);
            break;
        default:
            break;
    }
}
void MainWindow::show_blk_input7(int field, float value, int value_inte)
{
    switch(field)
    {
        case 0:
            input_cur_boxsize->setText(QString::number(value_inte));
            break;
        case 2:
            common_boxw->setText(QString::number(value_inte));
            break;
        case 3:
            common_boxh->setText(QString::number(value_inte));
            break;
        case 4:
            input_boxw[0]->setText(QString::number(value_inte));
            break;
        case 5:
            input_boxh[0]->setText(QString::number(value_inte));
            break;
        case 6:
            input_boxw[1]->setText(QString::number(value_inte));
            break;
        case 7:
            input_boxh[1]->setText(QString::number(value_inte));
           break;
        case 8:
            input_boxw[2]->setText(QString::number(value_inte));
            break;
        case 9:
            input_boxh[2]->setText(QString::number(value_inte));
            break;
        default:
            break;
    }

}
