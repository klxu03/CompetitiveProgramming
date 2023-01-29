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

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll q, Q, T, k, l, r, x, y, z;
int n, m, ss;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	// cin >> test_cases;
	
	f0r(test_case, test_cases) {
		solve();
	}
}
vector<pair<ll, ll>> vals;

ll greedy_swaps() {
	ll ret = 0;

	f0r(i, vals.size()) {
		ret += vals[i].first * vals[i].second;
	}

	while (true) {
		ll diff = 0;

		f0r(i, vals.size() - 1) {
			// check if swap is smaller
			ll orig = vals[i].first * vals[i].second + vals[i + 1].first * vals[i + 1].second;
			ll next = vals[i].first * vals[i + 1].first + vals[i].second * vals[i + 1].second;

			if (next < orig) {
				// go swap
				diff -= (orig - next);

				swap(vals[i].second, vals[i + 1].first);
			}
		}

		ret += diff;

		if (diff == 0) break;
	}
	DEBUG(vals);
	
	return ret;
}

void solve() {
	cin >> n >> ss;
	vector<int> inp(n);

	f0r(i, n) {
		cin >> inp[i];
	}
	int first;
	int second;

	// assume a small big initial construct
	vals = vector<pair<ll, ll>>(0);
	if (inp[1] <= ss) {
		vals.push_back({inp[0], 0});
	} else {
		vals.push_back({inp[0], ss});
	}

	for (int i = 1; i < n - 2; i++) {
		if (inp[i] <= ss) {
			first = inp[i];
		} else {
			first = inp[i] - ss;
		}

		if (inp[i + 1] <= ss) {
			second = 0;
		} else {
			second = ss;
		}

		vals.push_back({first, second});
	}

	if (inp[n - 2] <= ss) {
		first = inp[n - 2];
	} else {
		first = inp[n - 2] - ss;
	}
	vals.push_back({first, inp[n - 1]});

	ll ans = greedy_swaps();
	
	// then try again big small construct again
	vals = vector<pair<ll, ll>>(0);
	if (inp[1] <= ss) {
		vals.push_back({inp[0], inp[1]});
	} else {
		vals.push_back({inp[0], inp[1] - ss});
	}

	for (int i = 1; i < n - 2; i++) {
		if (inp[i] <= ss) {
			first = 0;
		} else {
			first = ss;
		}
	}

}