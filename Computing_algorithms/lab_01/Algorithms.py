from Point import Point

EPS = 1e-8

def transpose(data):
    return list(zip(*data))

def get_index(data, x):
    dif = abs(data[0].x - x)
    index = 0
    for i in range(len(data)):
        if abs(data[i].x - x) < dif:
            dif = abs(data[i].x - x)
            index = i
    return index

def get_works_points(data, index, n):
    left = index
    right = index
    for i in range(n):
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


def get_hermit_table(data):
    data_cols_count = 2
    derivative_count = 2
    table_subs = []

    
    
    return table_subs


def get_approximate_value(table_subs, x, n):
    args_count = 2
    sum_ = table_subs[1][0]
    mainPart = 1
    for i in range(n):
        mainPart *= (x - table_subs[0][i])
        sum_ += mainPart * table_subs[i + args_count][0]
    return sum_


def get_rev_data(data):
    rev_data = []
    for i in data:
        rev_data.append(Point(i.y, i.x,
                        i.derivative, i.second_derivative))
        
    return rev_data

def get_root_by_Newton(data, n):
    rev_data = get_rev_data(data)

    index = get_index(rev_data, 0)
    working_points = get_works_points(rev_data, index, n)

    table = get_newton_table(working_points)
    return get_approximate_value(table, 0, n)

def get_root_by_Hermit(data, n):
    rev_data = get_rev_data(data)

    index = get_index(rev_data, 0)
    working_points = get_works_points(rev_data, index, n)

    table = get_hermit_table(working_points)
    return get_approximate_value(table, 0, n)

def get_compare_Newton_Hermit(points, x, max_n = 5):
    index = get_index(points, x)

    result = []
    for n in range(max_n + 1):
        working_points = get_works_points(points, index, n)
        newton_table = get_newton_table(working_points)
        hermit_table = get_hermit_table(working_points)

        result.append([get_approximate_value(newton_table, x, n),
                      get_approximate_value(hermit_table, x, n)])
        
    return result
