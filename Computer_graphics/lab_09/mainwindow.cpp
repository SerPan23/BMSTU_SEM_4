#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    drawer = new Drawer(ui->graphicsView, this);

    set_preview_widget_color(ui->figure_color_preview, this->figure_color);
    set_preview_widget_color(ui->clip_color_preview, this->clip_color);
    set_preview_widget_color(ui->result_color_preview, this->result_color);


    connect(ui->btn_figure_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_figure_color_change_clicked);
    connect(ui->btn_clip_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_clip_color_change_clicked);
    connect(ui->btn_result_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_result_color_change_clicked);

    connect(ui->btn_clear, &QPushButton::clicked, this,
            &MainWindow::clear_clicked);



    connect(drawer->scene(), &MyGraphicsScene::mouseLeftBtnClicked, this,
            &MainWindow::mouse_add_figure_vertex);
    connect(ui->btn_add_figure_vertex, &QPushButton::clicked, this,
            &MainWindow::form_add_figure_vertex);

    connect(drawer->scene(), &MyGraphicsScene::mouseLeftBtnClickedWithShift, this,
            &MainWindow::mouse_close_figure);
    connect(ui->btn_close_figure, &QPushButton::clicked, this,
            &MainWindow::mouse_close_figure);


    connect(drawer->scene(), &MyGraphicsScene::mouseRightBtnClicked, this,
            &MainWindow::mouse_add_clip_vertex);
    connect(ui->btn_add_clip_vertex, &QPushButton::clicked, this,
            &MainWindow::form_add_clip_vertex);

    connect(drawer->scene(), &MyGraphicsScene::mouseRightBtnClickedWithShift, this,
            &MainWindow::mouse_close_clip);
    connect(ui->btn_close_clip, &QPushButton::clicked, this,
            &MainWindow::mouse_close_clip);



    connect(ui->btn_cut, &QPushButton::clicked, this,
            &MainWindow::btn_cut_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_x_vertex_figure->setValidator(int_validator);
    ui->input_y_vertex_figure->setValidator(int_validator);

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

void MainWindow::btn_figure_color_change_clicked()
{
    this->figure_color = QColor(QColorDialog::getColor(this->figure_color).rgb());
    set_preview_widget_color(ui->figure_color_preview, this->figure_color);
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
    ui->clip_points->clear();
    ui->figure_points->clear();
    drawer->clear();

    figure.points.clear();
    figure.lines.clear();
    figure.is_closed = false;

    clip.points.clear();
    clip.lines.clear();
    clip.is_closed = false;
}

void MainWindow::draw()
{
    drawer->draw_polygon(figure, figure_color);

    drawer->draw_polygon(clip, clip_color);
}
void MainWindow::update_view()
{
    drawer->clear();
    draw();
    drawer->render();
}

void MainWindow::add_figure_vertex(int x, int y)
{
    if (figure.is_closed)
    {
        ui->figure_points->clear();
        figure.is_closed = false;
        figure.points.clear();
        figure.lines.clear();
        update_view();
    }

    Point p(x, y);

    figure.points.push_back(p);

    figure.update_lines(p);

    write_points(figure, ui->figure_points);
    update_view();
}
void MainWindow::mouse_add_figure_vertex()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();
    add_figure_vertex(round(point.x()), round(point.y()));
}
void MainWindow::form_add_figure_vertex()
{
    bool x_ok, y_ok;

    int x = ui->input_x_vertex_figure->text().toInt(&x_ok);
    int y = ui->input_y_vertex_figure->text().toInt(&y_ok);

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

    add_figure_vertex(x, y);
}

void MainWindow::close_figure()
{
    if (figure.points.size() == 0)
    {
        show_err_msg("Фигуры не существует, ниодной точки не введено");
        return;
    }

    if (figure.points.size() < 3)
    {
        show_err_msg("Фигура не может быть замкнута, введенно менее 3-х образующих точек");
        return;
    }

    figure.is_closed = true;
    figure.update_lines(figure.points[0]);

    write_points(figure, ui->figure_points);
    update_view();
}
void MainWindow::mouse_close_figure()
{
    close_figure();
}
void MainWindow::btn_close_figure_clicked()
{
    close_figure();
}



void MainWindow::add_clip_vertex(int x, int y)
{
    if (clip.is_closed)
    {
        ui->clip_points->clear();
        clip.is_closed = false;
        clip.points.clear();
        clip.lines.clear();
        update_view();
    }

    Point p(x, y);

    clip.points.push_back(p);

    clip.update_lines(p);

    write_points(clip, ui->clip_points);
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

    write_points(clip, ui->clip_points);
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



void MainWindow::add_text_line(QString str, QPlainTextEdit *textedit)
{
    textedit->appendPlainText(str);
}

void MainWindow::write_points(polygon_t& polygon, QPlainTextEdit *textedit)
{
    textedit->clear();
    for (int i = 0; i < polygon.points.size(); i++)
    {
        QString str = QString::number(i + 1) + ") ";
        Point& tmp = polygon.points[i];
        str += QString::number(tmp.x()) + " " + QString::number(tmp.y());
        add_text_line(str, textedit);
    }
    if (polygon.is_closed)
    {
        add_text_line("--Closed--\n", textedit);
    }
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

    if (figure.points.size() == 0)
    {
        show_err_msg("Не введена фигура");
        return;
    }

    if (!figure.is_closed)
    {
        show_err_msg("Не закончен ввод фигуры");
        return;
    }

    sutherlandHodgman(drawer, clip, figure, result_color);
    drawer->render();
}
