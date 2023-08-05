#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = b; a >= c; a--)
#define pb push_back
#define f first
#define s second

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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

#include <chrono>
using namespace std::chrono;
struct timer {
    high_resolution_clock::time_point begin;

    timer() {}
    timer(bool b) {
        if (b) start();
    }

    void start() {
        begin = high_resolution_clock::now();
    }

    void print() {
        cout << "Time taken: " << duration_cast<duration<double>>(high_resolution_clock::now() - begin).count() << " seconds" << endl;
    }

    double report() {
        return duration_cast<duration<double>>(high_resolution_clock::now() - begin).count();
    }
};
// Start of main put tin, end of main put tpr (tgt gives you value not printed)
#define tin timer __timer__(1);
#define tpr __timer__.print();
#define tgt __timer__.report()

ll q, Q, T, k, l, r, x, y, z;
ll n, m;
ll s;

void solve();

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

ll calc_accum(ll start, ll num_accum) {
    if (num_accum == 0) {
        return start;
    }

    if (start % 10 == 0) {
        return start;
    }

    if (start % 5 == 0) {
        return start + 5;
    }

    if ((start % 10) % 2 == 1) {
        return calc_accum(start + (start % 10), num_accum - 1);
    }

    // we have enterred the cycle
    ll cycles = num_accum / 4;
//    DEBUG(start, cycles, num_accum);

    for (int i = 0; i < num_accum % 4; i++) {
        start += (start % 10);
    }

    return start + ((ll) 20) * cycles;
}

ll calc(ll start, ll num_accum, ll num_cash) {
    if (num_accum < 0 || num_cash < 0) {
        return -1e9;
    }

    DEBUG(calc_accum(start, num_accum), num_cash);
    return calc_accum(start, num_accum) * num_cash;
}

void solve() {
    cin >> s >> k;
    DEBUG(s, k);

    ll l = 0;
    ll r = k;
    DEBUG(l, r);

    while (l < r) {
        ll mid = l + (r - l)/2;

        // deriv = f(mid + 4) - f(mid)
        // if (deriv > 0) means going right is going up, thus l = mid

        ll deriv_4 = calc(s, mid + 4, k - mid - 4);
        ll deriv = calc(s, mid, k - mid);
        DEBUG(l, mid, r);
        DEBUG(deriv_4 - deriv);
        DEBUG(calc_accum(s, mid));

        if (deriv_4 - deriv > 0) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    DEBUG(l);
    ll ans = 0;
    for (int i = l - 50; i < l + 50; i++) {
        ans = max(ans, calc(s, i, k - i));
    }

    for (int i = 0; i <= 100; i++) {
        ans = max(ans, calc(s, i, k - i));
    }

    cout << ans << "\n";
}
