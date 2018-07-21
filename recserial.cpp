#include "recserial.h"
#include "mainwindow.h"
#include <QDebug>

volatile bool thread_run = true;
extern  unsigned char output_array[64];
extern  unsigned char output_array_6[64];
extern  unsigned char output_array_7[64];
extern  unsigned char output_array_8[64];
volatile unsigned int output_cnt =0;

extern volatile unsigned char rcv_buf[5000];
extern volatile unsigned int BufWrite ;
extern volatile unsigned int BufRead ;
extern volatile unsigned char BufRcvStatus;

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


}

void recSerial::run()  //线程运行函数，调用前需要在主线程中声明并定义一个该线程的类的对象，
{                          // 然后通过该对象的 start() 方法来调用这个线程运行函数；
    unsigned char pRxByte =0;
    unsigned char frame_flag =0;
    unsigned char crc_sum =0;
    int pkg_length = 0;

    while(true == thread_run)
    {
        if(thread_run == false) {
            break;
        }
        if( 1 == Get_One_Char((unsigned char*)&pRxByte)  )//从网口读一个字节存到pRxByte
        {
            switch(frame_flag)//从网口读取一帧数据，并检查校验和。
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
<<<<<<< HEAD
=======
                        crc_sum ^= pRxByte;
>>>>>>> dd380fdf507711ec1ec2eca5972d636e6ee83304
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
<<<<<<< HEAD
                    frame_flag = 3;
                    break;
                case 3:
                    output_array[output_cnt++] = pRxByte;
                    if(output_cnt >= pkg_length-3){
=======
                    crc_sum ^= pRxByte;
                    frame_flag = 3;
                    break;
                case 3:
                    pkg_length = (pkg_length|(pRxByte<<8));
                    frame_flag = 4;
                    crc_sum ^= pRxByte;
                    break;
                case 4:
                    output_array[output_cnt++] = pRxByte;
                    if(output_cnt >= pkg_length+1){
>>>>>>> dd380fdf507711ec1ec2eca5972d636e6ee83304
                        if(crc_sum == pRxByte ){
                            if(0x06 == output_array[0])
                            {
                                memcpy(output_array_6, output_array, sizeof(output_array));
                                emit send2main_signal(output_array_6[0]);
                            }
                            else if(0x07 == output_array[0])
                            {
                                memcpy(output_array_7, output_array, sizeof(output_array));
                                emit send2main_signal(output_array_7[0]);
                            }
                            else if(0x08 == output_array[0])
                            {
                                memcpy(output_array_8, output_array, sizeof(output_array));
                                emit send2main_signal(output_array_8[0]);
                            }
                            else
                            {
                                emit send2main_signal(output_array[0]);
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
}
