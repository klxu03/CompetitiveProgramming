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

const int MAX_PRIMES = 1415;
vector<int> num_nodes(MAX_PRIMES + 1); // 1-index it
const int MAX_VALUE = 3e5;
vector<int> lp(MAX_VALUE + 1);
vector<int> primes_map;

void init_primes() {
    for (int i = 2; i <= 3e5; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes_map.push_back(i);
        }

        for (int j = 0; i * primes_map[j] <= MAX_VALUE; j++) {
            lp[i * primes_map[j]] = primes_map[j];
            if (primes_map[j] == lp[i]) {
                break;
            }
        }
    }

    primes_map.insert(primes_map.begin(), 1);
}

// Problem URL:
int main() {
    io;
//    usaco("f_cf");
    long long test_cases = 1;
    cin >> test_cases;
    init_primes();

    for (int i = 1; i <= MAX_PRIMES; i++) {
        if (i & 1) {
            // odd case
            num_nodes[i] = i * (i - 1)/2 + i + 1;
        } else {
            // even case
            num_nodes[i] = i * (i - 1)/2 - (i/2 - 1) + i + 1;
        }
    }

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class Graph {
public:
    int nodes;
    vector<set<int>> edges;

    Graph() {}

    void init() {
        edges = vector<set<int>>(nodes);
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                edges[i].insert(j);
            }
        }

        if (!(nodes & 1)) {
            // even case, need to delete some edges
            for (int i = 1; i < nodes - 2; i++) {
                edges[i].erase(i + 1);
                edges[i + 1].erase(i);
                i++;
            }
        }
    }

    vector<int> run() {
        vector<int> ret;
        deque<int> dq;
        dq.pb(0);

        while (!dq.empty()) {
            int curr = dq.back();
            if (edges[curr].empty()) {
                ret.pb(curr);
                dq.pop_back();
                continue;
            }

            int other = *edges[curr].begin();
            edges[curr].erase(other);
            edges[other].erase(curr);
            dq.pb(other);
        }

        return ret;
    }
};

void solve() {
    cin >> n;

    int l = 0;
    int r = MAX_PRIMES + 1;

    // find the leftmost index such that num_nodes[i] >= n
    while (l < r) {
        int mid = (l + r)/2;
        if (num_nodes[mid] < n) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    Graph g;
    g.nodes = l;
    g.init();

    vector<int> paths = g.run();
    for (int i = 0; i < n; i++) {
        cout << primes_map[paths[i]] << " ";
    }
    cout << "\n";
}
