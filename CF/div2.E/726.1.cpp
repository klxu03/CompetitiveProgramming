// Problem: https://codeforces.com/contest/1537/problem/E1
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

    ll s_length = 1;
    s += s; // Double the string length now so I can always compare left and right side without it going out of bounds on the right side with total string being 10 long, and string A being 6 long and B being 4 long. Now total string is 20 long, so it can go all the way to 10 and 10
    while (true) {
        DEBUG(s_length, s.substr(0, s_length), s.substr(s_length, s_length));

        // Brute force method of doing the bottom part
        // string leftSide = s.substr(0, s_length);
        // string rightSide = s.substr(s_length, s_length);
        // if (leftSide >= rightSide && s_length < s.length()/2) {
        //     s_length++;
        // } else {
        //     break;
        // }

        // Better way of doing the top part without taking up so much string memory
        bool condition = true;
        f0r(i, s_length) {
            if (s[i] > s[i + s_length]) {
                break;
            } else if (s[i] < s[i + s_length]) {
                condition = false;
            }
        }

        if (condition && s_length < s.length()/2) {
            s_length++;
        } else {
            break;
        }
    }
    s = s.substr(0, s_length);
   

    // Prune out the ending substrings that are exactly the same as the first part

    s_length = s.length();
    string og_string = s;
    f0r(i, k/s_length + 1) {
        s += og_string;
    }

    s = s.substr(0, k); 
    
    cout << s;
}