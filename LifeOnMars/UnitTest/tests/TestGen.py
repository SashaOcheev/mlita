import random

fileName = "input.txt"
count = 1000
limit = 1
speed = 1

f = open(fileName, "w")

f.write(str(count) + ' ')
f.write(str(limit) + ' ')
f.write(str(speed) + '\n')

for i in range(0, count):
    f.write(str(random.randint(-1000, 1000)) + ' ')
    f.write(str(random.randint(-1000, 1000)) + '\n')

f.close();
