// Problem URL: https://leetcode.com/problems/valid-sudoku/

#include <bits/stdc++.h>

using namespace std;

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // Code to do row by row, and then column by column
        for(int doThisTwice = 0; doThisTwice < 2; doThisTwice++) {
            for(int i = 0; i < 9; i++) {
                vector<int> counters(9, 0);
                for(int j = 0; j < 9; j++) {
                    char currentValue = doThisTwice ? board[i][j] : board[j][i];
                    if (currentValue != '.') {
                        counters[currentValue - '1']++;
                    }
                }

                for(int k = 0; k < 9; k++) {
                    if (counters[k] > 1) {
                        return false;
                    }
                }
            }
        }

        // Code to check the 9 different 3x3 squares
        for(int col = 0; col < 3; col++) {
            for(int row = 0; row < 3; row++) {
                vector<int> counters(9, 0);
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        char currentValue = board[row * 3 + i][col * 3 + j];

                        if (currentValue != '.') {
                            counters[currentValue - '1']++;
                        }
                    }
                }

                for(int k = 0; k < 9; k++) {
                    if (counters[k] > 1) {
                        return false;
                    }
                }
            }
        }

        return true;
    }
};

    bool isValidSudoku(vector<vector<char>>& board) {
        // Code to do row by row, and then column by column
        for(int doThisTwice = 0; doThisTwice < 2; doThisTwice++) {
            for(int i = 0; i < 9; i++) {
                vector<int> counters(9, 0);
                for(int j = 0; j < 9; j++) {
                    char currentValue = doThisTwice ? board[i][j] : board[j][i];
                    if (currentValue != '.') {
                        counters[currentValue - '1']++;
                    }
                }

                for(int k = 0; k < 9; k++) {
                    if (counters[k] > 1) {
                        return false;
                    }
                }
            }
        }

        // Code to check the 9 different 3x3 squares
        for(int col = 0; col < 3; col++) {
            for(int row = 0; row < 3; row++) {
                vector<int> counters(9, 0);
                for(int i = 0; i < 3; i++) {
                    for(int j = 0; j < 3; j++) {
                        char currentValue = board[row * 3 + i][col * 3 + j];

                        if (currentValue != '.') {
                            counters[currentValue - '1']++;
                        }
                    }
                }

                for(int k = 0; k < 9; k++) {
                    if (counters[k] > 1) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

int main() {

    /*
    0["1","2","3","4","5","6","7","8","9"],

    1[".",".",".",".","5",".",".","1","."],
    2[".","4",".","3",".",".",".",".","."],
    3[".",".",".",".",".","3",".",".","1"],
    4["8",".",".",".",".",".",".","2","."],
    5[".",".","2",".","7",".",".",".","."],
    6[".","1","5",".",".",".",".",".","."],
    7[".",".",".",".",".","2",".",".","."],
    8[".","2",".","9",".",".",".",".","."],
    9[".",".","4",".",".",".",".",".","."]
    */

    vector<vector<char>> inp_board = 
    {
        {'.', '.', '.', '.', '5', '.', '.', '1', '.'},
        {'.', '4', '.', '3', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '3', '.', '.', '1'},
        {'.', '.', '.', '.', '.', '.', '.', '2', '.'},
        {'.', '.', '2', '.', '7', '.', '.', '.', '.'},
        {'.', '1', '5', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '2', '.', '.', '.'},
        {'.', '2', '.', '9', '.', '.', '.', '.', '.'},
        {'.', '.', '4', '.', '.', '.', '.', '.', '.'},
    };


    cout << "True: " << true << endl;
    cout << isValidSudoku(inp_board) << endl;
}