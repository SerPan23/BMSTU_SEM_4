#include "QtDrawer.h"

#include <QDebug>

void QtDrawer::drawLine(int x1, int y1, int x2, int y2)
{
    // qDebug() << x1 << y1 << x2 << y2 << "\n";
    scene.lock()->addLine(x1, y1, x2, y2);
}

void QtDrawer::clear()
{
    scene.lock()->clear();
}
