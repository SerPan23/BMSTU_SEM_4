from data_funcs import *

from least_squares_1D import least_squares_method_1D, grafic_aprox_function_1D
from least_squares_2D import least_squares_method_2D, grafic_aprox_function_2D

from matplotlib import pyplot as plt

def f_1d(x):
    return x**2


def f_2d(x, y):
    return x**2 + y**2


table_1D = generate_data_1D(f_1d, -5, 5, 10)
table_2D = generate_data_2D(f_2d, -5, 5, 2, 10, 10, 20)

n = 3

fn = least_squares_method_1D(table_1D, n)
grafic_aprox_function_1D(fn, table_1D)

fn_1 = least_squares_method_1D(table_1D, 1)
grafic_aprox_function_1D(fn_1, table_1D, is_empty=False)
plt.show()


fn = least_squares_method_2D(table_2D, n)
axes = grafic_aprox_function_2D(fn, table_2D)

fn_1 = least_squares_method_2D(table_2D, 1)
grafic_aprox_function_2D(fn_1, table_2D, color='red', axes=axes)
plt.show()
