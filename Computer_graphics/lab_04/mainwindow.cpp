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

    connect(ui->btn_time_cmp_circles, &QPushButton::clicked, this,
            &MainWindow::btn_time_cmp_circles_clicked);
    connect(ui->btn_time_cmp_ellipses, &QPushButton::clicked, this,
            &MainWindow::btn_time_cmp_ellipses_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    // auto double_validator = new QDoubleValidator;
    // double_validator->setLocale(locale);

    // ui->start_x->setValidator(double_validator);
    // ui->start_y->setValidator(double_validator);

    // ui->end_x->setValidator(double_validator);
    // ui->end_y->setValidator(double_validator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->center_x->setValidator(int_validator);
    ui->center_y->setValidator(int_validator);

    ui->radius->setValidator(int_validator);
    ui->radius_x->setValidator(int_validator);
    ui->radius_y->setValidator(int_validator);

    ui->start_radius->setValidator(int_validator);
    ui->start_radius_x->setValidator(int_validator);
    ui->start_radius_y->setValidator(int_validator);

    ui->step->setValidator(int_validator);

    ui->figures_count->setValidator(int_validator);
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

    int center_x = ui->center_x->text().toInt(&center_x_ok);
    int center_y = ui->center_y->text().toInt(&center_y_ok);

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

    algorithm_t alg = get_algorithm(algorithm);
    draw_circle(view, alg, this->line_color, center, radius);

    draw();
}

void MainWindow::btn_ellipse_draw_clicked()
{

    bool center_x_ok, center_y_ok, radius_x_ok, radius_y_ok;

    int center_x = ui->center_x->text().toInt(&center_x_ok);
    int center_y = ui->center_y->text().toInt(&center_y_ok);

    int radius_x = ui->radius_x->text().toInt(&radius_x_ok);
    int radius_y = ui->radius_y->text().toInt(&radius_y_ok);


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

    algorithm_t alg = get_algorithm(algorithm);
    draw_ellipse(view, alg, this->line_color, center, radius);

    draw();
}

void MainWindow::btn_circles_draw_spectrum_clicked()
{
    bool start_radius_ok, step_ok, figures_count_ok;

    int start_radius = ui->start_radius->text().toInt(&start_radius_ok);
    int step = ui->step->text().toInt(&step_ok);
    int figures_count = ui->figures_count->text().toInt(&figures_count_ok);

    if (!start_radius_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса окружности спектра");
        return;
    }

    if (!step_ok)
    {
        show_err_msg("Не коректное значение шага изменения спектра");
        return;
    }

    if (!figures_count_ok)
    {
        show_err_msg("Не коректное значение количества фигур в спектре");
        return;
    }

    point_t center{(int)round(ui->graphicsView->scene()->width() / 2),
                   (int)round(ui->graphicsView->scene()->height() / 2)};


    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    algorithm_t alg = get_algorithm(algorithm);

    int radius = start_radius;
    for (int i = 0; i < figures_count; i++, radius += step)
        draw_circle(view, alg, this->line_color, center, radius);

    draw();
}

void MainWindow::btn_ellipses_draw_spectrum_clicked()
{
    bool start_radius_x_ok, start_radius_y_ok, step_ok, figures_count_ok;

    int start_radius_x = ui->start_radius_x->text().toInt(&start_radius_x_ok);
    int start_radius_y = ui->start_radius_y->text().toInt(&start_radius_y_ok);

    int step = ui->step->text().toInt(&step_ok);
    int figures_count = ui->figures_count->text().toInt(&figures_count_ok);

    if (!start_radius_x_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса x эллипса спектра");
        return;
    }
    if (!start_radius_y_ok)
    {
        show_err_msg("Не коректное начальное значение радиуса y эллипса спектра");
        return;
    }

    if (!step_ok)
    {
        show_err_msg("Не коректное значение шага изменения спектра");
        return;
    }

    if (!figures_count_ok)
    {
        show_err_msg("Не коректное значение количества фигур в спектре");
        return;
    }

    point_t start_radius{start_radius_x, start_radius_y};

    point_t center{(int)round(ui->graphicsView->scene()->width() / 2),
                   (int)round(ui->graphicsView->scene()->height() / 2)};


    QString algorithm = ui->algorithm_selection->currentText();


    draw_view_t view = {
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    algorithm_t alg = get_algorithm(algorithm);

    point_t radius = start_radius;
    int step_b = round(step * 1.0 * radius.y / radius.x);
    for (int i = 0; i < figures_count; i++, radius.x += step, radius.y += step_b)
        draw_ellipse(view, alg, this->line_color, center, radius);

    draw();
}

void MainWindow::create_series_circle(QLineSeries *series, long &max_el, QColor color, QString name, figure_t (*alg)(point_t center, int radius))
{
    point_t center{(int)round(ui->graphicsView->scene()->width() / 2),
                   (int)round(ui->graphicsView->scene()->height() / 2)};

    int end_radius = 1000;
    int step = 100;

    // auto series = new QLineSeries;

    for (int radius = 0; radius <= end_radius; radius += step)
    {
        long time = time_measurement_circle(center, radius, alg);
        max_el = std::max(max_el, time);
        series->append(radius, time);
    }

    series->setColor(color);
    series->setName(name);

    // return series;
}

void MainWindow::btn_time_cmp_circles_clicked()
{
    long max_el = -1;

    // QLineSeries *canonical_s = create_series_circle(max_el, Qt::red, "Каноническое уравнение", canonical_circle);
    // QLineSeries *parametric_s = create_series_circle(max_el, Qt::blue, "Параметрическое уравнение", canonical_circle);
    // QLineSeries *bresenham_s = create_series_circle(max_el, Qt::green, "Алгоритм Брезенхема", bresenham_circle);
    // QLineSeries *middle_point_s = create_series_circle(max_el, QColor::fromRgb(255, 190, 26), "Алгоритм средней точки", middle_point_circle);


    QLineSeries *canonical_s = new QLineSeries;
    QLineSeries *parametric_s = new QLineSeries;
    QLineSeries *bresenham_s = new QLineSeries;
    QLineSeries *middle_point_s = new QLineSeries;


    create_series_circle(canonical_s, max_el, Qt::red, "Каноническое уравнение", canonical_circle);
    create_series_circle(parametric_s, max_el, Qt::blue, "Параметрическое уравнение", canonical_circle);
    create_series_circle(bresenham_s, max_el, Qt::green, "Алгоритм Брезенхема", bresenham_circle);
    create_series_circle(middle_point_s, max_el, QColor::fromRgb(255, 190, 26), "Алгоритм средней точки", middle_point_circle);


    //
    point_t min{0, 0};
    point_t max{1000, 0};

    auto chart = new QChart;
    // chart->legend()->hide();

    auto axisX = new QValueAxis;
    axisX->setRange(min.x, max.x);
    axisX->setTitleText("Длина радиуса");
    chart->addAxis(axisX, Qt::AlignBottom);
    // // series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setRange(min.y, max_el);
    axisY->setTitleText("Время (нс)");
    chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);


    chart->addSeries(canonical_s);
    chart->addSeries(parametric_s);
    chart->addSeries(bresenham_s);
    chart->addSeries(middle_point_s);

    // chart->addSeries(series);
    // chart->createDefaultAxes();
    chart->setTitle("Замеры для окружности");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    //
    ui->pages->setCurrentIndex(1);

    QLayoutItem *item;
    while ((item = ui->time_layout->takeAt(0)))
        delete item;

    ui->time_layout->addWidget(chartView);
}

