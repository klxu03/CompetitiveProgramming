#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define pb push_back
#define f first
#define s second
using ll = long long;

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
	// cin >> test_cases;
	
    for (int i = 0; i < test_cases; i++) {
		solve();
    }
}

vector<int> adj; 
vector<vector<int>> inc; // a list of incoming edges

vector<int> previ; // the prev of each node
// return a vector of all the nodes in a cycle to be compressed
vector<int> dfs_cycle(int node, vector<bool> &visited) {
    vector<int> ret;

    set<int> curr_visited; // in this specific visited, curr_visited
    curr_visited.insert(node);

    int neighbor = adj[node];
    visited[node] = true;

    while (!visited[neighbor]) {
        previ[neighbor] = node;
        visited[neighbor] = true;
        curr_visited.insert(neighbor);

        node = neighbor;
        neighbor = adj[neighbor];
    }

    // node: d
    // neig: b
    // curr_visited: [b, c, d, ]

    // distinguish from b -> c -> d -> b cycle to
    // e -> b, b already visited but not in curr_visited
    // check if the last node's neighbor, first being b second being b
    if (curr_visited.count(neighbor) == 0) {
        // latter half
        return ret;
    }

    // add d, node = c. add c, node = b
    while(node != neighbor) {
        ret.pb(node);
        node = previ[node];
    }
    ret.pb(neighbor);
    reverse(ret.begin(), ret.end()); // unnecessary, but just so it's in order

    return ret;
}

// given a vector of nodes that are a cycle, compress them in reference to adj and inc vectors
void compress_nodes(vector<int> & nodes) {
    // aggregate the inc array
    for (int i = 1; i < nodes.size(); i++) {
        for (int node : inc[nodes[i]]) {
            inc[nodes[0]].push_back(node);
            inc[nodes[i]] = {}; // no more incoming for this other cycle
            adj[node] = nodes[0];
        }
    }
}

// go ahead and compress all cycles in this forest
void compress_cycle() {
    vector<bool> visited(n, false);

    previ = vector<int>(n, -1);

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;

        vector<int> res = dfs_cycle(i, visited);
        compress_nodes(res);
    }
}

void solve() {
	cin >> n;
    adj = vector<int>(n);
    inc = vector<vector<int>>(n);

    int neighbor;
    f0r(i, n) {
        cin >> neighbor;
        inc[neighbor - 1].pb(i);
        adj[i] = neighbor - 1;
    }

    compress_cycle();
}