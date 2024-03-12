import IO as io
from algorithms import *

points = io.read_table_from_file("./data/data_1.txt")
points.sort(key=lambda point: point.x)

io.print_table(points)
