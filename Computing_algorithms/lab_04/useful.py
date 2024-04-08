from Point import *


def matrix_to_triangle_view(matrix):
    n = len(matrix)
    for k in range(n):
        for i in range(k + 1, n):
            coeff = -(matrix[i][k] / matrix[k][k])
            for j in range(k, n + 1):
                matrix[i][j] += coeff * matrix[k][j]

    return matrix


def gauss_solution(matrix):
    n = len(matrix)

    matrix = matrix_to_triangle_view(matrix)
    
    # print("\nМатрица преведена к треугольному ввиду:")
    # printMatrix(matrixSlau)

    result = [0.0 for _ in range(n)]
    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i, -1):
            matrix[i][n] -= result[j] * matrix[i][j]

        result[i] = matrix[i][n] / matrix[i][i]
    return result

def get_interval_x(table):
    minim = table[0].x
    maxim = table[0].x
    for p in table:
        value = p.x
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim


def get_interval_y(table):
    minim = table[0].y
    maxim = table[0].y
    for p in table:
        value = p.y
        if value > maxim:
            maxim = value
        if value < minim:
            minim = value
    return minim, maxim


def print_coeffs(coeffs_values):
    print("Результаты подсчетов коэффициент:")
    for i in range(len(coeffs_values)):
        print("a" + str(i) + " = {:10.6g}".format(coeffs_values[i]))


def print_matrix(matrix):
    for row in matrix:
        for el in row:
            if abs(el) < 1e-6:
                el = 0.0
            print("{:15.6g}".format(el), end=" ")
        print()
