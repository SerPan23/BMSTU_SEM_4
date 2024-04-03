#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");

    QRect rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());

    clear_screen();

    set_preview_widget_color(ui->bg_color_preview, this->bg_color);
    set_preview_widget_color(ui->line_color_preview, this->line_color);

    this->scale_center = QPointF(round(ui->graphicsView->scene()->width() / 2),
                                 round(ui->graphicsView->scene()->height() / 2));

    // connects block
    connect(ui->btn_bg_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_bg_color_change_clicked);
    connect(ui->btn_line_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_line_color_change_clicked);

    connect(ui->btn_clear_screen, &QPushButton::clicked, this,
            &MainWindow::clear_screen);

    connect(ui->scale_slider, &QSlider::valueChanged, this,
            &MainWindow::slider_scale_changed);

    connect(ui->back_btn, &QPushButton::clicked, this,
            &MainWindow::go_to_main_page);



    connect(ui->btn_circle_draw, &QPushButton::clicked, this,
            &MainWindow::btn_circle_draw_clicked);

    connect(ui->btn_ellipse_draw, &QPushButton::clicked, this,
            &MainWindow::btn_ellipse_draw_clicked);

    connect(ui->btn_draw_circles_spectrum, &QPushButton::clicked, this,
            &MainWindow::btn_circles_draw_spectrum_clicked);
    connect(ui->btn_draw_ellipses_spectrum, &QPushButton::clicked, this,
            &MainWindow::btn_ellipses_draw_spectrum_clicked);

    // connect(ui->btn_time_cmp_circles, &QPushButton::clicked, this,
    //         &MainWindow::btn_time_cmp_clicked);
    // connect(ui->btn_time_cmp_ellipses, &QPushButton::clicked, this,
    //         &MainWindow::btn_time_cmp_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    // auto double_validator = new QDoubleValidator;
    // double_validator->setLocale(locale);

    // ui->start_x->setValidator(double_validator);
    // ui->start_y->setValidator(double_validator);

    // ui->end_x->setValidator(double_validator);
    // ui->end_y->setValidator(double_validator);

    // auto int_validator = new QIntValidator;
    // int_validator->setLocale(locale);

    // ui->angle->setValidator(int_validator);
    // ui->radius->setValidator(double_validator);

    // ui->line_len->setValidator(double_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show_err_msg(QString msg)
{
    QMessageBox::critical(NULL, "Ошибка!", msg);
}

