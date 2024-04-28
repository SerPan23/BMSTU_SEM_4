import numpy as np
# import pandas as pd

def read_data(path:str):
    # df = pd.read_csv('./data/data.csv')
    # n_points = 13
    # x = np.array(list(map(lambda x: x / 10, range(n_points))))
    # y = np.array(list(map(lambda x: x / 10, range(n_points))))
    # z = df.values
    
    x = []
    y = []
    z = []
    with open(path, "r") as f:
        x = list(map(float, f.readline().split('\t')[1:]))
        for line in f:
            line = list(map(float, line.split('\t')))
            y.append(line[0])
            z.append(line[1:])
    
    x = np.array(x)
    y = np.array(y)
    return x, y, z

