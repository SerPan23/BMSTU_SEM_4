from Point import Point
import numpy as np

def generateData(f, x_s, x_e, x_c, y_s, y_e, y_c, z_s, z_e, z_c):
    x_index = 0
    y_index = 1
    z_index = 2
    matrix_index = 3
    dataTable = [[], [], [], [[]]]

    dataTable[x_index] = np.linspace(x_s, x_e, x_c)
    dataTable[y_index] = np.linspace(y_s, y_e, y_c)
    dataTable[z_index] = np.linspace(z_s, z_e, z_c)


    for i in range(z_c):
        dataTable[matrix_index].append([])
        for j in range(y_c):
            dataTable[matrix_index][i].append([])
            for k in range(x_c):
                dataTable[matrix_index][i][j].append(f(dataTable[x_index][k],
                                                        dataTable[y_index][j],
                                                        dataTable[z_index][i]))
    return dataTable

def read_data_from_file(path):
    matrix = [[]]
    x_data = []
    y_data = []
    z_data = []
    
    file = open(path)
    flag_add_x = False
    flag_add_y = False
    z_index = 0
    y_index = 0
    for line in file.readlines():
        row = line.split("\n")[0].split("\t")

        if "z=" in row[0]:
            zStr = row[0].split("z=")
            z_data.append(float(zStr[1]))
        elif "y\\x" in row[0]:
            if flag_add_x:
                continue
            for i in range(1, len(row)):
                x_data.append(float(row[i]))
            flag_add_x = True
        else:
            if "end" in row[0]:
                continue
            if not row[0].isdigit():
                z_index += 1
                matrix.append([])
                y_index = 0
                flag_add_y = True
                continue

            if not flag_add_y:
                y_data.append(float(row[0]))

            matrix[z_index].append([])
            for i in range(1, len(row)):
                matrix[z_index][y_index].append(float(row[i]))
            y_index += 1
    
    file.close()

    return [x_data, y_data, z_data, matrix]


def print_data(data):    
    matrix = data[3]
    x_data = data[0]
    y_data = data[1]
    z_data = data[2]
    
    for k in range(len(z_data)):
        print("z =", z_data[k])
        print(("+" + "-" * 10) * (len(x_data) + 1) + "+")
        print("| {:^8s}".format("Y / X"), end=" ")
        for i in range(len(x_data)):
            print("| {:^8.2f}".format(x_data[i]), end=" ")
        print("|")
        print(("+" + "-" * 10) * (len(x_data) + 1) + "+")
        for i in range(len(matrix[k])):
            print("| {:^8.3f}".format(y_data[i]), end=" ")
            for j in range(len(matrix[2][i])):
                if matrix[k][i][j] == None:
                    print("| {:^8s}".format("inf"), end=" ")
                else:
                    print("| {:^8.3f}".format(
                        matrix[k][i][j]), end=" ")
            print("|")
        print(("+" + "-" * 10) * (len(x_data) + 1) + "+")

    
            