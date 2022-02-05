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
#define pll pair<ll, ll>

/* For Debugging Purposes */
// #ifdef LOCAL
// #define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
// #else
#define DEBUG(...) 6
// #endif

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

class Graph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<ll> visited; // visited nodes

	Graph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		visited = vector<ll>(n, -1);
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

	void dfs(ll starting_node, ll group_counter) {
		deque<int> dq;
		dq.push_front(starting_node);
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = group_counter;

			if(adj[current].size() == 0) {
				dq.pop_front();
			}

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == -1) {
					dq.push_front(neighbor);
					break;
				} 
				/* If I've skipped through all and none of 
				the neighbors haven't been visited */
				if (i == adj[current].size() - 1) dq.pop_front();
			}
		}
	}

    bool bfs(ll starting_node) {
		deque<int> dq;
		dq.push_back(starting_node);

		ll group = 0;
		bool possible = true;
		visited[starting_node] = group;

		bool valid = true;
		while(!dq.empty() && valid) {
			DEBUG(visited);
			ll current = dq.front();
			dq.pop_front();
			group = (visited[current] + 1) % 2;

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == -1) {
					visited[neighbor] = group;
					dq.push_back(neighbor);
				} else if (visited[neighbor] != group) {
					DEBUG("not possible", group, current, neighbor);
					possible = false;
					break;
				}
			}
		}

		return possible;
    }

};

ll n, q, Q, T, k, l, r, x, y, z, g;

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=920 
int main() {
    usaco("revegetate");
    // io;

	cin >> n >> k;
	vector<pll > same;
	vector<pll > diff;

	f0r(i, k) {
		string s; ll t1, t2;
		cin >> s >> t1 >> t2;
		t1--; t2--;

		if (s == "S") {
			same.pb(mp(min(t1, t2), max(t1, t2)));
		} else {
			diff.pb(mp(min(t1, t2), max(t1, t2)));
		}
	}
	DEBUG(same, diff);

	Graph g_same(n, same.size(), true);
	vector<vector<ll> > adj_same(n);
	f0r(i, same.size()) {
		adj_same[same[i].f].pb(same[i].s);
		adj_same[same[i].s].pb(same[i].f);
	}
	DEBUG(adj_same);

	g_same.add_adj(adj_same);

	ll group_counter = 0;
	f0r(i, n) {
		if(g_same.visited[i] == -1) {
			g_same.dfs(i, group_counter);
			group_counter++;
		}
	}
	DEBUG(g_same.visited, group_counter);

	/* If node 2 and 3 are in the same group,they are effectively 
	one big node if they have the same g_same.visited[i] value */

	Graph g_diff(group_counter, diff.size(), true);
	vector<vector<ll> > adj_diff(group_counter);
	f0r(i, diff.size()) {
		ll prev = diff[i].f;
		ll aft = diff[i].s;
		adj_diff[g_same.visited[diff[i].f]].pb(g_same.visited[diff[i].s]);
		adj_diff[g_same.visited[diff[i].s]].pb(g_same.visited[diff[i].f]);
	}
	DEBUG(adj_diff);
	g_diff.add_adj(adj_diff);

	ll counter = 0;
	bool possible = true;
	f0r(i, group_counter) {
		if (g_diff.visited[i] == -1) {
			DEBUG(g_diff.visited);
			possible = g_diff.bfs(i) && possible;
			counter++;
		}
	}
	DEBUG(g_diff.visited);
	DEBUG(counter, possible);
	
	if(possible) {
		cout << 1;
		f0r(i, counter) {
			cout << 0;
		}
	} else {
		cout << 0;
	}
	cout << endl;

	// cout << counter << endl;
}

ll binary_search(ll lo, ll hi, bool works) {
	ll mid = (lo + hi + 1)/2;

	// Binary search part
	DEBUG(lo, hi, mid, works);
	if(works) {
		if(hi == mid) {
			hi--;
		} else {
			hi = mid;
		}
	} else {
		lo = mid;
	}
}
