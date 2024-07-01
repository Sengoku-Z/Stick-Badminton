#include "Widget.h"
#include "ui_Widget.h"
#include <QMediaPlayer>
#include <QToolButton>
#include <QGraphicsPixmapItem>
#include "Inlog.h"
#include "Regis.h"
#include <QFont>
#include <QTimer>
#include <QKeyEvent>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 音效设置 到时候定义一个槽，选择了之后在播放音乐，这个先这么放着
    GameMusic = new QSoundEffect(this); // 创建游戏音效对象
    GameMusic->setSource(QUrl::fromLocalFile(":/music/music/gamemusic.wav")); // 设置音效文件
    GameMusic->setLoopCount(QSoundEffect::Infinite); // 设置循环播放
    GameMusic->play(); // 播放音效
// 图像处理------------------------------------------------------------------------------------------------------------------------------------
    // 设置窗口固定大小
    this->setFixedSize(1024, 678);
    GameView.setFixedSize(1024, 678);

    // 设置视图大小和场景矩形
    GameView.setSceneRect(QRect(0, 0, 1024, 678)); // 设置视图大小
    PlayScene.setSceneRect(QRect(0, 0, 1024, 678)); // 背景(游戏进行时场景)
    StartScene.setSceneRect(QRect(0, 0, 1024, 678)); // 开始场景
    FirstScene.setSceneRect(QRect(0, 0, 1024, 678)); // 第一个选择场景

    // 添加选择场景背景图像
    QGraphicsPixmapItem *chooseBackground = new QGraphicsPixmapItem();
    chooseBackground->setPixmap(QPixmap(":/imgs/images/FirstScene.png"));
    FirstScene.addItem(chooseBackground);
    // 添加开始场景背景图像
    QGraphicsPixmapItem *startBackground = new QGraphicsPixmapItem();
    startBackground->setPixmap(QPixmap(":/imgs/images/StartScene.png"));
    StartScene.addItem(startBackground);
    // 添加游戏场景背景图像
    QGraphicsPixmapItem *playBackground = new QGraphicsPixmapItem();
    playBackground->setPixmap(QPixmap(":/imgs/images/Play_Item.png").scaled(1024, 678, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    PlayScene.addItem(playBackground);

    // 设置初始场景为选择场景
    GameView.setScene(&FirstScene);


    // 设置视图的父亲为窗口
    GameView.setParent(this);
    GameView.show();
    GameView.fitInView(GameView.sceneRect(), Qt::IgnoreAspectRatio); // 调整视图以适应场景

    PlayScene.addItem(&mynet); // 羽毛球网加入到场景里面
    PlayScene.addItem(&player_left);
    PlayScene.addItem(&player_right);

// 按钮处理------------------------------------------------------------------------------------------------------------------------------------
    // 羽毛球游戏选择按钮
    auto chooseBtn_1 = new QToolButton();
    chooseBtn_1->resize(360, 95);
    chooseBtn_1->setIconSize(QSize(360, 100));
    chooseBtn_1->move(1024 - 360, 678 - 100);
    chooseBtn_1->setText("Badminton");
    chooseBtn_1->setFont(QFont("楷体", 40, 20, 5)); // 字体，字号，加粗，倾斜
    //chooseBtn_1->setStyleSheet("background-color: transparent;"); // 把原先图片白的部分，变成透明，不会覆盖住原图
    connect(chooseBtn_1, &QToolButton::clicked, [this]()
    {
        GameView.setScene(&StartScene);
        GameView.show();
    });

    // 创建开始按钮
    auto startBtn = new QToolButton();
    startBtn->setAutoRaise(true); // 能让按键好看一点
    startBtn->resize(150, 150);
    startBtn->setIcon(QIcon(":/imgs/images/playbutton.png"));
    startBtn->setIconSize(QSize(150, 150));
    startBtn->setStyleSheet("background-color: transparent; border: none;"); // 把原先图片白的部分，变成透明，不会覆盖住原图
    startBtn->move(1024 - 150, 678 - 150);
    // lamada表达式
    connect(startBtn, &QToolButton::clicked, [this]()
    {
        GameView.setScene(&PlayScene);
        GameView.fitInView(GameView.sceneRect(), Qt::IgnoreAspectRatio);
        GameView.show();
    });

    FirstScene.addWidget(chooseBtn_1);
    StartScene.addWidget(startBtn);

    Player_Left_Move_Timer = new QTimer(this);
    Player_Left_Move_Timer->start(10);
    connect(Player_Left_Move_Timer, &QTimer::timeout, this, &Widget::Player_Left_Move);
    Player_Right_Move_Timer = new QTimer(this);
    Player_Right_Move_Timer->start(10);
    connect(Player_Right_Move_Timer, &QTimer::timeout, this, &Widget::Player_Right_Move);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Player_Left_Move()
{
    for(int keyCode : mKeyList_Left)
    {
        switch(keyCode)
        {
        case Qt::Key_W : break;
        case Qt::Key_S : break;
        case Qt::Key_A : player_left.moveBy(-1 * player_left.PlayerSpeed, 0); break;
        case Qt::Key_D : player_left.moveBy(1 * player_left.PlayerSpeed, 0); break;
        }
    }

    // if(player_left.x() < 0)
    // {
    //     player_left.setX(0);
    // }
    // if(player_left.x() > this->width() / 2 - player_left.pixmap().width())
    // {
    //     player_left.setX(this->width() / 2 - player_left.pixmap().width());
    // }
}

void Widget::Player_Right_Move()
{
    for(int keyCode : mKeyList_Right)
    {
        switch(keyCode)
        {
        case Qt::Key_Up : break;
        case Qt::Key_Down : break;
        case Qt::Key_Left : player_right.moveBy(-1 * player_right.PlayerSpeed, 0); break;
        case Qt::Key_Right : player_right.moveBy(1 * player_right.PlayerSpeed, 0); break;
        }
    }

    // if(player_right.x() < this->width() / 2)
    // {
    //     player_right.setX(this->width() / 2);
    // }
    // if(player_right.x() > this->width() - player_right.pixmap().width())
    // {
    //     player_right.setX(this->width() - player_right.pixmap().width());
    // }
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    // 左边玩家的按键
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        if (!mKeyList_Left.contains(event->key()))
        {
            mKeyList_Left.append(event->key());
        }
        break;

    // 右边玩家的按键
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (!mKeyList_Right.contains(event->key()))
        {
            mKeyList_Right.append(event->key());
        }
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    // 左边玩家的按键
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        mKeyList_Left.removeOne(event->key());
        break;

    // 右边玩家的按键
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        mKeyList_Right.removeOne(event->key());
        break;
    }
}

