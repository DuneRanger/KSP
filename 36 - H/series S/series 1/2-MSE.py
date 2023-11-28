with open("./inputs/2.in", 'r') as inp:
    line = inp.readline().split()
    N, F = int(line[0]), int(line[1])
    constants = list(map(float, inp.readline().split()))
    MSE = 0
    for x in range(N):
        values = list(map(float, inp.readline().split()))
        correctValue = values[-1]
        values[-1] = 1 # inserting bias instead of correct value
        prediction = 0
        for y in range(F+1):
            prediction += constants[y]*values[y]
        MSE += pow((round(prediction - correctValue, 6)), 2)
    MSE /= N
    print(MSE)
