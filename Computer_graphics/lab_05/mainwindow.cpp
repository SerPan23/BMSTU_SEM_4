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

    connect(ui->btn_clear_screen, &QPushButton::clicked, this,
            &MainWindow::clear_screen);


    connect(scene, &MyGraphicsScene::mouseLeftBtnClicked, this,
            &MainWindow::mouse_add_dot);

    connect(scene, &MyGraphicsScene::mouseRightBtnClicked, this,
            &MainWindow::mouse_close_figure);


    connect(ui->btn_close_figure, &QPushButton::clicked, this,
            &MainWindow::btn_close_figure_clicked);


    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto int_validator = new QIntValidator;
    int_validator->setLocale(locale);

    ui->input_x->setValidator(int_validator);
    ui->input_y->setValidator(int_validator);
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

void MainWindow::clear_screen()
{
    this->pxp = QPixmap(ui->graphicsView->scene()->width(), ui->graphicsView->scene()->height());
    this->pxp.fill(Qt::transparent);


    ui->graphicsView->scene()->clear();
}

void MainWindow::add_dot(int x, int y)
{
    current_figure.add_point(Point(x, y));

    write_figures_list();
}
void MainWindow::mouse_add_dot()
{
    MyGraphicsScene *scene = (MyGraphicsScene *)ui->graphicsView->scene();
    QPointF point = scene->get_mouse_pos();
    add_dot(round(point.x()), round(point.x()));
}
void MainWindow::form_add_dot()
{

}

void MainWindow::close_figure()
{
    //TODO: add checks

    current_figure.closed();
    this->closed_figures.push_back(current_figure);
    current_figure.clear();

    write_figures_list();
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
