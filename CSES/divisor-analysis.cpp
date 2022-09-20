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

ll q, Q, T, k, l, r, x, y, z, g;
ll n, m;

ll const MOD = (ll) 1e9 + 7;

void usacio(string filename) {
    io;
    freopen((filename + ".txt").c_str(), "r", stdin);
}

// Binary exponentiation with mod
// O(logn) iteratively give base^expo % mod
ll modpow(ll base, ll expo, ll mod) {
    ll result = 1;
    while (expo) {
      if (expo & 1) {
        result *= base;
        result %= mod;
      }
        
      expo >>= 1;
      base *= base;
      base %= mod;
    }

    return result;
}

//Problem URL: https://cses.fi/problemset/task/2182
int main() {
    // io;
    usacio("test_input");
    cin >> n;
    vector<pll> inp(n);
    f0r(i, n) {
        ll f, s;
        cin >> f >> s;
        inp[i] = mp(f, s);
    }

    ll number = 1, sum = 1, product = 1;

    ll og_num = 1; // x^k multiplied by each other 
    f0r(i, n) {
        number *= inp[i].s + 1;
        number %= MOD;
        og_num *= modpow(inp[i].f, inp[i].s, MOD); 
        og_num %= MOD;
    }
    DEBUG(og_num, number, number/2, (ll) sqrt(og_num));

    if (number % 2 == 0) {
        product = modpow(og_num, number/2, (ll) 1e9 + 7);
    } else {
        product = modpow(og_num, number/2, (ll) 1e9 + 7);

        ll sqrt = 1;
        f0r(i, n) {
            sqrt *= modpow(inp[i].f, inp[i].s/2, (ll) 1e9 + 7);
            sqrt %= MOD;
        }
        product *= sqrt;
        product %= MOD;
    }

    f0r(i, n) {
        sum *= (modpow(inp[i].f, inp[i].s + 1, MOD) - 1)/(inp[i].f - 1);
        sum %= MOD;
    }

    cout << number << " " << sum << " " << product << endl;
}