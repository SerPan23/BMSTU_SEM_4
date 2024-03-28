import IO as io
from three_dimensional_interpolation import three_dimensional_interpolation

algorithms = ["newton", "spline"]


def choose_algorithm():
    print("Choose type of algorithm:\n1) Newton\n2) Spline")
    c = int(input("Enter number of algorithm: "))
    
    return algorithms[c - 1]



data = io.read_data_from_file("./data/data_1.txt")

io.print_data(data)

point = [1.5, 1.5, 1.5]
newton_ns = [1, 1, 1]


# algo_list = ["newton", "newton", "newton"]
# algo_list_2 = ["spline", "spline", "spline"]
# print("Newton", three_dimensional_interpolation(data, point, algo_list, newton_ns))
# print("Spline", three_dimensional_interpolation(data, point, algo_list_2, newton_ns))



point = [float(input(f"Enter {letters} coord: ")) for letters in ['x', 'y', 'z']]

algo_list = ['', '', '']

algorithms = ["newton", "spline"]
print("Choose type of algorithm:\n1) Newton\n2) Spline\n3) Combaniton")
c = int(input("Enter number of algorithm: "))
if c == 1:
    for i in range(3):
        algo_list[i] = algorithms[0]
        newton_ns[i] = int(input(f"Enter n_{i}: "))
elif c == 2:
    algo_list = [algorithms[1] for _ in range(3)]
else:
    for i in range(3):
        algo_list[i] = choose_algorithm()
        if algo_list[i] == 'newton':
            newton_ns[i] = int(input(f"Enter n_{i}: "))


print("u = f(x, y, z) = ", three_dimensional_interpolation(
    data, point, algo_list, newton_ns))
