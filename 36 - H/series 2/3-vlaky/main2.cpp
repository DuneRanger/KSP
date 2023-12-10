#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

std::string fileDir = "./inOut/test";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

#define in inputFile
#define out outputFile
// #define in std::cin
// #define out std::cout

// struct station {};

struct arrival {
    std::string trainName;
    int time;
    std::map<std::string, int> trainWaitTimes; // wait time for this arrival for each train
    arrival(std::string n, int a) {
        trainName = n;
        time = a;
    };
};

struct departure {
    std::string trainName;
    std::string stationN;
    int trainArriv;
    std::map<std::string, int> transferTimes;
    departure(std::string n, std::string s, int i) {
        trainName = n;
        stationN = s;
        trainArriv = i;
    };
};

struct qEl {
    std::string st;
    std::string train;
    int totalWaitTime;
    qEl(std::string s, std::string t, int w) {
        st = s;
        train = t;
        totalWaitTime = w;
    }
};

struct station {
    std::string name;
    std::vector<arrival> arrivals;
    std::vector<departure> departures;
    std::map<std::string, qEl> idealTrains; // each train has it's best waitTime and last station name
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
        string name;
        int stationCount;
        in >> name >> stationCount;

        for (int s = 0; s < stationCount; s++) {
            string sName;
            int time;
            in >> sName >> time;

            if (stations.find(sName) == stations.end()) {
                station temp;
                temp.name = sName;
                temp.arrivals.push_back(arrival(name, time));
                stations.emplace(std::make_pair(sName, temp));
            } else {
                stations[sName].arrivals.push_back(arrival(name, time));
            }
            stations[sName].departures.push_back(departure(name, sName, time));
            stations[sName].idealTrains.emplace(std::make_pair(name, qEl(sName, name, std::numeric_limits<int>::max())));
        }
    }

    for (std::map<string, station>::iterator it = stations.begin(); it  != stations.end(); it++) {
        station *curStation = &it->second;
        for (int i = 0; i < curStation->arrivals.size(); i++) {
            arrival *arriv = &curStation->arrivals[i];
            for (int j = 0; j < curStation->departures.size(); i++) {
                int time = curStation->departures[j].trainArriv - arriv->time;
                if (time < 0) time += 86400;
                curStation->departures[j].transferTimes.emplace(std::make_pair(arriv->trainName, time));
            }
        }
    }

    std::queue<qEl> Q;

    for (vector<departure>::iterator it = stations[start].departures.begin(); it != stations[start].departures.end(); it++) {
        station *depSt = &stations[it->stationN];
        int time = it->trainArriv - startTime;
        if (time < 0) time += 86400;
        depSt->idealTrains[it->trainName].totalWaitTime = time;
        depSt->idealTrains[it->trainName].st = start;
        depSt->idealTrains[it->trainName].train = it->trainName;
        Q.push(qEl(it->stationN, it->trainName, time));
    }

    while (!Q.empty()) {
        station *curStation = &stations[Q.front().st];
        string train = Q.front().train;
        int totalTime = Q.front().totalWaitTime;
        Q.pop();

        for (vector<departure>::iterator it = curStation->departures.begin(); it != curStation->departures.end(); it++) {
            station *depSt = &stations[it->stationN];
            if (depSt->idealTrains[it->trainName].totalWaitTime > totalTime + it->transferTimes[train]) {
                depSt->idealTrains[it->trainName].totalWaitTime = totalTime + it->transferTimes[train];
                depSt->idealTrains[it->trainName].st = it->stationN;
                depSt->idealTrains[it->trainName].train = it->trainName;
                Q.push(qEl(it->stationN, it->trainName, totalTime + it->transferTimes[train]));
            }
        }
    }

    vector<string> answer;
    string curStation = end;
    // while (curStation != start) {
    //     answer.push_back(curStation + "\n");
    //     answer.push_back(stations[curStation].lastTrain + " ");
    //     curStation = stations[curStation].lastStation;
    // }

    for (std::map<string, qEl>::iterator it = stations[end].idealTrains.begin(); it != stations[end].idealTrains.end(); it++) {
        cout << it->second.train << " " << it->second.totalWaitTime << " " << it->second.st << endl;
    }

    // for (int i = answer.size()-1; i > -1; i++) {
    //     out << answer[i];
    // }
}