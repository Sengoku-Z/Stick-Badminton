#include "Player_Left.h"
#include <QPixmap>
#include <QTimer>

Player_Left::Player_Left()
{
    PlayerSpeed = 3;
    QPixmap Player_Left(":/imgs/images/standright.png");
    this->setPixmap(Player_Left);
    this->setPos(237, 678 - Player_Left.height() - 42);
}
