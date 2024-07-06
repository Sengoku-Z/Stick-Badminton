#ifndef NEWGAME_H
#define NEWGAME_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

class NewGame : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit NewGame(QObject *parent = nullptr); // 构造函数声明，可以接受一个父对象作为参数

private:
    QGraphicsPixmapItem *player1; // 玩家1的图形像素项指针
    QGraphicsPixmapItem *player2; // 玩家2的图形像素项指针
    QGraphicsPixmapItem *ball; // 球的图形像素项指针
    QTimer *gameTimer; // 游戏定时器指针，用于控制游戏逻辑的定时执行
};

#endif // NEWGAME_H
