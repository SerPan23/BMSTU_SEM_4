from newton_polynom import *
import IO as io
import numpy as np
from matplotlib import pyplot as plt
import os

# from spline_algorithm import *
from spline_algorithm_new import *

n = 3

# data = io.read_table_from_file("./data/data_1.txt")
# data = io.read_table_from_file("./data/sin_1.txt")
# data = io.read_table_from_file("./data/sin_2.txt")
# data = io.read_table_from_file("./data/some_func_1.txt")
# data = io.read_table_from_file("./data/some_func_2.txt")
# data = io.read_table_from_file("./data/some_func_3.txt")

path="./data/"
dir_list=os.listdir(path)

for i, fname in enumerate(dir_list):
    print("{}) {}".format(i + 1, fname))

while True:
    try:
        selectedInt = int(input("Выберите файл из списка: "))
        selected = dir_list[selectedInt - 1]
        break
    except Exception:
        print("Ошибка: номер файла должен быть от 1 до {}".format(len(dir_list)))

print('\n\n', selected)
data = io.read_table_from_file(path + selected)

if n >= len(data):
    print("Ньютон 3-й степени нельзя посчитать степени",
          n, ", так как точек всего", len(data))
    
    exit

io.print_table(data)

x = float(input("Введите значение аргумента x: "))


start = find_derivative_newton_polynom(data, n + 1, data[0].x)
end = find_derivative_newton_polynom(data, n + 1, data[-1].x)

y_values = [[], [], [], []]

print("Ньютон 3-й степени:       ", newton_polynom(data, n + 1, x))
print("Cплайн 0 и 0:             ", spline(data, x, 0, 0))
print("Cплайн P''(x0) и 0:       ", spline(data, x, start, 0))
print("Cплайн P''(x0) и P''(xn): ", spline(data, x, start, end))

dots_count = int(data[-1].x - data[0].x + 1) * 100
# dots_count = 200
x_values = np.linspace(data[0].x, data[-1].x, dots_count)

for xi in x_values:
    y_values[0].append(newton_polynom(data, n + 1, xi))
    y_values[1].append(spline(data, xi, 0, 0))
    y_values[2].append(spline(data, xi, start, 0))
    y_values[3].append(spline(data, xi, start, end))

plt.plot(x_values, y_values[0], ':', color='orange', label="Newton")
plt.plot(x_values, y_values[1], '-.', color='red', label="Spline 0 and 0")
plt.plot(x_values, y_values[2], '-.', color='magenta', label="Spline P''(x0) and 0")
plt.plot(x_values, y_values[3], '--', color='cyan', label="Spline P''(x0) and P''(xn)")

plt.legend()

plt.show()
