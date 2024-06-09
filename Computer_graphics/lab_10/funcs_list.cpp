#include "funcs_list.h"

#include <cmath>

std::shared_ptr<Funcs::funcList> getFuncsList()
{
    std::vector<Funcs::SaveData> fs = {
        Funcs::SaveData("sin(x)^2 + cos(z)^2", f1),
    };

    return std::make_shared<Funcs::funcList>(fs);
}

double f1(double x, double z)
{
    return sin(x) * sin(x) + cos(z) * cos(z);
}
