#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

vector<uint64_t> orgIndexes;

int64_t BinaryArraySearch(int64_t left, int64_t right, uint64_t lowerBound, uint64_t upperBound, bool special) {
    int64_t found = -1;
    bool temp = false;
    int64_t middle = (left+right)/2;
    if (special) {
        if (orgIndexes[right] >= lowerBound) {
            while (orgIndexes[right] >= lowerBound) {
                right--;
                right--;
            }
            return right+1;
        } else {
            if (orgIndexes[left] <= upperBound) {
                return left;
            }
        }
        return -1;
    } else {
        while (left <= right) {
            // cout << orgIndexes[middle] << " " << left << " " << right << " " << middle << " " << lowerBound << endl;
            if (orgIndexes[middle] >= lowerBound && orgIndexes[middle] <= upperBound) {
                found = middle;
                right = middle-1;
            } else if (orgIndexes[middle] > lowerBound) {
                right = middle > 0 ? middle-1 : 0;
            } else {
                left = middle+1;
            }
            middle = (left+right)/2;
        }
    }
    return found;
}

//01 - 9
//02 - 
//03 - 411

int main() {
    string fileDir = "./inOut/03";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t answer = 0;
    uint64_t pNum, orgNum, visNum, orgVisNum;
    inputFile >> pNum >> orgNum >> visNum >> orgVisNum;

    for (int i = 0; i < orgNum; i++) {
        uint64_t temp;
        inputFile >> temp;
        orgIndexes.push_back(temp);
    }

    sort(orgIndexes.begin(), orgIndexes.end());

    // for (int i = 0; i < 50; i++) {
    //     cout << orgIndexes[i] << " ";
    // }
    // cout << endl;

    uint64_t lrOffset = (visNum-1)/2;
    uint64_t midOffset = pNum/2;
    for (uint64_t i = midOffset+lrOffset; i < midOffset+lrOffset+pNum; i++) {
        uint64_t lowerBound = (midOffset - lrOffset + i)%pNum;
        uint64_t upperBound = (midOffset + lrOffset + i)%pNum;
        // cout << lowerBound << " " << i << " " << upperBound << " ";
        int64_t temp = -1;

        if (i+lrOffset >= pNum+midOffset) {
            temp = BinaryArraySearch(0, orgNum-1, lowerBound, upperBound, true);
            if (temp == -1) continue;
            int64_t temp2 = orgNum-temp;
            for (int i = 0; orgIndexes[i] <= upperBound; i++) {
                temp2++;
            }
            if (temp2 == orgVisNum) answer++;
            // cout << temp2;
        } else {
            temp = BinaryArraySearch(0, orgNum-1, lowerBound, upperBound, false);
            if (temp == -1) continue;
            int64_t temp2 = temp;
            while (orgIndexes[temp2] <= upperBound) {
                temp2++;
            }
            if (temp2-temp == orgVisNum) answer++;
            // cout << temp2-temp;
        }
        // cout << endl;
    }

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}