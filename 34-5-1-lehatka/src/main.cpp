#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string fileDir = "inOut/01";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int a, b;
    inputFile >> a >> b;
    cout << a << " " << b << endl;

    vector<unsigned long long> chairs;

    unsigned long long c;
    for (int i = 0; i < b; i++) {
        inputFile >> c;
        chairs.push_back(c);
    }

    inputFile.close();

    vector<int> indexes = {0}; //first hippo will always be at 0
    vector<unsigned long long> chairDists= {0}; //Added 0 just so the indexes align
    for (int i = 1; i < a-1; i++) {
        unsigned long long AverageDist = (chairs[chairs.size()-1]-chairs[indexes[i-1]])/(a-i);
        //Sets hippo index to a ceiled value of the average distance between hippos
        for (int j = indexes[i-1]; j < chairs.size(); j++) {
            if ((AverageDist + chairs[indexes[i-1]]) < chairs[j]) {
                indexes.push_back(j);
                chairDists.push_back(chairs[j]-chairs[indexes[i-1]]);
                break;
            }
        }
        cout << indexes[i] << " " << AverageDist << " " << (a-i) << endl;
    }
    chairDists.push_back(chairs[chairs.size()-1]-chairs[indexes[indexes.size()-1]]);
    indexes.push_back(chairs.size()-1);
    cout << chairs[indexes[indexes.size()-1]]-chairs[indexes[indexes.size()-2]] << endl;

    for (int i = 0; i < indexes.size(); i++) {
        cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
    }
    unsigned long long currentMin = chairs[indexes[indexes.size()-1]]-chairs[indexes[indexes.size()-2]];
    unsigned long long trueAverage = chairs[chairs.size()-1]/(a-1);
    cout << currentMin << " " << trueAverage << endl;

    int temp = 1;
    while (temp < a-1) {
        unsigned long long pairMin = min(chairDists[temp], chairDists[temp+1]);
        int tempInd = indexes[temp]-1;
        unsigned long long tempDist1 = chairs[tempInd] - chairs[indexes[temp-1]];
        unsigned long long tempDist2 = chairs[indexes[temp+1]] - chairs[tempInd];
        cout << chairDists[temp] << " " << chairDists[temp+1] << " " << tempDist1 << " " << tempDist2 << " " << tempInd << endl;
        if (pairMin < min(tempDist1, tempDist2)) {
            chairDists[temp] = tempDist1;
            chairDists[temp+1] = tempDist2;
            indexes[temp] = tempInd;
            temp = 0;
            cout << endl;
        }
        temp++;
    }

    for (int i = 0; i < indexes.size(); i++) {
        cout << indexes[i] << " " << chairs[indexes[i]] << " " << chairDists[i] << endl;
    }

    outputFile.open(fileDir + ".txt", ios::out);
    outputFile << *min_element(chairDists.begin()+1, chairDists.end()) << "\n";
    for (int i = 0; i < a; i++) {
        outputFile << indexes[i] << "\n";
    }
    outputFile.close();

    return 0;
}