#include "find_func_root.h"

double func(double x)
{
    double res = 0;
    double m = 5;

    __asm__ __volatile__(
        "fld %1\n"
        "fld %1\n"
        "fmulp\n" // x^2
        "fld %1\n"
        "fld %2\n"
        "fmulp\n" // 5*x
        "faddp\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res)
        : "m"(x), "m"(m)
        : "memory"
    );

    return res;
}

double mid_point(double a, double b)
{
    double res = 0;
    double div = 2;
    __asm__ __volatile__(
        "fld %1\n" // загружаем a на вершину стека
        "fld %2\n" // загружаем b на вершину стека
        "faddp\n"   // вычитаем ST(1) и ST(0), сохраняем результат в ST(1)
                    // и извлекаем из стека сопроцессора (поэтому 'p' в названии команды)
        "fld %3\n"
        "fdivp\n" // делим ST(1) на ST(0), сохраняем результат в ST(1)
                  // и извлекаем из стека сопроцессора

        "fstp %0\n"               // извлекаем число из FPU в память, из ST(0) в res
        : "=m"(res)                // res - выходной параметр
        : "m"(a), "m"(b), "m"(div) // a, b, div - входные параметры
        : "memory");

    return res;
}

int sign(double x)
{
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    return 0;
}

double find_func_root(double start, double end, int step_count)
{
    printf("Start: %lf\nEnd: %lf\nStep: %d\n", start, end, step_count);

    double res = 0;
    double c = 0;

    for (int i = 0; i < step_count; ++i)
    {
        c = mid_point(start, end);

        if (fabs(func(c)) < EPS)
            return c;

        if (sign(func(c)) == sign(func(start)))
            start = c;
        else
            end = c;
    }

    return mid_point(start, end);
}

extern char ans[1000];

void str_func_root(char *start, char *end, char *step_count)
{
    // printf("Start: %s\nEnd: %s\nStep: %s\n\n", start, end, step_count);
    double st = 0, ed = 0, step_c = 0;
    sscanf(start, "%lf", &st);
    sscanf(end, "%lf", &ed);
    sscanf(step_count, "%lf", &step_c);

    double root = find_func_root(st, ed, step_c);

    printf("Root: %lf\n", root);
    sprintf(ans, "%lf", root);
}