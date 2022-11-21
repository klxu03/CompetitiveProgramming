#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
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

ll q, Q, T, k, l, r, x, y, z;

int n, m;
ll a, b;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	cin >> test_cases;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

vector<vector<pll> > adj; // adjacency neighbor vector going to be {other node, weight}
vector<ll> a_visited;
vector<ll> b_visited;

void a_bfs() {
	deque<ll> dq;
	dq.pb(a);

	a_visited[a] = 0;
	while(!dq.empty()) {
		ll curr = dq.front();
		dq.pop_front();

		for(pll other: adj[curr]) {
			if (a_visited[other.f] == -1 && other.f != b) {
				a_visited[other.f] = a_visited[curr] ^ other.s;
				dq.pb(other.f);
			}
		}
	}
}

void b_bfs() {
	deque<ll> dq;
	dq.pb(b);

	b_visited[b] = 0;
	while(!dq.empty()) {
		ll curr = dq.front();
		dq.pop_front();

		for(pll other: adj[curr]) {
			if (b_visited[other.f] == -1) {
				b_visited[other.f] = b_visited[curr] ^ other.s;
				dq.pb(other.f);
			}
		}
	}
}

void solve() {
	cin >> n >> a >> b;
	a--; b--;
	adj = vector<vector<pll>>(n);
	a_visited = vector<ll>(n, -1);
	b_visited = vector<ll>(n, -1);

	f0r(i, n - 1) {
		ll x, y, w;
		cin >> x >> y >> w;
		adj[x - 1].pb({y - 1, w});
		adj[y - 1].pb({x - 1, w});
	}

	a_bfs();
	b_bfs();

	// a_visited[a] = -1;
	b_visited[b] = -1;
	DEBUG(a_visited);
	DEBUG(b_visited);

	set<ll> in_a;
	f0r(i, a_visited.size()) {
		if (a_visited[i] != -1) {
			in_a.insert(a_visited[i]);
		}
	}

	bool valid = false;
	f0r(i, b_visited.size()) {
		if (in_a.find(b_visited[i]) != in_a.end()) {
			valid = true;
			break;
		}
	}

	if (valid) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
}