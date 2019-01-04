#include  "mainwindow.h"

volatile bool thread_run_usocket = true;
extern volatile unsigned int usocket_BufWrite ;
extern volatile unsigned int usocket_BufRead ;
extern volatile unsigned char usocket_BufRcvStatus;
extern volatile unsigned char usocket_rcv_buf[5000];
volatile unsigned char usocket_rcv_buf2[5000];
volatile unsigned int usocket_output_cnt =0;
extern  unsigned char uoutput_array[5000];
extern QMutex usocket_mutex;
extern QTcpSocket *usocket;
extern QByteArray usocket_copy_bytearray;


RcvUSocketdata::RcvUSocketdata(QObject *parent) : QThread(parent)
{
    connect(usocket, &QTcpSocket::readyRead, this, &RcvUSocketdata::usocket_Read_Data);
}

unsigned char usocket_Get_One_Char(unsigned char* pRxByte)
{
    usocket_mutex.lock();
    if((usocket_BufRcvStatus == BUFFER_FULL) ||(usocket_BufRcvStatus == BUFFER_DATA))
    {
        *pRxByte = usocket_rcv_buf[usocket_BufRead++];

        if (usocket_BufRead == sizeof(usocket_rcv_buf)){
            usocket_BufRead = 0;
        }
        if (usocket_BufWrite == usocket_BufRead) {
            usocket_BufRcvStatus = BUFFER_EMPTY;
        }
        else{
            usocket_BufRcvStatus = BUFFER_DATA;

        }
        usocket_mutex.unlock();
        return 1;
    }
    usocket_mutex.unlock();
    return 0;
}
void RcvUSocketdata::run()  //线程运行函数，调用前需要在主线程中声明并定义一个该线程的类的对象，然后通过该对象的 start() 方法来调用这个线程运行函数；
{
    /*
    unsigned char pRxByte =0;
    unsigned char frame_flag =0;
    unsigned char crc_sum =0;
    int pkg_length = 0;

    while(true == thread_run_usocket)
    {
        if(thread_run_usocket == false) {
            break;
        }

        if( 1 == usocket_Get_One_Char((unsigned char*)&pRxByte)  )//从网口读一个字节存到pRxByte
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
                        usocket_output_cnt = 0;
                        crc_sum = 0;
                    }

                    break;
                case 1:
                    if(pRxByte == 0x53){
                        frame_flag = 2;
                        usocket_output_cnt = 0;
                        crc_sum ^= pRxByte;
                    }
                    else
                    {
                        frame_flag = 0;
                        usocket_output_cnt = 0;
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
                    crc_sum ^= pRxByte;
                    frame_flag = 4;
                    break;
                case 4:
                    if(usocket_output_cnt>(sizeof(uoutput_array)/sizeof(uoutput_array[0])-1))
                    {
                        frame_flag = 0;
                        crc_sum = 0;
                        usocket_output_cnt = 0;
                        break;
                    }
                    uoutput_array[usocket_output_cnt++] = pRxByte;
                    if(usocket_output_cnt >= pkg_length+1){
                        if(crc_sum == pRxByte )
                        {
                            if(uoutput_array[0]==0x33)
                            {
                                exportfile(uoutput_array);
                            }
                            else if(uoutput_array[0]==0x32)
                                importfileresp(uoutput_array);
                            else if(uoutput_array[0]==0x35)
                            {
                                //qDebug("it is upgradefw response");
                                upgraderesp(uoutput_array);
                            }
                            else if(uoutput_array[0]==0x37)
                            {
                                //qDebug("it is upgradefpga response");
                                upgradefpgaresp(uoutput_array);
                            }
                            frame_flag = 0;
                            crc_sum = 0;
                            usocket_output_cnt = 0;
                            break;
                        }
                        else{
                            frame_flag = 0;
                            usocket_output_cnt = 0;
                            crc_sum = 0;
                            break;
                        }
                    }
                    crc_sum ^= pRxByte;
                    break;
                default:
                    frame_flag = 0;
                    crc_sum = 0;
                    usocket_output_cnt = 0;
                    break;
            }
        }
    }
    */
}
void RcvUSocketdata::exportfile(unsigned char *uoutput_array)
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
void RcvUSocketdata::importfileresp(unsigned char *uoutput_array)
{
    if(uoutput_array[1] == 0x01)
        upgrade_show->append("导入成功");
    else if(uoutput_array[1] == 0x02)
        upgrade_show->append("导入失败");
}
void RcvUSocketdata::upgraderesp(unsigned char *uoutput_array)
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
void RcvUSocketdata::upgradefpgaresp(unsigned char *uoutput_array)
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


unsigned char pRxByte =0;
unsigned char frame_flag =0;
unsigned char crc_sum =0;
int pkg_length = 0;

void RcvUSocketdata::usocket_Read_Data()
{
    while(usocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        int cnt = 0;
        datagram.resize(usocket->bytesAvailable());
        int len = usocket->read(datagram.data(),datagram.size());
        while(cnt<len)
        {
            pRxByte = datagram.at(cnt++);
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
                            usocket_output_cnt = 0;
                            crc_sum = 0;
                        }

                        break;
                    case 1:
                        if(pRxByte == 0x53){
                            frame_flag = 2;
                            usocket_output_cnt = 0;
                            crc_sum ^= pRxByte;
                        }
                        else
                        {
                            frame_flag = 0;
                            usocket_output_cnt = 0;
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
                        crc_sum ^= pRxByte;
                        frame_flag = 4;
                        break;
                    case 4:
                        if(usocket_output_cnt>(sizeof(uoutput_array)/sizeof(uoutput_array[0])-1))
                        {
                            frame_flag = 0;
                            crc_sum = 0;
                            usocket_output_cnt = 0;
                            break;
                        }
                        uoutput_array[usocket_output_cnt++] = pRxByte;
                        if(usocket_output_cnt >= pkg_length+1){
                            if(crc_sum == pRxByte )
                            {
                                if(uoutput_array[0]==0x33)
                                {
                                    exportfile(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x32)
                                    importfileresp(uoutput_array);
                                else if(uoutput_array[0]==0x35)
                                {
                                    //qDebug("it is upgradefw response");
                                    upgraderesp(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x37)
                                {
                                    //qDebug("it is upgradefpga response");
                                    upgradefpgaresp(uoutput_array);
                                }
                                frame_flag = 0;
                                crc_sum = 0;
                                usocket_output_cnt = 0;
                                break;
                            }
                            else{
                                frame_flag = 0;
                                usocket_output_cnt = 0;
                                crc_sum = 0;
                                break;
                            }
                        }
                        crc_sum ^= pRxByte;
                        break;
                    default:
                        frame_flag = 0;
                        crc_sum = 0;
                        usocket_output_cnt = 0;
                        break;
                }
            }
        }
    }
}
