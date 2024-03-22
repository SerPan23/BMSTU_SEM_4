from IO import write_data_to_file
from Point import *

import math


def generate(path, func, start, end, step):
    data = []
    x = start
    while x <= end:
        data.append(Point(x, func(x)))
        x += step

    write_data_to_file(data, path)


def parabola(x):
    return x*x


def some_func(x):
    return (x**3)/100 + 4 * math.cos(x**2 + 0.5) - 1


def my_cos(x):
    return 4 * math.cos(x**2 + 0.5)

if __name__ == "__main__":
    # generate("./data/sin_2.txt", math.sin, 0, 10, 1)

    # generate("./data/parabola_1.txt", parabola, -10, 10, 1)

    # generate("./data/some_func_3.txt", some_func, -2, 1, 0.25)

    # generate("./data/my_cos_2.txt", my_cos, -10, 10, 2)
    print("generated")
