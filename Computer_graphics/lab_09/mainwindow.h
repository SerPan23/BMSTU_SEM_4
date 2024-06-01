#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QColorDialog>
#include <QValidator>
#include <QColor>
#include <QPlainTextEdit>

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

    polygon_t figure;
    polygon_t clip;

    QColor figure_color = QColor(0, 0, 255);
    QColor clip_color = QColor(0, 0, 0);
    QColor result_color = QColor(255, 0, 0);


    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_figure_color_change_clicked();
    void btn_clip_color_change_clicked();
    void btn_result_color_change_clicked();

    void clear_clicked();

    void draw();
    void update_view();

    void add_figure_vertex(int x, int y);
    void mouse_add_figure_vertex();
    void form_add_figure_vertex();
    void close_figure();
    void mouse_close_figure();
    void btn_close_figure_clicked();

    void add_parallel_lines();

    void add_clip_vertex(int x, int y);
    void mouse_add_clip_vertex();
    void form_add_clip_vertex();
    void close_clip();
    void mouse_close_clip();
    void btn_close_clip_clicked();

    void add_text_line(QString str, QPlainTextEdit *textedit);
    void write_points(polygon_t& polygon, QPlainTextEdit *textedit);


    void btn_cut_clicked();
};
#endif // MAINWINDOW_H
