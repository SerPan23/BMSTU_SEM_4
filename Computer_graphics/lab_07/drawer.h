#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QGraphicsView>

#include "mygraphicsscene.h"

#include "point.h"

struct line
{
    Point start;
    Point end;
};

using line_t = struct line;

using lines_t = std::vector<line_t>;

struct rect
{
    Point p1;
    Point p2;
};

using rect_t = struct rect;

class Drawer
{
public:
    Drawer(QGraphicsView *view, QObject *parent = nullptr);

    void draw_point(int x, int y, QColor& color);
    void draw_point(Point &p, QColor& color);
    void draw_line(Point &start, Point &end, QColor& color);
    void draw_lines(lines_t &lines, QColor& color);
    void draw_rect(rect_t &rect, QColor& color);


    QColor get_pixel_color(const Point &position) const;
    QColor get_pixel_color(int x, int y) const;

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
