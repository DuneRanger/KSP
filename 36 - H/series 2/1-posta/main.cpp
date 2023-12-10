#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

std::string fileDir = "./inOut/04";
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

    int Q, P;
    in >> Q >> P;

    std::map<int, std::queue<int>> queues;
    vector<std::pair<int, int>> customers; // customer arrival time and time waiting

    std::queue<int> q;
    queues.emplace(0, q);

    for (int p = 0; p < P; p++) {
        std::queue<int> temp;
        int t, j, k;
        char instr;
        in >> t >> instr;
        switch(instr) {
            case 'N':
                customers.push_back(std::make_pair(t, std::numeric_limits<int>::max()));
                queues[0].push(customers.size()-1);
                break;
            case 'P':
                in >> j >> k;
                queues.emplace(k, temp);
                queues[k].push(queues[j].front());
                queues[j].front();
                queues[j].pop();
                break;
            case 'V':
                in >> j;
                customers[queues[j].front()].second = t - customers[queues[j].front()].first + 1;
                queues[j].pop();
                break;
        }
    }

    int bestTime = -1;
    int minWait = std::numeric_limits<int>::max();
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].second < minWait) {
            bestTime = customers[i].first;
            minWait = customers[i].second;
        }
    }
    out << minWait+1 << " " << bestTime-1;
}