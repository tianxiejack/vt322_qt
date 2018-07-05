#include "jos.h"
#include "ui_jos.h"
#include <QDebug>

int mousePress = 0;
QMutex send_mutex;
unsigned char send_arr[64];
unsigned short sectrk_x = 0;
unsigned short sectrk_y = 0;
Jos::Jos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Jos)
{
    ui->setupUi(this);

    this->setWindowTitle("手柄控制");
    //this->setGeometry(1260,1080,600,600);
}

Jos::~Jos()
{
    delete ui;
}

void Jos::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter paint(this);
    //paint.drawRect(POINTX-WIDTH/2, POINTY-HEIGHT/2, WIDTH, HEIGHT);
    // 反走样
    paint.setRenderHint(QPainter::Antialiasing, true);
    // 设置画笔颜色、宽度
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    // 设置画刷颜色
    paint.setBrush(QColor(200, 255, 250));
    paint.drawEllipse(POINTX,POINTY,CENTER,CENTER);
   // paint.drawRect(POINTX-WIDTH/RATIO/2, POINTY-HEIGHT/RATIO/2, WIDTH/RATIO, HEIGHT/RATIO);
    paint.setPen(QPen(QColor(0, 0, 0), 1));
    //paint.drawLine(QPointF(a-5, b), QPointF(a+5, b));
    //paint.drawLine(QPointF(a, b-5), QPointF(a, b+5));
    paint.drawEllipse(a-5,b-5,10,10);
    paint.drawPoint(a,b);

}

void Jos::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x();
    int y=event->pos().y();
    mousePress = 1;
   if((abs(event->pos().x()-a)<=10)&&((event->pos().y()-b)<=10)){
       m_dragging = 1;
      qDebug()<<"x"<<x<<endl<<"y"<<y<<endl;
   }
   else
       m_dragging = 0;
}

void Jos::mouseReleaseEvent(QMouseEvent *e)
{
    if(mousePress==1){
        mousePress = 0;
        a=POINTX+CENTER/2;
        b=POINTY+CENTER/2;
        update();
    }

}

void Jos::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePress&&m_dragging)
    {
        int x=event->pos().x();
        int y=event->pos().y();
        if(x>POINTX && x<(POINTX+CENTER) && y>POINTY && y<(POINTY+CENTER) && ((x-POINTX-CENTER/2)*(x-POINTX-CENTER/2)+(y-POINTY-CENTER/2)*(y-POINTY-CENTER/2))<CENTER*CENTER/4)
        {
            sectrk_x = (event->pos().x()-POINTX)*RATIO+CENTER/2;
            sectrk_y = (event->pos().y()-POINTY)*RATIO+CENTER/2;
             //ui->label_xy->setText(tr("(")+QString::number(sectrk_x)+","+QString::number(sectrk_y)+")");
            a=event->pos().x();
            b=event->pos().y();
            if(0)
            {
                send_mutex.lock();
                send_arr[3] = 0x0b;
                send_arr[4] = 0x01;
                send_arr[5] = sectrk_x&0xff;
                send_arr[6] = (sectrk_x>>8)&0xff;
                send_arr[7] = sectrk_y&0xff;
                send_arr[8] = (sectrk_y>>8)&0xff;
                //send_oneframe(10);
                send_mutex.unlock();
            }
            update();
            //repaint();
        }
    }
}
