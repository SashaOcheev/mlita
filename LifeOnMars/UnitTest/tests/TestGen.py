import random

fileName = "input.txt"

count = 1000
limit = 10
speed = 2

f = open(fileName, "w")

f.write(str(count) + ' ')
f.write(str(limit) + ' ')
f.write(str(speed) + '\n')

for i in range(0, 1000):
    f.write(str(random.randint(-1000, 1000)) + ' ')
    f.write(str(random.randint(-1000, 1000)) + '\n')

f.close();
