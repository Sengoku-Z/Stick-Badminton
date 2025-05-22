#include "Regis.h"
#include "ui_Regis.h"
#include "Inlog.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QDir>

Regis::Regis(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Regis)
{
    ui->setupUi(this);

    // 在构造函数或其他地方添加这段代码
    qDebug() << "Database file path:" << QDir::currentPath() + "/user.db";


    this->setWindowTitle("用户注册");
    ui->Let_Passward_1->setEchoMode(QLineEdit::Password); // 开始时密文显示
    ui->Let_Passward_2->setEchoMode(QLineEdit::Password); // 开始时密文显示
    ui->Let_Passward_1->setMaxLength(6); // 密码最大长度不能超过6
    ui->Let_Passward_2->setMaxLength(6); // 密码最大长度不能超过6

    initializeDatabase();
}

Regis::~Regis()
{
    delete ui;
}

void Regis::initializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::currentPath() + "/user.db");

    if (!db.open())
    {
        qDebug() << "Database connection failed";
        QMessageBox::critical(this, "错误", "无法连接到数据库");
    }
    else
    {
        // 创建 user 表（如果不存在）
        QSqlQuery query;
        QString createTable = "CREATE TABLE IF NOT EXISTS user ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "username TEXT NOT NULL, "
                              "password TEXT NOT NULL)";
        if (!query.exec(createTable))
        {
            qDebug() << "Failed to create table: " << query.lastError();
        }
        else
        {
            qDebug() << "Table created or already exists";
        }
    }
}

// 注册按钮，注册完成跳转到登录界面
void Regis::on_pushButton_clicked()
{
    QString username = ui->Let_Name->text();
    QString passward1 = ui->Let_Passward_1->text();
    QString passward2 = ui->Let_Passward_2->text();

    if (username.isEmpty() || passward1.isEmpty() || passward2.isEmpty())
    {
        QMessageBox::about(this, "错误", "所有字段都必须填写");
        return;
    }

    if (passward1 != passward2)
    {
        QMessageBox::about(this, "错误", "两次密码输入不同");
        return;
    }

    if (passward1.length() < 6)
    {
        QMessageBox::about(this, "错误", "密码长度必须为6个字符");
        return;
    }

    // 检查用户名是否已存在
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec())
    {
        qDebug() << "Failed to execute query: " << query.lastError();
        QMessageBox::critical(this, "错误", "查询失败，请重试");
        return;
    }

    if (query.next())
    {
        QMessageBox::about(this, "错误", "用户名已存在");
        return;
    }

    // 插入新用户
    query.prepare("INSERT INTO user (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", passward1);

    if (!query.exec())
    {
        qDebug() << "Failed to insert new user: " << query.lastError();
        QMessageBox::critical(this, "错误", "注册失败，请重试");
        return;
    }

    QMessageBox::about(this, "成功", "注册成功");
    InLog *w = new InLog();
    w->show();
    this->hide();
}

// 退出按钮，跳转到登录界面
void Regis::on_Btn_Quit_clicked()
{
    InLog *w = new InLog();
    w->show();
    this->hide();
}
