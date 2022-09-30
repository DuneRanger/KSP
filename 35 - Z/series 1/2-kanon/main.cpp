#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;

int SpecialisedGetIndex(pair<int, int>* input, int start, int end, int searched) {
        for (int i = start; i < end; i++) {
        if (input[i].first == searched) {
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

    int width, height, cannNumber;
    inputFile >> width >> height >> cannNumber;
    cout << width << " " << height << " " << cannNumber << endl;

    pair<int, int>* cannons = new pair<int, int>[cannNumber];

    int x, y;
    for (int i = 0; i < cannNumber; i++) {
        inputFile >> x >> y;
        cannons[i] = make_pair(x, y);
    }
    pair<int, int>* originalCannons = new pair<int, int>[cannNumber];
    copy(cannons, cannons+cannNumber, originalCannons);
    sort(cannons, cannons+cannNumber);

    // for (int i = 0; i < cannNumber; i++) {
    //     cout << cannons[i].first << " " << cannons[i].second << endl;
    // }
    cout << "actually searching now" << endl;

    string answer = "";
    for (int i = 0; i < cannNumber; i++) {
        int baseX = cannons[i].first;
        int baseY = cannons[i].second;
        for (int n = 0; n < cannNumber; n++) {
            if (n!= i && (cannons[n].first > cannons[n].second == cannons[i].first > cannons[i].second)) {
                if (cannons[n].first - cannons[n].second == cannons[i].first - cannons[i].second) {
                    cout << cannons[n].first << " " << cannons[n].second << " " << cannons[i].first << " " << cannons[i].second << endl;
                    cout << cannons[n].first - cannons[n].second << " " << cannons[i].first - cannons[i].second << endl;
                    cout << "searchin in original" << endl;
                    int temp;
                    do {
                        temp = SpecialisedGetIndex(originalCannons, 0, cannNumber, baseX);

                    } while (originalCannons[temp].second != baseY);
                    answer += to_string(temp) + " ";
                    do {
                        temp = SpecialisedGetIndex(originalCannons, 0, cannNumber, cannons[n].first);

                    } while (originalCannons[temp].second != cannons[n].second);
                    answer += to_string(temp);
                    goto end;
                }
            }
        }
        // int y = baseY-1;
        // int x = baseX-1;
        // while (x > -1 && y > -1) {
        //     int tempIndex = SpecialisedGetIndex(cannons, 0, i, x);


        // }



        // y = baseY+1;
        // for (int x = baseX+1; x < width && y < height; x++, y++) {
        //     int tempIndex = SpecialisedGetIndex(cannons, i, cannNumber, x);
        //     if (tempIndex > -1 && cannons[tempIndex].second == y) {
        //         int temp;
        //         do {
        //             temp = SpecialisedGetIndex(originalCannons, 0, cannNumber, baseX);

        //         } while (originalCannons[temp].second != baseY);
        //         answer += to_string(temp) + " ";
        //         do {
        //             temp = SpecialisedGetIndex(originalCannons, 0, cannNumber, x);

        //         } while (originalCannons[temp].second != y);
        //         answer += to_string(temp);
        //         goto end;
        //     }
        // }
    }
    end:
    {
        cout << answer;
        delete[] cannons;

        outputFile.open(fileDir + ".out", ios::out);
        outputFile << answer;
        outputFile.close();
    }


}