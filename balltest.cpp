#include "balltest.h" // 包含Ball1类的头文件
#include "qcoreevent.h" // 包含Qt核心事件类的头文件
#pragma once

Ball1::Ball1(QLabel *parent)
    : QLabel{parent} // Ball1类的构造函数，继承自QLabel
{
    x3 = 330; // 初始化球的x坐标
    y3 = 200; // 初始化球的y坐标
    ay3 = 3; // 初始化重力加速度
    vx3 = 0; // 初始化x方向速度
    vy3 = 0; // 初始化y方向速度

    ball1 = new QLabel; // 创建一个QLabel对象作为球的显示对象
    ball1->setParent(this); // 设置球的父对象为当前对象（可能是窗口或其他控件）

    ball1->setGeometry(x3, y3, 100, 100); // 设置球的初始几何位置和大小
    QImage *imgball = new QImage; // 创建一个QImage对象用于加载球的图片资源
    imgball->load("://images/images2/Husky.jpg"); // 加载球的图片资源
    ball1->setPixmap(QPixmap::fromImage(*imgball)); // 设置球显示的图片
    ball1->show(); // 显示球
}

void Ball1::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == id) // 如果定时器事件的ID与当前对象的ID匹配
    {
        if(judgefloor(x3, y3) == 0) // 如果球在空中，只受重力影响
        {
            if(vy3 <= 24 && vy3 >= -24) // 限制y方向速度的范围
            {
                vy3 -= ay3; // 应用重力加速度
            }
            if(vy3 > 24)
            {
                vy3 = 24; // 如果速度超过上限，设置为上限值
                ay3 = 3; // 重力加速度恢复初始值
            }
            if(vy3 < -24)
            {
                vy3 = -24; // 如果速度超过下限，设置为下限值
            }
        }
        if(judgewallleft(x3) == 1) // 如果球碰到左墙，反弹
        {
            vx3 = -vx3; // x方向速度取反
        }
        if(judgefloor(x3, y3) == 1) // 如果球碰到地面，反弹
        {
            vy3 = -vy3; // y方向速度取反
        }
        x3 += vx3; // 更新球的x坐标
        y3 -= vy3; // 更新球的y坐标（向上移动）

        // 更新球的显示位置和图片
        ball1->setGeometry(x3, y3, 100, 100); // 设置球的显示位置和大小
        QImage *imgball = new QImage; // 创建一个QImage对象用于加载球的图片资源
        imgball->load("://images/images2/Husky.jpg"); // 加载球的图片资源
        ball1->setPixmap(QPixmap::fromImage(*imgball)); // 设置球显示的图片
        ball1->show(); // 显示球
    }
}

bool Ball1::judgefloor(qreal x, qreal y)
{
    if(y >= 475 && y <= 485) // 如果球的y坐标在地面范围内
    {
        return true; // 返回true，表示球碰到地面
    }
    else
    {
        return false; // 返回false，表示球在空中
    }
}

bool Ball1::judgewallleft(qreal x)
{
    if(x <= 30) // 如果球的x坐标小于等于30
    {
        return true; // 返回true，表示球碰到左墙
    }
    else
    {
        return false; // 返回false，表示球没有碰到左墙
    }
}

bool Ball1::judgewallright(qreal x)
{
    if(x >= 710) // 如果球的x坐标大于等于710
    {
        return true; // 返回true，表示球碰到右墙
    }
    else
    {
        return false; // 返回false，表示球没有碰到右墙
    }
}
