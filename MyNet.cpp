#include "MyNet.h"
#include <QPixmap>

MyNet::MyNet()
{
    // 加载网格图像
    QPixmap pixmap(":/imgs/images/net.png");

    // 缩小图片到 30%
    QPixmap scaledPixmap = pixmap.scaled(pixmap.width() * 0.30, pixmap.height() * 0.30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 设置缩小后的图片
    this->setPixmap(scaledPixmap);

    // 设置网格的位置，使其居中并在底部
    int sceneWidth = 1024;
    int sceneHeight = 678;
    // 40 200
    int netX = (sceneWidth - scaledPixmap.width()) / 2;
    int netY = sceneHeight - scaledPixmap.height();
    this->setPos(netX, netY);

    // 设置碰撞检测矩形的大小和位置
    netRect.setRect(netX, netY, scaledPixmap.width(), scaledPixmap.height());
}
