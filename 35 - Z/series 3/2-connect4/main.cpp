#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

std::string fileDir = "./inOut/06";
std::ifstream inputFile(fileDir+".in");
std::ofstream outputFile(fileDir+".out");

// #define in std::cin
// #define out std::cout
#define in inputFile
#define out outputFile


bool checkWin(std::vector<std::vector<int8_t>> board, int col, int row) {

    if (row < 2) return false;
    
    // if the piece is in the bottom left of the 3x3
    if (col < board[0].size()-2) {
        int sum = 0;
        sum += board[row][col];
        sum += board[row][col+1];
        sum += board[row][col+2];
        sum += board[row-1][col];
        sum += board[row-1][col+1];
        sum += board[row-1][col+2];
        sum += board[row-2][col];
        sum += board[row-2][col+1];
        sum += board[row-2][col+2];
        if (sum == 9 || sum == -9) return true;
    }
    // if the piece is in the bottom middle of the 3x3
    if (col > 0 && col < board[0].size()-1) {
        int sum = 0;
        sum += board[row][col];
        sum += board[row][col+1];
        sum += board[row][col-1];
        sum += board[row-1][col];
        sum += board[row-1][col+1];
        sum += board[row-1][col-1];
        sum += board[row-2][col];
        sum += board[row-2][col+1];
        sum += board[row-2][col-1];
        if (sum == 9 || sum == -9) return true;
    }
    // if the piece is in the bottom right of the 3x3
    if (col > 1) {
        int sum = 0;
        sum += board[row][col];
        sum += board[row][col-2];
        sum += board[row][col-1];
        sum += board[row-1][col];
        sum += board[row-1][col-2];
        sum += board[row-1][col-1];
        sum += board[row-2][col];
        sum += board[row-2][col-2];
        sum += board[row-2][col-1];
        if (sum == 9 || sum == -9) return true;
    }

    return false;
}

int main() {
    using std::string;
    using std::vector;
    using std::endl;

    string answer = "";
    int inpLen, gameSize;
    in >> inpLen >> gameSize;

    vector<vector<int8_t>> game;
    vector<int8_t> baseRow;

    for (int i = 0; i < gameSize; i++) {
        baseRow.push_back(0);
    }
    game.push_back(baseRow);

    // 't' for the same player | 'f' for the other player | 'k' for kevin | 's' for sara
    vector<char> wins;
    vector<int> turns;

    int turn = 0;
    for (int i = 0; i < inpLen; i++) {
        int col;
        int row;
        in >> col;
        col--;
        turn++;
        

        bool added = false;
        for (int j = 0; j < game.size(); j++) {
            if (game[j][col] == 0) {
                game[j][col] = turn%2 == 1 ? 1 : -1;
                added = true;
                row = j;
                break;
            }
        }
        if (!added) {
            row = game.size();
            game.push_back(baseRow);
            game[game.size()-1][col] = turn%2 == 1 ? 1 : -1;
        }

        // for (int j = 0; j < game.size(); j++) {
        //     for (int k = 0; k < game[0].size(); k++){
        //         std::cout << (game[j][k]+1) << ",";
        //     }
        //     std::cout << endl;
        // }
        // std::cout << endl;

        if (checkWin(game, col, row)) {
            if (turn%2 == 1) {
                wins.push_back('f');
            }
            else {
                wins.push_back('t');
            }
            turns.push_back(i+1);
            game.clear();
            game.push_back(baseRow);
            turn = 0;
        }
    }

    int score = 0;
    char old = wins[wins.size()-1];
    wins[wins.size()-1] = 'k';
    score++;
    for (int i = wins.size()-2; i > -1; i--) {
        if (old == 't') {
            score++;
            old = wins[i];
            wins[i] = wins[i+1];
        }
        else {
            score--;
            old = wins[i];
            wins[i] = wins[i+1] == 'k' ? 's' : 'k';
        }
    }

    for (int i = 0; i < wins.size(); i++) {
        // std::cout << turns[i]+0;
        out << std::to_string(turns[i]+0);
        out << " ";
        out << (wins[i] == 'k' ? "Kevin" : "Sara");
        out << endl;
    }
    out << (score >= 0 ? score > 0 ? "Kevin" : "remiza" : "Sara");
}