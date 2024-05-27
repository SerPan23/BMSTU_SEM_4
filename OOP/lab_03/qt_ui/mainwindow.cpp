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
