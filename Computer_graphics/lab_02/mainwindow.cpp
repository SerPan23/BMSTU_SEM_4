#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QDoubleValidator>
#include "draw_screen.h"
#include <QMessageBox>

void MainWindow::create_figure()
{
    shapes_alloc(&this->figure.shapes, 10);

    point_t *circles_center = point_create(400, 350);
    double cir_1_r = 50;
    double cir_2_r = 10;

    double arc_1_r_x = 70, arc_1_r_y = 60;
    double arc_2_r_x = 80, arc_2_r_y = 70;
    int arc_angle_start = 45, arc_angle_span = 90;

    double legs_x = 10, legs_y = 20;
    double dash_len = 10;
    double minute_hand_len = 25, hour_hand_len = 15;

    shape_t *tmp = NULL;

    tmp = shape_create(
        ellipse_create(point_create(circles_center->x, circles_center->y), cir_1_r, cir_1_r));

    shapes_push(&this->figure.shapes, tmp);


    tmp = shape_create(
        ellipse_create(point_create(circles_center->x,
                                    circles_center->y - arc_2_r_y - cir_2_r),
                       cir_2_r, cir_2_r));

    shapes_push(&this->figure.shapes, tmp);


    tmp = shape_create(
        arc_create(
                point_create(circles_center->x, circles_center->y),
                arc_1_r_x, arc_1_r_y,
                arc_angle_start, arc_angle_span
            ));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        arc_create(
            point_create(circles_center->x, circles_center->y),
            arc_2_r_x, arc_2_r_y,
            arc_angle_start, arc_angle_span
            ));

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        line_create(
            get_arc_point(circles_center, arc_1_r_x, arc_1_r_y, to_rad(arc_angle_start) + M_PI),
            get_arc_point(circles_center, arc_2_r_x, arc_2_r_y, to_rad(arc_angle_start) + M_PI)
            )
        );

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        line_create(
            get_arc_point(circles_center, arc_1_r_x, arc_1_r_y,
                          to_rad(arc_angle_start + arc_angle_span) + M_PI),
            get_arc_point(circles_center, arc_2_r_x, arc_2_r_y,
                          to_rad(arc_angle_start + arc_angle_span) + M_PI)
            )
        );

    shapes_push(&this->figure.shapes, tmp);

    point_t *t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                                   to_rad(45));

    tmp = shape_create(
        line_create(t, point_create(t->x + legs_x, t->y + legs_y))
        );

    shapes_push(&this->figure.shapes, tmp);

    t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                                   to_rad(135));

    tmp = shape_create(
        line_create(t, point_create(t->x - legs_x, t->y + legs_y))
        );

    shapes_push(&this->figure.shapes, tmp);

    t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                          to_rad(0));

    tmp = shape_create(
        line_create(t, point_create(t->x - dash_len, t->y))
        );

    shapes_push(&this->figure.shapes, tmp);

    t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                          to_rad(90));

    tmp = shape_create(
        line_create(t, point_create(t->x, t->y - dash_len))
        );

    shapes_push(&this->figure.shapes, tmp);

    t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                          to_rad(180));

    tmp = shape_create(
        line_create(t, point_create(t->x + dash_len, t->y))
        );

    shapes_push(&this->figure.shapes, tmp);

    t = get_ellipse_point(circles_center, cir_1_r, cir_1_r,
                          to_rad(270));

    tmp = shape_create(
        line_create(t, point_create(t->x, t->y + dash_len))
        );

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        line_create(point_create(circles_center->x, circles_center->y),
                    point_create(circles_center->x, circles_center->y - minute_hand_len))
        );

    shapes_push(&this->figure.shapes, tmp);

    tmp = shape_create(
        line_create(point_create(circles_center->x, circles_center->y),
                    point_create(circles_center->x + hour_hand_len, circles_center->y))
        );

    shapes_push(&this->figure.shapes, tmp);


    figure_find_and_set_center(&this->figure);

    set_center_label();
}

void MainWindow::set_center_label()
{
    ui->center_label->setText("Центр изображения: (" +
                              QString::number(this->figure.center->x) + "; " +
                              QString::number(this->figure.center->y) + ")");
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

    connect(ui->btn_move_center, &QPushButton::clicked, this,
            &MainWindow::move_to_center_clicked);

    connect(ui->btn_cancel, &QPushButton::clicked, this,
            &MainWindow::get_prev_clicked);

    connect(ui->btn_reset, &QPushButton::clicked, this,
            &MainWindow::reset_figure_clicked);


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
    this->is_prev = false;



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
    set_center_label();
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

void show_err_msg(QString str)
{
     QMessageBox::critical(NULL, "Ошибка!", str);
}

void MainWindow::move_btn_clicked()
{
    bool dx_ok, dy_ok;

    double dx = ui->input_dx->text().toDouble(&dx_ok);
    double dy = ui->input_dy->text().toDouble(&dy_ok);

    if (dx_ok && dy_ok)
    {
        set_prev_figure();
        this->figure = figure_move(&this->figure, point_create(dx, dy));
    }
    else
    {
        if (!dx_ok && dy_ok)
            show_err_msg("Не введен dx!");
        else if (dx_ok && !dy_ok)
            show_err_msg("Не введен dy!");
        else
            show_err_msg("Не введен ни один из коэффициентов смещения!");
    }

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
    {
        set_prev_figure();
        this->figure = figure_rotate(&this->figure, point_create(cx, cy), angle);
    }
    else
    {
        if (!angle_ok)
            show_err_msg("Не введен угол поворота!");
        else
        {
            if (!cx_ok && cy_ok)
                show_err_msg("Не введена координата x центра операций!");
            else if (cx_ok && !cy_ok)
                show_err_msg("Не введена координата y центра операций!");
            else
                show_err_msg("Не введена ни одина координата центра операций!");
        }
    }

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
    {
        set_prev_figure();
        this->figure = figure_scale(&this->figure, point_create(cx, cy), point_create(kx, ky));
    }
    else
    {
        if (!kx_ok || !ky_ok)
        {
            if (!kx_ok && ky_ok)
                show_err_msg("Не введен kx!");
            else if (kx_ok && !ky_ok)
                show_err_msg("Не введен ky!");
            else
                show_err_msg("Не введен ни один из коэффициентов масштабирования!");
        }
        else
        {
            if (!cx_ok && cy_ok)
                show_err_msg("Не введена координата x центра операций!");
            else if (cx_ok && !cy_ok)
                show_err_msg("Не введена координата y центра операций!");
            else
                show_err_msg("Не введена ни одина координата центра операций!");
        }
    }

    clear_screen();
    draw_screen();
}

void MainWindow::move_to_center_clicked()
{
    double dx = (double) this->pxp.width() / 2 - this->figure.center->x;
    double dy = (double) this->pxp.height() / 2 - this->figure.center->y;

    set_prev_figure();
    this->figure = figure_move(&this->figure, point_create(dx, dy));

    clear_screen();
    draw_screen();
}

void MainWindow::set_prev_figure()
{
    this->prev_figure = this->figure;
    this->is_prev = true;
}

void MainWindow::get_prev_figure()
{
    if (is_prev)
    {
        this->figure = this->prev_figure;
        this->is_prev = false;
    }
    else
    {
        show_err_msg("Нет предыдущей трансформации фигуры!");
    }
}

void MainWindow::get_prev_clicked()
{
    get_prev_figure();
    clear_screen();
    draw_screen();
}

void MainWindow::reset_figure_clicked()
{
    create_figure();
    this->is_prev = false;
    clear_screen();
    draw_screen();
}
