#include "draw.h"

static void set_pixel(draw_view_t& view, QColor &color, pixel_t pixel)
{
    QPainter painter(view.scene);
    color.setAlpha(pixel.intensity);
    QPen pen(color);
    painter.setPen(pen);
    painter.drawLine(pixel.x, pixel.y, pixel.x, pixel.y);
}

static void set_symmetric_pixels(draw_view_t& view, QColor &color, pixel_t& pixel, pixel_t center, bool is_circle)
{

    if (is_circle)
    {
        set_pixel(view, color,
                  pixel_create(pixel.y - center.y + center.x,
                               pixel.x - center.x + center.y
                               ));

        set_pixel(view, color,
                  pixel_create(-pixel.y + center.y + center.x,
                               pixel.x - center.x + center.y
                               ));

        set_pixel(view, color,
                  pixel_create(pixel.y - center.y + center.x,
                               -pixel.x + center.x + center.y
                               ));

        set_pixel(view, color,
                  pixel_create(-pixel.y + center.y + center.x,
                               -pixel.x + center.x + center.y
                               ));
    }
    set_pixel(view, color, pixel);

    set_pixel(view, color,
              pixel_create(-pixel.x + 2 * center.x, pixel.y));

    set_pixel(view, color,
              pixel_create(pixel.x, -pixel.y + 2 * center.y));

    set_pixel(view, color,
              pixel_create(-pixel.x + 2 * center.x, -pixel.y + 2 * center.y));
}

static void draw_figure(draw_view_t& view, QColor &color, figure_t &figure, bool is_circle=false)
{
    for (int i = 0; i < figure.data.size(); i++)
        set_symmetric_pixels(view, color, figure.data[i], figure.center, is_circle);
}

static void draw_lib_ellipse(draw_view_t& view, QColor &color, point_t center, point_t radius)
{
    QPainter painter(view.scene);
    QPen pen(color);
    painter.setPen(pen);

    painter.drawEllipse(center.x - radius.x, center.y - radius.y, radius.x * 2, radius.y * 2);
}

void draw_circle(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, int &radius)
{
    figure_t figure;
    if (alg == LIBRARY)
    {
        draw_lib_ellipse(view, color, center, point_t{radius, radius});
    }
    else
    {
        switch (alg)
        {
        case CANONICAL:
            figure = canonical_circle(center, radius);
            break;
        case PARAMETRIC:
            figure = parametric_circle(center, radius);
            break;
        case BRESENHAM:
            figure = bresenham_circle(center, radius);
            break;
        case MIDDLE_POINT:
            figure = middle_point_circle(center, radius);
            break;
        case LIBRARY:
            break;
        }
        draw_figure(view, color, figure, true);
    }
}

void draw_ellipse(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, point_t &radius)
{
    figure_t figure;
    if (alg == LIBRARY)
    {
        draw_lib_ellipse(view, color, center, radius);
    }
    else
    {
        switch (alg)
        {
        case CANONICAL:
            figure = canonical_ellipse(center, radius);
            break;
        case PARAMETRIC:
            figure = parametric_ellipse(center, radius);
            break;
        case BRESENHAM:
            figure = bresenham_ellipse(center, radius);
            break;
        case MIDDLE_POINT:
            figure = middle_point_ellipse(center, radius);
            break;
        case LIBRARY:
            break;
        }
        draw_figure(view, color, figure);
    }
}
