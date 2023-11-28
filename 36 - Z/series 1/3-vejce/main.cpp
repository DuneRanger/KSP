#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

std::string fileDir = "./inOut/05";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    int K, P, D;
    in >> K >> P >> D;

    std::vector<uint64_t> chickens;
    std::vector<uint64_t> eggs;

    for (int i = 1; i <= K; i++) {
        eggs.push_back(0);
    }
    eggs[K] = 1;
    for (int i = 1; i <= P; i++) {
        chickens.push_back(0);
    }
    
    uint64_t eggsHatched = 0;
    uint64_t eggsLaid = 0;
    while (D > -1) {
        eggsHatched = eggs[1];
        for (int i = 2; i <= K; i++) {
            eggs[i-1] = eggs[i];
        }

        eggsLaid = chickens[1];
        for (int i = 2; i <= P; i++) {
            chickens[i-1] = chickens[i];
        }
        
        eggs[K] = eggsLaid;
        chickens[P] = eggsHatched + eggsLaid; // + eggsLaid is renewing the old chickens from chickens[1]

        D--;
    }

    uint64_t chickenCount = 0;
    for (int i = 1; i <= P; i++) {
        chickenCount += chickens[i];
    }

    out << chickenCount;
}