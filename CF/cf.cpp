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
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

string s;

void solve() {
    cin >> s;
    n = s.size();

    vector<array<ll, 6>> v(n, {LLONG_MIN, LLONG_MIN, LLONG_MIN, LLONG_MIN, LLONG_MIN, LLONG_MIN}); // prefix, new swap to these 5, standing best 5 with the max being this letter
    f0r(i, n) {
        f0r(j, 6) {
            v[i][j] = LLONG_MIN + 2e9;
        }
    }
    int mx;
    array<ll, 5> val = {1, 10, 100, 1000, 10000};

    // do the first row
    {
        int curr = s[n - 1] - 'A';
        mx = curr;

        v[n - 1][0] = val[curr];
        f0r(i, 5) {
            v[n - 1][i + 1] = val[i];
        }
        DEBUG(v[n - 1]);
    }

    for (int i = n - 2; i >= 0; i--) {
        int curr = s[i] - 'A';

        // update the prefix
        if (curr >= mx) {
            v[i][0] = v[i + 1][0] + val[curr];
        } else {
            v[i][0] = v[i + 1][0] - val[curr];
        }

        // update new
        f0r(j, 5) {
            if (curr > j) {
                // need to bring curr letter down

                // if already brought a previous letter down to reach this point, continue impossible
                if (mx > j) continue;

                v[i][j + 1] = v[i + 1][0] + val[j];
                // I don't care about previous value max since I need to use my letter swap right now
            } else if (j == curr) {
                // just use previous row's max for this letter and previous letters and add current, greedily optimal decision
                f0r(k, curr + 1) {
                    v[i][j + 1] = max(v[i][j + 1], v[i + 1][k + 1] + val[curr]);
                }
            } else { // curr < j
                // I can either change current letter bringing value up OR use previous max at this letter and subtract

                // to bring letter up, I need to first make sure I haven't needed to previously bring a letter down to maintain this max
                if (mx <= j) {
                    v[i][j + 1] = v[i + 1][0] + val[j];
                }
                // compare this value to the previous max and subtracting
                // if I've needed to previously bring a letter down to bring this letter up, then answer is just previous answer subtracting curr
                if (v[i + 1][j + 1] != LLONG_MIN) {
                    v[i][j + 1] = max(v[i][j + 1], v[i + 1][j + 1] - val[curr]);
                }
            }
        }

        DEBUG(v[i]);
        mx = max(mx, curr);
    }

    ll ret = LLONG_MIN;
    f0r(i, 5) {
        ret = max(ret, v[0][1 + i]);
    }

    cout << ret << endl;
}
