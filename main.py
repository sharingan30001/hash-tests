import random, string, sys
from random import randint
def randomword(length):
   letters = string.ascii_lowercase
   return ''.join(random.choice(letters) for i in range(length))


file1 = open("output_for_string.txt", "w")
file2 = open("output_for_substr.txt", "w")
for i in range(100):
   n = randint(1, 100000)
   s = randomword(n)
   file1.write(s)
   file1.write('\n')
   x = randint(1, n)
   y = randint(x, n)
   file2.write(s[x : y])
   file2.write('\n')
file1.close()
file2.close()