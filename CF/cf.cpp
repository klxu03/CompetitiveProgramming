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

vector<int> arr;
// leftmost element that is greater than or equal to val
int binary_search_leftmost(int val) {
	int l = 0; // left
	int r = n - 1; // right

	while (l < r) {
		int mid = l + (r - l)/2;

		if (arr[mid] >= val) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}

	// could instead just set r = n instead so its possible to assume value of n
	if (arr[l] < val) {
		l++; 
	}

	return l;
}

int binary_search_greater(int val) {
	int l = 0; // left
	int r = n - 1; // right

	while (l < r) {
		int mid = l + (r - l)/2;

		if (arr[mid] > val) {
			r = mid;
		} else {
			l = mid + 1;
		}
	}

	// could instead just set r = n instead so its possible to assume value of n
	if (arr[l] <= val) {
		l++; 
	}

	return l;
}

// rightmost element that is less than or equal to val
int binary_search_rightmost(int val) {
	int l = 0; // left
	int r = n - 1; // right
 
	while (l < r) {
		int mid = l + (r - l)/2;
 
		if (arr[mid] <= val) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}

	if (arr[l] > val) {
		l--;
	}
 
	return l;
}

void solve() {
	cin >> n;
	arr = vector<int>(n);

	f0r(i, n) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());
	DEBUG(arr);

	cin >> q;
	f0r(i, q) {
		int inp_l, inp_r;
		cin >> inp_l >> inp_r;
		int l = binary_search_leftmost(inp_l);
		int r = binary_search_greater(inp_r);

		DEBUG(l, r);
		cout << r - l << " ";
	}
	cout << endl;
}