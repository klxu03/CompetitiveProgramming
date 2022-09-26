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

ll n, q, Q, T, k, l, r, x, y, z, g;

ll solve(); 

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

	vector<ll> dfs(ll starting_node) {
		deque<int> dq;
		dq.push_front(starting_node);
        vector<ll> last_visited;
        fill(visited.begin(), visited.end(), false);
		visited[starting_node] = true;
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = true;
			DEBUG(current, dq, visited);

			if(adj[current].size() == 0) {
                last_visited.pb(current);
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
				if (i == adj[current].size() - 1) {
                    last_visited.pb(current);
                    dq.pop_front();
                }
			}
		}

        return last_visited;
	}

};


// Problem: https://cses.fi/problemset/task/1682
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void dfs(ll starting_node, vector<vector<ll> > &adj, vector<bool> &visited) {
	deque<int> dq;
	dq.push_front(starting_node);
	fill(visited.begin(), visited.end(), false);
	visited[starting_node] = true;

	while(!dq.empty()) {
		ll current = dq.front();
		visited[current] = true;

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
			if (i == adj[current].size() - 1) {
				dq.pop_front();
			}
		}
	}
}


ll solve() {
	cin >> n >> k;
	ll connected = -1, unconnected = -1;

	vector<vector<ll> > adj(n);
	vector<vector<ll> > rev_adj(n);
	vector<bool> visited(n, false);
	vector<bool> possible(n, false);

	f0r(i, k) {
		ll from, to;
		cin >> from >> to;
		from--; to--;
		adj[from].pb(to);
		rev_adj[to].pb(from);
	}

	DEBUG(adj, rev_adj);

	dfs(0, adj, visited);
	DEBUG(visited);
	f0r(i, visited.size()) {
		if(visited[i] == false) {
			connected = 1;
			unconnected = i + 1;
			break;
		}
	}

	if (connected != -1) {
        cout << "NO" << endl;
        cout << connected << " " << unconnected << endl;
		return 0;
    } 

	possible[0] = true;
	fill(visited.begin(), visited.end(), false);
	dfs(0, rev_adj, visited);
	DEBUG(visited);

	f0r(i, visited.size()) {
		if(visited[i] == false) {
			connected = i + 1;
			unconnected = 1;
			break;
		}
	}

	if (connected != -1) {
        cout << "NO" << endl;
        cout << connected << " " << unconnected << endl;
		return 0;
    } 

	cout << "YES" << endl;
	return -1;
}