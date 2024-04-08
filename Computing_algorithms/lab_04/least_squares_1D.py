import numpy as np
from matplotlib import pyplot as plt
from useful import *

def find_amount_equations_1D(n):
    return n + 1


def make_slau_1D(data, n):
    matrixSlau = [[0.0 for _ in range(n + 1)] for _ in range(n)]

    for i in range(n):
        for j in range(n):
            sums = 0
            for p in data:
                sums += p.weight * p.x**(i + j)
            matrixSlau[i][j] = sums

        sums = 0
        for p in data:
            sums += p.weight * p.y * p.x**i
        matrixSlau[i][n] = sums

    return matrixSlau


def least_squares_method_1D(data, n=1, print_mode=False):
    slau = make_slau_1D(data, find_amount_equations_1D(n))

    if print_mode:
        print("\nМатрица СЛАУ:")
        print_matrix(slau)
    
    a_values = gauss_solution(slau)

    if print_mode:
        print_coeffs(a_values)

    def approximate_func_1D(x):
        y = 0
        for i in range(len(a_values)):
            y += a_values[i] * x**i
        return y

    return approximate_func_1D


def grafic_aprox_function_1D(aprox_func, data, color='blue', label="y = f(x)", is_empty=True):
    x_min, x_max = get_interval_x(data)
    dots_count = int(x_max - x_min + 1) * 100
    x_values = np.linspace(x_min, x_max, dots_count)

    if is_empty:
        plt.figure("График(и) функции, полученный аппроксимации наименьших квадратов")
        plt.ylabel("Y")
        plt.xlabel("X")

    for p in data:
        plt.plot(p.x, p.y, 'r.')

    y_values = aprox_func(x_values)
    plt.plot(x_values, y_values, color=color, label=label)

    plt.legend()
    # plt.show()
    