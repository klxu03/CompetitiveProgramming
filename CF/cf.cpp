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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll q, Q, T, k, l, r, x, y, z;
int n, m;

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

vector<string> inp;
vector<vector<int>> v;

void solve() {
	cin >> n;
	inp = vector<string>(n);
	v = vector<vector<int>>(n, vector<int>(26, 0));

	f0r(i, n) {
		cin >> inp[i];
	}

	f0r(i, n) {
		vector<int> curr(26, 0);
		f0r(j, inp[i].size()) {
			curr[inp[i][j] - 'a']++;
		}

		v[i] = curr;
	}

	// sorts my v with [even, odd] or even first, odd second
	sort(v.begin(), v.end(), [](const vector<int> &x, const vector<int> &y) {
		for (int i = 0; i < 26; i++) {
			if (x[i] % 2 == y[i] % 2) continue;

			return x[i] % 2 < y[i] % 2;
		}

		return x[25] % 2 < y[25] % 2;
	});

	ll ret = 0;
	// i is current index of bsearching which ones are pairs
	f0r(i, n) {
		// j is which index is going to be the 0
		f0r(j, 26) {
			bool valid = true;
			if (v[i][j] != 0) continue;
			
			ll lo = 0;
			ll hi = n - 1;
			// bsearching this char, make sure sum is odd
			// before the one we set to be 0
			f0r(k, j) {
				// current is even, need first odd
				if (v[i][k] % 2 == 0) {
					// update the lo
					int l = lo;
					int r = hi;

					while (l < r) {
						int mid = l + (r - l)/2;

						if (v[mid][k] % 2 == 1) {
							r = mid;
						} else {
							l = mid + 1;
						}
					}

					if (v[l][k] % 2 == 0) {
						l++;
					}

					lo = l;
				} else {
					// current is odd, need last even
					// update the hi

					int l = lo;
					int r = hi;

					while (l < r) {
						int mid = l + (r - l + 1)/2;

						if (v[mid][k] % 2 == 0) {
							l = mid;
						} else {
							r = mid - 1;
						}
					}

					if (v[l][k] % 2 == 1) {
						l--;
					}

					hi = l;
				}

				if (lo > hi) {
					valid = false;
					break;
				} 
			}

			if (!valid) continue;

			// after the one we set to be 0
			f1r(k, j + 1, 26) {
				// current is even, need first odd
				if (v[i][k] % 2 == 0) {
					// update the lo
					int l = lo;
					int r = hi;

					while (l < r) {
						int mid = l + (r - l)/2;

						if (v[mid][k] % 2 == 1) {
							r = mid;
						} else {
							l = mid + 1;
						}
					}

					if (v[l][k] % 2 == 0) {
						l++;
					}

					lo = l;
				} else {
					// current is odd, need last even
					// update the hi

					int l = lo;
					int r = hi;

					while (l < r) {
						int mid = l + (r - l + 1)/2;

						if (v[mid][k] % 2 == 0) {
							l = mid;
						} else {
							r = mid - 1;
						}
					}

					if (v[l][k] % 2 == 1) {
						l--;
					}

					hi = l;
				}

				if (lo > hi) {
					valid = false;
					break;
				} 
			}

			if (!valid) continue;
			if (lo == hi && lo == n) {
				continue;
			}

			// make sure this singular one is right
			if (lo == hi) {
				f0r(i2, 26) {
					if (i2 == j) continue;

					if (v[i][i2] % 2 == 0) {
						if (v[lo][i2] % 2 != 1) {
							valid = false;
							break;
						}
					} else {
						if (v[lo][i2] % 2 != 0) {
							valid = false;
							break;
						}
					}
				}
			}
			if (!valid) continue;

			ll counter = 0;
			// prune out everything where the mid isnt 0
			f1r(i2, lo, hi + 1) {
				if (v[i2][j] == 0) {
					counter++;
				}
			}

			DEBUG(i, lo, counter);
			ret += counter;
		}
	}

	cout << (ret + 1)/2 << endl;
}