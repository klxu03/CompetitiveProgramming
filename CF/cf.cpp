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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// rng() gives a better random unsigned 32 bit number

void solve();

// Problem URL:
int main() {
    io;
//    usaco("f_cf");
    long long test_cases = 1;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class FindingBridges {
public:
    set<pii> bridges;
    set<int> bridge_nodes;
    void IS_BRIDGE(int v,int to) {
        bridges.insert({v, to});
        bridge_nodes.insert(v);
        bridge_nodes.insert(to);
    } // some function to process the found bridge

    int n; // number of nodes
    int m; // num edges
    vector<vector<int>> adj; // adjacency list of graph
    int num_visited;

    vector<bool> visited;
    vector<int> tin, low;
    int timer;

    vector<int> from;
    FindingBridges(int n) {
        this->n = n;
        num_visited = 0;
        adj = vector<vector<int>>(n);
//        visited = vector<bool>(n, false);
//        tin = vector<int>(n, -1);
//        low = vector<int>(n, -1);

        from = vector<int>(n, -1);
    }

    void init_adj() {
        f0r(i, m) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }
    }

    void dfs(int v, int p = -1) {
        visited[v] = true;
        num_visited++;
        tin[v] = low[v] = timer++;
        bool parent_skipped = false;
        for (int to : adj[v]) {
            if (to == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v]) {
                    IS_BRIDGE(v, to);
                }
            }
        }
    }

    void find_bridges() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
    }

    int bfs(int start) {
        // see how many nodes you can visit without crossing any bridge
        // return the number of nodes visited

        int ret = 0;

        deque<int> q;
        q.push_back(start);
        set<int> visited;
        visited.insert(start);
        from[start] = -1;

        while (!q.empty()) {
            int node = q.front();
            q.pop_front();
            ret++;

            for (int to : adj[node]) {
                if (visited.count(to) || bridges.count({node, to}) || bridges.count({to, node})) {
                    continue;
                }

                visited.insert(to);
                from[to] = node;
                q.push_back(to);
            }
        }

        return ret;
    }
};

int splitIntoTwoGroups(const std::vector<int>& nums) {
    int n = nums.size();
    int totalSum = std::accumulate(nums.begin(), nums.end(), 0);
    int halfSum = totalSum / 2;

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(halfSum + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = halfSum; j >= nums[i - 1]; --j) {
            dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        }
        for (int j = 0; j <= halfSum; ++j) {
            dp[i][j] = dp[i][j] || dp[i - 1][j];
        }
    }

    int group1Sum = 0;
    for (int j = halfSum; j >= 0; --j) {
        if (dp[n][j]) {
            group1Sum = j;
            break;
        }
    }

    std::vector<int> group1, group2;
    int w = group1Sum;
    for (int i = n; i > 0; --i) {
        if (!dp[i - 1][w]) {
            group1.push_back(nums[i - 1]);
            w -= nums[i - 1];
        } else {
            group2.push_back(nums[i - 1]);
        }
    }

    int group2Sum = totalSum - group1Sum;

    for (int num : group1) {
//        std::cout << num << " ";
    }

    for (int num : group2) {
//        std::cout << num << " ";
    }

    return group1Sum;
}

void solve() {
    int n, m;
    cin >> n >> m;

    FindingBridges fb(n);
    fb.m = m;
    fb.init_adj();

    fb.find_bridges();

    DEBUG(fb.bridges);

    vector<int> val;
    for (auto p : fb.bridge_nodes) {
        val.pb(fb.bfs(p));
//        DEBUG(fb.bfs(p));
    }

    int best = splitIntoTwoGroups(val);

    cout << ((n - best) * (n - best - 1) + best * (best - 1)) / 2 << "\n";
}
