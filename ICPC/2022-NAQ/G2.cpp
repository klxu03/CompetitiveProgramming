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

class DSU {
    public:
    vector<int> c; // c for components

    DSU() {
    }

    void init(int n) {
        c = vector<int>(n, -1);
    }

    // get representive component (uses path compression)
	int get(int x) { 
        return c[x] < 0 ? x : c[x] = get(c[x]); 
    }

    bool same_set(int a, int b) { 
        return get(a) == get(b); 
    }

    int size(int x) { 
        return -c[get(x)]; 
    }

    bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false; // same group
		if (c[x] > c[y]) swap(x, y); // if c[x] is less negative, or greater than c[y]
		
        c[x] += c[y]; 
        c[y] = x;
		return true;
	}
};

DSU groups;

vector<int> adj;
vector<int> visited;

vector<int> cycles; // include one node in a cycle

void dfs(int node, int group) {
    int neighbor = adj[node];
    visited[node] = group;

    if (visited[neighbor] == -1) {
        dfs(neighbor, group);
    } else if (visited[neighbor] == group) {
        // cycle found
        cycles.pb(neighbor);
    } else {
        groups.unite(group, visited[neighbor]);
    }
}

vector<bool> cyc_visited;
int get_cyc_len(int node, int sz) {
    int neighbor = adj[node];
    cyc_visited[node] = true;

    if (cyc_visited[neighbor]) {
        return sz;
    } else {
        return get_cyc_len(neighbor, sz + 1);
    }
}

map<int, int> cyc_len; // key group, val is cycle length
map<int, int> group_sz; // key group, val is size
const ll modulo = 1e9 + 7;

void solve() {
	cin >> n;

    adj = vector<int>(n);
    visited = vector<int>(n, -1);
    cyc_visited = vector<bool>(n, false);
    groups.init(n);

    f0r(i, n) {
        int inp;
        cin >> inp;
        adj[i] = inp - 1;
    }

    int curr_group = 0;
    f0r(i, n) {
        if (visited[i] == -1) {
            dfs(i, curr_group);
            curr_group++;
        }
    }

    f0r(i, n) {
        visited[i] = groups.get(visited[i]);
        group_sz[visited[i]]++;
    }

    DEBUG(visited);
    DEBUG(cycles);

    for (int i : cycles) {
        cyc_len[groups.get(visited[i])] = get_cyc_len(i, 1);
    }

    DEBUG(cyc_len);

    ll ret = 1;
    for (int i : cycles) {
        int group = groups.get(visited[i]);

        ll multiple = group_sz[group] - cyc_len[group] + 2;
        DEBUG(group, group_sz[group], cyc_len[group]);
        ret = (ret * multiple) % modulo;
    }

    if (ret == 0) {
        cout << modulo - 1 << endl;
    } else {
        cout << ret - 1 << endl;
    }
}