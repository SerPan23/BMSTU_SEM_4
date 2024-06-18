#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QColorDialog>
#include <QValidator>
#include <QColor>
#include <QPlainTextEdit>

#include <memory>

#include "drawer.h"
#include "funcs.h"
#include "funcs_list.h"

#include "algorithm.h"

#define EPS 1e-8

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

    std::shared_ptr<Drawer> drawer;
    std::shared_ptr<Funcs> funcs;
    Funcs::func_ptr current_func{nullptr};
    SurfaceData current_surface{};
    bool smt_draw = false;

    std::shared_ptr<TransformData> transformData = std::make_shared<TransformData>();

    QColor surface_color = QColor(0, 0, 0);


    void show_err_msg(QString);
    void set_preview_widget_color(QWidget *widget, QColor color);

    void btn_surface_color_change_clicked();

    void surface_choosed();
    void surfaces_load();

    void clear_clicked();
    void draw();
    void draw_clicked();

    void x_rotate_clicked();
    void y_rotate_clicked();
    void z_rotate_clicked();

    void reset_angles_clicked();

    void scale_change_clicked();

};
#endif // MAINWINDOW_H
