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


#ifdef galen_colin_local
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

const unsigned int sz = 2e5;
//const unsigned int sz = 11;

class UnweightedGraph {
public:
    long long nodes; // # of nodes
    long long edges; // # of edges
    bool undirected;
    vector<vector<long long> > adj; // adjacency neighbor vector

    ll global_min;
    vector<int> global_visited; // constantly storing one's min distance to another black node

    UnweightedGraph() {}

    void init(long long nodes, long long edges, bool undirected) {
        this->nodes = nodes;
        this->edges = edges;
        this->undirected = undirected;
        adj = vector<vector<long long> >(nodes);
        global_visited = vector<int>(nodes, 2 * 1e5 + 7);

        global_min = 2 * 1e5 + 7;
    }

    void init_adj() {
        f0r(i, edges) {
            ll n1, n2; // n1 for node1
            cin >> n1 >> n2;
            adj[n1 - 1].pb(n2 - 1);
            if(undirected) {
                adj[n2 - 1].pb(n1 - 1);
            }
        }
    }

    void init_global_visited(int start) {
        deque<int> dq;
        dq.push_back(start);
        global_visited[start] = 0;

        while (!dq.empty()) {
            int curr = dq.front();
            dq.pop_front();

            for (int neighbor : adj[curr]) {
                if (global_visited[neighbor] == 2 * 1e5 + 7) {
                    global_visited[neighbor] = global_visited[curr] + 1;
                    dq.push_back(neighbor);
                }
            }
        }

        // DEBUG(global_visited);
    }

    void black(int node) {
        deque<pair<int, int>> dq; // other node, current node distance
        dq.push_back({node, 0});

        global_visited[node] = 0;

//        set<int> visited;
//        visited.insert(node);

//        vector<bool> visited(n);
//        visited[node] = true;

        bitset<sz> bs;
        bs.set(node);

        while(!dq.empty()) {
            pii current = dq.front();
            dq.pop_front();

            if (current.s >= global_min) {
                break;
            }

            for (int neighbor : adj[current.f]) {
//                if (!visited[neighbor]) {
                if (!(bs[neighbor])) {
                    bs.set(neighbor);
//                    visited[neighbor] = true;
                    global_min = min(global_min, (ll)global_visited[neighbor] + current.s + 1);
                    if (current.s + 1 < global_visited[neighbor]) {
                        // DEBUG(current, neighbor, global_visited[neighbor], global_min);
                        dq.pb({neighbor, current.s + 1});
                    }
                    global_visited[neighbor] = min(global_visited[neighbor], current.s + 1);
                }
            }
        }

        // DEBUG(global_visited, global_min);
    }
};

UnweightedGraph g;

void solve() {
    int init;
    cin >> n >> init;
    init--;

    vector<int> colors(n - 1); // coloring order
    f0r(i, n - 1) {
        cin >> colors[i];
        colors[i]--;
    }

    g.init(n, n - 1, true);
    g.init_adj();
    g.init_global_visited(init);

    f0r(i, n - 1) {
        g.black(colors[i]);
        cout << g.global_min << " ";
    }
    cout << endl;
}