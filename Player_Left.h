#ifndef PLAYER_LEFT_H
#define PLAYER_LEFT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Player_Left : public QGraphicsPixmapItem
{
public:
    Player_Left();
    float PlayerSpeed;

signals:
};

#endif // PLAYER_LEFT_H
