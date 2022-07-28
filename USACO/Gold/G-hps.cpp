#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, m, q, Q, T, k, l, r, x, y, z, g;

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=694 
int main() {
    usaco("hps");
    // io;

    cin >> n >> k;
    vector<char> input(n);
    f0r(i, n) {
        cin >> input[i];
    }

    // DP
    // x = which turn we're on, y = number of switches, 
    // z = currently hoof 0, paper 1, scissors 2
    // dp[x][y][z]
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(3, 0)));

    // Initialize first column n = 1 with 0s except for 1 on winning
    f0r(i, k + 1) {
        if (input[0] == 'H') {
            dp[0][i][1] = 1;
        } else if (input[0] == 'P') {
            dp[0][i][2] = 1;
        } else if (input[0] == 'S') {
            dp[0][i][0] = 1;
        }
    }

    // First column onwards keep going right
    f1r(i, 1, n) {
        // Manually do the first row, or no switches
        if (input[i] == 'H') {
            dp[i][0][1] = dp[i - 1][0][1] + 1;

            dp[i][0][0] = dp[i - 1][0][0];
            dp[i][0][2] = dp[i - 1][0][2];
        } else if (input[i] == 'P') {
            dp[i][0][2] = dp[i - 1][0][2] + 1;

            dp[i][0][0] = dp[i - 1][0][0];
            dp[i][0][1] = dp[i - 1][0][1];
        } else if (input[i] == 'S') {
            dp[i][0][0] = dp[i - 1][0][0] + 1;

            dp[i][0][1] = dp[i - 1][0][1];
            dp[i][0][2] = dp[i - 1][0][2];
        }
        
        f1r(j, 1, k + 1) {

            // J number of switches
            if (input[i] == 'H') {
                // max (previous most paper, previous most hoof - 1 switch (+ 1 since switching into paper), previous most scissors - 1 switch (+ 1 since switching into paper))
                dp[i][j][1] = max({dp[i - 1][j][1] + 1, dp[i - 1][j - 1][0] + 1, dp[i - 1][j - 1][2] + 1});

                dp[i][j][0] = dp[i - 1][j][0];
                dp[i][j][2] = dp[i - 1][j][2];
            } else if (input[i] == 'P') {
                dp[i][j][2] = max({dp[i - 1][j][2] + 1, dp[i - 1][j - 1][0] + 1, dp[i - 1][j - 1][1] + 1});

                dp[i][j][0] = dp[i - 1][j][0];
                dp[i][j][1] = dp[i - 1][j][1];
            } else if (input[i] == 'S') {
                dp[i][j][0] = max({dp[i - 1][j][0] + 1, dp[i - 1][j - 1][1] + 1, dp[i - 1][j - 1][2] + 1});

                dp[i][j][1] = dp[i - 1][j][1];
                dp[i][j][2] = dp[i - 1][j][2];
            }

        }
    }

    f0r(i, n) {
        DEBUG(dp[i]);
    }

    // Return the highest # in the most bottom right array for all ending positions
    // Which represents last turn and most number of switches made
    int ret = -1;
    f0r(i, 3) {
        ret = max(ret, dp[n - 1][k][i]);
    }
    cout << ret << endl;
}
