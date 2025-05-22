#include "Widget.h"
#include "ui_Widget.h"
#include <QMediaPlayer>
#include <QToolButton>
#include <QGraphicsPixmapItem>
#include <QFont>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <Menu.h>
#include <QVBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <Ball.h>
#include <QGraphicsProxyWidget>
#include <Instruction.h>
#include <ui_Instruction.h>

// 一系列初始化
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , currentFrame_Left_Right(0)
    , currentFrame_Left_Left(0)
    , currentFrame_Right_Right(0)
    , currentFrame_Right_Left(0)
    , currentFrame_Right_Start_Hit(0)
    , currentFrame_Right_Hit(0)
    , currentFrame_Left_Start_Hit(0)
    , currentFrame_Left_Hit(0)
    , JumpHeight(150)
    , JumpSpeed(8)
    , L_currentJumpHeight(0)
    , R_currentJumpHeight(0)
    , L_isJumping(false)
    , R_isJumping(false)

{
    ui->setupUi(this);
    ball = new Ball(this);

    // 初始化球网的碰撞矩形
    netRect = QRect(512, 478, 1, 200);

    this->setWindowIcon(QPixmap(":/imgs/images/ball.png"));
    this->setWindowTitle("Badminton_Stick");

    // 初始化计分板
    leftScoreLabel = new QLabel();
    leftScoreLabel->setText("左侧玩家得分: 0");
    leftScoreLabel->setStyleSheet("color: white; font-size: 20px;");

    rightScoreLabel = new QLabel();
    rightScoreLabel->setText("右侧玩家得分: 0");
    rightScoreLabel->setStyleSheet("color: white; font-size: 20px;");

    // 使用 QGraphicsProxyWidget 将 QLabel 嵌入 QGraphicsScene
    QGraphicsProxyWidget *leftScoreProxy = PlayScene.addWidget(leftScoreLabel);
    leftScoreProxy->setPos(10, 10);

    QGraphicsProxyWidget *rightScoreProxy = PlayScene.addWidget(rightScoreLabel);
    rightScoreProxy->setPos(800, 10);

    // 初始化人物不同的行走方式的帧数
    Run_Num_L_L = 4;
    Run_Num_L_R = 3;
    Run_Num_R_R = 5;
    Run_Num_R_L = 6;
    Right_Start_Hit_Frame = 5;
    Right_Hit_Frame = 4;
    Left_Start_Hit_Frame = 5;
    Left_Hit_Frame = 4;

    for(int i = 0; i < Right_Start_Hit_Frame; ++ i)
    {
        QString filename = QString("://images/hitleft/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if(!frame.isNull())
        {
            Right_Start_Hit.append(frame);
        }
    }
    for(int i = 0; i < Right_Hit_Frame; ++ i)
    {
        QString filename = QString("://images/beatleft/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if(!frame.isNull())
        {
            Right_Hit.append(frame);
        }
    }
    for(int i = 0; i < Left_Start_Hit_Frame; ++ i)
    {
        QString filename = QString("://images/hitright/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if(!frame.isNull())
        {
            Left_Start_Hit.append(frame);
        }
    }
    for(int i = 0; i < Left_Hit_Frame; ++ i)
    {
        QString filename = QString("://images/beatright/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if(!frame.isNull())
        {
            Left_Hit.append(frame);
        }
    }

    for (int i = 0; i < Run_Num_L_L; ++i)
    {
        QString filename = QString(":/images/images/player1runleft/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if (!frame.isNull())
        {
            Run_Left_Left.append(frame);
        }
    }

    for (int i = 0; i < Run_Num_L_R; ++i)
    {
        QString filename = QString("://images/player1runright/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if (!frame.isNull())
        {
            Run_Left_Right.append(frame);
        }
    }

    for (int i = 0; i < Run_Num_R_R; ++i)
    {
        QString filename = QString("://images/player2runright/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if (!frame.isNull())
        {
            Run_Right_Right.append(frame);
        }
    }

    for (int i = 0; i < Run_Num_R_L; ++i)
    {
        QString filename = QString("://images/player2runleft/%1.png").arg(i, 3, 10, QChar('0'));
        QPixmap frame(filename);
        if (!frame.isNull())
        {
            Run_Right_Left.append(frame);
        }
    }

    this->setFixedSize(1024, 678);
    GameView.setFixedSize(1024, 678);

    GameView.setSceneRect(QRect(0, 0, 1024, 678));
    PlayScene.setSceneRect(QRect(0, 0, 1024, 678));
    StartScene.setSceneRect(QRect(0, 0, 1024, 678));
    FirstScene.setSceneRect(QRect(0, 0, 1024, 678));
    EndScene_Lose.setSceneRect(QRect(0, 0, 1024, 678));
    EndScene_Win.setSceneRect(QRect(0, 0, 1024, 678));

    QGraphicsPixmapItem *chooseBackground = new QGraphicsPixmapItem();
    chooseBackground->setPixmap(QPixmap(":/imgs/images/FirstScene.png"));
    FirstScene.addItem(chooseBackground);

    QGraphicsPixmapItem *startBackground = new QGraphicsPixmapItem();
    startBackground->setPixmap(QPixmap(":/imgs/images/StartScene.png"));
    StartScene.addItem(startBackground);

    QGraphicsPixmapItem *playBackground = new QGraphicsPixmapItem();
    playBackground->setPixmap(QPixmap(":/imgs/images/Play_Item.png").scaled(1024, 678, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    PlayScene.addItem(playBackground);
    // 1 300 400 100 150
    // 2 400 100 100 150

    QGraphicsPixmapItem *Win_Item1 = new QGraphicsPixmapItem();
    QPixmap winItem1Pixmap(":/imgs/images/win1.png");
    Win_Item1->setPixmap(winItem1Pixmap.scaled(300, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    EndScene_Win.addItem(Win_Item1);
    Win_Item1->setPos(100, 250);

    QGraphicsPixmapItem *Win_Item2 = new QGraphicsPixmapItem();
    QPixmap winItem2Pixmap(":/imgs/images/win2.png");
    Win_Item2->setPixmap(winItem2Pixmap.scaled(400, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    EndScene_Win.addItem(Win_Item2);
    Win_Item2->setPos(100, 150);

    QGraphicsPixmapItem *Lose_Item = new QGraphicsPixmapItem();
    QPixmap loseItemPixmap(":/imgs/images/lose.png");
    Lose_Item->setPixmap(loseItemPixmap.scaled(300, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    EndScene_Lose.addItem(Lose_Item);
    Lose_Item->setPos(100, 250);

    QGraphicsPixmapItem *Win_Black = new QGraphicsPixmapItem();
    Win_Black->setPixmap(QPixmap(":/imgs/images/black.png").scaled(1024, 678, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    Win_Black->setZValue(-1); // 确保背景在最底层
    EndScene_Win.addItem(Win_Black);

    QGraphicsPixmapItem *Lose_Black = new QGraphicsPixmapItem();
    Lose_Black->setPixmap(QPixmap(":/imgs/images/black.png").scaled(1024, 678, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    Lose_Black->setZValue(-1); // 确保背景在最底层
    EndScene_Lose.addItem(Lose_Black);

    GameView.setScene(&FirstScene);
    GameView.setParent(this);
    GameView.show();
    GameView.fitInView(GameView.sceneRect(), Qt::IgnoreAspectRatio);

    PlayScene.addItem(&mynet);
    PlayScene.addItem(&player_left);
    PlayScene.addItem(&player_right);

    ball = new Ball(this);
    PlayScene.addItem(ball);

    auto chooseBtn_1 = new QToolButton();
    chooseBtn_1->resize(400, 250);
    chooseBtn_1->setIconSize(QSize(400, 250));
    chooseBtn_1->move(1024 - 400, 678 - 250);
    chooseBtn_1->setText("Badminton");
    chooseBtn_1->setFont(QFont("楷体", 40, 20, 5));
    connect(chooseBtn_1, &QToolButton::clicked, [this]()
            {
                GameView.setScene(&StartScene);
                GameView.show();
            });

    auto Play_Menu_Btn = new QToolButton();
    Menu * w = new Menu();
    Play_Menu_Btn->resize(80, 80);
    Play_Menu_Btn->setIcon(QIcon(":/imgs/images/help.png"));
    Play_Menu_Btn->setStyleSheet("background-color: transparent; border: none;");
    Play_Menu_Btn->setIconSize(QSize(80, 80));
    Play_Menu_Btn->move(0, 0);
    connect(Play_Menu_Btn, &QToolButton::clicked, [=]()
            {
                w->show();
            });

    auto Exit_Btn = new QToolButton();
    Exit_Btn->resize(80, 80);
    Exit_Btn->setIcon(QIcon(":/imgs/images/exit.png"));
    Exit_Btn->setStyleSheet("background-color: transparent; border: none;");
    Exit_Btn->move(0, 80);
    connect(Exit_Btn, &QToolButton::clicked, [this]()
            {
                GameView.setScene(&FirstScene);
                GameView.show();
            });

    auto startBtn = new QToolButton();
    startBtn->setAutoRaise(true);
    startBtn->resize(150, 150);
    startBtn->setIcon(QIcon(":/imgs/images/playbutton.png"));
    startBtn->setIconSize(QSize(150, 150));
    startBtn->setStyleSheet("background-color: transparent; border: none;");
    startBtn->move(1024 - 150, 678 - 150);
    connect(startBtn, &QToolButton::clicked, [this]()
            {
                GameView.setScene(&PlayScene);
                GameView.fitInView(GameView.sceneRect(), Qt::IgnoreAspectRatio);
                GameView.show();
            });

    // 新增简单难度按钮
    auto easyBtn = new QToolButton();
    easyBtn->resize(200, 100);
    easyBtn->setIconSize(QSize(200, 100));
    easyBtn->move(1024 - 200, 678 - 250 - 100);
    easyBtn->setText("简单");
    easyBtn->setFont(QFont("楷体", 20, 20, 5));
    connect(easyBtn, &QToolButton::clicked, this, &Widget::setEasyDifficulty);

    // 新增困难难度按钮
    auto hardBtn = new QToolButton();
    hardBtn->resize(200, 100);
    hardBtn->setIconSize(QSize(200, 100));
    hardBtn->move(1024 - 200, 678 - 250 - 100 - 100);
    hardBtn->setText("困难");
    hardBtn->setFont(QFont("楷体", 20, 20, 5));
    connect(hardBtn, &QToolButton::clicked, this, &Widget::setHardDifficulty);

    auto Instruction_Btn = new QToolButton();
    Instruction_Btn->resize(200, 100);
    Instruction_Btn->setIconSize(QSize(200, 100));
    Instruction_Btn->move(1024 - 200, 678 - 250 - 100 - 100 - 100);
    Instruction_Btn->setText("玩法介绍");
    Instruction_Btn->setFont(QFont("楷体", 20, 20, 5));
    connect(Instruction_Btn, &QToolButton::clicked, [this](){
        Instruction *w = new Instruction();
        w->show();
    });

    FirstScene.addWidget(Instruction_Btn);
    FirstScene.addWidget(easyBtn);
    FirstScene.addWidget(hardBtn);
    PlayScene.addWidget(Play_Menu_Btn);
    FirstScene.addWidget(chooseBtn_1);
    StartScene.addWidget(startBtn);
    PlayScene.addWidget(Exit_Btn);

    Player_Left_Move_Timer = new QTimer(this);
    Player_Left_Move_Timer->start(10);
    connect(Player_Left_Move_Timer, &QTimer::timeout, this, &Widget::Player_Left_Move);

    Player_Right_Move_Timer = new QTimer(this);
    Player_Right_Move_Timer->start(10);
    connect(Player_Right_Move_Timer, &QTimer::timeout, this, &Widget::Player_Right_Move);

    Run_Left_Right_Timer = new QTimer(this);
    connect(Run_Left_Right_Timer, &QTimer::timeout, this, &Widget::animateRun_Left_Right);

    Run_Left_Left_Timer = new QTimer(this);
    connect(Run_Left_Left_Timer, &QTimer::timeout, this, &Widget::animateRun_Left_Left);

    Run_Right_Right_Timer = new QTimer(this);
    connect(Run_Right_Right_Timer, &QTimer::timeout, this, &Widget::animateRun_Right_Right);

    Run_Right_Left_Timer = new QTimer(this);
    connect(Run_Right_Left_Timer, &QTimer::timeout, this, &Widget::animateRun_Right_Left);

    Left_JumpTimer = new QTimer(this);
    connect(Left_JumpTimer, &QTimer::timeout, this, &Widget::Left_Jump);

    Right_JumpTimer = new QTimer(this);
    connect(Right_JumpTimer, &QTimer::timeout, this, &Widget::Right_Jump);

    Fall_Timer = new QTimer(this);
    connect(Fall_Timer, &QTimer::timeout, this, &Widget::Fall);

    Right_Start_Hit_Timer = new QTimer(this);
    connect(Right_Start_Hit_Timer, &QTimer::timeout, this, &Widget::animateRight_Start_Hit);

    Right_Hit_Timer = new QTimer(this);
    connect(Right_Hit_Timer, &QTimer::timeout, this, &Widget::animateRight_Hit);

    Left_Start_Hit_Timer = new QTimer(this);
    connect(Left_Start_Hit_Timer, &QTimer::timeout, this, &Widget::animateLeft_Start_Hit);

    Left_Hit_Timer = new QTimer(this);
    connect(Left_Hit_Timer, &QTimer::timeout, this, &Widget::animateLeft_Hit);
}

Widget::~Widget()
{
    // 析构
    delete Player_Right_Move_Timer;
    delete Player_Left_Move_Timer;
    delete Run_Left_Right_Timer;
    delete Run_Left_Left_Timer;
    delete Run_Right_Right_Timer;
    delete Run_Right_Left_Timer;
    delete Left_JumpTimer;
    delete Right_JumpTimer;
    delete Fall_Timer;
    delete Right_Hit_Timer;
    delete Right_Start_Hit_Timer;
    delete Left_Start_Hit_Timer;
    delete Left_Hit_Timer;
    delete ball;
    delete ui;
}

void Widget::Player_Left_Move()
{
    for (int keyCode : mKeyList_Left)
    {
        switch (keyCode)
        {
        case Qt::Key_W: break;
        case Qt::Key_S: break;
        case Qt::Key_A:
            player_left.moveBy(-1 * player_left.PlayerSpeed, 0);
            if(!ball->Ball_is_Flying && ball->is_on_Left)
            {
                ball->moveBy(-1 * player_left.PlayerSpeed, 0);
            }
            break;
        case Qt::Key_D:
            player_left.moveBy(1 * player_left.PlayerSpeed, 0);
            if(!ball->Ball_is_Flying && ball->is_on_Left)
            {
                ball->moveBy(1 * player_left.PlayerSpeed, 0);
            }
            break;
        }
    }

    if (player_left.x() < 0)
    {
        player_left.setX(0);
    }
    if (player_left.x() > this->width() / 2 - player_left.pixmap().width())
    {
        player_left.setX(this->width() / 2 - player_left.pixmap().width());
    }
}

void Widget::Player_Right_Move()
{
    for (int keyCode : mKeyList_Right)
    {
        switch (keyCode)
        {
        case Qt::Key_I: break;
        case Qt::Key_K: break;
        case Qt::Key_J:
            player_right.moveBy(-1 * player_right.PlayerSpeed, 0);
            if(!ball->Ball_is_Flying && ball->is_on_Right)
            {
                ball->moveBy(-1 * player_right.PlayerSpeed, 0);
            }
            break;
        case Qt::Key_L:
            player_right.moveBy(1 * player_right.PlayerSpeed, 0);
            if(!ball->Ball_is_Flying && ball->is_on_Right)
            {
                ball->moveBy(1 * player_right.PlayerSpeed, 0);
            }
            break;
        }
    }

    if (player_right.x() < this->width() / 2)
    {
        player_right.setX(this->width() / 2);
    }
    if (player_right.x() > this->width() - player_right.pixmap().width())
    {
        player_right.setX(this->width() - player_right.pixmap().width());
    }
}

// void Widget::updateScoreboard()
// {
//     leftScoreLabel->setText(QString("Left: %1").arg(leftPlayerScore));
//     rightScoreLabel->setText(QString("Right: %1").arg(rightPlayerScore));
// }


void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        if (!mKeyList_Left.contains(event->key()))
        {
            mKeyList_Left.append(event->key());
            if (event->key() == Qt::Key_A) {
                Run_Left_Left_Timer->start(50);
            }
            else if (event->key() == Qt::Key_D) {
                Run_Left_Right_Timer->start(50);
            }
            else if (event->key() == Qt::Key_W && !L_isJumping)
            {
                L_isJumping = true;
                Left_JumpTimer->start(20);
            }
            else if (event->key() == Qt::Key_S && !ball->Ball_is_Flying && ball->is_on_Left)
            {
                Left_Start_Hit_Timer->start(100);
                ball->setVelocity(7, -10 , true);
                ball->Ball_is_Flying = true;
            }
            else if (event->key() == Qt::Key_S && ball->Ball_is_Flying)
            {
                Left_Hit_Timer->start(100);
            }
        }
        break;

    case Qt::Key_I:
    case Qt::Key_K:
    case Qt::Key_J:
    case Qt::Key_L:
        if (!mKeyList_Right.contains(event->key()))
        {
            mKeyList_Right.append(event->key());
            if (event->key() == Qt::Key_J)
            {
                Run_Right_Left_Timer->start(50);
            }
            else if (event->key() == Qt::Key_L)
            {
                Run_Right_Right_Timer->start(50);
            }
            else if (event->key() == Qt::Key_I && !R_isJumping)
            {
                R_isJumping = true;
                Right_JumpTimer->start(20);
            }
            else if (event->key() == Qt::Key_K && !ball->Ball_is_Flying && ball->is_on_Right)
            {
                Right_Start_Hit_Timer->start(100);
                ball->setVelocity(-7, -10, false);
                ball->Ball_is_Flying = true;
            }
            else if (event->key() == Qt::Key_K && ball->Ball_is_Flying)
            {
                Right_Hit_Timer->start(100);
            }
        }
        break;
    default:
        QWidget::keyPressEvent(event);
    }

    // 检查球拍与球的碰撞
    if (ball->getCollisionRect().intersects(player_left.boundingRect().translated(player_left.pos())) && ball->Ball_is_Flying)
    {
        qDebug() << "左边球拍击球";
        ball->setVelocity(7, -10, true); // 设置球的速度，使其反弹回去
        ball->Ball_is_Flying = true;
    }

    if (ball->getCollisionRect().intersects(player_right.boundingRect().translated(player_right.pos())) && ball->Ball_is_Flying)
    {
        qDebug() << "右边球拍击球";
        // 处理碰撞事件
        ball->setVelocity(-7, -10, false); // 设置球的速度，使其反弹回去
        ball->Ball_is_Flying = true;
    }
    // 检查球与球网的碰撞
    if (ball->getCollisionRect().intersects(mynet.boundingRect()))
    {
        qDebug() << "球碰到了球网";
        // 处理碰撞事件，例如反弹或停止球的运动
        ball->setVelocity(-ball->vx, -ball->vy, true); // 简单的反弹效果
    }

}

void Widget::updateScoreBoard()
{
    leftScoreLabel->setText(QString("左侧玩家得分: %1").arg(leftScore));
    rightScoreLabel->setText(QString("右侧玩家得分: %1").arg(rightScore));
}

void Widget::checkBallPosition()
{
    QPointF ballPos = ball->getBallPosition();

    if (ballPos.y() >= 650) // 假设 650 是地面高度
    {
        if (ballPos.x() < 512) // 球落在左侧
        {
            rightScore++;
            ball->lastWinner = "right"; // 更新获胜者为右侧玩家
        }
        else // 球落在右侧
        {
            leftScore++;
            ball->lastWinner = "left"; // 更新获胜者为左侧玩家
        }
        updateScoreBoard(); // 更新计分板的方法
        ball->Ball_is_Flying = false;
        ball->resetBallPosition();
        resetPlayerPositions();
    }

    checkGameOver();
}


void Widget::checkGameOver()
{
    if(leftScore >= 4)
    {
        GameView.setScene(&EndScene_Win);
        GameView.show();
    }
    else if(rightScore >= 4)
    {
        GameView.setScene(&EndScene_Lose);
        GameView.show();
    }
}


void Widget::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        mKeyList_Left.removeOne(event->key());
        if (event->key() == Qt::Key_A)
        {
            if (!mKeyList_Left.contains(Qt::Key_A))
            {
                Run_Left_Left_Timer->stop();
            }
        }
        else if (event->key() == Qt::Key_D) {
            if (!mKeyList_Left.contains(Qt::Key_D)) {
                Run_Left_Right_Timer->stop();
            }
        }
        break;

    case Qt::Key_I:
    case Qt::Key_K:
    case Qt::Key_J:
    case Qt::Key_L:
        mKeyList_Right.removeOne(event->key());
        if (event->key() == Qt::Key_L)
        {
            if (!mKeyList_Right.contains(Qt::Key_L))
            {
                Run_Right_Right_Timer->stop();
            }
        }
        else if (event->key() == Qt::Key_J)
        {
            if (!mKeyList_Right.contains(Qt::Key_J))
            {
                Run_Right_Left_Timer->stop();
            }
        }
        break;
    default:
        QWidget::keyReleaseEvent(event);
    }
}

void Widget::animateRun_Left_Right()
{
    if (!Run_Left_Right.isEmpty())
    {
        currentFrame_Left_Right++;
        if (currentFrame_Left_Right >= Run_Num_L_R)
            currentFrame_Left_Right = 0;

        if (currentFrame_Left_Right < Run_Left_Right.size())
        {
            QPixmap frame = Run_Left_Right.at(currentFrame_Left_Right);
            player_left.setPixmap(frame);
        }
    }
}

void Widget::animateRun_Left_Left()
{
    if (!Run_Left_Left.isEmpty())
    {
        currentFrame_Left_Left++;
        if (currentFrame_Left_Left >= Run_Num_L_L)
            currentFrame_Left_Left = 0;

        if (currentFrame_Left_Left < Run_Left_Left.size())
        {
            QPixmap frame = Run_Left_Left.at(currentFrame_Left_Left);
            player_left.setPixmap(frame);
        }
    }
}

void Widget::animateRun_Right_Right()
{
    if(!Run_Right_Right.isEmpty())
    {
        currentFrame_Right_Right++;
        if(currentFrame_Right_Right >= Run_Num_R_R)
        {
            currentFrame_Right_Right = 0;
        }
        if(currentFrame_Right_Right < Run_Right_Right.size())
        {
            QPixmap frame = Run_Right_Right.at(currentFrame_Right_Right);
            player_right.setPixmap(frame);
        }
    }
}

void Widget::animateRun_Right_Left()
{
    if(!Run_Right_Left.isEmpty())
    {
        currentFrame_Right_Left++;
        if(currentFrame_Right_Left >= Run_Num_R_L)
        {
            currentFrame_Right_Left = 0;
        }
        if(currentFrame_Right_Left < Run_Right_Left.size())
        {
            QPixmap frame = Run_Right_Left.at(currentFrame_Right_Left);
            player_right.setPixmap(frame);
        }
    }
}

void Widget::animateRight_Start_Hit()
{
    if(!Right_Start_Hit.isEmpty())
    {
        currentFrame_Right_Start_Hit++;
        if(currentFrame_Right_Start_Hit >= Right_Start_Hit_Frame)
        {
            currentFrame_Right_Start_Hit = 0;
            Right_Start_Hit_Timer->stop();
            Right_Hit_Timer->start(100);
        }
        else
        {
            if(currentFrame_Right_Start_Hit < Right_Start_Hit.size())
            {
                QPixmap frame = Right_Start_Hit.at(currentFrame_Right_Start_Hit);
                player_right.setPixmap(frame);
            }
        }
    }
}

void Widget::animateRight_Hit()
{
    if(!Right_Hit.isEmpty())
    {
        currentFrame_Right_Hit++;
        if(currentFrame_Right_Hit >= Right_Hit_Frame)
        {
            currentFrame_Right_Hit = 0;
            Right_Hit_Timer->stop();
        }
        else
        {
            if(currentFrame_Right_Hit < Right_Hit.size())
            {
                QPixmap frame = Right_Hit.at(currentFrame_Right_Hit);
                player_right.setPixmap(frame);
            }
        }
    }
}

void Widget::animateLeft_Start_Hit()
{
    if(!Left_Start_Hit.isEmpty())
    {
        currentFrame_Left_Start_Hit++;
        if(currentFrame_Left_Start_Hit >= Left_Start_Hit_Frame)
        {
            currentFrame_Left_Start_Hit = 0;
            Left_Start_Hit_Timer->stop();
            Left_Hit_Timer->start(100);
        }
        else
        {
            if(currentFrame_Left_Start_Hit < Left_Start_Hit.size())
            {
                QPixmap frame = Left_Start_Hit.at(currentFrame_Left_Start_Hit);
                player_left.setPixmap(frame);
            }
        }
    }
}

void Widget::animateLeft_Hit()
{
    if(!Left_Hit.isEmpty())
    {
        currentFrame_Left_Hit++;
        if(currentFrame_Left_Hit >= Left_Hit_Frame)
        {
            currentFrame_Left_Hit = 0;
            Left_Hit_Timer->stop();
        }
        else
        {
            if(currentFrame_Left_Hit < Left_Hit.size())
            {
                QPixmap frame = Left_Hit.at(currentFrame_Left_Hit);
                player_left.setPixmap(frame);
            }
        }
    }
}

void Widget::Right_Jump()
{
    if(R_currentJumpHeight < JumpHeight)
    {
        player_right.moveBy(0, -JumpSpeed);
        R_currentJumpHeight += JumpSpeed;
    }
    else
    {
        Right_JumpTimer->stop();
        Fall_Timer->start(20);
    }
}

void Widget::Left_Jump()
{
    if(L_currentJumpHeight < JumpHeight)
    {
        player_left.moveBy(0, -JumpSpeed);
        L_currentJumpHeight += JumpSpeed;
    }
    else
    {
        Left_JumpTimer->stop();
        Fall_Timer->start(20);
    }
}

void Widget::Fall()
{
    int groundY = this->height() - player_left.pixmap().height() - 42;

    if(L_isJumping)
    {
        if(player_left.y() < groundY)
        {
            player_left.moveBy(0, JumpSpeed);
        }
        else
        {
            L_isJumping = false;
            L_currentJumpHeight = 0;
            Fall_Timer->stop();
        }
    }
    if(R_isJumping)
    {
        if(player_right.y() < groundY)
        {
            player_right.moveBy(0, JumpSpeed);
        }
        else
        {
            R_isJumping = false;
            R_currentJumpHeight = 0;
            Fall_Timer->stop();
        }
    }
}

void Widget::resetPlayerPositions()
{
    player_left.setPos(237, 678 - 100 - 42);
    player_right.setPos(690, 678 - 100 - 42);

    if (!ball->Ball_is_Flying)
    {
        if (ball->is_on_Left)
        {
            ball->setPos(player_left.x() +  75, player_left.y() + 40);
        }
        else if (ball->is_on_Right)
        {
            ball->setPos(player_right.x() - 25, player_right.y() + 45);
        }
    }
}

void Widget::setEasyDifficulty()
{
    difficulty = Easy;
    qDebug() << "设置难度为简单";
}

void Widget::setHardDifficulty()
{
    difficulty = Hard;
    qDebug() << "设置难度为困难";
}
