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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve();

vector<int> fib(46);

// Problem:
int main() {
    io;
    ll test_cases = 1;
    cin >> test_cases;

    fib[0] = 1;
    fib[1] = 1;
    f1r(i, 2, 46) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    f0r(test_case, test_cases) {
        solve();
    }
}

// every input is inclusive, f is the fib number
bool handle(int x, int y, int f, int x0, int x1, int y0, int y1) {
    DEBUG(x, y, f, x0, x1, y0, y1);
    // check up
    if (y - y0 >= fib[f]) {
        return handle(x, y, f - 1, x0, x1, y0 + fib[f], y1);
    }

    // check right
    if (x1 - x >= fib[f]) {
        return handle(x, y, f - 1, x0, x1 - fib[f], y0, y1);
    }

    // check down
    if (y1 - y >= fib[f]) {
        return handle(x, y, f - 1, x0, x1, y0, y1 - fib[f]);
    }

    // check left
    if (x - x0 >= fib[f]) {
        return handle(x, y, f - 1, x0 + fib[f], x1, y0, y1);
    }

    DEBUG("stopped recursing down");
    if (f == 0 && x0 == x1 && y0 == y1) {
        return true;
    }

    return false;
}

void solve() {
    int x, y;
    cin >> n >> y >> x;

    if (handle(x, y, n, 1, fib[n + 1], 1, fib[n])) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}