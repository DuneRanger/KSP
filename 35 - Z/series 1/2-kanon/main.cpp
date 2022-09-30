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

void Merge(int* Unsorted, int left, int middle, int right) {
    //Console.WriteLine("Merge: " + left + " " + middle + " " + right);

    int LSize = middle - left + 1;
    int RSize = right - middle;

    int* L = new int[LSize]; // +1 to include left (or middle, depending on your thought process)
    int* R = new int[RSize];

    for (int i = 0; i < LSize; i++) {
        L[i] = Unsorted[left + i];
    }

    for (int i = 0; i < RSize; i++) {
        R[i] = Unsorted[middle + 1 + i];
    }

    int LI = 0;
    int RI = 0;

    int OgI = left; // Index of where the lower number will be in the original array

    while (LI < LSize && RI < RSize) {  
        if (L[LI] < R[RI]) {
            Unsorted[OgI] = L[LI];
            LI++;
        }
        else {
            Unsorted[OgI] = R[RI];
            RI++;
        }
        OgI++;
    }

    if (LI < LSize) {
        for (; LI < LSize; LI++, OgI++) {
            Unsorted[OgI] = L[LI];
        }
    } else {
        for (; RI < RSize; RI++, OgI++) {
            Unsorted[OgI] = R[RI];
        }
    }
}

void SpecialisedMergeSort(int* Unsorted, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2; // left index + half the length
        SpecialisedMergeSort(Unsorted, left, middle);
        SpecialisedMergeSort(Unsorted, middle + 1, right);

        Merge(Unsorted, left, middle, right);
    }
    return;
}

int main() {
    string fileDir = "inOut/test";
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open(fileDir + ".in", ios::in);

    int width, height, cannNumber;
    inputFile >> width >> height >> cannNumber;
    cout << width << " " << height << " " << cannNumber << endl;

    int* cannons = new int[cannNumber*2];
}