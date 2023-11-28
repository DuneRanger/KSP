#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/05";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
#define in std::cin
#define out std::cout

struct path {
    int start = -1;
    path* next;
    int pathCount = 0;
};

struct path newPath(int g, path* child) {
    path temp;
    temp.start = g;
    temp.pathCount = child->pathCount+1;
    temp.next = child;
    return temp;
};

int inpLen;
std::vector<int> gToB;
std::vector<int> bToG;
std::vector<path> memo2;
uint64_t totalRecurionCount = 0;

std::chrono::time_point<std::chrono::system_clock> st, en;

path DynamicRecursionBecauseIHateWhileLoops(int g, int b) {
    // totalRecurionCount++;
    // if (totalRecurionCount%1000000000 == 0) {
    //     en = std::chrono::system_clock::now();
    //     std::chrono::duration<double> elapsed_seconds = en - st;
    //     std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;
    //     std::cout << "total function calls: " << totalRecurionCount/1000000000 << " billion" << std::endl;
    // }
    if (memo2[g].start != -1) return memo2[g];

    path curBest;
    int indCurBest = inpLen;
    // int lastSavedSize = 0;
    if (g >= b) {
        for (int i = g+1; i < inpLen; i++) {
            if (gToB[i] > b) {
                path temp = DynamicRecursionBecauseIHateWhileLoops(i, gToB[i]);
                // if (temp.pathCount < (lastSavedSize-150000)) break;
                if (temp.pathCount > curBest.pathCount) {
                    curBest = temp;
                    indCurBest = i;
                    // lastSavedSize = temp.pathCount;
                }
            }
        }
    } else {
        for (int i = b+1; i < inpLen; i++) {
            if (bToG[i] > g) {
                path temp = DynamicRecursionBecauseIHateWhileLoops(bToG[i], i);
                if (temp.pathCount > curBest.pathCount) {
                    curBest = temp;
                    indCurBest = bToG[i];
                }
            }
        }
    }
    path thisBest = newPath(g, &memo2[indCurBest]);

    memo2[g] = thisBest;

    // if (memo.size()%1000 == 0) std::cout << memo.size() << " " << g << " " << b << std::endl;

    return memo2[g];
}

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    st = std::chrono::system_clock::now();

    in >> inpLen;

    for (int i = 0; i < inpLen; i++) {
        gToB.push_back(0);
        bToG.push_back(0);
        path temp;
        memo2.push_back(temp);
    }
    path temp;
    memo2.push_back(temp);

    for (int i = 0; i < inpLen; i++) {
        int a;
        in >> a;
        gToB[i] = a-1;
        bToG[a-1] = i;
    }

    path answer;
    for (int i = inpLen-1; i > -1; i--) {
        path temp = DynamicRecursionBecauseIHateWhileLoops(i, gToB[i]);
        if (temp.pathCount > answer.pathCount) {
            answer = temp;
        }
        // if (i%50000 == 0) cout << i << " left" << endl;
    }

    // cout << answer.start << " " << answer.next->start << " " << answer.next->next->start << endl;

    out << answer.pathCount << endl;
    path curPath = answer;

    // cout << curPath.start << " " << curPath.next->start << " " << curPath.next->next->start << endl;

    for (int i = 0; i < answer.pathCount; i++) {
        out << curPath.start+1 << endl;
        curPath = *curPath.next;
    }
    // cout << totalRecurionCount << endl;

    // en = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = en - st;
    // cout << "elapsed time: " << elapsed_seconds.count() << endl;
}