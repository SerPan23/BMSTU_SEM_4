#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSize sizes(250, 800);

    w.resize(sizes);
    w.setMinimumSize(sizes);
    w.setMaximumSize(sizes);

    w.show();
    return a.exec();
}
