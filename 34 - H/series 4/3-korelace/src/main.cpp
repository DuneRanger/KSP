#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int specializedGetIndex(int (*arr)[3], int key, int start = 0)
{
    for (int i = start+1; i < 300000; i++)
    {
        if (*(arr+i*3)[0] == key || *(arr+i*3)[1] == key) {
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

    int (*data)[3] = new int[900000][3];

    int c, d, e;
    for (int i = 0; i < b; i++) {
        inputFile >> c >> d >> e;
        *(data+i*3)[0] = c;
        *(data+i*3)[1] = d;
        *(data+i*3)[2] = e;
    }
    inputFile.close();

    map<int, int> statements;
    for (int i = 0; i < a; i++) {
        statements[i] = -1;
    }

    vector<int> path = {0};
    int ind = -1;
    int justInCase = 0;
    int key = -1;
    int key2 = -1;
    string ans = "";
    int ansLen = -1;
    //Variables for logging
    int lastOne = 0;
    int num = 0;

    
    while (ans.size() < 1) {
        num++;
        key = path[path.size()-1];
        ind = specializedGetIndex(data, key);
        if (!(path.size()%1000)) {
            int temp = num-path.size();
            cout << "path length:" << path.size() << "iterations:" << num << "paths removed since last log:" << (temp-lastOne) << "paths removed total:" << temp << endl;
            lastOne = temp;
        }
        label:
            while (ind == -1) {
                path.pop_back();
                if (path.size() == 0) {
                    justInCase++;
                    path.push_back(justInCase);
                }
                key = path[path.size()-1];
                ind = specializedGetIndex(data, key);
            }
        while (*(data+ind*3)[0] == NULL) {
            ind = specializedGetIndex(data, key, ind);
            if (ind == -1) goto label;
        }
        key2 = *(data+ind*3)[0] == key ? *(data+ind*3)[1] : *(data+ind*3)[0];
        path.push_back(key2);
        if (*(data+ind*3)[2] == 1) {
            if (statements[key2] != -1 && statements[key2] != statements[key]) {
                int startInd = -1;
                for (int i = 0; i < path.size(); i++) {
                    if (path[i] == key2) {
                        startInd = i;
                        break;
                    } 
                }
                if (startInd == -1) break;
                for (int i = startInd; i < path.size(); i++) {
                    ans += to_string(path[i]) + " ";
                }
                ansLen = path.size()-startInd;
            }
            else statements[key2] = statements[key];
        }
        else {
            if (statements[key2] != -1 && statements[key2] == statements[key]) {
                int startInd = -1;
                for (int i = 0; i < path.size(); i++) {
                    if (path[i] == key2) {
                        startInd = i;
                        break;
                    } 
                }
                if (startInd == -1) break;
                for (int i = startInd; i < path.size(); i++) {
                    ans += to_string(path[i]) + " ";
                }
                ansLen = path.size()-startInd;
            }
            else statements[key2] = !statements[key];
        }
        *(data+ind*3)[0] = NULL;
    }

    delete[] data;

    outputFile.open(fileDir + ".txt", ios::out);
    outputFile << ansLen << "\n" << ans;
    outputFile.close();

    return 0;
}