import numpy as np
from numpy import random as rd

n = 2048
a = rd.randint(0, 20, (n, n))
b = rd.randint(0, 20, (n, n))

print(a)
print(b)
c = np.matrix(np.dot(a, b))
#print(c)

a.tofile('C:/users/admin/source/repos/labsParProg/x64/Release/matrix1.bin')
b.tofile('C:/users/admin/source/repos/labsParProg/x64/Release/matrix2.bin')
c.tofile('C:/users/admin/source/repos/labsParProg/x64/Release/result_py.bin')





