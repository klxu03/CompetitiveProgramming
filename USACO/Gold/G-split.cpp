// http://www.usaco.org/index.php?page=viewproblem2&cpid=645

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
// void usaco(string filename) {
//     io;
//     freopen((filename + ".in").c_str(), "r", stdin);
//     freopen((filename + ".out").c_str(), "w", stdout);
// }

ll n;

int main() {
    io;
    // usaco("split");
    cin >> n;
    vector<pair<ll, ll> > cowsX(n); //Sorted by X first
    vector<pair<ll, ll> > cowsY(n); //Sorted by Y first

    f0r(i, n) {
        ll first, second;
        cin >> first >> second;
        pair<ll, ll> input = mp(first, second);
        cowsX[i] = input;
        cowsY[i] = input;
    }

    sort(cowsX.begin(), cowsX.end(), [] (pair<ll, ll> &a, pair<ll, ll> &b) {
        return a.f < b.f;
    });

    sort(cowsY.begin(), cowsY.end(), [] (pair<ll, ll> &a, pair<ll, ll> &b) {
        return a.s < b.s;
    });

    DEBUG(cowsX, cowsY);

    /* Dividing the cows between the left and right half of the field */
    vector<ll> leftRectangle(n);
    leftRectangle[0] = 0; 
    ll highest = cowsX[0].s;
    ll lowest = cowsX[0].s;
    ll left = cowsX[0].f;
    f1r(i, 1, n) {
        if (cowsX[i].s > highest) {
            highest = cowsX[i].s;
        } 
        
        if (cowsX[i].s < lowest) {
            lowest = cowsX[i].s;
        }

        ll height = highest - lowest;
        if (height == 0) {
            height = 1;
        }

        ll length = cowsX[i].f - left;
        if (length == 0) {
            length = 1;
        }

        leftRectangle[i] = height * length;
    }

    vector<ll> rightRectangle(n);
    rightRectangle[n - 1] = 0; 
    highest = cowsX[n - 1].s;
    lowest = cowsX[n - 1].s;
    ll right = cowsX[n - 1].f;
    for (ll i = n - 2; i >= 0; i--) {
        if (cowsX[i].s > highest) {
            highest = cowsX[i].s;
        } 
        
        if (cowsX[i].s < lowest) {
            lowest = cowsX[i].s;
        }

        ll height = highest - lowest;
        if (height == 0) {
            height = 1;
        }

        ll length = right - cowsX[i].f;
        if (length == 0) {
            length = 1;
        }

        rightRectangle[i] = height * length;
    }

    DEBUG(leftRectangle, rightRectangle);

    ll minArea = rightRectangle[0];
    f1r(i, 0, n) {
        if (leftRectangle[i] + rightRectangle[i + 1] < minArea) {
            minArea = leftRectangle[i] + rightRectangle[i + 1];
        }
        DEBUG(minArea);
    }

    /* Dividing the cows between the upper and lower half of the field */
    vector<ll> bottomRectangle(n);
    bottomRectangle[0] = 0; 
    left = cowsY[0].f;
    right = cowsY[0].f;
    lowest = cowsY[0].s;
    f1r(i, 1, n) {
        if (cowsY[i].f > right) {
            right = cowsY[i].f;
        } 
        
        if (cowsY[i].f < left) {
            left = cowsY[i].f;
        }

        ll length = right - left;
        if (length == 0) {
            length = 1;
        }

        ll height = cowsY[i].s - lowest;
        if (height == 0) {
            height = 1;
        }

        bottomRectangle[i] = height * length;
    }

    vector<ll> upperRectangle(n);
    upperRectangle[n - 1] = 0; 
    left = cowsY[n - 1].f;
    right = cowsY[n - 1].f;
    highest = cowsY[n - 1].s;
    for (ll i = n - 2; i >= 0; i--) {
        if (cowsY[i].f > right) {
            right = cowsY[i].f;
        } 
        
        if (cowsY[i].f < left) {
            left = cowsY[i].f;
        }

        ll length = right - left;
        if (length == 0) {
            length = 1;
        }

        ll height = highest - cowsY[i].s;
        if (height == 0) {
            height = 1;
        }

        upperRectangle[i] = height * length;
    }

    DEBUG(bottomRectangle, upperRectangle);

    f1r(i, 0, n) {
        if (bottomRectangle[i] + upperRectangle[i + 1] < minArea) {
            minArea = bottomRectangle[i] + upperRectangle[i + 1];
        }
        DEBUG(minArea);
    }

    cout << rightRectangle[0] - minArea << endl;
}