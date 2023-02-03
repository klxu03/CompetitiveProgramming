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
ll n, c, m;

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
	cin >> n >> c;
	vector<ll> teleporters(n);
	f0r(i, n) {
		cin >> teleporters[i];
	}

	vector<ll> costs(n);
	vector<ll> left_costs(n);
	vector<ll> right_costs(n);

	map<ll, int> left_costs_s;
	map<ll, int> right_costs_s;

	f0r(i, n) {
		// you either full go left chain or go right
		// costs is just n - i + 1 or just i + 1
		left_costs[i] = i + 1 + teleporters[i];
		left_costs_s.insert({left_costs[i], i});

		right_costs[i] = n - i + teleporters[i];
		right_costs_s.insert({right_costs[i], i});

		costs[i] = min(left_costs[i], right_costs[i]);
	}

	int right_ret = 0;
	ll right_cost = 0;

	bool used_left = false;
	// simulate always choosing right
	while (right_costs_s.size() > 2 && right_costs_s.begin()->first < left_costs_s.begin()->first) {
		if (right_costs_s.begin()->second == left_costs_s.begin()->second) {
			// DEBUG("made it into the first if");
			// the best right is the same as the best left, figure out next one
			
			ll next_left = (++left_costs_s.begin())->first + right_costs_s.begin()->first;
			ll next_right = (++right_costs_s.begin())->first + (++left_costs_s.begin())->first;

			if (right_cost + min(next_left, next_right) > c) {
				DEBUG("break1");
				break;
			}

			if (next_right == next_left) {
				// use current right as a left
				right_cost += next_right;

				// erase from leftmost from left
				left_costs_s.erase(left_costs_s.begin());

				// erase rightmost and next right from right
				right_costs_s.erase(right_costs_s.begin());
				right_costs_s.erase(right_costs_s.begin());

				right_ret += 2;
				used_left = true;
				DEBUG("break2");
				break; // found a suitable left
			} else {
				// use next left, and keep current right as a right
				right_cost += right_costs_s.begin()->first;

				// erase right most
				right_costs_s.erase(right_costs_s.begin());

				// erase leftmost 
				left_costs_s.erase(left_costs_s.begin());

				right_ret++;
			}

		} else {
			// DEBUG("made it into the first else");
			ll to_add = right_costs_s.begin()->first;
			if (right_cost + to_add + left_costs_s.begin()->first > c) {
				// need to add left right now
				right_cost += left_costs_s.begin()->first;
				right_ret++;
				used_left = true;

				DEBUG("break3");
				break;
			} else {
				right_cost += right_costs_s.begin()->first;
				right_costs_s.erase(right_costs_s.begin());
				right_ret++;
			}

		}
	}

	if (!used_left) {
		DEBUG("did not use left");
		DEBUG(right_cost, right_ret);
		DEBUG(left_costs_s.begin()->first);
		if (left_costs_s.begin()->first > c) {
			
		} else {
		// use left right now
		right_cost += left_costs_s.begin()->first;
		right_ret++;

		// erase the equivalent in the right
		int ind = left_costs_s.begin()->second;
		right_costs_s.erase(right_costs[ind]);

		left_costs_s.erase(left_costs_s.begin());

		used_left = true;
		DEBUG(left_costs_s, right_costs_s);
		}
	}

	if (used_left) {
		while (right_costs_s.size() > 0 && c >= right_cost + min(right_costs_s.begin()->first, left_costs_s.begin()->first)) {
			if (right_costs_s.begin()->first < left_costs_s.begin()->first) {
				right_cost += right_costs_s.begin()->first;
				right_ret++;

				// erase equivalent in left
				int ind = right_costs_s.begin()->second;
				left_costs_s.erase(left_costs[ind]);

				right_costs_s.erase(right_costs_s.begin());
			} else if (left_costs_s.begin()->first < right_costs_s.begin()->first) {
				right_cost += left_costs_s.begin()->first;
				right_ret++;

				// erase equivalent in right
				int ind = left_costs_s.begin()->second;
				right_costs_s.erase(right_costs[ind]);

				left_costs_s.erase(left_costs_s.begin());
			} else {
				if (right_costs_s.begin()->second == left_costs_s.begin()->second) {
					right_cost += right_costs_s.begin()->first;

					right_costs_s.erase(right_costs_s.begin());
					left_costs_s.erase(left_costs_s.begin());

					right_ret++;
				} else {
					// arbitrarily decide to use right
					right_cost += right_costs_s.begin()->first;

					// erase equivalent in left
					int ind = right_costs_s.begin()->second;
					left_costs_s.erase(left_costs[ind]);

					right_costs_s.erase(right_costs_s.begin());
					right_ret++;
				}
			}
		}
	}

	cout << right_ret << endl;
}