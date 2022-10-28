#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <math.h>
using namespace std;


int primeNumCount(int num) {
    return num/log(num);
}

int countDivisors(int n)
{
    int cnt = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            // If divisors are equal,
            // count only one
            if (n == i)
                if (i%2 == 1) cnt++;
 
            else // Otherwise count both
                if (i%2 == 1) cnt = cnt + 2;
        }
    }
    return cnt;
}

int divisorsCount(int n)
{
    int cnt = 0;
    int i;
    for (i = 1; i * i < n; i++) {
        if (n % i == 0)
            if (i%2 == 1) cnt++;
            // cnt++;
    }
    if (i - (n / i) == 1) {
        i--;
    }
    for (; i >= 1; i--) {
        if (n % i == 0)
            if ((n/i)%2 == 1) cnt++;
            // cnt++;
    }
    return cnt;
}

void printDivisors(int n)
{
    int i;
    for (i = 1; i * i < n; i++) {
        if (n % i == 0)
            cout << i << " ";
    }
    if (i - (n / i) == 1) {
        i--;
    }
    for (; i >= 1; i--) {
        if (n % i == 0)
            cout << n/i << " ";
    }
}

int main() {
    string fileDir = ".data";
    ifstream inputFile;
    ofstream outputFile;

    string data;
    for (int i = 3; i < 1000000; i+=2) {
        data += to_string(i) + "," + to_string(primeNumCount(i)) + "," + to_string(i-divisorsCount(i)) + "\n"; 
    }

    outputFile.open(fileDir + ".csv", ios::out);
    outputFile << data;
    outputFile.close();
}