#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int main() {
    string fileDir = "./inOut/test";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t answer = 0;
    int inpLen;
    inputFile >> inpLen;


    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}