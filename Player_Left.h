#ifndef PLAYER_LEFT_H
#define PLAYER_LEFT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QList>
#include <QTimer>

class Player_Left : public QGraphicsPixmapItem
{
public:
    Player_Left();
    float PlayerSpeed;

signals:
};

#endif // PLAYER_LEFT_H
