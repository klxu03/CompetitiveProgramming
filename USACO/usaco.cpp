#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>
#include <deque>
#include <climits>

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

ll n, q, Q, T, k, l, r, x, y, z, g;

class Graph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<bool> visited; // visited nodes

	Graph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		visited = vector<bool>(n);
	}

    void init_adj(ll edges) {
		f0r(i, e) {
			ll n1, n2; // n1 for node1
			cin >> n1 >> n2;
			adj[n1 - 1].pb(n2 - 1);
			if(undirected) {
				adj[n2 - 1].pb(n1 - 1);
			}
		}
    }

    void add_adj(vector<vector<ll> > &adj) {
        this->adj = adj;
    }

	void init_adj() {
		f0r(i, e) {
			ll n1, n2; // n1 for node1
			cin >> n1 >> n2;
			adj[n1 - 1].pb(n2 - 1);
			if(undirected) {
				adj[n2 - 1].pb(n1 - 1);
			}
		}
	}

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

	void dfs(ll starting_node) {
		deque<int> dq;
		dq.push_front(starting_node);
		visited[starting_node] = true;
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = true;
			// DEBUG(current, dq, visited);

			if(adj[current].size() == 0) {
				dq.pop_front();
			}

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				// DEBUG(i, neighbor);
				if(!visited[neighbor]) {
					dq.push_front(neighbor);
					break;
				} 
				/* If I've skipped through all and none of 
				the neighbors haven't been visited */
				if (i == adj[current].size() - 1) dq.pop_front();
			}
		}
	}

};

bool cmp(array<ll, 3>& x, array<ll, 3>&y) {
	return x[2] > y[2];
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=992 
int main() {
    // usaco("wormsort");
    io;

	cin >> n >> k;
	vector<ll> cows(n);
	f0r(i, n) {
		ll inp;
		cin >> inp;
		inp--; // 0 indexing
		cows[i] = inp;
	}

	vector<array<ll, 3> > portals(k);
	f0r(i, k) {
		ll x, y, w;
		cin >> x >> y >> w;
		x--; y--; // 0 indexing
		portals[i] = {x, y, w};
	}

	sort(portals.begin(), portals.end(), cmp);
	DEBUG(cows, portals);

	set<pair<ll, ll> > changes;
	f0r(i, n) {
		if(cows[i] != i) {
			pair<ll, ll> p = mp(i, cows[i]);
			// This prevents the same entry, (1, 3) and (3, 1) being needed are both
			// the same, we need a connection between 1 and 3
			if (i > cows[i]) { 
				p.f = cows[i];
				p.s = i;
			}
			changes.insert(p);
		}
	}
	DEBUG(changes);
	if(changes.size() == 0) {
		cout << -1 << endl;
		return 0;
	}

	

}