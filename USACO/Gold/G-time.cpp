#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "[";for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];}return cout << "]";}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll n, m, c;
vector<vector<ll> > adj; // adjacency neighbor vector

void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

int main() {
    usaco("time");
    // io;
    cin >> n >> m >> c;
    vector<int> val(n, 0); // value of mooney each city
    f0r(i, n) {
        cin >> val[i];
    }
    DEBUG(val);

    adj = vector<vector<ll>>(n);
    f0r(i, m) {
        int from, to;
        cin >> from >> to;
        from--; to--; // one index
        adj[from].pb(to);
    }

    vector<vector<ll>> dp(n, vector<ll>(1001, -1));
    dp[0][0] = 0;
    // iterate through the different Ts except last one 1000 as from 999 you progress forward to 1000
    f0r(j, 1000) {
        // iterate through each node going down
        f0r(i, n) {
            if (dp[i][j] != -1) {
            DEBUG(i, adj[i]);
                f0r(k, adj[i].size()) {
                    DEBUG(adj[i][k]);
                    if (dp[i][j] + val[adj[i][k]] > dp[adj[i][k]][j + 1]) {
                        dp[adj[i][k]][j + 1] = dp[i][j] + val[adj[i][k]];
                    }
                }
            }
        }
    }

    ll ret = -1;
    f0r(i, 1001) {
        ret = max(ret, dp[0][i] - c * i * i);
    }

    cout << ret << endl;
}