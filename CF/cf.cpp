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

string s;

void solve() {
    cin >> n >> s;

    if (n % 2 == 1) {
        cout << -1 << endl;
        return;
    }

    string rev = s;
    reverse(rev.begin(), rev.end());
    DEBUG(s, rev);

    vector<int> same(26); // how many same of each letter
    ll same_c = 0; // same counter

    // only need to do for half the string
    f0r(i, n/2) {
        if (s[i] == rev[i]) {
            same[s[i] - 'a']++;
            same_c++;
        }
    }

    int most_same = 0;
    char most_c = 'Z';
    f0r(i, 26) {
        if (same[i] > most_same) {
            most_c = 'a' + i;
            most_same = same[i];
        }
    }
    DEBUG(most_same, same_c);

    int non_same = 0; // the # of letters that you can swap the most_same letters that are c | c with
    f0r(i, n/2) {
        if (s[i] != most_c && rev[i] != most_c) {
            non_same++;
        }
    }

    // swap amongst themselves
    if (most_same <= same_c / 2) {
        DEBUG("we can end early");
        if (same_c % 2 == 1) {
            cout << same_c/2 + 1 << endl;
        } else {
            cout << same_c/2 << endl;
        }
        return;
    }
    // there's one letter to rule them all

    // ones the most_same can swap with
    if (most_same > non_same) {
        cout << -1 << endl;
        return;
    }

    cout << most_same << endl;
}
