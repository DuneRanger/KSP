#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

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

    vector<int> lettersNum;

    for (int i = 0; i < 26; i++) {
        int temp;
        in >> temp;
        lettersNum.push_back(temp);
    }

    int lineCount;
    in >> lineCount;
    string wholeString = "";
    string nothing;
    std::getline(in, nothing);

    vector <int> lettersCount;

    for (int i = 0; i < 26; i++) {
        lettersCount.push_back(0);
    }

    for (int i = 0; i < lineCount; i++) {
        string temp;
        std::getline(in, temp);
        wholeString += temp + "\n";
        // cout << "here" << temp.size() << temp << endl;
        for (int j = 0; j < temp.size(); j++) {
            if ((int)temp[j] > 96 && (int)temp[j] < 123) {
                lettersCount[(int)temp[j]-97]++;
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            if (lettersCount[i] == lettersNum[j]) {
                lettersCount[i] = j;
                // cout << (char)(i+97) << " " << (char)(j+97) << endl;
                break;
            }
        }
    }

    for (int i = 0; i < wholeString.size(); i++) {
        if ((int)wholeString[i] > 96 && (int)wholeString[i] < 123) {
            wholeString[i] = (char)(lettersCount[(int)wholeString[i]-97]+97);
        }
    }
    // cout << (int)'a' << " " << (int)'z';

    out << wholeString;
}