#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pxp = QPixmap(ui->graphic_lable->width(), ui->graphic_lable->height());
    pxp.fill();
    ui->graphic_lable->setPixmap(pxp);


    connect(ui->btn_get_result, &QPushButton::clicked, this,
            &MainWindow::get_result_clicked);

    connect(ui->btn_add_point, &QPushButton::clicked, this,
            &MainWindow::add_point);

    connect(ui->btn_del_point, &QPushButton::clicked, this,
            &MainWindow::del_point);

    connect(ui->btn_del_points, &QPushButton::clicked, this,
            &MainWindow::del_all_points);

    connect(ui->btn_task, &QPushButton::clicked, this,
            &MainWindow::show_task);

    points_alloc(&this->points, 10);
}

MainWindow::~MainWindow()
{
    points_free(&this->points);
    delete ui;
}

return_codes_t MainWindow::draw()
{
    ui->graphic_lable->setPixmap(this->pxp);

    return SUCCESS;
}

void MainWindow::get_result_clicked()
{
    this->pxp.fill();
    triangle_t triangle;
    double minn = 0;
    bool flag = true;

    for (size_t i = 0; i < this->points.size; i++)
    {
        for (size_t j = i + 1; j < this->points.size; j++)
        {
            for (size_t k = j + 1; k < this->points.size; k++)
            {
                point_t *pa = this->points.data[i];
                point_t *pb = this->points.data[j];
                point_t *pc = this->points.data[k];
                if (is_triangle(pa, pb, pc))
                {
                    double r = find_inscribed_circle_radius(pa, pb, pc);
                    double cs = circle_sqr(r);
                    double ts = triangle_sqr(pa, pb, pc);
                    if (flag || minn > ts - cs)
                    {
                        flag = false;
                        minn = ts - cs;
                        triangle.a = pa;
                        triangle.b = pb;
                        triangle.c = pc;
                    }
                }
            }
        }
    }

    point_t *pab = find_bisector_on_front_side(triangle.a, triangle.b, triangle.c);
    point_t *pbb = find_bisector_on_front_side(triangle.b, triangle.a, triangle.c);
    point_t *pcb = find_bisector_on_front_side(triangle.c, triangle.a, triangle.b);
    point_t *pcenter = find_line_cross(triangle.a, pab, triangle.b, pbb);

    QPainter painter(&this->pxp);
    double h = (double)painter.device()->height();
    double w = (double)painter.device()->width();
    draw_view_t view = {
        .scene = &this->pxp,
        .painter = &painter,
        .width = w,
        .height = h,
    };

    draw_result(&view, &triangle, pab, pbb, pcb, pcenter);

    draw();
}

void MainWindow::add_point()
{
    double x = ui->input_X->value();
    double y = ui->input_Y->value();

    auto table = ui->table_points;

    table->insertRow ( table->rowCount() );
    table->setItem   ( table->rowCount()-1,
                         0,
                         new QTableWidgetItem(QString::number(x)));
    table->setItem   ( table->rowCount()-1,
                         1,
                         new QTableWidgetItem(QString::number(y)));

    point_t *p = point_create(x, y);

    points_push(&this->points, p);
}

void MainWindow::del_point()
{
    int index = ui->input_index->value();
    ui->table_points->removeRow(index);

    points_pop(&this->points, index);
}

void MainWindow::del_all_points()
{

}

void MainWindow::show_task()
{
    QMessageBox::information(NULL, "Условие задачи",
                             "Найти минимальную разность площадей между площадь треугольника "
                             "и вписанной в него окружностью.");
}

