#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");


    connect(ui->btn_move, &QPushButton::clicked, this,
            &MainWindow::btn_move_clicked);

    connect(ui->btn_rotate, &QPushButton::clicked, this,
            &MainWindow::btn_rotate_clicked);

    connect(ui->btn_scale, &QPushButton::clicked, this,
            &MainWindow::btn_scale_clicked);


    connect(ui->btn_load, &QPushButton::clicked, this,
            &MainWindow::btn_load_clicked);

    connect(ui->btn_save, &QPushButton::clicked, this,
            &MainWindow::btn_save_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator *double_validator = new QDoubleValidator;
    double_validator->setLocale(locale);

    ui->input_dx->setValidator(double_validator);
    ui->input_dy->setValidator(double_validator);
    ui->input_dz->setValidator(double_validator);

    ui->input_angle_x->setValidator(double_validator);
    ui->input_angle_x->setValidator(double_validator);
    ui->input_angle_x->setValidator(double_validator);

    ui->input_kx->setValidator(double_validator);
    ui->input_kx->setValidator(double_validator);
    ui->input_kx->setValidator(double_validator);
}

MainWindow::~MainWindow()
{
    request_t request;
    request.action = QUIT;
    request_manager(request);
    delete ui;
}

void MainWindow::error_show(return_codes_t code)
{
    error_msg_t msg = get_error_msg(code);

    switch (msg.type)
    {
        case INFORMATION:
            QMessageBox::information(NULL, msg.title, msg.text);
            break;
        case CRITICAL:
            QMessageBox::critical(NULL, msg.title, msg.text);
            break;
    }
}

return_codes_t MainWindow::draw()
{
    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());

    request_t request;
    request.action = DRAW;
    request.view = {
        .scene = ui->graphicsView->scene(),
        .width =  ui->graphicsView->scene()->width(),
        .height =  ui->graphicsView->scene()->height()
    };

    return request_manager(request);
}

void MainWindow::btn_load_clicked()
{
    QString path = QFileDialog::getOpenFileName();
    request_t request;
    request.action = LOAD;

    // request.filename = path.toLocal8Bit().data();
    char buf[path.length()];
    strncpy(buf, path.toUtf8().data(), path.length());
    buf[path.length()] = '\0';
    request.filename = buf;

    return_codes_t rc = request_manager(request);
    if (rc)
        error_show(rc);
    else
    {
        rc = draw();
        if (rc)
            error_show(rc);
    }
}

void MainWindow::btn_save_clicked()
{
    QString path = QFileDialog::getSaveFileName();

    request_t request;
    request.action = SAVE;

    printf("%s\n", path.toStdString().c_str());

    char buf[path.length()];
    strncpy(buf, path.toUtf8().data(), path.length());
    buf[path.length()] = '\0';
    request.filename = buf;

    return_codes_t rc = request_manager(request);
    if (rc)
        error_show(rc);
    else
    {
        rc = draw();
        if (rc)
            error_show(rc);
    }
}

void MainWindow::btn_move_clicked()
{
    request_t request;
    request.action = MOVE;
    request.move = {
        .dx = ui->input_dx->text().toDouble(),
        .dy = ui->input_dy->text().toDouble(),
        .dz = ui->input_dz->text().toDouble()
    };

    return_codes_t rc = request_manager(request);
    if (rc)
        error_show(rc);
    else
    {
        rc = draw();
        if (rc)
            error_show(rc);
    }
}

void MainWindow::btn_rotate_clicked()
{
    request_t request;
    request.action = ROTATE;
    request.rotate = {
        .angle_x = ui->input_angle_x->text().toDouble(),
        .angle_y = ui->input_angle_y->text().toDouble(),
        .angle_z = ui->input_angle_z->text().toDouble()
    };

    return_codes_t rc = request_manager(request);
    if (rc)
        error_show(rc);
    else
    {
        rc = draw();
        if (rc)
            error_show(rc);
    }
}

void MainWindow::btn_scale_clicked()
{
    request_t request;
    request.action = SCALE;
    request.scale = {
        .kx = ui->input_kx->text().toDouble(),
        .ky = ui->input_ky->text().toDouble(),
        .kz = ui->input_kz->text().toDouble()
    };

    return_codes_t rc = request_manager(request);
    if (rc)
        error_show(rc);
    else
    {
        rc = draw();
        if (rc)
            error_show(rc);
    }
}
