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

    // Выравниваем стек перед возвратом
    size_t stack_adjustment = (16 - (((size_t)(start)) & 15)) & 15;
    printf("ADJ: %zu\n", stack_adjustment);
    if (stack_adjustment > 0)
    {
        __asm__ __volatile__("sub %%rsp, %0" : : "r"(stack_adjustment) : "memory");
    }
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

// void double_to_str(double num, char *dst)
// {
//     printf("*1\n");
//     snprintf(dst, 50,"%.7lf", num);
//     printf("*2\n");
// }

// void str_func_root(double start, double end, int step_count, char *dst)
// {
//     printf("%lf %lf %d\n", start, end, step_count);

//     double root = find_func_root(start, end, step_count);
//     printf("%lf\n", root);

//     double_to_str(root, dst);
// }

// double str_to_double(const char *str)
// {
//     double res = 0;
//     printf("C: %s\t", str);

//     // sscanf(str, "%lf", &res);
//     res = strtod(str, NULL);

//     printf("%s\n", str);

//     return res;
// }