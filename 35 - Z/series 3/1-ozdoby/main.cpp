#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

std::ifstream inputFile;
std::ofstream outputFile;
#define in std::cin
#define out std::cout

struct source {
    int pot;
    int price;
    int origInd;
};

struct light {
    int minPot;
    int maxPot;
};

int main() {
    using std::cout;
    using std::string;
    using std::vector;
    using std::endl;

    string fileDir = "./inOut/01";

    // inputFile.open(fileDir + ".in", std::ios::in);

    vector<int> answer = {0, 0, 0, 0};
    int lightNum;
    in >> lightNum;

    vector<source> sources;
    for (int i = 0; i < 3; i++) {
        source temp;
        in >> temp.pot >> temp.price;
        temp.origInd = i;
        sources.push_back(temp);
    }

    sort(sources.begin(), sources.end(), [](source a, source b) {return a.price < b.price;});

    vector<light> lights;
    for (int i = 0; i < lightNum; i++) {
        light temp;
        in >> temp.minPot >> temp.maxPot;
        for (int j = 0; j < sources.size(); j++) {
            if (sources[j].pot >= temp.minPot && sources[j].pot <= temp.maxPot) {
                answer[sources[j].origInd] += 1;
                answer[3] += sources[j].price;
                break;
            }
        }
    }


    // outputFile.open(fileDir + ".out", std::ios::out);
    out << answer[0] << " " << answer[1] << " " << answer[2] << " " << answer[3];
    // outputFile.close();
}