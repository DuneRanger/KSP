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

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

struct path {
    int start;
    int end;
    std::vector<int> blocked;
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    int inpLen;
    in >> inpLen;

    vector<path> paths;
    
    for (int i = 0; i < inpLen; i++) {
        path temp;
        temp.start = i;
        paths.push_back(temp);
    }

    for (int i = 0; i < inpLen; i++) {
        int a;
        in >> a;
        paths[i].end = a;
    }
    for (int i = 0; i < inpLen; i++) {
        for (int j = i+1; j < inpLen; j++) {
            if (paths[i].end > paths[j].end) {
                paths[i].blocked.push_back(j);
                paths[j].blocked.push_back(i);
            }
        }
    }

    std::sort(paths.begin(), paths.end(), [](const path& p1, const path& p2) {return p1.blocked.size() < p2.blocked.size();});

    vector<bool> blockedList;

    for (int i = 0; i < inpLen; i++) {
        blockedList.push_back(false);
    }

    vector<int> answer;

    for (int i = 0; i < inpLen; i++) {
        // cout << paths[i].start+1 << " " << paths[i].blocked.size() << "|||";
        if (blockedList[paths[i].start]) continue;
        answer.push_back(paths[i].start + 1);
        for (int j = 0; j < paths[i].blocked.size(); j++) {
            // cout << paths[i].blocked[j]+1 << " ";
            blockedList[paths[i].blocked[j]] = true;
        }
        // cout << endl;
    }

    out << answer.size() << endl;
    for (int i = 0; i < answer.size(); i++) {
        out << answer[i] << endl;
    }
}