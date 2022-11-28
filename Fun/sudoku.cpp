#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define isOdd & 1
#define qpow2(exponent) 1 << exponent
/* 2^exponent, because every time shifting bit to the leftBound you are essentially multiplying function by two */
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>

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

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

vector<vector<int>> board(9, vector<int>(9, 0));
vector<vector<set<int>>> possible(9, vector<set<int>>(9));

void print_board() {
    f0r(i, 9) {
        DEBUG(board[i]);
    }
}

void print_possible() {
    int counter = 0;
    f0r(i, 9) {
        f0r(j, 9) {
            cout << possible[i][j] << " | ";

            if (possible[i][j].size() == 1) {
                cout << "HERE j + 1:" << j + 1 << " ";
                counter++;
            }
        }
        cout << "endl i + 1:" << i + 1 << endl;
    }

    DEBUG(counter);
}

bool is_possible(int y, int x, int num) {
    // Check rows and columns
    f0r(i, 9) {
        if (board[i][x] == num) {
            return false;
        }

        if (board[y][i] == num) {
            return false;
        }
    }

    // Check square
    set<ll> square;
    int starting_x = (x/3) * 3;
    int starting_y = (y/3) * 3;
    f1r(i, starting_x, starting_x + 3) {
        f1r(j, starting_y, starting_y + 3) {
            square.insert(board[j][i]);
        }
    }

    if (square.count(num) > 0) {
        return false;
    }

    return true;
}

bool super_is_possible(int y, int x, int num) {
    // Check rows and columns
    f0r(i, 9) {
        if (board[i][x] == num) {
            return false;
        }

        for(int possibility: possible[i][x]) {
            if (possibility == num) {
                return false;
            }
        }

        if (board[y][i] == num) {
            return false;
        }

        for(int possibility: possible[y][i]) {
            if (possibility == num) {
                return false;
            }
        }
    }

    // Check square
    set<ll> square;
    int starting_x = (x/3) * 3;
    int starting_y = (y/3) * 3;
    f1r(i, starting_x, starting_x + 3) {
        f1r(j, starting_y, starting_y + 3) {
            square.insert(board[j][i]);
            for(int possibility: possible[j][i]) {
                square.insert(possibility);
            }
        }
    }

    if (square.count(num) > 0) {
        return false;
    }

    return true;
}

void manual_board_adjustment() {

}

int main() {
    io;

    f0r(i, 9) {
        f0r(j, 9) {
            cin >> board[i][j];
        }
    }

    manual_board_adjustment();

    print_board();

    // Layer 1 of possible
    f0r(i, 9) {
        f0r(j, 9) {
            if (board[i][j] != 0) {
                continue;
            }

            f1r(k, 1, 10) {
                if (is_possible(i, j, k)) {
                    possible[i][j].insert(k);
                }
            }
        }
    }

    print_possible();

    f0r(i, 9) {
        f0r(j, 9) {
            f0r(k, 9) {
                if (super_is_possible(j, i, k)) {
                    DEBUG(j, i, k);
                }
            }
        }
    }
}