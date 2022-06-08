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

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=643
int main() {
    usaco("diamond");
    // io;

    cin >> n >> k;
    vector<ll> inp(n);

    f0r(i, n) {
        cin >> inp[i];
    }

    sort(inp.begin(), inp.end());
    DEBUG(inp);

    // Storing [min, num] where min is index of min val going down or curr - k and num is current index - min index or 
    // # of vals in the case if you were to go backwards from this index being the biggest
    vector<array<ll, 2> > backwards(n);

    // Similar to above but its [max, num] so it's going in the forward direction so what is the biggest the
    // case can be if this was the smallest case (curr + k) and then num of diamonds
    vector<array<ll, 2> > forwards(n);

    // Setting some initials
    backwards[0] = {0, 1};
    forwards[n - 1] = {n - 1, 1};

    f1r(i, 1, n) {
        ll min_index = backwards[i - 1][0];

        // Case where prev min is still big enough
        if (inp[i] - inp[min_index] <= k) {
            backwards[i] = {min_index, backwards[i - 1][1] + 1};
        } else {
            ll counter = 0;
            while(inp[i] - inp[min_index] > k) {
                min_index++; // Keep going forward until it's in k again
                counter++;
            }
            
            backwards[i] = {min_index, backwards[i - 1][1] - counter + 1};
        }
    }
    DEBUG(backwards);

    for(ll i = n - 2; i >= 0; i--) {
        ll max_index = forwards[i + 1][0];

        // Case where prev max is still small enough
        if (inp[max_index] - inp[i] <= k) {
            forwards[i] = {max_index, forwards[i + 1][1] + 1};
        } else {
            ll counter = 0;
            while(inp[max_index] - inp[i] > k) {
                max_index--; // Keep max index backwards until it's in k again
                counter++;
            }

            forwards[i] = {max_index, forwards[i + 1][1] - counter + 1};
        }
    }
    DEBUG(forwards);

    ll ret = 2;
    // Edge case if n = 1 or n = 0
    if (n <= 1) {
        ret = n;
    }

    ll best_backward = -1;
    vector<ll> best_backwards(n);
    f0r(i, n) {
        best_backward = max(best_backward, backwards[i][1]);

        best_backwards[i] = best_backward;
    }

    ll best_forward = -1;
    vector<ll> best_forwards(n);
    for (ll i = n - 1; i >= 0; i--) {
        best_forward = max(best_forward, forwards[i][1]);

        best_forwards[i] = best_forward;
    }
    
    
    f0r(i, n - 1) {
        ll curr_combo = best_backwards[i] + best_forwards[i + 1];
        DEBUG(i, curr_combo);
        ret = max(ret, curr_combo);  
    }

    cout << ret << endl;
}