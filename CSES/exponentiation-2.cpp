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

// O(logn) produce x^n mod m quickly
ll modpow(ll x, ll n, ll m) {
	if (n == 0) return 1%m;
	long long u = modpow(x,n/2,m);
	u = (u*u)%m;
	if (n%2 == 1) u = (u*x)%m;
	return u;
}

ll normalpow(ll x, ll n, ll m) {
	if (n == 0) return 1;
	long long u = normalpow(x,n/2, m);
	u = (u*u);
	if (n%2 == 1) u = (u*x);
    u = u - u/(m - 1) * (m - 1);
	return u;
}

/*
 x = 7, y = 19, x^(101 - floor(101/(y - 1))(y - 1)) mod y
 =
  x = 7, y = 19, x^(101) mod y

  With Fermat's thm, because we know x^y mod y = y, so
  x ^ (y - 1) mod y = 1. I abused this with
  x ^ (100) mod y = x ^ (100 - (y - 1)) mod y 
  because of exponent rules
*/

void solve() {
    ll a, b, c;
    ll m = 1e9 + 7;
	cin >> a >> b >> c;

    // ll res = normalpow(b, c, m);
    ll res = modpow(b, c, m - 1);
    DEBUG(res);
    res = modpow(a, res, m);
    DEBUG(res);
    cout << res << endl;
}