#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

pair<int, int> cityACoords;
pair<int, int> cityBCoords;
int inpLen;
int lineLen;
int mntCost;

vector<vector<int>> memo;
vector<vector<int>> trailMap;
int maxDist;

int counter = 0;

void pathCalculator(pair<int, int> coords, int cost = 0) {
    if ((memo[coords.first][coords.second] == 0) || cost < memo[coords.first][coords.second]) {/*cout << "value written" << endl;*/ memo[coords.first][coords.second] = cost;}
    else return; //{cout << "path ended" << endl; return;}

    if ((coords.first == cityBCoords.first && coords.second == cityBCoords.second) || cost > maxDist) return; //{cout << "finish" << endl; return;}

    if (coords.first > 0) pathCalculator(make_pair(coords.first-1, coords.second), cost+trailMap[coords.first][coords.second]);
    if (coords.first < inpLen-1) pathCalculator(make_pair(coords.first+1, coords.second), cost+trailMap[coords.first][coords.second]);
    if (coords.second > 0) pathCalculator(make_pair(coords.first, coords.second-1), cost+trailMap[coords.first][coords.second]);
    if (coords.second < lineLen-1) pathCalculator(make_pair(coords.first, coords.second+1), cost+trailMap[coords.first][coords.second]);

    counter++;
    if (counter%10000000 == 0) cout << counter << endl;

    return;
}


int main() {
    string fileDir = "./inOut/06";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    uint64_t answer = 0;
    
    inputFile >> inpLen >> lineLen >> mntCost;


    for (int i = 0; i < inpLen; i++) {
        vector<int> temp;
        for (int j = 0; j < lineLen; j++) {
            temp.push_back(0);
        }
        memo.push_back(temp);
    }

    for (int i = 0; i < inpLen; i++) {
        vector<int> temp;
        string inp;
        inputFile >> inp;
        for (int j = 0; j < lineLen; j++) {
            if (inp[j] == '.') {
                temp.push_back(1);
            } else if (inp[j] == 'A') {
                temp.push_back(mntCost);
            } else if (inp[j] == 'X') {
                temp.push_back(0);
                cityACoords = make_pair(i, j);
            } else if (inp[j] == 'Y') {
                temp.push_back(0);
                cityBCoords = make_pair(i, j);
            }
        }
        trailMap.push_back(temp);
    }

    maxDist = abs(cityACoords.first-cityBCoords.first)*mntCost + abs(cityACoords.second-cityBCoords.second)*mntCost;

    pathCalculator(cityACoords);

    cout << "sdfsdfsdfsdf";

    answer = memo[cityBCoords.first][cityBCoords.second];


    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();
}