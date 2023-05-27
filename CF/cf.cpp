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

class UnweightedGraph {
public:
    long long nodes; // # of nodes
    long long edges; // # of edges
    bool undirected;
    vector<vector<ll>> adj; // adjacency neighbor vector
    vector<long long> visited; // visited nodes

    UnweightedGraph() {}

    void init(long long nodes, long long edges, bool undirected) {
        this->nodes = nodes;
        this->edges = edges;
        this->undirected = undirected;
        adj = vector<vector<ll>>(nodes);
        visited = vector<long long>(nodes, false);
    }

    int get(ll node, ll dist) {
        visited[node] = true;
        if (dist == 0) return node;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) return get(neighbor, dist - 1);
        }
        return -1;
    }

    // get node from a starting_node and the node that is dist away
    int get_node(long long start_node, ll start_dist) {
        if (start_dist == 0) return start_node;
        fill(visited.begin(), visited.end(), false);

        return get(start_node, start_dist);
    }
};

UnweightedGraph g;

void solve() {
    cin >> n;
    ll res;

    // handle n == 2 case
    if (n == 2) {
        cout << "! 1 2 2 1" << endl;
        cout.flush();
        cin >> res;
        return;
    }

    cout << "+ " << n + 1 << endl;
    cout.flush();
    cin >> res;
    if (res == -2) return;

    cout << "+ " << n + 2 << endl;
    cout.flush();
    cin >> res;
    if (res == -2) return;

    // let's build the graph now
    g.init(n, -1, true);
    int s = 0; // start
    int t = n - 1; // end
    f0r(i, n/2) {
        g.adj[s].pb(t);
        g.adj[t].pb(s);
        s++;
        g.adj[t].pb(s);
        g.adj[s].pb(t);
        t--;
    }
    DEBUG(g.adj);
    DEBUG("fix this case at the end with 4 self-loop is n = 6, or some weird behavior possiblye n = 7 or right");

    // go ahead and clear the "other" end point, and then manually set its neighbor
    if (n % 2 == 0) {
        g.adj[n/2] = {n/2 - 1};
    }
    DEBUG("final", g.adj);

    vector<ll> dist0(n, 0); // distance of every node from 0
    dist0[0] = 0;
    pii furthest = {0, 0}; // {distance, node number (0 indexed)}

    // get dist0
    f1r(i, 1, n) {
        cout << "? " << 1 << " " << i + 1 << endl;
        cout.flush();
        cin >> res;
        if (res == -2) return;
        dist0[i] = res;

        if (res > furthest.f) {
            furthest = {res, i};
        }
    }
    DEBUG(dist0);
    DEBUG(furthest);

    /* this is actually not important */
    // figure out which possible node i == 0 is
    // this is based on max distance from one of the ends

    vector<ll> dist(n, 0);
    dist[0] = dist0[furthest.s];
    f1r(i, 1, n) {
        if (i == furthest.s) continue;

        cout << "? " << furthest.s + 1 << " " << i + 1 << endl;
        cout.flush();
        cin >> res;
        if (res == -2) return;
        dist[i] = res;
    }
    DEBUG(dist);

    // ends (1-indexed) being 1 and n/2 + 1
    vector<int> ret(n * 2);

    int end = 0;
    DEBUG(end);
    // assuming end is 1
    f0r(i, n) {
        ret[i] = g.get_node(end, dist[i]) + 1;
    }
    DEBUG(ret);

    end = n/2;
    DEBUG(end);
    f0r(i, n) {
        ret[i + n] = g.get_node(end, dist[i]) + 1;
    }
    DEBUG(ret);

    cout << "! ";
    f0r(i, 2 * n) {
        cout << ret[i] << " ";
    }
    cout << endl;
    cout.flush();

    cin >> res;
    if (res == -2) return;
}
