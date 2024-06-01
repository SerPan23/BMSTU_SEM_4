#ifndef DRAWER_H
#define DRAWER_H

#include <QPainter>
#include <QGraphicsView>

#include <vector>

#include "mygraphicsscene.h"

#include "point.h"

struct line
{
    Point start;
    Point end;

    bool is_full() { return !(start.is_null() || end.is_null()); };
    bool is_full() const { return !(start.is_null() || end.is_null()); };
};

using line_t = struct line;

using lines_t = std::vector<line_t>;

struct polygon
{
    std::vector<Point> points;
    lines_t lines;
    bool is_closed = false;

    void update_lines(Point &p)
    {
        if (lines.empty()) {
            lines.push_back({});
            lines[0].start = p;
        } else {
            size_t last = lines.size() - 1;
            lines[last].end = p;
            if (!is_closed) {
                lines.push_back({});
                lines[++last].start = p;
            }
        }
    }
};

using polygon_t = struct polygon;

class Drawer
{
public:
    Drawer(QGraphicsView *view, QObject *parent = nullptr);

    void draw_point(int x, int y, QColor& color);
    void draw_point(Point &p, QColor& color);
    void draw_line(Point &start, Point &end, QColor& color);
    void draw_lines(lines_t &lines, QColor& color);
    void draw_polygon(polygon_t &polygon, QColor& color);


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
