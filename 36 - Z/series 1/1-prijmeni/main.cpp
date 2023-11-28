#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


std::string fileDir = "./inOut/01";
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

    int inpLen;
    in >> inpLen;

    std::map<string, int> names;

    for (int i = 0; i < inpLen; i++) {
        string curName;
        in >> curName;
        if (names.find(curName) != names.end()) {
            names[curName] += 1;
        }
        else {
            names.insert(make_pair(curName, 1));
        }
        if (names[curName] > highestCount) {
            highestCount = names[curName];
            answer = curName;
        }
    }

    answer += " " + std::to_string(highestCount);
    out << answer;
}