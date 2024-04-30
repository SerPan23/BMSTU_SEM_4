#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawer = new Drawer(ui->graphicsView, this);

    set_preview_widget_color(ui->line_color_preview, this->line_color);
    set_preview_widget_color(ui->rect_color_preview, this->rect_color);
    set_preview_widget_color(ui->result_color_preview, this->result_color);


    connect(ui->btn_line_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_line_color_change_clicked);
    connect(ui->btn_rect_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_rect_color_change_clicked);
    connect(ui->btn_result_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_result_color_change_clicked);

    connect(ui->btn_clear, &QPushButton::clicked, this,
            &MainWindow::clear_clicked);



    connect(drawer->scene(), &MyGraphicsScene::mouseLeftBtnClicked, this,
            &MainWindow::mouse_add_line);

    connect(drawer->scene(), &MyGraphicsScene::mouseRightBtnClicked, this,
            &MainWindow::mouse_add_rect);


    connect(ui->btn_add_line, &QPushButton::clicked, this,
            &MainWindow::form_add_line);

    connect(ui->btn_add_rect, &QPushButton::clicked, this,
            &MainWindow::form_add_rect);

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_x_s_line->setValidator(int_validator);
    ui->input_y_s_line->setValidator(int_validator);
    ui->input_x_e_line->setValidator(int_validator);
    ui->input_y_e_line->setValidator(int_validator);

    ui->input_x_s_rect->setValidator(int_validator);
    ui->input_y_s_rect->setValidator(int_validator);
    ui->input_x_e_rect->setValidator(int_validator);
    ui->input_y_e_rect->setValidator(int_validator);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawer;
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

void MainWindow::btn_line_color_change_clicked()
{
    this->line_color = QColor(QColorDialog::getColor(this->line_color).rgb());
    set_preview_widget_color(ui->line_color_preview, this->line_color);
}
void MainWindow::btn_rect_color_change_clicked()
{
    this->rect_color = QColor(QColorDialog::getColor(this->rect_color).rgb());
    set_preview_widget_color(ui->rect_color_preview, this->rect_color);
}
void MainWindow::btn_result_color_change_clicked()
{
    this->result_color = QColor(QColorDialog::getColor(this->result_color).rgb());
    set_preview_widget_color(ui->result_color_preview, this->result_color);
}

void MainWindow::clear_clicked()
{
    drawer->clear();
    //TODO: ADD LINES AND RECT CLEAR
}

void MainWindow::draw()
{
    drawer->draw_lines(lines, line_color);
    if (is_cut_rect_set)
        drawer->draw_rect(cut_rect, rect_color);
}
void MainWindow::update_view()
{
    draw();
    drawer->render();
}

void MainWindow::add_line(int x_s, int y_s, int x_e, int y_e)
{
    line_t line;
    line.start = Point(x_s, y_s);
    line.end = Point(x_e, y_e);

    lines.push_back(line);

    update_view();
}
void MainWindow::mouse_add_line()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();

    if (cur_line_start)
    {
        cur_line.end = Point(round(point.x()), round(point.y()));
        lines.push_back(cur_line);
        update_view();
    }
    else
        cur_line.start = Point(round(point.x()), round(point.y()));

    cur_line_start = !cur_line_start;
}
void MainWindow::form_add_line()
{
    bool x_s_ok, y_s_ok, x_e_ok, y_e_ok;

    int x_s = ui->input_x_s_line->text().toInt(&x_s_ok);
    int y_s = ui->input_y_s_line->text().toInt(&y_s_ok);

    int x_e = ui->input_x_e_line->text().toInt(&x_e_ok);
    int y_e = ui->input_y_e_line->text().toInt(&y_e_ok);

    if (!x_s_ok)
    {
        show_err_msg("Не введена координата x точки начала отрезка");
        return;
    }
    if (!y_s_ok)
    {
        show_err_msg("Не введена координата y точки начала отрезка");
        return;
    }

    if (!x_e_ok)
    {
        show_err_msg("Не введена координата x точки конца отрезка");
        return;
    }
    if (!y_e_ok)
    {
        show_err_msg("Не введена координата y точки конца отрезка");
        return;
    }

    add_line(x_s, y_s, x_e, y_e);
}

void MainWindow::add_rect(int x_s, int y_s, int x_e, int y_e)
{
    cut_rect.left_top = Point(x_s, y_s);
    cut_rect.right_down = Point(x_e, y_e);

    is_cut_rect_set = true;

    update_view();
}
void MainWindow::mouse_add_rect()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();

    if (cut_rect_start)
    {
        cut_rect.right_down = Point(round(point.x()), round(point.y()));
        is_cut_rect_set = true;
    }
    else
    {
        cut_rect.left_top = Point(round(point.x()), round(point.y()));
        is_cut_rect_set = false;
    }

    cut_rect_start = !cut_rect_start;
    update_view();
}
void MainWindow::form_add_rect()
{
    bool x_s_ok, y_s_ok, x_e_ok, y_e_ok;

    int x_s = ui->input_x_s_rect->text().toInt(&x_s_ok);
    int y_s = ui->input_y_s_rect->text().toInt(&y_s_ok);

    int x_e = ui->input_x_e_rect->text().toInt(&x_e_ok);
    int y_e = ui->input_y_e_rect->text().toInt(&y_e_ok);

    if (!x_s_ok)
    {
        show_err_msg("Не введена координата x верхней левой точки отсекателя");
        return;
    }
    if (!y_s_ok)
    {
        show_err_msg("Не введена координата y верхней левой точки отсекателя");
        return;
    }

    if (!x_e_ok)
    {
        show_err_msg("Не введена координата x правой нижней точки отсекателя");
        return;
    }
    if (!y_e_ok)
    {
        show_err_msg("Не введена координата y правой нижней точки отсекателя");
        return;
    }

    add_rect(x_s, y_s, x_e, y_e);
}

void MainWindow::btn_cut_clicked()
{

}