void MainWindow::set_preview_widget_color(QWidget *widget, QColor color)
{
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    widget->setAutoFillBackground(true);
    widget->setPalette(palette);
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

void MainWindow::clear_screen()
{
    this->pxp = QPixmap(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    this->pxp.fill(Qt::transparent);


    ui->graphicsView->scene()->clear();
}

void MainWindow::draw()
{
    ui->graphicsView->scene()->addPixmap(this->pxp);
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


void MainWindow::btn_circle_draw_clicked()
{
    bool center_x_ok, center_y_ok, radius_ok;

    double center_x = ui->center_x->text().toDouble(&center_x_ok);
    double center_y = ui->center_y->text().toDouble(&center_y_ok);

    int radius = ui->radius->text().toInt(&radius_ok);


    if (!center_x_ok)
    {
        show_err_msg("Не коректное значение х центра окружности/эллипса");
        return;
    }

    if (!center_y_ok)
    {
        show_err_msg("Не коректное значение y центра окружности/эллипса");
        return;
    }

    if (!radius_ok)
    {
        show_err_msg("Не коректное значение радиуса окружности");
        return;
    }



    point_t center{center_x, center_y};

    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    // void draw_circle(draw_view_t *view, algorithm_t alg, QColor color, point_t center, double radius);

    algorithm_t alg = get_algorithm(algorithm);
    draw_circle(view, alg, this->line_color, center, radius);

    draw();
}

void MainWindow::btn_ellipse_draw_clicked()
{

    bool center_x_ok, center_y_ok, radius_x_ok, radius_y_ok;

    double center_x = ui->center_x->text().toDouble(&center_x_ok);
    double center_y = ui->center_y->text().toDouble(&center_y_ok);

    double radius_x = ui->radius_x->text().toDouble(&radius_x_ok);
    double radius_y = ui->radius_y->text().toDouble(&radius_y_ok);


    if (!center_x_ok)
    {
        show_err_msg("Не коректное значение х центра окружности/эллипса");
        return;
    }

    if (!center_y_ok)
    {
        show_err_msg("Не коректное значение y центра окружности/эллипса");
        return;
    }

    if (!radius_x)
    {
        show_err_msg("Не коректное значение радиуса по x эллипса");
        return;
    }

    if (!radius_y)
    {
        show_err_msg("Не коректное значение радиуса по y эллипса");
        return;
    }


    point_t center{center_x, center_y};
    point_t radius{radius_x, radius_y};

    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    // void draw_ellipse(draw_view_t *view, algorithm_t alg, QColor color, point_t center, point_t radius);

    algorithm_t alg = get_algorithm(algorithm);
    draw_ellipse(view, alg, this->line_color, center, radius);

    draw();
}

int MainWindow::read_spectrum_data_circle(spectrum_data_t& data)
{

    bool start_radius_ok, step_ok, figures_count_ok;

    double start_radius = ui->start_radius->text().toInt(&start_radius_ok);
    double step = ui->step->text().toInt(&step_ok);
    double figures_count = ui->figures_count->text().toInt(&figures_count_ok);

    if (!start_radius_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса окружности");
        return 1;
    }

    if (!step_ok)
    {
        show_err_msg("Не коректное значение шага изменения");
        return 1;
    }

    if (!figures_count_ok)
    {
        show_err_msg("Не коректное значение количества фигур");
        return 1;
    }

    data.start_radius = point_t{start_radius, start_radius};
    data.step = step;
    data.figures_count = figures_count;

    data.center = point_t{round(ui->graphicsView->scene()->width() / 2),
                   round(ui->graphicsView->scene()->height() / 2)};

    data.color = this->line_color;

    return 0;
}

int MainWindow::read_spectrum_data_ellipse(spectrum_data_t& data)
{

    bool start_radius_x_ok, start_radius_y_ok, step_ok, figures_count_ok;

    double start_radius_x = ui->start_radius_x->text().toInt(&start_radius_x_ok);
    double start_radius_y = ui->start_radius_y->text().toInt(&start_radius_y_ok);

    double step = ui->step->text().toInt(&step_ok);
    double figures_count = ui->figures_count->text().toInt(&figures_count_ok);

    if (!start_radius_x_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса x эллипса");
        return 1;
    }
    if (!start_radius_y_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса y эллипса");
        return 1;
    }

    if (!step_ok)
    {
        show_err_msg("Не коректное значение шага изменения");
        return 1;
    }

    if (!figures_count_ok)
    {
        show_err_msg("Не коректное значение количества фигур");
        return 1;
    }

    data.start_radius = point_t{start_radius_x, start_radius_y};
    data.step = step;
    data.figures_count = figures_count;

    data.center = point_t{round(ui->graphicsView->scene()->width() / 2),
                          round(ui->graphicsView->scene()->height() / 2)};

    data.color = this->line_color;

    return 0;
}

void MainWindow::btn_circles_draw_spectrum_clicked()
{
    spectrum_data_t spectrum_data;
    int rc = read_spectrum_data_circle(spectrum_data);
    if (rc)
        return;


    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    algorithm_t alg = get_algorithm(algorithm);

    // int radius = start_radius;
    // for (int i = 0; i < figure_count; i++, radius += step)
    //     draw_circle(view, alg, this->line_color, center, radius);

    draw_circles_spectrum(view, alg, spectrum_data);

    draw();
}

void MainWindow::btn_ellipses_draw_spectrum_clicked()
{
    spectrum_data_t spectrum_data;
    int rc = read_spectrum_data_ellipse(spectrum_data);
    if (rc)
        return;


    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    algorithm_t alg = get_algorithm(algorithm);

    // point_t radius = start_radius;
    // for (int i = 0; i < figure_count; i++, radius.x += step, radius.y += step)
    //     draw_ellipse(view, alg, this->line_color, center, radius);

    draw_ellipses_spectrum(view, alg, spectrum_data);

    draw();
}

void MainWindow::btn_time_cmp_circles_clicked()
{
    spectrum_data_t spectrum_data;
    int rc = read_spectrum_data_circle(spectrum_data);
    if (rc)
        return;


    QString algorithm = ui->algorithm_selection->currentText();

    // std::vector<long> times;
    // times.push_back(time_measurement(start, end, dda));
    // times.push_back(time_measurement(start, end, bresenham_double));
    // times.push_back(time_measurement(start, end, bresenham_integer));
    // times.push_back(time_measurement(start, end, bresenham_smooth));
    // times.push_back(time_measurement(start, end, wu));


    // ui->pages->setCurrentIndex(1);

    // QLayoutItem *item;
    // while ((item = ui->time_layout->takeAt(0)))
    //     delete item;


    // auto set0 = new QBarSet("ЦДА");
    // auto set1 = new QBarSet("Брезенхем");
    // auto set2 = new QBarSet("Брезенхем целочисленный");
    // auto set3 = new QBarSet("Брезенхем со сглаживанием");
    // auto set4 = new QBarSet("Ву");


    // double min_y = 0, max_y = (double) *max_element(times.begin(), times.end());

    // *set0 << times[0];
    // *set1 << times[1];
    // *set2 << times[2];
    // *set3 << times[3];
    // *set4 << times[4];

    // QBarSeries *series = new QBarSeries;
    // series->append(set0);
    // series->append(set1);
    // series->append(set2);
    // series->append(set3);
    // series->append(set4);

    // auto chart = new QChart;
    // chart->addSeries(series);
    // chart->setTitle("Сравнение времени работы алгоритмов");
    // chart->setAnimationOptions(QChart::SeriesAnimations);

    // auto axisY = new QValueAxis;
    // axisY->setRange(min_y, max_y);
    // axisY->setTitleText("Время (нс)");
    // chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);

    // chart->legend()->setVisible(true);
    // chart->legend()->setAlignment(Qt::AlignBottom);

    // QChartView *chartView = new QChartView(chart);
    // chartView->setRenderHint(QPainter::Antialiasing);

    // ui->time_layout->addWidget(chartView);
}

void MainWindow::btn_time_cmp_ellipses_clicked()
{
    ui->pages->setCurrentIndex(1);
}

void MainWindow::go_to_main_page()
{
    ui->pages->setCurrentIndex(0);
}
