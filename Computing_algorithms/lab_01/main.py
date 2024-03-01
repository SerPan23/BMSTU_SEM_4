import IO as io
from Algorithms import *

# TODO: Make Ermite method


points = io.read_table_from_file("./data/data_2.txt")
points.sort(key=lambda point: point.x)

io.print_table(points)

x = float(input("Enter x: "))
n = int(input("Enter n: "))

index = get_index(points, x)
working_points = get_works_points(points, index, n)

newton_table = get_newton_table(working_points)
ermite_table = get_ermite_table(working_points)

print("Newton subs table:")
io.print_sub_table(newton_table)

print("Ermite subs table:")
io.print_sub_table(ermite_table)

# RESULTS
newton_result = get_approximate_value(newton_table, x, n)
print("Newton result: ", newton_result)

ermite_result = get_approximate_value(ermite_table, x, n)
print("Ermite result: ", ermite_result)

print("Root by Newton: ", get_root_by_Newton(points, n))
print("Root by Ermite: ", get_root_by_Ermite(points, n))

compare_table = get_compare_Newton_Ermite(points, x)
print("Compare table:")
io.print_compare_table(compare_table)


print("\n\n--------Solving nonlinear equations--------\n")

# Solve system of nonlinear equations
n = 4
data_func_1_y_x = [
    Point(0.005, 0.137, None, None),
    Point(0.035, 0.343, None, None),
    Point(0.055, 0.421, None, None),
    Point(0.065, 0.454, None, None),
    Point(0.135, 0.626, None, None),
    Point(0.155, 0.664, None, None),
    Point(0.195, 0.731, None, None),
    Point(0.275, 0.843, None, None),
    Point(0.315, 0.891, None, None),
    Point(0.405, 0.985, None, None),
]

data_func_2_x_y = [
    Point(0.1, -0.284, None, None),
    Point(0.3, -0.300, None, None),
    Point(0.4, -0.293, None, None),
    Point(0.48, -0.266, None, None),
    Point(0.6, -0.165, None, None),
    Point(0.68, -0.037, None, None),
    Point(0.75, 0.128, None, None),
    Point(0.88, 0.610, None, None),
    Point(0.95, 0.988, None, None),
    Point(1.03, 1.547, None, None),
]

data_func_1_x_y = get_rev_data(data_func_1_y_x)

new_data_func_1_x_y = []

for point in data_func_2_x_y:
    index = get_index(data_func_1_x_y, point.x)
    working_points = get_works_points(data_func_1_x_y, index, n)

    newton_table = get_newton_table(working_points)
    new_data_func_1_x_y.append(Point(
        point.x, get_approximate_value(newton_table, point.x, n), None, None))
    
new_data_func_2_x_y = []

for point in data_func_1_x_y:
    index = get_index(data_func_2_x_y, point.x)
    working_points = get_works_points(data_func_2_x_y, index, n)

    newton_table = get_newton_table(working_points)
    new_data_func_2_x_y.append(Point(
        point.x, get_approximate_value(newton_table, point.x, n), None, None))

print("data_1_new")
io.print_two_cols_table(new_data_func_1_x_y)
print("data_2")
io.print_two_cols_table(data_func_2_x_y)

new_data = []
for i in range(len(new_data_func_1_x_y)):
    new_data.append(Point(
        new_data_func_1_x_y[i].x, new_data_func_1_x_y[i].y - data_func_2_x_y[i].y, None, None))
    
new_data_2 = []
for i in range(len(new_data_func_2_x_y)):
    new_data_2.append(Point(
        data_func_1_x_y[i].x, data_func_1_x_y[i].y - new_data_func_2_x_y[i].y, None, None))
    
print("new data")
io.print_two_cols_table(new_data)

solve = get_root_by_Newton(new_data, n)
print("Solve: ", solve)


print("data_1")
io.print_two_cols_table(data_func_1_x_y)
print("data_2_new")
io.print_two_cols_table(new_data_func_2_x_y)

print("new data 2")
io.print_two_cols_table(new_data_2)

solve_2 = get_root_by_Newton(new_data_2, n)
print("Solve_2: ", solve_2)
    

