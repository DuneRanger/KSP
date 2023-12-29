#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

std::string fileDir = "./inOut/1";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

struct station;

struct departure {
    std::string trainName;
    station* from;
    station* to;
    int departTime;
    int arrivTime;
    departure(station *s, station *s2, std::string n, int t, int t2) {
        trainName = n;
        from = s;
        to = s2;
        departTime = t;
        arrivTime = t2;
    };
};

struct connection {
    station *lastStation;
    station *nextStation;
    std::string train;
    std::string arrivedWith = "";
    int totalWaitTime;
    bool transfer = false;
    station *transferStation;
    connection(station *s, station *s2, std::string t, int w) {
        lastStation = s;
        nextStation = s2;
        train = t;
        totalWaitTime = w;
    }
    connection() {}
};

struct station {
    std::string name;
    std::vector<departure> departures;
    std::map<std::string, connection> bestConnections; // each train has it's best waitTime and last station name
};


int main() {
    using std::string;
    using std::vector;
    using std::endl;
    using std::cout;

    string start, end;
    int startTime, trainCount;
    in >> start >> startTime;
    in >> end >> trainCount;

    std::map<std::string, station> stations;

    for (int t = 0; t < trainCount; t++) {
        string train;
        int stationCount;
        in >> train >> stationCount;
        string firstStation;
        string prevStation;
        int firstTime;
        int prevTime;

        for (int s = 0; s < stationCount; s++) {
            string sName;
            int time;
            in >> sName >> time;
            if (s == 0) {
                firstStation = sName;
                firstTime = time;
            }

            if (stations.find(sName) == stations.end()) {
                station temp;
                temp.name = sName;
                stations.emplace(std::make_pair(sName, temp));
            }
            if (s != 0) {
                stations[prevStation].departures.push_back(departure(&stations[prevStation], &stations[sName], train, prevTime, time));
                stations[prevStation].bestConnections.emplace(train, connection(&stations[prevStation], &stations[sName], train, std::numeric_limits<int>::max()));
            }
            if (s == stationCount-1) {
                stations[sName].departures.push_back(departure(&stations[sName], &stations[firstStation], train, time, firstTime));
                stations[sName].bestConnections.emplace(train, connection(&stations[sName], &stations[firstStation], train, std::numeric_limits<int>::max()));
            }

            prevStation = sName;
            prevTime = time;
        }
    }
    for (std::map<string, connection>::iterator it = stations[end].bestConnections.begin(); it != stations[end].bestConnections.end(); it++) {
        cout << it->first << " " << it->second.nextStation->name << " " << it->second.train << " " << it->second.lastStation->name << " " << it->second.totalWaitTime << endl;
    }
    cout << endl;

    std::queue<std::pair<connection*, std::pair<int, std::pair<string, string>>>> Q;

    for (vector<departure>::iterator it = stations[start].departures.begin(); it != stations[start].departures.end(); it++) {
        station *depSt = it->from;
        int waitTime = it->departTime - startTime;
        if (waitTime < 0) waitTime += 86400;
        depSt->bestConnections.at(it->trainName).totalWaitTime = waitTime;
        depSt->bestConnections.at(it->trainName).lastStation = &stations[start];
        depSt->bestConnections.at(it->trainName).train = it->trainName;
    
        Q.push(std::make_pair(&depSt->bestConnections.at(it->trainName), std::make_pair(it->arrivTime, std::make_pair("", ""))));
    }

    while (!Q.empty()) {
        connection* curCon = Q.front().first;
        int curTime = Q.front().second.first;
        string transferStation = Q.front().second.second.first;
        string transferTrain = Q.front().second.second.second;
        Q.pop();
        // cout << curCon->nextStation->name << " | ";

        for (vector<departure>::iterator it = curCon->nextStation->departures.begin(); it != curCon->nextStation->departures.end(); it++) {
            int waitTime = it->departTime - curTime;
            if (waitTime < 0) waitTime += 86400;
            if (curCon->nextStation->bestConnections.at(it->trainName).totalWaitTime > curCon->totalWaitTime + waitTime) {
                curCon->nextStation->bestConnections.at(it->trainName).totalWaitTime = curCon->totalWaitTime + waitTime;
                    
                
                if (transferStation != "") {
                    curCon->nextStation->bestConnections.at(it->trainName).lastStation = &stations[transferStation];
                    curCon->nextStation->bestConnections.at(it->trainName).arrivedWith = transferTrain;
                }
                else {
                    curCon->nextStation->bestConnections.at(it->trainName).lastStation = curCon->lastStation;
                    curCon->nextStation->bestConnections.at(it->trainName).train = it->trainName;
                }
                if (it->trainName == curCon->train) {
                    transferStation = "";
                    transferTrain = "";
                }
                else {
                    transferStation = curCon->nextStation->name;
                    transferTrain = curCon->train;
                }
                // cout << it->trainName << " " << curCon->train << " | ";
                // cout << curCon->nextStation->name << " " << curCon->nextStation->bestConnections.at(it->trainName).lastStation->name << " ||| ";
                Q.push(std::make_pair(&curCon->nextStation->bestConnections.at(it->trainName), std::make_pair(it->arrivTime, std::make_pair(transferStation, transferTrain))));
            }
        }
        // cout << endl;
    }

    // for (std::map<string, connection>::iterator it = stations[end].bestConnections.begin(); it != stations[end].bestConnections.end(); it++) {
    //     cout << it->first << " " << it->second.train << " " << it->second.arrivedWith << " " << it->second.lastStation->name << " " << it->second.nextStation->name << " " << it->second.totalWaitTime << endl;
    // }
    // cout << endl;
    // for (std::map<string, connection>::iterator it = stations["PREROV"].bestConnections.begin(); it != stations["PREROV"].bestConnections.end(); it++) {
    //     cout << it->first << " " << it->second.train << " " << it->second.arrivedWith << " " << it->second.lastStation->name << " "  << it->second.nextStation->name << " "<< it->second.totalWaitTime << endl;
    // }
    // cout << endl;
    // for (std::map<string, connection>::iterator it = stations["ZABREH-NA-MORAVE"].bestConnections.begin(); it != stations["ZABREH-NA-MORAVE"].bestConnections.end(); it++) {
    //     cout << it->first << " " << it->second.train << " " << it->second.arrivedWith << " " << it->second.lastStation->name << " "  << it->second.nextStation->name << " "<< it->second.totalWaitTime << endl;
    // }
    vector<string> answer;
    station *curStation = &stations[end];
    answer.push_back(end + "\n");

    connection *curCon = nullptr;
    for (std::map<string, connection>::iterator it = curStation->bestConnections.begin(); it != curStation->bestConnections.end(); it++) {
        if (curCon == nullptr) curCon = &it->second;
        else if (it->second.totalWaitTime < curCon->totalWaitTime) curCon = &it->second;
    }
    string curTrain = curCon->train;
    answer.push_back(curTrain + " ");
    

    while (curCon->train != curCon->arrivedWith) {
        answer.push_back(curCon->lastStation->name + "\n");
        answer.push_back(curCon->arrivedWith + " ");

        curCon = &curCon->lastStation->bestConnections[curCon->train];
    }
    cout << answer.size();
    for (int i = answer.size()-1; i > -1; i--) {
        out << answer[i];
    }
}