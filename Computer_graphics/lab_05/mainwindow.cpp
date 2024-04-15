#include "mainwindow.h"
#include "./ui_mainwindow.h"

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


    clear_screen();


    set_preview_widget_color(ui->fill_color_preview, this->fill_color);


    connect(ui->btn_fill_color_change, &QPushButton::clicked, this,
            &MainWindow::btn_fill_color_change_clicked);

    connect(ui->btn_remove_fill, &QPushButton::clicked, this,
            &MainWindow::remove_fiil);

    connect(ui->btn_clear, &QPushButton::clicked, this,
            &MainWindow::clear_all);


    connect(scene, &MyGraphicsScene::mouseLeftBtnClicked, this,
            &MainWindow::mouse_add_dot);

    connect(scene, &MyGraphicsScene::mouseRightBtnClicked, this,
            &MainWindow::mouse_close_figure);


    connect(ui->btn_close_figure, &QPushButton::clicked, this,
            &MainWindow::btn_close_figure_clicked);

    connect(ui->btn_add_dot, &QPushButton::clicked, this,
            &MainWindow::form_add_dot);


    connect(ui->btn_fill, &QPushButton::clicked, this,
            &MainWindow::btn_fill_clicked);

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_x->setValidator(int_validator);
    ui->input_y->setValidator(int_validator);
    ui->delay_time->setValidator(int_validator);
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

void MainWindow::btn_fill_color_change_clicked()
{
    this->fill_color = QColorDialog::getColor(this->fill_color);
    set_preview_widget_color(ui->fill_color_preview, this->fill_color);
}

void MainWindow::remove_fiil()
{
    clear_screen();
    draw_carcas();
    draw();
}

void MainWindow::clear_all()
{
    ui->figures_list->clear();
    clear_screen();
    current_figure.clear();
    closed_figures.clear();
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

void MainWindow::draw_carcas()
{
    // clear_screen();

    draw_view_t view = {
        .view = ui->graphicsView,
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    QColor color = Qt::black;

    for (int i = 0; i < closed_figures.size(); i++)
        draw_figure(view, color, closed_figures[i]);

    draw_figure(view, color, current_figure);
}

void MainWindow::update_view()
{
    write_figures_list();
    draw_carcas();
    draw();
}

void MainWindow::add_dot(int x, int y)
{
    current_figure.add_point(Point(x, y));

    update_view();
}
void MainWindow::mouse_add_dot()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();
    add_dot(round(point.x()), round(point.y()));
}
void MainWindow::form_add_dot()
{
    bool x_ok, y_ok;

    int x = ui->input_x->text().toInt(&x_ok);
    int y = ui->input_y->text().toInt(&y_ok);

    if (!x_ok)
    {
        show_err_msg("Не введена координата x точки");
        return;
    }
    if (!y_ok)
    {
        show_err_msg("Не введена координата y точки");
        return;
    }

    add_dot(x, y);
}

void MainWindow::close_figure()
{
    if (current_figure.size() == 0)
    {
        show_err_msg("Фигуры не существует, ниодной точки не введено");
        return;
    }

    if (current_figure.size() < 3)
    {
        show_err_msg("Фигура не может быть замкнута, введенно менее 3-х образующих точек");
        return;
    }

    current_figure.close();
    this->closed_figures.push_back(current_figure);

    current_figure.clear();

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

void MainWindow::add_text_line(QString str)
{
    // ui->figures_list->moveCursor(QTextCursor::End);
    // ui->figures_list->insertPlainText(str);
    // ui->figures_list->moveCursor (QTextCursor::End);
    ui->figures_list->appendPlainText(str);
}

void MainWindow::write_figure(Figure& figure)
{
    for (int i = 0; i < figure.size(); i++)
    {
        QString str = QString::number(i + 1) + ") ";
        Point& tmp = figure.get_point(i);
        str += QString::number(tmp.getX()) + " " + QString::number(tmp.getY());
        add_text_line(str);
    }
}

void MainWindow::write_figures_list()
{
    ui->figures_list->clear();
    for (int i = 0; i < closed_figures.size(); i++)
    {
        write_figure(closed_figures[i]);
        add_text_line("--Closed--\n");
    }

    write_figure(current_figure);
}

void MainWindow::btn_fill_clicked()
{
    if (current_figure.size() > 0 && !current_figure.is_closed())
    {
        show_err_msg("Замкните все фигуры");
        return;
    }

    if (closed_figures.empty())
    {
        show_err_msg("Не введено ниодной фигуры");
        return;
    }

    bool delay = ui->is_delay->isChecked();

    bool delay_time_ok;

    int delay_time = ui->delay_time->text().toInt(&delay_time_ok);

    if (delay)
    {
        if (!delay_time_ok)
        {
            show_err_msg("Не введено время задержки");
            return;
        }

        if (delay_time_ok && delay_time < 0)
        {
            show_err_msg("Время задержки не может быть отрицательным числом");
            return;
        }
    }


    clear_screen();

    draw_view_t view = {
        .view = ui->graphicsView,
        .scene = &this->pxp,
        .width = ui->graphicsView->scene()->width(),
        .height = ui->graphicsView->scene()->height(),
    };

    double time = fill_with_cap(view, this->fill_color, this->closed_figures, delay, delay_time);

    if (!delay)
        QMessageBox::information(NULL, "Время закрашивания", QString::number(time) + " мс");

    // draw_carcas();

    // draw();
}
