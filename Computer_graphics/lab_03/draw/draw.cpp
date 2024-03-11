#include "draw.h"

void draw_line(draw_view_t *view, QColor color, point_t start, point_t end)
{
    QPainter painter(view->scene);
    QPen pen(color);
    painter.setPen(pen);
    painter.drawLine(start.x, start.y, end.x, end.y);
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
