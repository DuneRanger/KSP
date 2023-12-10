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

struct departure {
    std::string trainName;
    std::string stationN;
    int arrival;
    std::map<std::string, int> trainWaitTimes; // wait time for this departure for each train
    departure(std::string n, std::string s, int a) {
        trainName = n;
        stationN = s;
        arrival = a;
    };
};

typedef std::pair<int, std::string> idealTrain;

struct station {
    std::string name;
    std::vector<departure> departures;
    std::map<std::string, idealTrain> idealTrains; // each train has it's best waitTime and last station name
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
            int departTime;
            in >> sName >> departTime;

            if (stations.find(sName) == stations.end()) {
                station temp;
                temp.name = sName;
                temp.departures.push_back(departure(name, sName, departTime));
                stations.emplace(sName, temp);
            } else {
                stations[sName].departures.push_back(departure(name, sName, departTime));
            }
        }
    }

    for (std::map<string, station>::iterator it = stations.begin(); it  != stations.end(); it++) {
        station *curStation = &it->second;
        for (int i = 0; i < curStation->departures.size(); i++) {
            departure *dep = &curStation->departures[i];
            station *depStation = &stations[dep->stationN];
            
        }
    } 

    std::queue<station*> Q;
    Q.push(&stations[start]);

    while (!Q.empty()) {
        station *curStation = Q.front();
        Q.pop();

        for (int i = 0; i < curStation->departures.size(); i++) {
            
        }
    }

    vector<string> answer;
    string curStation = end;
    // while (curStation != start) {
    //     answer.push_back(curStation + "\n");
    //     answer.push_back(stations[curStation].lastTrain + " ");
    //     curStation = stations[curStation].lastStation;
    // }

    for (int i = answer.size()-1; i > -1; i++) {
        out << answer[i];
    }
}