void MainWindow::create_series_ellipse(QLineSeries *series, long &max_el, QColor color, QString name, figure_t (*alg)(point_t center, point_t radius))
{
    point_t center{(int)round(ui->graphicsView->scene()->width() / 2),
                   (int)round(ui->graphicsView->scene()->height() / 2)};

    int end_radius = 1000;
    int step = 100;


    // auto series = new QLineSeries;

    for (point_t radius{0, 100}; radius.x <= end_radius; radius.x += step, radius.y += step)
    {
        long time = time_measurement_ellipse(center, radius, alg);
        max_el = std::max(max_el, time);
        series->append(radius.x, time);
    }

    series->setColor(color);
    series->setName(name);

    // return series;
}

void MainWindow::btn_time_cmp_ellipses_clicked()
{
    long max_el = -1;

    // QLineSeries *canonical_s = create_series_ellipse(max_el, Qt::red, "Каноническое уравнение", canonical_ellipse);
    // QLineSeries *parametric_s = create_series_ellipse(max_el, Qt::blue, "Параметрическое уравнение", parametric_ellipse);
    // QLineSeries *bresenham_s = create_series_ellipse(max_el, Qt::green, "Алгоритм Брезенхема", bresenham_ellipse);
    // QLineSeries *middle_point_s = create_series_ellipse(max_el, QColor::fromRgb(255, 190, 26), "Алгоритм средней точки", middle_point_ellipse);


    QLineSeries *canonical_s = new QLineSeries;
    QLineSeries *parametric_s = new QLineSeries;
    QLineSeries *bresenham_s = new QLineSeries;
    QLineSeries *middle_point_s = new QLineSeries;


    create_series_ellipse(canonical_s, max_el, Qt::red, "Каноническое уравнение", canonical_ellipse);
    create_series_ellipse(parametric_s, max_el, Qt::blue, "Параметрическое уравнение", parametric_ellipse);
    create_series_ellipse(bresenham_s, max_el, Qt::green, "Алгоритм Брезенхема", bresenham_ellipse);
    create_series_ellipse(middle_point_s, max_el, QColor::fromRgb(255, 190, 26), "Алгоритм средней точки", middle_point_ellipse);


    //
    point_t min{0, 0};
    point_t max{1000, 0};

    auto chart = new QChart;
    // chart->legend()->hide();

    auto axisX = new QValueAxis;
    axisX->setRange(min.x, max.x);
    axisX->setTitleText("Длина радиуса");
    chart->addAxis(axisX, Qt::AlignBottom);
    // // series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setRange(min.y, max_el);
    axisY->setTitleText("Время (нс)");
    chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);


    chart->addSeries(canonical_s);
    chart->addSeries(parametric_s);
    chart->addSeries(bresenham_s);
    chart->addSeries(middle_point_s);

    // chart->addSeries(series);
    // chart->createDefaultAxes();
    chart->setTitle("Замеры для эллипса");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    //
    ui->pages->setCurrentIndex(1);

    QLayoutItem *item;
    while ((item = ui->time_layout->takeAt(0)))
        delete item;

    ui->time_layout->addWidget(chartView);
}

void MainWindow::go_to_main_page()
{
    ui->pages->setCurrentIndex(0);
}
