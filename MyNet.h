#ifndef MYNET_H
#define MYNET_H

#include <QGraphicsPixmapItem> // 包含Qt图形项类的头文件
#include <QRect> // 包含Qt矩形类的头文件，用于定义矩形区域

class MyNet : public QGraphicsPixmapItem // 定义一个MyNet的类
{
public:
    MyNet(); // 构造函数

    QRect netRect; // 用于碰撞检测的矩形区域，存储对象的位置和大小信息
};

#endif // MYNET_H
