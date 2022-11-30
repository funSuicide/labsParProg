import numpy as np


c_result = np.fromfile('C:/users/admin/source/repos/labsParProg/x64/Release/result.bin')
py_result = np.fromfile('C:/users/admin/source/repos/labsParProg/x64/Release/result_py.bin')

if (np.array_equal(c_result, py_result)):
    print("Матрицы равны...")
else:
    print("Матрицы не равны...")
