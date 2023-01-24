#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

// #define in inputFile
// #define out outputFile
#define in std::cin
#define out std::cout

struct node {
    int num;
    int parent;
    std::vector<int> children;
    std::vector<int> leadsTo; // specific rooms underneath the node
    char state;
    bool isRoom;
    char req; // only for rooms
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t actions = 0;
    int nodeNum, roomNum;
    in >> nodeNum >> roomNum;

    vector<node> tree;
    vector<int> roomIds;

    for (int i = 0; i < nodeNum; i++) {
        node empty;
        tree.push_back(empty);
    }

    tree[0].state = 'O';
    tree[0].isRoom = false;
    tree[0].parent = -1;
    tree[0].num = 0;

    for (int i = 0; i < nodeNum-1; i++) {
        int parentId;
        int id;
        char state;
        in >> parentId >> id >> state;
        id--;
        parentId--;
        tree[id].num = id;
        tree[id].parent = parentId;
        tree[parentId].children.push_back(id);
        tree[id].state = state;
        tree[id].isRoom = false;
    }



    for (int i = 0; i < roomNum; i++) {
        int id;
        char req;
        in >> id >> req;
        id--;
        tree[id].isRoom = true;
        tree[id].req = req;

        roomIds.push_back(id);

        node curNode = tree[id];
        while (curNode.parent != -1) {
            tree[curNode.parent].leadsTo.push_back(id);
            curNode = tree[curNode.parent];
        }
    }

    //Opens up all paths to P rooms
    for (int i = 0; i < roomIds.size(); i++) {
        if (tree[roomIds[i]].req == 'P') {
            node curNode = tree[roomIds[i]];
            while (curNode.parent != -1) {
                if (curNode.state == 'Z') {
                    tree[curNode.num].state = 'O';
                    actions++;
                }
                curNode = tree[curNode.parent];
            }
        }        
    }

    //Changes all M rooms that are already closed to E
    for (int i = 0; i < roomIds.size(); i++) {
        if (tree[roomIds[i]].req == 'M') {
            node curNode = tree[roomIds[i]];
            while (curNode.parent != -1) {
                if (curNode.state == 'Z') {
                    tree[roomIds[i]].req = 'E';
                    break;
                }
                curNode = tree[curNode.parent];
            }
        }
    }

    //Closes off all remaining M rooms
    for (int i = 0; i < roomIds.size(); i++) {
        if (tree[roomIds[i]].req == 'M') {
            node curNode = tree[roomIds[i]];
            while (curNode.parent != -1) {
                bool stop = false;
                for (int j = 0; j < tree[curNode.parent].leadsTo.size(); j++) {
                    if (tree[tree[curNode.parent].leadsTo[j]].req == 'P') {
                        stop = true;
                        break;
                    }
                }
                if (stop) {
                    if (curNode.state == 'O') {
                        //Should always be true
                        curNode.state = 'Z';
                        actions++;
                        for (int j = 0; j < curNode.leadsTo.size(); j++) {
                            if (tree[curNode.leadsTo[j]].req == 'M') {
                                tree[curNode.leadsTo[j]].req = 'E';
                            }
                        }
                    }
                    break;
                } else {
                    curNode = tree[curNode.parent];
                }
            }
        }
    }

    out << actions;
}