#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <unordered_map>
#include <algorithm>

// #include <bits/stdc++.h>

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

#define mp = make_pair
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

int main() {
	io;
	ll test_cases = 1;
	
	// cin >> test_cases;
	f0r(i, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n >> k;
    vector<ll> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }
    vector<ll> orig(n);
    orig = inp;

    sort(inp.begin(), inp.end());
    bool not_found = true;

    f0r(i, n) {
        ll num = inp[i];

        ll left = 0;
        if(i == 0 && n > 1) left = 1;
        ll right = n - 1;
        if(i == n - 1 && n > 1) right = n - 2;

        while(left != right && not_found) {
            ll sum = inp[left] + inp[right];
            if(sum != k - num) {
                if(sum > k - num) right--;
                if(right == i) right--;

                if(sum < k - num) left++;
                if(left == i) left++;
            } else {
                not_found = false;
                DEBUG("Found something");

                f0r(j, n) {
                    if(orig[j] == inp[i]) cout << j + 1 << " ";
                }

                f0r(j, n) {
                    if(orig[j] == inp[left]) cout << j + 1 << " ";
                }

                f0r(j, n) {
                    if(orig[j] == inp[right]) cout << j + 1 << endl;
                }
            }

            DEBUG(left, right);
        }
    }

    if(not_found) {
        cout << "IMPOSSIBLE" << endl;
    }
}