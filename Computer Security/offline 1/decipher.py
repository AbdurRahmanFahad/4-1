output_file = "out.txt"
output_file2 = "out2.txt"

def decrypt_file():
    file1 = open(output_file, 'rb')
    file2 = open(output_file2, 'wb')
    while True:
        data = file1.read(32)
        if not data:
            break
        pltext = data
        pltext = data.decode('utf-8')
        #pltext2 = decipher_func(pltext)
        print(pltext)
        #pltext = pltext.replace('\n', '')
        #deciphertext = decrypt(key, ciphertext)
        #deciphertext = bytes.fromhex(deciphertext)
        #file2.write(pltext2)
    file1.close()
    file2.close()

decrypt_file()