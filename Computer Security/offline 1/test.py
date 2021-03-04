

# from BitVector import *
# x = 0x3
# y = 0x2f
# a = BitVector(intVal = x)
# b = BitVector(intVal = y)
# AES_modulus = BitVector(bitstring='100011011')
# bv3 = a.gf_multiply_modular(b, AES_modulus, 8)
# print(bv3)

# for round in range(1, 11):
#     print(round)



#s = 'hello'
# s = s.ljust(6, '0')
# print(s)
matrix1 = [[2,3,1,1],[1,2,3,1],[1,1,2,3,],[3,1,1,2]]
tmat = matrix1[0][0:4]
matrix1[0] = tmat
tmat = matrix1[1][3:4] + matrix1[1][0:3]
matrix1[1] = tmat
tmat = matrix1[2][2:4] + matrix1[2][0:2]
matrix1[2] = tmat
tmat = matrix1[3][1:4] + matrix1[3][0:1]
matrix1[3] = tmat

print(matrix1)