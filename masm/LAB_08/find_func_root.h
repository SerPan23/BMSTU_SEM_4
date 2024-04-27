#ifndef FIND_FUNC_ROOT
#define FIND_FUNC_ROOT

#include <cmath>
#include <iostream>

#define EPS 1e-6

double func(double x)
{
    double res = 0;
    double m = 5;

    __asm(
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
        : "m"(x), "m"(m));

    //     double first_part = 0;
    //     __asm__(
    //         "fld %1\n"
    //         "fld %1\n"
    //         "fmulp %%ST(1), %%ST(0)\n"
    //         "fstp %0\n"
    //         : "=m"(first_part)
    //         : "m"(x));

    //     double second_part = 0;
    //     __asm__(
    //         "fld %2\n"
    //         "fld %1\n"
    //         "fmulp %%ST(1), %%ST(0)\n"
    //         "fstp %0\n"
    //         : "=m"(second_part)
    //         : "m"(x), "m"(m));

    //     double arg = 0;
    //     __asm__(
    //         "fld %1\n"                 // загружаем a на вершину стека
    //         "fld %2\n"                 // загружаем b на вершину стека
    //         "faddp %%ST(1), %%ST(0)\n" // складываем ST(1) и ST(0), сохраняем результат в ST(1)
    //                                    // и извлекаем из стека сопроцессора (поэтому 'p' в названии команды)
    //         "fstp %0\n"                // извлекаем число из FPU в память, в данном случае из ST(0) в res
    //         : "=m"(arg)                // res - выходной параметр
    //         : "m"(first_part),         // a - входной параметр
    //           "m"(second_part)         // b - входной параметр
    //     );

    //     __asm__(
    //         "fld %1\n"
    //         "fsin\n"
    //         "fstp %0\n" : "=m"(res) : "m"(arg));

    return res;
}

double mid_point(double a, double b)
{
    double res = 0;
    double div = 2;
    __asm__(
        "fld %1\n"                 // загружаем a на вершину стека
        "fld %2\n"                 // загружаем b на вершину стека
        "faddp %%ST(1), %%ST(0)\n" // вычитаем ST(1) и ST(0), сохраняем результат в ST(1)
                                   // и извлекаем из стека сопроцессора (поэтому 'p' в названии команды)
        "fld %3\n"
        "fdivp\n"

        "fstp %0\n"        // извлекаем число из FPU в память, в данном случае из ST(0) в res
        : "=m"(res)        // res - выходной параметр
        : "m"(a),          // a - входной параметр
          "m"(b), "m"(div) // b - входной параметр
    );

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
    double res = 0;
    double c = 0;

    // c = mid_point(start, end);
    // std::cout << c << " " << func(c) << "*\n";

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

#endif