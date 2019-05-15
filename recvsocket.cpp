#include  "mainwindow.h"

extern volatile unsigned char socket_rcv_buf[5000];
extern volatile unsigned int rcv_cnt;
extern volatile unsigned int socket_BufWrite ;
extern volatile unsigned int socket_BufRead ;
extern volatile unsigned char socket_BufRcvStatus;
volatile unsigned int socket_output_cnt =0;
extern  unsigned char output_array[1024];
extern  unsigned char output_array_6[1024];
extern  unsigned char output_array_7[1024];
extern  unsigned char output_array_8[1024];
volatile bool thread_run_socket = true;
extern int data_length;
extern QTcpSocket *socket;


RcvSocketdata::RcvSocketdata(QObject *parent) : QThread(parent)
{
    connect(socket, &QTcpSocket::readyRead, this, &RcvSocketdata::socket_Read_Data);
}

unsigned char socket_Get_One_Char(unsigned char* pRxByte)
{
    if((socket_BufRcvStatus == BUFFER_FULL) ||(socket_BufRcvStatus == BUFFER_DATA))
    {
        *pRxByte = socket_rcv_buf[socket_BufRead++];

        if (socket_BufRead == sizeof(socket_rcv_buf)){
            socket_BufRead = 0;
        }
        if (socket_BufWrite == socket_BufRead) {
            socket_BufRcvStatus = BUFFER_EMPTY;
        }
        else{
            socket_BufRcvStatus = BUFFER_DATA;
        }
        return 1;
    }

    return 0;
}



void RcvSocketdata::run()  //线程运行函数，调用前需要在主线程中声明并定义一个该线程的类的对象，
{                          // 然后通过该对象的 start() 方法来调用这个线程运行函数；
/*
    unsigned char pRxByte =0;
    unsigned char frame_flag =0;
    unsigned char crc_sum =0;
    int pkg_length = 0;

    while(true == thread_run_socket)
    {
        if(thread_run_socket == false) {
            break;
        }

        if( 1 == socket_Get_One_Char((unsigned char*)&pRxByte)  )//从网口读一个字节存到pRxByte
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
                        socket_output_cnt = 0;
                        crc_sum = 0;
                    }

                    break;
                case 1:
                    if(pRxByte == 0x53){
                        frame_flag = 2;
                        socket_output_cnt = 0;
                        crc_sum ^= pRxByte;
                    }
                    else
                    {
                        frame_flag = 0;
                        socket_output_cnt = 0;
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
                    data_length=pkg_length;
                    crc_sum ^= pRxByte;
                    frame_flag = 4;
                    break;
                case 4:
                    if(socket_output_cnt>(sizeof(output_array)/sizeof(output_array[0])-1))
                    {
                        frame_flag = 0;
                        crc_sum = 0;
                        socket_output_cnt = 0;
                        break;
                    }
                    output_array[socket_output_cnt++] = pRxByte;
                    if(socket_output_cnt >= pkg_length+1){
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
                            socket_output_cnt = 0;
                            break;
                        }
                        else{
                            frame_flag = 0;
                            socket_output_cnt = 0;
                            crc_sum = 0;
                            break;
                        }
                    }
                    crc_sum ^= pRxByte;
                    break;
                default:
                    frame_flag = 0;
                    crc_sum = 0;
                    socket_output_cnt = 0;
                    break;
            }
        }
    }
    */
}



unsigned char socket_pRxByte =0;
unsigned char socket_frame_flag =0;
unsigned char socket_crc_sum =0;
int socket_pkg_length = 0;

void RcvSocketdata::socket_Read_Data()
{
    while(socket->bytesAvailable()>0)
    {
        QByteArray datagram;
        int cnt = 0;
        datagram.resize(socket->bytesAvailable());
        int len = socket->read(datagram.data(),datagram.size());
        pthis->setrecvbytes(datagram);
        while(cnt<len)
        {
            socket_pRxByte = datagram.at(cnt++);
            {
                switch(socket_frame_flag)//从网口读取一帧数据，并检查校验和。
                {
                    case 0:
                        if(socket_pRxByte == 0xEB) {
                            socket_frame_flag = 1;
                        }
                        else
                        {
                            socket_frame_flag = 0;
                            socket_output_cnt = 0;
                            socket_crc_sum = 0;
                        }

                        break;
                    case 1:
                        if(socket_pRxByte == 0x53){
                            socket_frame_flag = 2;
                            socket_output_cnt = 0;
                            //socket_crc_sum ^= socket_pRxByte;
                        }
                        else
                        {
                            socket_frame_flag = 0;
                            socket_output_cnt = 0;
                            socket_crc_sum = 0;
                        }
                        break;
                    case 2:
                        socket_pkg_length = socket_pRxByte;
                        //socket_crc_sum ^= socket_pRxByte;
                        socket_frame_flag = 3;
                        break;
                    case 3:
                        socket_pkg_length = (socket_pkg_length|(socket_pRxByte<<8));
                        data_length=socket_pkg_length;
                        //socket_crc_sum ^= socket_pRxByte;
                        socket_frame_flag = 4;
                        break;
                    case 4:
                        if(socket_output_cnt>(sizeof(output_array)/sizeof(output_array[0])-1))
                        {
                            socket_frame_flag = 0;
                            socket_crc_sum = 0;
                            socket_output_cnt = 0;
                            break;
                        }
                        output_array[socket_output_cnt++] = socket_pRxByte;
                        if(socket_output_cnt >= socket_pkg_length+1){
                            if(socket_crc_sum == socket_pRxByte ){
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
                                socket_frame_flag = 0;
                                socket_crc_sum = 0;
                                socket_output_cnt = 0;
                                break;
                            }
                            else{
                                socket_frame_flag = 0;
                                socket_output_cnt = 0;
                                socket_crc_sum = 0;
                                break;
                            }
                        }
                        socket_crc_sum ^= socket_pRxByte;
                        break;
                    default:
                        socket_frame_flag = 0;
                        socket_crc_sum = 0;
                        socket_output_cnt = 0;
                        break;
                }
            }
        }
    }
}
