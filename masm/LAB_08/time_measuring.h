#ifndef TIME_MEASURING_H
#define TIME_MEASURING_H

#include <iostream>
#include <ctime>
#include <string>

#define ITER_COUNT 100

static long delta_time(struct timespec mt1, struct timespec mt2)
{
    return (1000000000 * (mt2.tv_sec - mt1.tv_sec) + (mt2.tv_nsec - mt1.tv_nsec));
}

template <typename T>
void measure(T (*func)(T a, T b), const std::string &name)
{
    double sum = 0;
    for (int i = 0; i < ITER_COUNT; i++)
    {
        T a = static_cast<T>(rand()) / 50.0;
        T b = static_cast<T>(rand()) / 500.0;

        struct timespec tbegin, tend;
        clock_gettime(CLOCK_REALTIME, &tbegin);

        func(a, b);

        clock_gettime(CLOCK_REALTIME, &tend);

        sum += delta_time(tbegin, tend);
    }
    std::cout << name << " time = " << sum / ITER_COUNT << std::endl;
}

#endif