#Cyclically permutable codeword calculator
#Robert Ruark
#2022

word_len = 8
word_size = 256

cpcw=[]
def ISHFTC(n, d, N):  
    return ((n << d) % (1 << N)) | (n >> (N - d))

for x in range(0,word_size):
    collide = 0;
    for d in range(0,word_len):
        z = ISHFTC(x, d, word_len)
        for y in cpcw:
            if (z == y):
                collide = 1
    if(not collide):
        cpcw.append(x)
        print(format(x, '#010b'));
print("Total cyclically permutable codewords: " + str(len(cpcw)))