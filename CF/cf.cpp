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
// #define s second
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

ll q, Q, T, k, l, r, x, y, z;
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

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds; 

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

ll p;
void solve() {
	cin >> n >> p;
	vector<ll> inp(n);

	set<ll> inps; // numbers that have been seen
	f0r(i, n) {
		ll x;
		cin >> x;
		inp[i] = x;
		inps.insert(x);
	}
	DEBUG(inp);

	set<ll> s; // Set containing number "ranges" that need to be dealt with
	// If set contains 0 5, then 0 1 2 3 4 5 are not present

	// Insert in the smallest element possible starting at 0
	// f0r(i, p - 1) {
	// 	if (inps.count(i) == 0) {
	// 		s.insert(i);
	// 		break;
	// 	}
	// }

	// Create the set s
	f0r(i, n) {
		bool prev_num = true; // insert previous number into set
		bool next_num = true; // insert next number into set

		ll prev_number = inp[i] - 1;
		if (inp[i] == 0) {
			prev_number = p - 1;
		}
		if (inps.count(prev_number) > 0) {
			prev_num = false;
		}
		ll next_number = inp[i] + 1;
		if (inp[i] == p - 1) {
			next_number = 0;
		}
		if (inps.count(next_number) > 0) {
			next_num = false;
		}

		if (prev_num) {
			s.insert(prev_number);
		}
		if (next_num) {
			s.insert(next_number);
		}
	}
	DEBUG(s);

	// Case where no overflow is required
	if (s.size() == 0 || *(s.begin()) > inp[n - 1]) {
		DEBUG("overflow not needed");
		if (s.size() == 0) {
			cout << 0 << endl;
		} else {
			// Attempt to add the biggest element
			if (inps.count(p - 1) == 0) {
				s.insert(p - 1);
			}

			// Since no overflow needed, just subtract the biggest end bound with last digit
			cout << *(--s.end()) - inp[n - 1] << endl;
		}
	} else {
		DEBUG("overflow needed");
		DEBUG(s);

		// Simulate overflow happening
		s.erase(0); // since we are overflowing, 0 is achieved
		
		if (n - 1 == 0) {
			// manually erase 1 from "last" digit overflowing
			s.erase(1);
			inps.insert(1);

			if (inps.count(2) == 0) {
				s.insert(2);
			}
		}
		r0f(i, n - 1) {
			if (inp[i] != p - 1) {
				// break overflowing continuing

				// kill a lower bound, now see if you need to push up the lower bound
				DEBUG("erase:", inp[i] + 1);
				s.erase(inp[i] + 1);
				inps.insert(inp[i] + 1); // a new number we have "visited"

				if (inps.count(inp[i] + 2) == 0) {
					s.insert(inp[i] + 2);
				}
				DEBUG(s);

				break;
			} else if (i == 0) {
				// the last, or "first" digit is also p - 1 manually erase 1
				s.erase(1);
				inps.insert(1);	

				if (inps.count(2) == 0) {
					s.insert(2);
				}
			}

			// else keep overflowing
		}

		ll max_num = 0; // max number less than pivot that we still haven't had yet
		DEBUG("final", s);
		for (ll num : s) {
			DEBUG(num, inp[n - 1]);
			if (num > inp[n - 1]) {
				break;
			}

			max_num = num;
		}
		DEBUG(max_num, p - 1, inp[n - 1]);

		// res = overflowed up amount + amount needed to begin overflowing
		cout << (max_num + 1) + ((p - 1) - inp[n - 1]) << endl; 
	}
}