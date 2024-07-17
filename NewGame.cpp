#include "NewGame.h"
#include <QDebug>

NewGame::NewGame(QObject *parent)
    : QGraphicsScene(parent)
{
    qDebug() << "NewGame Constructor Called"; // 添加调试信息

    // 设置场景大小
    this->setSceneRect(0, 0, 730, 500);

    // 初始化玩家和球的属性
    player1 = new QGraphicsPixmapItem(QPixmap("://images/images2/player1_left.png").scaled(50, 50));
    player2 = new QGraphicsPixmapItem(QPixmap("://images/images2/player1_right.png").scaled(50, 50));
    ball = new QGraphicsPixmapItem(QPixmap("://images/images2/ball1.png").scaled(30, 30));

    // 设置初始位置
    player1->setPos(100, 350);
    player2->setPos(500, 350);
    ball->setPos(330, 50);

    // 添加玩家和球到场景中
    this->addItem(player1);
    this->addItem(player2);
    this->addItem(ball);

    // 初始化游戏计时器
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, [this]()
    {
                ball->moveBy(1, 0);
    });

    gameTimer->start(30);
}
