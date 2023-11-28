#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>

std::string fileDir = "./inOut/random-10";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

enum state {open, visited, closed};

struct Node {
    int id;
    std::vector<std::pair<int, int>> edges; //edge destination and 
    state curState;
    int pathCost;
    
    Node(int a) {
        id = a;
        curState = open;
        pathCost = INT32_MAX;
    }
};

struct Compare {
    bool operator()(const std::pair<int, int> l, const std::pair<int, int> r) const { return l.second < r.second; }
};

int Dijsktra(std::vector<Node> vertices, int startID, int endID) {
    std::vector<std::pair<int, int>> toVisit;
    vertices[startID].pathCost = 0;

    toVisit.push_back(std::make_pair(startID, 0));

    while (toVisit.size()) {
        Node curNode = vertices[toVisit.front().first];
        std::pop_heap(toVisit.begin(), toVisit.end(), Compare());
        toVisit.pop_back();

        std::cout << curNode.id << " ";
        std::cout << curNode.pathCost << " ";
        std::cout << curNode.edges.size() << std::endl;

        for (int i = 0; i < curNode.edges.size(); i++) {
            if (vertices[curNode.edges[i].first].curState != closed) {
                if (vertices[curNode.edges[i].first].curState != visited) {
                    toVisit.push_back(std::make_pair(curNode.edges[i].first, vertices[curNode.edges[i].first].pathCost));
                    std::push_heap(toVisit.begin(), toVisit.end(), Compare());
                    vertices[curNode.edges[i].first].curState = visited;
                }
                if (vertices[curNode.edges[i].first].pathCost > curNode.pathCost + curNode.edges[i].second) {
                    // std::cout << vertices[curNode.edges[i].first].id << " " << curNode.pathCost << " " << curNode.pathCost + curNode.edges[i].second << " ";
                    vertices[curNode.edges[i].first].pathCost = curNode.pathCost + curNode.edges[i].second;
                    // std::cout << vertices[curNode.edges[i].first].id << std::endl;
                    std::make_heap(toVisit.begin(), toVisit.end(), Compare());
                }
            }
        }
            for (int j = 0; j < toVisit.size(); j++) {
                std::cout << toVisit[j].id << " " << toVisit[j].pathCost << " ";
            }
            std::cout << std::endl;

        curNode.curState = closed;
    }

    return vertices[endID].pathCost;

}

//GOAL go from node 0 to N-1

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


    out << Dijsktra(Nodes, 0, N-1);
}