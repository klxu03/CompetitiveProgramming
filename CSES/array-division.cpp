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

// Problem URL: https://cses.fi/problemset/task/1085
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

ll lastTrue(ll lo, ll hi, ll k, function<int(int)> f) {
    hi++;
    while(lo < hi) {
        ll mid = lo + (hi - lo + 1)/2;
        DEBUG(lo, mid, hi);
        if(f(mid) > k) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    if(f(lo + 1) == k) {
        return lo + 1;
    } else {
        return lo;
    }
}

set<ll>::iterator greatest_number_smaller(set<ll>& s, ll num) {
    DEBUG(num, *(--s.end()), *s.begin());

    if(num <= *(--s.end()) && num >= *s.begin()) {
        return --s.upper_bound(num);
    } else {
        return s.end();
    }
}


void solve() {
    cin >> n >> k;
    vector<ll> inp(n);
    set<ll> sums;
    ll right = 0;
    ll left = 0;
    f0r(i, n) {
        cin >> inp[i];
        right += inp[i];
        sums.insert(right);
        if(inp[i] > left) {
            left = inp[i];
        }
    }
    
    DEBUG(inp, sums);
    DEBUG(left, right); // Bounds for the binary search

    ll last_true = lastTrue(left, right, k, [&sums](ll mid) {
        ll k_counter = 1;
        ll counter = 0;

        auto it = greatest_number_smaller(sums, counter + mid);
        while(it != sums.end() && *it < *(--sums.end())) {
            k_counter++;
            counter = *it;
            it = greatest_number_smaller(sums, counter + mid);

            if(k_counter > k) {
                break;
            }
        }

        DEBUG(mid, k_counter);
        return k_counter;
        // if (k_counter > k) {
        //     return true;
        // } else {
        //     return false;
        // }

    });

    cout << last_true << endl;
}