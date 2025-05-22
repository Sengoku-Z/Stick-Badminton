#include "Inlog.h"
#include "ui_Inlog.h"
#include "Widget.h"
#include "Regis.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase> // 执行sql语句
#include <QSqlQuery> // 数据库驱动

#pragma execution_character_set("utf-8")// 设置中文 = =

// 创建数据库
// 遍历数据库
// 增删改查

InLog::InLog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InLog)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");
    ui->Let_Passward->setEchoMode(QLineEdit::Password); // 开始时密文显示
    ui->Let_Passward->setMaxLength(6); // 密码最大长度不能超过6
    ui->Let_Passward->setPlaceholderText("请输入6位字符");

    // 创建数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("user.db");
    if (!db.open())
    {
        qDebug() << "Database connection failed";
        QMessageBox::critical(this, "错误", "无法连接到数据库");
    }
}



InLog::~InLog()
{
    delete ui;
}

// 登录按钮，跳转到主页面
void InLog::on_Btn_In_clicked()
{
    QString username = ui->Let_Name->text();
    QString passward = ui->Let_Passward->text();
    if(passward.length() < 6)
    {
        QMessageBox::about(this, "错误", "字符个数不符");
        return;
    }
    // 查询数据库
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", passward);
    query.exec();

    if (!query.next())
    {
        qDebug() << "Login error";
        QMessageBox::information(this, "登录认证", "登录失败:账户或密码错误");
    }
    else
    {
        qDebug() << "Login success";
        QMessageBox::information(this, "登录认证", "登录成功");

        // 登录成功后跳转到主页面
        Widget *w = new Widget();
        w->show();
        this->hide();
    }
}

// 注册按钮，跳转到注册界面
void InLog::on_Btn_Regis_clicked()
{
    Regis *w = new Regis();
    w->show();
    this->hide();
}

// 退出
void InLog::on_Btn_Quit_clicked()
{
    this->close();
}

// 显示密码
void InLog::on_checkBox_clicked(bool checked) // bool型
{
    if(checked)
    {
        // 显示  Normal, NoEcho, Password, PasswordEchoOnEdit
        ui->Let_Passward->setEchoMode(QLineEdit::Normal);// 密码的回响模式
    }
    else
    {
        // 密
        ui->Let_Passward->setEchoMode(QLineEdit::NoEcho);
    }
}

