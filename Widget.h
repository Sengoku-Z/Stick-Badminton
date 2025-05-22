#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>
#include <QSoundEffect>
#include "Ball.h"
#include "Player_Left.h"
#include "Player_Right.h"
#include "Menu.h"
#include "MyNet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void Player_Right_Move();
    void Player_Left_Move();
    void resetPlayerPositions();

    void animateRun_Left_Right();
    void animateRun_Left_Left();
    void animateRun_Right_Right();
    void animateRun_Right_Left();
    void animateRight_Start_Hit();
    void animateRight_Hit();
    void animateLeft_Start_Hit();
    void animateLeft_Hit();

    void Left_Jump();
    void Right_Jump();
    void Fall();

    void updateScoreBoard(); // 更新计分板的方法
    void checkBallPosition();
    void checkGameOver();

    void setEasyDifficulty(); // 设置简单难度
    void setHardDifficulty(); // 设置困难难度

    MyNet mynet;
    Player_Right player_right;
    Player_Left player_left;

    int leftScore = 0; // 左侧玩家得分
    int rightScore = 0; // 右侧玩家得分

    // 新增难度设置
    enum Difficulty { Easy, Hard };
    Difficulty difficulty;

    QRect netRect; // 定义球网的碰撞矩形

private:
    Ui::Widget *ui;

    QLabel *leftScoreLabel;
    QLabel *rightScoreLabel;

    Ball *ball;

    // 元素 -> 场景 -> 视图 -> 窗口
    // 其他成员变量和函数声明...
    QSoundEffect *GameMusic;
    QGraphicsView GameView;

    QGraphicsScene FirstScene;
    QGraphicsScene StartScene;
    QGraphicsScene PlayScene;
    QGraphicsScene EndScene_Win;
    QGraphicsScene EndScene_Lose;

    QGraphicsPixmapItem First_Item;
    QGraphicsPixmapItem Start_Scene;
    QGraphicsPixmapItem PlayScene_Item;
    QGraphicsPixmapItem Start_Button;
    QGraphicsPixmapItem Ball_Item;
    QGraphicsPixmapItem gMenu;
    QGraphicsPixmapItem Win_Item1;
    QGraphicsPixmapItem Win_Item2;
    QGraphicsPixmapItem Lose_Item;
    QGraphicsPixmapItem Lose_Black;
    QGraphicsPixmapItem Win_Black;
    QGraphicsPixmapItem Volleyball_PlayScene_Item;

    QTimer* Player_Right_Move_Timer;
    QTimer* Player_Left_Move_Timer;

// 键盘控制的容器链表，用于存储键盘的输入，实现同时性的操作
    QList<int> mKeyList_Left;
    QList<int> mKeyList_Right;

// 人物各个行走动作的帧数总数-----------------------------------------------------------------------------------
    int Run_Num_L_L;
    int Run_Num_L_R;
    int Run_Num_R_R;
    int Run_Num_R_L;
    int Right_Start_Hit_Frame;
    int Left_Start_Hit_Frame;
    int Right_Hit_Frame;
    int Left_Hit_Frame;

// 记录当前的帧数------------------------------------------------------------------------------------
    int currentFrame_Left_Right;
    int currentFrame_Left_Left;
    int currentFrame_Right_Right;
    int currentFrame_Right_Left;
    int currentFrame_Right_Start_Hit;
    int currentFrame_Right_Hit;
    int currentFrame_Left_Start_Hit;
    int currentFrame_Left_Hit;

// 初始化人物移动的动作的帧-----------------------------------------------------------------------------
    QList<QPixmap> Run_Left_Right;
    QList<QPixmap> Run_Left_Left;
    QList<QPixmap> Run_Right_Right;
    QList<QPixmap> Run_Right_Left;
    QList<QPixmap> Right_Start_Hit;
    QList<QPixmap> Right_Hit;
    QList<QPixmap> Left_Start_Hit;
    QList<QPixmap> Left_Hit;
    // 使用 QLinkedList 替换 QList
    // QLinkedList<QPixmap> Run_Left_Right;
    // QLinkedList<QPixmap> Run_Left_Left;
    // QLinkedList<QPixmap> Run_Right_Right;
    // QLinkedList<QPixmap> Run_Right_Left;
    // QLinkedList<QPixmap> Right_Start_Hit;
    // QLinkedList<QPixmap> Right_Hit;
    // QLinkedList<QPixmap> Left_Start_Hit;
    // QLinkedList<QPixmap> Left_Hit;

// 定时器-----------------------------------------------------------------------------------------------------------
    QTimer* Run_Left_Right_Timer;
    QTimer* Run_Left_Left_Timer;
    QTimer* Run_Right_Right_Timer;
    QTimer* Run_Right_Left_Timer;
    QTimer* Right_JumpTimer;
    QTimer* Left_JumpTimer;
    QTimer* Fall_Timer;
    QTimer* Right_Start_Hit_Timer;
    QTimer* Right_Hit_Timer;
    QTimer* Left_Start_Hit_Timer;
    QTimer* Left_Hit_Timer;

    bool L_isJumping;
    bool R_isJumping;
    int JumpHeight;
    int JumpSpeed;
    int L_currentJumpHeight;
    int R_currentJumpHeight;

};

#endif // WIDGET_H
