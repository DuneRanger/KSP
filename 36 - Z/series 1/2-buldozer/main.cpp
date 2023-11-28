#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


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

    int highestCount = 0;
    string answer = "";

    std::pair<int, int> dozerCoords;
    std::pair<int, int> boxCoords;
    string instructions;

    in >> dozerCoords.first >> dozerCoords.second;
    in >> boxCoords.first >> boxCoords.second;
    in >> instructions;

    for (int i = 0; i < instructions.size(); i++) {
        switch (instructions[i])
        {
        case 'P':
            dozerCoords.first++;
            if (dozerCoords.first == boxCoords.first && dozerCoords.second == boxCoords.second) boxCoords.first++;
            break;
        case 'L':
            dozerCoords.first--;
            if (dozerCoords.first == boxCoords.first && dozerCoords.second == boxCoords.second) boxCoords.first--;
            break;
        case 'N':
            dozerCoords.second++;
            if (dozerCoords.first == boxCoords.first && dozerCoords.second == boxCoords.second) boxCoords.second++;
            break;
        case 'D':
            dozerCoords.second--;
            if (dozerCoords.first == boxCoords.first && dozerCoords.second == boxCoords.second) boxCoords.second--;
            break;

        default:
            break;
        }
    }

    out << dozerCoords.first << " " << dozerCoords.second << endl << boxCoords.first << " " << boxCoords.second << endl;
}