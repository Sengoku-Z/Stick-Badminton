#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QToolButton>

class Widget;

class Ball : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    // 构造函数，接受一个指向 Widget 的指针作为参数
    Ball(Widget* widget);
    // 设置球的速度和方向，isLeftPlayer 表示是否是左侧玩家，用于发球的判断
    void setVelocity(double vx, double vy, bool isLeftPlayer);
    void Ball_Move(); // 球的移动
    void resetBallPosition(); // 重置球的位置
    void followPlayer(); // 实现发球前，球跟着人走
    QRectF getCollisionRect() const; // 新增的获取碰撞矩形函数
    QPointF getBallPosition() const; // 获取球当前的位置

    // 球的初始属性
    double x;
    double y;
    double vx;
    double vy;
    QRect boundingRec; // 判定碰撞
    QPixmap ballPix;
    bool Ball_is_Flying;
    bool is_on_Left;
    bool is_on_Right;
    double ballg; // 重力加速度，模拟日常生活
    int All_Score;
    QString ballType; // 新增的球类型属性
    QString lastWinner = "left"; // 记录谁赢了上一分 将羽毛球模式改为谁赢了谁发球

private:
    QTimer *moveTimer; // 定时器
    QToolButton *Continue_Btn; // 继续游戏的按钮
    Widget* widget;
};

#endif // BALL_H
