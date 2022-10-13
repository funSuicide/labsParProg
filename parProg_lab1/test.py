import numpy as np

c_result = np.genfromtxt('C:/users/admin/source/repos/labsParProg/parProg_lab1/result.txt')
py_result = np.genfromtxt('C:/users/admin/source/repos/labsParProg/parProg_lab1/result_py.txt')

if (np.array_equal(c_result, py_result)):
    print("Матрицы равны...")
else:
    print("Матрицы не равны...")
