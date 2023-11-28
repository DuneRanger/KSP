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

#define in inputFile
#define out outputFile
#define in std::cin
#define out std::cout

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int R, S, x, y;
    in >> R >> S >> x >> y;
    int lastX, lastY;

    vector<string> map;

    for (int i = 0; i < R; i++) {
        string a;
        in >> a;
        map.push_back(a);
    }

    while (true) {
        switch(map[y][x]) {
            case '>':
                x++;
                break;
            case '<':
                x--;
                break;
            case '^':
                y--;
                break;
            case 'v':
                y++;
                break;
        }
        if (x >= S || x < 0 || y >= R || y < 0) {
            break;
        }
        lastX = x;
        lastY = y;
    }

    out << lastX << " " << lastY;
}