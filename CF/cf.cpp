#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// rng() gives a better random unsigned 32 bit number

ll q, Q, T, k, l, r, x, y, z;
int n, m;

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

void solve() {
    ll nr, ng, nb;
    cin >> nr >> ng >> nb;

    set<ll> r, g, b;
    vector<int> vr(nr), vg(ng), vb(nb);
    f0r(i, nr) {
       cin >> vr[i];
       r.insert(vr[i]);
    }
    f0r(i, ng) {
        cin >> vg[i];
        g.insert(vg[i]);
    }
    f0r(i, nb) {
        cin >> vb[i];
        b.insert(vb[i]);
    }
    r.insert(INT_MAX); r.insert(INT_MIN);
    g.insert(INT_MAX); g.insert(INT_MIN);
    b.insert(INT_MAX); b.insert(INT_MIN);

    sort(vr.begin(), vr.end());
    sort(vg.begin(), vg.end());
    sort(vb.begin(), vb.end());

    DEBUG(vr);
    DEBUG(vg);
    DEBUG(vb);

    __int128 ret = LLONG_MAX;
    for (int el : vr) {
        // gg be lower first
        auto gg = g.upper_bound(el);
        --gg;
        auto bb = b.lower_bound(el);

        __int128 dist_g = el - *gg;
        __int128 dist_b = *bb - el;
        __int128 dist = *bb - *gg;
        ret = min(ret, dist_g * dist_g + dist_b * dist_b + dist * dist);

        // bb lower now
        gg = g.lower_bound(el);
        bb = b.upper_bound(el);
        --bb;

        dist_g = *gg - el;
        dist_b = el - *bb;
        dist = *gg - *bb;
        ret = min(ret, dist_g * dist_g + dist_b * dist_b + dist * dist);
    }

    for (int el : vg) {
        // rr lower first
        auto rr = r.upper_bound(el);
        --rr;
        auto bb = b.lower_bound(el);

        __int128 dist_r = el - *rr;
        __int128 dist_b = *bb - el;
        __int128 dist = *bb - *rr;
        ret = min(ret, dist_r * dist_r + dist_b * dist_b + dist * dist);

        // bb lower now
        rr = r.lower_bound(el);
        bb = b.upper_bound(el);
        --bb;
        dist_r = el - *rr;
        dist_b = *bb - el;
        dist = *bb - *rr;
        ret = min(ret, dist_r * dist_r + dist_b * dist_b + dist * dist);
    }

    for (int el : vb) {
        // rr lower first
        auto rr = r.upper_bound(el);
        --rr;
        auto gg = g.lower_bound(el);

        __int128 dist_r = *rr - el;
        __int128 dist_g = *gg - el;
        __int128 dist = *rr - *gg;
        ret = min(ret, dist_r * dist_r + dist_g * dist_g + dist * dist);

        // gg lower now
        rr = r.lower_bound(el);
        gg = g.upper_bound(el);
        --gg;

        dist_r = *rr - el;
        dist_g = *gg - el;
        dist = *rr - *gg;
        ret = min(ret, dist_r * dist_r + dist_g * dist_g + dist * dist);
    }

    cout << ((ll) ret) << endl;
}