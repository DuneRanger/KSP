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
// #define in std::cin
// #define out std::cout

bool comparePair(std::pair<int, int> p1, std::pair<int, int> p2) {
    return (abs(p1.first) < abs(p2.first));
}


struct intervalTreeNode {
    int gVal;
    int bVal;
    intervalTreeNode* leftChild;
    intervalTreeNode* rightChild;
};

int inpLen;
intervalTreeNode endOfTreeNode;
int maxDepth = 0;

struct intervalTreeNode* newIntervalTreeNode(int g, int b) {
    intervalTreeNode* n = new intervalTreeNode;
    n->gVal = g;
    n->bVal = b;
    n->leftChild = &endOfTreeNode;
    n->rightChild = &endOfTreeNode;
    return n;
}

std::vector<intervalTreeNode> nodes;

bool searchIntervalTree(int g, int b, intervalTreeNode* curNode) {
    int minB = -1;
    int maxB = inpLen;

    while(true) {
        if (g > curNode->gVal) {
            minB = (curNode->bVal);
            if (curNode->rightChild->gVal != -1) {
                curNode = curNode->rightChild;
            }
            else {
                return (b > minB && b < maxB);
            }
        }
        else if (g < curNode->gVal) {
            maxB = (curNode->bVal);
            if (curNode->leftChild->gVal != -1) {
                curNode = curNode->leftChild;
            }
            else {
                return (b > minB && b < maxB);
            }
        }
    }
}

void addToIntervalTree(int g, int b, intervalTreeNode* curNode) {
    int depth = 0;

    while(true) {
        depth++;
        if (depth > maxDepth) {
            maxDepth = depth;
            std::cout << depth << std::endl;
        }
        if (g > curNode->gVal) {
            if (curNode->rightChild->gVal != -1) {
                curNode = curNode->rightChild;
            }
            else {
                intervalTreeNode* newNode = newIntervalTreeNode(g, b);

                nodes.push_back(*newNode);

                curNode->rightChild = newNode;
                return;
            }
        }
        else if (g < curNode->gVal) {
            if (curNode->leftChild->gVal != -1) {
                curNode = curNode->leftChild;
            }
            else {
                intervalTreeNode* newNode = newIntervalTreeNode(g, b);

                nodes.push_back(*newNode);

                curNode->leftChild = newNode;
                return;
            }
        }
    }
}

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    in >> inpLen;

    vector<int> gToB;
    vector<int> bToG;
    vector<std::pair<int, int>> diffs;

    for (int i = 0; i < inpLen; i++) {
        gToB.push_back(0);
        bToG.push_back(0);
        diffs.push_back(std::make_pair(0, 0));
    }


    for (int i = 0; i < inpLen; i++) {
        int a;
        in >> a;
        gToB[i] = a-1;
        bToG[a] = i;
        diffs[i] = std::make_pair(a-i-1, i);
    }


    std::sort(diffs.begin(), diffs.end(), comparePair);

    endOfTreeNode.gVal = -1;
    endOfTreeNode.bVal = -1;

    vector<int> answer;

    intervalTreeNode* root = newIntervalTreeNode(diffs[0].second, gToB[diffs[0].second]);
    // cout << diffs[0].second+1 << " " << gToB[diffs[0].second]+1 << endl;
    answer.push_back(diffs[0].second);

    nodes.push_back(*root);

    for (int i = 1; i < inpLen; i++) {
        // cout << diffs[i].second+1 << " " << gToB[diffs[i].second]+1 << " ";
        bool test = searchIntervalTree(diffs[i].second, gToB[diffs[i].second], root);
        // cout << (test ? "true" : "false") << endl;

        if (test) {
            answer.push_back(diffs[i].second);
            addToIntervalTree(diffs[i].second, gToB[diffs[i].second], root);
        }
        // if (nodes.size()%1000 == 0) cout << nodes.size() << endl;
    }

    out << answer.size() << endl;
    for (int i = 0; i < answer.size(); i++) {
        out << (answer[i]+1) << endl;
    }
}