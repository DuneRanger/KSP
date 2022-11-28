#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

int main() {
    using std::cout;
    using std::endl;
    using std::min;
    using std::max;

    std::string fileDir = "./inOut/03";
    std::ifstream inputFile;
    std::ofstream outputFile;

    inputFile.open(fileDir + ".in", std::ios::in);

    uint64_t answer = 0;
    uint64_t pNum, orgNum, visNum, orgVisNum;
    inputFile >> pNum >> orgNum >> visNum >> orgVisNum;

    std::vector<uint64_t> orgs;

    for (int i = 0; i < orgNum; i++) {
        uint64_t temp;
        inputFile >> temp;
        orgs.push_back(temp);
        if (temp%pNum == 0) orgs.emplace(orgs.begin(), 0);
    }

    std::sort(orgs.begin(), orgs.end());

    //Doubles the array so that I don't have to deal with weird if conditions for when the upper bound goes back to 1
    for (int i = 0; i < orgNum; i++) {
        orgs.push_back(orgs[i]+pNum);
    }

    uint64_t lowerBound = 0;
    uint64_t upperBound = visNum-1;
    int lowerBoundInd = 0;
    int upperBoundInd;
    for (int i = 0; i < orgNum; i++) {
        if (orgs[i] <= upperBound) upperBoundInd = i+1;
        else break;
    }

    int it = 0;
    int orgCount = upperBoundInd-lowerBoundInd;

    // for (int i = 0; i < orgNum*2; i++) {
    //     cout << orgs[i] << " ";
    // }
    // cout << endl;
    while (lowerBound < pNum) {
        it++;

        uint64_t positions = min(orgs[upperBoundInd]-upperBound-1, orgs[lowerBoundInd]-lowerBound)+1;
        positions = min(positions, pNum-lowerBound);

        // cout << lowerBound << " " << orgs[lowerBoundInd] << " | ";
        // cout << upperBound << " " << orgs[upperBoundInd] << " | ";
        // cout << lowerBoundInd << " " << upperBoundInd << " | ";
        // cout << orgCount << " " << orgVisNum << " | ";
        // cout << positions << " ";
        // cout << endl;

        if (orgCount == orgVisNum) answer += positions;

        
        lowerBound += positions;
        upperBound += positions;

        if (orgs[upperBoundInd] <= upperBound) {
            upperBoundInd++;
            orgCount++;
        }
        if (lowerBound > orgs[lowerBoundInd]) {
            lowerBoundInd++;
            orgCount = max(orgCount-1, 0);
        }
    }

    cout << endl << answer << " " << it;

    outputFile.open(fileDir + ".out", std::ios::out);
    outputFile << answer;
    outputFile.close();
}