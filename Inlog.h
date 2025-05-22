#ifndef INLOG_H
#define INLOG_H

#include <QWidget>

namespace Ui
{
class InLog;
}

class InLog : public QWidget
{
    Q_OBJECT

public:
    explicit InLog(QWidget *parent = nullptr);
    ~InLog();

private slots:
    // 注册按钮的实现
    void on_Btn_Regis_clicked();

    // 退出按钮的实现
    void on_Btn_Quit_clicked();

    // 登录按钮的实现
    void on_Btn_In_clicked();

    // 显示密码
    void on_checkBox_clicked(bool checked);

private:
    Ui::InLog *ui;
};

#endif // INLOG_H
