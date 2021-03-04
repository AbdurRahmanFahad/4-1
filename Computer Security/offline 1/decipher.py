import numpy as np
from BitVector import *


# Preprocessing -------------------------------------

cyphertext = "54b0f718f62f03c0a455ed78007c6386"
matrix2 = []
cypher_array = []
for i in range(16):
        hex_str = cyphertext[2*i:2*i+2]
        hex_int = int(hex_str, 16)
        cypher_array.append(hex_int)

for i in range(4):
    matrix2.append(cypher_array[i*4:i*4+4])

matrix2 = np.transpose(matrix2).tolist()


# for i in range(4):
#     for j in range(4):
#         print(hex(matrix2[i][j]), end = " ")
#     print("")

