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
// #define in std::cin
// #define out std::cout

struct Node {
    int id;
    std::vector<std::pair<int, int>> edges; //edge destination and 
    
    Node(int a) {
        id = a;
    }
};

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int N, M;
    in >> N >> M;

    vector<Node> Nodes;
    for (int i = 0; i < N; i++) {
        Nodes.push_back(Node(i));
    }

    for (int i = 0; i < M; i++) {
        int a, b, c;
        in >> a >> b >> c;
        Nodes[a].edges.push_back(std::make_pair(b, c));
        Nodes[b].edges.push_back(std::make_pair(a, c));
    }


    out << answer;
}