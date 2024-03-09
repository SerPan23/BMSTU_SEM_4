#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "algorithms/algorithms.h"
#include <iostream>

void print_vector(std::vector <pixel_t> vec)
{
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i].x << " " << vec[i].y << " (" << vec[i].intensity << ")" << std::endl;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    point_t start{0, 0};
    point_t end{-8, -4};


    std::cout << "dda\n";
    print_vector(dda(start, end));

    std::cout << "bresenham_double\n";
    print_vector(bresenham_double(start, end));

    std::cout << "bresenham_integer\n";
    print_vector(bresenham_integer(start, end));

    std::cout << "bresenham_smooth\n";
    print_vector(bresenham_smooth(start, end));

    std::cout << "wu\n";
    print_vector(wu(start, end));
}

MainWindow::~MainWindow()
{
    delete ui;
}
