import numpy as np
from timeit import default_timer as timer

with open("test_case.txt", "r") as input:
    test_case = input.readlines()

    i = 0
    for line in test_case: 
        i += 1
        lst = [float(x) for x in line.split()]

        start = timer()

        lst = np.sort(lst)

        end = timer()
        print(f"Sort time [{i}]:\t{round((end - start) * 1000)}\tms")