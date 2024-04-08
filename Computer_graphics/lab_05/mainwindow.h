#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QColorDialog>
#include <QValidator>

#include "mygraphicsscene.h"

#include <vector>

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
    Ui::MainWindow *ui;
    QPixmap pxp;

    QColor fill_color = Qt::black;

    Figure current_figure;
    std::vector<Figure> closed_figures;

    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_fill_color_change_clicked();

    void clear_screen();

    void add_dot(int x, int y);
    void mouse_add_dot();
    void form_add_dot();

    void close_figure();
    void mouse_close_figure();
    void btn_close_figure_clicked();

    void write_figures_list();
    void add_text_line(QString str);
    void write_figure(Figure& figure);

};
#endif // MAINWINDOW_H
