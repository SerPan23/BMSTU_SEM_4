from Point import *

from newton_polynom import newton_polynom

# from spline_algorithm import spline
from spline_algorithm_new import spline

def three_dimensional_interpolation(data, point, algo_list, newton_ns):
    start = 0
    end = 0
    
    matrix_index = 3
    x_index = 0
    y_index = 1
    z_index = 2

    matrix = data[matrix_index]
    x_arr = data[x_index]
    y_arr = data[y_index]
    z_arr = data[z_index]

    z_values = []
    
    tmp = 0
    
    for k in range(len(z_arr)):
        y_values = []

        for i in range(len(y_arr)):
            x_values = []

            for j in range(len(x_arr)):
                x_values.append(Point(x_arr[j], matrix[k][i][j]))

            # print("Значение для нахождение nx: (x_values)")
            # for el in x_values:
            #     print(el.x, el.y)
            # print("end\n")
            
            if algo_list[0] == "newton":
                tmp = Point(y_arr[i], newton_polynom(
                    x_values, newton_ns[0], point[0]))
            else:
                tmp = Point(y_arr[i], spline(x_values, point[0], start, end))
                
            y_values.append(tmp)
            
        # print("Значение для нахождение ny: (y_values)")
            # for el in y_values:
            #     print(el.x, el.y)
            # print("end\n")

        if algo_list[1] == "newton":
            tmp = Point(z_arr[k], newton_polynom(
                y_values, newton_ns[1], point[1]))
        else:
            tmp = Point(z_arr[k], spline(y_values, point[1], start, end))
            
        z_values.append(tmp)
    
    # print("Значение для нахождение полином Ньютона nz: (z_values)")
    # for el in z_values:
    #     print(el.x, el.y)
    # print("end\n")
        
    result = 0
    if algo_list[2] == "newton":
        result = newton_polynom(z_values, newton_ns[2], point[2])
    else:
        result = spline(z_values, point[2], start, end)

    return result
