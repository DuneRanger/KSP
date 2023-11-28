#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/01";
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

    int score = -1, move = 0, start = 0, end = 0;
    int w1Len, w2Len;
    in >> w1Len >> w2Len;

    string word1, word2;
    in >> word1 >> word2;

    vector<int> numbers;


    int curMove = 0;
    for (int i = 0; i < w1Len; i++) {
        if (i >= w2Len) break;
        if (word1[i] == word2[i]) numbers.push_back(1);
        else numbers.push_back(-1);
    }

    int curSum = 0, curStart = 0, curEnd = 0;
    for (int i = 0; i < numbers.size(); i++) {
        if (curSum < 0) {
            curSum = 0;
            curStart = i;
        }
        curSum += numbers[i];
        curEnd = i;
        if (curSum > score) {
            score = curSum;
            start = curStart;
            end = curEnd;
            move = curMove;
        }
    }

    for (int j = w1Len-1; j > -w2Len; j--) {
        vector<int> numbers;
        
        int curMax = -1, curMaxMove = 0, curMaxStart = 0, curMaxEnd = 0;

        int curMove = -j;
        for (int i = std::max(-curMove, 0); i < w1Len; i++) {
            if (i+curMove >= w2Len) break;
            if (word1[i] == word2[i+curMove]) numbers.push_back(1);
            else numbers.push_back(-1);
        }
        int curSum = 0;
        int curStart = std::max(-curMove, 0), curEnd = std::max(-curMove, 0);
        for (int i = 0; i < numbers.size(); i++) {
            if (curSum < 0) {
                curSum = 0;
                curStart = i+std::max(-curMove, 0);
            }
            curSum += numbers[i];
            curEnd = i+std::max(-curMove, 0);
            if (curSum > curMax) {
                curMax = curSum;
                curMaxStart = curStart;
                curMaxEnd = curEnd;
                curMaxMove = curMove;
            }
        }
        if (curMax > score) {
            score = curMax;
            start = curMaxStart;
            end = curMaxEnd;
            move = curMaxMove;
        }
    }



    // out << word1 << endl << word2 << endl;
    out << (score*2) << " " << move << " " << start << " " << end;
}