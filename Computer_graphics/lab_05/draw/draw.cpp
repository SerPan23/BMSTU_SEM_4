#include "draw.h"

// #include <iostream>

void draw_line(draw_view_t& view, QColor& color, Point& start, Point& end)
{
    QPainter painter(view.scene);
    QPen pen(color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(start.getX(), start.getY(), end.getX(), end.getY());

    // std::cout << start.getX() << " " << start.getY() << " | " << end.getX() << " " << end.getY() << std::endl;
}

void draw_figure(draw_view_t& view, QColor& color, Figure& figure)
{
    for (int i = 1; i < figure.size(); i++)
        draw_line(view, color, figure.get_point(i - 1), figure.get_point(i));

    if (figure.is_closed())
        draw_line(view, color, figure.get_point(figure.size() - 1), figure.get_point(0));
}
