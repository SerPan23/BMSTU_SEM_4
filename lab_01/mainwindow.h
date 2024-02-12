#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "return_codes.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void get_result_clicked();
    void show_task();
    void add_point();
    void del_point();
    void del_all_points();

private slots:
    return_codes_t draw();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
