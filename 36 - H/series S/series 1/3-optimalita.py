N, F = 0, 0

features = []
correctValues = []
predictions = []

with open("./inputs/3.in", 'r') as inp:
    line = inp.readline().split()
    N, F = int(line[0]), int(line[1])
    weights = list(map(float, inp.readline().split()))
    for x in range(N):
        features.append(list(map(float, inp.readline().split())))
        correctValues.append(features[x][-1])
        features[x][-1] = 1 # inserting bias instead of correct value

        prediction = 0
        for y in range(F+1):
            prediction += weights[y]*features[x][y]
        predictions.append(prediction)

optimal = True
for x in range(F):
    evaluation = 0
    for y in range(N):
        evaluation += features[y][x]*(predictions[y] - correctValues[y])
    evaluation *= 2/N
    print(evaluation, abs(evaluation))
    if (abs(evaluation) > pow(10, -6)): optimal = False

print("ANO" if optimal else "NE")