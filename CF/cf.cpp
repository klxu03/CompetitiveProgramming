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
ll n, m;

void solve();

// Problem:
int main() {
    io;
    ll test_cases = 1;
//    cin >> test_cases;

    f0r(test_case, test_cases) {
        solve();
    }
}

ll get_min(string &s) {
    vector<bool> visited(m, false);
    // first bunch 11 together
    ll c2 = 0; // groups of 2 counters
    f0r(i, m - 1) {
        if (s[i] == '1' && s[i + 1] == '1') {
            visited[i] = true;
            visited[i + 1] = true;
            i++;
            c2++;
        }
    }

    ll g1 = 0; // num grouped ones

    // too many 11 grouped together
    if (c2 >= m/4) {
        // get rid of some
        int rmv = c2 - m / 4;
        f0r(i, m - 1) {
            if (rmv == 0) {
                break;
            }

            if (visited[i]) {
                visited[i] = false;
                visited[i + 1] = false;
                i++;
                rmv--;
            }
        }
    }

    ll a1 = 0; // number of alone 1s, or non_visited ones
    // need to group some more 2s, all |11| grouped together, just group some |01|
    f0r(i, m) {
        if (visited[i]) {
            g1++;
            i++;
        } else if (s[i] == '1') {
            a1++;
        }
    }

    return a1 + g1;
}

ll get_max(string &s) {
    vector<bool> grouped(m, false); // start i, and i + 1 will be grouped together
    ll c2 = 0;
    f0r(i, m - 1) {
        if (s[i] == '0' && s[i + 1] == '0') {
            c2++;
            i++;
            continue;
        }

        if (s[i] == '0' && s[i + 1] == '1') {
            c2++;
            i++;
            continue;
        }

        if (s[i] == '1' && s[i + 1] == '0') {
            c2++;
            i++;
            continue;
        }
    }

    ll num1 = 0;
    f0r(i, m) {
        if (s[i] == '1') {
            num1++;
        }
    }

    // not enough groups, deficit so need to take some |1|1| and group them together, losing a new appt
    if (c2 < m/4) {
        return num1 - (m/4 - c2);
    }

    return num1;
}

void solve() {
    cin >> n >> m;

    vector<string> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }

    ll rmin = 0; // ret min
    ll rmax = 0; // ret max

    f0r(i, n) {
        string s = inp[i];
        rmin += get_min(s);
        rmax += get_max(s);
    }

    cout << rmin << " " << rmax << endl;
}
