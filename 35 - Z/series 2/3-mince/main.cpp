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

    string answer = "";
    int ansLen, winCon, repCon;
    inputFile >> ansLen >> winCon >> repCon;

    int countO = 0;
    int countP = 0;
    int countInd = 1;

    while (winCon-countO > ansLen-winCon-countP) {
        if (countInd%repCon == 0) {
            answer += "P";
            countP++;
        }
        else {
            answer += "O";
            countO++;
        } 
        countInd++;
    }
    while (winCon-countO < ansLen-winCon-countP) {
        if (countInd%repCon == 0) {
            answer += "O";
            countO++;
        }
        else {
            answer += "P";
            countP++;
        } 
        countInd++;
    }
    while (countO + countP < ansLen) {
        if (countInd%2 == 0) {
            answer += "O";
            countO++;
        } else {
            answer += "P";
            countP++;
        }
    }


    cout << answer.length();

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}