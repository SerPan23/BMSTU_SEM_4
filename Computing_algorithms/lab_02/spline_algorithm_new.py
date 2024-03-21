def A(y):
    return y

def get_a_values(y_values):
    a_values = [None]

    for i in range(1, len(y_values) + 1):
        a_values.append(A(y_values[i - 1]))

    return a_values

def get_h_values(x_values):
    h_values = [None]

    for i in range(1, len(x_values)):
        h_values.append(x_values[i] - x_values[i - 1])

    return h_values

def ksi_next(h, h_prev, ksi):
    return -(h / (2 * (h + h_prev) + h_prev * ksi))


def f(y, y_prev, y_prevprev, h, h_prev):
    return 3 * ((y - y_prev) / h - (y_prev - y_prevprev) / h_prev)


def teta_next(f_i, h, h_prev, teta, ksi):
    return (f_i - h_prev * teta) / (2 * (h + h_prev) + h_prev * ksi)


def get_run_through_coeff(h_values, y_values, start):
    ksi_start = 0
    teta_start = start

    ksi_values = [0, 0, ksi_start]

    teta_values = [0, 0, teta_start]

    for i in range(2, len(h_values)):
        new_ksi = ksi_next(h_values[i], h_values[i - 1], ksi_values[-1])
        ksi_values.append(new_ksi)

        f_i = f(
            y_values[i],
            y_values[i - 1],
            y_values[i - 2],
            h_values[i],
            h_values[i - 1]
        )

        new_teta = teta_next(
            f_i,
            h_values[i],
            h_values[i - 1],
            teta_values[-1],
            ksi_values[i]
        )

        teta_values.append(new_teta)

    return ksi_values, teta_values


def C(ksi, c, teta):
    return ksi * c + teta


def get_c_values(h_values, y_values, start, end):
    c_values = [end]  # cN + 1

    ksi_values, teta_values = get_run_through_coeff(h_values, y_values, start)

    for i in range(len(ksi_values) - 2, 1, -1):
        c_values.insert(0,
                        C(ksi_values[i + 1], c_values[0], teta_values[i + 1]))

    c_values.insert(0, start)  # c1
    c_values.insert(0, None)

    return c_values


def B(y, y_prev, h, c_next, c):
    return (y - y_prev) / h - h * (c_next + 2 * c) / 3


def get_b_values(h_values, y_values, c_values):
    b_values = [None]

    for i in range(1, len(y_values)):
        b_values.append(B(y_values[i], y_values[i - 1],
                          h_values[i], c_values[i + 1], c_values[i])
        )

    b_values.append(None)

    return b_values


def D(c_next, c, h):
    return (c_next - c) / (3 * h)


def get_d_values(h_values, c_values):
    d_values = [None]

    for i in range(1, len(c_values) - 1):
        d_values.append(D(c_values[i + 1], c_values[i], h_values[i]))

    d_values.append(None)

    return d_values


def get_coefs(x_values, y_values, x0_deriv, xn_deriv):
    a_values = get_a_values(y_values)

    h_values = get_h_values(x_values)

    c_0 = x0_deriv / 2
    c_n = xn_deriv / 2

    c_values = get_c_values(h_values, y_values, c_0, c_n)
    b_values = get_b_values(h_values, y_values, c_values)
    d_values = get_d_values(h_values, c_values)

    return a_values, h_values, b_values, c_values, d_values


def find_left_sector_index(x_values, x):
    size = len(x_values) - 1
    index = 1

    while index < size and x_values[index] < x:
        index += 1

    return index

def spline(data, x, x0_deriv, xn_deriv):
    x_values = [i.x for i in data]
    y_values = [i.y for i in data]

    a, h, b, c, d = get_coefs(x_values, y_values, x0_deriv, xn_deriv)

    i = find_left_sector_index(x_values, x)

    diff = x - x_values[i - 1]
    y = a[i] + b[i] * diff + c[i] * (diff**2) + d[i] * (diff**3)

    return y


def debug_spline(data, x, x0_deriv, xn_deriv):

    x_values = [i.x for i in data]
    y_values = [i.y for i in data]

    a, h, b, c, d = get_coefs(x_values, y_values, x0_deriv, xn_deriv)

    ksi_values, teta_values = get_run_through_coeff(
        h, y_values, x0_deriv / 2)

    print("ksi: ", ksi_values)
    print("teta: ", teta_values)

    print("a: ", a)
    # print("h: ", h)
    print("b: ", b)
    print("c: ", c)
    print("d: ", d)

    i = find_left_sector_index(x_values, x)

    diff = x - x_values[i - 1]
    y = a[i] + b[i] * diff + c[i] * (diff**2) + d[i] * (diff**3)

    return y
