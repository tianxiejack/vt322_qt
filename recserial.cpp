#include "recserial.h"
#include "mainwindow.h"
#include <QDebug>

volatile bool thread_run = true;
extern  unsigned char output_array[5000];
extern  unsigned char output_array_6[1024];
extern  unsigned char output_array_7[1024];
extern  unsigned char output_array_8[1024];
volatile unsigned int output_cnt =0;

extern volatile unsigned char rcv_buf[5000];
extern volatile unsigned int BufWrite ;
extern volatile unsigned int BufRead ;
extern volatile unsigned char BufRcvStatus;
extern int data_length;
extern QSerialPort * serialPort_command;

unsigned char Get_One_Char(unsigned char* pRxByte)
{
    if((BufRcvStatus == BUFFER_FULL) ||(BufRcvStatus == BUFFER_DATA))
    {
        *pRxByte = rcv_buf[BufRead++];

        if (BufRead == sizeof(rcv_buf)){
            BufRead = 0;
        }
        if (BufWrite == BufRead) {
            BufRcvStatus = BUFFER_EMPTY;
        }
        else{
            BufRcvStatus = BUFFER_DATA;
        }
        return 1;
    }

    return 0;
}


recSerial::recSerial(QObject *parent) : QThread(parent)
{
    connect(serialPort_command, &QSerialPort::readyRead, this, &recSerial::serial_Read_Data);
}

unsigned char pRxByte =0;
unsigned char frame_flag =0;
unsigned char crc_sum =0;
int pkg_length = 0;
void recSerial::serial_Read_Data()
{
    while(serialPort_command->bytesAvailable()>0)
    {
        QByteArray datagram;
        int cnt = 0;
        datagram.resize(serialPort_command->bytesAvailable());
        int len = serialPort_command->read(datagram.data(),datagram.size());
        pthis->setrecvbytes(datagram);
        while(cnt<len)
        {
            pRxByte = datagram.at(cnt++);
            switch(frame_flag)//从串口读取一帧数据，并检查校验和。
            {
                case 0:
                    if(pRxByte == 0xEB) {
                        frame_flag = 1;
                    }
                    else
                    {
                        frame_flag = 0;
                        output_cnt = 0;
                        crc_sum = 0;
                    }
                    break;
                case 1:
                    if(pRxByte == 0x53){
                        frame_flag = 2;
                        output_cnt = 0;
                        //crc_sum ^= pRxByte;
                    }
                    else
                    {
                        frame_flag = 0;
                        output_cnt = 0;
                        crc_sum = 0;
                    }
                    break;
                case 2:
                    pkg_length = pRxByte;
                    //crc_sum ^= pRxByte;
                    frame_flag = 3;
                    break;
                case 3:
                    pkg_length = (pkg_length|(pRxByte<<8));
                    data_length=pkg_length;
                    frame_flag = 4;
                    //crc_sum ^= pRxByte;
                    break;
                case 4:
                    if(output_cnt>(sizeof(output_array)/sizeof(output_array[0])-1))
                    {
                        frame_flag = 0;
                        crc_sum = 0;
                        output_cnt = 0;
                        break;
                    }
                    output_array[output_cnt++] = pRxByte;
                    if(output_cnt >= pkg_length+1){
                        if(crc_sum == pRxByte ){
                            pthis->output_to_label(output_array[0]);
                            frame_flag = 0;
                            crc_sum = 0;
                            output_cnt = 0;
                            break;
                        }
                        else{
                            frame_flag = 0;
                            output_cnt = 0;
                            crc_sum = 0;
                            break;
                        }
                    }
                    crc_sum ^= pRxByte;
                    break;
                default:
                    frame_flag = 0;
                    crc_sum = 0;
                    output_cnt = 0;
                    break;
            }
        }
    }
}

