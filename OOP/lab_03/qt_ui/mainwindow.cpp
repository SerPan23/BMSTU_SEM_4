#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "DrawManager.h"
#include "DrawManagerCreator.h"
#include "DrawerSolution.h"

#include "ManagerSolution.h"

#include <filesystem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Current path is " << std::filesystem::current_path().c_str() << '\n'; // (1)

    int screen_width = ui->graphicsView->width();
    int screen_height = ui->graphicsView->height();
    scene = std::make_shared<QGraphicsScene>(0, 0, screen_width - 2, screen_height - 2, parent);
    scene->addRect(scene->sceneRect());
    ui->graphicsView->setScene(scene.get());
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");


    std::shared_ptr<BaseDrawer> drawer = DrawerSolution::create(DrawerType::QtDrawer, scene);

    auto drawManager = DrawManagerCreator().get();
    drawManager->setDrawer(drawer);

    auto loadManager = ManagerSolution::getLoadManager();
    loadManager->loadMeshModel("/Users/serp/development/projects/BMSTU_SEM_4/OOP/lab_03/data/cube_45.ves");
    loadManager->loadMeshModel("/Users/serp/development/projects/BMSTU_SEM_4/OOP/lab_03/data/cube.ves");

    auto cameraManager = ManagerSolution::getCameraManager();
    int camId = cameraManager->newCamera();
    cameraManager->setActiveCamera(camId);

    drawManager->drawScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showError(QString str)
{

}

void MainWindow::btnMoveClicked()
{
    bool dx_ok, dy_ok, dz_ok;
    int dx, dy, dz;

    dx = ui->input_dx->text().toInt(&dx_ok);
    dy = ui->input_dy->text().toInt(&dy_ok);
    dz = ui->input_dz->text().toInt(&dz_ok);

    if (!dx_ok || !dy_ok || !dz_ok)
    {
        showError("dx, dy or dz has wrong value!");
        return;
    }

    logic->moveObject(meta->getSelectedObject(), dx, dy, dz);
}

void MainWindow::btnMoveAllClicked()
{
    bool dx_ok, dy_ok, dz_ok;
    int dx, dy, dz;

    dx = ui->input_dx->text().toInt(&dx_ok);
    dy = ui->input_dy->text().toInt(&dy_ok);
    dz = ui->input_dz->text().toInt(&dz_ok);

    if (!dx_ok || !dy_ok || !dz_ok)
    {
        showError("dx, dy or dz has wrong value!");
        return;
    }

    logic->moveAllObject(dx, dy, dz);
}

void MainWindow::btnRotateClicked()
{
    bool ax_ok, ay_ok, az_ok;
    int ax, ay, az;

    ax = ui->input_kx->text().toInt(&ax_ok);
    ay = ui->input_ky->text().toInt(&ay_ok);
    az = ui->input_kz->text().toInt(&az_ok);

    if (!ax_ok || !ay_ok || !az_ok)
    {
        showError("angle by x, y or z has wrong value!");
        return;
    }

    logic->rotateObject(meta->getSelectedObject(), ax, ay, az);
}

void MainWindow::btnRotateAllClicked()
{
    bool ax_ok, ay_ok, az_ok;
    int ax, ay, az;

    ax = ui->input_kx->text().toInt(&ax_ok);
    ay = ui->input_ky->text().toInt(&ay_ok);
    az = ui->input_kz->text().toInt(&az_ok);

    if (!ax_ok || !ay_ok || !az_ok)
    {
        showError("angle by x, y or z has wrong value!");
        return;
    }

    logic->rotateAllObject(ax, ay, az);
}

void MainWindow::btnScaleClicked()
{
    bool kx_ok, ky_ok, kz_ok;
    int kx, ky, kz;

    kx = ui->input_kx->text().toInt(&kx_ok);
    ky = ui->input_ky->text().toInt(&ky_ok);
    kz = ui->input_kz->text().toInt(&kz_ok);

    if (!kx_ok || !ky_ok || !kz_ok)
    {
        showError("kx, ky or kz has wrong value!");
        return;
    }

    logic->scaleObject(meta->getSelectedObject(), kx, ky, kz);
}

void MainWindow::btnScaleAllClicked()
{
    bool kx_ok, ky_ok, kz_ok;
    int kx, ky, kz;

    kx = ui->input_kx->text().toInt(&kx_ok);
    ky = ui->input_ky->text().toInt(&ky_ok);
    kz = ui->input_kz->text().toInt(&kz_ok);

    if (!kx_ok || !ky_ok || !kz_ok)
    {
        showError("kx, ky or kz has wrong value!");
        return;
    }

    logic->scaleAllObject(kx, ky, kz);
}

void MainWindow::btnNewCameraClicked()
{
    logic->newCamera();
}

void MainWindow::btnDeleteCameraClicked()
{
    logic->deleteCamera(meta->getActiveCamera());
}

void MainWindow::choosedCamera()
{
    int cameraId = 0;
    //TODO: add choose
    meta->setCamera(cameraId);
}

void MainWindow::cameraMoveUp()
{
    logic->moveCamera(meta->getActiveCamera(), 0, 10, 0);
}

void MainWindow::cameraMoveDown()
{
    logic->moveCamera(meta->getActiveCamera(), 0, -10, 0);
}

void MainWindow::cameraMoveLeft()
{
    logic->moveCamera(meta->getActiveCamera(), -10, 0, 0);
}

void MainWindow::cameraMoveRight()
{
    logic->moveCamera(meta->getActiveCamera(), 10, 0, 0);
}

void MainWindow::cameraSpinUp()
{
    logic->rotateCamera(meta->getActiveCamera(), 0, 10);
}

void MainWindow::cameraSpinDown()
{
    logic->rotateCamera(meta->getActiveCamera(), 0, -10);
}

void MainWindow::cameraSpinLeft()
{
    logic->rotateCamera(meta->getActiveCamera(), -10, 0);
}

void MainWindow::cameraSpinRight()
{
    logic->rotateCamera(meta->getActiveCamera(), 10, 0);
}

void MainWindow::btnLoadModelClicked()
{
    std::string path;
    //TODO: ADD path collector
    logic->loadObject(path);
    logic->draw();
}

void MainWindow::btnDeleteModelClicked()
{
    logic->deleteObject(meta->getSelectedObject());
    logic->draw();
}

void MainWindow::btnDeleteAllModelClicked()
{
    logic->deleteAllObject();
    logic->draw();
}

void MainWindow::choosedModel()
{
    int objectId = 0;
    //TODO: add choose
    meta->setObject(objectId);
}
