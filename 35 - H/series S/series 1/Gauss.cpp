#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int parNum;
vector<vector<int>> leftMatrix;
vector<int> rightMatrix;

int gcd(int a,int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
 
int lcm(int a, int b)
{
    return (a * b / gcd(a, b));
}

int reorderMatrixRows(int ind) {
    int reordered = 0;
    for (int i = parNum-1; i > -1; i--) {
        bool cond = true;
        for (int j = 0; j <= ind; j++) {
            if (leftMatrix[i][j] != 0) {
                cond = false;
                break;
            }
        }
        if (cond) {
            swap(leftMatrix[i], leftMatrix[parNum-1-reordered]);
            swap(rightMatrix[i], rightMatrix[parNum-1-reordered]);
            reordered++;
        }
    }
    return reordered;
}

// int upTo is not inclusive!!
void nullifyMatrixColumn(int ind, int upTo) {
    for (int i = ind+1; i < upTo; i++) {
        int multiple1 = lcm(leftMatrix[i][ind], leftMatrix[ind][ind])/leftMatrix[ind][ind];
        int multiple2 = lcm(leftMatrix[i][ind], leftMatrix[ind][ind])/leftMatrix[i][ind];
        for (int j = ind; j < parNum; j++) {
            leftMatrix[i][j] = leftMatrix[i][j]*multiple2 - leftMatrix[ind][j]*multiple1;
        }
        rightMatrix[i] = rightMatrix[i]*multiple2 - rightMatrix[ind]*multiple1;
    }
}

int main() {
    string fileDir = "./inOut/03";
    ifstream inputFile;
    ofstream outputFile;

    string answer;

    inputFile.open(fileDir + ".in", ios::in);

    inputFile >> parNum;

    for (int i = 0; i < parNum; i++) {
        vector<int> tempParamHolder;
        int tempInp;
        for (int j = 0; j < parNum; j++) {
            inputFile >> tempInp;
            tempParamHolder.push_back(tempInp);
        }
        leftMatrix.push_back(tempParamHolder);
        inputFile >> tempInp;
        rightMatrix.push_back(tempInp);
    }
    cout << parNum << endl;

    for (int i = 0; i < parNum; i++) {
        for (int j = 0; j < parNum; j++) {
            for (int x = 0; x < parNum; x++) {
                cout << leftMatrix[j][x] << " ";
            }
            cout << rightMatrix[j] << endl;
        }
        cout << endl;
        int reordered = reorderMatrixRows(i);
        cout << reordered << " " << i << endl;
        nullifyMatrixColumn(i, parNum-reordered);
    } 

    //If this is true, the matrix can either be parameterized or is unsolveable
    if (leftMatrix[parNum-1][parNum-1] == 0) {
        if (rightMatrix[parNum-1] != 0) answer = "N";
        else {
            //This is going to look messy until I decide to refactor it
            //(Which is probably never, sorry whoever reads this, but I don't have much time)
            
        }
    } else {
        rightMatrix[parNum-1] /= leftMatrix[parNum-1][parNum-1];
        leftMatrix[parNum-1][parNum-1] = 1;
        for (int i = parNum-2; i > -1; i--) {
            for (int j = parNum-1; j > i; j--) {
                rightMatrix[i] -= leftMatrix[i][j]*rightMatrix[j];
                leftMatrix[i][j] = 0;
            }
            rightMatrix[i] /= leftMatrix[i][i];
            leftMatrix[i][i] = 1;
        }

        for (int j = 0; j < parNum; j++) {
            for (int x = 0; x < parNum; x++) {
                cout << leftMatrix[j][x] << " ";
            }
            cout << rightMatrix[j] << endl;
        }
        cout << endl;

        answer = "J\n";
        for (int i = 0; i < parNum; i++) {
            answer += to_string(rightMatrix[i]) + " ";
        }
    }


    outputFile.open(fileDir + ".out", ios::out);
    outputFile << answer;
    outputFile.close();    

}