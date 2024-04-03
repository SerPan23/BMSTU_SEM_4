#include "algorithms.h"

algorithm_t get_algorithm(QString name)
{
    if (name == "Канонического уравнения")
        return CANONICAL;

    if (name == "Параметрического уравнения")
        return PARAMETRIC;

    if (name == "Брезенхема")
        return BRESENHAM;

    if (name == "Средней точки")
        return MIDDLE_POINT;

    return LIBRARY;
}

static long delta_time(struct timespec mt1, struct timespec mt2)
{
    return 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
}

static long time_measurement_circle(point_t center, double radius, figure_t (*alg)(point_t center, double radius))
{
    long time1;
    long sum1 = 0;
    struct timespec tbegin, tend;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &tbegin);
        alg(center, radius);
        clock_gettime(CLOCK_REALTIME, &tend);
        sum1 += delta_time(tbegin, tend);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    return time1;
}
long time_measurement_circle(spectrum_data_t spectrum_data, figure_t (*alg)(point_t center, double radius))
{
    long time = 0;
    int spects_count = 10;

    for (int j = 0; j < spects_count; j++)
    {
        long tmp = 0;
        int radius = spectrum_data.start_radius.x;
        for (int i = 0; i < spectrum_data.figures_count; i++, radius += spectrum_data.step)
            tmp += time_measurement_circle(spectrum_data.center, radius, alg);

        time += tmp / spects_count;
    }

    return time;
}

static long time_measurement_ellipse(point_t center, point_t radius, figure_t (*alg)(point_t center, point_t radius))
{
    long time1;
    long sum1 = 0;
    struct timespec tbegin, tend;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &tbegin);
        alg(center, radius);
        clock_gettime(CLOCK_REALTIME, &tend);
        sum1 += delta_time(tbegin, tend);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    return time1;
}

long time_measurement_ellipse(spectrum_data_t spectrum_data, figure_t (*alg)(point_t center, point_t radius))
{
    long time = 0;
    int spects_count = 10;

    for (int j = 0; j < spects_count; j++)
    {
        long tmp = 0;

        point_t radius = spectrum_data.start_radius;
        for (int i = 0; i < spectrum_data.figures_count; i++, radius.x += spectrum_data.step, radius.y += spectrum_data.step)
            tmp += time_measurement_ellipse(spectrum_data.center, radius, alg);

        time += tmp / spects_count;
    }

    return time;
}
