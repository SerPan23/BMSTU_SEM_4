#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "algorithms/algorithms.h"
#include <iostream>

#include <QtCharts>

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


    connect(ui->back_btn, &QPushButton::clicked, this,
            &MainWindow::go_to_main_page);
    connect(ui->back_btn_2, &QPushButton::clicked, this,
            &MainWindow::go_to_main_page);

    connect(ui->btn_time_cmp, &QPushButton::clicked, this,
            &MainWindow::btn_time_cmp_clicked);

    connect(ui->btn_steps_cmp, &QPushButton::clicked, this,
            &MainWindow::btn_steps_cmp_clicked);


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

    ui->line_len->setValidator(double_validator);
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
        .view = ui->graphicsView,
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

    // clear_screen();

    QString algorithm = ui->algorithm_selection->currentText();
    line_t line;

    draw_view_t view = {
        .view = ui->graphicsView,
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    point_t start{round(view.width / 2), round(view.height / 2)};


    for (int i = 0; i < 360; i += angle)
    {
        point_t end{
            start.x + radius * cos((M_PI / 180) * i),
            start.y + radius * sin((M_PI / 180) * i * -1)};

        // std::cout << i << " " << end.x << " " << end.y << std::endl;

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

void MainWindow::go_to_main_page()
{
    ui->pages->setCurrentIndex(0);
}

QLineSeries *create_line_series(QString name, std::vector<int> &steps_count, QColor color, int max_ang, int step_ang)
{
    auto series = new QLineSeries;

    // double min_x = 0, max_x = max_ang;
    // double min_y = 0, max_y = (int) *max_element(steps_count.begin(), steps_count.end());

    int ang = 0;

    for (int i = 0; i < steps_count.size(); i++, ang += step_ang)
        series->append(ang, steps_count[i]);

    series->setColor(color);
    series->setName(name);

    return series;
}

QChartView *create_graphic(QString title, std::vector<QLineSeries *> &series_vec, point_t min, point_t max)
{
    auto chart = new QChart;
    // chart->legend()->hide();

    auto axisX = new QValueAxis;
    axisX->setRange(min.x, max.x);
    chart->addAxis(axisX, Qt::AlignBottom);
    // // series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setRange(min.y, max.y);
    chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);

    for (int i = 0; i < series_vec.size(); i++)
    {
        chart->addSeries(series_vec[i]);
        series_vec[i]->attachAxis(axisX);
        series_vec[i]->attachAxis(axisY);
    }

    // chart->addSeries(series);
    // chart->createDefaultAxes();
    chart->setTitle(title);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

QChartView *create_graphic(QString title, QLineSeries *series, point_t min, point_t max)
{
    std::vector<QLineSeries *> series_vec;
    series_vec.push_back(series);
    return create_graphic(title, series_vec, min, max);
}

void MainWindow::btn_steps_cmp_clicked()
{
    bool len_ok;

    double line_len = ui->line_len->text().toDouble(&len_ok);

    if (!len_ok)
    {
        show_err_msg("Не коректное значение длины");
        return;
    }


    point_t start{0, 0};

    int max_ang = 90;
    int step_ang = 5;

    std::vector<int> dda_steps_counts;
    std::vector<int> bresenham_double_steps_counts;
    std::vector<int> bresenham_integer_steps_counts;
    std::vector<int> bresenham_smooth_steps_counts;
    std::vector<int> wu_steps_counts;

    for (int i = 0; i <= max_ang; i += step_ang)
    {
        point_t end{
                    start.x + line_len * cos((M_PI / 180) * i),
                    start.y + line_len * sin((M_PI / 180) * i * -1)};

        dda_steps_counts.push_back(dda_step_count(start, end));
        bresenham_double_steps_counts.push_back(bresenham_double_step_count(start, end));
        bresenham_integer_steps_counts.push_back(bresenham_integer_step_count(start, end));
        bresenham_smooth_steps_counts.push_back(bresenham_smooth_step_count(start, end));
        wu_steps_counts.push_back(wu_step_count(start, end));
    }

    int max_el = (int) *max_element(dda_steps_counts.begin(), dda_steps_counts.end());
    max_el = std::max(max_el, (int) *max_element(bresenham_double_steps_counts.begin(),
                                                 bresenham_double_steps_counts.end()));
    max_el = std::max(max_el, (int) *max_element(bresenham_integer_steps_counts.begin(),
                                                 bresenham_integer_steps_counts.end()));
    max_el = std::max(max_el, (int) *max_element(bresenham_smooth_steps_counts.begin(),
                                                 bresenham_smooth_steps_counts.end()));
    max_el = std::max(max_el, (int) *max_element(wu_steps_counts.begin(),
                                                 wu_steps_counts.end()));


    // for (int i = 0; i <= max_ang; i += step_ang)
    //     std::cout << i << " ";
    // std::cout << std::endl;

    // for (int i = 0; i < dda_steps_counts.size(); i++)
    // {
    //     std::cout << dda_steps_counts[i] << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < bresenham_double_steps_counts.size(); i++)
    // {
    //     std::cout << bresenham_double_steps_counts[i] << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < bresenham_integer_steps_counts.size(); i++)
    // {
    //     std::cout << bresenham_integer_steps_counts[i] << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < bresenham_smooth_steps_counts.size(); i++)
    // {
    //     std::cout << bresenham_smooth_steps_counts[i] << " ";
    // }
    // std::cout << std::endl;

    // for (int i = 0; i < wu_steps_counts.size(); i++)
    // {
    //     std::cout << wu_steps_counts[i] << " ";
    // }
    // std::cout << std::endl;

    point_t min{0, 0};
    point_t max{(double)max_ang, (double)max_el};


    std::vector<QLineSeries *> series_vec;
    series_vec.push_back(create_line_series("ЦДА", dda_steps_counts, Qt::blue, max_ang, step_ang));
    series_vec.push_back(create_line_series("Брезенхем",bresenham_double_steps_counts, QColor::fromRgb(255, 190, 26), max_ang, step_ang));
    series_vec.push_back(create_line_series("Брезенхем целочисленный", bresenham_integer_steps_counts, Qt::red, max_ang, step_ang));
    series_vec.push_back(create_line_series("Брезенхем со сглаживанием", bresenham_smooth_steps_counts, Qt::green, max_ang, step_ang));
    series_vec.push_back(create_line_series("Ву", wu_steps_counts, QColor::fromRgb(255, 26, 232), max_ang, step_ang));

    QLayoutItem *item;
    while ((item = ui->grapchics_layout->takeAt(0)))
        delete item;

    // ui->main_page->addWidget(chartView);

    // ui->grapchics_layout->addWidget(create_graphic("Сравнение ступеньчатости | Длна отрезка = "
    //                                                + QString::number(line_len), series_vec), 0, 0);

    ui->grapchics_layout->addWidget(create_graphic("Сравнение ступеньчатости", series_vec, min, max), 0, 0);

    ui->grapchics_layout->addWidget(create_graphic("ЦДА", create_line_series("ЦДА", dda_steps_counts, Qt::blue,
                                                                             max_ang, step_ang), min, max), 0, 1);
    ui->grapchics_layout->addWidget(create_graphic("Ву", create_line_series("Ву", wu_steps_counts, QColor::fromRgb(255, 26, 232),
                                                                            max_ang, step_ang), min, max), 0, 2);

    ui->grapchics_layout->addWidget(create_graphic("Брезенхем",
                                                   create_line_series("Брезенхем",bresenham_double_steps_counts,
                                                                      QColor::fromRgb(255, 190, 26), max_ang, step_ang)
                                                   , min, max), 1, 0);
    ui->grapchics_layout->addWidget(create_graphic("Брезенхем целочисленный",
                                                   create_line_series("Брезенхем целочисленный", bresenham_integer_steps_counts,
                                                                      Qt::red, max_ang, step_ang), min, max), 1, 1);
    ui->grapchics_layout->addWidget(create_graphic("Брезенхем со сглаживанием",
                                                   create_line_series("Брезенхем со сглаживанием", bresenham_smooth_steps_counts,
                                                                      Qt::green, max_ang, step_ang), min, max), 1, 2);


    for(int c=0; c < ui->grapchics_layout->columnCount(); c++) ui->grapchics_layout->setColumnStretch(c,1);
    for(int r=0; r < ui->grapchics_layout->rowCount(); r++)  ui->grapchics_layout->setRowStretch(r,1);

    ui->pages->setCurrentIndex(1);
}

void MainWindow::btn_time_cmp_clicked()
{
    bool len_ok;

    double line_len = ui->line_len->text().toDouble(&len_ok);

    if (!len_ok)
    {
        show_err_msg("Не коректное значение длины");
        return;
    }


    point_t start{0, 0};
    point_t end{line_len, line_len};

    std::vector<long> times;
    times.push_back(time_measurement(start, end, dda));
    times.push_back(time_measurement(start, end, bresenham_double));
    times.push_back(time_measurement(start, end, bresenham_integer));
    times.push_back(time_measurement(start, end, bresenham_smooth));
    times.push_back(time_measurement(start, end, wu));


    ui->pages->setCurrentIndex(2);

    QLayoutItem *item;
    while ((item = ui->time_layout->takeAt(0)))
        delete item;


    auto set0 = new QBarSet("ЦДА");
    auto set1 = new QBarSet("Брезенхем");
    auto set2 = new QBarSet("Брезенхем целочисленный");
    auto set3 = new QBarSet("Брезенхем со сглаживанием");
    auto set4 = new QBarSet("Ву");


    double min_y = 0, max_y = (double) *max_element(times.begin(), times.end());

    *set0 << times[0];
    *set1 << times[1];
    *set2 << times[2];
    *set3 << times[3];
    *set4 << times[4];

    QBarSeries *series = new QBarSeries;
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Сравнение времени работы алгоритмов");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    auto axisY = new QValueAxis;
    axisY->setRange(min_y, max_y);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->time_layout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
