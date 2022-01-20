#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>

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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, q, Q, T, k, l, r, x, y, z, g;

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=595 
int main() {
    usaco("div7");
    // io;

    cin >> n;
    vector<ll> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }

    vector<ll> sums(n + 1);
    sums[0] = 0;
    f0r(i, n) {
        sums[i + 1] = sums[i] + (inp[i] % 7);    
    }

    vector<ll> sums_mod(n + 1);
    f0r(i, n + 1) {
        sums_mod[i] = sums[i] % 7;
    }

    // Find occurences of the same number, like 3 and 3 and set its first like pairs[1].f to be first time 1 exists 
    // and pairs[1].s to be the last time 1 exists
    vector<pair<ll, ll> > pairs(8);
    // Initially fill in pairs[1].f to be -1 as it hasn't been seen yet
    f0r(i, 8) {
        pairs[i] = make_pair(-1, -1);
    }

    f0r(i, n + 1) {
        ll num = sums_mod[i];
        if(pairs[num].f == -1) {
            pairs[num].f = i;
        } else {
            pairs[num].s = i;
        }
    }
    DEBUG(pairs);

    ll max = -1;
    f0r(i, 8) {
        if (pairs[i].s - pairs[i].f > max) max = pairs[i].s - pairs[i].f;
    }

    cout << max << endl;

}