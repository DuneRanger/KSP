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

    std::map<int, uint64_t> chickensBornAtTime;

    for (int i = 1; i <= D; i++) {
        chickensBornAtTime.insert(std::make_pair(i, 0));
    }
    chickensBornAtTime[K] = 1;
    
    for (int i = K; i <= D; i++) {
        if (chickensBornAtTime[K] == 0) continue;
        for (int j = i+K+P; j <= D; j += P) {
            chickensBornAtTime[j] += chickensBornAtTime[i];
        }
    }

    uint64_t chickenCount = 0;
    for (int i = K; i <= D; i++) {
        chickenCount += chickensBornAtTime[i];
    }

    out << chickenCount;
}