#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "movetest.h"

namespace Ui
{
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();
    void paintEvent(QPaintEvent *event) override;

    Movetest *pgame;
    Movetest *pgame2;

private:
    Ui::FirstWindow *ui;
};

#endif // FIRSTWINDOW_H
