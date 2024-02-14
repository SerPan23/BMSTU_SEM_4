from Point import Point

def read_table_from_file(path):
    table = []
    with open(path, "r") as file:
        for line in file:
            row = list(map(float, line.split(" ")))
            table.append(Point(row[0], row[1], row[2], row[3]))

    return table


def print_table(pointTable):
    COL_COUNT = 4

    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    print("| {:^5s} | {:^10s} | {:^10s} | {:^10s} | {:^10s} |".format(
        "№", "X", "Y", "Y\'", "Y\'\'"))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    for i in range(len(pointTable)):
        print("| {:^5d} | {:^10.3f} | {:^10.3f} | {:^10.3f} | {:^10.3f} |".format(i,
            pointTable[i].x,
            pointTable[i].y,
            pointTable[i].derivative,
            pointTable[i].second_derivative))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")

def print_compare_table(comapre_table):
    COL_COUNT = 2

    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    print("| {:^5s} | {:^10s} | {:^10s} |".format(
        "N", "Newton", "Hermit"))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    for i in range(len(comapre_table)):
        print("| {:^5d} | {:^10.3f} | {:^10.3f} |".format(i,
            comapre_table[i][0],
            comapre_table[i][1]))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")

def print_two_cols_table(data):
    COL_COUNT = 2

    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    print("| {:^5s} | {:^10s} | {:^10s} |".format(
        "№", "x", "y"))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    for i in range(len(data)):
        print("| {:^5d} | {:^10.3f} | {:^10.3f} |".format(i,
            data[i].x,
            data[i].y))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")


def print_sub_table(sub_table):
    count_array = len(sub_table)
    max_len = len(sub_table[0])

    print(("+" + "-" * 22) * count_array + "+")
    print("| {:^20s} | {:^20s}".format("X", "Y"), end=' ')
    for k in range(2, count_array):
        print("| {:^20s}".format("Y" + "\'" * (k - 1)), end=' ')
    print("|")
    print(("+" + "-" * 22) * count_array + "+")

    for i in range(max_len):
        for j in range(count_array):
            if j >= count_array - i:
                print("| {:^20s}".format(" "), end=' ')
            else:
                print("| {:^20.10f}".format(sub_table[j][i]), end=' ')
        print("|")

    print(("+" + "-" * 22) * count_array + "+")
