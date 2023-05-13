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

ll q, Q, T, k, l, r, x, y, z;
ll n, m;

void solve(); 

// Problem URL: 
int main() {
    // io;
    usaco("fencedin");
    long long test_cases = 1;
    // cin >> test_cases;
	
    for (int i = 0; i < test_cases; i++) {
		solve();
    }
}

class Dsu {
    public:
    vector<long long> c; // c for components; indexed nodes with corresponding pointer to parent node; if root, then stores size as a negative value

    Dsu() {}

    void init(long long n) {
        c = vector<ll>(n, -1);
    }

    long long root(long long p) {
        return c[p] < 0 ? p : c[p] = root(c[p]); // recursively find root and set root as pointer for all children
    }

    bool connected(long long p, long long q) {
        return root(p) == root(q);
    } 

    ll size(ll p) {
        return -c[root(p)]; // if this does not work, multiply it by -1
    }
    
    bool unioned(long long p, long long q) {
        ll rp = root(p);
        ll rq = root(q);

        if (rp == rq) return false; // already the same component 
        
        if (c[rp] > c[rq]) swap(rp, rq); // when rp is smaller in size than rq
        c[rp] += c[rq];
        c[rq] = rp;
        return true;
    }
};

Dsu g;

void solve() {
    ll A; ll B;
    cin >> A >> B >> n >> m;
    vector<array<int, 3>> edge;
    vector<int> col(2 + n);
    vector<int> row(2 + m);

    f0r(i, n) {
        cin >> col[i];
    }
    col[n] = 0;
    col[n + 1] = A;

    f0r(i, m) {
        cin >> row[i];
    }
    row[m] = 0;
    row[m + 1] = B;

    sort(col.begin(), col.end());
    sort(row.begin(), row.end());

    // add vertical edges
    f0r(i, m + 1) {
        f0r(j, n) {
            edge.pb({(row[i + 1] - row[i]), j + ((n + 1) * i), j + 1 + ((n + 1) * i)});
        }
    }

    // add horizontal edges
    f0r(i, n + 1) {
        f0r(j, m) {
            edge.pb({(col[i + 1] - col[i]), i + j * (n + 1), i + (j + 1) * (n + 1)});
        }
    }

    // min sort the edges
    sort(edge.begin(), edge.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[0] < b[0];
    });

    // implement DSU to see if all the cows are connected to their proper place
    g.init((m + 1) * (n + 1));

    // traverse to to see if each region is connected to next region; if not, add the smallest edge; 
    // keep a counter to know where the current smallest edge is
    ll ret = 0;
    int counter = 0;
    ll sz = (m + 1) * (n + 1) - 1;

    f0r(i, edge.size()) {
        if(g.unioned(edge[i][1], edge[i][2])) {
            ret += edge[i][0];
            counter++;
            
            if(counter == sz) {
                break;
            }
        }
    }

    cout << ret << endl;
}