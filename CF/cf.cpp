#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = b; a >= c; a--)
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
    cin >> n;
    vector<ll> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }

    // store value, and then its index
    vector<pair<ll, int>> pref(n);
    pref[0] = {inp[0], 0};
    f1r(i, 1, n) {
        if (inp[i] + i > pref[i - 1].f) {
            pref[i] = {inp[i] + i, i};
        } else {
            pref[i] = pref[i - 1];
        }
    }
    vector<pair<ll, int>> suff(n);
    suff[n - 1] = {inp[n - 1], n - 1};
    r1f(i, n - 2, 0) {
        if (inp[i] + (n - 1) - i > suff[i + 1].f) {
            suff[i] = {inp[i] + (n - 1) - i, i};
        } else {
            suff[i] = suff[i + 1];
        }
    }
    DEBUG(pref);
    DEBUG(suff);

    // go through, select each point as a mid
    ll ret = -1;
    vector<ll> ans;
    f1r(i, 1, n - 1) {
        pair<ll, int> left = pref[i - 1];
        pair<ll, int> right = suff[i + 1];

        ll curr = inp[i] + inp[left.s] + inp[right.s];
        DEBUG("init sum", curr);
        curr -= (right.s - left.s);
        ans.pb(curr);
        ret = max(ret, curr);
    }
    DEBUG(ans);

    cout << ret << endl;
}
