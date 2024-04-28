# 1
def get_left_derivative(y0, y1, h=1):
    return (y1 - y0) / h


# 2
def get_center_derivative(y0, y2, h=1):
    return (y2 - y0) / (2*h)


# 3
def get_second_runge_formula_derivative(y0, y1, y2):
    d1 = get_left_derivative(y0, y1, 1)
    d2 = get_left_derivative(y0, y2, 2)

    return d1 + (d1 - d2) / 3


# 4
def get_alignment_variables_derivative(y0, y1, x0, x1):
    eta0 = 1/y0
    eta1 = 1/y1

    ksi0 = 1/x0
    ksi1 = 1/x1

    a1 = eta1 - eta0
    a0 = ksi1 - ksi0

    derivative = (a1 / a0) * (y0 ** 2) / (x0 ** 2)  # der. in (x0, y0)

    return derivative

# 5
def get_second_derivative(y0, y1, y2, h=1):
    return (y0 - 2 * y1 + y2) / (h ** 2)
