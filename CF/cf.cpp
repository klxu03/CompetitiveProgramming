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
    cin >> n >> x >> y;

    vector<llt> inp(n);

    f0r(i, n) {
        cin >> inp[i];

        // help catch bugs
        if (inp[i] >= y) {
            inp[i] = LLONG_MAX;
        }
    }

    sort(inp.begin(), inp.end());

    ll curr = x;

    int stop = -1; // index he stops at, also the left counter for future code
    f0r(i, n) {
        if (curr >= inp[i]) {
            curr++;
        } else {
            stop = i;
            break;
        }
    }

    ll total_diff = y - x; // how much rating he wants to gain

    // do some actual math
    if (stop == -1) {
        cout << total_diff << endl;
        DEBUG("r1");
        return;
    }

    if (x + stop >= y) {
        cout << total_diff << endl;
        DEBUG("r2");
        return;
    }

    // tie or you gain less than you win
    if (stop <= n - stop) {
        cout << -1 << endl;
        DEBUG("r3");
        return;
    }

    // actual problem time
    int total_rds = 0;
    curr = x;

    DEBUG(inp, stop);
    DEBUG(x, y);

    while (stop < n && inp[stop] < y) {
        ll diff = inp[stop] - curr; // how much rating you need to get in order to achieve next level of rating gain

        int per = stop - (n - stop); // how much you win per cycle
        DEBUG(((diff - stop) + (per - 1))); // ceil((diff - stop)/per) num cycles you go through
        int num = ((diff - stop) + (per - 1))/per; // ceil((diff - stop)/per) num cycles you go through

        // now let's apply the buff of num cycles
        total_rds += num;
        curr += per * num;

        ll orig = curr;
        curr += stop;
        f1r(i, stop, n) {
            if (curr >= y) {
                // do the math right now, you achieved your ELO in this cycle
                DEBUG(diff, per, num);
                DEBUG(total_rds, curr, orig);
                cout << total_rds * n + curr - orig << endl;
                DEBUG("r4");
                return;
            }

            if (curr >= inp[i]) {
                stop++;
                curr++;
            } else {
                curr -= (n - stop);
                break; // you cannot beat this opponent, get out, and subtract out all the losses
            }
        }
        total_rds++; // just did another round above
    }

    // case you've unlocked em all
    if (stop == n) {
        // do some math time, but not really since you've unlocked em all now
        total_diff = y - curr;
        cout << total_rds * n + total_diff << endl;
        DEBUG("r5");
        return;
    }

    // your next goal is y, not the next unlocking phase
    ll diff = y - curr; // how much rating you need to get in order to achieve your goal elo

    int per = stop - (n - stop); // how much you win per cycle
    int num = ((diff - stop) + (per - 1))/per; // ceil((diff - stop)/per)

    total_rds += num;
    curr += per * num;

    ll final_res = (y - curr) + total_rds * n;
    DEBUG("final return");
    cout << final_res << endl;
}
