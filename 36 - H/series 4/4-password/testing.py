import re

data = {}

with open("data3.txt", 'r') as f:
    lines = f.readlines()
    for x in range(len(lines)):
        lines[x] = re.findall(r"\d+", lines[x])
    
    for x in lines:
        if x[0] in data:
            data[x[0]].append(x[1])
        else:
            data[x[0]] = [x[1]]

with open("test.txt", 'r') as f:
    lines = f.readlines()
    for x in range(len(lines)):
        lines[x] = re.findall(r"\d+", lines[x])

    for x in lines:
        if x[1] in data:
            data[x[1]].append(x[0])
        else:
            data[x[1]] = [x[0]]

highestCount = "700"

with open("data3.txt", 'w') as f:
    print(list(data.keys()))
    keys = list(data.keys())
    keys.sort()
    for x in keys:
        for y in data[x]:
            if (len(data[x]) > len(data[highestCount])): highestCount = x
            f.write(x + " " + y + "\n")

with open("test.txt", 'w') as f:
    f.flush()

print(highestCount + " " + str(len(data[highestCount])))

            

# for x in data.keys():
#     print(x, len(data[x]))

# for y in range(1, 1000000):
#     for x in data["780"]:
#         last = -1
#         it = 0
#         if last == -1:
#             last = int(x)%y
#             it += 1
#         elif int(x)%y != last:
#             break
#         else: it += 1
#     if it == len(x):
#         print(y)

# import random
# for x in data["780"]:
    # random.seed(x)
    # for y in range(10):
    #     print(round(random.randint(0, 100), 3), end=" ")
    # print()


import math
 
def primeFactors(n):
    print(str(n) + ": ", end=" ")
    while (n % 2 == 0):
        print("2", end=" "),
        n = n / 2
    for i in range(3, int(math.sqrt(n))+1,2):
        while n % i== 0:
            print(str(i), end=" "),
            n = n / i
    if (n > 2):
        print(str(n), end=" ")
    print()

for x in data[highestCount]:
    primeFactors(int(x))

def getSum(n): 
    sum = 0
    for digit in str(n):  
      sum += int(digit)       
    return sum