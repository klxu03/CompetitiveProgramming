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
#include <cmath>
#include <iomanip>

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

ll n, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

int main() {
	io;
	ll test_cases = 1;
    cout << setprecision(15) << fixed;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

double binary_search(double lo, double hi, bool works) {
	while(lo < hi) {
		ll mid = (lo + hi + 1)/2;

		// Binary search part
		// DEBUG(lo, hi, mid, works);
		if(works) {
			if(hi == mid) {
				hi--;
			} else {
				hi = mid;
			}
		} else {
			lo = mid + 1;
		}
	}
	
	// check to see if it works on lo
	if (works == false) {
		lo++;
	}
	return lo;
}

bool works(vector<pll >& inp, double& time, ll maxDistance) {
    double upper = maxDistance;
    double lower = 0;

    f0r(i, inp.size()) {
        // Still to the left of meeting point
        if (inp[i].f < upper) {
            upper = min(upper, (inp[i].f + (inp[i].s * time)));
        } else {
            lower = max(lower, (inp[i].f - (inp[i].s * time)));
        }
        DEBUG(i, lower, upper);
    }
    DEBUG(lower, upper);

    return (upper - lower <= 0.000000000000000000001);
}

void solve() {
	cin >> n;
    vector<pll > inp(n);

    double hi;
    ll maxDistance;
    f0r(i, n) {
        ll location;
        cin >> location;
        if (location > hi) {
            maxDistance = location;
            hi = location;
        }
        inp[i].f = location;
    }

    f0r(i, n) {
        cin >> inp[i].s;
    }

    sort(inp.begin(), inp.end(), [](pll& x, pll& y) {
        if (x.f == x.s) {
            return x.s < x.f;
        } else {
            return x.f < y.f;
        }
    });
    DEBUG(inp);

    double oldTime = hi;

    double lo = 0;
    while (abs(hi - lo) > 0.0000001) {
        double mid = (lo + hi)/2;

        if (works(inp, mid, maxDistance)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    DEBUG(lo);
    cout << lo << endl;
}