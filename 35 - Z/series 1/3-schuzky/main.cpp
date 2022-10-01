#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <limits>
using namespace std;

int main() {
    string fileDir = "inOut/06";
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

    // sort(days, days+n, [](auto &left, auto &right) {
    //     return left.second < right.second;
    // });

    uint64_t* values = new uint64_t[n];

    cout << "n^2 searching" << endl;

    for (int i = 0; i < n; i++) {
        uint64_t currentDay = days[i].first;
        uint64_t valueCounter = 1;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            else if (days[j].first > currentDay) continue;
            else if (days[j].second < currentDay) continue;
            else valueCounter++;
        }
        values[i] = valueCounter;
    }

    cout << "indexing" << endl;
    uint64_t bestValue = *max_element(values, values+n);
    uint64_t bestValueIndex;
    for (int i = 0; i < n; i++) {
        if (values[i] == bestValue) {
            bestValueIndex = i;
            break;
        }
    }
    uint64_t bestDay = days[bestValueIndex].first;

    answer = to_string(bestDay) + " " + to_string(bestValue);

    delete[] days;


    cout << answer;

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();

}