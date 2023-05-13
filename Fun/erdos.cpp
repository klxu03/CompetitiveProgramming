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
//    io;
    long long test_cases = 1;
//    usaco("erdos");
    usaco("break");
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class UnweightedGraph {
public:
    long long nodes; // # of nodes
    bool undirected;
    vector<vector<int> > adj; // adjacency neighbor vector

    UnweightedGraph() {}

    void init(long long nodes, bool undirected) {
        this->nodes = nodes;
        this->undirected = undirected;
    }

    vector<int> even_cycle(int start, int len) {
        vector<bool> visited(nodes);
        deque<pii> dq; // {node, dist}
        dq.pb({start, 0});
        visited[start] = true;
        vector<int> prev(nodes, -2);
        vector<int> leaves; // nodes that are exactly (n - 1)/2 nodes away

        while(!dq.empty()) {
            int curr, dist;
            tie(curr, dist) = dq.front();
            dq.pop_front();

            if (dist + 1 >= len/2) break;

            for (int neighbor : adj[curr]) {
                if (visited[neighbor]) continue;
                visited[neighbor] = true;
                dq.pb({neighbor, dist + 1});
                prev[neighbor] = curr;
                if (dist + 1 == len/2 - 1) leaves.pb(neighbor);
            }
        }

        // now see if any leaves match a common child
        array<int, 3> path = {-1, -1, -1};
        set<int> s;
        for (int curr : leaves) {
            for (int neighbor : adj[curr]) {
                if (visited[neighbor]) continue;
                if (s.count(neighbor) == 1) path = {curr, neighbor, prev[neighbor]};
                s.insert(neighbor);
                prev[neighbor] = curr;
            }
        }

        if (path[0] == -1) return {-1};

        vector<int> ret(len);
        ret[len/2] = path[1];
        int curr = path[0];
        for (int i = len/2 - 1; i >= 0; i--) {
            ret[i] = curr;
            curr = prev[curr];
        }

        curr = path[2];
        f1r(i, len/2 + 1, len) {
            ret[i] = curr;
            curr = prev[curr];
        }

        return ret;
    }

    vector<int> odd_cycle(int start, int len) {
        vector<bool> visited(nodes);
        deque<pii> dq; // {node, dist}
        dq.pb({start, 0});
        visited[start] = true;
        vector<int> prev(nodes, -2);
        set<int> leaves; // nodes that are exactly (n - 1)/2 nodes away

        while(!dq.empty()) {
            int curr, dist;
            tie(curr, dist) = dq.front();
            dq.pop_front();

            if (dist + 1 > len/2) break;

            for (int neighbor : adj[curr]) {
                if (visited[neighbor]) continue;
                visited[neighbor] = true;
                dq.pb({neighbor, dist + 1});
                prev[neighbor] = curr;
                if (dist + 1 == len/2) leaves.insert(neighbor);
            }
        }

        // now see if any leaves match a common child
        array<int, 2> path = {-1, -1};
        for (int curr : leaves) {
            for (int neighbor : adj[curr]) {
                if (leaves.count(neighbor) == 1) {
                    DEBUG(curr, neighbor);
                    path[0] = curr;
                    path[1] = neighbor;
                }
            }
        }

        if (path[0] == -1) return {-1};

        vector<int> ret(len);
        int curr = path[0];
        DEBUG(path);
        for (int i = len/2; i >= 0; i--) {
            ret[i] = curr;
            curr = prev[curr];
        }

        curr = path[1];
        f1r(i, len/2 + 1, len) {
            ret[i] = curr;
            curr = prev[curr];
        }

        return ret;
    }

    // returns a vector of the path of the cycle at the start node of length len
    // returns a vector with one element {-1} if no cycle was found
    vector<int> cycle(int start, int len) {
        if (len % 2 == 0) {
            return even_cycle(start, len);
        } else {
            return odd_cycle(start, len);
        }
    }
};
UnweightedGraph g;

void handle_input(int type) {
    cin >> n;
    vector<vector<int>> adj(n);

    switch(type) {
        case 0:
            cin >> m;
            g.init(n, true);
            f0r(i, m) {
                int x, y;
                cin >> x >> y;
                adj[x].pb(y);
                adj[y].pb(x);
            }
            g.adj = adj;

            break;
        case 1:
            g.init(n, true);
            int inp;
            f0r(i, n) {
                f0r(j, n) {
                    cin >> inp;
                    if (inp) adj[i].pb(j);
                }
            }
            g.adj = adj;
            break;
        default:
            cerr << "Invalid input" << endl;
            break;
    }
}

void solve() {
    int type; // type of input, {edges, full adj matrix}
    cin >> type;
    /*
     * Assume for type 0 input that each edge is given with 0-indexed node values in the edge and don't give 0 1, 1 0 assume only one
     */
    handle_input(type);
    vector<int> cycles_exist;
    f1r(len, 3, n + 1) {
        f0r(start, n) {
            if (g.cycle(start, len)[0] != -1) {
                DEBUG(len, start, g.cycle(start, len));
                cycles_exist.pb(len);
                break;
            }
        }
    }

    DEBUG(cycles_exist.size() + 2); // + 2 since obviously no cycles of length 1 and 2 (or there are)
    DEBUG(cycles_exist);
    cout << cycles_exist.size() << endl;
}
