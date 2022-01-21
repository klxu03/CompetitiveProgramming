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
#include <deque>

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

ll n, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

int main() {
	io;
	ll test_cases = 1;
	
	f0r(i, test_cases) {
		solve();
	}
}

// Problem URL: https://cses.fi/problemset/task/1632/
bool cmp(const pair<ll, ll>& x, const pair<ll, ll>& y) {
    if (x.s != y.s) {
        return x.s < y.s;
    } else {
        return x.f < y.f;
    }
}

bool set_cmp(const ll& x, const ll& y) {
    return x < y;
}

set<ll, bool(*)(const ll&, const ll&)>::iterator greatest_number_smaller(set<ll, bool(*)(const ll&, const ll&)>& s, ll num) {
    DEBUG(num, *(s.begin()));

    if(num >= *(s.begin())) {
        return --s.upper_bound(num);
    } else {
        return s.end();
    }
}

void solve() {
    cin >> n >> k;

    vector<pair<ll, ll> > movies(n);
    f0r(i, n) {
        ll start, end;
        cin >> start >> end;
        movies[i] = mp(start, end);
    }
    sort(movies.begin(), movies.end(), cmp);
    DEBUG(movies);

    set<ll, bool(*)(const ll&, const ll&)> s(set_cmp);
    s.insert(movies[0].s);
    ll movies_watched = 1;

    f1r(i, 1, n) {
        auto it = greatest_number_smaller(s, movies[i].f);
        if(it != s.end()) {
            DEBUG("Erasing a number");
            s.erase(it);
            s.insert(movies[i].s);
            movies_watched++;
        } else if(s.size() < k) {
            DEBUG("Adding number, size() < k");
            s.insert(movies[i].s);
            movies_watched++;
        } 
        DEBUG(s);
    }

    cout << movies_watched << endl;

}