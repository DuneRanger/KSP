#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int getIndexOfString(string* input, int start, int end, string searched) {
        for (int i = start; i < end; i++) {
        if (input[i] == searched) {
            return i;
        }
    }
    return -1;
}

int main() {
    string fileDir = "inOut/05";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int a, b;
    inputFile >> a >> b;
    cout << a << " " << b << endl;

    string* words = new string[a];
    string* searches = new string[b*2];

    string c;
    for (int i = 0; i < a; i++) {
        inputFile >> c;
        words[i] = c;
    }

    string d, e;
    for (int i = 0; i < b; i++) {
        inputFile >> d >> e;
        string* temp = new string[2];
        temp[0] = d;
        temp[1] = e;
        sort(temp, temp+2);
        // cout << temp[0] << temp[1] << endl;
        searches[i*2] = temp[0];
        searches[i*2+1] = temp[1];
    }

    cout << "input parsed" << endl;
    
    inputFile.close();
    
    sort(words, words+a);

    cout << "words sorted" << endl;

    string answer = "";
    for (int i = 0; i < b; i++) {
        int index1 = getIndexOfString(words, 0, a, searches[i*2]);
        int index2 = getIndexOfString(words, index1, a, searches[i*2+1]);
        answer += to_string(index2-index1-1) + "\n";
    }


    // string wordsAsText = "";
    // for (int i = 0; i < a; i++) {
    //     wordsAsText += words[i] + "\n";
    // }

    delete[] words;

    // for (int i = 0; i < b; i++) {
    //     wordsAsText += searches[i*2] + " " + searches[i*2+1] + "\n";
    // }

    delete[] searches;

    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();

    return 0;
}