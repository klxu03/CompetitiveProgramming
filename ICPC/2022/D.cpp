#include <vector>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <utility>
#include <deque>

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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n >> m;
    vector<vector<ll>> inp(n, vector<ll>(m));
    array<ll, 3> counts;
    fill(counts.begin(), counts.end(), 0);

    f0r(i, n) {
        f0r(j, m) {
            ll num;
            cin >> num;
            inp[i][j] = num;
            counts[num]++;
        }
    }

    DEBUG(counts);
    DEBUG(n, m);
    f0r(i, n) {
        DEBUG(inp[i]);
    }

    if (counts[0] >= 2) {
        cout << 0 << endl;
    } else if (counts[0] == 1) {
        // do a floodfill with the 0
        if (n == 1) {
            if (inp[0][0] == 1) {
                cout << 1 << endl;
            } else if (inp[0][m - 1] == 1) {
                cout << 1 << endl;
            } else {
                cout << 2 << endl;
            }
        } else if (m == 1) {
            if (inp[0][0] == 1) {
                cout << 1 << endl;
            } else if (inp[n - 1][0] == 1) {
                cout << 1 << endl;
            } else {
                cout << 2 << endl;
            }
        } else if (counts[1] >= 1) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    } else {
        ll num_2 = counts[2];
        if (num_2 % 2 == 0) {
            cout << 0 << endl;
        } else if (num_2 == 1) {
            cout << 1 << endl;
        } else {
            ll ret = (ll) pow(2L, num_2/2L);
            DEBUG(ret);
            cout << ret << endl;
        }
    }

}