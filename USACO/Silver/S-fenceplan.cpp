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
	vector<ll> visited; // visited nodes

	Graph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		visited = vector<ll>(n, 0);
	}

    void init(ll edges) {
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

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

	void dfs(ll starting_node, ll& group) {
		deque<int> dq;
		dq.push_front(starting_node);
        // fill(visited.begin(), visited.end(), false);
		visited[starting_node] = group;
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = group;
			DEBUG(current, dq, visited);

			if(adj[current].size() == 0) {
				dq.pop_front();
			}

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				// DEBUG(i, neighbor);
				if(visited[neighbor] == 0) {
					dq.push_front(neighbor);
					break;
				} 
				/* If I've skipped through all and none of 
				the neighbors haven't been visited */
				if (i == adj[current].size() - 1) dq.pop_front();
			}
		}

		group++;
	}

};

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=944
int main() {
    usaco("fenceplan");
    // io;

    cin >> n >> k;
    vector<pair<ll, ll> > inp(n); // x, y, p for power of walkie talkie

    f0r(i, n) {
        ll x, y;
        cin >> x >> y;
		inp[i] = mp(x, y);
    }
    DEBUG(inp);
	Graph g1(n, k, true);
	
	g1.init(k);
    DEBUG(g1.adj);
    
	ll bool_counter = 0;
	ll group_counter = 1;
	while(bool_counter < n) {
		if(g1.visited[bool_counter] == 0) {
			g1.dfs(bool_counter, group_counter);
		} else {
			bool_counter++;
		}
	}
	group_counter--;

	DEBUG(g1.visited);
	vector<vector<pair<ll, ll> > > groups(group_counter); 
	f0r(i, n) {
		groups[g1.visited[i] - 1].pb(inp[i]);
	}
	DEBUG(groups);

	vector<ll> coords(4); // top, right, bottom, left
	ll min_perimeter = LLONG_MAX;
	f0r(i, group_counter) {
		// stub
		coords = {-1, -1, LLONG_MAX, LLONG_MAX};
		f0r(j, groups[i].size()) {
			pair<ll, ll> curr = groups[i][j];
			if(curr.f > coords[0]) {
				coords[0] = curr.f;
			} 
			if (curr.f < coords[2]) {
				coords[2] = curr.f;
			}

			if (curr.s > coords[1]) {
				coords[1] = curr.s;
			}

			if (curr.s < coords[3]) {
				coords[3] = curr.s;
			}
		}

		ll perimeter = coords[1] - coords[3] + coords[0] - coords[2];
		perimeter *= 2;

		if (perimeter < min_perimeter) min_perimeter = perimeter;
	}

	cout << min_perimeter << endl;
}
