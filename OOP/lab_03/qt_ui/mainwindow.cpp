#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "BaseException.h"
#include "DrawManagerCreator.h"
#include "DrawerSolution.h"

#include <filesystem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupScene(this);

    connects();

    meta = std::make_shared<MetaData>();

    logic = std::make_shared<Logic>(meta);

    btnNewCameraClicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupScene(QWidget *parent)
{
    qDebug() << "Current path is " << std::filesystem::current_path().c_str() << '\n'; // (1)

    ui->graphicsView->setFrameShape(QFrame::NoFrame);


    int screenWidth = ui->graphicsView->width();
    int screenHeight = ui->graphicsView->height();
    scene = std::make_shared<QGraphicsScene>(0, 0, screenWidth, screenHeight, parent);

    scene->addRect(scene->sceneRect());

    ui->graphicsView->setScene(scene.get());
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");



    std::shared_ptr<BaseDrawer> drawer = DrawerSolution::create(DrawerType::QtDrawer, scene);

    auto drawManager = DrawManagerCreator().get();
    drawManager->setDrawer(drawer);
    drawManager->drawScene();


    // --------
    // auto loadManager = ManagerSolution::getLoadManager();
    // loadManager->loadMeshModel("/Users/serp/development/projects/BMSTU_SEM_4/OOP/lab_03/data/cube_45.ves");
    // loadManager->loadMeshModel("/Users/serp/development/projects/BMSTU_SEM_4/OOP/lab_03/data/cube.ves");

    // auto cameraManager = ManagerSolution::getCameraManager();
    // int camId = cameraManager->newCamera();
    // cameraManager->setActiveCamera(camId);

    // drawManager->drawScene();
}
void MainWindow::connects()
{
    connect(ui->btn_move, &QPushButton::clicked, this,
            &MainWindow::btnMoveClicked);
    connect(ui->btn_move_all, &QPushButton::clicked, this,
            &MainWindow::btnMoveAllClicked);

    connect(ui->btn_rotate, &QPushButton::clicked, this,
            &MainWindow::btnRotateClicked);
    connect(ui->btn_rotate_all, &QPushButton::clicked, this,
            &MainWindow::btnRotateAllClicked);

    connect(ui->btn_scale, &QPushButton::clicked, this,
            &MainWindow::btnScaleClicked);
    connect(ui->btn_scale_all, &QPushButton::clicked, this,
            &MainWindow::btnScaleAllClicked);

    connect(ui->btn_new_camera, &QPushButton::clicked, this,
            &MainWindow::btnNewCameraClicked);
    connect(ui->btn_delete_camera, &QPushButton::clicked, this,
            &MainWindow::btnDeleteCameraClicked);

    connect(ui->btn_spin_left, &QPushButton::clicked, this,
            &MainWindow::cameraSpinLeft);
    connect(ui->btn_spin_right, &QPushButton::clicked, this,
            &MainWindow::cameraSpinRight);
    connect(ui->btn_spin_down, &QPushButton::clicked, this,
            &MainWindow::cameraSpinDown);
    connect(ui->btn_spin_up, &QPushButton::clicked, this,
            &MainWindow::cameraSpinUp);

    connect(ui->btn_left, &QPushButton::clicked, this,
            &MainWindow::cameraMoveLeft);
    connect(ui->btn_right, &QPushButton::clicked, this,
            &MainWindow::cameraMoveRight);
    connect(ui->btn_down, &QPushButton::clicked, this,
            &MainWindow::cameraMoveDown);
    connect(ui->btn_up, &QPushButton::clicked, this,
            &MainWindow::cameraMoveUp);

    connect(ui->btn_delete_model, &QPushButton::clicked, this,
            &MainWindow::btnDeleteModelClicked);
    connect(ui->btn_delete_all_model, &QPushButton::clicked, this,
            &MainWindow::btnDeleteAllModelClicked);

    connect(ui->btn_load_model, &QPushButton::clicked, this,
            &MainWindow::btnLoadModelClicked);


    connect(ui->cameraCB, &QComboBox::currentIndexChanged, this,
            &MainWindow::choosedCamera);
    connect(ui->modelCB, &QComboBox::currentIndexChanged, this,
            &MainWindow::choosedModel);

    connect(ui->btn_undo_all, &QPushButton::clicked, this,
            &MainWindow::btnUndoAllClicked);
    connect(ui->btn_undo, &QPushButton::clicked, this,
            &MainWindow::btnUndoClicked);

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto doubleValidator = new QDoubleValidator;
    doubleValidator->setLocale(locale);

    ui->input_dx->setValidator(doubleValidator);
    ui->input_dy->setValidator(doubleValidator);
    ui->input_dz->setValidator(doubleValidator);

    ui->input_angle_x->setValidator(doubleValidator);
    ui->input_angle_y->setValidator(doubleValidator);
    ui->input_angle_z->setValidator(doubleValidator);

    ui->input_kx->setValidator(doubleValidator);
    ui->input_ky->setValidator(doubleValidator);
    ui->input_kz->setValidator(doubleValidator);
}

void MainWindow::showError(QString str)
{
    QMessageBox::critical(nullptr, "Ошибка", str);
}

