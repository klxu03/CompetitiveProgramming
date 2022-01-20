#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define isOdd & 1
#define qpow2(exponent) 1 << exponent
/* 2^exponent, because every time shifting bit to the leftBound you are essentially multiplying function by two */
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp = make_pair
#define t third

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

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, q, Q, T, k, l, r, x, y, z, g;

// Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=643
int main() {
    usaco("diamond");
    // io;

    cin >> n >> k;
    vector<ll> diamonds(n);
    f0r(i, n) {
        cin >> diamonds[i];
    }
    sort(diamonds.begin(), diamonds.end());

    vector<ll> amt(n, 0);
    f0r(i, n) {
        ll num = diamonds[i];

        f1r(j, i + 1, n) {
            if(diamonds[j] - num <= k) {
                amt[i]++;
            } else {
                break;
            }
        }
    }

    DEBUG(diamonds);
    DEBUG(amt);

    // ll max1 = 0, max_total = 0, left = 0, right = 1, curr = 0;
    // while(right < n) {
    //     curr = 0;
    //     if(amt[left] + left >= right) curr--;
        
    //     curr += amt[left] + amt[right];
        
    //     if(max1 <)


    // }
    pair<ll, ll> max1 = make_pair(-10, -1); //first is max1, second is index
    f0r(i, n) {
        if(amt[i] > max1.f) max1 = make_pair(amt[i], i);
    }

    if(n > 1) {
        pair<ll, ll> max2 = make_pair(-10, -1);
        f0r(i, n) {
            if(amt[i] > max2.f && i != max1.s) {
                // Do some math about diamond cannabilism
                // If in the diamond range
                if(i > max1.s && max1.s + max1.f >= i) {
                    ll num_diamonds_cannabilized = i - max1.f;
                    if(max1.f - num_diamonds_cannabilized + amt[i] > max2.f + max1.f) {
                        max2 = make_pair(max1.f - num_diamonds_cannabilized + amt[i], i);
                    }
                } else {
                    max2 = make_pair(amt[i], i);
                }
            }
        }

        cout << max1.f + max2.f + 2 << endl;
    } else {
        cout << 1 << endl;
    }
}   