#include "Widget.h"
#include "Inlog.h"
#include <QApplication>
#include "Inlog.h"
#include "Regis.h"

// 2748
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w; 原先是这样，直接显示主界面，现在我们把它换成登录界面
    InLog w;
    w.show();
    return a.exec();
}

// 不要把东西写死，可以随时改，那种，或者添加别的可以直接调用
// 切换视图 视图是可以隐藏的(这个看看应该可以做)
// 自己写的类效果更好一些，功能更多一些
// 组合按键，必须实现的
// lamada表达式
// 人物碰撞的判定，不能出去
// 羽毛球类可以看看那个buttle类 它的位置(一开始得再人手上) 它的图片，它的类型，属于左面的还是右面的
// 图片的循环播放
// MySQL的注册登录管理系统
// 对象池??(容器)就是完成之后，放入对象池中，等用的时候，从对象池中拿，这样能大大利用
// 可以设置一个菜单，菜单里有退出什么的，音量和音效的设置，对于背景音乐和打球音效
