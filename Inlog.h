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
    void on_Btn_Regis_clicked();

    void on_Btn_Quit_clicked();

    void on_Btn_In_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::InLog *ui;
};

#endif // INLOG_H
