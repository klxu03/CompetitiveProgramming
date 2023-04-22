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

// Problem:
int main() {
    io;
    ll test_cases = 1;
    cin >> test_cases;

    f0r(test_case, test_cases) {
        solve();
    }
}

void solve() {
    cin >> n >> k;

    vector<ll> inp1(n);
    vector<ll> inp2(n);
    f0r (i, n) {
        cin >> inp1[i];
    }
    f0r(i, n) {
        cin >> inp2[i];
    }

    vector<pll> ranges_p;
    ranges_p.pb({inp1[0], inp2[0]});
    f1r(i, 1, n) {
        if (inp1[i] <= inp2[i - 1]) {
            ranges_p[ranges_p.size() - 1].s = max(inp2[i - 1], inp2[i]);
        } else {
            ranges_p.pb({inp1[i], inp2[i]});
        }
    }

    vector<ll> ranges(ranges_p.size());
    f0r(i, ranges_p.size()) {
        ranges[i] = ranges_p[i].s - ranges_p[i].f + 1;
    }

    multiset<ll, greater<ll>> s;
    ll sum = 0;

    ll ret = LLONG_MAX;
    f0r(i, ranges.size()) {
        sum += ranges[i];
        s.insert(ranges[i]);

        DEBUG(sum, *(--s.end()), k, s.size());

        while (sum - *(--s.end()) >= k) {
            ll rightmost = inp2[i] - (sum - k);
            ll new_cost = rightmost + s.size() * 2;
            ret = min(ret, new_cost);
            sum -= *(--s.end());
            s.erase((--s.end()));
        }

        if (sum >= k) {
            ll rightmost = inp2[i] - (sum - k);
            ll new_cost = rightmost + s.size() * 2;
            ret = min(ret, new_cost);
        }

        DEBUG("post", sum, *(--s.end()), k, s.size());
    }

    if (ret == LLONG_MAX) {
        cout << -1 << endl;
        return;
    }

    cout << ret << endl;
}
