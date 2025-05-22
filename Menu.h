#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QSlider>
#include <QSoundEffect>
#include <QLabel>

namespace Ui
{
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_Volume_sliderMoved(int position);

private:
    Ui::Menu *ui;

    QSlider *VolumeSlider;   // 音量控制滑动条对象
    QLabel *VolumeLabel;     // 显示音量文本标签
    QSoundEffect *GameMusic; // 游戏音效对象
};

#endif // MENU_H
