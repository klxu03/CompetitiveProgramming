#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
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
void usaco(string filename) {
    io;
    freopen((filename + ".txt").c_str(), "r", stdin);
    freopen((filename + "_output.txt").c_str(), "w", stdout);
}

ll q, Q, T, k, l, r, x, y, z, g;
ll n, m;

void solve(); 

// Problem: https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-1/problems/B1 
int main() {
	// io;
    usaco("watering_well_chapter_1_input");
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

void solve() {
	cin >> n;
    vector<pll> trees(n); // trees[1].f = x, trees[1].s = y
    vector<ll> col_preprocess(3001, 0); // How much additional sum you get in col[i]
    vector<ll> row_preprocess(3001, 0); // How much additional sum you get in row[i]
    f0r(i, n) {
        ll x, y;
        cin >> x >> y;
        trees[i] = mp(x, y);
    }

    cin >> q;
    vector<pll> queries(q);
    f0r(i, q) {
        ll x, y;
        cin >> x >> y;
        queries[i] = mp(x, y);
    }

    // Preprocess the row_preprocess and col_preprocess arrays
    f0r(i, 3001) {
        ll sum = 0;
        f0r(j, n) {
            sum += (trees[j].f - i) * (trees[j].f - i);
            sum %= (ll) 1e9 + 7;
        }
        row_preprocess[i] = sum;

        sum = 0;
        f0r(j, n) {
            sum += (trees[j].s - i) * (trees[j].s - i);
            sum %= (ll) 1e9 + 7;
        }
        col_preprocess[i] = sum;
    }

    ll ret = 0;
    f0r(i, q) {
        ll x = queries[i].f, y = queries[i].s;
        ret += row_preprocess[x] + col_preprocess[y];
        ret %= (ll) 1e9 + 7;
    }
    cout << ret << endl;
}