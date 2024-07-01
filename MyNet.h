#ifndef MYNET_H
#define MYNET_H

#include <QGraphicsPixmapItem>
#include <QRect>

class MyNet : public QGraphicsPixmapItem
{
public:
    MyNet();
    QRect netRect; // 用于碰撞检测的矩形
};

#endif // MYNET_H
