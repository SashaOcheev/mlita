import random

fileName = "input.txt"

count = 10**5

f = open(fileName, "w")

for k in range(0, 2):
    for i in range(0, count):
        f.write(str(chr(random.randint(ord('a'), ord('z')))))
    f.write('\n')

f.close();
