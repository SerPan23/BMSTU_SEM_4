#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QColorDialog>
#include <QValidator>
#include <QColor>

#include "figure.h"
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

    QColor fill_color = QColor(193, 139, 255);
    QColor border_color = QColor(0, 0, 0);

    Figure current_figure;
    figures_t closed_figures;

    Point seed = Point(350, 350);

    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_fill_color_change_clicked();
    void btn_border_color_change_clicked();

    void remove_fiil();
    void clear_all();

    void draw_carcas();
    void update_view();

    void add_dot(int x, int y);
    void mouse_add_dot();
    void form_add_dot();

    void close_figure();
    void mouse_close_figure();
    void btn_close_figure_clicked();

    void write_figures_list();
    void add_text_line(QString str);
    void write_figure(Figure& figure);

    void btn_fill_clicked();
};
#endif // MAINWINDOW_H
