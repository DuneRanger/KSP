#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <chrono>

std::string fileDir = "./inOut/03";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

struct pathInstance {
    bool descending = false;
    std::pair<int, int> position;
    int pathCost;
};

struct path {
    int cost;
    std::vector<std::pair<int, int>> steps;
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int N, M;
    in >> N >> M;
    std::pair<int, int> start, end;
    in >> start.second >> start.first >> end.second >> end.first;

    // x and y are reversed in this problem!!!!!
    // make sure to undo that when printing the answer
    std::chrono::time_point<std::chrono::system_clock> st, en;
    st = std::chrono::system_clock::now();
    // cout << N*M << endl;
    vector<vector<int>> map;
    vector<vector<path>> pathCost;

    for (int i = 0; i < N; i++) {
        vector<int> temp;
        vector<path> temp2;
        for (int j = 0; j < M; j++) {
            int a;
            in >> a;
            temp.push_back(a);
            path p;
            p.cost = 1;
            temp2.push_back(p);
        }
        map.push_back(temp);
        pathCost.push_back(temp2);
    }

    int endHeight = map[end.first][end.second];

    auto compare = [](const pathInstance path1, const pathInstance path2)  
        { return path1.pathCost < path2.pathCost; };

    std::priority_queue<pathInstance, vector<pathInstance>, decltype(compare)> Q(compare);

    pathInstance initPath;
    initPath.position = start;

    Q.push(initPath);

    while (Q.size()) {
        pathInstance curPath = Q.top();
        std::pair<int, int> curPos = curPath.position;
        // cout << curPos.first << " " << curPos.second << endl;
        // cout << Q.top().pathCost << " ";
        Q.pop();
        // cout << Q.top().pathCost << endl;

        if (curPos.first == end.first && curPos.second == end.second) continue;

        if (curPos.first != 0) {
            if (map[curPos.first][curPos.second] != map[curPos.first-1][curPos.second]) {
                if (!curPath.descending) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first-1][curPos.second].cost) {
                        pathCost[curPos.first-1][curPos.second].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first-1][curPos.second].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first-1][curPos.second].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first-1, curPos.second);
                        newPath.descending = map[curPos.first][curPos.second] > map[curPos.first-1][curPos.second];
                        newPath.pathCost = pathCost[curPos.first-1][curPos.second].cost;
                        Q.push(newPath);
                    }
                }
                else if (map[curPos.first][curPos.second] > map[curPos.first-1][curPos.second] && map[curPos.first][curPos.second] > endHeight) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first-1][curPos.second].cost) {
                        pathCost[curPos.first-1][curPos.second].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first-1][curPos.second].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first-1][curPos.second].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first-1, curPos.second);
                        newPath.descending = true;
                        newPath.pathCost = pathCost[curPos.first-1][curPos.second].cost;
                        Q.push(newPath);
                    }
                }
            }
        }
        if (curPos.second != 0) {
            if (map[curPos.first][curPos.second] != map[curPos.first][curPos.second-1]) {

                if (!curPath.descending) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first][curPos.second-1].cost) {
                        pathCost[curPos.first][curPos.second-1].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first][curPos.second-1].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first][curPos.second-1].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first, curPos.second-1);
                        newPath.descending = map[curPos.first][curPos.second] > map[curPos.first][curPos.second-1];
                        newPath.pathCost = pathCost[curPos.first][curPos.second-1].cost;
                        Q.push(newPath);
                    }
                }
                else if (map[curPos.first][curPos.second] > map[curPos.first][curPos.second-1]) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first][curPos.second-1].cost) {
                        pathCost[curPos.first][curPos.second-1].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first][curPos.second-1].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first][curPos.second-1].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first, curPos.second-1);
                        newPath.descending = true;
                        newPath.pathCost = pathCost[curPos.first][curPos.second-1].cost;
                        Q.push(newPath);
                    }
                }
            }
        }
        if (curPos.first != N-1) {
            if (map[curPos.first][curPos.second] != map[curPos.first+1][curPos.second]) {
                if (!curPath.descending) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first+1][curPos.second].cost) {
                        pathCost[curPos.first+1][curPos.second].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first+1][curPos.second].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first+1][curPos.second].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first+1, curPos.second);
                        newPath.descending = map[curPos.first][curPos.second] > map[curPos.first+1][curPos.second];
                        newPath.pathCost = pathCost[curPos.first+1][curPos.second].cost;
                        Q.push(newPath);
                    }
                }
                else if (map[curPos.first][curPos.second] > map[curPos.first+1][curPos.second]) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first+1][curPos.second].cost) {
                        pathCost[curPos.first+1][curPos.second].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first+1][curPos.second].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first+1][curPos.second].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first+1, curPos.second);
                        newPath.descending = true;
                        newPath.pathCost = pathCost[curPos.first+1][curPos.second].cost;
                        Q.push(newPath);
                    }
                }
            }
        }
        if (curPos.second != M-1) {
            if (map[curPos.first][curPos.second] != map[curPos.first][curPos.second+1]) {
                if (!curPath.descending) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first][curPos.second+1].cost) {
                        pathCost[curPos.first][curPos.second+1].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first][curPos.second+1].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first][curPos.second+1].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first, curPos.second+1);
                        newPath.descending = map[curPos.first][curPos.second] > map[curPos.first][curPos.second+1];
                        newPath.pathCost = pathCost[curPos.first][curPos.second+1].cost;
                        Q.push(newPath);
                    }
                }
                else if (map[curPos.first][curPos.second] > map[curPos.first][curPos.second+1]) {
                    if (pathCost[curPos.first][curPos.second].cost + 1 > pathCost[curPos.first][curPos.second+1].cost) {
                        pathCost[curPos.first][curPos.second+1].cost = pathCost[curPos.first][curPos.second].cost + 1;
                        pathCost[curPos.first][curPos.second+1].steps = pathCost[curPos.first][curPos.second].steps;
                        pathCost[curPos.first][curPos.second+1].steps.push_back(curPos);
                        pathInstance newPath;
                        newPath.position = std::make_pair(curPos.first, curPos.second+1);
                        newPath.descending = true;
                        newPath.pathCost = pathCost[curPos.first][curPos.second+1].cost;
                        Q.push(newPath);
                    }
                }
            }
        }
        // if (Q.size()%100 == 0) cout << Q.size() << endl;
        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < M; j++) {
        //         cout << pathCost[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    en = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = en - st;
    cout << "elapsed time: " << elapsed_seconds.count() << endl;

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //         cout << map[i][j];
    //     }
    //     cout << endl;
    // }

    out << pathCost[end.first][end.second].cost << endl;
    for (int i = 0; i < pathCost[end.first][end.second].steps.size(); i++) {
        out << pathCost[end.first][end.second].steps[i].second << " " << pathCost[end.first][end.second].steps[i].first << endl;
    }
    out << end.second << " " << end.first << endl;
}