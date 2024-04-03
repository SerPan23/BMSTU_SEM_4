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

long time_measurement_circle(point_t center, double radius, figure_t (*alg)(point_t center, double radius))
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

long time_measurement_ellipse(point_t center, point_t radius, figure_t (*alg)(point_t center, point_t radius))
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
