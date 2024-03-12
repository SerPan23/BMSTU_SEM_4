#include "algorithms.h"

pixel_t pixel_create(int x, int y)
{
    return pixel_create(x, y, 255);
}

pixel_t pixel_create(int x, int y, double intensity)
{
    return pixel_t{x, y, intensity};
}

int count_steps(line_t line)
{
    int count = 0;

    int x = line.pixels[0].x;
    int y = line.pixels[0].y;

    for (int i = 0; i < line.pixels.size(); i++)
    {
        if (x != line.pixels[i].x and y != line.pixels[i].y)
            count += 1;
        x = line.pixels[i].x;
        y = line.pixels[i].y;
    }

    return count;
}


static long delta_time(struct timespec mt1, struct timespec mt2)
{
    return 1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec);
}

long time_measurement(point_t start, point_t end, line_t (*alg)(point_t start, point_t end))
{
    int ITER_COUNT_TIME = 100;
    long time1;
    long sum1 = 0;
    struct timespec tbegin, tend;

    for (size_t i = 0; i < ITER_COUNT_TIME; i++)
    {
        clock_gettime(CLOCK_REALTIME, &tbegin);
        alg(start, end);
        clock_gettime(CLOCK_REALTIME, &tend);
        sum1 += delta_time(tbegin, tend);
    }
    time1 = sum1 / ITER_COUNT_TIME;

    return time1;
}
