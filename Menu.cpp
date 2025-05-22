#include "Menu.h" // 包含Menu类的头文件
#include "ui_Menu.h"
#include <QVBoxLayout> // 包含布局管理器QVBoxLayout的头文件
#include <QToolButton> // 包含工具按钮QToolButton的头文件
#include <QStyle> // 包含Qt样式相关的头文件

Menu::Menu(QWidget *parent) : QWidget(parent)
{
    // 创建音量控制滑动条对象
    VolumeSlider = new QSlider(Qt::Horizontal, this);
    VolumeSlider->setRange(0, 100);  // 设置范围
    VolumeSlider->setValue(50);      // 设置默认值
    connect(VolumeSlider, &QSlider::sliderMoved, this, &Menu::on_Volume_sliderMoved);

    // 创建显示音量文本标签
    VolumeLabel = new QLabel("50%", this);
    VolumeLabel->setAlignment(Qt::AlignCenter); // 设置文本居中对齐

    // 创建垂直布局管理器
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(VolumeSlider); // 将音量控制滑动条添加到布局中
    layout->addWidget(VolumeLabel); // 将音量文本标签添加到布局中
    setLayout(layout); // 设置窗口的布局为垂直布局

    // 创建游戏音效对象
    GameMusic = new QSoundEffect(this);
    GameMusic->setSource(QUrl::fromLocalFile(":/music/music/gamemusic.wav")); // 设置音效文件路径
    GameMusic->setLoopCount(QSoundEffect::Infinite); // 设置循环播放
    GameMusic->play(); // 播放音效
}

Menu::~Menu()
{
    delete ui; // 删除UI对象，如果有的话
}

void Menu::on_Volume_sliderMoved(int position)
{
    qreal volume = position / 100.0; // 计算音量（0.0到1.0之间）
    GameMusic->setVolume(volume); // 设置音效的音量
    VolumeLabel->setText(QString("%1%").arg(position)); // 更新音量文本标签显示
}
