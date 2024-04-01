#include "draw.h"

static void set_pixel(draw_view_t& view, QColor &color, pixel_t pixel)
{
    QPainter painter(view.scene);
    color.setAlpha(pixel.intensity);
    QPen pen(color);
    painter.setPen(pen);
    painter.drawLine(pixel.x, pixel.y, pixel.x, pixel.y);
}

static pixel_t pixel_y_mirror(pixel_t& pixel, int center)
{
    return pixel_t{
        2 * center - pixel.x,
        pixel.y,
        pixel.intensity
    };
}

static pixel_t pixel_x_mirror(pixel_t& pixel, int center)
{
    return pixel_t{
        pixel.x,
        2 * center - pixel.y,
        pixel.intensity
    };
}

static void set_symmetric_pixels(draw_view_t& view, QColor &color, pixel_t& pixel, pixel_t center) {
    pixel_t x_mirr = pixel_x_mirror(pixel, center.y);
    pixel_t y_mirr = pixel_y_mirror(pixel, center.x);

    set_pixel(view, color, pixel);
    set_pixel(view, color, x_mirr);
    set_pixel(view, color, y_mirr);
    set_pixel(
        view,
        color,
        pixel_x_mirror(y_mirr, center.y)
    );
}

static void draw_figure(draw_view_t& view, QColor &color, figure_t &figure)
{
    for (int i = 0; i < figure.data.size(); i++)
        set_symmetric_pixels(view, color, figure.data[i], figure.center);
}

void draw_circle(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, double &radius)
{
    figure_t figure;
    if (alg == LIBRARY)
    {

    }
    else
    {
        switch (alg)
        {
        case CANONICAL:
            figure = canonical_circle(center, radius);
            break;
        case PARAMETRIC:
            // figure = parametric_circle(center, radius);
            break;
        case BRESENHAM:
            // figure = bresenham_circle(center, radius);
            break;
        case MIDDLE_POINT:
            // figure = middle_point_circle(center, radius);
            break;
        case LIBRARY:
            break;
        }
        draw_figure(view, color, figure);
    }
}

void draw_ellipse(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, point_t &radius)
{
    figure_t figure;
    if (alg == LIBRARY)
    {

    }
    else
    {
        switch (alg)
        {
        case CANONICAL:
            figure = canonical_ellipse(center, radius);
            break;
        case PARAMETRIC:
            // figure = parametric_ellipse(center, radius);
            break;
        case BRESENHAM:
            // figure = bresenham_ellipse(center, radius);
            break;
        case MIDDLE_POINT:
            // figure = middle_point_ellipse(center, radius);
            break;
        case LIBRARY:
            break;
        }
        draw_figure(view, color, figure);
    }
}
