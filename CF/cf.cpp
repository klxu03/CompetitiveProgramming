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

void solve();

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

vector<int> inp;

// INT_MAX means that there is no next_greater, pretty fucked
vector<int> next_greater; // functions similar to a map, next_greater[5] == 4 means the next value (value to left) of the value 5 is index 4, which may have a value of say 8 for example
vector<int> next_smaller;
// -1 means there is no prev_greater
vector<int> prev_greater;
vector<int> prev_smaller;

// left and right bound inclusive for answer range
ll divide(int l, int r) {
    if (l == r) {
        DEBUG(l, r, "ret 0");
        return 0;
    }

    int midd = (l + r)/2;
    ll left = divide(l, midd);
    ll right = divide(midd + 1, r);
    DEBUG(l, midd, r);

    // calculate merge
    // min is on the left, max can be on left or right
    ll merge = 0;
    pii mi = {INT_MAX, -1}; // running min
    pii ma = {-1, -1}; // running max
    for (int i = midd; i >= l; i--) {
        mi = min(mi, {inp[i], i});
        ma = max(ma, {inp[i], i});

        DEBUG(mi, next_smaller[mi.f]);
        DEBUG(ma, next_greater[ma.f]);

        // hi is on the left, already proper
        if (mi.s < ma.s) {
            merge += min(next_smaller[mi.f], r + 1) - (midd + 1);
        } else {
            merge += max(0, min(next_smaller[mi.f], r + 1) - next_greater[ma.f]);
        }
    }
    DEBUG(merge);

    // Merge case when mid | [lo hi]
    // [2] | [1 4]
    mi = {inp[midd + 1], midd + 1};
    ma = {inp[midd + 1], midd + 1};
    for (int i = midd + 2; i <= r; i++) {
        mi = min(mi, {inp[i], i});
        ma = max(ma, {inp[i], i});

        // min is to the right of max
        if (mi.s > ma.s) continue;

        DEBUG(mi, prev_smaller[mi.f]);
        DEBUG(ma, prev_greater[ma.f]);

        // inclusive mid, exclusive minus
        merge += midd - max(prev_greater[ma.f], prev_smaller[mi.f], l - 1);
    }

    DEBUG(l, midd, r, left, right, merge);
    return left + right + merge;
}

void solve() {
    cin >> n;
    inp = vector<int>(n);
    next_greater = vector<int>(n + 1); // + 1 since 1-index the map
    prev_greater = vector<int>(n + 1); // + 1 since 1-index the map
    next_smaller = vector<int>(n + 1); // + 1 since 1-index the map
    prev_smaller = vector<int>(n + 1); // + 1 since 1-index the map

    ll arr[n];

    f0r(i, n) {
        cin >> inp[i];
        arr[i] = inp[i];
    }

    // monotonic stack for next_greater
    deque<pii> dq; // {val, ind}
    for (int i = n - 1; i >= 0; i--) {
        while (!dq.empty()) {
            pii front = dq.front();
            if (inp[i] < front.f) {
                next_greater[inp[i]] = front.s;
                break;
            }
            dq.pop_front();
        }

        if (dq.empty()) {
            next_greater[inp[i]] = INT_MAX;
        }

        dq.push_front({inp[i], i});
    }
    DEBUG(next_greater);

    // next_smaller
    dq.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (!dq.empty() && dq.front().f > inp[i]) dq.pop_front();
        next_smaller[inp[i]] = dq.empty() ? INT_MAX : dq.front().s;
        dq.push_front({inp[i], i});
    }
    DEBUG(next_smaller);

    // prev_greater
    dq.clear();
    f0r(i, n) {
        while (!dq.empty() && dq.front().f < inp[i]) dq.pop_front();
        prev_greater[inp[i]] = dq.empty() ? -1 : dq.front().s;
        dq.push_front({inp[i], i});
    }

    // prev_smaller
    dq.clear();
    f0r(i, n) {
        while (!dq.empty() && dq.front().f > inp[i]) dq.pop_front();
        prev_smaller[inp[i]] = dq.empty() ? -1 : dq.front().s;
        dq.push_front({inp[i], i});
    }

    cout << divide(0, n - 1) << endl;
}