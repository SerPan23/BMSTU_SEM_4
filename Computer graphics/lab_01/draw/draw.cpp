#include "draw.h"

return_codes_t clear_scene(const draw_view_t *view)
{
    if (!view->scene)
        return ERROR_SCENE_WRONG;

    view->scene->fill();
    return SUCCESS;
}

return_codes_t draw_line(draw_view_t *view, point_t *p1, point_t *p2)
{
    if (!view->scene)
        return ERROR_SCENE_WRONG;

    view->painter->drawLine(p1->x, p1->y, p2->x, p2->y);
    return SUCCESS;
}

return_codes_t draw_point_cords(draw_view_t *view, point_t *p1_norm, point_t *p1, point_t *pmin_norm, point_t *pmax_norm)
{
    if (!view->scene)
        return ERROR_SCENE_WRONG;

    // view->painter->drawPoint(p1_norm->x, p1_norm->y);

    QPen pen(Qt::darkYellow);
    view->painter->setPen(pen);
    view->painter->setFont(QFont("Courier New", 14, 5));

    // point_t ptext = {p1_norm->x + 5, p1_norm->y - 10};

    point_t ptext = {p1_norm->x + 5, p1_norm->y - 10};

    QString text = "(" + QString::number(p1->x, 'f',2) + "; "
                   + QString::number(p1->y, 'f', 2) + ")";

    if ((ptext.x + text.size() * 8) >= pmax_norm->x)
        ptext.x -= (ptext.x + text.size() * 8) - pmax_norm->x;

    if (ptext.x <=  pmin_norm->x)
        ptext.x += pmin_norm->x - ptext.x;


    view->painter->drawText(ptext.x, ptext.y, text);

    // pen.setColor(Qt::red);
    // pen.setWidth(1);
    // view->painter->setPen(pen);

    // point_t p2 = {, p1_norm->y};
    // draw_line(view, &ptext, &p2);


    return SUCCESS;
}

void draw_triangle(draw_view_t *view, triangle_t *triangle_norm, triangle_t *triangle)
{
    draw_line(view, triangle_norm->a, triangle_norm->b);
    draw_line(view, triangle_norm->a, triangle_norm->c);
    draw_line(view, triangle_norm->b, triangle_norm->c);
}

point_t *transform_to_screen(draw_view_t *view, point_t *point, point_t *scale_center, point_t *scale)
{
    point_t *tmp = point_scale(point, scale_center, scale);

    tmp->x += view->width / 2 - scale_center->x ;
    tmp->y += view->height / 2 - scale_center->y ;

    tmp->y = (-1) * tmp->y + view->height;

    return tmp;
}

return_codes_t draw_result(draw_view_t *view, triangle_t *triangle, point_t *pab, point_t *pbb, point_t *pcb, point_t *pcenters)
{
    point_t pmin = {std::min(std::min(triangle->a->x, triangle->b->x), triangle->c->x),
                    std::min(std::min(triangle->a->y, triangle->b->y), triangle->c->y)};

    point_t pmax = {std::max(std::max(triangle->a->x, triangle->b->x), triangle->c->x),
                    std::max(std::max(triangle->a->y, triangle->b->y), triangle->c->y)};

    point_t p1 = {pmin.x, pmax.y};
    point_t p2 = {pmax.x, pmin.y};

    point_t *scale_center = find_line_cross(&pmin, &pmax, &p1, &p2);

    double max_size = std::max(pmax.x - pmin.x, pmax.y - pmin.y);
    double min_size_screen = std::max(view->height, view->width);
    double k = min_size_screen / max_size * 0.8;

    point_t scale = {k, k};


    triangle_t triangle_norm = {transform_to_screen(view, triangle->a, scale_center, &scale),
                                transform_to_screen(view, triangle->b, scale_center, &scale),
                                transform_to_screen(view, triangle->c, scale_center, &scale)};

    point_t *pab_norm = transform_to_screen(view, pab, scale_center, &scale);
    point_t *pbb_norm = transform_to_screen(view, pbb, scale_center, &scale);
    point_t *pcb_norm = transform_to_screen(view, pcb, scale_center, &scale);
    point_t *pcenter_norm = transform_to_screen(view, pcenters, scale_center, &scale);

    double r = find_inscribed_circle_radius(triangle_norm.a, triangle_norm.b, triangle_norm.c);

    point_t *pmin_norm = transform_to_screen(view, &pmin, scale_center, &scale);
    point_t *pmax_norm = transform_to_screen(view, &pmax, scale_center, &scale);


    // draw
    QPen pen(Qt::black);
    pen.setWidth(2);
    view->painter->setPen(pen);

    draw_triangle(view, &triangle_norm, triangle);

    draw_point_cords(view, triangle_norm.a, triangle->a, pmin_norm, pmax_norm);
    draw_point_cords(view, triangle_norm.b, triangle->b, pmin_norm, pmax_norm);
    draw_point_cords(view, triangle_norm.c, triangle->c, pmin_norm, pmax_norm);

    pen.setColor(Qt::green);
    view->painter->setPen(pen);

    draw_line(view, triangle_norm.a, pab_norm);
    draw_line(view, triangle_norm.b, pbb_norm);
    draw_line(view, triangle_norm.c, pcb_norm);

    draw_point_cords(view, pcenter_norm, pcenters, pmin_norm, pmax_norm);

    pen.setColor(Qt::blue);
    view->painter->setPen(pen);

    view->painter->drawEllipse(pcenter_norm->x - r, pcenter_norm->y - r, r * 2, r * 2);
    //------


    point_free(&pab_norm);
    point_free(&pbb_norm);
    point_free(&pcb_norm);
    point_free(&pcenter_norm);
    triangle_free(&triangle_norm);
    return SUCCESS;
}
