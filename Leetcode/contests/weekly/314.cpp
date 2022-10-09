// Leetcode Weekly Contest 314
// Full solved 1:29:56 | 3 WA
// Rank: 1825
// https://leetcode.com/contest/weekly-contest-314/problems/paths-in-matrix-whose-sum-is-divisible-by-k/

#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "[";for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];}return cout << "]";}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        vector<vector<vector<int>>> dp = vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(k, 0)));
        // dp[row][col][k]

        // Do top row
        dp[0][0][grid[0][0] % k]++; // Set first one to 1
        f1r(i, 1, grid[0].size()) {
            int add = grid[0][i] % k;

            f0r(j, k) {
                dp[0][i][j] = dp[0][i - 1][(j - add + k) % k];
            }
        }

        // Do left column
        f1r(i, 1, grid.size()) {
            int add = grid[i][0] % k;

            f0r(j, k) {
                dp[i][0][j] = dp[i - 1][0][(j - add + k) % k];
            }
        }

        f1r(i, 1, grid.size()) {
            f1r(j, 1, grid[0].size()) {
                int add = grid[i][j] % k;

                f0r(i2, k) {
                    dp[i][j][i2] = dp[i - 1][j][(i2 - add + k) % k];
                    dp[i][j][i2] += dp[i][j - 1][(i2 - add + k) % k];
                    dp[i][j][i2] %= (int) 1e9 + 7;
                }
            }
        }

        return dp[grid.size() - 1][grid[0].size() - 1][0];
    }
};

int main() {
    Solution s;
    vector<vector<int>> sample = {{5, 2, 4}, {3, 0, 5}, {0, 7, 2}};
    s.numberOfPaths(sample, 3);
}