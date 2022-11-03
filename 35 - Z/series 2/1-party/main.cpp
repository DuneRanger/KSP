#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int main() {
    string fileDir = "./inOut/05";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int inpLen;
    inputFile >> inpLen;
    cout << inpLen << endl;

    int answer = 0;

    vector<int> nums;

    for (int i = 0; i < inpLen; i++) {
        int temp;
        inputFile >> temp;
        nums.push_back(temp);
    }

    int oldanswer = answer;

    while (oldanswer != answer) {
        oldanswer = answer;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] <= answer) {
                answer++;
                nums.erase(nums.begin()+i);
            }
        }
    }

    cout << answer;

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}