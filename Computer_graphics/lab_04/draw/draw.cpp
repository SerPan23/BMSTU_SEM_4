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

void draw_circle(draw_view_t& view, algorithm_t &alg, QColor &color, point_t &center, int &radius)
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

void draw_circles_spectrum(draw_view_t& view, algorithm_t &alg, spectrum_data_t& spectrum_data)
{
    int radius = spectrum_data.start_radius.x;
    for (int i = 0; i < spectrum_data.figures_count; i++, radius += spectrum_data.step)
        draw_circle(view, alg, spectrum_data.color, spectrum_data.center, radius);
}

void draw_ellipses_spectrum(draw_view_t& view, algorithm_t &alg, spectrum_data_t& spectrum_data)
{
    point_t radius = spectrum_data.start_radius;
    for (int i = 0; i < spectrum_data.figures_count; i++, radius.x += spectrum_data.step, radius.y += spectrum_data.step)
        draw_ellipse(view, alg, spectrum_data.color, spectrum_data.center, radius);
}
