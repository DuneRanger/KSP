#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

struct lid {
    std::vector<std::pair<int, int>> differences; //value and index
    int originalInd;
    int newInd;
};

struct box {
    int amount;
    bool hasLid;
    lid lidRef;
    std::vector<lid> possLids;
    // std::vector<int> lidSums;
};

std::vector<box> boxes;
std::vector<lid> lids;

void assignLidToBox(int ind) {
    // //This can never happen, right?
    // if (lids[ind].differences.size() == 1) { std::cout << "WTF"; return; }
    // if (boxes[lids[ind].differences[0].second].lidRef.differences.size() == 1) { std::cout << "ALSOWHAT"; return; }
    std::cout << "lid " << lids[ind].originalInd << std::endl;
    //Has to finish before reaching the condition
    for (int i = 0; i < lids[ind].differences.size(); i++) {
        if (i == lids[ind].differences.size()-1) {
            boxes[lids[ind].differences[i].second].hasLid = true;
            boxes[lids[ind].differences[i].second].lidRef = lids[ind];
            boxes[lids[ind].originalInd].hasLid = false;
            // boxes[lids[ind].originalInd].lidRef = null;
            lids[ind].newInd = lids[ind].differences[i].second;
            return;
        }

        lid otherLid = boxes[lids[ind].differences[i].second].lidRef;
        int indOther = -1;

        //Again, shouldn't ever hit .size()
        for (int j = 0; j < otherLid.differences.size(); j++) {
            if (otherLid.differences[j].second == lids[ind].differences[i].second) {
                indOther = j;
                break;
            }
        }
        std::cout << (boxes[lids[ind].differences[i].second].amount - boxes[lids[ind].differences[i+1].second].amount) << " ";
        std::cout << (boxes[otherLid.differences[indOther].second].amount - boxes[otherLid.differences[indOther+1].second].amount) << std::endl;
        
        std::cout << (boxes[lids[ind].differences[i].second].amount - boxes[lids[ind].differences[i+1].second].amount
        > boxes[otherLid.differences[indOther].second].amount - boxes[otherLid.differences[indOther+1].second].amount) << std::endl;

        //Add condition, so that indOther == 0
        if (boxes[lids[ind].differences[i].second].amount - boxes[lids[ind].differences[i+1].second].amount
        > boxes[otherLid.differences[indOther].second].amount - boxes[otherLid.differences[indOther+1].second].amount) {
            int otherLidInd = -1;
            for (int j = 0; j < lids.size(); j++) {
                if (otherLid.originalInd == lids[i].originalInd) {
                    otherLidInd = j;
                }
            }

            boxes[otherLid.differences[indOther].second].lidRef = lids[ind];

            assignLidToBox(otherLidInd);
            return;
        }
    }

}


int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int boxNum, ropeLen;
    in >> boxNum >> ropeLen;


    for (int i = 0; i < boxNum; i++) {
        box temp;
        in >> temp.amount >> temp.hasLid;
        if (temp.hasLid) {
            lid temp2;
            temp2.originalInd = i;
            lids.push_back(temp2);
            temp.lidRef = temp2;
        }
        boxes.push_back(temp);
    }

    for (int i = 0; i < lids.size(); i++) {
        for (int j = std::max(lids[i].originalInd-ropeLen, 0); j < std::min(lids[i].originalInd+ropeLen+1, boxNum); j++) {
            // boxes[j].possLids.push_back(lids[i]);
            lids[i].differences.push_back(std::make_pair(boxes[j].amount - boxes[lids[i].originalInd].amount, j));
        }
    }

    for (int i = 0; i < lids.size(); i++) {
        std::sort(lids[i].differences.begin(), lids[i].differences.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) {
            return p1.first > p2.first;
        });
    }

    for (int i = 0; i < boxNum; i++) {
        if (boxes[i].hasLid) {
            int ind;
            for (int j = 0; j < lids.size(); j++) {
                if (lids[j].originalInd == i) {
                    ind = j;
                    break;
                }
            }
            boxes[i].lidRef = lids[ind];
        }
    }

    for (int i = 0; i < lids.size(); i++) {
        if (boxes[lids[i].differences[0].second].hasLid && boxes[lids[i].differences[0].second].lidRef.originalInd != lids[i].originalInd) {
            assignLidToBox(i);
        }
        else {
            boxes[lids[i].originalInd].hasLid = false;
            boxes[lids[i].differences[0].second].hasLid = true;
            boxes[lids[i].differences[0].second].lidRef = lids[i];
            // boxes[lids[i].originalInd].lidRef = null;
            lids[i].newInd = lids[i].differences[0].second;
        }
    }

    int sum = 0;
    for (int i = 0; i < lids.size(); i++) {
        sum += boxes[lids[i].newInd].amount;
    }

    out << sum << endl;

    for (int i = 0; i < lids.size(); i++) {
        out << lids[i].originalInd << " " << lids[i].newInd << endl;
    }    

    // out << answer;
}