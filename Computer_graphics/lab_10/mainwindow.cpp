#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawer = std::make_shared<Drawer>(ui->graphicsView, this);

    set_preview_widget_color(ui->surface_color_preview, this->surface_color);

    connect(ui->btn_surface_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_surface_color_change_clicked);

    connect(ui->btn_clear, &QPushButton::clicked, this,
            &MainWindow::clear_clicked);
    connect(ui->btn_draw, &QPushButton::clicked, this,
            &MainWindow::draw_clicked);

    connect(ui->x_rotate_btn, &QPushButton::clicked, this,
            &MainWindow::x_rotate_clicked);
    connect(ui->y_rotate_btn, &QPushButton::clicked, this,
            &MainWindow::y_rotate_clicked);
    connect(ui->z_rotate_btn, &QPushButton::clicked, this,
            &MainWindow::z_rotate_clicked);

    connect(ui->scale_change, &QPushButton::clicked, this,
            &MainWindow::scale_change_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto double_validator = new QDoubleValidator;
    double_validator->setLocale(locale);

    ui->x_start->setValidator(double_validator);
    ui->x_end->setValidator(double_validator);
    ui->x_step->setValidator(double_validator);

    ui->z_start->setValidator(double_validator);
    ui->z_end->setValidator(double_validator);
    ui->z_step->setValidator(double_validator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->x_rotate->setValidator(int_validator);
    ui->y_rotate->setValidator(int_validator);
    ui->z_rotate->setValidator(int_validator);

    ui->scale_coef->setValidator(int_validator);

    auto f = getFuncsList();
    funcs = std::make_shared<Funcs>(f);
    surfaces_load();
    surface_choosed();
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

void MainWindow::btn_surface_color_change_clicked()
{
    this->surface_color = QColor(QColorDialog::getColor(this->surface_color).rgb());
    set_preview_widget_color(ui->surface_color_preview, this->surface_color);
}

void MainWindow::surface_choosed()
{
    std::string func_name = ui->funcsCB->currentData().toString().toStdString();
    current_func = funcs->get(func_name);
}

void MainWindow::surfaces_load()
{
    for (auto func : *funcs)
    {
        QString d = QString::fromLocal8Bit(func.first.c_str());
        ui->funcsCB->addItem(d, d);
    }
}

void MainWindow::clear_clicked()
{
    drawer->clear();
    transformData = std::make_shared<TransformData>();
}

void MainWindow::draw()
{
    drawer->clear();
    draw_surface(drawer, current_surface, transformData);
    drawer->render();
}

void MainWindow::draw_clicked()
{
    bool x_start_ok, x_end_ok, x_step_ok;
    double x_start, x_end, x_step;

    x_start = ui->x_start->text().toDouble(&x_start_ok);
    x_end = ui->x_end->text().toDouble(&x_end_ok);
    x_step = ui->x_step->text().toDouble(&x_step_ok);

    if (!x_start_ok)
    {
        show_err_msg("Начало по x не задано!");
        return;
    }
    if (!x_end_ok)
    {
        show_err_msg("Конец по x не задан!");
        return;
    }
    if (!x_step_ok)
    {
        show_err_msg("Шаг по x не задан!");
        return;
    }

    bool z_start_ok, z_end_ok, z_step_ok;
    double z_start, z_end, z_step;

    z_start = ui->z_start->text().toDouble(&z_start_ok);
    z_end = ui->z_end->text().toDouble(&z_end_ok);
    z_step = ui->z_step->text().toDouble(&z_step_ok);

    if (!z_start_ok)
    {
        show_err_msg("Начало по z не задано!");
        return;
    }
    if (!z_end_ok)
    {
        show_err_msg("Конец по z не задан!");
        return;
    }
    if (!z_step_ok)
    {
        show_err_msg("Шаг по z не задан!");
        return;
    }

    current_surface =
    {
        x_start, x_end, x_step,
        z_start, z_end, z_step,
        current_func,
        surface_color
    };

    draw();
}

void MainWindow::x_rotate_clicked()
{
    bool ax_ok;
    int ax;

    ax = ui->x_rotate->text().toInt(&ax_ok);

    if (!ax_ok)
    {
        show_err_msg("Угол по x не задан!");
        return;
    }

    transformData->x_rotate(ax);

    draw();
}

void MainWindow::y_rotate_clicked()
{
    bool ay_ok;
    int ay;

    ay = ui->y_rotate->text().toInt(&ay_ok);

    if (!ay_ok)
    {
        show_err_msg("Угол по y не задан!");
        return;
    }

    transformData->y_rotate(ay);

    draw();
}

void MainWindow::z_rotate_clicked()
{
    bool az_ok;
    int az;

    az = ui->z_rotate->text().toInt(&az_ok);

    if (!az_ok)
    {
        show_err_msg("Угол по z не задан!");
        return;
    }

    transformData->z_rotate(az);

    draw();
}

void MainWindow::scale_change_clicked()
{
    bool scale_ok;
    int scale;

    scale = ui->scale_coef->text().toInt(&scale_ok);

    if (!scale_ok)
    {
        show_err_msg("Коэффициент масштабирования не задан!");
        return;
    }

    transformData->set_scale(scale);

    draw();
}
