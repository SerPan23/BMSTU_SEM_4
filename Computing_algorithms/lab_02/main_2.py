from newton_polynom import *
import IO as io

from spline_algorithm import *
# from spline_algorithm_new import *


data = io.read_table_from_file("./data/data_2.txt")
io.print_table(data)


def func(x):
    return x**3 - x - 1


x = 1.3

start1 = 0
end1 = 12

print("x ", x)

print("Cплайн 0 и 0:             ", debug_spline(data, x, start1, end1))
print("Func", func(x))
