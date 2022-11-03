#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

struct block {
    int start;
    int end; // Not inclusive (similar to array lengths/sizes)
    int length;
    int startHeight;
};

int main() {
    string fileDir = "./inOut/01";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t possibilities = 0;
    int inpLen;
    string inp;
    inputFile >> inpLen;
    cout << inpLen << endl;
    inputFile >> inp;

    vector<block> blocks;
    
    int currentHeight = 0;
    bool blockNow = false;

    for (int i = 0; i < inpLen; i++) {
        if (inp[i] == "^"[0]) {
            if (blockNow) {
                blockNow = false;
                blocks[blocks.size()-1].end = i;
                blocks[blocks.size()-1].length = blocks[blocks.size()-1].end - blocks[blocks.size()-1].start;
            }
            currentHeight++;
        }
        else if (inp[i] == "v"[0]) {
            if (blockNow) {
                blockNow = false;
                blocks[blocks.size()-1].end = i;
                blocks[blocks.size()-1].length = blocks[blocks.size()-1].end - blocks[blocks.size()-1].start;
            }
            currentHeight--;
        }
        else if (!blockNow){
            blockNow = true;
            block temp;
            temp.start = i;
            temp.startHeight = currentHeight;
            blocks.push_back(temp);
        }
        if (blockNow && i == inpLen-1) {
            blockNow = false;
            blocks[blocks.size()-1].end = i+1;
            blocks[blocks.size()-1].length = blocks[blocks.size()-1].end - blocks[blocks.size()-1].start;
        }
    }  

    cout << inp << endl;
    
    for (int i = 0; i < blocks.size(); i++) {
        cout << "block " << i << ": ";
        cout << blocks[i].start << " " << blocks[i].end << " " << blocks[i].length << " " << blocks[i].startHeight << endl;
    }

    vector<int> allMarkPoss;

    for (int i = 0; i < blocks.size(); i++) {
        int offset = abs(blocks[i+1].startHeight - blocks[i].startHeight);
    }



    outputFile.open(fileDir + ".out", ios::out);
    outputFile << possibilities;
    outputFile.close();
}