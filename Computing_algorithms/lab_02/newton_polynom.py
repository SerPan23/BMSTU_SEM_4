from scipy.misc import derivative
from Point import *

infinity = None

def transpose(data):
    return list(zip(*data))

def get_index(data, x):
    diff = abs(data[0].x - x)
    index = 0
    for i in range(len(data)):
        if abs(data[i].x - x) < diff:
            diff = abs(data[i].x - x)
            index = i
    return index


def get_work_points(data, index, n):
    left = index
    right = index
    for i in range(n - 1):
        if i % 2 == 0:
            if left == 0:
                right += 1
            else:
                left -= 1
        else:
            if right == len(data) - 1:
                left -= 1
            else:
                right += 1
    return data[left:right + 1]

# расчет полином Ньютона м результаты в виде таблицы всех данных f(xi .... xn)
def get_newton_table(data):
    data_cols_count = 2
    table_subs = []
    for point in data:
        table_subs.append([point.x, point.y])

    table_subs = transpose(table_subs)

    x_row = table_subs[0]

    for args_count in range(1, len(x_row)):
        table_subs.append([])
        cur_y_row = table_subs[len(table_subs) - data_cols_count]

        for j in range(0, len(x_row) - args_count):
            cur = (cur_y_row[j] - cur_y_row[j + 1]) / \
                (x_row[j] - x_row[j + args_count])
            
            table_subs[ args_count + data_cols_count - 1].append(cur)
    
    return table_subs


def newton_polynom(data, n, x):
    work_points = get_work_points(data, get_index(data, x), n)
    subs = get_newton_table(work_points)
    return calc_approximate_value(subs, n, x)


def find_derivative_newton_polynom(data, n, x):
    working_table = get_work_points(data, get_index(data, x), n)
    subs = get_newton_table(working_table)

    def aprox_func(x):
        res = 0
        tmp = x
        for i in range(len(subs)):
            res += subs[i][0] * tmp
            tmp *= x
        return res

    y_derivative_n_2 = derivative(aprox_func, x, n=2, dx=1e-6)
    return y_derivative_n_2

# расчет конечного результат по польном Ньютону
def calc_approximate_value(subs_table, n, x):
    args_count = 2

    if subs_table[1][0] == infinity:
        sum_ = subs_table[1][1]
    else:
        sum_ = subs_table[1][0]

    main_part = 1

    for i in range(len(subs_table) - args_count):
        if subs_table[0][i] == infinity:
            main_part *= x
        else:
            main_part *= (x - subs_table[0][i])

        if subs_table[i + args_count][0] != infinity:
            sum_ += main_part * subs_table[i + args_count][0]
    return sum_

