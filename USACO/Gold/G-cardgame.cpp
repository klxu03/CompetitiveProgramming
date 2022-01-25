#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>

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

#define mp make_pair
#define pll pair<ll, ll>

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

set<ll>::iterator greatest_number_smaller(set<ll>& s, ll num) {
    DEBUG(num, *(s.begin()));

    if(num >= *(s.begin())) {
        return --s.upper_bound(num);
    } else {
        return s.end();
    }
}

// Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=573
int main() {
    usaco("cardgame");
    // io;

    cin >> n;
    vector<ll> total_cards(2*n, 0); // 1 means Elsie has it
    vector<ll> elsie_first(n/2); // Cards elsie is playing in the first half
    vector<ll> elsie_second(n/2); // Cards elsie is playing in the second half
    vector<ll> bessie_cards; // Cards bessie has
    ll win_counter = 0;

    f0r(i, n) {
        ll inp;
        cin >> inp;
        inp--; //0 indexing
        if(i < n/2) {
            elsie_first[i] = inp;
        } else {
            elsie_second[i - n/2] = inp;
        }
        total_cards[inp] = 1;
    }
    sort(elsie_first.begin(), elsie_first.end());
    sort(elsie_second.begin(), elsie_second.end(), greater<ll>()); // In 2nd half, greater first since want smaller
    DEBUG(elsie_first);
    DEBUG(elsie_second);

    f0r(i, 2*n) {
        if(total_cards[i] == 0) {
            bessie_cards.pb(i);
        }
    }
    // sort(bessie_cards.begin() + n/2, bessie_cards.end(), greater<ll>());
    // In 2nd half, greater first we want Bessie's largest hands to be bigger than Elsie's hands
    // 1st half already sorted by smallest first since those smaller half cards want to be smaller than Elsie's 2nd half
    DEBUG(bessie_cards);

    set<ll> bessie_first;
    set<ll> bessie_second;
    f0r(i, n/2) {
        bessie_second.insert(bessie_cards[i]);
    }

    f1r(i, n/2, n) {
        bessie_first.insert(bessie_cards[i]);
    }

    f0r(i, n/2) {
        // Elsie_first = 0, bessie_first(0) = it
        auto it = bessie_first.lower_bound(elsie_first[i]);
        if(it != bessie_first.end()) {
            DEBUG("first", *it, elsie_first[i]);
            bessie_first.erase(it);
            win_counter++;
        }
    }

    f1r(i, n/2, n) {
        // Elsie_second = 3, bessie_second = 1
        auto it = greatest_number_smaller(bessie_second, elsie_second[i - n/2]);
        if(it != bessie_second.end()) {
            DEBUG("second", *it, elsie_second[i - n/2]);
            bessie_second.erase(it);
            win_counter++;
        }
    }

    cout << win_counter << endl;

}   