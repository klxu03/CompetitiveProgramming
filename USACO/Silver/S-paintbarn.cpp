#include <bits/stdc++.h>

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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: http://www.usaco.org/index.php?page=viewproblem2&cpid=919 
int main() {
    usaco("paintbarn");
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> q >> k;

    vector<int[1002]> vec(1002);
    f0r(i, q) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        vec[x1][y1]++;
        vec[x2][y1]--;
        vec[x1][y2]--;
        vec[x2][y2]++;
    }

    // Setting the two edges up
    vector<int[1002]> paint(1002);
    ll prefix_sum = 0;
    f0r(i, 1002) {
        prefix_sum += vec[0][i];
        paint[0][i] = prefix_sum;
    }
    prefix_sum = 0;
    f0r(i, 1002) {
        prefix_sum += vec[i][0];
        paint[i][0] = prefix_sum;
    }

    f1r(i, 1, 1002) {
        f1r(j, 1, 1002) {
            paint[i][j] = vec[i][j] + paint[i - 1][j] + paint[i][j - 1] - paint[i - 1][j - 1];
        }
    }

    // f0r(i, 10) {
    //     f0r(j, 10) {
    //         cout << vec[9 - i][j] << ", ";
    //     }
    //     cout << endl;
    // }

    // DEBUG("---------");

    // f0r(i, 10) {
    //     f0r(j, 10) {
    //         cout << paint[9 - i][j] << ", ";
    //     }
    //     cout << endl;
    // }
    
    ll counter = 0;
    f0r(i, 1002) {
        f0r(j, 1002) {
            if (paint[i][j] == k) {
                counter++;
            }
        }
    }

    cout << counter << endl;
}