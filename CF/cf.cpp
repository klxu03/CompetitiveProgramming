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
// #ifdef LOCAL
// #define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
// #else
#define DEBUG(...) 6
// #endif

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
	ll a, b, c, d;

	cin >> a >> b >> c >> d;

	ll prod = a * b;

	vector<ll> smol_fac; // factors of prod
	vector<ll> big_fac;
	for(int i = 1; i*i <= prod; i++) {
		if (prod % i == 0) {
			smol_fac.pb(i);
			big_fac.pb(prod/i);
		}
	}
	DEBUG(prod);
	DEBUG(smol_fac);
	DEBUG(big_fac);

	bool swapped = false;
	// I want a - c to be smol, and b to d be big
	if (c > d) {
		swapped = true;
		// swap(a, b);
		// swap(c, d);

		ll temp_b = b;
		b = a;
		a = temp_b;

		ll temp_d = d;
		d = c;
		c = temp_d;

	}

	f0r(i, smol_fac.size()) {
		ll smol = smol_fac[i];
		ll big = big_fac[i];

		DEBUG(i, smol, big);

		ll ret_left = -1;
		ll ret_right = -1;

		double epsilon = 0.000000000001;

		double left = (((double) (a + 1)) - epsilon)/smol; // left bound not okay
		left -= epsilon;
		double right = (((double) c) + epsilon)/smol;
		right += epsilon;
		ll b_left = ceil(left);
		ll b_right = floor(right);

		DEBUG("left: ", b_left, b_right);
		if (b_right >= b_left) {
			// found a match
			ret_left = b_right * smol;
		}


		left = (((double) (b + 1)) - epsilon)/big; // left bound not okay
		left -= epsilon;
		right = (((double) d) + epsilon)/big;
		right += epsilon;
		ll a_left = ceil(left);
		ll a_right = floor(right);
		DEBUG("right: ", a_left, a_right);

		if (a_right >= a_left) {
			// found a match

			ret_right = a_right * big;
		}
		DEBUG(ret_left, ret_right);

		if (ret_left != -1 && ret_right != -1) {
			if (swapped) {
				cout << ret_right << " " << ret_left << endl;
			} else {
				cout << ret_left << " " << ret_right << endl;
			}
			return;
		}

		// if (a < smol && smol <= c) {
		// 	double left = ((double) (b + 1))/big; // left bound not okay
		// 	double right = ((double) d)/big;
		// 	ll a_left = ceil(left);
		// 	ll a_right = floor(right);

		// 	if (a_right >= a_left) {
		// 		// found a match
		// 		cout << smol << " " << a_right * big << endl;
		// 		return;
		// 	}

		// }

		// if (b < big && big <= d) {
		// 	double left = ((double) (a + 1))/smol; // left bound not okay
		// 	double right = ((double) c)/smol;
		// 	ll b_left = ceil(left);
		// 	ll b_right = floor(right);

		// 	if (b_right >= b_left) {
		// 		// found a match
		// 		cout << b_right * smol << " " << big << endl;
		// 		return;
		// 	}
		// }
	}

	cout << -1 << " " << -1 << endl;
}