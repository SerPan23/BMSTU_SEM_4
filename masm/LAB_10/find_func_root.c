#include "find_func_root.h"

double func(double x)
{
    double res = 0;
    double m = 5;

    __asm__ __volatile__(
        "fldt %1\n"
        "fldt %1\n"
        "fmulp\n" // x^2
        "fldt %1\n"
        "fldt %2\n"
        "fmulp\n" // 5*x
        "faddp\n"
        "fsin\n"
        "fstpt %0\n"
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
        "fldt %1\n" // загружаем a на вершину стека
        "fldt %2\n" // загружаем b на вершину стека
        "faddp\n"   // вычитаем ST(1) и ST(0), сохраняем результат в ST(1)
                    // и извлекаем из стека сопроцессора (поэтому 'p' в названии команды)
        "fldt %3\n"
        "fdivp\n" // делим ST(1) на ST(0), сохраняем результат в ST(1)
                  // и извлекаем из стека сопроцессора

        "fstpt %0\n"               // извлекаем число из FPU в память, из ST(0) в res
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
    printf("%lf %lf %d\n", start, end, step_count);

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

// char *num_to_str(double num)
// {
//     char *res = NULL;
//     int count = 0;

//     count = snprintf(NULL, 0, "%.7lf", num);

//     if (count > 0)
//     {
//         res = calloc(count + 1, sizeof(char));
//         sprintf(res, "%.7lf", num);
//         res[count] = '\0';
//     }

//     return res;
// }

void double_to_str(double num, char *dst)
{
    printf("*1\n");
    snprintf(dst, 50,"%.7lf", num);
    printf("*2\n");
}

void str_func_root(double start, double end, int step_count, char *dst)
{
    printf("%lf %lf %d\n", start, end, step_count);

    double root = find_func_root(start, end, step_count);
    printf("%lf\n", root);

    double_to_str(root, dst);
}

double str_to_double(const char *str)
{
    double res = 0;
    printf("C: %s\t", str);

    // sscanf(str, "%lf", &res);
    res = strtod(str, NULL);

    printf("%s\n", str);

    return res;
}