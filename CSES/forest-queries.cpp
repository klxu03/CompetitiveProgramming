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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: https://cses.fi/problemset/task/1652/ 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n >> q;

	vector<string> vec(n);
	f0r(i, n) {
		cin >> vec[i];
	}
	vector<vector<ll> > sums(n, vector<ll> (n, 0));

	f0r(i, n) {
		DEBUG(vec[i]);
	}

	if (vec[0][0] == '*') {
		sums[0][0] = 1;
	}

	// Do the first row
	f1r(i, 1, n) {
		if (vec[0][i] == '*') {
			sums[0][i] = sums[0][i - 1] + 1;
		} else {
			sums[0][i] = sums[0][i - 1];
		}
	}

	// Do the first column
	f1r(i, 1, n) {
		if (vec[i][0] == '*') {
			sums[i][0] = sums[i - 1][0] + 1;
		} else {
			sums[i][0] = sums[i - 1][0];
		}
	}

	// Do the rest normally
	f1r(i, 1, n) {
		f1r(j, 1, n) {
			sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1]; 
			if (vec[i][j] == '*') {
				sums[i][j]++;
			}
		}
	}

	f0r(i, n) {
		DEBUG(sums[i]);
	}

	DEBUG(sums[1][2]);
	f0r(i, q) {
		/* Sample
		4 1
		.*..
		*.**
		**..
		****

		3 2 4 3
		*/

		array<ll, 4> query;
		cin >> query[0] >> query[1] >> query[2] >> query[3];
		// y1 x1 y2 x2

		query[0]--; query[1]--; query[2]--; query[3]--;
		DEBUG(query);
		ll right_bottom_corner = sums[query[2]][query[3]]; // (3, 2)
		DEBUG(query[2], query[3]);

		ll left_bottom_corner = 0;
		if (query[2] >= 0 && query[1] - 1 >= 0) {
			left_bottom_corner = sums[query[2]][query[1] - 1]; // (3, 0)
			DEBUG(query[2], query[1] - 1);
		}

		ll right_top_corner = 0;
		if (query[0] - 1 >= 0 && query[3] >= 0) {
			right_top_corner = sums[query[0] - 1][query[3]]; // (1, 3)
			DEBUG(query[0] - 1, query[3]);
		}

		ll left_top_corner = 0;
		if (query[0] - 1 >= 0 && query[1] - 1 >= 0) {
			left_top_corner = sums[query[0] - 1][query[1] - 1]; // (1, 0)
			DEBUG(query[0] - 1, query[1] - 1); 
		}

		DEBUG(right_bottom_corner, left_bottom_corner, right_top_corner, left_top_corner);
		cout << right_bottom_corner - left_bottom_corner - right_top_corner + left_top_corner << endl;
	}
}