void MainWindow::btnMoveClicked()
{
    bool dx_ok, dy_ok, dz_ok;
    float dx, dy, dz;

    dx = ui->input_dx->text().toDouble(&dx_ok);
    dy = ui->input_dy->text().toDouble(&dy_ok);
    dz = ui->input_dz->text().toDouble(&dz_ok);

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
    float dx, dy, dz;

    dx = ui->input_dx->text().toDouble(&dx_ok);
    dy = ui->input_dy->text().toDouble(&dy_ok);
    dz = ui->input_dz->text().toDouble(&dz_ok);

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
    float ax, ay, az;

    ax = ui->input_angle_x->text().toDouble(&ax_ok);
    ay = ui->input_angle_y->text().toDouble(&ay_ok);
    az = ui->input_angle_z->text().toDouble(&az_ok);

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
    float ax, ay, az;

    ax = ui->input_angle_x->text().toDouble(&ax_ok);
    ay = ui->input_angle_y->text().toDouble(&ay_ok);
    az = ui->input_angle_z->text().toDouble(&az_ok);

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
    float kx, ky, kz;

    kx = ui->input_kx->text().toDouble(&kx_ok);
    ky = ui->input_ky->text().toDouble(&ky_ok);
    kz = ui->input_kz->text().toDouble(&kz_ok);

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
    float kx, ky, kz;

    kx = ui->input_kx->text().toDouble(&kx_ok);
    ky = ui->input_ky->text().toDouble(&ky_ok);
    kz = ui->input_kz->text().toDouble(&kz_ok);

    if (!kx_ok || !ky_ok || !kz_ok)
    {
        showError("kx, ky or kz has wrong value!");
        return;
    }

    logic->scaleAllObject(kx, ky, kz);
}

void MainWindow::btnNewCameraClicked()
{
    int cameraId = logic->newCamera();

    QString cameraName = QString("Camera ") + QString::number(cameraId);

    ui->cameraCB->addItem(cameraName, cameraId);
    ui->cameraCB->setCurrentIndex(ui->cameraCB->count() - 1);
}

void MainWindow::btnDeleteCameraClicked()
{
    if (ui->cameraCB->count() == 1)
    {
        showError("Не возможно удалить камеру, так как она единственная!");
        return;
    }

    logic->deleteCamera(ui->cameraCB->currentData().toInt());

    ui->cameraCB->removeItem(ui->cameraCB->currentIndex());

    logic->setActiveCamera(ui->cameraCB->currentData().toInt());

    logic->draw();
}

void MainWindow::choosedCamera()
{
    int cameraId = 0;
    cameraId = ui->cameraCB->currentData().toInt();

    logic->setActiveCamera(cameraId);
}

void MainWindow::cameraMoveUp()
{
    logic->moveCamera(meta->getActiveCamera(), 0, -10, 0);
}

void MainWindow::cameraMoveDown()
{
    logic->moveCamera(meta->getActiveCamera(), 0, 10, 0);
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
    logic->rotateCamera(meta->getActiveCamera(), 10, 0);
}

void MainWindow::cameraSpinRight()
{
    logic->rotateCamera(meta->getActiveCamera(), -10, 0);
}

void MainWindow::btnLoadModelClicked()
{
    auto path = QFileDialog::getOpenFileName(nullptr,
                                             "Загрузка модели",
                                             "../../../../data",
                                             "Text files (*.ves *.adls)");

    if (path.isNull())
        return;

    int objectId = -1;

    try
    {
        qDebug() << path.toStdString();
        objectId = logic->loadObject(path.toStdString());
        qDebug() << "Loaded: " << objectId;
    }
    catch (const BaseException &error)
    {
        showError("Ошибка при загрузке файла!");
        return;
    }


    auto fileName = QFileInfo(path.toUtf8().data()).fileName();
    QString figName = QString("MeshModel (") + QString::number(objectId)
                      + QString(") load from ") + QString(fileName);


    ui->modelCB->addItem(figName, objectId);
    ui->modelCB->setCurrentIndex(ui->modelCB->count() - 1);

    logic->draw();
}

void MainWindow::btnDeleteModelClicked()
{
    if (ui->modelCB->count() == 0)
    {
        showError("Список объектов пуст, удалять нечего!");
        return;
    }

    logic->deleteObject(ui->modelCB->currentData().toInt());

    ui->modelCB->removeItem(ui->modelCB->currentIndex());

    meta->setObject(ui->modelCB->currentData().toInt());

    logic->draw();
}

void MainWindow::btnDeleteAllModelClicked()
{
    if (ui->modelCB->count() == 0)
    {
        showError("Список объектов пуст, удалять нечего!");
        return;
    }

    logic->deleteAllObject();

    ui->modelCB->clear();

    logic->draw();
}

void MainWindow::choosedModel()
{
    int objectId = 0;

    // qDebug() << ui->modelCB->currentIndex() << ui->modelCB->currentData();
    objectId = ui->modelCB->currentData().toInt();

    meta->setObject(objectId);
}

void MainWindow::btnUndoAllClicked()
{
    if (ui->modelCB->count() == 0)
    {
        showError("Список объектов пуст!");
        return;
    }

    logic->restoreAllState();
}

void MainWindow::btnUndoClicked()
{
    if (ui->modelCB->count() == 0)
    {
        showError("Список объектов пуст!");
        return;
    }

    logic->restoreState(ui->modelCB->currentData().toInt());
}
