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
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>

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

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

vector<vector<ll>> adj;
vector<vector<ll>> ret;

void solve() {
	cin >> n >> m;
    ret = vector<vector<ll>>(n, vector<ll>(n, INT_MAX));

    /* n^2 preprocessing of adj matrix @ t = 0 */
    DEBUG("start preprocessing");
    adj = vector<vector<ll>>(n, vector<ll>(n, INT_MAX - 5));

    vector<vector<int>> inp(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        inp[i] = {a, b, c};
    }

    sort(inp.begin(), inp.end());

    vector<pair<int, int>> min_start(n, {-1, INT_MAX - 5}); // min_start[2] = {1, 3} means cheapest cost of 3 is city 2 point to city 1
    int n_counter = 0;
    for (int i = 0; i < m; i++) {
        adj[inp[i][0]][inp[i][1]] = inp[i][2];
        if (inp[i][2] < min_start[inp[i][0]].second) {
            min_start[inp[i][0]] = {inp[i][1], inp[i][2]};
        }
    }
    DEBUG(min_start);

    DEBUG("adj 1");
    f0r(i, n) {
        DEBUG(adj[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int curr_j = (min_start[i].first + j) % n;
            adj[i][curr_j] = min(adj[i][(curr_j - 1 + n) % n] + 1, adj[i][curr_j]);
        }
    }

    DEBUG("finished preprocessing");
    DEBUG("adj end");
    f0r(i, n) {
        DEBUG(adj[i]);
    }
    /* pre-processing of adj @ t = 0 done */

    // later wrap start in a for loop 
    f0r(start, n) {
        DEBUG(start);
        ret[start][start] = 0;
        vector<bool> visited(n, false);

        // stuff that doesn't persist, starts new loop every next_start
        ll time = 0;
        int next_start = start; // next for loop in v * v, for v^2

        f0r(v, n) {
            // fill out ret[start]
            visited[next_start] = true;
            f0r(i, n) {
                ret[start][i] = min(ret[start][i], time + adj[next_start][(((i - time + n) % n) + n) % n]);
            }

            // find next start
            time = INT_MAX;
            f0r(i, n) {
                if (!visited[i] && ret[start][i] < time) {
                    time = ret[start][i];
                    next_start = i;
                }
            }
        }

        DEBUG("ret");

        f0r(i, n) {
            DEBUG(ret[i]);
        }
    }

    DEBUG("output");
    f0r(i, n) {
        f0r(j, n) {
            cout << ret[i][j] << " ";
        }
        cout << endl;
    }
}