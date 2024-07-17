#include "movetest.h"
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include "ui_movetest.h"
#include <Windows.h>

bool Movetest::up = false;

Movetest::Movetest(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Movetest)
{
    ui->setupUi(this);

    // 设置窗口大小和标题
    this->setFixedSize(730, 500);
    this->setWindowTitle("Volleyball");
    this->setWindowIcon(QIcon("://images/images2/ball1.png"));

    // 初始化玩家和球的属性
    modex = 0;
    modey = 0;
    n = 1;
    vx = 0;
    vy = 0;
    X = 100;
    Y = 350;
    ax = 10;
    ay = 0;

    modex2 = 0;
    modey2 = 0;
    n2 = 1;
    vx2 = 0;
    vy2 = 0;
    X2 = 500;
    Y2 = 350;
    ax2 = 10;
    ay2 = 0;
    id = startTimer(30);

    x3 = 330;
    y3 = 50;
    vy3 = 0;
    vx3 = 0;

    score1 = 0;
    score2 = 0;
    isnormal = false;
    isstart = true;

    // 初始化QLabel
    player = new QLabel(this);
    player2 = new QLabel(this);
    ball = new QLabel(this);
}

Movetest::~Movetest()
{
    delete ui;
}

bool Movetest::judgefloor(qreal x, qreal y)
{
    return y >= 350;
}

bool Movetest::judgewallleft(qreal x)
{
    return x <= 30;
}

bool Movetest::judgewallright(qreal x)
{
    return x >= 620;
}

bool Movetest::judgenet(qreal x, qreal y)
{
    if (!up) {
        if (vx3 >= 0)
            return (x + 60 >= 350) && (x + 60 <= 370) && (y + 60 >= 220);
        else if (vx3 <= 0)
            return (x <= 350) && (x >= 330) && (y + 60 >= 220);
        else
            return false;
    }

    if (up) {
        if (vx3 >= 0)
            return (x + 60 >= 350) && (x + 60 <= 370) && (y + 60 >= 140);
        else if (vx3 <= 0)
            return (x <= 350) && (x >= 330) && (y + 60 >= 140);
        else
            return false;
    }
}

bool Movetest::judgenet_head(qreal x, qreal y)
{
    if (!up)
        return (y + 60 >= 230) && (y + 60 <= 255) && (x + 50 >= 350) && (x + 10 <= 360);
    if (up)
        return (y + 60 >= 150) && (y + 60 <= 175) && (x + 50 >= 350) && (x + 10 <= 360);
}

bool Movetest::judge_player1_head(qreal x, qreal y)
{
    return (y + 60 >= Y - 4) && (y + 60 <= Y + 28) && (x + 40 >= X)
           && (x <= X + player->width() - 15);
}

bool Movetest::judge_player1_right(qreal x, qreal y)
{
    return judge_player1_head(x, y) == 0 && (x >= X + player->width() - 27)
           && (x <= X + player->width() - 3) && (y + 30 >= Y) && (y + 30 <= Y + player->height());
}

bool Movetest::judge_player1_left(qreal x, qreal y)
{
    return judge_player1_head(x, y) == 0 && (x + 60 >= X - 12) && (x + 60 <= X + 12)
           && (y + 30 >= Y) && (y + 30 <= Y + player->height());
}

bool Movetest::judge_player2_head(qreal x, qreal y)
{
    return (y + 60 >= Y2) && (y + 60 <= Y2 + 25) && (x + 40 >= X2)
           && (x <= X2 + player2->width() - 27);
}

bool Movetest::judge_player2_right(qreal x, qreal y)
{
    return judge_player2_head(x, y) == 0 && (x >= X2 + player2->width() - 27)
           && (x <= X2 + player2->width() - 3) && (y + 30 >= Y2)
           && (y + 30 <= Y2 + player2->height());
}

bool Movetest::judge_player2_left(qreal x, qreal y)
{
    return judge_player2_head(x, y) == 0 && (x + 60 >= X2 - 12) && (x + 60 <= X2 + 12)
           && (y + 30 >= Y2) && (y + 30 <= Y2 + player2->height());
}

bool Movetest::switch_up(qreal x, qreal y)
{
    return ((x <= 37) && (250 <= y + 40) && (y + 20 <= 270))
           || ((x + 60 >= 693) && (250 <= y + 40) && (y + 20 <= 270));
}

bool Movetest::switch_down(qreal x, qreal y)
{
    return ((vx3 < 0) && (x <= 367) && (x >= 355) && (300 <= y + 40) && (y + 20 <= 320))
           || ((vx3 > 0) && (x + 60 >= 343) && (x + 60 <= 355) && (300 <= y + 40)
               && (y + 20 <= 320));
}

