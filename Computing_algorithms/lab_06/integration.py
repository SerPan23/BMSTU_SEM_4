from scipy.interpolate import CubicSpline as Spline
import numpy as np
from typing import Callable as Fn, Dict, Tuple
IntegrationFn = Fn[[Fn[[float], float], float, float], float]
Point = Tuple[float, float]
RegionDict = Dict[Point, float]

from numpy.polynomial.legendre import Legendre


def table_fn(x: list, y: list, z: list, x_: float, y_: float, use_eta=True):
    x_ind = list(x).index(x_)
    y_ind = list(y).index(y_)
    
    if use_eta:
        eta = np.array([[np.log(i) for i in zi] for zi in z])

    result = eta[y_ind][x_ind] if use_eta else z[y_ind][x_ind]

    return result


def get_gauss_rhs_coefs_for_system_of_equations(k):
    return 2 / (k + 1) if k % 2 == 0 else 0


def get_legendre_polynomial_roots(n):
    return Legendre(n * [0] + [1]).roots()


def get_coefficients(legendre_polynomial_roots):
    roots = legendre_polynomial_roots
    n = len(roots)

    matrix = np.array([[t ** t_power for t in roots] for t_power in range(n)])

    values = np.array(
        [get_gauss_rhs_coefs_for_system_of_equations(k) for k in range(n)])

    coefs = np.linalg.solve(matrix, values)

    return coefs


def integrate_gauss(func: Fn[[float], float], a: float, b: float, n=3):
    roots = get_legendre_polynomial_roots(n)
    coefs = get_coefficients(roots)

    xs = np.array(list(map(lambda t: (b - a) / 2 * t + (a + b) / 2, roots)))

    result = (b - a) / 2 * sum([coefs[i] * func(xs[i])
                                for i in range(len(roots))])

    return result


def integrate_simpson(func: Fn[[float], float], a: float, b: float, n=30):
    h = (b - a) / (n*2)

    xs = np.array([a + i * h for i in range(n*2 + 1)])
    ys = np.array([func(x) for x in xs])

    s1 = 4 * np.sum([ys[2*i - 1] for i in range(1, n)])
    s2 = 2 * np.sum([ys[2*i] for i in range(1, n - 1)])
    s = (h / 3) * (ys[0] + s1 + s2 + ys[-1])

    return s


# Integration region
def G(x: float, y: float):
    return x >= 0 and y >= 0 and (x + y) <= 1


def integrate_region(integrate_main: IntegrationFn,
                     integrate_Fs: IntegrationFn,
                     region_dict: RegionDict,
                     use_eta=True
                     ):
    xs = np.unique(list(map(lambda p: p[0], region_dict.keys())))
    ys = np.unique(list(map(lambda p: p[1], region_dict.keys())))

    def points_by_y(y): return [p for p in region_dict.keys() if p[1] == y]

    Fs = []
    Ys = []

    for k in ys:
        points = points_by_y(k)
        xs = [p[0] for p in points]
        fn = [region_dict[p] for p in points]

        if len(xs) > 1:
            spline = Spline(xs, fn)

            if use_eta:
                def func(x): return np.e ** spline(x)
            else:
                def func(x): return spline(x)

            x_min = min(xs)
            x_max = max(xs)

            Fk = integrate_Fs(func, x_min, x_max)

            Fs.append(Fk)
            Ys.append(k)

    func = Spline(Ys, Fs)

    y_min = min(Ys)
    y_max = max(Ys)

    return integrate_main(func, y_min, y_max)
