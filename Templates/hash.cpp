#include <bits/stdc++.h>
#include <chrono> 
 
using namespace std;
using namespace std::chrono; 
 
// #pragma GCC target ("avx2")
// #pragma GCC optimization ("O3")
// #pragma GCC optimization ("unroll-loops")
 
#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define f0rd(a, b) for (long long a = b; a >= 0; a--)
#define f1rd(a, b, c) for (long long a = b; a >= c; a--)
#define ms(arr, v) memset(arr, v, sizeof(arr))
#define pb push_back
#define io {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);}
#define mp make_pair
#define f first
#define s second
#define presum(p, a, n) {p[0] = a[0]; for (int i = 1; i < n; i++) p[i] = a[i] + p[i-1];}
#define all(v) v.begin(), v.end()
#define readgraph(list, edges) for (int i = 0; i < edges; i++) {int a, b; cin >> a >> b; a--; b--; list[a].pb(b); list[b].pb(a);}
#define ai(a, n) for (int ele = 0; ele < n; ele++) cin >> a[ele];
#define ain(a, lb, rb) for (int ele = lb; ele <= rb; ele++) cin >> a[ele];
#define ao(a, n) {for (int ele = 0; ele < n; ele++) { if (ele) cout << " "; cout << a[ele]; } cout << '\n';}
#define aout(a, lb, rb) {for (int ele = lb; ele <= rb; ele++) { if (ele > lb) cout << " "; cout << a[ele]; } cout << '\n';}
typedef long long ll;
typedef double ld;
typedef long double lld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
 
template<typename A, typename B> ostream& operator<<(ostream &cout, pair<A, B> const &p) { return cout << "(" << p.f << ", " << p.s << ")"; }
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
  cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}
// template<typename A, typename B> ll max(A x, B y) {
//   return x > y ? x : y;
// }
// template<typename A, typename B> ll min(A x, B y) {
//   return x < y ? x : y;
// }
 
mt19937 rng(steady_clock::now().time_since_epoch().count());
/* usage - just do rng() */
 
void usaco(string filename) {
  #pragma message("be careful, freopen may be wrong")
	freopen((filename + ".in").c_str(), "r", stdin);
	freopen((filename + ".out").c_str(), "w", stdout);
}
 
ll kk[10] = {
  89, 
  101, 
  189,
  94,
  621,
  (ll)rng() % 1000 + 1051,
  (ll)rng() % 2000 + 2761,
  (ll)rng() % 4000 + 4441,
  (ll)rng() % 8000 + 8111,
  (ll)rng() % 16000 + 18883
};

ll primes[10] = {
  533000401,
  735632791,
  776531419,
  797003413,
  1062599999,
  1047899999,
  1031999999, 
  1027799999,
  1018199999,
  1000000007
};

struct string_hash {
  int len;
  ll mod, poly, inv;
  vector<ll> prefix;
  vector<ll> invs;
  
  void init(int n, string s, ll k = 89, ll m = 1000000007) {
    mod = m;
    poly = k;
    prefix = vector<ll>(n);
    invs = vector<ll>(n);

    inv = minv(k);

    if (n > 0) {
      invs[0] = 1;
      for (int i = 1; i < n; i++) {
        invs[i] = (invs[i - 1] * inv) % mod;
      }

      ll x = 1;
      prefix[0] = (s[0] - '0' + 1);
      for (int i = 1; i < n; i++) {
        x = (x * k) % mod;
        prefix[i] = (prefix[i - 1] + x * (s[i] - '0' + 1)) % mod;
      }
    }

    len = n;
  }

  void extend(string next) {
    int x = next.length();
    for (int i = 0; i < x; i++) {
      if (i + len == 0) {
        invs.push_back(1);
      } else {
        invs.push_back((invs[i + len - 1] * inv) % mod);
      }      
    }

    ll p = mpow(poly, len);
    for (int i = 0; i < x; i++) {
      if (i + len == 0) {
        prefix.push_back(next[i] - '0' + 1);
      } else {
        prefix.push_back((prefix[i + len - 1] + p * (next[i] - '0' + 1)) % mod);
      }
      p = (p * poly) % mod;
    }

    len += x;
  }
  
  void kill(int sz) { // remove last [sz] characters
	  for (int i = 0; i < sz; i++) {
		  invs.pop_back();
		  prefix.pop_back();
	  }
	  
	  len -= sz;
  }

  ll get_hash(int left, int right) {
    if (left == 0) return prefix[right];
    return ((prefix[right] - prefix[left - 1] + mod) * invs[left]) % mod;
  }

  ll mpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
      if (exp % 2 == 1) {
          res = (res * base) % mod;
      }
      exp >>= 1;
      base = (base * base) % mod;
    }
    return res;
  }
  ll minv(ll base) {
    return mpow(base, mod - 2);
  }
};

template<int K>
struct multihash {
  string_hash sh[K];
 
  void init(int n, string s) {
    for (int i = 0; i < K; i++) {
      sh[i].init(n, s, kk[9 - i], primes[9 - i]);
    }
  }
  
  void extend(string s) {
	  for (int i = 0; i < K; i++) {
		  sh[i].extend(s);
	  }
  }
  
  void kill(int x) {
	  for (int i = 0; i < K; i++) {
		  sh[i].kill(x);
	  }
  }
 
  array<ll, K> get_hash(int l, int r) {
    array<ll, K> ret;
    for (int i = 0; i < K; i++) {
      ret[i] = sh[i].get_hash(l, r);
    }
    return ret;
  }
};

ll n, m, k, q, Q, T, l, r, x, y, z;
int a[500005];
int b[500005];
string s, t;
// ll ans = 0;

multihash<2> sh, th;

int main() {
  io;
  // freopen("case", "r", stdin);
  // freopen("test.txt", "r", stdin);
  // freopen("case", "w", stdout);

  usaco("censor");

  cin >> s >> t;
  sh.init(0, "");
  th.init(t.length(), t);
  array<ll, 2> tv = th.get_hash(0, t.length() - 1);

  string ns = "";
  for (char c: s) {
    ns.push_back(c);
    sh.extend(string(1, c));
    if (ns.length() >= t.length()) {
      if (sh.get_hash(ns.length() - t.length(), ns.length() - 1) == tv) {
        sh.kill(t.length());
        for (int i = 0; i < t.length(); i++) ns.pop_back();
      }
    }
  }

  cout << ns << endl;
}