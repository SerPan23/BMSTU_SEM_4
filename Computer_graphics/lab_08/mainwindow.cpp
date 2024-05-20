#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawer = new Drawer(ui->graphicsView, this);

    set_preview_widget_color(ui->line_color_preview, this->line_color);
    set_preview_widget_color(ui->clip_color_preview, this->clip_color);
    set_preview_widget_color(ui->result_color_preview, this->result_color);


    connect(ui->btn_line_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_line_color_change_clicked);
    connect(ui->btn_clip_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_clip_color_change_clicked);
    connect(ui->btn_result_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_result_color_change_clicked);

    connect(ui->btn_clear, &QPushButton::clicked, this,
            &MainWindow::clear_clicked);



    connect(drawer->scene(), &MyGraphicsScene::mouseLeftBtnClicked, this,
            &MainWindow::mouse_add_line);

    connect(ui->btn_add_line, &QPushButton::clicked, this,
            &MainWindow::form_add_line);


    connect(drawer->scene(), &MyGraphicsScene::mouseRightBtnClicked, this,
            &MainWindow::mouse_add_clip_vertex);

    connect(drawer->scene(), &MyGraphicsScene::mouseRightBtnClickedWithShift, this,
            &MainWindow::mouse_close_clip);



    connect(ui->btn_cut, &QPushButton::clicked, this,
            &MainWindow::btn_cut_clicked);



    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_x_s_line->setValidator(int_validator);
    ui->input_y_s_line->setValidator(int_validator);
    ui->input_x_e_line->setValidator(int_validator);
    ui->input_y_e_line->setValidator(int_validator);

    ui->input_x_vertex_clip->setValidator(int_validator);
    ui->input_y_vertex_clip->setValidator(int_validator);
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
void MainWindow::btn_clip_color_change_clicked()
{
    this->clip_color = QColor(QColorDialog::getColor(this->clip_color).rgb());
    set_preview_widget_color(ui->clip_color_preview, this->clip_color);
}
void MainWindow::btn_result_color_change_clicked()
{
    this->result_color = QColor(QColorDialog::getColor(this->result_color).rgb());
    set_preview_widget_color(ui->result_color_preview, this->result_color);
}

void MainWindow::clear_clicked()
{
    drawer->clear();

    lines.clear();
    cur_line_start = false;

    clip.points.clear();
    clip.lines.clear();
    clip.is_closed = false;
}

void MainWindow::draw()
{
    drawer->draw_lines(lines, line_color);
    drawer->draw_clip(clip, clip_color);
}
void MainWindow::update_view()
{
    drawer->clear();
    draw();
    drawer->render();
}

void MainWindow::add_line(int x_s, int y_s, int x_e, int y_e)
{
    line_t line;
    line.start = Point(x_s, y_s);
    line.end = Point(x_e, y_e);

    lines.push_back(line);
    cur_line_start = false;

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
        ui->input_x_e_line->setText(QString::number(cur_line.end.x()));
        ui->input_y_e_line->setText(QString::number(cur_line.end.y()));
        update_view();
    }
    else
    {
        cur_line.start = Point(round(point.x()), round(point.y()));
        ui->input_x_s_line->setText(QString::number(cur_line.start.x()));
        ui->input_y_s_line->setText(QString::number(cur_line.start.y()));
    }

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

void MainWindow::add_clip_vertex(int x, int y)
{
    if (clip.is_closed)
    {
        clip.is_closed = false;
        clip.points.clear();
        clip.lines.clear();
        update_view();
    }

    Point p(x, y);

    clip.points.push_back(p);

    clip.update_lines(p);

    update_view();
}
void MainWindow::mouse_add_clip_vertex()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();
    add_clip_vertex(round(point.x()), round(point.y()));
}
void MainWindow::form_add_clip_vertex()
{
    bool x_ok, y_ok;

    int x = ui->input_x_vertex_clip->text().toInt(&x_ok);
    int y = ui->input_y_vertex_clip->text().toInt(&y_ok);

    if (!x_ok)
    {
        show_err_msg("Не введена координата x вершины");
        return;
    }
    if (!y_ok)
    {
        show_err_msg("Не введена координата y вершины");
        return;
    }

    add_clip_vertex(x, y);
}

void MainWindow::close_clip()
{
    if (clip.points.size() == 0)
    {
        show_err_msg("Отсекателя не существует, ниодной точки не введено");
        return;
    }

    if (clip.points.size() < 3)
    {
        show_err_msg("Отсекатель не может быть замкнута, введенно менее 3-х образующих точек");
        return;
    }

    clip.is_closed = true;
    clip.update_lines(clip.points[0]);

    update_view();
}
void MainWindow::mouse_close_clip()
{
    close_clip();
}
void MainWindow::btn_close_clip_clicked()
{
    close_clip();
}

void MainWindow::btn_cut_clicked()
{

    if (clip.points.size() == 0)
    {
        show_err_msg("Не введен отсекатель");
        return;
    }

    if (!clip.is_closed)
    {
        show_err_msg("Не закончен ввод отсекателя");
        return;
    }

    if (!check_convex(clip) || check_cross(clip))
    {
        show_err_msg("Введен не корректный отсекатель");
        return;
    }

    if (cur_line_start)
    {
        show_err_msg("Не закончен ввод отрезка");
        return;
    }


    // simple_cut(drawer, cut_rect, lines, result_color);
    cyrus_beck_cut(drawer, clip, lines, result_color);
    drawer->render();
}
