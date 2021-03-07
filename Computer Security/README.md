# AES OFFLINE

## Topic:

In this assignment you will have to implement the Advanced Encryption Standard (AES)
algorithm for 128-bit key. Total marks of this assignment is 30.

### Overview of AES:

Advanced Encryption Standard (AES) is a popular and widely adopted symmetric key
encryption algorithm.
AES uses repeat cycles or "rounds". There are 10, 12, or 14 rounds for keys of 128, 192,
and 256 bits, respectively.
Each round of Algorithm consists of four

### Steps:

- [x] ### subBytes: for each byte in the array, use its value as an index into a fixed 256-
      element lookup table, and replace its value in the state by the byte value stored at
      that location in the table. You can find the table and the inverse table on the web.
- [x] ### shiftRows: Let Ri denote the ith row in state. Shift R0 in the state left 0 bytes (i.e.,
      no change); shift R1 left 1 byte; shift R2 left 2 bytes; shift R3 left 3 bytes. These
      are circular shifts. They do not affect the individual byte values themselves. Shift
      left for decryption.
- [x] ### mixColumns: for each column of the state, replace the column by its value
      multiplied by a fixed 4 x 4 matrix of integers (in a particular Galois Field). This is
      a relatively complex step, but if you utilize the BitVector library demonstrated in
      the sessional class it will be simple matrix multiplication. Note that the inverse
      operation multiplies by a different matrix.
- [x] ### addRoundkey: XOR the state with a 128-bit round key derived from the original
      key K by a recursive process.
