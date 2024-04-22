from data_funcs import *
from useful import *
from least_squares_2D import least_squares_method_2D, get_value_2D_exp


def f_2d(x, y):
    # return x**2 + y**2
    return 2 * x**2 - np.exp(y) + 0.5

# data = generate_data_2D(f_2d, -2, 2, -1, 2, 5, 4)
# # ws = [2, 8, 7, 6, 0, 3, 6, 1, 6, 9, 3, 6, 3, 1, 1, 0, 0, 4, 5, 3]
# ws = [6, 7, 2, 7, 7, 4, 6, 9, 5, 4, 6, 8, 4, 6, 5, 9, 6, 8, 6, 1]
# for i in range(len(ws)):
#     set_n_weight(data, i, ws[i])

data = generate_from_file_2D("./data/data_2D/data_4.txt")

print("-------Matrix 1----------")
aprox_func = least_squares_method_2D(
    data, 2, print_mode=True)

print("-------Matrix 2----------")
aprox_func_exp = least_squares_method_2D(
    data, 2, print_mode=True, get_value_2D=get_value_2D_exp)

print("-------------------------\n")

x = 0.3
y = -0.2
print("Func: ", f_2d(x, y))
print("Aprox: ", aprox_func(x, y))
print("Aprox exp: ", aprox_func_exp(x, y))

