//http://www.usaco.org/index.php?page=viewproblem2&cpid=811

#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)

#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
  cout << "["; 
  for(int i = 0; i < v.size(); i++) {
    if (i) cout << ", "; cout << v[i];
  } 
  return cout << "]";
}

int main() {
  ll n, b;
  cin >> n >> b;

  vector<ll> f(n), d(b), s(b); 
  f0r(i, n) {
    cin >> f[i];
  }

  f0r(i, b) {
    cin >> d[i] >> s[i];
  }

  vector<vector<bool>> dp(b, vector<bool>(n));
  dp[0][0] = true;

  f0r(y, b) {
    next:
    f0r(x, n) {
      f0r(x1, s[y]) {
        f0r(y1, y + 1) {
          if (dp[x - x1][y - y1]) {
            dp[x][y] = true;
            goto next;
          }
        }
      }
    }
  }

  ll ret = 252;
  f0r(y, b) {
    if (dp[n - 1][y]) {
      ret = y;
    }
  }

  cout << ret << endl;

  return 0;
}