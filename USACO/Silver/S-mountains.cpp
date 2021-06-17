//http://www.usaco.org/index.php?page=viewproblem2&cpid=896

#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "[";for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];}return cout << "]";}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__);
#else
#define DEBUG(...) 6;
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {cerr << s.substr(0, s.find(',')) << " = " << x << " | "; debug(s.substr(s.find(',') + 2), args...);}

ll n;

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

int main() {
    // io;
    usaco("mountains");
    cin >> n;
    vector<pair<ll, ll> > mountains(n);

    f0r(i, n) {
        ll x, y;
        cin >> x >> y;
        ll first = x - y;
        ll second = x + y;
        mountains[i] = mp(first, second);
    }

    sort(mountains.begin(), mountains.end(), [](pair<ll, ll> &a, pair<ll, ll> &b) {
        if (a.f == b.f) {
            return a.s > b.s;
        } 
        return a.f < b.f;
    });

    ll prevHighest = 0;
    ll counter = 0;
    f0r(i, n) {
        if (mountains[i].s > prevHighest) {
            counter++;
            prevHighest = mountains[i].s;
        }
    }

    cout << counter << endl;
}