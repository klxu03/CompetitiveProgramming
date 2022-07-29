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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

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
		visited = vector<ll>(n, false);
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

    void insert_edge(ll from, ll to) {
        adj[from].pb(to);
        if (undirected) {
            adj[to].pb(from);
        }
        e++;
    }

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

    // Modified BFS to determine shortest path back to the starting_node
    ll bfs(ll starting_node) {
		deque<int> dq;
		dq.push_back(starting_node);

		fill(visited.begin(), visited.end(), -1);
		visited[starting_node] = 0;
		vector<ll> prev(n, -1);
		prev[starting_node] = -2;
		ll ret = LLONG_MAX;

		bool valid = true;
		while(!dq.empty() && valid) {
			ll current = dq.front();
			dq.pop_front();
			// DEBUG(current);

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == -1) {
					visited[neighbor] = visited[current] + 1;
					prev[neighbor] = current;
					dq.push_back(neighbor);
				} else if (visited[neighbor] != -1 && prev[current] != neighbor) {
					// We have found a cycle
					DEBUG("found a cycle");
					DEBUG(neighbor, current, prev[current]);
					DEBUG(visited[neighbor], visited[current]);
					DEBUG(ret, visited[neighbor] + visited[current] + 1);
					// Add 1 since you are connecting two groups with one extra connection
					ret = min(ret, visited[neighbor] + visited[current] + 1);
				} 
			}
		}

		DEBUG(ret);
		return ret;
    }
};


// Problem: https://cses.fi/problemset/task/1707 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n >> m;

    Graph g(n, m, true);
    g.init_adj();

	ll ret = LLONG_MAX;
	f0r(i, n) {
		ll curr = g.bfs(i);
		ret = min(ret, curr);
	}
	
	if (ret == LLONG_MAX) {
		cout << -1 << endl;
	} else {
		cout << ret << endl;
	}
}