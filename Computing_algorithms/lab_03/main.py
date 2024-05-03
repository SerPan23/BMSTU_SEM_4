import IO as io
from three_dimensional_interpolation import three_dimensional_interpolation
import numpy as np

algorithms = ["newton", "spline"]


def choose_algorithm():
    print("Choose type of algorithm:\n1) Newton\n2) Spline")
    c = int(input("Enter number of algorithm: "))
    
    return algorithms[c - 1]


# data = io.read_data_from_file("./data/data_1.txt")
x_start, x_end, x_counts = -5, 5, 20
y_start, y_end, y_counts = -3, 4, 50
z_start, z_end, z_counts = -1, 2, 30


def f(x, y, z):
    return 1 / (x + y) - z
    # return z * x * y
    # return (x**2 + y**2) / z
    # return np.exp(2 * x - y) * z**2


data = io.generateData(f, x_start, x_end, x_counts,
                      y_start, y_end, y_counts,
                      z_start, z_end, z_counts)

# io.print_data(data)

point = [-1.152, 1.141, -1.43]
newton_ns = [3, 2, 5]


# algo_list = ["newton", "newton", "newton"]
# algo_list_2 = ["spline", "spline", "spline"]
# print("Newton", three_dimensional_interpolation(data, point, algo_list, newton_ns))
# print("Spline", three_dimensional_interpolation(data, point, algo_list_2, newton_ns))



# point = [float(input(f"Enter {letters} coord: ")) for letters in ['x', 'y', 'z']]

algo_list = ['', '', '']

algorithms = ["newton", "spline"]
print("Choose type of algorithm:\n1) Newton\n2) Spline\n3) Combaniton")
c = int(input("Enter number of algorithm: "))
if c == 1:
    for i in range(3):
        algo_list[i] = algorithms[0]
        # newton_ns[i] = int(input(f"Enter n_{i}: "))
elif c == 2:
    algo_list = [algorithms[1] for _ in range(3)]
else:
    for i in range(3):
        algo_list[i] = choose_algorithm()
        # if algo_list[i] == 'newton':
        #     newton_ns[i] = int(input(f"Enter n_{i}: "))


print("u = f(x, y, z) = ", three_dimensional_interpolation(
    data, point, algo_list, newton_ns))
