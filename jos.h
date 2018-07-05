#ifndef JOS_H
#define JOS_H

#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QMutex>

#define POS_MIN 0
#define POS_MAX 65535
#define POS_CENTER 32767
#define POINTX 100 //圆左上角坐标x
#define POINTY 30 //圆左上角坐标Y
#define CENTER 160//圆的半径
#define RATIO 10 //矩形框缩小比例

#define BUFFER_FULL          1
#define BUFFER_DATA          2
#define BUFFER_EMPTY         3

namespace Ui {
class Jos;
}

class Jos : public QWidget
{
    Q_OBJECT

public:
    explicit Jos(QWidget *parent = 0);
    ~Jos();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::Jos *ui;
    int a, b, m_dragging;
};

#endif // JOS_H
