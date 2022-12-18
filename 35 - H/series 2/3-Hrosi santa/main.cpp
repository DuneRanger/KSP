#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

int main() {
    using std::cout;
    using std::string;
    using std::__gcd;
    using std::endl;
    using std::min;
    using std::max;
    
    string fileDir = "./inOut/05";
    std::ifstream inputFile;
    std::ofstream outputFile;

    // inputFile.open(fileDir + ".in", std::ios::in);

    int capA, capB;
    // inputFile >> capA >> capB;
    std::cin >> capA >> capB;
    
    int goal;
    // inputFile >> goal;
    std::cin >> goal;
 
    string answer1 = "";
    string answer2 = "";

    int temp;
    int B = 0;
    int Bbefore = 0;
    int A = 0;
    int Abefore = 0;
    
    while (!(A == goal || B == goal)) {
        while (A < capA) {
            B = capB;
            answer1 += "B";

            Bbefore = B;
            B -= min(capA-A, B);
            A = min(capA, A+Bbefore);
            answer1 += "<";
            if (A == goal || B == goal) goto next;
        }
        A = 0;
        answer1 += "a";

        Bbefore = B;
        B -= min(capA-A, B);
        A = min(capA, A+Bbefore);
        answer1 += "<";
    }

    next:
    A, B = 0;

    while (!(A == goal || B == goal)) {
        while (B < capB) {
            A = capA;
            answer2 += "A";

            Abefore = A;
            A -= min(capB-B, A);
            B = min(capB, B+Abefore);
            answer2 += ">";
            if (A == goal || B == goal) goto end;
            // cout << A << B << endl;
        }
        B = 0;
        answer2 += "b";

        Abefore = A;
        A -= min(capB-B, A);
        B = min(capB, B+Abefore);
        answer2 += ">";
        // cout << A << B << endl;

    }

    end: {}

    // cout << answer1.size() << " " << answer2.size() << endl;
    string answer = answer1.size() <= answer2.size() ? answer1 : answer2;

    // outputFile.open(fileDir + ".out", ios::out);
    // outputFile << answer.size() << endl;
    // outputFile << answer;
    // outputFile.close();
    cout << answer.size() << endl;
    cout << answer;
}