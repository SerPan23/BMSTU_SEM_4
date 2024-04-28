#ifndef SUM_H
#define SUM_H

template <typename T>
T sum(T a, T b)
{
    T res = 0;

    res = a + b;

    return res;
}

template <typename T>
T sum_asm(T a, T b)
{
    T res = 0;

    __asm__(
        "fld %1\n"                 // загружаем a на вершину стека
        "fld %2\n"                 // загружаем b на вершину стека
        "faddp %%ST(1), %%ST(0)\n" // складываем ST(1) и ST(0), сохраняем результат в ST(1)
                                   // и извлекаем из стека сопроцессора (поэтому 'p' в названии команды)
        "fstp %0\n"                // извлекаем число из FPU в память, в данном случае из ST(0) в res
        : "=m"(res)                // res - выходной параметр
        : "m"(a),                  // a - входной параметр
          "m"(b)                   // b - входной параметр
    );

    return res;
}

#endif