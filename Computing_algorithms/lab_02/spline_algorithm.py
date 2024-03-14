def C(c_i, ksi_i, teta_i):
    return ksi_i * c_i + teta_i

# y1 = y_i-1
# y2 = y_i
# hi
# c1 = c_i+1
# c2 = c_i
def B(y1, y2, c1, c2, hi):
    return (y2 - y1) / hi - (hi * (c2 + 2 * c1) / 3)


def D(c1, c2, hi):
    return (c1 - c2) / (3 * hi)


def get_a_values(y_values):
    a_values = [y_values[i] for i in range(len(y_values) - 1)]
    return a_values


# y1 = yi-2
# y2 = yi-1
# y3 = yi
# h1 = hi-1
# h2 = hi
def fi(y1, y2, y3, h1, h2):
    return 3 * ((y3 - y2) / h2 - (y2 - y1) / h1)


# функция расcчтывает значение ksi i-го элемента
# ksi_i+1 = -h_i / (h_i-1  * ksi_i-1 * (h_i - h_i-1))
# ksi_i = -h_i-1 / (h_i  * ksi_i + 2 * (h_i-1 - h_i))
# ksi1 = ksi_i-1
# h1 = h_i-1
# h2 = h_i
def ksi(ksi1, h1, h2):
    return - h1 / (h2 * ksi1 + 2 * (h2 + h1))


# fi - значение функции fi()
# teta - teta_i-1
# ksi - ksi_i-1
# h1 - h_i-1
# h2 - h_i
def teta(fi, teta_i, ksi_i, h1, h2):
    return (fi - h1 * teta_i) / (h1 * ksi_i + 2 * (h2 + h1))


def get_run_through_coeff(x_values, y_values, start, end):
    x_size = len(x_values)

    if start == 0 and end == 0:
        ksi_values = [0, 0]
        teta_values = [0, 0]
    elif start == 0:
        ksi_values = [0, end / 2]
        teta_values = [0, end / 2]
    else:
        ksi_values = [start / 2, end / 2]
        teta_values = [start / 2, end / 2]

    for i in range(2, x_size):
        h2 = x_values[i] - x_values[i - 1]       # hi
        h1 = x_values[i - 1] - x_values[i - 2]   # hi-1

        fi_cur = fi(y_values[i - 2], y_values[i - 1], y_values[i], h1, h2)

        ksi_values.append(ksi(ksi_values[i - 1], h1, h2))
        teta_values.append(teta(fi_cur, teta_values[i - 1], ksi_values[i - 1], h1, h2))

    return ksi_values, teta_values


def get_c_values(x_values, y_values, start, end):
    x_size = len(x_values)

    c_values = [0] * (x_size - 1)
    c_values[0] = start
    c_values[1] = end
    
    ksi_values, teta_values = get_run_through_coeff(x_values, y_values, start, end)

    c_values[-1] = teta_values[-1]

    for i in range(x_size - 2, 0, -1):
        c_values[i - 1] = C(c_values[i], ksi_values[i], teta_values[i])

    return c_values


def get_b_values(x_values, y_values, c_values):
    b_values = list()
    for i in range(1, len(x_values) - 1):
        hi = x_values[i] - x_values[i - 1]
        b_values.append(B(y_values[i - 1], y_values[i],
                       c_values[i - 1], c_values[i], hi))

    hi = x_values[-1] - x_values[-2]
    b_values.append(B(y_values[-2], y_values[-1], 0, c_values[-1], hi))

    return b_values


def get_d_values(x_values, c_values):
    d_values = []

    size = len(x_values)

    for i in range(1, size - 1):
        hi = x_values[i] - x_values[i - 1]
        d_values.append(D(c_values[i], c_values[i - 1], hi))

    hi = x_values[-1] - x_values[-2]
    d_values.append(D(0, c_values[-1], hi))

    return d_values


def get_coefs(x_values, y_values, start, end):
    a_values = get_a_values(y_values)
    c_values = get_c_values(x_values, y_values, start, end)
    b_values = get_b_values(x_values, y_values, c_values)
    d_values = get_d_values(x_values, c_values)

    return a_values, b_values, c_values, d_values


def find_left_sector_index(x_values, x):
    size = len(x_values)
    index = 1

    while index < size and x_values[index] < x:
        index += 1

    return index - 1


def spline_polynom_calc(x, x_values, left_index, coefs):
    h = x - x_values[left_index]
    y = 0

    for i in range(4):
        y += coefs[i][left_index] * (h ** i)

    return y


def spline(data, x, start, end):
    x_values = [i.x for i in data]
    y_values = [i.y for i in data]

    coeffs = get_coefs(x_values, y_values, start, end)

    left_index = find_left_sector_index(x_values, x)

    y = spline_polynom_calc(x, x_values, left_index, coeffs)

    return y
