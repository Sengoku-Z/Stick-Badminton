#ifndef REGIS_H
#define REGIS_H

#include <QWidget>

namespace Ui
{
class Regis;
}

class Regis : public QWidget
{
    Q_OBJECT

public:
    explicit Regis(QWidget *parent = nullptr);
    ~Regis();

private slots:
    // 点击确定
    void on_pushButton_clicked();

    // 退出按钮
    void on_Btn_Quit_clicked();

    // 链接数据库
    void initializeDatabase();

private:
    Ui::Regis *ui;
};

#endif // REGIS_H
