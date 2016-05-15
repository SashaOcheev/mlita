import random

fileName = "input.txt"

ln = 2000
col = 2000
divider = 1000000000

f = open(fileName, "w")

f.write(str(ln) + ' ')
f.write(str(col) + ' ')
f.write(str(divider) + '\n')

for i in range(0, col):
    f.write(str(random.randint(0, divider)) + ' ')

f.close();
