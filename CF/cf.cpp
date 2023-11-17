#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// rng() gives a better random unsigned 32 bit number

ll q, Q, T, k, l, r, x, y, z;
int n, m;

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

vector<vector<int>> adj;
vector<vector<int>> from;
map<int, int> d;

void bfs(vector<int> &dist) {
    deque<int> dq;
    dq.pb(0);
    dist[0] = 0;

    while (!dq.empty()) {
        int curr = dq.front();
        dq.pop_front();

        for (int i : adj[curr]) {
            if (dist[i] == INT_MAX) {
                dist[i] = dist[curr] + 1;
                dq.push_back(i);
            }
        }
    }
}

// do layer 1
void layer1(vector<int> &dp) {
    set<pair<int, int>> s; // dist, node id
    for (int i = 0; i < n; i++) {
        s.insert({dp[i], i});
    }

    while (!s.empty()) {
        auto curr = *s.begin();
        s.erase(s.begin());
        if (d[curr.f] > d[dp[curr.s]]) continue; // out of date

        for (int i : from[curr.s]) {
            // i -> curr since push DP
            if (d[i] >= d[curr.s]) continue; // do not do action 2

            if (curr.f < dp[i]) {
                dp[i] = curr.f;
                s.insert({curr.f, i});
            }
        }
    }
}

// try to get the best 1-score based on 0-score of adj nodes
void layer2(vector<vector<int>>& dp) {
    for (int i = 0; i < n; i++) {
        for (int neigh : adj[i]) {
            // i -> neigh
            if (d[i] >= d[neigh]) {
                dp[1][neigh] = min(dp[1][neigh], dp[0][i]);
            }
        }
    }
}

void layer3(vector<vector<int>> &dp) {
    set<pair<int, int>> s; // 1-score, node id
    for (int i = 0; i < n; i++) {
        s.insert({dp[1][i], i});
    }

    while (!s.empty()) {
        auto curr = *s.begin();
        DEBUG(curr);
        s.erase(s.begin());
        if (curr.f > dp[1][curr.s]) continue; // out of date

        for (int i : from[curr.s]) {
            // i -> curr since push DP
            DEBUG(i, curr.s);
            if (d[i] < d[curr.s]) { // action 1
                if (curr.f < dp[1][i]) {
                    dp[1][i] = curr.f;
                    s.insert({curr.f, i});
                }
            } else { //action 2
                if (dp[0][curr.s] < dp[1][i]) {
                    dp[1][i] = dp[0][curr.s];
                    s.insert({dp[0][curr.s], i});
                }
            }
        }
    }
}

void solve() {
    cin >> n >> m;

    adj = vector<vector<int>>(n);
    from = vector<vector<int>>(n);
    d.clear();
    f0r(i, m) {
        int x, y;
        cin >> x >> y;
        x--; y--;

        adj[x].pb(y);  
        from[y].pb(x);  
    }
    
    vector<vector<int>> dp(2, vector<int>(n, INT_MAX)); // dp[0] is 0-score, dp[1] is 1-score
    bfs(dp[0]);
    f0r(i, n) {
        d[i] = dp[0][i];
    }

    DEBUG("bfs", dp[0]);
    layer1(dp[0]);
    DEBUG("l1", dp[0]);
    layer2(dp);
    DEBUG("l2", dp[1]);
    dp[1][0] = 0;
    layer3(dp);
    DEBUG("l3", dp);

    f0r(i, n) {
        cout << min(dp[0][i], dp[1][i]) << " ";
    }
    cout << endl;
}