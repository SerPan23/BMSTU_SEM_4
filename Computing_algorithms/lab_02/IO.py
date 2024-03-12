from Point import Point

def read_table_from_file(path):
    table = []
    with open(path, "r") as file:
        for line in file:
            row = list(map(float, line.split(" ")))
            table.append(Point(*row))

    return table


def print_table(pointTable):
    # COL_COUNT = 4
    COL_COUNT = 2

    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    # print("| {:^5s} | {:^10s} | {:^10s} | {:^10s} | {:^10s} |".format(
    #     "№", "X", "Y", "Y\'", "Y\'\'"))
    print("| {:^5s} | {:^10s} | {:^10s} |".format(
        "№", "X", "Y"))
    print("+" + "-" * 7 + ("+" + "-" * 12) * COL_COUNT + "+")
    for i in range(len(pointTable)):
        print("| {:^5d} | {:^10.3f} | {:^10.3f} |".format(i,
            pointTable[i].x,
            pointTable[i].y,
        ))
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

    
            