#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "figure.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void draw_screen();
    void clear_screen();
    void create_figure();

    void move_btn_clicked();
    void rotate_btn_clicked();
    void scale_btn_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap pxp;
    figure_t figure;

};
#endif // MAINWINDOW_H
