#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QDoubleValidator>
#include "draw_screen.h"

#include <iostream>

void MainWindow::create_figure()
{
    shapes_alloc(&this->figure.shapes, 10);

    this->figure.center = point_create(300, 300);

    shape_t *tmp = NULL;

    tmp = shape_create(
        ellipse_create(
            rectangle_create(
                point_create(this->figure.center->x - 50, this->figure.center->y - 50),
                point_create(this->figure.center->x + 50, this->figure.center->y - 50),
                point_create(this->figure.center->x + 50, this->figure.center->y + 50),
                point_create(this->figure.center->x - 50, this->figure.center->y + 50))));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        arc_create(
            rectangle_create(
                point_create(this->figure.center->x - 70, this->figure.center->y - 70),
                point_create(this->figure.center->x + 70, this->figure.center->y - 70),
                point_create(this->figure.center->x + 70, this->figure.center->y + 70),
                point_create(this->figure.center->x - 70, this->figure.center->y + 70)),
                45, 90
            ));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        arc_create(
            rectangle_create(
                point_create(this->figure.center->x - 90, this->figure.center->y - 90),
                point_create(this->figure.center->x + 90, this->figure.center->y - 90),
                point_create(this->figure.center->x + 90, this->figure.center->y + 90),
                point_create(this->figure.center->x - 90, this->figure.center->y + 90)),
            45, 90
            ));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        arc_create(
            rectangle_create(
                point_create(this->figure.center->x - 90, this->figure.center->y - 90),
                point_create(this->figure.center->x + 90, this->figure.center->y - 90),
                point_create(this->figure.center->x + 90, this->figure.center->y + 90),
                point_create(this->figure.center->x - 90, this->figure.center->y + 90)),
            45, 90
            ));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        ellipse_create(
            rectangle_create(
                point_create(this->figure.center->x - 10, this->figure.center->y - 110),
                point_create(this->figure.center->x + 10, this->figure.center->y - 110),
                point_create(this->figure.center->x + 10, this->figure.center->y - 90),
                point_create(this->figure.center->x - 10, this->figure.center->y - 90))));

    shapes_push(&this->figure.shapes, tmp);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pxp = QPixmap(ui->graphic_lable->width(), ui->graphic_lable->height());
    pxp.fill();
    ui->graphic_lable->setPixmap(pxp);

    connect(ui->btn_move, &QPushButton::clicked, this,
            &MainWindow::move_btn_clicked);

    connect(ui->btn_rotate, &QPushButton::clicked, this,
            &MainWindow::rotate_btn_clicked);

    connect(ui->btn_scale, &QPushButton::clicked, this,
            &MainWindow::scale_btn_clicked);

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto double_validator = new QDoubleValidator;
    double_validator->setLocale(locale);

    ui->input_dx->setValidator(double_validator);
    ui->input_dy->setValidator(double_validator);

    ui->input_cx->setValidator(double_validator);
    ui->input_cy->setValidator(double_validator);

    ui->input_kx->setValidator(double_validator);
    ui->input_ky->setValidator(double_validator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_angel->setValidator(int_validator);


    create_figure();



    draw_screen();
}

void MainWindow::draw_screen()
{
    QPainter painter(&this->pxp);
    double h = (double)painter.device()->height();
    double w = (double)painter.device()->width();
    draw_view_t view = {
        .scene = &this->pxp,
        .painter = &painter,
        .width = w,
        .height = h,
    };

    draw(&view, &this->figure);

    ui->graphic_lable->setPixmap(this->pxp);
}

void MainWindow::clear_screen()
{
    this->pxp.fill();
    draw_screen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::move_btn_clicked()
{
    bool dx_ok, dy_ok;

    double dx = ui->input_dx->text().toDouble(&dx_ok);
    double dy = ui->input_dy->text().toDouble(&dy_ok);

    if (dx_ok && dy_ok)
        this->figure = figure_move(&this->figure, point_create(dx, dy));

    clear_screen();
    draw_screen();
}

void MainWindow::rotate_btn_clicked()
{
    bool angle_ok, cx_ok, cy_ok;

    int angle = ui->input_angel->text().toInt(&angle_ok);

    double cx = ui->input_cx->text().toDouble(&cx_ok);
    double cy = ui->input_cy->text().toDouble(&cy_ok);

    if (angle_ok && cx_ok && cy_ok)
        this->figure = figure_rotate(&this->figure, point_create(cx, cy), angle);

    clear_screen();
    draw_screen();
}

void MainWindow::scale_btn_clicked()
{
    bool kx_ok, ky_ok, cx_ok, cy_ok;

    double kx = ui->input_kx->text().toDouble(&kx_ok);
    double ky = ui->input_ky->text().toDouble(&ky_ok);

    double cx = ui->input_cx->text().toDouble(&cx_ok);
    double cy = ui->input_cy->text().toDouble(&cy_ok);

    if (kx_ok && ky_ok && cx_ok && cy_ok)
        this->figure = figure_scale(&this->figure, point_create(cx, cy), point_create(kx, ky));

    clear_screen();
    draw_screen();
}
