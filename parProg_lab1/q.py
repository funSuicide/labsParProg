import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("C:/users/admin/source/repos/labsParProg/parProg_lab1/results.txt", sep=" ", header=None)
sizes = [32, 64, 128, 256, 512, 1024, 2048, 4096]
average_values = []

i = 0
s = 32
while i < 40:
    q = i
    tmp = 0
    while q < i + 5:
        tmp += data[q]
        q += 1
    average_values.append(tmp / 5)
    print(s, "x", s, ": ", "{0:.2f}".format(float(tmp/5)))
    s = s * 2
    i = i + 5

plt.xlabel('sizeMatrix', fontsize=10, color='black')
plt.ylabel('timeMultiplication', fontsize=10, color='black')
plt.plot(sizes, average_values)
plt.grid(True)
plt.show()
