import numpy as np
from scipy.linalg import solve
from scipy.special import erfi
import math


def get_polynom(x, n: int, coeffs: list):    
    result = 0
    
    for i in range(n + 1):
        tmp = (1 - x) * x**i
        if i > 0:
            tmp *= coeffs[i - 1]
              
        result += tmp
    
    return result


def get_init_func(x):
    return (math.exp(-x**2/2) * ((1 + math.exp(x**2/2) * x) * erfi(1/math.sqrt(2)) 
            - (1 + math.sqrt(math.e)) * erfi(x/math.sqrt(2))))/erfi(1/math.sqrt(2))


def ODE(x_start=-0.5, x_end=2, n=100):
    # x_start = -0.5
    # x_end = 2
    # n = 10

    x = np.linspace(x_start, x_end, n) 
    y = np.array([get_init_func(x_i) for x_i in x])

    # m = 2

    alphas = -2 + 2 * x - 3 * x ** 2
    bethas = 2 - 6 * x + 3 * x ** 2 - 4 * x ** 3
    alphas_bethas = alphas * bethas

    coeffs_a = np.array([
        [np.sum(alphas ** 2), np.sum(alphas_bethas)],
        [np.sum(alphas_bethas), np.sum(bethas ** 2)]
    ])

    sum_1 = alphas * (4 * x - 1)
    sum_2 = bethas * (4 * x - 1)

    coeffs_b = np.array([
        [np.sum(sum_1)],
        [np.sum(sum_2)]
    ])

    coeffs_x_2 = solve(coeffs_a, coeffs_b).reshape((2, ))
    print(coeffs_x_2)

    y_2 = get_polynom(x, 2, coeffs_x_2)

    # m = 3

    gammas = 6 * x - 12 * x ** 2 + 4 * x ** 3 - 5 * x ** 4
    alphas_gammas = alphas * gammas
    bethas_gammas = bethas * gammas

    coeffs_a = np.array([
        [np.sum(alphas ** 2), np.sum(alphas_bethas), np.sum(alphas_gammas)],
        [np.sum(alphas_bethas), np.sum(bethas ** 2), np.sum(bethas_gammas)],
        [np.sum(alphas_gammas), np.sum(bethas_gammas), np.sum(gammas ** 2)]
    ])

    sum_3 = gammas * (4 * x - 1)

    coeffs_b = np.array([
        [np.sum(sum_1)],
        [np.sum(sum_2)],
        [np.sum(sum_3)]
    ])

    coeffs_x_3 = solve(coeffs_a, coeffs_b).reshape((3, ))
    print(coeffs_x_3)

    y_3 = get_polynom(x, 3, coeffs_x_3)

    return [x, y, y_2, y_3]
