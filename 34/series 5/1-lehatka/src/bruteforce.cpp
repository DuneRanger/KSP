#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int main() {
    string fileDir = "inOut/02";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int numOfHippos, numOfChairs;
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

    uint64_t* tempIndexes = new uint64_t[numOfHippos];
    uint64_t* tempChairDists = new uint64_t[numOfHippos];
    copy(indexes, indexes+numOfHippos, tempIndexes);
    copy(chairDists, chairDists+numOfHippos, tempChairDists);

    cout << "here" << endl;

    for (int i = 1; i < numOfHippos-1; i++) {
        int newInd = tempIndexes[i]-1;
        uint64_t tempDist1 = chairs[newInd] - chairs[tempIndexes[i-1]];
        uint64_t tempDist2 = chairs[indexes[i+1]] - chairs[newInd];
        while (min(tempDist1, tempDist2) > currentMin) {
            cout << newInd << " " << tempDist1 << " " << tempDist2 << endl;
            tempChairDists[i] = tempDist1;
            tempChairDists[i+1] = tempDist2;
            tempIndexes[i] = newInd;
            
            for (int j = i+1; j < numOfHippos-1; j++) {
                newInd = tempIndexes[j]-1;
                tempDist1 = chairs[newInd] - chairs[tempIndexes[j-1]];
                tempDist2 = chairs[indexes[j+1]] - chairs[newInd];
                if (currentMin < min(tempDist1, tempDist2)) {
                    cout << newInd << " " << tempDist1 << " " << tempDist2 << endl;
                    tempChairDists[j] = tempDist1;
                    tempChairDists[j+1] = tempDist2;
                    tempIndexes[j] = newInd;
                } else {
                    break;
                }
            }
            
            newInd = tempIndexes[i]-1;
            tempDist1 = chairs[newInd] - chairs[tempIndexes[i-1]];
            tempDist2 = chairs[indexes[i+1]] - chairs[newInd];
            cout << endl;
        }
        uint64_t tempMin = *min_element(tempChairDists+1, tempChairDists+numOfHippos);
        if (currentMin < tempMin) {
            currentMin = tempMin;
            copy(tempIndexes, tempIndexes+numOfHippos, indexes);
            copy(tempChairDists, tempChairDists+numOfHippos, chairDists);
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