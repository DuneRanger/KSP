with open("./inputs/1.in", 'r') as inp:
    line = inp.readline().split()
    N, F = int(line[0]), int(line[1])
    constants = list(map(float, inp.readline().split()))
    for x in range(N):
        values = list(map(float, inp.readline().split())) + [1]
        prediction = 0
        for y in range(F+1):
            prediction += constants[y]*values[y]
        print(round(prediction, 6))
