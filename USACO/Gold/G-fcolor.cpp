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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, m, q, Q, T, k, l, r, x, y, z, g;

class DSU {
    public:
    vector<int> c; // c for components

    DSU(int n) {
        c = vector<int>(n, -1);
    }

    // get representive component (uses path compression)
	int get(int x) { 
        return c[x] < 0 ? x : c[x] = get(c[x]); 
    }

    bool same_set(int a, int b) { 
        return get(a) == get(b); 
    }

    int size(int x) { 
        return -c[get(x)]; 
    }

    bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false; // same group
		if (c[x] > c[y]) swap(x, y); // if c[x] is less negative, or greater than c[y]
		
        c[x] += c[y]; 
        c[y] = x;
		return true;
	}
};

class UnweightedGraph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<vector<ll> > into; // into neighbor vector (opposite of adjacency)
	vector<ll> visited; // visited nodes

	UnweightedGraph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		into = vector<vector<ll> >(n);
		visited = vector<ll>(n, false);
	}

	void init_adj() {
		f0r(i, e) {
			ll n1, n2; // n1 for node1
			cin >> n1 >> n2;
            into[n1 - 1].pb(n2 - 1);
			adj[n2 - 1].pb(n1 - 1);
		}
	}

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

	void display_into() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, into[i]);
		}
		DEBUG("]");
	}

	void dfs(ll starting_node) {
		deque<int> dq;
		dq.push_front(starting_node);
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = true;

			if(adj[current].size() == 0) {
				dq.pop_front();
			}

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == false) {
					dq.push_front(neighbor);
					break;
				} 
				/* If I've skipped through all and none of 
				the neighbors haven't been visited */
				if (i == adj[current].size() - 1) dq.pop_front();
			}
		}
	}

    void bfs(ll starting_node) {
		deque<int> dq;
		dq.push_back(starting_node);
		visited[starting_node] = true;

		bool valid = true;
		while(!dq.empty() && valid) {
			ll current = dq.front();
			dq.pop_front();

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == false) {
					visited[neighbor] = true;
					dq.push_back(neighbor);
				} 
			}
		}
    }

	void shortest_distance(ll starting_node) {
		deque<int> dq;
		dq.push_back(starting_node);
		visited[starting_node] = true;

        vector<ll> dist = vector<ll>(n);

		bool valid = true;
		while(!dq.empty() && valid) {
			ll current = dq.front();
			dq.pop_front();

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				if(visited[neighbor] == false) {
					visited[neighbor] = true;
					dq.push_back(neighbor);
                    dist[neighbor] = dist[current] + 1;
				} 
			}
		}
    }
};

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=1042 
int main() {
    // usaco("fcolor");
    io;

    cin >> n >> m;
    DSU d(n);
    UnweightedGraph g(n, m, false);
    g.init_adj();

    g.display();
    g.display_into();

    // Initially setting colors together for mutual admiration
    f0r(i, n) {
        if (g.into[i].size() >= 2) {
            f1r(j, 1, g.into[i].size()) {
                d.unite(g.into[i][j - 1], g.into[i][j]);
            }
        }
    }

    // Initially setting colors if a cow admires multiple other cows
    // Observation I thought up at midnight, might not be correct and an edge case if wrong
    f0r(i, n) {
        if (g.adj[i].size() >= 2) {
            f1r(j, 1, g.adj[i].size()) {
                d.unite(g.adj[i][j - 1], g.adj[i][j]);
            }
        }
    }

    // For each colored node, add its BFS "neighbors" of cows admiring those colored cows
    // Queue for the BFS
    deque<int> dq;
    // Set keeping track of nodes already added into the dq
    unordered_set<int> s;

    f0r(i, n) {
        // Node i is already in a group
        if(d.c[i] != -1) {
            DEBUG(i, d.size(i), d.get(i), g.into[i]);
            vector<ll> neighbors = g.into[i];
            DEBUG(neighbors);
            f0r(j, neighbors.size()) {
                // if neighbors[j] isn't already colored and hasn't already been added to dq, add to dq
                if (d.c[neighbors[j]] != -1 && s.find(neighbors[j]) == s.end()) {
                    dq.pb(neighbors[j]);
                    s.insert(neighbors[j]);
                }
            }
        }
    }

    while(!dq.empty()) {
        int curr = dq.front();
        dq.pop_front();
        // do stuff, sample is node 8
        // make node 8 the same color as any node that's pointing to a node with the same color as node 5

        // the color curr admires (is pointing to)
        int color = d.get(curr);

        // Erasing from hash set at end in case cow likes itself, don't want to re-add
        s.erase(s.find(curr));
    }

    DEBUG(d.c);
    DEBUG(dq, s);
}
