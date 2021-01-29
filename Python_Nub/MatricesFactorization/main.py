# AUTHOR : sammyon7

import numpy as np
from MatrixFac import MF

R = np.array([
    [5, 3, 0, 1],
    [4, 0, 0, 1],
    [1, 1, 0, 5],
    [1, 0, 0, 4],
    [0, 1, 5, 4],
])

mf = MF(R, K=2, alpha=0.1, beta=0.01, iterations=20)
training_process = mf.train()
print(mf.P)
print(mf.Q)
print(mf.full_matrix())