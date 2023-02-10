#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>
#define pii pair<int, int>

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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

#include <chrono> 
using namespace std::chrono; 
struct timer {
  high_resolution_clock::time_point begin;

  timer() {}
  timer(bool b) {
    if (b) start();
  }

  void start() {
    begin = high_resolution_clock::now();
  }

  void print() {
    cout << "Time taken: " << duration_cast<duration<double>>(high_resolution_clock::now() - begin).count() << " seconds" << endl;
  }

  double report() {
    return duration_cast<duration<double>>(high_resolution_clock::now() - begin).count();
  }
};
// Start of main put tin, end of main put tpr (tgt gives you value not printed)
#define tin timer __timer__(1);
#define tpr __timer__.print();
#define tgt __timer__.report()

ll q, Q, T, l, r, x, y, z;

void solve(); 

// Problem URL: 
int main() {
	io;
	long long test_cases = 1;
	// cin >> test_cases;
	
    for (int i = 0; i < test_cases; i++) {
		solve();
    }
}

ll n, s, k;

// when solving, lets double everything so 1/2 isnt a concern since doubled, just halve final answer
void solve() {
	cin >> n >> s >> k;
    s *= 2;
    k *= 2;
    vector<ll> inp(n);

    f0r(i, n) {
        cin >> inp[i];
    }

    f0r(i, n) {
        inp[i] *= 2;
    }

    sort(inp.begin(), inp.end());

    vector<pll> bounds(n); // f is left_bound, s is right_bound
    bounds[0] = {inp[0] - s/2, inp[0] + s/2};
    f1r(i, 1, n) {
        bounds[i] = {inp[i] - s/2, inp[i] + s/2};

        if (bounds[i].f < bounds[i - 1].s) {
            cout << -1 << endl;
            return;
        }
    }

    int counter; // counter is how you go into the center
    for (counter = 0; counter < n/2; counter++) {
        // keep going towards the center

        // do left one first:

        // check max amt can go left first is in max_dist
        ll max_dist = k/2;
        if (counter > 0) {
            max_dist = min(k/2, inp[counter] - bounds[counter - 1].s);
        }

        if (inp[counter] + max_dist > bounds[counter + 1].f) {
            max_dist = bounds[counter + 1].f - inp[counter];
        }
        bounds[counter] = {inp[counter] - max_dist, inp[counter] + max_dist};


        // right one:
        max_dist = k/2;
        int ind = n - counter - 1;
        if (counter > 0) {
            max_dist = min(k/2, bounds[ind + 1].f - inp[ind]);
        }

        if (inp[ind] - max_dist < bounds[ind - 1].s) {
            max_dist = inp[ind] - bounds[ind - 1].s;
        }
        bounds[ind] = {inp[ind] - max_dist, inp[ind] + max_dist};
    }

    // odd # of platforms, do you're best with the center one
    // handle the n == 1 case
    if (n == 1) {
        cout << k/2 << endl;
        return;
    }

    if (n % 2 == 1) {
        ll max_dist = k/2;
        max_dist = min(max_dist, inp[counter] - bounds[counter - 1].s, bounds[counter + 1].f - inp[counter]);
        bounds[counter] = {inp[counter] - max_dist, inp[counter] + max_dist};
    }

    DEBUG(bounds);

    ll ret = 0;
    f0r(i, n) {
        ret += bounds[i].s - bounds[i].f;
    }

    cout << ret/2 << endl;
}