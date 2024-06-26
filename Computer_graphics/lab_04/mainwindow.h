#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColorDialog>

#include <QtCharts>


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


    void btn_circles_draw_spectrum_clicked();
    void btn_ellipses_draw_spectrum_clicked();

    void create_series_circle(QLineSeries *series, long &max_el, QColor color, QString name, figure_t (*alg)(point_t center, int radius));
    void create_series_ellipse(QLineSeries *series, long &max_el, QColor color, QString name, figure_t (*alg)(point_t center, point_t radius));


    void btn_time_cmp_circles_clicked();
    void btn_time_cmp_ellipses_clicked();


    void go_to_main_page();
};
#endif // MAINWINDOW_H
