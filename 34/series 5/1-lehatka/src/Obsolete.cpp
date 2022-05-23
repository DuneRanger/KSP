#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    string fileDir = "inOut/01";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int numOfHippos, numOfChairs;
    // todo: change a and b to numOfHippos and numOfChairs
    // numOfHippos == indexes.size()
    // numOfChairs == chairs.size()
    inputFile >> numOfHippos >> numOfChairs;
    cout << numOfHippos << " " << numOfChairs << endl;

    uint64_t* chairs = new uint64_t[numOfChairs];

    uint64_t c;
    for (int i = 0; i < numOfChairs; i++) {
        inputFile >> c;
        chairs[i] = c;
    }

    inputFile.close();

    int* indexes = new int[numOfHippos];
    indexes[0] = 0; //first hippo will always be at 0
    uint64_t* chairDists = new uint64_t[numOfChairs];
    chairDists[0] = 0; //Added 0 just so the indexes align
    
    //sets each hippo to the next chair after the ideal distancd
    for (int i = 1; i < numOfHippos-1; i++) {
        uint64_t AverageDist = (chairs[numOfChairs-1]-chairs[indexes[i-1]])/(numOfHippos-i);
        //Sets hippo index to a ceiled value of the average distance between hippos
        for (int j = indexes[i-1]; j < numOfChairs; j++) {
            if ((AverageDist + chairs[indexes[i-1]]) < chairs[j]) {
                indexes[i] = j;
                chairDists[i] = chairs[j]-chairs[indexes[i-1]];
                break;
            }
        }
        cout << indexes[i] << " " << AverageDist << " " << (numOfHippos-i) << endl;
    }

    chairDists[numOfHippos-1] = chairs[numOfChairs-1]-chairs[indexes[numOfHippos-2]];
    indexes[numOfHippos-1] = numOfChairs-1;

    for (int i = 0; i < numOfHippos; i++) {
        cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
    }

    uint64_t trueAverage = chairs[numOfChairs-1]/(numOfHippos-1);
    cout << trueAverage << endl << endl;
    
    //todo: convert this into a function
    //This "optimises" the current permutation
    
    for (int i = 1; i < numOfHippos-1; i++) {
        uint64_t chairMinDist = min(chairDists[i], chairDists[i+1]);
        int newInd = indexes[i]-1;
        uint64_t tempDist1 = chairs[newInd] - chairs[indexes[i-1]];
        uint64_t tempDist2 = chairs[indexes[i+1]] - chairs[newInd];
        cout << chairDists[i] << " " << chairDists[i+1] << " " << tempDist1 << " " << tempDist2 << " " << newInd << endl;
        if (chairMinDist < min(tempDist1, tempDist2)) {
            chairDists[i] = tempDist1;
            chairDists[i+1] = tempDist2;
            indexes[i] = newInd;
            i = max(0, i-2); //because i++ will set to to 1
            cout << endl;
        }
    }
    
    uint64_t currentMin = *min_element(chairDists+1, chairDists+numOfHippos);

    //prints current info
    for (int i = 0; i < numOfHippos; i++) {
        cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
    }
    cout << endl;
    
    //todo: create a loop that makes all iterations
    //optimise first permutation, then create more
    //start at chair 1 and check and optimise all permutations
    //until moving chair 1 will create a lower min distance
    //continue like this until you reach the third last chair
    //(second last is already checked as part of the first optimisation)
    //save current permutation and answer
    //if a better one is found, replace it and set new currentMin
    
    for (int i = 1; i < numOfHippos-1; i++) {
        int* newIndexes = new int[numOfHippos];
        copy(indexes, indexes+numOfHippos, newIndexes);
        while (true) {
            newIndexes[i] -= 1;
            uint64_t Dist1 = chairs[newIndexes[i]]-chairs[newIndexes[i-1]];
            uint64_t Dist2 = chairs[newIndexes[i+1]]-chairs[newIndexes[i]];
            if (min(Dist1, Dist2) < currentMin) {
                cout << "no permutation" << endl;
                break;
            } else {
                cout << "new permutation" << endl;
                uint64_t* newChairDists = new uint64_t[numOfChairs];
                copy(chairDists, chairDists+numOfChairs, newChairDists);
                newChairDists[i] = Dist1;
                newChairDists[i+1] = Dist2;
                for (int j = 1; j < numOfHippos-1; j++) {
                    uint64_t chairMinDist = min(newChairDists[j], newChairDists[j+1]);
                    int newInd = newIndexes[j]-1;
                    uint64_t tempDist1 = chairs[newInd] - chairs[newIndexes[j-1]];
                    uint64_t tempDist2 = chairs[newIndexes[j+1]] - chairs[newInd];
                    cout << newChairDists[j] << " " << newChairDists[j+1] << " " << tempDist1 << " " << tempDist2 << " " << newInd << endl;
                    if (chairMinDist < min(tempDist1, tempDist2)) {
                        newChairDists[j] = tempDist1;
                        newChairDists[j+1] = tempDist2;
                        newIndexes[j] = newInd;
                        j = max(0, j-2); //because j++ will set to to 1
                        cout << endl;
                    }
                }
                for (int z = 0; z < numOfHippos; z++) {
                    cout << newIndexes[z] << " " << chairs[newIndexes[z]] << " " << newChairDists[z] << endl;
                }
                cout << currentMin << " " << *min_element(newChairDists+1, newChairDists+numOfHippos) << endl;
                if (currentMin < *min_element(newChairDists+1, newChairDists+numOfHippos)) {
                    currentMin = *min_element(newChairDists+1, newChairDists+numOfHippos);
                    copy(newIndexes, newIndexes+numOfHippos, indexes);
                    copy(newChairDists, newChairDists+numOfHippos, chairDists);
                    cout << "rewritten" << endl;
                    i = 1;
                }
                cout << endl;
            }
        }
    }

    //prints current info
    for (int i = 0; i < numOfHippos; i++) {
        cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
    }

    //writes answer to file
    outputFile.open(fileDir + ".txt", ios::out);
    outputFile << *min_element(chairDists+1, chairDists+numOfHippos) << "\n";
    for (int i = 0; i < numOfHippos; i++) {
        outputFile << indexes[i] << "\n";
    }
    outputFile.close();

    return 0;
}