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

bool recurse(ll height, ll width, multiset<pll, greater<pll>> &inp_h, multiset<pll, greater<pll>> &inp_w) {
    DEBUG(height, width, inp_h, inp_w);
    if (height == 0 || width == 0) return true;

    if ((*inp_w.begin()).f == width) {
        pii popped_w = *inp_w.begin();
        inp_w.erase(inp_w.begin());

        pii popped_h = {popped_w.s, popped_w.f};
        inp_h.erase(inp_h.find(popped_h));

        bool res = recurse(height - popped_w.s, width, inp_h, inp_w);
        inp_w.insert(popped_w);
        inp_h.insert(popped_h);
        if (res) return true;
    }

    if ((*inp_h.begin()).f == height) {
        pii popped_h = *inp_h.begin();
        inp_h.erase(inp_h.begin());

        pii popped_w = {popped_h.s, popped_h.f};
        inp_w.erase(inp_w.find(popped_w));

        bool res = recurse(height, width - popped_h.s, inp_h, inp_w);
        inp_h.insert(popped_h);
        inp_w.insert(popped_w);
        if (res) return true;
    }

    DEBUG("returning false");
    return false;
}

void solve() {
    cin >> n;
    vector<pll> inp(n);

    f0r(i, n) {
        cin >> inp[i].f >> inp[i].s;
    }

    multiset<pll, greater<pll>> inp_h; // sorted greatest height down
    multiset<pll, greater<pll>> inp_w; // sorted greatest height down

    ll area = 0; // summed area
    f0r(i, n) {
        inp_h.insert(inp[i]);
        inp_w.insert({inp[i].s, inp[i].f});
        area += inp[i].f * inp[i].s;
    }

    DEBUG(area, *(inp_h.begin()), *inp_w.begin());

    vector<pll> ans;
    ll height = (*inp_h.begin()).f;
    ll width = (*inp_w.begin()).f;

    if (n == 1) {
        ans.pb({height, width}); // only one rectangle, obvious
    } else {
        if (area % height == 0) {
            bool res = recurse(height, area/height, inp_h, inp_w);
            if (res) ans.pb({height, area/height});
        }

        if (area % width == 0) {
            bool res = recurse(area/width, width, inp_h, inp_w);
            if (res) ans.pb({area/width, width});
        }
    }

    cout << ans.size() << endl;
    f0r(i, ans.size()) {
        cout << ans[i].f << " " << ans[i].s << endl;
    }
}
