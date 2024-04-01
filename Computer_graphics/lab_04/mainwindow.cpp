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

    // connect(ui->btn_line_draw, &QPushButton::clicked, this,
    //         &MainWindow::btn_draw_line_clicked);

    // connect(ui->btn_spectrum_draw, &QPushButton::clicked, this,
    //         &MainWindow::btn_draw_line_spectrum_clicked);

    connect(ui->btn_clear_screen, &QPushButton::clicked, this,
            &MainWindow::clear_screen);


    connect(ui->back_btn, &QPushButton::clicked, this,
            &MainWindow::go_to_main_page);

    // connect(ui->btn_time_cmp_circles, &QPushButton::clicked, this,
    //         &MainWindow::btn_time_cmp_clicked);
    // connect(ui->btn_time_cmp_ellipses, &QPushButton::clicked, this,
    //         &MainWindow::btn_time_cmp_clicked);



    connect(ui->scale_slider, &QSlider::valueChanged, this,
            &MainWindow::slider_scale_changed);


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


// void MainWindow::btn_draw_line_clicked()
// void MainWindow::btn_draw_line_spectrum_clicked()


void MainWindow::go_to_main_page()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::btn_time_cmp_clicked()
{
    ui->pages->setCurrentIndex(1);
}
