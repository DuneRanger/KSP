#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <limits>
using namespace std;

int SpecialisedGetIndex(pair<int, int>* input, int start, int end, int searched) {
        for (int i = start; i < end; i++) {
        if (input[i].first == searched) {
            return i;
        }
    }
    return -1;
}

uint64_t SpecialisedGetMaxOfPairs(pair<uint64_t, uint64_t>* input, int end, bool temp) {
    uint64_t max = 0;
    if (temp) {
        for (int i = 0; i < end; i++) {
            if (input[i].first > max) {
                max = input[i].first;
            }
        }
    } else {
        for (int i = 0; i < end; i++) {
            if (input[i].second > max) {
                max = input[i].second;
            }
        } 
    }
    return max;
}

uint64_t SpecialisedGetMinOfPairs(pair<uint64_t, uint64_t>* input, int end, bool temp) {
    uint64_t min = numeric_limits<float>::infinity();
    if (temp) {
        for (int i = 0; i < end; i++) {
            if (input[i].first < min) {
                min = input[i].first;
            }
        }
    } else {
        for (int i = 0; i < end; i++) {
            if (input[i].second < min) {
                min = input[i].second;
            }
        } 
    }
    return min;
}

int main() {
    string fileDir = "inOut/03";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int n;
    inputFile >> n;
    cout << n << endl;

    pair<uint64_t, uint64_t>* days = new pair<uint64_t, uint64_t>[n];

    uint64_t a, b;
    for (int i = 0; i < n; i++) {
        inputFile >> a >> b;
        days[i] = make_pair(a, b);
    }

    uint64_t temp1, temp2;
    string answer;
    temp1 = SpecialisedGetMaxOfPairs(days, n, true);
    temp2 = SpecialisedGetMinOfPairs(days, n, false);

    answer = to_string(temp1) + " " + to_string(n);

    delete[] days;


    cout << answer;

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();

}