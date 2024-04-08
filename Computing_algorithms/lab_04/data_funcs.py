import numpy as np
from Point import *
from random import randint


def generate_data_1D(f, sx, ex, amount):
    data = list()
    x_values = np.linspace(sx, ex, amount)

    for x in x_values:
        data.append(Point(x, f(x), 0, randint(1, 5)))

    return data


def generate_data_2D(f, sx, ex, sy, ey, amount_x, amount_y):
    data = list()
    x_values = np.linspace(sx, ex, amount_x)
    y_values = np.linspace(sy, ey, amount_y)

    for i in range(amount_x):
        for j in range(amount_y):
            data.append(Point(x_values[i], y_values[j], f(
                x_values[i], y_values[j]), randint(1, 10)))

    return data

def set_all_weight(data, w=1):
    for d in data:
        d.weight = w
        
def set_n_weight(data, n, w=1):
    if 0 <= n < len(data):
        data[n] = w

def print_data(data):
    i = 0
    for d in data:
        print(f"{i})", d)
        i += 1
