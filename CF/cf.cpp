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

ll q, Q, T, k, l, r, x, y, z, g;
int n, m;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	cin >> test_cases;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	ll hum;
	cin >> n >> hum;
	int num_double = 2;
	int num_triple = 1;

	vector<ll> astros(n + 1);
	f0r(i, n) {
		cin >> astros[i];
	}
	astros[n] = 0;

	sort(astros.begin(), astros.end());

	int num_rows = (num_double + 1) * (num_triple + 1);
	vector<vector<ll>> dp(n + 1, vector<ll>(num_rows));
	// dp[1][0] is the case we're on astro 1 and best case of no potions used

	// num 2s used, then num 3. And then split by num 2, so iterate over all num 3 possibilities order:
	// <0, 0>, <0, 1> | <1, 0>, <1, 1> | <2, 0>, <2, 1>

	dp[0][0] = hum;
	dp[0][1] = hum * 3;

	f1r(i, 2, num_triple + 1) {
		dp[0][i] = dp[0][i - 1] * 3;
	}

	f1r(i, num_triple + 1, num_rows) {
		// Usually more complicating, abusing num_triple == 1 here so just each iteration lol
		dp[0][i] = dp[0][i - num_triple - 1] * 2;
	}

	int ret = 0;
	// Do the actual DP now
	f1r(i, 1, n + 1) {
		f0r(j, num_rows) {
			if (dp[i - 1][j] > astros[i]) {
				dp[i][j] = dp[i - 1][j] + (astros[i]/2);
			} else {
				dp[i][j] = -1;
			}

			// Do comparisons for max value, doubling and tripling right value

			// Double
			if (j >= num_triple + 1) {
				dp[i][j] = max(dp[i][j], 2 * dp[i][j - num_triple - 1]);
			}

			// Triple, make sure actually has used a triple pot and not none used
			if (j > 0 && j % (num_triple + 1) != 0) {
				dp[i][j] = max(dp[i][j], 3 * dp[i][j - 1]);
			}

			if (dp[i][j] != -1) {
				ret = i;
			}
		}
	}

	/*
	f0r(j, num_rows) {
		f0r(i, n + 1) {
			printf("%5d ", dp[i][j]);
		}
		printf("\n");
	}
	*/

	cout << ret << endl;
}