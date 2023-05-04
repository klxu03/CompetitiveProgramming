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

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve();

// Problem:
int main() {
    io;
    ll test_cases = 1;
    cin >> test_cases;

    f0r(test_case, test_cases) {
        solve();
    }
}

class DSU {
public:
    vector<int> c; // c for components

    DSU() {}

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
DSU d;

class UnweightedGraph {
public:
    long long nodes; // # of nodes
    long long edges; // # of edges
    bool undirected;
    vector<vector<long long> > adj; // adjacency neighbor vector
    vector<long long> visited; // visited nodes

    UnweightedGraph() {}
    vector<ll> indegree;
    vector<ll> s_indegree; // summed indegree, so a DP running sum of indegrees from previous ones

    void init(long long nodes, long long edges, bool undirected) {
        this->nodes = nodes;
        this->edges = edges;
        this->undirected = undirected;

        adj = vector<vector<long long> >(nodes);
        visited = vector<long long>(nodes, false);

        indegree = vector<ll>(nodes);
        s_indegree = vector<ll>(nodes);
    }

    void add_adj(int from, int to) {
        adj[from].pb(to);
        indegree[to]++;
    }

    // handle the super indegree for the nodes along the starting path
    // this handles cases of starting cycles by going backwards to a node along the path or other nodes that may make their way onto this path
    void toposort() {
        deque<long long> dq;

        for (int i = 0; i < nodes; i++) {
            if (indegree[i] == 0) {
                dq.pb(i);
            }
        }

        while(!dq.empty()) {
            long long current = dq.front();
            dq.pop_front();

            for (long long neighbor : adj[current]) {
                indegree[neighbor]--;
                s_indegree[neighbor] += s_indegree[current] + 1;

                if (indegree[neighbor] == 0) {
                    dq.push_back(neighbor);
                }
            }
        }
    }
};
UnweightedGraph g;

vector<int> inp;

void fill_d(int start) {
    int curr = start;
    while (true) {
        int diff = inp[curr];
        if (diff == 0) break; // no hop, done infinite loop
        if (curr + diff < 0 || curr + diff >= n) break; // done, broke out of 0 - (n - 1)
        if (d.same_set(curr + diff, curr)) break; // done, repeating a loop back to same set
        d.unite(curr, curr + diff);
        g.add_adj(curr, curr + diff);
        curr += diff;
    }
}

vector<bool> visited;
// determine if this start node ends up infinite looping or exiting
int determine_end(int start) {
    int curr = start;
    visited[start] = true;
    while (true) {
        int diff = inp[curr];
        if (curr + diff < 0 || curr + diff >= n) return 1; // done, broke out of 0 - (n - 1)
        curr += diff;
        if (visited[curr]) return -1; // already visited before, looping back
        visited[curr] = true;
    }
}


vector<bool> og_path;
void get_og_path() {
    int curr = 0;
    og_path[curr] = true;
    while (true) {
        curr += inp[curr];
        if (curr < 0 || curr >= n) break; // out of bounds, reached the end
        if (og_path[curr]) break;
        og_path[curr] = true;
    }
}

ll num_exits; // the number of indices that exit naturally

void solve() {
    cin >> n;
    inp = vector<int>(n);
    visited = vector<bool>(n);
    og_path = vector<bool>(n);
    num_exits = 0;
    d.init(n);
    DEBUG(inp, visited, og_path, num_exits, d.c, g.adj);
    g.init(n, 0, false);

    f0r(i, n) {
        cin >> inp[i];
    }
    DEBUG(n, inp);

    // init the dsu
    f0r(i, n) {
        if (d.size(i) == 1) {
            fill_d(i);
        }
    }
    g.toposort();

    map<int, int> m; // map of group to status. [-1 if infinite loop, 1 if exits, 2 if unit]
    f0r(i, n) {
        m[d.get(i)] = 2;
    }

    DEBUG(m);
    for (auto p : m) {
        m[p.f] = determine_end(p.f);
        if (m[p.f] == 1) num_exits += d.size(p.f);
    }
    fill(visited.begin(), visited.end(), false);

    ll ret = 0;
    get_og_path();
    bool initial_exits = m[d.get(0)] == 1;

    // handle the og_path first
    f0r(i, n) {
        // initial one can point to any index that exits and go out of bounds n + 1 itself
        // ^ this one gets handled naturally from the bottom stuff

        // every point along the initial path can point to a node that exits (except going backwards along the path since that creates a new cycle) or n + 1 out itself
        // do some math. if there are 5 nodes along this path, then the first one gets 4 choices forward, next one is 3, then 2, then 1, or like 4(4 + 1)/2. This math doesn't include other nodes not connected on the path that exit naturally or the n + 1 options of exiting
        // actually this math should just be turned into super indegree from the graph g

        if (og_path[i]) {
            ret += n + 1 + num_exits;
            if (initial_exits) {
                ret -= 1 + g.s_indegree[i];
            }
            DEBUG(num_exits, g.s_indegree[i]);
            DEBUG(i, ret);
        }
    }

    // if initial one exits by itself every other index that is not directly on the path of the initial one can visit any 2 * n + 1 node
    if (initial_exits) {
        DEBUG("og exits");
        f0r(i, n) {
            if (og_path[i] == false) {
                ret += 2 * n + 1;
                DEBUG(i, ret);
            }
        }
    }

    cout << ret << endl;
}
