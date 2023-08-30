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
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class Graph {
public:
    int nodes;
    vector<vector<int>> adj;
    vector<int> par; // parent of this node
    vector<int> leaves; // [ids]
    vector<int> depth;

    Graph() {}

    void init(int nodes) {
        this->nodes = nodes;
        par = vector<int>(nodes);
        depth = vector<int>(nodes);
    }

    void bfs() {
        deque<pii> dq;
        vector<bool> visited(nodes);
        dq.push_back({0, 1});
        visited[0] = true;
        par[0] = -1;

        while (!dq.empty()) {
            auto [curr, dist] = dq.front();
            DEBUG(curr, dist);
            dq.pop_front();

            for (int neigh : adj[curr]) {
                if (!visited[neigh]) {
                    dq.push_back({neigh, dist + 1});
                    visited[neigh] = true;
                    par[neigh] = curr;
                    depth[neigh] = dist + 1;
                }
            }

            // is a leaf
            if (adj[curr].size() == 1) {
                leaves.pb(curr);
            }
        }
    }
};

void solve() {
    cin >> n >> k;

    vector<vector<int>> adj(n);
    f0r(i, n - 1) {
        int a, b;
        cin >> a >> b;
        a--; b--;

        adj[a].pb(b);
        adj[b].pb(a);
    }

    Graph g;
    g.init(n);
    g.adj = adj;
    g.bfs();
    DEBUG("bfs finished", g.leaves);

    // ll next_gain, branch_len, num_occupied, node;
    multiset<array<ll, 4>> ms;
    for (int leaf : g.leaves) {
        DEBUG(leaf);
        ms.insert({g.depth[leaf] - 1, g.depth[leaf], 0, leaf});
    }
    DEBUG(ms);

    ll ret = 0;
    f0r(i, k) {
        array<ll, 4> curr = *(ms.rbegin());
        ms.erase(--ms.end());

        ret += curr[0];

        ll next_gain = curr[1] - (curr[2] + 1) - (curr[2] + 1);
        if (curr[2] + 1 < curr[1]) {
            ms.insert({next_gain, curr[1], curr[2] + 1, g.par[curr[3]]});
        }
        DEBUG(ms);
    }

    cout << ret << endl;
}
