#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = b; a >= c; a--)
#define pb push_back
#define f first
#define s second

#define mp make_pair
#define t third
#define pll pair<ll, ll>
#define pii pair<int, int>

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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

#include <chrono>
using namespace std::chrono;
struct timer {
    high_resolution_clock::time_point begin;

    timer() {}
    timer(bool b) {
        if (b) start();
    }

    void start() {
        begin = high_resolution_clock::now();
    }

    void print() {
        cout << "Time taken: " << duration_cast<duration<double>>(high_resolution_clock::now() - begin).count() << " seconds" << endl;
    }

    double report() {
        return duration_cast<duration<double>>(high_resolution_clock::now() - begin).count();
    }
};
// Start of main put tin, end of main put tpr (tgt gives you value not printed)
#define tin timer __timer__(1);
#define tpr __timer__.print();
#define tgt __timer__.report()

ll q, Q, T, k, l, r, x, y, z;
ll n, m;

void solve();

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

const ll MOD = 1e9 + 7;

void solve() {
    cin >> n;
    cin >> m;

    vector<int> inp(n);
    vector<int> num_balls(n);
    vector<int> loc; // loc[1] gives me location of the 2nd ball
    f0r(i, n) {
        cin >> inp[i];
        if (inp[i] == 1) {
            loc.pb(i);
        }
        num_balls[i] = loc.size();
    }

    vector<vector<vector<ll>>> dp(2, vector<vector<ll>>(loc.size() + 1, vector<ll>(m + 1)));
    dp[0][0][0] = 1;
    for (int i = 1; i < n + 1; i++) {
        // first i positions
        for (int j = max(0, num_balls[i - 1] - 70); j < min(i + 1, num_balls[i - 1] + 70, (int) loc.size() + 1); j++) {
            f0r(k, m + 1) {
                dp[i % 2][j][k] = dp[(i + 1) % 2][j][k];

                // i, j - 1, k - cost
                if (j > 0) {
                    int cost = abs(loc[j - 1] - i + 1); // 1-indexing because i being 1-indexed
                    if (k - cost >= 0) {
                        dp[(i % 2)][j][k] += dp[(i + 1) % 2][j - 1][k - cost];
                    }
                }

                dp[i % 2][j][k] %= MOD;
            }
        }
//        DEBUG(dp[i % 2]);
    }

    ll sum = 0;
    for (int k = 0; k < m + 1; k++) {
        if (k % 2 != m % 2) continue;

        sum += dp[n % 2][loc.size()][k];
    }

    sum %= MOD;

    cout << sum << endl;
}
