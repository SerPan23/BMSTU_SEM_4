#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");


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
}

MainWindow::~MainWindow()
{
    delete ui;
}

return_codes_t MainWindow::draw()
{
    auto rcontent = ui->graphicsView->contentsRect();
    ui->graphicsView->scene()->setSceneRect(0, 0, rcontent.width(),
                                            rcontent.height());

    return SUCCESS;
}

void MainWindow::get_result_clicked()
{

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
}

void MainWindow::del_point()
{
    double index = ui->input_index->value();
    ui->table_points->removeRow(index);
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

