#ifndef BALL_H
#define BALL_H
#pragma once // 防止头文件被包含多次

#include<QWidget>
#include <QObject>
#include<QTimer>
#include<QLabel>
#include<QPixmap>
#include<QImage>
#include<QTimer>

class Ball1 : public QLabel
{
    Q_OBJECT
public:
    explicit Ball1(QLabel *parent = nullptr);

    QLabel *ball1;

    // 球的各个属性
    int id = 20;
    int x3, y3;
    int vx3, vy3;
    float ay3;

    // 定时器事件处理函数，更新球的位置
    void timerEvent(QTimerEvent *event) override;

    // 碰撞检测函数，判断是否碰到地面
    bool judgefloor(qreal x, qreal y);

    // 碰撞检测函数，判断是否碰到左墙
    bool judgewallleft(qreal x);

    // 碰撞检测函数，判断是否碰到右墙
    bool judgewallright(qreal x);
};

#endif // BALL_H
