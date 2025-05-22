#include "Ball.h" // 包含Ball类的头文件
#include <QPixmap> // 包含Qt图片类的头文件
#include <QTimer> // 包含Qt定时器类的头文件
#include <QGraphicsScene> // 包含Qt图形场景类的头文件
#include <QDebug> // 包含Qt调试类的头文件，用于输出调试信息
#include "Widget.h" // 包含Widget类的头文件，用于访问游戏窗口对象

Ball::Ball(Widget* widget) // Ball类的构造函数，接受一个Widget对象指针作为参数
    : vx(0), vy(0), Ball_is_Flying(false), is_on_Left(true), is_on_Right(false), ballg(0.2), Continue_Btn(new QToolButton()),
    widget(widget) // 初始化列表，初始化成员变量和对象指针
{
    ballType = "left"; // 默认为左侧玩家的球类型

    // 加载球的图片资源
    QPixmap BallPixmap(":/imgs/images/ball.png");
    setPixmap(BallPixmap); // 设置球的图片

    // 初始化位置
    resetBallPosition();

    // 设置继续按钮的属性和信号槽连接
    Continue_Btn->setAutoRaise(true); // 设置按钮自动升起
    Continue_Btn->resize(300, 150); // 设置按钮大小
    Continue_Btn->setText("继续"); // 设置按钮文本
    Continue_Btn->setIconSize(QSize(300, 150)); // 设置按钮图标大小
    Continue_Btn->move(1024 / 2 + 100, 678 / 2 + 25); // 移动按钮到指定位置
    Continue_Btn->setEnabled(false); // 初始状态下禁用按钮
    Continue_Btn->setVisible(false); // 初始状态下隐藏按钮
    connect(Continue_Btn, &QToolButton::clicked, [this, widget]()
            {
                // 继续按钮点击事件的处理逻辑，例如重置游戏状态等
                Ball_is_Flying = false; // 球不再飞行
                resetBallPosition(); // 重置球的位置
                widget->resetPlayerPositions(); // 调用Widget类中的函数重置玩家位置
                Continue_Btn->setEnabled(false); // 禁用继续按钮
                Continue_Btn->setVisible(false); // 隐藏继续按钮
            });

    // 创建一个移动定时器，并连接到 Ball_Move 函数
    moveTimer = new QTimer(this); // 创建移动定时器对象
    connect(moveTimer, &QTimer::timeout, this, &Ball::Ball_Move); // 连接定时器的超时信号到Ball_Move函数
    moveTimer->start(30); // 定时器每30毫秒触发一次，更新球的位置
}

void Ball::setVelocity(double vx, double vy, bool isLeftPlayer)
{
    // 设置球的速度和类型
    double speedMultiplier = 1.0;

    if (widget->difficulty == Widget::Easy)
    {
        speedMultiplier = 0.83;
    }
    else if (widget->difficulty == Widget::Hard)
    {
        speedMultiplier = 1.1;
    }

    this->vx = vx * speedMultiplier; // 设置水平速度并调整
    this->vy = vy * speedMultiplier; // 设置垂直速度并调整
    if (isLeftPlayer)
    {
        setPixmap(QPixmap(":/imgs/images/ball.png")); // 设置为左侧玩家的球图片
        ballType = "left"; // 设置球类型为左侧
    }
    else
    {
        setPixmap(QPixmap(":/imgs/images/ball_right.png")); // 设置为右侧玩家的球图片
        ballType = "right"; // 设置球类型为右侧
    }
}

void Ball::resetBallPosition()
{
    if (lastWinner == "left")
    { // 如果上次得分为左侧玩家
        x = 310; // 设置球的x位置为310
        is_on_Left = true; // 标记在左侧
        is_on_Right = false; // 标记不在右侧
    }
    else
    {
        x = 650; // 设置球的x位置为650
        is_on_Left = false; // 标记不在左侧
        is_on_Right = true; // 标记在右侧
    }
    y = 580; // 设置球的y位置为580
    setPos(x, y); // 更新球的场景位置
}

void Ball::followPlayer()
{
    if (!Ball_is_Flying)
    {
        // 如果球没有飞行
        if (is_on_Left && widget)
        {
            // 如果球在左侧且widget对象存在
            x = widget->player_left.x() + 75; // 调整球相对于左侧玩家的位置
            y = widget->player_left.y() + 40;
        }
        else if (is_on_Right && widget)
        {
            // 如果球在右侧且widget对象存在
            x = widget->player_right.x() - 20; // 调整球相对于右侧玩家的位置
            y = widget->player_right.y() + 45;
        }
        setPos(x, y); // 更新球的场景位置
    }
}

void Ball::Ball_Move()
{
    if (Ball_is_Flying)
    {
        // 更新球的位置
        x += vx; // 更新水平位置
        y += vy; // 更新垂直位置
        vy += ballg; // 更新垂直速度，模拟重力

        // 检查球是否碰到墙壁
        if (x <= 0 || x + boundingRect().width() >= 1024)
        {
            vx = -vx; // 反转水平速度，实现反弹
        }

        // 检查球是否落地
        if (y >= 650)
        {
            // 如果球到达地面
            y = 650; // 设置球的y位置为地面高度
            Ball_is_Flying = false; // 球停止飞行
            if (widget->leftScore <= 4 || widget->rightScore <= 4)
            {
                // 如果左右玩家得分不超过4分
                Continue_Btn->setEnabled(true); // 启用继续按钮
                Continue_Btn->setVisible(true); // 显示继续按钮
            }
        }

        // 检查球是否碰到球网
        if (widget->netRect.contains(x, y))
        {
            vx = -vx; // 反转球的水平速度
        }

        setPos(x, y); // 更新球的场景位置

        widget->checkBallPosition(); // 调用Widget类中的函数检查球的位置
    }
    else
    {
        followPlayer(); // 如果球没有飞行，则跟随玩家
    }
}

QRectF Ball::getCollisionRect() const
{
    // 返回球的碰撞矩形
    return boundingRect().translated(pos());
}

QPointF Ball::getBallPosition() const
{
    return pos(); // 返回球的当前位置
}
