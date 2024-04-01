#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColorDialog>

#include "point.h"
#include "draw.h"

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

    QColor bg_color = Qt::white;
    QColor line_color = Qt::black;

    QPointF scale_center;

    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_bg_color_change_clicked();
    void btn_line_color_change_clicked();

    void clear_screen();
    void draw();
    void slider_scale_changed();


    void btn_circle_draw_clicked();
    void btn_ellipse_draw_clicked();

    // void btn_draw_line_spectrum_clicked();


    void go_to_main_page();
    void btn_time_cmp_clicked();
};
#endif // MAINWINDOW_H
