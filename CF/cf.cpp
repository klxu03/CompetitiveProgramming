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

ll n, q, Q, T, t, k, l, r, x, y, z, g;

int main() {
    io;
    cin >> n >> k;
    
    string s;
    cin >> s;

    DEBUG(s, s[s.length() - 1], 'a' < 'c', true);
    while (s.length() != k) {

        vector<ll> firstLetter;
        for (ll i = 0; (i = s.find(s[0], i)) != string::npos; i++) {
            firstLetter.pb(i);
        }

        ll maxLengthBetween = 0;
        f0r(i, firstLetter.size() - 1) {
            if (firstLetter[i + 1] - firstLetter[i] > maxLengthBetween) {
                maxLengthBetween = firstLetter[i + 1] - firstLetter[i];
            }
        }


        if (firstLetter.size() == 1) {
            while(s[s.length() - 1] > s[0]) {
                s.pop_back();
            }
        } else {
            vector<string> subStrings(firstLetter.size());
            f0r(i, firstLetter.size()) {
                subStrings[i] = s.substr(firstLetter[i], firstLetter[i + 1] - firstLetter[i]);
            }
            DEBUG(maxLengthBetween, firstLetter, subStrings, firstLetter.size());
            //DEBUG(s.substr(firstLetter[1], firstLetter[2]), s.substr(4, 4));
            bool condition = true;

            while (condition) {
                condition = false;
            }

            ll firstLengthBetween = firstLetter[1] - firstLetter[0];

            f0r(i, firstLengthBetween) {
                
            }
        }

        ll s_length = s.length();
        f0r(i, k/s_length + 1) {
            s += s;
        }

        s = s.substr(0, k); 
    }
    
    cout << s;
}