void recSerial::exportfile(unsigned char *uoutput_array)
{
    unsigned int filelen =0;
    unsigned int currentlen =0;
    unsigned int writelen = 0;
    static unsigned int writetotal = 0;
    static int openflag = 0;
    filelen =(uoutput_array[1]|(uoutput_array[2]<<8)|(uoutput_array[3]<<16)|(uoutput_array[4]<<24));
    currentlen =(uoutput_array[6]|(uoutput_array[7]<<8));
    if(openflag == 0)
    {
        bool isok = expfile.open(QFile::WriteOnly);
        if(false == isok)
        {
            upgrade_show->append("打开导出文件失败");
            return;
        }
        else
        {
            openflag = 1;
        }
    }
    writelen = expfile.write((char*)(uoutput_array+8),currentlen);
    writetotal += writelen;
    if(uoutput_array[5]==2)
    {
        if(writetotal == filelen)
        {
            upgrade_show->append("导出成功");
        }
        else
        {
            upgrade_show->append("导出失败");
        }
        expfile.close();
        writetotal = 0;
        openflag = 0;
    }
}

void recSerial::importfileresp(unsigned char *uoutput_array)
{
    if(uoutput_array[1] == 0x00)
    {
        emit socket2main_signal(0,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x01)
    {
        emit socket2main_signal(1,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x02)
    {
        emit socket2main_signal(2,uoutput_array[2]);
    }
}

void recSerial::upgraderesp(unsigned char *uoutput_array)
{
    if(uoutput_array[1] == 0x00)
    {
        emit socket2main_signal(0,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x01)
    {
        emit socket2main_signal(1,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x02)
    {
        emit socket2main_signal(2,uoutput_array[2]);
    }
}

void recSerial::run()  //线程运行函数，调用前需要在主线程中声明并定义一个该线程的类的对象，
{                          // 然后通过该对象的 start() 方法来调用这个线程运行函数；
    /*
    unsigned char pRxByte =0;
    unsigned char frame_flag =0;
    unsigned char crc_sum =0;
    int pkg_length = 0;

    while(true == thread_run)
    {
        if(thread_run == false) {
            break;
        }
        if( 1 == Get_One_Char((unsigned char*)&pRxByte)  )//从串口读一个字节存到pRxByte
        {
            switch(frame_flag)//从串口读取一帧数据，并检查校验和。
            {
                case 0:
                    if(pRxByte == 0xEB) {
                        frame_flag = 1;
                    }
                    else
                    {
                        frame_flag = 0;
                        output_cnt = 0;
                        crc_sum = 0;
                    }
                    break;
                case 1:
                    if(pRxByte == 0x53){
                        frame_flag = 2;
                        output_cnt = 0;
                        crc_sum ^= pRxByte;
                    }
                    else
                    {
                        frame_flag = 0;
                        output_cnt = 0;
                        crc_sum = 0;
                    }
                    break;
                case 2:
                    pkg_length = pRxByte;
                    crc_sum ^= pRxByte;
                    frame_flag = 3;
                    break;
                case 3:
                    pkg_length = (pkg_length|(pRxByte<<8));
                    frame_flag = 4;
                    crc_sum ^= pRxByte;
                    break;
                case 4:
                    if(output_cnt>(sizeof(output_array)/sizeof(output_array[0])-1))
                    {
                        frame_flag = 0;
                        crc_sum = 0;
                        output_cnt = 0;
                        break;
                    }
                    output_array[output_cnt++] = pRxByte;
                    if(output_cnt >= pkg_length+1){
                        if(crc_sum == pRxByte ){
                            if(0x06 == output_array[0])
                            {
                                memcpy(output_array_6, output_array, sizeof(output_array));
                                pthis->output_to_label(output_array_6[0]);
                            }
                            else if(0x07 == output_array[0])
                            {
                                memcpy(output_array_7, output_array, sizeof(output_array));
                                pthis->output_to_label(output_array_7[0]);
                            }
                            else if(0x08 == output_array[0])
                            {
                                memcpy(output_array_8, output_array, sizeof(output_array));
                                pthis->output_to_label(output_array_8[0]);
                            }
                            else
                            {
                                pthis->output_to_label(output_array[0]);
                            }
                            frame_flag = 0;
                            crc_sum = 0;
                            output_cnt = 0;
                            break;
                        }
                        else{
                            frame_flag = 0;
                            output_cnt = 0;
                            crc_sum = 0;
                            break;
                        }
                    }
                    crc_sum ^= pRxByte;
                    break;
                default:
                    frame_flag = 0;
                    crc_sum = 0;
                    output_cnt = 0;
                    break;
            }
        }
    }
    */
}
