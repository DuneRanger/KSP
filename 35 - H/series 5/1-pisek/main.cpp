#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cmath>

int equalD(double a, double b) {
    // std::cout << floor(a*1000) << " " << floor(b*1000) << std::endl;
    return floor(a*1000) == floor(b*1000);
}

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

// #define in inputFile
// #define out outputFile
#define in std::cin
#define out std::cout

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t sand = 0;
    int inpLen;
    vector<int> blockH;
    vector<double> sandH;

    in >> inpLen;

    for (int i = 0; i < inpLen; i++) {
        int temp;
        in >> temp;
        blockH.push_back(temp);
    }

    for (int i = 0; i < inpLen;) {
        double curH = blockH[i];
        sandH.push_back(curH+0.5);
        i++;
        while (blockH[i] <= sandH[i-1] && i < inpLen) {
            sandH.push_back(sandH[i-1]+1);
            i++;
        }
    }

    // for (int i = 0; i < inpLen; i++) {
    //     cout << sandH[i] << " ";
    // }
    // cout << endl;

    for (int i = inpLen-1; i >= 0;) {
        double curH = blockH[i];
        if (equalD(sandH[i], curH+0.5)) {
            sandH[i] = curH+0.25;
        } else {
            sandH[i] = std::min(sandH[i], curH+0.5);
        }
        i--;
        while (blockH[i] <= sandH[i+1] && i >= 0) {
            if (equalD(sandH[i], sandH[i+1]+1)) {
                sandH[i] = sandH[i]-0.25;
            } else {
                sandH[i] = std::min(sandH[i], sandH[i+1]+1);
            }
            i--;
        }
    }
    // for (int i = 0; i < inpLen; i++) {
    //     cout << sandH[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < inpLen; i++) {
        sand += (sandH[i]-blockH[i])*4000;
    }

    out << sand/1000;
}