import numpy as np
from BitVector import *


# Preprocessing 1 -------------------------------------------------


#s = "Two One Nine Two"
#key = "Thats my Kung Fu"

s = "WillGraduateSoon"
key = "BUET CSE16 Batch"

arr1 = []

for c in key:
    arr1.append(ord(c))

Sbox = [
    [0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76],
    [0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0],
    [0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15],
    [0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75],
    [0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84],
    [0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF],
    [0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8],
    [0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2],
    [0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73],
    [0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB],
    [0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79],
    [0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08],
    [0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A],
    [0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E],
    [0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF],
    [0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16],
]

ws = []
w0 = []

for i in range(4):
    w0 = arr1[i*4 : i*4+4]
    ws.append(w0)

round_constant = [0x01, 0x00, 0x00, 0x00]

#loop for ROUNDKEYS ------------------------------------------------
for round in range(10):

    temp1 = ws[round*4 + 3]
    wg = temp1[1:4] + temp1[0:1]

    # S-box Substitution
    
    for i in range(len(wg)):
        tt = wg[i]
        p1 = 0xF
        p2 = 0xF0
        y = tt & p1
        x = (tt & p2)>>4
        wg[i] = Sbox[x][y]
        wg[i] = wg[i] ^ round_constant[i]

    
    if round_constant[0] >= 128:
        round_constant[0] = (round_constant[0]*2)^0x11B
    else:
        round_constant[0] = round_constant[0]*2

    w4 = []
    w5 = []
    w6 = []
    w7 = []

    for i in range(4):
        x = ws[round*4][i]^wg[i]
        w4.append(x)

    ws.append(w4)

    for i in range(4):
        x = ws[round*4+4][i]^ws[round*4+1][i]
        w5.append(x)

    ws.append(w5)

    for i in range(4):
        x = ws[round*4+5][i]^ws[round*4+2][i]
        w6.append(x)

    ws.append(w6)

    for i in range(4):
        x = ws[round*4+6][i]^ws[round*4+3][i]
        w7.append(x)

    ws.append(w7)


# count = 0
# for i in range(len(ws)):
#     for j in range(len(ws[i])):
#         count = count + 1
#         print(hex(ws[i][j]), end = " ")
#         if count%16 == 0:
#             print("-")

# Preprocessing 2 -------------------------------------------------

matrix1 = []
arr2 = []
for c in s:
    arr2.append(ord(c))

for i in range(4):
    matrix1.append(arr2[i*4:i*4+4])

matrix1 = np.transpose(matrix1).tolist()

keymatrix = ws[0:4]
keymatrix = np.transpose(keymatrix)
for i in range(4):
    for j in range(4):
        matrix1[i][j] ^= keymatrix[i][j]


for round in range(1, 11):

    # Substitution -------------------------------------------------

    for i in range(4):
        for j in range(4):
                tt = matrix1[i][j]
                p1 = 0xF
                p2 = 0xF0
                y = tt & p1
                x = (tt & p2)>>4
                matrix1[i][j] = Sbox[x][y]


    # Shifting row -------------------------------------------------

    tmat = matrix1[0][0:4]
    matrix1[0] = tmat
    tmat = matrix1[1][1:4] + matrix1[1][0:1]
    matrix1[1] = tmat
    tmat = matrix1[2][2:4] + matrix1[2][0:2]
    matrix1[2] = tmat
    tmat = matrix1[3][3:4] + matrix1[3][0:3]
    matrix1[3] = tmat

    # Mixing Column -------------------------------------------------
    if round != 10:
        Mixer = [[2,3,1,1],[1,2,3,1],[1,1,2,3,],[3,1,1,2]]
        result = [[0, 0, 0, 0], 
                [0, 0, 0, 0], 
                [0, 0, 0, 0],
                [0, 0, 0, 0]] 
        AES_modulus = BitVector(bitstring='100011011')

        for i in range(4): 
            for j in range(4): 
                for k in range(4):
                    x = Mixer[i][k]
                    y = matrix1[k][j]
                    a = BitVector(intVal = x)
                    b = BitVector(intVal = y)
                    bv3 = a.gf_multiply_modular(b, AES_modulus, 8)   
                    result[i][j] = result[i][j] ^ bv3.intValue() 

        matrix1 = result

    # New keymatrix -------------------------------------------------

    #keymatrix = ws[0:4]
    keymatrix = ws[round*4 : round*4 + 4]
    keymatrix = np.transpose(keymatrix)

    matrix1 = matrix1 ^ keymatrix
    matrix1 = matrix1.tolist()

# Printing -------------------------------------------------

# for i in range(4):
#     for j in range(4):
#         print(hex(matrix1[i][j]), end = " ")
#     print("")

cyphertext = ""

for i in range(4):
    for j in range(4):
        tempo = hex(matrix1[j][i]).lstrip("0x")
        if len(tempo) == 1:
            cyphertext += "0"
        if len(tempo) == 0:
            cyphertext += "00"    
            
        cyphertext += tempo

print(cyphertext)

if cyphertext == "54b0f718f62f03c0a455ed78007c6386":
    print("yeeeeeeeeeeeeeeeeeee")