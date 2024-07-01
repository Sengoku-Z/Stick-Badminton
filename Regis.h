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
    void on_pushButton_clicked();

    void on_Btn_Quit_clicked();

    void initializeDatabase();  // 确保在类中声明这个函数

private:
    Ui::Regis *ui;
};

#endif // REGIS_H
