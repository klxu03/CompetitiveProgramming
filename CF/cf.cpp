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
    cin >> n;
    vector<ll> inp(n);

    f0r(i, n) {
        cin >> inp[i];
    }

    vector<ll> dp(n, -1); // if the right ends here, what is the best 3 answers to the left

    set<pair<ll, int>, greater<pair<ll, int>>> s; // set of {"summed value", ind}
    vector<pair<ll, int>> cache(3);
    s.insert({inp[0], 0});
//    s.insert({inp[1] + 1, 1});
    cache[0] = {inp[1] + 1, 1};
    cache[1] = {inp[2] + 2, 2};
    dp[2] = inp[0] + inp[1] + inp[2] - 2;
    f1r(i, 3, n) {
        cache[2] = {inp[i] + i, i};
        DEBUG(i);
        DEBUG(s, cache);

        int counter = 0;
        vector<pair<ll, int>> s_best(6, {-1, -1});
        // get the top 3, and then their sums
        for (auto p : s) {
            s_best[counter] = p;
            counter++;

            if (counter == 3) break;
        }

        f0r(j, 3) {
            s_best[3 + j] = {cache[j].f - j, cache[j].s};
        }
        sort(s_best.begin(), s_best.end(), greater<pair<ll, int>>());
        DEBUG(s_best);
        ll sum = 0;
        int lowest_ind = INT_MAX;
        f0r(j, 3) {
            sum += inp[s_best[j].s];
            lowest_ind = min(lowest_ind, s_best[j].s);
        }
        // compare s_best with cache
        DEBUG(sum, lowest_ind);

        // update the cache
        s.insert(cache[0]);
        cache[0] = cache[1];
        cache[1] = cache[2];

        dp[i] = sum - (i - lowest_ind);
    }
    DEBUG(dp);

    ll ret = -1;
    f0r(i, n) {
        ret = max(ret, dp[i]);
    }

    cout << ret << endl;
}