void Movetest::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() == id && isstart) {
        // 画出三个物体
        QImage *img = new QImage;
        img->load("://images/images2/player1_left.png");
        player->setPixmap(QPixmap::fromImage(*img));

        QImage *img2 = new QImage;
        img2->load("://images/images2/player1_right.png");
        player2->setPixmap(QPixmap::fromImage(*img2));

        QImage *imgball = new QImage;
        imgball->load("://images/images2/ball1.png");
        QPixmap ball2("://images/images2/ball1.png");
        ball2 = ball2.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation); // 调整图片大小
        ball->setPixmap(ball2);

        // 设置球网状态
        if (!isnormal)
        {
            if (switch_up(x3, y3) == 1)
            {
                up = true;
                update();
            }

            if (switch_down(x3, y3) == 1)
            {
                up = false;
                update();
            }
        }

        // 确定每id毫秒player1的位置信息
        if (modex == 0)
        {
            vx = 0;
        }
        if (GetAsyncKeyState('A') & 0x8000)
        {
            vx = judgewallleft(X) ? 0 : -10;
        }
        if (GetAsyncKeyState('D') & 0x8000)
        {
            vx = (X + player->width() - 15 >= 350) ? 0 : 10;
        }
        if (judgefloor(X, Y) == 1)
        {
            Y = 350;
            if (GetAsyncKeyState('W') & 0x8000)
            {
                vy = 24;
            }
            else
            {
                vy = 0;
                ay = 0;
            }
            n = 1;
        }
        if (judgefloor(X, Y) == 0) {
            ay = 3;
            vy = (vy > 24) ? 24 : (vy < -24) ? -24 : vy - ay;
        }
        X += vx;
        Y -= vy;

        // 确定每id毫秒player2的位置信息
        if (modex2 == 0) {
            vx2 = 0;
        }
        if (GetAsyncKeyState(37)) {
            vx2 = (X2 <= 360) ? 0 : -10;
        }
        if (GetAsyncKeyState(39)) {
            vx2 = judgewallright(X2) ? 0 : 10;
        }
        if (judgefloor(X2, Y2) == 1)
        {
            Y2 = 350;
            if (GetAsyncKeyState(38)) {
                vy2 = 24;
            } else {
                vy2 = 0;
                ay2 = 0;
            }
            n2 = 1;
        }
        if (judgefloor(X2, Y2) == 0)
        {
            ay2 = 3;
            vy2 = (vy2 > 24) ? 24 : (vy2 < -24) ? -24 : vy2 - ay2;
        }
        X2 += vx2;
        Y2 -= vy2;

        // 确定每id毫秒ball的位置信息
        if (judgefloor(x3, y3) == 0)
        {
            ay3 = 1.1;
            vy3 = (vy3 > 20) ? 20 : (vy3 < -20) ? -20 : vy3 - ay3;
        }
        if (judgewallleft(x3))
        {
            vx3 = -vx3;
        }
        if (x3 >= 640)
        {
            vx3 = -vx3;
        }
        if (y3 >= 375)
        {
            int ret1;
            int ret2;
            if (score1 <= 4 && score2 <= 4)
            {
                if (x3 <= 350)
                {
                    score2++;
                    if (score2 < 5)

                    ret1 = QMessageBox::question(this,
                                                     tr("红方得分！"),
                                                     tr("红方得分！是否继续？"),
                                                     QMessageBox::Ok);
                }
                else
                {
                    score1++;
                    if (score1 < 5)
                        ret2 = QMessageBox::question(this,
                                                     tr("蓝方得分！"),
                                                     tr("蓝方得分！是否继续？"),
                                                     QMessageBox::Ok);
                }
                if (ret1 == QMessageBox::Ok || ret2 == QMessageBox::Ok)
                {
                    x3 = 330;
                    y3 = 100;
                    vx3 = 5;
                    vy3 = 15;
                    modex = 0;
                    modey = 0;
                    n = 1;
                    vx = 0;
                    vy = 0;
                    X = 100;
                    Y = 350;
                    ax = 10;
                    ay = 0;
                    modex2 = 0;
                    modey2 = 0;
                    n2 = 1;
                    vx2 = 0;
                    vy2 = 0;
                    X2 = 500;
                    Y2 = 350;
                    ax2 = 10;
                    ay2 = 0;
                    up = false;
                    this->show();
                }
                if(ret1 == QMessageBox::No || ret2 == QMessageBox::No) {
                    this->close();
                }
            }
            if (!isnormal)
            {
                if (score1 == 5)
                {
                    ret1 = QMessageBox::question(this,
                                                 tr("蓝方胜利"),
                                                 tr("蓝方胜利！"),
                                                 QMessageBox::Ok);
                    if (ret1 == QMessageBox::Ok)
                        this->killTimer(id);
                    connect(ui->back, &QPushButton::clicked, [=]() { emit this->back(); });
                }
                if (score2 == 5)
                {
                    ret2 = QMessageBox::question(this,
                                                 tr("红方胜利"),
                                                 tr("红方胜利！"),
                                                 QMessageBox::Ok);
                    if (ret2 == QMessageBox::Ok)
                        this->killTimer(id);
                    connect(ui->back, &QPushButton::clicked, [=]() { emit this->back(); });
                }
            }
            else
            {
                if (score1 == 5)
                {
                    ret1 = QMessageBox::question(this,
                                                 tr("蓝方胜利"),
                                                 tr("蓝方胜利！"),
                                                 QMessageBox::Ok);
                    if (ret1 == QMessageBox::Ok)
                        this->killTimer(id);
                    connect(ui->back, &QPushButton::clicked, [=]() { emit this->back(); });
                }
                if (score2 == 5)
                {
                    ret2 = QMessageBox::question(this,
                                                 tr("红方胜利"),
                                                 tr("红方胜利！"),
                                                 QMessageBox::Ok);
                    if (ret2 == QMessageBox::Ok)
                        this->killTimer(id);
                    connect(ui->back, &QPushButton::clicked, [=]() { emit this->back(); });
                }
            }
        }

        if (judgenet(x3, y3)) {
            vx3 = -vx3;
        }
        if (judgenet_head(x3, y3) && !judgenet(x3, y3)) {
            vy3 = -vy3;
        }

        if (judge_player1_head(x3, y3))
        {
            if (vy3 <= 0)
            {
                if (modex != 0)
                {
                    vy3 = -vy3;
                    vx3 = vx;
                    vy = (vy > 0) ? 0 : vy;
                }
                else if (modex == 0)
                {
                    vy3 = -vy3;
                    vy = (vy > 0) ? 0 : vy;
                }
                if (modey == 0)
                {
                    vy3 = -vy3;
                    vy = 0;
                }
            }
            if (vy3 < 0)
            {
                vy3 = -vy3;
            }
        }

        if (judge_player2_head(x3, y3))
        {
            if (vy3 <= 0)
            {
                if (modex2 != 0)
                {
                    vy3 = -vy3;
                    vx3 = vx2;
                    vy2 = (vy2 > 0) ? 0 : vy2;
                }
                else if (modex2 == 0)
                {
                    vy3 = -vy3;
                    vy2 = (vy2 > 0) ? 0 : vy2;
                }
                if (modey2 == 0)
                {
                    vy3 = -vy3;
                    vy = 0;
                }
            }
            if (vy3 < 0)
                vy3 = -vy3;
        }

        x3 += vx3;
        y3 -= vy3;

        // 更新角色和球的位置
        player->setGeometry(X, Y, 100, 100);
        player2->setGeometry(X2, Y2, 100, 100);
        ball->setGeometry(x3, y3, 100, 100);

        // 显示角色和球
        player->show();
        player2->show();
        ball->show();
    }
}

