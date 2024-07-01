#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWidget>
#include <QGraphicsPixmapItem> // 图形元素
#include <QGraphicsView> // 视图
#include <QGraphicsScene> // 场景
#include <QList> // QList 链表
#include <QtMultimedia/QSoundEffect> // 使用音效
#include <QSqlDatabase> // 数据驱动
#include <QSqlQuery> // 数据库执行语句
#include <QMessageBox> // 消息盒子
#include <QDebug>
#include <MyNet.h>
#include <Player_Left.h>
#include <Player_Right.h>
#include <QTimer>

// 元素组成 --->  场景 ---> 视图 ---> 窗口

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // 按键事件
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void Player_Right_Move();
    void Player_Left_Move();


private:
    Ui::Widget *ui;

    QSoundEffect *GameMusic;//背景音乐
    QGraphicsView GameView; // 游戏视图

    // 场景----------------------------------------------------------------------------------------------------------------------
    QGraphicsScene FirstScene; // 第一个场景 选择场景
    QGraphicsScene StartScene; // 开始场景
    QGraphicsScene PlayScene; // 比赛场景

    // 场景元素---------------------------------------------------------------------------------------------------------
    QGraphicsPixmapItem First_Item; // 第一个场景 选择场景图片
    QGraphicsPixmapItem Start_Scene;
    QGraphicsPixmapItem PlayScene_Item; // 比赛背景元素
    QGraphicsPixmapItem Start_Button; // 开始游戏按钮
    QGraphicsPixmapItem Ball; // 羽毛球

    MyNet mynet; // 羽毛球网
    Player_Right player_right;
    Player_Left player_left;

    // 定时器
    QTimer* Player_Right_Move_Timer;
    QTimer* Player_Left_Move_Timer;

    // 容器--------------------------------------------------------------------------------------------
    // 按键组合
    QList<int> mKeyList_Left;
    QList<int> mKeyList_Right;
};
#endif // WIDGET_H
