// https://cses.fi/problemset/task/1163

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
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll n, x;

int main() {
    io;
    cin >> x >> n;

    set<pair<ll, ll> > s_x; //<x, y> x is its value, location, and y is the distance to next point
    set<pair<ll, ll> > s_y; //Same thing as s_x, just swapped order of <x, y>

    s_x.insert(mp(0, x)); s_x.insert(mp(x, 0));
    s_y.insert(mp(x, 0)); s_y.insert(mp(0, x));

    ll interest;
    f0r(i, n) {
        cin >> interest;
        DEBUG(s_x, s_y, interest);
        auto it = s_x.lower_bound(mp(interest, -1));
        // DEBUG(*it);
        // DEBUG((*it).f);
        ll newY = (*it).f - interest;

        ll first = (*(prev(it))).f;
        ll second = (*(prev(it))).s; // For the 2nd one, I can change prev(it) to it--, but 
        // only 2nd one since doing it for 1st one will change the value of it
        DEBUG(first, second);

        s_x.erase(mp(first, second));
        s_y.erase(mp(second, first));

        DEBUG(interest, second);
        s_x.insert(mp(first, interest - first));
        s_y.insert(mp(interest - first, first));

        s_x.insert(mp(interest, newY));
        s_y.insert(mp(newY, interest));

        cout << (*prev((s_y.end()))).f << " ";

        // 0 8
        // 0 3 8
        // 0 3 6 8
    }

}