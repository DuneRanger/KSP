#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <chrono>

std::string fileDir = "./inOut/01";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
#define in std::cin
#define out std::cout

struct path {
    int cost;
    std::pair<int, int> position;
    std::pair<int, int> before;
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    int N, M;
    in >> N >> M;
    std::pair<int, int> start, end;
    in >> start.second >> start.first >> end.second >> end.first;

    // x and y are reversed in this problem!!!!!
    // make sure to undo that when printing the answer

    // cout << N*M << endl;
    vector<vector<int>> map;
    vector<vector<path>> pathsUp;
    vector<vector<path>> pathsDown;

    for (int i = 0; i < N; i++) {
        vector<int> temp;
        vector<path> temp2;
        for (int j = 0; j < M; j++) {
            int a;
            in >> a;
            temp.push_back(a);
            path p;
            p.cost = 0;
            temp2.push_back(p);
        }
        map.push_back(temp);
        pathsUp.push_back(temp2);
        pathsDown.push_back(temp2);
    }

    std::queue<std::pair<int, int>> Q;
    Q.push(start);

    while (Q.size()) {
        std::pair<int, int> curPos = Q.front();
        Q.pop();

        if (curPos.first != 0) {
            if (map[curPos.first][curPos.second] < map[curPos.first-1][curPos.second]) {
                if (pathsUp[curPos.first][curPos.second].cost + 1 > pathsUp[curPos.first-1][curPos.second].cost) {
                    pathsUp[curPos.first-1][curPos.second].cost = pathsUp[curPos.first][curPos.second].cost + 1;
                    pathsUp[curPos.first-1][curPos.second].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first-1, curPos.second));
                }
            }
        }
        if (curPos.second != 0) {
            if (map[curPos.first][curPos.second] < map[curPos.first][curPos.second-1]) {
                if (pathsUp[curPos.first][curPos.second].cost + 1 > pathsUp[curPos.first][curPos.second-1].cost) {
                    pathsUp[curPos.first][curPos.second-1].cost = pathsUp[curPos.first][curPos.second].cost + 1;
                    pathsUp[curPos.first][curPos.second-1].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first, curPos.second-1));
                }
            }
        }
        if (curPos.first != N-1) {
            if (map[curPos.first][curPos.second] < map[curPos.first+1][curPos.second]) {
                if (pathsUp[curPos.first][curPos.second].cost + 1 > pathsUp[curPos.first+1][curPos.second].cost) {
                    pathsUp[curPos.first+1][curPos.second].cost = pathsUp[curPos.first][curPos.second].cost + 1;
                    pathsUp[curPos.first+1][curPos.second].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first+1, curPos.second));
                }
            }
        }
        if (curPos.second != M-1) {
            if (map[curPos.first][curPos.second] < map[curPos.first][curPos.second+1]) {
                if (pathsUp[curPos.first][curPos.second].cost + 1 > pathsUp[curPos.first][curPos.second+1].cost) {
                    pathsUp[curPos.first][curPos.second+1].cost = pathsUp[curPos.first][curPos.second].cost + 1;
                    pathsUp[curPos.first][curPos.second+1].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first, curPos.second+1));
                }
            }
        }
    }

    // std::queue<std::pair<int, int>> Q;
    Q.push(end);

    while (Q.size()) {
        // cout << pathsDown[0][9].before.second << " " << pathsDown[0][9].before.first << " | ";
        // cout << pathsDown[1][9].before.second << " " << pathsDown[1][9].before.first << " | ";
        // cout << pathsDown[1][8].before.second << " " << pathsDown[1][8].before.first << endl;
        std::pair<int, int> curPos = Q.front();
        Q.pop();

        if (curPos.first != 0) {
            if (map[curPos.first][curPos.second] < map[curPos.first-1][curPos.second]) {
                if (pathsDown[curPos.first][curPos.second].cost + 1 > pathsDown[curPos.first-1][curPos.second].cost) {
                    pathsDown[curPos.first-1][curPos.second].cost = pathsDown[curPos.first][curPos.second].cost + 1;
                    pathsDown[curPos.first-1][curPos.second].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first-1, curPos.second));
                }
            }
        }
        if (curPos.second != 0) {
            if (map[curPos.first][curPos.second] < map[curPos.first][curPos.second-1]) {
                if (pathsDown[curPos.first][curPos.second].cost + 1 > pathsDown[curPos.first][curPos.second-1].cost) {
                    pathsDown[curPos.first][curPos.second-1].cost = pathsDown[curPos.first][curPos.second].cost + 1;
                    pathsDown[curPos.first][curPos.second-1].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first, curPos.second-1));
                }
            }
        }
        if (curPos.first != N-1) {
            if (map[curPos.first][curPos.second] < map[curPos.first+1][curPos.second]) {
                if (pathsDown[curPos.first][curPos.second].cost + 1 > pathsDown[curPos.first+1][curPos.second].cost) {
                    pathsDown[curPos.first+1][curPos.second].cost = pathsDown[curPos.first][curPos.second].cost + 1;
                    pathsDown[curPos.first+1][curPos.second].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first+1, curPos.second));
                }
            }
        }
        if (curPos.second != M-1) {
            if (map[curPos.first][curPos.second] < map[curPos.first][curPos.second+1]) {
                if (pathsDown[curPos.first][curPos.second].cost + 1 > pathsDown[curPos.first][curPos.second+1].cost) {
                    pathsDown[curPos.first][curPos.second+1].cost = pathsDown[curPos.first][curPos.second].cost + 1;
                    pathsDown[curPos.first][curPos.second+1].before = std::make_pair(curPos.first, curPos.second);
                    Q.push(std::make_pair(curPos.first, curPos.second+1));
                }
            }
        }
    }

    int bestPathCost = 0;
    std::pair<int, int> bestPathPos;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // cout << pathsDown[i][j].cost + pathsUp[i][j].cost << " | ";
            if (pathsDown[i][j].cost + pathsUp[i][j].cost > bestPathCost) {
                bestPathCost = pathsDown[i][j].cost + pathsUp[i][j].cost;
                bestPathPos = std::make_pair(i, j);
            }
        }
    }

    vector<std::pair<int, int>> answer;

    int curX = bestPathPos.first;
    int curY = bestPathPos.second;
    while (curX != start.first || curY != start.second) {
        int oldX = curX;
        int oldY = curY;
        answer.push_back(std::make_pair(curX, curY));
        curX = pathsUp[oldX][oldY].before.first;
        curY = pathsUp[oldX][oldY].before.second;
    }

    std::reverse(answer.begin(), answer.end());

    curX = pathsDown[bestPathPos.first][bestPathPos.second].before.first;
    curY = pathsDown[bestPathPos.first][bestPathPos.second].before.second;

    while (curX != end.first || curY != end.second) {
        int oldX = curX;
        int oldY = curY;
        answer.push_back(std::make_pair(curX, curY));
        curX = pathsDown[oldX][oldY].before.first;
        curY = pathsDown[oldX][oldY].before.second;
    }

    std::reverse(answer.begin(), answer.end());

    out << bestPathCost+1 << endl;
    out << start.second << " " << start.first << endl;
    for (int i = answer.size()-1; i > -1; i--) {
        out << answer[i].second << " " << answer[i].first << endl;
    }
    
    out << end.second << " " << end.first << endl;
}