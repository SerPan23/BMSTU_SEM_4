#include <iostream>

#include "time_measuring.h"
#include "sum.h"
#include "mul.h"
#include "sin_compare.h"
#include "find_func_root.h"

int main()
{
    srand(time(NULL));

    std::cout << "float compare:" << std::endl;
    measure<float>(sum<float>, "add");
    measure<float>(sum_asm<float>, "asm add");
    measure<float>(mul<float>, "mul");
    measure<float>(mul_asm<float>, "asm mul");

    std::cout << "\ndouble compare:" << std::endl;
    measure<double>(sum<double>, "add");
    measure<double>(sum_asm<double>, "asm add");
    measure<double>(mul<double>, "mul");
    measure<double>(mul_asm<double>, "asm mul");

    std::cout << "\nSin compare:" << std::endl;
    c_sin();
    std::cout << std::endl;
    asm_sin();

    std::cout << "\nRoot: " << find_func_root(0, 5, 100000) << std::endl;
}
