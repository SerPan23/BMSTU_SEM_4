#include "draw_screen.h"

#include <QPainterPath>

QRectF rect_to_qt(rectangle_t *rect)
{
    return QRectF(
        QPointF(rect->a->x, rect->a->y),
        QPointF(rect->c->x, rect->c->y));
}

void draw_ellipse(draw_view_t *view, shape_t *shape, double start_angle, double end_angle)
{
    QPainterPath path;

    double step = 1 / std::max(shape->shape.ellipse->radius_x, shape->shape.ellipse->radius_y);

    bool is_started = false;

    for (double angle = start_angle; angle < end_angle; angle += step)
    {
        point_t *tmp = point_create(0, 0);

        tmp->x = shape->shape.ellipse->center->x + shape->shape.ellipse->radius_x * cos(angle);
        tmp->y = shape->shape.ellipse->center->y + shape->shape.ellipse->radius_y * sin(angle);

        if (!is_started)
        {
            path.moveTo(tmp->x, tmp->y);
            is_started = true;
        }
        else
            path.lineTo(tmp->x, tmp->y);
    }


    view->painter->drawPath(path);
}

void draw_shape(draw_view_t *view, shape_t *shape)
{
    QPen pen(Qt::black);
    switch (shape->type)
    {
    case POINT:
        pen.setWidth(1);
        view->painter->setPen(pen);
        view->painter->drawPoint(round(shape->shape.point->x), round(shape->shape.point->y));
        break;

    // case ARC:
    //     pen.setWidth(1);
    //     view->painter->setPen(pen);
    //     view->painter->drawArc(rect_to_qt(shape->shape.arc->rect),
    //                            shape->shape.arc->start_ang * 16, shape->shape.arc->span_ang * 16);
    //     break;

    case ARC:
        pen.setWidth(1);
        view->painter->setPen(pen);
        draw_ellipse(view, shape, to_rad(shape->shape.arc->start_ang) + M_PI,
                     to_rad(shape->shape.arc->start_ang + shape->shape.arc->span_ang) + M_PI);
        break;

    // case ELLIPSE:
    //     pen.setWidth(1);
    //     view->painter->setPen(pen);
    //     view->painter->drawEllipse(rect_to_qt(shape->shape.ellipse->rect));
    //     break;
    case ELLIPSE:
        pen.setWidth(1);
        view->painter->setPen(pen);
        draw_ellipse(view, shape, 0, 2 * M_PI);
        break;

    case LINE:
        pen.setWidth(shape->shape.line->width);
        view->painter->setPen(pen);
        view->painter->drawLine(
            round(shape->shape.line->start->x), round(shape->shape.line->start->y),
            round(shape->shape.line->end->x), round(shape->shape.line->end->y));
        break;
    }
}

void draw(draw_view_t *view, figure_t *figure)
{
    for (size_t i = 0; i < figure->shapes.size; i++)
        draw_shape(view, figure->shapes.data[i]);
}
