#ifndef SIN_COMPARE
#define SIN_COMPARE

#include <math.h>
#include <stdio.h>

void c_sin()
{
    printf("C\n");
    printf("sin(PI) = %g\n", sin(M_PI));
    printf("sin(PI / 2) = %g\n", sin(M_PI / 2));
    printf("sin(3.14) = %g\n", sin(3.14));
    printf("sin(3.141596) = %g\n", sin(3.141596));
}

void asm_sin()
{
    printf("Asm\n");
    double div = 0;

    double res = 0.0;
    double arg = 0.0;
    __asm__(
        "fldpi\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res));
    printf("sin(pi) = %g\n", res);

    res = 0;
    div = 2.0;

    __asm__(
        "fldpi\n"
        "fld %1\n"
        "fdivp\n"
        "fsin\n"
        "fstp %0\n"
        : "=m"(res) : "m"(div));
    printf("sin(pi / 2) = %g\n", res);

    arg = 3.14;
    __asm__(
        "fld %1\n"
        "fsin\n"
        "fstp %0\n" : "=m"(res) : "m"(arg));
    printf("sin(3.14) = %g\n", res);

    arg = 3.141596;
    __asm__(
        "fld %1\n"
        "fsin\n"
        "fstp %0\n" : "=m"(res) : "m"(arg));
    printf("sin(3.141596) = %g\n", res);
}

#endif