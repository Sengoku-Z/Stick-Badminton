#include "firstwindow.h" // 包含FirstWindow类的头文件
#include <QPushButton> // 包含QPushButton类的头文件
#include "ui_firstwindow.h" // 包含UI定义的头文件

FirstWindow::FirstWindow(QWidget *parent)
    : QMainWindow(parent) // FirstWindow类的构造函数，继承自QMainWindow
    , ui(new Ui::FirstWindow) // 创建UI对象
{
    ui->setupUi(this); // 设置UI界面
    setFixedSize(730, 500); // 设置窗口固定大小为730x500像素

    // 创建两个Movetest对象
    this->pgame = new Movetest;
    this->pgame2 = new Movetest;

    // 设置按钮normal的图标为ball1.png
    QPixmap icon1(tr("://images/images2/ball1.png"));
    ui->normal->setIcon(icon1);

    // 连接按钮normal的clicked信号到lambda表达式，处理点击事件
    connect(ui->normal, &QPushButton::clicked, [=]()
    {
        this->hide(); // 隐藏当前窗口
        this->pgame2->isnormal = true; // 设置pgame2为普通模式
        this->pgame2->vx3 = -5; // 设置pgame2的水平速度为-5
        this->pgame2->vy3 = 15; // 设置pgame2的垂直速度为15
        this->pgame2->isstart = true; // 设置pgame2为开始状态

        this->pgame2->show(); // 显示pgame2窗口
    });

    // 连接按钮pushButton_2的clicked信号到lambda表达式，处理点击事件
    connect(ui->pushButton_2, &QPushButton::clicked, [=]()
    {
        this->hide();
    });

    // 连接Movetest对象pgame的back信号到lambda表达式，处理返回事件
    connect(this->pgame, &Movetest::back, [=]()
    {
        this->pgame->hide(); // 隐藏pgame窗口
        this->show(); // 显示当前窗口
    });

    // 连接Movetest对象pgame2的back信号到lambda表达式，处理返回事件
    connect(this->pgame2, &Movetest::back, [=]()
    {
        this->pgame2->hide(); // 隐藏pgame2窗口
        this->show(); // 显示当前窗口
    });
}

FirstWindow::~FirstWindow()
{
    delete pgame; // 删除pgame对象
    delete ui; // 删除UI对象
}

void FirstWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); // 创建一个QPainter对象，并指定绘制目标为当前窗口

    painter.setPen(Qt::black); // 设置画笔颜色为黑色

    QPixmap background(":/imgs/images/Play_Item.png"); // 加载背景图片
    painter.drawPixmap(30, 0, 670, 480, background); // 在指定位置绘制背景图片

    QPixmap player("://images/images2/player1_right.png"); // 加载球员图片
    painter.drawPixmap(540, 370, 60, 80, player); // 在指定位置绘制球员图片

    QFont font2("Courier", 50); // 设置字体
    painter.setFont(font2); // 应用字体
    painter.setPen(Qt::red); // 设置画笔颜色为红色
    painter.setBrush(Qt::red); // 设置画刷颜色为红色
    painter.drawText(160, 240, "Volleyball"); // 在指定位置绘制文本
}
