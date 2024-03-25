#include "draw.h"
#include <QGraphicsLineItem>

void draw_line(draw_view_t *view, QColor color, point_t start, point_t end)
{
    QPainter painter(view->scene);
    QPen pen(color);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(start.x, start.y, end.x, end.y);

    // pen.setColor(Qt::red);
    // painter.setPen(pen);
    // painter.drawLine(start.x, start.y, start.x, start.y);
    // painter.drawLine(end.x, end.y, end.x, end.y);
    // std::cout << "\t*" << start.x << " " << start.y << " | " << end.x << " " << end.y << std::endl;
}

void draw_line(draw_view_t *view, QColor color, line_t line)
{
    QPainter painter(view->scene);
    for (int i = 0; i < line.pixels.size(); i++)
    {
        /*QColor::setAlpha(color, intensity)*/
        color.setAlpha(line.pixels[i].intensity);
        QPen pen(color);
        painter.setPen(pen);
        painter.drawLine(line.pixels[i].x, line.pixels[i].y, line.pixels[i].x, line.pixels[i].y);
    }
}
