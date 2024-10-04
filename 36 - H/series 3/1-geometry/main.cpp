#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cmath>

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

double dist(std::pair<int, int> b1, std::pair<int, int> b2, std::pair<int, int> b3) {
    int x1 = b1.first;
    int y1 = b1.second;
    int x2 = b2.first;
    int y2 = b2.second;
    int x = b3.first;
    int y = b3.second;

    int nx = (y1-y2);
    int ny = -(x1-x2);
    int c = -nx*x1 - ny*y1;
    // std::cout << nx << "," << ny << "," << c << std::endl;
    return double(abs((nx*x + ny*y + c)))/(sqrt(nx*nx + ny*ny));
}

double BinarySearch(std::vector<std::pair<int, int>>* arr, int side) {
    double found = -1;

    int jumpSize = arr->size()/2;
    int middle = (side + jumpSize)%arr->size(); // gets the point "opposite" between left and right point of the side
    int left = (middle-1+arr->size())%arr->size();
    int right = (middle+1+arr->size())%arr->size();


    while (true) {
        double distM = dist((*arr)[(side-1+arr->size())%arr->size()], (*arr)[side%arr->size()], (*arr)[middle]);
        double distL = dist((*arr)[(side-1+arr->size())%arr->size()], (*arr)[side%arr->size()], (*arr)[left]);
        double distR = dist((*arr)[(side-1+arr->size())%arr->size()], (*arr)[side%arr->size()], (*arr)[right]);

        jumpSize = std::max(1, jumpSize/2);
        // std::cout << middle << " " << distL << " " << distM << " " << distR << std::endl;
        if (distM >= distL) {
            if (distM >= distR) {
                return distM;
            } else {
                middle = (middle+jumpSize)%arr->size();
            }
        } else {
            middle = (middle-jumpSize+arr->size())%arr->size();
        }
        left = (middle-1+arr->size())%arr->size();
        right = (middle+1+arr->size())%arr->size();
    }

    return found;
}

int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    uint64_t answer = 0;
    int N;
    in >> N;

    vector<std::pair<int, int>> points;

    for (int i = 0; i < N; i++) {
        int x, y;
        in >> x >> y;
        points.push_back(std::make_pair(x, y));
    }


    vector<double> dists;
    std::pair<double, int> bestSide = std::make_pair(0, 0);
    for (int i = 0; i < N; i++) {
        // cout << "side: " << points[i].first << " " << points[i].second << " " << points[(i+1)%N].first << " " << points[(i+1)%N].second << endl;
        dists.push_back(BinarySearch(&points, i+1));
        if (dists[i] > bestSide.first) bestSide = std::make_pair(dists[i], i+1);
    }


    out << bestSide.second;
}