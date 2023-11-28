#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
#define in std::cin
#define out std::cout

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int M, N;
    in >> M >> N;

    vector<int> molehills;
    for (int i = 0; i < N; i++) {
        int a;
        in >> a;
        molehills.push_back(a);
    }

    int leftP = 0;
    int rightP = 1;
    while (leftP < N) {
        while (molehills[rightP] - molehills[leftP] < M) {
            rightP++;
        }
        answer++;
        leftP = rightP;
        rightP++;
    }

    out << answer;
}