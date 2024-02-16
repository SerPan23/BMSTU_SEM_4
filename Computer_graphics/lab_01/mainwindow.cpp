#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "itemdelegate.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pxp = QPixmap(ui->graphic_lable->width(), ui->graphic_lable->height());
    pxp.fill();
    ui->graphic_lable->setPixmap(pxp);

    ItemDelegate *itDelegate = new  ItemDelegate;
    ui->table_points->setItemDelegate(itDelegate);

    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto validator = new QDoubleValidator;
    validator->setLocale(locale);

    ui->input_X->setValidator(validator);
    ui->input_Y->setValidator(validator);

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

    connect(ui->table_points, &QTableWidget::cellChanged, this,
            &MainWindow::edit_table);

}

void MainWindow::edit_table()
{
    this->ui->lable_answer->setText("");
    clear_draw();
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

void MainWindow::clear_draw()
{
    this->pxp.fill();
    draw();
}

void MainWindow::read_table()
{
    if (this->points.size > 0)
        points_clear(&this->points);

    for (size_t i = 0; i < this->ui->table_points->rowCount(); i++)
    {
        QString text_x = this->ui->table_points->item(i, 0)->text();
        QString text_y = this->ui->table_points->item(i, 1)->text();

        point_t *p = point_create(text_x.toDouble(), text_y.toDouble());
        points_push(&this->points, p);
    }
}

void MainWindow::get_result_clicked()
{
    clear_draw();
    read_table();

    if (this->points.size < 3)
    {
        this->ui->lable_answer->setText("Не достаточно точек для вычислений!");
    }
    else
    {
        this->pxp.fill();
        triangle_t triangle;
        double minn = 0;
        double mcs, mts;
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
                            mcs = cs;
                            mts = ts;
                        }
                    }
                }
            }
        }

        if (flag)
        {
            this->ui->lable_answer->setText("Не найдено ни одного треугольника!");
        }
        else
        {
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

            this->ui->lable_answer->setText("Площадь треугольника = " + QString::number(mts) + "\n" +
                                            "Площадь круга = " + QString::number(mcs) + "\n" +
                                            "Их разность = " + QString::number(mts - mcs));
        }
    }
}

void MainWindow::add_point()
{
    clear_draw();
    bool x_ok, y_ok;

    double x = ui->input_X->text().toDouble(&x_ok);
    double y = ui->input_Y->text().toDouble(&y_ok);


    if (x_ok && y_ok)
    {
        auto table = ui->table_points;

        table->insertRow ( table->rowCount() );
        table->setItem   ( table->rowCount()-1,
                       0,
                       new QTableWidgetItem(QString::number(x)));
        table->setItem   ( table->rowCount()-1,
                       1,
                       new QTableWidgetItem(QString::number(y)));

        this->ui->lable_answer->setText("Точка (" + QString::number(x) + "; "
                                        + QString::number(y) + ") успешно добавленна\n");
    }
    else
    {
        this->ui->lable_answer->setText("Координаты одной из точки не указаны\nили введенны не верно\n");
    }

    // point_t *p = point_create(x, y);

    // points_push(&this->points, p);
}

void MainWindow::del_point()
{
    clear_draw();
    int index = ui->input_index->value() - 1;
    if (index < 0 || index >= this->ui->table_points->rowCount())
    {
        this->ui->lable_answer->setText("Точки под таким номером не существует!");
    }
    else
    {
        QString text_x = this->ui->table_points->item(index, 0)->text();
        QString text_y = this->ui->table_points->item(index, 1)->text();

        ui->table_points->removeRow(index);

        this->ui->lable_answer->setText("Точка (" + text_x + "; " + text_y + ") успешно удаленна\n");

        // double x = this->points.data[index - 1]->x;
        // double y = this->points.data[index - 1]->y;
        // points_pop(&this->points, index - 1);
        // this->ui->lable_answer->setText("Точка (" + QString::number(x) + "; "
        //                                 + QString::number(y) + ") успешно удаленна\n");
    }
}

void MainWindow::del_all_points()
{
    // size_t size = this->points.size;
    clear_draw();
    size_t size = this->ui->table_points->rowCount();
    if (size == 0)
        this->ui->lable_answer->setText("Список точек пуст!");
    else
    {
        for (size_t i = 0; i < size; i++)
        {
            ui->table_points->removeRow(0);
            // points_pop(&this->points, 0);
        }
        this->ui->lable_answer->setText("Все точки успешно удаленны\n");
    }
}

void MainWindow::show_task()
{
    QMessageBox::information(NULL, "Условие задачи",
                             "Найти треугольник с минимальной разностью площадей между площадь "
                             "самого треугольника и вписанной в него окружностью.");
}

