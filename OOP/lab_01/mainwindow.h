#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "return_codes.h"
#include "request.h"
#include <QFileDialog>
#include <QDoubleValidator>

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
    void btn_load_clicked();

    void btn_save_clicked();

    return_codes_t draw();

    void btn_move_clicked();

    void btn_rotate_clicked();

    void btn_scale_clicked();

    void error_show(return_codes_t code);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
