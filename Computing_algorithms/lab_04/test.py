from data_funcs import *

# from matplotlib import pyplot as plt
from useful import *

# def f_1d(x):
#     return x**2


def f_2d(x, y):
    # return x**2 + y**2
    return 2 * x**2 - np.exp(y) + 0.5


def get_value_2D(x, y, powx, powy):
    return x**powx * y**powy


def make_slau_2D(data, n):
    a = list()
    b = list()
    for i in range(n + 1):
        for j in range(n + 1 - i):
            a_row = []
            for k in range(n + 1):
                for t in range(n + 1 - k):
                    a_row.append(sum(list(map(
                        lambda p: get_value_2D(
                            p.x, p.y, k + i, t + j) * p.weight,
                        data
                    ))))
            a.append(a_row)
            b.append(sum(list(map(
                lambda p: get_value_2D(p.x, p.y,
                                       i, j) * p.z * p.weight,
                data
            ))))
    slau = list()
    for i in range(len(a)):
       slau.append(a[i])
       slau[i].append(b[i])
    return slau

def least_squares_method_2D(data, n=1, print_mode=False):

    slau = make_slau_2D(data, n)

    c = gauss_solution(slau)

    if print_mode:
        print_coeffs(c)

    def approximateFunction_2D(x, y):
        result = 0
        c_index = 0
        for i in range(n + 1):
            for j in range(n + 1 - i):
                result += c[c_index] * get_value_2D(x, y, i, j)
                c_index += 1
        return result

    return approximateFunction_2D


# table_1D = generate_data_1D(f_1d, -5, 5, 10)
# table_2D = generate_data_2D(f_2d, -5, 5, 2, 10, 10, 20)

# n = 3

# fn = least_squares_method_1D(table_1D, n)
# grafic_aprox_function_1D(fn, table_1D)

# fn_1 = least_squares_method_1D(table_1D, 1)
# grafic_aprox_function_1D(fn_1, table_1D, is_empty=False)
# plt.show()


# fn = least_squares_method_2D(table_2D, n)
# axes = grafic_aprox_function_2D(fn, table_2D)

# fn_1 = least_squares_method_2D(table_2D, 1)
# grafic_aprox_function_2D(fn_1, table_2D, color='red', axes=axes)
# plt.show()


data = generate_data_2D(f_2d, -2, 2, -1, 2, 5, 4)


# ws = [2, 8, 7, 6, 0, 3, 6, 1, 6, 9, 3, 6, 3, 1, 1, 0, 0, 4, 5, 3]
ws = [6, 7, 2, 7, 7, 4, 6, 9, 5, 4, 6, 8, 4, 6, 5, 9, 6, 8, 6, 1]
for i in range(len(ws)):
    set_n_weight(data, i, ws[i])
    
    
def get_interval_x(table):
    minim = table[0].x
    maxim = table[0].x
    for p in table:
        value = p.x
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim


def get_interval_y(table):
    minim = table[0].y
    maxim = table[0].y
    for p in table:
        value = p.y
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim


aprox_func = least_squares_method_2D(
    data, 2)
    
x_min, x_max = get_interval_x(data)
y_min, y_max = get_interval_y(data)

# dots_count_x = int(x_max - x_min + 1) * 100
dots_count_x = 40
x_values = np.linspace(x_min, x_max, dots_count_x)

# dots_count_y = int(y_max - y_min + 1) * 100
dots_count_y = 40
y_values = np.linspace(y_min, y_max, dots_count_y)

z_values = [aprox_func(x_values[i], y_values[i])
            for i in range(len(x_values))]


def make_2D_matrix():
    # Создаем двумерную матрицу-сетку
    x_grid, y_grid = np.meshgrid(x_values, y_values)
    # В узлах рассчитываем значение функции
    z_grid = np.array([
        [
            aprox_func(
                x_grid[i][j],
                y_grid[i][j],
            ) for j in range(len(x_values))
        ] for i in range(len(y_values))
    ])
    return x_grid, y_grid, z_grid
    
    
x_values, y_values, z_values = make_2D_matrix()

print(aprox_func(0.3, -0.2))
