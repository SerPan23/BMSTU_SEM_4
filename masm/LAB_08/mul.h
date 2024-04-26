#ifndef MUL_H
#define MUL_H

template <typename Type>
Type mul(Type a, Type b)
{
    Type result = 0;

    result = a * b;

    return result;
}

template <typename Type>
Type mul_asm(Type a, Type b)
{
    Type result = 0;

    __asm__(
        "fld %1\n"
        "fld %2\n"
        "fmulp %%ST(1), %%ST(0)\n"
        "fstp %0\n"
        : "=m"(result)
        : "m"(a),
          "m"(b));

    return result;
}

#endif