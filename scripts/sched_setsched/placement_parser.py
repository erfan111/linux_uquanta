import numpy as np
import sys

data = np.genfromtxt(sys.argv[1],  delimiter=" ", dtype=int)
print(data.shape)
with open( sys.argv[1] + ".output", "w") as output:
    for row in data:
        table = np.zeros(40, dtype=int)
        for cpu in row:
            table[cpu]+=1
        for i in table:
            output.write("{} ".format(i))
        output.write("\n")
