#include "draw.h"

return_codes_t clear_scene(const draw_view_t *view)
{
    if (!view->scene)
        return ERROR_SCENE_WRONG;

    view->scene->fill();
    return SUCCESS;
}

point_t *get_normalized(point_t *p, draw_view_t *view, point_t *pmin, point_t *pmax)
{
    point_t *tmp = point_create(
        (p->x - pmin->x) / (pmax->x - pmin->x) * view->width,
        (pmax->y - p->y) / (pmax->y - pmin->y) * view->height
    );
    return tmp;
}

void transfom_min_max(draw_view_t *view, point_t *pmin, point_t *pmax)
{
    point_t pc;
    // Отступ от краев поля графика
    pc.x = (pmin->x + pmax->x) / 2;
    pmin->x = pc.x - (pc.x - pmin->x) * (BORDER_X + pmax->x / view->width + 0.1);
    pmax->x = pc.x + (pmax->x - pc.x) * (BORDER_X + pmax->x / view->width + 0.1);

    pc.y = (pmin->y + pmax->y) / 2;
    pmin->y = pc.y - (pc.y - pmin->y) * (BORDER_Y + pmax->y / view->height + 0.1);
    pmax->y = pc.y + (pmax->y - pc.y) * (BORDER_Y + pmax->y / view->height + 0.1);

    // Коэффициенты доли в экране
    double kx = (pmax->x - pmin->x) / view->width;
    double ky = (pmax->y - pmin->y) / view->height;

    if (kx < ky)
    {
        // Координаты центра растяжения
        pc.x = (pmin->x + pmax->x) / 2;
        pmin->x = pc.x - (pc.x - pmin->x) * (ky / kx);
        pmax->x = pc.x + (pmax->x - pc.x) * (ky / kx);
    }
    else
    {
        // Координаты центра растяжения
        pc.y = (pmin->y + pmax->y) / 2;
        pmin->y = pc.y  - (pc.y  - pmin->y) * (kx / ky);
        pmax->y = pc.y  + (pmax->y - pc.y ) * (kx / ky);
    }
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

return_codes_t draw_result(draw_view_t *view, triangle_t *triangle, point_t *pab, point_t *pbb, point_t *pcb, point_t *pcenters)
{
    point_t pmin = {std::min(std::min(triangle->a->x, triangle->b->x), triangle->c->x),
                    std::min(std::min(triangle->a->y, triangle->b->y), triangle->c->y)};

    point_t pmax = {std::max(std::max(triangle->a->x, triangle->b->x), triangle->c->x),
                    std::max(std::max(triangle->a->y, triangle->b->y), triangle->c->y)};

    //--for points text--
    point_t *pmin_norm = get_normalized(&pmin, view, &pmin, &pmax);
    point_t *pmax_norm = get_normalized(&pmax, view, &pmin, &pmax);
    //----


    // add border
    transfom_min_max(view, &pmin, &pmax);


    triangle_t triangle_norm = {get_normalized(triangle->a, view, &pmin, &pmax),
                                get_normalized(triangle->b, view, &pmin, &pmax),
                                get_normalized(triangle->c, view, &pmin, &pmax)};

    point_t *pab_norm = get_normalized(pab, view, &pmin, &pmax);
    point_t *pbb_norm = get_normalized(pbb, view, &pmin, &pmax);
    point_t *pcb_norm = get_normalized(pcb, view, &pmin, &pmax);
    point_t *pcenter_norm = get_normalized(pcenters, view, &pmin, &pmax);

    double r = find_inscribed_circle_radius(triangle_norm.a, triangle_norm.b, triangle_norm.c);


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
