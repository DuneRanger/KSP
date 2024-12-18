#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

// g++ -O2 -std=c++11 -Wall "-Wl,--stack=268435456" main.cpp -o main.exe

struct potion {
    vector<uint64_t> dependencies;
    uint64_t time;
    uint64_t initialTime;
};

vector<potion> potions;

void calculatePotionTime(int potInd, int depth = 0) {
    if (potions[potInd].time == 0) {
        // if (depth%1000==0) {cout << depth << " ";}
        uint64_t maxWaitTime = 0;
        for (int i = 0; i < potions[potInd].dependencies.size(); i++) {
            calculatePotionTime(potions[potInd].dependencies[i], depth+1);
            if (maxWaitTime < potions[potions[potInd].dependencies[i]].time) {
                maxWaitTime = potions[potions[potInd].dependencies[i]].time;
            }
        }
        potions[potInd].time = maxWaitTime + potions[potInd].initialTime;
    }
}

int main() {
    string fileDir = "./inOut/04";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t potNum, depNum;
    inputFile >> potNum >> depNum;
    cout << potNum << " " << depNum << endl;

    for (uint64_t i = 0; i < potNum; i++) {
        potion temp;
        temp.time = 0;
        inputFile >> temp.initialTime;
        potions.push_back(temp);
    }

    for (uint64_t i = 0; i < depNum; i++) {
        uint64_t req, pot;
        inputFile >> req >> pot;
        potions[pot-1].dependencies.push_back(req-1);
    }

    string answer;
    for (uint64_t i = 0; i < potNum; i++) {
        calculatePotionTime(i);

        answer += to_string(potions[i].time - potions[i].initialTime);
        if (i != potNum-1) {
            answer += " ";
        }
    }

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}