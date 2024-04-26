#include <iostream>

#include "time_measuring.h"
#include "sum.h"
#include "mul.h"
#include "sin_compare.h"


int main()
{
    srand(time(NULL));

    std::cout << "float compare:" << std::endl;
    measure<float>(sum<float>, "add");
    measure<float>(sum_asm<float>, "asm add");
    measure<float>(mul<float>, "mul");
    measure<float>(mul_asm<float>, "asm mul");

    std::cout << "double compare:" << std::endl;
    measure<double>(sum<double>, "add");
    measure<double>(sum_asm<double>, "asm add");
    measure<double>(mul<double>, "mul");
    measure<double>(mul_asm<double>, "asm mul");

    std::cout << "Sin compare:" << std::endl;
    c_sin();
    asm_sin();
}
