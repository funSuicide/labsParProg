import numpy as np
from numpy import random as rd

n = 4096
a = rd.randint(0, 20, (n, n))
b = rd.randint(0, 20, (n, n))

print(a)
print(b)
c = np.matrix(np.dot(a, b))
print(c)

np.savetxt('C:/users/admin/source/repos/labsParProg/parProg_lab1/matrix1.txt', a, fmt='%3.0d', delimiter=' ')
np.savetxt('C:/users/admin/source/repos/labsParProg/parProg_lab1/matrix2.txt', b, fmt='%3.0d', delimiter=' ')
np.savetxt('C:/users/admin/source/repos/labsParProg/parProg_lab1/result_py.txt', c, fmt='%3.0d', delimiter=' ')



