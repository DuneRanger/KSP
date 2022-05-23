#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int numOfHippos, numOfChairs;
uint64_t* chairs;

void recursiveShit(int* newIndexes, uint64_t* newChairDists, int* indexes, uint64_t* chairDists, int index = 1, int joke = 0) {
    cout << index << " " << joke << endl;
    if (joke != 0) {
        cout << joke << " .       " << newIndexes[index-2] << endl;
        newIndexes[index-1] = joke;
        newChairDists[index-1] = chairs[joke]-chairs[newIndexes[index-2]];
    }
    if (index == numOfHippos-1) {
        newChairDists[numOfHippos-1] = chairs[numOfChairs-1]-chairs[newIndexes[numOfHippos-2]];
        newIndexes[numOfHippos-1] = numOfChairs-1;
        cout << *chairDists << endl;
        cout << "hery" << endl;
        for (int i = 0; i < numOfHippos; i++) {
            cout << newChairDists[i] << endl;
        }
        cout << *min_element(chairDists+1, chairDists+numOfHippos) << " " << *min_element(newChairDists+1, newChairDists+numOfHippos) << endl;
        if (*min_element(chairDists+1, chairDists+numOfHippos) < *min_element(newChairDists+1, newChairDists+numOfHippos)) {
            cout << "iffed";
            copy(newIndexes, newIndexes+numOfHippos, indexes);  
            copy(newChairDists, newChairDists+numOfHippos, chairDists);
        }
        cout << "here";
        //for (int i = 0; i < numOfHippos; i++) {
        //    cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
        //}
        return;
    }

    

    uint64_t AverageDist = (chairs[numOfChairs-1]-chairs[newIndexes[index-1]])/(numOfHippos-index);

    //Sets hippo index to a ceiled value of the average distance between hippos
    for (int j = newIndexes[index-1]; j < numOfChairs; j++) {
        if ((AverageDist + chairs[newIndexes[index-1]]) < chairs[j]) {
            recursiveShit(newIndexes, newChairDists, indexes, chairDists, index+1, j);
            recursiveShit(newIndexes, newChairDists, indexes, chairDists, index+1, j-1);
            break;
        }
    }
}



int main() {
    string fileDir = "01";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    // todo: change a and b to numOfHippos and numOfChairs
    // numOfHippos == indexes.size()
    // numOfChairs == chairs.size()
    inputFile >> numOfHippos >> numOfChairs;
    cout << numOfHippos << " " << numOfChairs << endl;

    chairs = new uint64_t[numOfChairs];

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

    int* tempIndexes = new int[numOfHippos];
    tempIndexes[0] = 0; //first hippo will always be at 0
    uint64_t* tempChairDists = new uint64_t[numOfChairs];
    tempChairDists[0] = 0; //Added 0 just so the indexes align

    cout << "here" << endl;

    recursiveShit(tempIndexes, tempChairDists, indexes, chairDists);

    // for (int i = 0; i < numOfHippos; i++) {
    //     cout << tempIndexes[i] << " " << chairs[tempIndexes[i]] << " " << tempChairDists[i] << endl;
    // }


    // uint64_t trueAverage = chairs[numOfChairs-1]/(numOfHippos-1);
    // cout << trueAverage << endl << endl;
    
    //todo: convert this into a function
    //This "optimises" the current permutation
    
    // for (int i = 1; i < numOfHippos-1; i++) {
    //     uint64_t chairMinDist = min(chairDists[i], chairDists[i+1]);
    //     int newInd = indexes[i]-1;
    //     uint64_t tempDist1 = chairs[newInd] - chairs[indexes[i-1]];
    //     uint64_t tempDist2 = chairs[indexes[i+1]] - chairs[newInd];
    //     cout << chairDists[i] << " " << chairDists[i+1] << " " << tempDist1 << " " << tempDist2 << " " << newInd << endl;
    //     if (chairMinDist < min(tempDist1, tempDist2)) {
    //         chairDists[i] = tempDist1;
    //         chairDists[i+1] = tempDist2;
    //         indexes[i] = newInd;
    //         i = max(0, i-2); //because i++ will set to to 1
    //         cout << endl;
    //     }
    // }
    
    uint64_t currentMin = *min_element(chairDists+1, chairDists+numOfHippos);

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
