#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QColorDialog>
#include <QValidator>
#include <QColor>

#include "drawer.h"
#include "algorithm.h"

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
    Ui::MainWindow *ui;

    Drawer *drawer;

    line_t cur_line;
    bool cur_line_start = false;

    lines_t lines;

    rect_t cut_rect;
    bool cut_rect_start = false;
    bool is_cut_rect_set = false;

    QColor line_color = QColor(0, 0, 255);
    QColor rect_color = QColor(0, 0, 0);
    QColor result_color = QColor(255, 0, 0);


    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_line_color_change_clicked();
    void btn_rect_color_change_clicked();
    void btn_result_color_change_clicked();

    void clear_clicked();

    void draw();
    void update_view();

    void add_line(int x_s, int y_s, int x_e, int y_e);
    void mouse_add_line();
    void form_add_line();

    void add_rect(int x_s, int y_s, int x_e, int y_e);
    void mouse_add_rect();
    void form_add_rect();

    void btn_cut_clicked();

};
#endif // MAINWINDOW_H
