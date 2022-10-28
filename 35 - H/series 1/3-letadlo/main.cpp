#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int main() {
    string fileDir = "./inOut/04";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t possibilities;
    int inpLen;
    string inp;
    inputFile >> inpLen;
    cout << inpLen << endl;
    inputFile >> inp;
    
    for (int i = 0; i < inpLen; i++) {
        
    }


    outputFile.open(fileDir + ".out", ios::out);
    outputFile << possibilities;
    outputFile.close();
}