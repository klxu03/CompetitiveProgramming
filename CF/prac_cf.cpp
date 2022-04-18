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
#include <cmath>

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

// Problem: PACMEN 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n;
    string input;
    cin >> input;
    bool goLeft = false;
    vector<ll> pacmen;
    ll firstAsterisk = -1;

    f0r(i, n) {
        if (firstAsterisk == -1 && input[i] == '*') firstAsterisk = i;

        if (input[i] == 'P') {
            pacmen.pb(i);
        }
    }
    if (firstAsterisk < pacmen[0]) {
        goLeft = true;
    }

    vector<ll> pacmen_cluster; // Start index of cluster, like .PP* will have 1 since index 1 has start in PP cluster
    f0r(i, pacmen.size() - 1) {
        if (pacmen[i + 1] - pacmen[i] == 1) {
            pacmen_cluster.pb(i);
        }
    }

    ll maxDistance = -1;
    f0r(i, pacmen.size()) {
        DEBUG(i, true, goLeft);
        if (goLeft) {
            // go left case
            ll counter = 1;
            ll star_counter = 0;
            while (pacmen[i] - counter >= 0 && input[pacmen[i] - counter] != 'P') {
                if (input[pacmen[i] - counter] == '*') {
                    star_counter = counter;
                }
                counter++;
            }
            maxDistance = max(maxDistance, star_counter);
        } else {
            ll counter = 1;
            ll star_counter = 0;
            while (pacmen[i] + counter < n && input[pacmen[i] + counter] != 'P') {
                if (input[pacmen[i] + counter] == '*') {
                    star_counter = counter;
                }
                counter++;
            }
            maxDistance = max(maxDistance, star_counter);
        }

        if (pacmen[i + 1] - pacmen[i] == 1) {
            goLeft = !goLeft;
        }
        DEBUG(i, maxDistance);
    }

    DEBUG(maxDistance);
    cout << maxDistance << endl;

}