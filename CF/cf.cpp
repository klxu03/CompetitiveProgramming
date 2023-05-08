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
    cin >> n >> m;
    m--;
    vector<ll> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }
    DEBUG(n, m, inp);
    ll ret = 0;

    if (n == 1) {
        cout << 0 << endl;
        return;
    }

    if (inp[m] > 0 && m > 0) {
        inp[m] = -inp[m];
        ret++;
    }

    vector<ll> pref(n);
    pref[0] = inp[0];
    f1r(i, 1, n) {
        pref[i] = pref[i - 1] + inp[i];
    }
    DEBUG(pref);

    // current prefix sum
    ll curr = pref[m];
    ll orig = curr;

    // going left
    priority_queue<ll> pq;
    r1f(i, m - 1, 0) {
        while (pref[i] < curr) {
            // keep flipping pos to negative
            ll t = pq.top();
            DEBUG(t);
            curr -= 2 * t;
            pq.pop();
            // don't really need to push a negative number into pq
//            pq.push(-1 * t);
            ret++;
        }
        pq.push(inp[i]); // changing this value from pos to neg will affect both curr prefix sum and the mth one, so never try to flip yet
    }
    DEBUG("left", ret);
    curr = orig; // undo the prefix changes since they affect everything going to the right and forward as well

    // going right
    priority_queue<ll, vector<ll>, greater<ll>> pq_r;
    ll pref_debt = 0;
    f1r(i, m + 1, n) {
        pq_r.push(inp[i]); // changing this value won't affect mth prefix sum, but will affect this one so can try to flip it
        while (pref[i] + pref_debt < curr) {
            // keep flipping from neg to positive
            ll t = pq_r.top();
            DEBUG(t);
            pref_debt -= 2 * t;
            pq_r.pop();
            DEBUG(pq_r.top());
            // don't really need to push a positive number into pq
//            pq_r.push(-1 * t);
            ret++;
            DEBUG(pref_debt);
        }
    }

    cout << ret << endl;
}
