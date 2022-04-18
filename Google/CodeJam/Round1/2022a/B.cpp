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

int solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	cin >> test_cases;
	
	f0r(test_case, test_cases) {
        // cout << "Case #" << test_case + 1 << ":";
		ll ret = solve();
		if (ret == -1) break;
	}
}

// Do something similar to upper_bound except greatest number smaller
set<ll>::iterator greatest_number_smaller(set<ll>& s, ll num) {
    DEBUG(num, *(--s.end()), *s.begin());
 
    if(num <= *(--s.end()) && num >= *s.begin()) {
        return --s.upper_bound(num);
    } else {
        set<ll>::iterator ending = s.end();
        ending--;
        return ending;
    }
}


int solve() {
	n = 100;

	vector<ll> inp;
    set<ll> nums;

	ll beginning = 1;

	f0r(i, 9) {
		f0r(j, 10) {
			if (i == 0 && j == 9) continue;
			inp.pb(beginning + j);
			nums.insert(beginning + j);
		}
		beginning *= 10;
	}

	// Throw in the remaining 19 numbers randomly
	beginning = 20;
	f0r(i, 11) {
		inp.pb(beginning + i);
		nums.insert(beginning + i);
	}

	// cout << inp.size() << " " << inp << endl;
	DEBUG(inp.size(), inp);
	f0r (i, 100) {
		cout << inp[i] << " ";
	}

	ll initial;
	cin >> initial;
	if (initial == -1) {
		return -1;
	}

	f0r(i, 100) {
		ll num;
		cin >> num;
		nums.insert(num);
		inp.pb(num);
	}

	DEBUG(nums.size(), nums);

	ll sum = 0;
	f0r(i, 200) {
		sum += inp[i];
	}
	DEBUG(sum, sum/2);
	sum /= 2;

	vector<ll> out;
	while(sum > 0) {
		ll res = *greatest_number_smaller(nums, sum);
		sum -= res;
		nums.erase(res);
		out.pb(res);
		DEBUG("current sum", res, sum);
	}

	// DEBUG(nums);
	// nums.erase(2);
	// DEBUG(nums);
	// set<ll> temp;
	// temp.insert(2);
	// temp.insert(5);
	// DEBUG(*temp.lower_bound(2));

	DEBUG(sum, out);
	f0r(i, out.size()) {
		cout << out[i] << " ";
	}
	cout << endl;

	return 0;
}
