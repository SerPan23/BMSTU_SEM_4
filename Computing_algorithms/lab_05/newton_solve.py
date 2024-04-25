import numpy as np

def newton_solve(matrix_fn, func, start_approx, eps=1e-5):
    n_vars = len(start_approx)
    coefs = matrix_fn(*start_approx)
    fn_values = -func(*start_approx)

    deltas = np.linalg.solve(coefs, fn_values).reshape((n_vars,))

    approx = start_approx + deltas

    while any(map(lambda x: abs(x) >= eps, deltas / approx)):
        coefs = matrix_fn(*approx)
        fn_values = -func(*approx)

        deltas = np.linalg.solve(coefs, fn_values).reshape((n_vars,))

        approx += deltas

    return approx
