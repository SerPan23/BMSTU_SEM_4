#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QGraphicsView>

#include <vector>

#include "mygraphicsscene.h"

#include "point.h"


class Drawer
{
public:
    Drawer(QGraphicsView *view, QObject *parent = nullptr);

    void draw_point(int x, int y, QColor& color);
    void draw_point(Point &p, QColor& color);
    void draw_line(Point &start, Point &end, QColor& color);
    void draw_line(int x1, int y1, int x2, int y2, QColor& color);

    void clear();
    void render();

    MyGraphicsScene *scene();

    int width();
    int height();

private:
    MyGraphicsScene *_scene;
    QPixmap _pxp;

    int _width;
    int _height;
};

#endif // DRAWER_H
