#include "Player_Right.h"
#include <QPixmap>

Player_Right::Player_Right()
{
    PlayerSpeed = 3;

    // 加载图像
    QPixmap Player_Right(":/imgs/images/standleft.png");
    this->setPixmap(Player_Right); // 把这张图片加到窗口中
    this->setPos(690, 678 - Player_Right.height() - 42); // 右侧人物的初始位置
}
