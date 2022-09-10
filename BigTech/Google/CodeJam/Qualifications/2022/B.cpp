#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>
#include <deque>
#include <climits>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define isOdd & 1
#define qpow2(exponent) 1 << exponent
/* 2^exponent, because every time shifting bit to the leftBound you are essentially multiplying function by two */
#define max3(a, b, c) max({a, b, c}) 
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

// Problem: https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a4672b 
int main() {
	io;
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

void solve() {
    vector<array<ll, 4> > inp = vector<array<ll, 4> > (3);
    f0r(i, 3) {
        f0r(j, 4) {
            cin >> inp[i][j];
        }
    }

    // f0r(i, 3) {
    //     DEBUG(inp[i]);
    // }
    vector<ll> ret(4);
    f0r(i, 4) {
        ret[i] = min({inp[0][i], inp[1][i], inp[2][i]});
    }
    DEBUG(ret);

    ll sum = 0;
    f0r(i, 4) {
        sum += ret[i];
    }

    // 1000000
    if (sum < 1000000) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Subtract from the back

        ll diff = sum - 1000000;

        ll index_counter = 3;
        while (diff > 0) {
            ll subtracted_amount = min(diff, ret[index_counter]);
            ret[index_counter] -= subtracted_amount;
            diff -= subtracted_amount;
            index_counter--;
        }
        f0r(i, 4) {
            cout << ret[i] << " ";
        }
        cout << endl;
    }

}