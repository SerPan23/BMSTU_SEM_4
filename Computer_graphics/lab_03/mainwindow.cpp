#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "algorithms/algorithms.h"
#include <iostream>

void print_vector(std::vector <pixel_t> vec)
{
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i].x << " " << vec[i].y << " (" << vec[i].intensity << ")" << std::endl;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MyGraphicsScene *scene = new MyGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());

    // this->pxp = QPixmap(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    clear_screen();

    set_preview_widget_color(ui->bg_color_preview, this->bg_color);
    set_preview_widget_color(ui->line_color_preview, this->line_color);


    reset_scale_center();


    connect(ui->btn_bg_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_bg_color_change_clicked);
    connect(ui->btn_line_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_line_color_change_clicked);

    connect(ui->btn_line_draw, &QPushButton::clicked, this,
            &MainWindow::btn_draw_line_clicked);

    connect(ui->btn_spectrum_draw, &QPushButton::clicked, this,
            &MainWindow::btn_draw_line_spectrum_clicked);

    connect(ui->btn_clear_screen, &QPushButton::clicked, this,
            &MainWindow::clear_screen);

    connect(ui->btn_reset_scale_center, &QPushButton::clicked, this,
            &MainWindow::reset_scale_center);


    connect(ui->scale_slider, &QSlider::valueChanged, this,
            &MainWindow::slider_scale_changed);

    connect(scene, &MyGraphicsScene::posChanged, this,
            &MainWindow::scene_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto double_validator = new QDoubleValidator;
    double_validator->setLocale(locale);

    ui->start_x->setValidator(double_validator);
    ui->start_y->setValidator(double_validator);

    ui->end_x->setValidator(double_validator);
    ui->end_y->setValidator(double_validator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->angle->setValidator(int_validator);
    ui->radius->setValidator(double_validator);
}

void MainWindow::set_preview_widget_color(QWidget *widget, QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(palette);
}

void MainWindow::show_err_msg(QString msg)
{
    QMessageBox::critical(NULL, "Ошибка!", msg);
}

void MainWindow::btn_bg_color_change_clicked()
{
    this->bg_color = QColorDialog::getColor(this->bg_color);
    set_preview_widget_color(ui->bg_color_preview, this->bg_color);

    QString css = QString("QGraphicsView {background-color: #%1%2%3}")
        .arg(bg_color.red(), 0, 16)
        .arg(bg_color.green(), 0, 16)
        .arg(bg_color.blue(), 0, 16);

    ui->graphicsView->setStyleSheet(css);
}

void MainWindow::btn_line_color_change_clicked()
{
    this->line_color = QColorDialog::getColor(this->line_color);
    set_preview_widget_color(ui->line_color_preview, this->line_color);
}

void MainWindow::btn_draw_line_clicked()
{
    bool start_x_ok, start_y_ok;
    bool end_x_ok, end_y_ok;

    double start_x = ui->start_x->text().toDouble(&start_x_ok);
    double start_y = ui->start_y->text().toDouble(&start_y_ok);

    double end_x = ui->end_x->text().toDouble(&end_x_ok);
    double end_y = ui->end_y->text().toDouble(&end_y_ok);


    if (!start_x_ok)
    {
        show_err_msg("Не коректное значение х начала линии");
        return;
    }

    if (!start_y_ok)
    {
        show_err_msg("Не коректное значение y начала линии");
        return;
    }

    if (!end_x_ok)
    {
        show_err_msg("Не коректное значение х конца линии");
        return;
    }

    if (!end_y_ok)
    {
        show_err_msg("Не коректное значение y конца линии");
        return;
    }


    point_t start{start_x, start_y};
    point_t end{end_x, end_y};

    QString algorithm = ui->algorithm_selection->currentText();
    line_t line;

    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    if (algorithm == "Библиотечный")
    {
        draw_line(&view, this->line_color, start, end);
    }
    else
    {
        if (algorithm == "ЦДА")
            line = dda(start, end);
        else if (algorithm == "Брезенхем")
            line = bresenham_double(start, end);
        else if (algorithm == "Брезенхем целочисленный")
            line = bresenham_integer(start, end);
        else if (algorithm == "Брезенхем со сглаживанием")
            line = bresenham_smooth(start, end);
        else if (algorithm == "Ву")
            line = wu(start, end);

        draw_line(&view, this->line_color, line);
    }

    ui->graphicsView->scene()->addPixmap(this->pxp);
}

void MainWindow::btn_draw_line_spectrum_clicked()
{
    bool angle_ok, radius_ok;

    double angle = ui->angle->text().toDouble(&angle_ok);
    double radius = ui->radius->text().toDouble(&radius_ok);

    if (!angle_ok)
    {
        show_err_msg("Не коректное значение угла");
        return;
    }

    if (!radius_ok)
    {
        show_err_msg("Не коректное значение радиуса");
        return;
    }

    clear_screen();

    QString algorithm = ui->algorithm_selection->currentText();
    line_t line;

    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    point_t start{round(view.width / 2), round(view.height / 2)};


    for (int i = 0; i <= 360; i += angle)
    {
        point_t end{
            start.x + radius * cos((M_PI / 180) * i),
            start.y + radius * sin((M_PI / 180) * i * -1)};

        if (algorithm == "Библиотечный")
        {
            draw_line(&view, this->line_color, start, end);
        }
        else
        {
            if (algorithm == "ЦДА")
                line = dda(start, end);
            else if (algorithm == "Брезенхем")
                line = bresenham_double(start, end);
            else if (algorithm == "Брезенхем целочисленный")
                line = bresenham_integer(start, end);
            else if (algorithm == "Брезенхем со сглаживанием")
                line = bresenham_smooth(start, end);
            else if (algorithm == "Ву")
                line = wu(start, end);

            draw_line(&view, this->line_color, line);
        }
    }

    ui->graphicsView->scene()->addPixmap(this->pxp);
}

void  MainWindow::clear_screen()
{
    // this->pxp.fill();
    // ui->graphicsView->scene()->addPixmap(this->pxp);

    this->pxp = QPixmap(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    this->pxp.fill(Qt::transparent);


    ui->graphicsView->scene()->clear();
}

void MainWindow::slider_scale_changed()
{
    int scale_per = ui->scale_slider->value();

    ui->slider_value->setText(QString::number(scale_per) + "%");

    double factor = scale_per / 100.0;

    ui->graphicsView->resetTransform();

    ui->graphicsView->scale(factor, factor);

    ui->graphicsView->centerOn(this->scale_center);
}

void MainWindow::reset_scale_center()
{
    this->scale_center = QPointF(round(ui->graphicsView->scene()->width() / 2),
                                 round(ui->graphicsView->scene()->height() / 2));
    set_scale_center_text();
}

void MainWindow::set_scale_center_text()
{
    ui->lable_scale_center->setText("Центр масштабирования (" +
                                    QString::number(scale_center.x()) + "; "
                                    + QString::number(scale_center.y()) + ")");
}

void MainWindow::scene_clicked()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    this->scale_center = scene->get_mouse_pos();

    set_scale_center_text();
}

MainWindow::~MainWindow()
{
    delete ui;
}
