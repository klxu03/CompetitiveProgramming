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

ll q, Q, T, k, l, r, x, y, z, g;
int n, m;
const ll MOD = (ll) 1e9 + 7;

void solve(); 

// Problem: https://cses.fi/problemset/task/1635 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> x;
    vector<ll> coins(6);
    vector<ll> dp(x + 1, 0); // dp[x] means number of coin combinations that can build up a coin sum of x
    f1r(i, 1, 7) {
        coins[i - 1] = i;
    }
	dp[0] = 1;

	f1r(i, 1, x + 1) {
		ll counter = 0;
		f0r(j, 6) {
			ll coin = coins[j];
			if (i - coin >= 0) {
				counter += dp[i - coin];
				counter %= MOD;
			}
		}

		dp[i] = counter;
	}

    DEBUG(coins);
    DEBUG(dp);
	cout << dp[x] << endl;
}