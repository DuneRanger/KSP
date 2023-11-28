#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/03";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

struct lid {
    int num;
    std::vector<std::pair<int, int>> possBoxes; //amount and index in boxes[]
    int originalInd;
    int newInd;
};

struct box {
    int num;
    int amount;
    bool hasLid;
    lid* lidRef;
    std::vector<std::pair<lid*, int>> possLids; //lid and index in lids[]
};

std::vector<box> boxes;
std::vector<lid> lids;


int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    int boxNum, ropeLen;
    in >> boxNum >> ropeLen;


    for (int i = 0; i < boxNum; i++) {
        box temp;
        in >> temp.amount >> temp.hasLid;
        temp.num = i;
        if (temp.hasLid) {
            lid temp2;
            temp2.originalInd = i;
            temp2.newInd = i;
            lids.push_back(temp2);
            temp.lidRef = &lids[lids.size()-1];
        }
        boxes.push_back(temp);
    }

    for (int i = 0; i < lids.size(); i++) {
        for (int j = std::max(lids[i].originalInd-ropeLen, 0); j < std::min(lids[i].originalInd+ropeLen+1, boxNum); j++) {
            lids[i].possBoxes.push_back(std::make_pair(boxes[j].amount, j));
        }
        lids[i].num = i;
    }

    for (int i = 0; i < lids.size(); i++) {
        for (int j = std::max(lids[i].originalInd-ropeLen, 0); j < std::min(lids[i].originalInd+ropeLen+1, boxNum); j++) {
            boxes[j].possLids.push_back(std::make_pair(&lids[i], i));
        }
    }


    for (int i = 0; i < lids.size(); i++) {
        std::sort(lids[i].possBoxes.begin(), lids[i].possBoxes.end(), [&](std::pair<int, int> p1, std::pair<int, int> p2) {
            return p1.first > p2.first;
        });
    }

    for (int i = 0; i < boxNum; i++) {
        if (boxes[i].hasLid) {
            int ind;
            for (int j = 0; j < boxes[i].possLids.size(); j++) {
                if ((*boxes[i].possLids[j].first).originalInd == i) {
                    ind = boxes[i].possLids[j].second;
                    break;
                }
            }
            boxes[i].lidRef = &lids[ind];
        }
    }

    // for (int i = 0; i < boxNum; i++) {
    //     out << boxes[i].amount << " " << boxes[i].hasLid << endl;
    //     if (boxes[i].hasLid) {
    //         out << (*boxes[i].lidRef).originalInd << endl;
    //     }
    //     for (int j = 0; j < boxes[i].possLids.size(); j++) {
    //         out << (*boxes[i].possLids[j].first).originalInd << " ";
    //     }
    //     out << endl << endl;
    // }


    std::deque<int> lidQueue;

    for (int i = 0; i < lids.size(); i++) {
        lidQueue.push_back(i);
    }
    // for (int i = 0; i < boxNum; i++) {
    //     out << boxes[i].amount << " " << boxes[i].hasLid << " " << (boxes[i].hasLid ? (*boxes[i].lidRef).originalInd : -1) << endl;
    // }
    // out << endl;


    while (!lidQueue.empty()) {
        if (lidQueue.size()) cout << lidQueue.size() << endl;
        // for (int i = 0; i < lidQueue.size(); i++) {
        //     out << lids[lidQueue[i]].originalInd << " ";
        // }
        // out << endl << lids[lidQueue.front()].originalInd << ":" << endl;

        lid* curLid = &lids[lidQueue.front()];
        lidQueue.pop_front();
        box* tBox = &boxes[(*curLid).possBoxes[0].second];

        // out << curLid->originalInd << " " << tBox->amount << " " << tBox->possLids.size() << " " << "" << endl;
    

    //     // if (curLid->newInd)

        for (int i = 0; i < (*tBox).possLids.size(); i++) {
            int tempInd = -1;
            // finds the current target box's index in the array of possible boxes of the current possible lid
            for (int j = 0; j < lids[(*tBox).possLids[i].second].possBoxes.size(); j++) {
                if (lids[(*tBox).possLids[i].second].possBoxes[j].second == (*tBox).num) {
                    tempInd = j;
                    break;
                }
            }
            // cout << i << " " << tempInd << " " << (*tBox).possLids.size() << endl;
            // out << curLid->originalInd << (*tBox).possLids[i].first->originalInd << (*tBox).possLids.size() << endl;
            
            if (lids[(*tBox).possLids[i].second].originalInd == curLid->originalInd) {/*out << "this is the lid" << curLid->originalInd << endl;*/ continue;}
            if (tempInd == lids[(*tBox).possLids[i].second].possBoxes.size()-1) {/*out << "not here" <<  lids[(*tBox).possLids[i].second].originalInd << endl;*/ continue;}


    //         out << (*tBox).amount << " " << lids[(*tBox).possLids[i].second].possBoxes[tempInd+1].first << " "
    //         << " " << (*curLid).possBoxes[1].first << endl;

            if ((*curLid).possBoxes.size() == 1 || lids[(*tBox).possLids[i].second].possBoxes[tempInd+1].first >= (*curLid).possBoxes[1].first) {
                    // for (int j = 0; j < lids[(*tBox).possLids[i].second].possBoxes.size(); j++) {
                    //     out << lids[(*tBox).possLids[i].second].possBoxes[j].second << " ";
                    // }
                    // out << endl;
                    lids[(*tBox).possLids[i].second].possBoxes.erase(lids[(*tBox).possLids[i].second].possBoxes.begin()+tempInd);
                    
                    // for (int j = 0; j < lids[(*tBox).possLids[i].second].possBoxes.size(); j++) {
                    //     out << lids[(*tBox).possLids[i].second].possBoxes[j].second << " ";
                    // }
                    (*tBox).possLids.erase((*tBox).possLids.begin()+i);
                    i--;
                    // out << endl;
                    // out << endl;
            }
        }
        if ((*tBox).hasLid) {
            (*(*tBox).lidRef).newInd = -1;

            if ((*(*tBox).lidRef).originalInd != (*curLid).originalInd) {
                int oldLidInd = (*(*tBox).lidRef).num;
                if (lidQueue.front() != oldLidInd) lidQueue.push_front(oldLidInd);
            }
        }
        if ((*curLid).newInd != -1) boxes[(*curLid).newInd].hasLid = false;
        (*tBox).hasLid = true;
        (*tBox).lidRef = curLid;
        (*curLid).newInd = (*tBox).num;
        // for (int i = std::max((*curLid).originalInd-ropeLen-5, 0); i < std::min((*curLid).originalInd+ropeLen+6, boxNum); i++) {
        //     out << boxes[i].amount << " " << boxes[i].hasLid << " " << (boxes[i].hasLid ? (*boxes[i].lidRef).originalInd : -1) << endl;
        // }
        // out << endl;
    }

    int sum = 0;
    for (int i = 0; i < lids.size(); i++) {
        sum += boxes[lids[i].newInd].amount;
    }

    out << sum << endl;

    for (int i = 0; i < lids.size(); i++) {
        // cout << lids[i].originalInd << " " << lids[i].newInd << endl;
        out << (lids[i].originalInd+1) << " " << (lids[i].newInd+1) << endl;
    }
}