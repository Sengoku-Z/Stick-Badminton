#ifndef MOVETEST_H
#define MOVETEST_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QLabel>
#include <QKeyEvent>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QUrl>
#include <QDebug>
#include "balltest.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Movetest;
}
QT_END_NAMESPACE

class Movetest : public QWidget

{
    Q_OBJECT

public:

    Movetest(QWidget *parent = nullptr);

    ~Movetest();

    QLabel* player; // 玩家 1 的 QLabel
    QLabel* player2; // 玩家 2 的 QLabel
    QLabel* ball; // 球的 QLabel

    // player1
    int modex, modey; // 玩家 1 的模式变量
    int n; // 的计数变量
    qreal vx, vy; // 玩家 1 的速度变量
    qreal X, Y; // 玩家 1 的位置变量
    qreal ax, ay; // 玩家 1 的加速度变量
    qreal id; // 定时器 ID
    int score1; // 玩家 1 的得分
    bool PressFlag = false; // 玩家 1 的按键标志

    // player2
    int modex2, modey2;
    int n2;
    qreal vx2, vy2;
    qreal X2, Y2;
    qreal ax2, ay2;
    int score2;

    // ball
    int modex3, modex4;
    int n3;
    qreal x3, y3;
    qreal vx3, vy3;
    qreal ballheight;
    qreal ballwidth;
    qreal ay3;

    bool isstart = false; // 游戏是否开始标志
    bool isnormal; // 游戏模式标志

    static bool up; // 静态变量，表示球网的状态
    bool down; // 球的下落状态

    // 判断球是否接触地面
    bool judgefloor(qreal x, qreal y);

    // 判断球是否接触左墙
    bool judgewallleft(qreal x);

    bool judgewallright(qreal y);

    // 判断球是否接触网
    bool judgenet(qreal x, qreal y);

    // 判断球是否接触网顶部
    bool judgenet_head(qreal x, qreal y);

    // 判断球是否接触玩家 1 的头部
    bool judge_player1_head(qreal x, qreal y);

    // 判断球是否接触玩家 1 的右侧
    bool judge_player1_right(qreal x, qreal y);

    // 判断球是否接触玩家 1 的左侧
    bool judge_player1_left(qreal x, qreal y);

    // 判断球是否接触玩家 2 的头部
    bool judge_player2_head(qreal x, qreal y);

    // 判断球是否接触玩家 2 的右侧
    bool judge_player2_right(qreal x, qreal y);

    // 判断球是否接触玩家 2 的左侧
    bool judge_player2_left(qreal x, qreal y);

    // 判断是否需要切换到上升状态
    bool switch_up(qreal x, qreal y);

    // 判断是否需要切换到下降状态
    bool switch_down(qreal x, qreal y);

    void timerEvent(QTimerEvent *ev) override;

    void keyPressEvent(QKeyEvent *key) override;

    void keyReleaseEvent(QKeyEvent *key) override;

    // 绘制事件处理函数
    // event 绘制事件指针
    void paintEvent(QPaintEvent *event) override;

signals:

    // 返回信号，用于触发返回操作
    void back();

private:
    Ui::Movetest *ui;
};

#endif // MOVETEST_H
