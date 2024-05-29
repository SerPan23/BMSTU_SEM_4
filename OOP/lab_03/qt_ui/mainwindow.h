#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include <QFileDialog>
#include <QMessageBox>

#include "Logic.h"

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
    std::shared_ptr<QGraphicsScene> scene;

    std::shared_ptr<Logic> logic;
    std::shared_ptr<MetaData> meta;

    void setupScene(QWidget *parent);
    void connects();
    void showError(QString str);

    void btnMoveClicked();
    void btnMoveAllClicked();

    void btnRotateClicked();
    void btnRotateAllClicked();

    void btnScaleClicked();
    void btnScaleAllClicked();

    void btnNewCameraClicked();
    void btnDeleteCameraClicked();
    void choosedCamera();

    void cameraMoveUp();
    void cameraMoveDown();
    void cameraMoveLeft();
    void cameraMoveRight();

    void cameraSpinUp();
    void cameraSpinDown();
    void cameraSpinLeft();
    void cameraSpinRight();

    void btnLoadModelClicked();
    void btnDeleteModelClicked();
    void btnDeleteAllModelClicked();
    void choosedModel();

    void btnUndoAllClicked();
    void btnUndoClicked();

};
#endif // MAINWINDOW_H
