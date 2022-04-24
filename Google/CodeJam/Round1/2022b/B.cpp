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
#include <numeric>
#include <cmath>
#include <iomanip>

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
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

void solve() {
    ll p;
	cin >> n >> p;

    vector<vector<ll> > vec(n, vector<ll>(p));

    f0r(i, n) {
        f0r(j, p) {
            cin >> vec[i][j];
        }
    }

    f0r(i, n) {
        sort(vec[i].begin(), vec[i].end());
        DEBUG(vec[i]);
    }

    // dp[5][0] means optimal # for 6th customer ending at small, 1 means ending at big 
    vector<vector<ll> > dp(n, vector<ll>(2));
    
    dp[0][1] = vec[0][p - 1];
    dp[0][0] = dp[0][1] + vec[0][p - 1] - vec[0][0];

    DEBUG(dp[0]);
    f1r(i, 1, n) {
        DEBUG(i);

        // Trying to get dp[i][0]
        
        // Case of 40 -> 80 -> 50
        ll small_1 = dp[i - 1][1]; // small starting previous biggest
        small_1 += abs(vec[i][p - 1] - vec[i - 1][p - 1]); // Go to the biggest number, 80
        small_1 += vec[i][p - 1] - vec[i][0]; // Now go to smallest number

        // Case of 10 -> 80 -> 50
        ll small_2 = dp[i - 1][0];
        small_2 += abs(vec[i][p - 1] - vec[i - 1][0]); // Go to biggest number
        small_2 += vec[i][p - 1] - vec[i][0];

        dp[i][0] = min(small_1, small_2);

        // Trying to get dp[i][1]
        // Case of 10 -> 50 -> 80

        ll big_1 = dp[i - 1][0];
        big_1 += abs(vec[i][0] - vec[i - 1][0]); // Go to smallest number 
        big_1 += vec[i][p - 1] - vec[i][0]; // Go to biggest number

        // Case of 40 -> 50 -> 80
        ll big_2 = dp[i - 1][1];
        big_2 += abs(vec[i][0] - vec[i - 1][p - 1]); // Go to smallest number
        big_2 += vec[i][p - 1] - vec[i][0]; // Go to biggest number

        dp[i][1] = min(big_1, big_2);

        DEBUG(dp[i]);
    }
    cout << min(dp[n - 1][0], dp[n - 1][1]) << endl;

}