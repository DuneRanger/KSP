#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

/*
    return a < b ? -1 : a > b ? 1 : 0
    @param int|double|float|uint64_t|char|string
*/
int compare(int a, int b) {
    return a < b ? -1 : a > b ? 1 : 0;
}

int compare(double a, double b) {
    return a < b ? -1 : a > b ? 1 : 0;
}

int compare(float a, float b) {
    return a < b ? -1 : a > b ? 1 : 0;
}

int compare(uint64_t a, uint64_t b) {
    return a < b ? -1 : a > b ? 1 : 0;
}

int compare(char a, char b) {
    return a < b ? -1 : a > b ? 1 : 0;
}

int compare(std::string a, std::string b) {
    int result = 0;
    int ind = 0;
    while (result == 0 && ind < std::min(a.size(), b.size())) {
        result = a[ind] < b[ind] ? -1 : a[ind] > b[ind] ? 1 : 0;
        ind++;
    }
    if (result == 0) result = a.size() < b.size() ? -1 : a.size() > b.size() ? 1 : 0;
    return result;
}

/*
    Works for 1D arrays of any type
*/
template <typename T>
int BinaryArraySearch(std::vector<T> arr, int left, int right, T val) {
    int found = -1;
    int middle = (left+right)/2;
    while (left <= right) {
        cout << left << " " << middle << " " << right << endl;
        if (compare(arr[middle], val) == 0) {
            found = middle;
            right = middle-1;
        } else if (compare(arr[middle], val) == 1) {
            right = middle-1;
        } else {
            left = middle+1;
        }
        middle = (left+right)/2;
    }
    return found;
}

int main() {
    using std::cout;
    using std::string;
    using std::vector;
    using std::endl;

    string fileDir = "./inOut/test";
    std::ifstream inputFile;
    std::ofstream outputFile;

    inputFile.open(fileDir + ".in", std::ios::in);

    uint64_t answer = 0;
    int inpLen;
    inputFile >> inpLen;


    outputFile.open(fileDir + ".out", std::ios::out);
    outputFile << answer;
    outputFile.close();
}