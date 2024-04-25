import numpy as np
from matplotlib import pyplot as plt
from useful import *


def get_value_2D_pows(x, y, powx, powy):
    return x**powx * y**powy


def get_value_2D_exp(x, y, powx, powy):
    # return np.exp(x**powx) * np.exp(y**powy)
    # return x**powx * y**powy
    return x ** powx * np.exp(y * powy)


def make_slau_2D(data, n, get_value_2D=get_value_2D_pows):
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


def least_squares_method_2D(data, n=1, print_mode=False, get_value_2D=get_value_2D_pows):

    slau = make_slau_2D(data, n, get_value_2D)
    
    if print_mode:
        print("\nМатрица СЛАУ:")
        print_matrix(slau)

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


def parseTableToCoordinates3D(pointTable):
    xs = list()
    ys = list()
    zs = list()
    for p in pointTable:
        xs.append(p.y)
        ys.append(p.y)
        zs.append(p.z)
    return np.array(xs), np.array(ys), np.array(zs)


def grafic_aprox_function_2D(aprox_func, data, color='blue', axes=None):
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

    if axes is None:
        fig = plt.figure(
            "График функции, полученный аппроксимации наименьших квадратов")
        xpoints, ypoints, zpoints = parseTableToCoordinates3D(data)
        
        axes = fig.add_subplot(projection='3d')
        axes.scatter(xpoints, ypoints, zpoints, c='red')
        axes.set_xlabel('OX')
        axes.set_ylabel('OY')
        axes.set_zlabel('OZ')
    
    x_values, y_values, z_values = make_2D_matrix()
    axes.plot_surface(x_values, y_values, z_values, color=color)
    # plt.show()
    return axes
