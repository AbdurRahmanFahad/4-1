from BitVector import *

def print_16_box(arr):
    for i in range(0, 16):
        for j in range(0, 16):
            print(hex(arr[i * 16 + j]).lstrip("0x").rjust(2, '0'), end=' ')
        print()


def generate_sbox():
    boxx = []
    AES_modulus = BitVector(bitstring='100011011')
    bv = BitVector(intVal=0x63, size=8)
    count = 1
    
    for i in range(16):
        for j in range(16):
            if i == 0 and j == 0:
                boxx.append(0x63)
                continue    
            a = BitVector(intVal=count, size=8)
            b = a.gf_MI(AES_modulus, 8)
            z = bv ^ b ^ (b << 1) ^ (b << 1) ^ (b << 1) ^ (b << 1)  
            boxx.append(z.intValue())
            count +=1

    return boxx

def generate_inv_sbox():
    boxx = []
    AES_modulus = BitVector(bitstring='100011011')
    bv = BitVector(intVal=0x5, size=8)
    count = 0
    
    for i in range(16):
        for j in range(16):
            if count == 0x63:
                boxx.append(0)
                count += 1
                continue    
            a = BitVector(intVal=count, size=8)
            b = bv ^ (a<<1) ^ (a<<2) ^ (a<<3)
            z = b.gf_MI(AES_modulus, 8)  
            boxx.append(z.intValue())
            count +=1
            
    return boxx

arr = generate_inv_sbox()
print_16_box(arr)