void Movetest::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
    {
        modex--;
    }
    if (event->key() == Qt::Key_D)
    {
        modex++;
    }
    if (event->key() == Qt::Key_W)
    {
        modey++;
    }

    if (event->key() == Qt::Key_Left)
    {
        modex2--;
    }
    if (event->key() == Qt::Key_Right)
    {
        modex2++;
    }
    if (event->key() == Qt::Key_Up)
    {
        modey2++;
    }
}

void Movetest::keyReleaseEvent(QKeyEvent *key)
{
    if (key->key() == Qt::Key_A || key->key() == Qt::Key_D)
    {
        modex = 0;
        modey = 0;
    }
    if (key->key() == Qt::Key_Left || key->key() == Qt::Key_Right)
    {
        modex2 = 0;
        modey2 = 0;
    }
}

void Movetest::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    QPixmap background(":/imgs/images/Play_Item.png");
    painter.drawPixmap(30, 0, 670, 480, background);

    painter.drawLine(30, 480, 700, 480);
    painter.drawLine(30, 480, 30, -100);
    painter.drawLine(700, -100, 700, 480);

    if(!isnormal)
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawRect(693, 260, 7, 20);
        painter.drawRect(30, 260, 7, 20);

        painter.setPen(Qt::green);
        painter.setBrush(Qt::green);
        painter.drawRect(343, 300, 7, 20);
        painter.drawRect(360, 300, 7, 20);
    }

    if(!up)
    {
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
        painter.drawPixmap(350, 230, 10, 220, QPixmap("://images/images2/net1.png"));
    }
    else if(up)
    {
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
        painter.drawPixmap(350, 150, 10, 300, QPixmap("://images/images2/net1.png"));
    }

    QFont font2("Courier", 30);
    painter.setFont(font2);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawText(340, 75, ":");
    if(score1 < 4)
    {
        painter.drawText(280, 75, QString::number(score1));
    }
    else if(score1 == 5)
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawText(280, 75, QString::number(score1));
    }
    else
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawText(280, 75, QString::number(score1));
        painter.setFont(QFont("Courier", 14));
        painter.drawText(225, 95, "match point");
    }

    if (score2 < 4)
    {
        painter.drawText(400, 75, QString::number(score2));
    }
    else if (score2 == 5)
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawText(400, 75, QString::number(score2));
    }
    else
    {
        painter.setPen(Qt::red);
        painter.setBrush(Qt::red);
        painter.drawText(400, 75, QString::number(score2));
        painter.setFont(QFont("Courier", 14));
        painter.drawText(360, 95, "match point");
    }
}
