// https://cses.fi/problemset/task/1164

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

ll n;

int main() {
    io;
    cin >> n;

    vector<array<ll, 3> > input(n); //[x, y, z] x is start date, y is end date, z is id
    f0r(i, n) {
        ll x, y; cin >> x >> y;
        array<ll, 3> in = {x, y, i + 1};
        input[i] = in;
    }

    sort(input.begin(), input.end());
    DEBUG(input);

    set<pair<ll, ll> > st; //[x, y] x is departure date, y is room #

    vector<ll> output(n + 1);
    ll max = 1;

    st.insert(mp(input[0][1], max));
    output[input[0][2]] = 1;

    f1r(i, 1, n) {
        ll start_date = input[i][0]; 
        ll end_date = input[i][1]; 
        ll id = input[i][2]; 
        pair<ll, ll> first_room = (*st.begin()); // The first room, or the one with the earliest departure date
        DEBUG(first_room);
        if (start_date > first_room.f) { // If the first room can be deleted and opened up for a new user
            output[id] = first_room.s;
            st.insert(mp(end_date, first_room.s));
            st.erase(first_room);
        } else {
            max++;
            st.insert(mp(end_date, max));
            output[id] = max;
        }
    }

    cout << max << endl;
    f1r(i, 1, n + 1) {
        cout << output[i] << " ";
    }

}