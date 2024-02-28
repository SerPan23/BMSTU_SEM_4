#include "draw_screen.h"

#include <QPainterPath>

QRectF rect_to_qt(rectangle_t *rect)
{
    return QRectF(
        QPointF(rect->a->x, rect->a->y),
        QPointF(rect->c->x, rect->c->y));
}

// void draw_ellipse(draw_view_t *view, shape_t *shape, double start_angle, double end_angle)
// {
//     QPainterPath path;

//     double step = 1 / std::max(shape->shape.ellipse->radius_x, shape->shape.ellipse->radius_y);

//     bool is_started = false;

//     for (double angle = start_angle; angle < end_angle; angle += step)
//     {
//         point_t *tmp = point_create(0, 0);

//         tmp->x = shape->shape.ellipse->center->x + shape->shape.ellipse->radius_x * cos(angle);
//         tmp->y = shape->shape.ellipse->center->y + shape->shape.ellipse->radius_y * sin(angle);

//         if (!is_started)
//         {
//             path.moveTo(tmp->x, tmp->y);
//             is_started = true;
//         }
//         else
//             path.lineTo(tmp->x, tmp->y);
//     }


//     view->painter->drawPath(path);
// }

double get_rounded(double n)
{
    return round(n);
}

void draw_ellipse(draw_view_t *view, shape_t *shape)
{
    QPainterPath path;

    int size;

    if (shape->type == ELLIPSE)
        size = shape->shape.ellipse->points.size();

    if (shape->type == ARC)
        size = shape->shape.arc->points.size();

    bool is_started = false;

    for (int i = 0; i < size; i++)
    {
        point_t *tmp;

        if (shape->type == ELLIPSE)
            tmp = shape->shape.ellipse->points[i];

        if (shape->type == ARC)
            tmp = shape->shape.arc->points[i];

        if (!is_started)
        {
            path.moveTo(get_rounded(tmp->x), get_rounded(tmp->y));
            is_started = true;
        }
        else
            path.lineTo(get_rounded(tmp->x), get_rounded(tmp->y));
    }

    if (shape->type == ELLIPSE && is_started)
        path.closeSubpath();

    view->painter->drawPath(path);
}

void draw_shape(draw_view_t *view, shape_t *shape, QColor color)
{
    QPen pen(color);
    switch (shape->type)
    {
    case POINT:
        pen.setWidth(1);
        view->painter->setPen(pen);
        view->painter->drawPoint(get_rounded(shape->shape.point->x),
                                 get_rounded(shape->shape.point->y));
        break;

    case ARC:
        pen.setWidth(1);
        view->painter->setPen(pen);
        // draw_ellipse(view, shape, to_rad(shape->shape.arc->start_ang) + M_PI,
        //              to_rad(shape->shape.arc->start_ang + shape->shape.arc->span_ang) + M_PI);
        draw_ellipse(view, shape);
        break;

    case ELLIPSE:
        pen.setWidth(1);
        view->painter->setPen(pen);
        draw_ellipse(view, shape);
        break;

    case LINE:
        pen.setWidth(shape->shape.line->width);
        view->painter->setPen(pen);
        view->painter->drawLine(
            get_rounded(shape->shape.line->start->x), get_rounded(shape->shape.line->start->y),
            get_rounded(shape->shape.line->end->x), get_rounded(shape->shape.line->end->y));
        break;
    }
}

void draw(draw_view_t *view, figure_t *figure)
{
    draw(view, figure, Qt::black);
}

void draw(draw_view_t *view, figure_t *figure, QColor color)
{
    for (size_t i = 0; i < figure->shapes.size; i++)
        draw_shape(view, figure->shapes.data[i], color);
}
