#include "funcs_list.h"

#include <cmath>

double f1(double x, double z)
{
    return sin(x) * sin(x) + cos(z) * cos(z);
}

double f2(double x, double z)
{
    return sin(x) * cos(z / 2) + cos(x) * sin(z / 2);
}

// эллиптический параболоид
double f3(double x, double z)
{
    return x*x / 20 + z*z / 20;
}

double f4(double x, double z)
{
    return x*z/15;
}

double f5(double x, double z)
{
    return exp(sin(sqrt(x*x + z*z)));
}

double f6(double x, double z)
{
    return sqrt(x*x + z*z);
}

std::shared_ptr<Funcs::funcList> getFuncsList()
{
    std::vector<Funcs::SaveData> fs = {
        Funcs::SaveData("sin(x)^2 + cos(z)^2", f1),
        Funcs::SaveData("sin(x) * cos(z/2) + cos(x) * sin(z/2)", f2),
        Funcs::SaveData("x^2 / 20 + z^2 / 20", f3),
        Funcs::SaveData("x*z/15", f4),
        Funcs::SaveData("exp(sin(sqrt(x^2 + z^2)))", f5),
        Funcs::SaveData("sqrt(x^2 + z^2)", f6),
    };

    return std::make_shared<Funcs::funcList>(fs);
}
