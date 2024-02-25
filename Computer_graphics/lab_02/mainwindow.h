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
    void move_to_center_clicked();

    void set_center_label();

    void set_prev_figure();
    void get_prev_figure();
    void get_prev_clicked();
    void reset_figure_clicked();


private:
    Ui::MainWindow *ui;
    QPixmap pxp;
    figure_t figure;
    bool is_prev;
    figure_t prev_figure;

};
#endif // MAINWINDOW_H
