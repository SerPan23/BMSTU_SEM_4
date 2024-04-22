#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QTime>
#include <QCoreApplication>

#include <stack>

#include "drawer.h"


void fill_with_seed(Drawer *drawer, Point &seed, QColor &fill_color, QColor &border_color, int delay=0);

#endif // ALGORITHM_H
