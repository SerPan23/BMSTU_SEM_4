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


def data_generator(f, x_start, x_end, x_step, y_start, y_end, y_step):
    x = []
    y = []
    z = []
    
    cur_x = x_start
    while (cur_x <= x_end):
        x.append(cur_x)
        cur_x += x_step
        
    cur_y = y_start
    while (cur_y <= y_end):
        y.append(cur_y)
        cur_y += y_step
        
    for i in range(len(x)):
        tmp = []
        for j in range(len(y)):
            tmp.append(f(x[i], y[j]))
        z.append(tmp)
    
    x = np.array(x)
    y = np.array(y)
    return x, y, z
        
        
