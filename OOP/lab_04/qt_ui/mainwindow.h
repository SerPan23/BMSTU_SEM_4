#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "elevator.h"

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

    void onCabinBtnClicked(int btn_number);

private slots:

    void onFloorBtnClicked(int btn_number);

private:
    Ui::MainWindow *ui;
    void generateUi();

    std::vector<QPushButton *> cabinButtons;
    std::vector<QPushButton *> floorButtons;

    Elevator elevator;

};
#endif // MAINWINDOW_H
