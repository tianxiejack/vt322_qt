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
    send_arr[2] = length;
    send_arr[3] = 0x00;
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
    //qDebug()<<sndData_02;
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
    ui->label->setText(str1);
}

