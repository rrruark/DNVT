#Minimum Hamming Distance Excluding Cyclically Permutable Codeword Calculator
#Robert Ruark
#2022

import numpy as np

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
        #print(format(x, '#010b'));
print("Total cyclically permutable codewords: " + str(len(cpcw)))
print(cpcw)
class Solution(object):
   def hammingDistance(self, x, y):
      """
      :type x: int
      :type y: int
      :rtype: int
      """
      ans = 0
      for i in range(31,-1,-1):
         b1= x>>i&1
         b2 = y>>i&1
         ans+= not(b1==b2)
         #if not(b1==b2):
            # print(b1,b2,i)
      return ans
ob1 = Solution()

cpcw2=cpcw
for x in cpcw2:
    for y in cpcw2:
        if(ob1.hammingDistance(x,y)==1):
            print("Removing:" + format(y, '#010b'))
            cpcw2.remove(y)

print("Remaining cyclically permutable codewords: " + str(len(cpcw2)))
print(cpcw2)