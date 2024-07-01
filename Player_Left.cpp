#include "Player_Left.h"
#include <QPixmap>

Player_Left::Player_Left()
{
    PlayerSpeed = 5;

    QPixmap Player_Left(":/imgs/images/standright.png");
    this->setPixmap(Player_Left);
    this->setPos(690, 678 - Player_Left.height() - 42);
}
