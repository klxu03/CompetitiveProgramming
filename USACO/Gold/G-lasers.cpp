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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

void usacio(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
}

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

map<pll, int> coord_to_node; // Full coordinate to node, like key <3, 2>, value is node_counter
map<int, int> x_to_node;  // <5, x> to node, where 5 (or first int) is fixed and x can be anything, value is node_counter
map<int, int> y_to_node;  // <x, 5> to node, where y (or first int) is fixed and x can be anything

class UnweightedGraph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<pair<int, int>> > adj; // adjacency neighbor vector, <node, weight>
	vector<ll> visited; // visited nodes

	UnweightedGraph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<pair<int, int>> >(n);
		visited = vector<ll>(n, false);
	}

    void insert_edge(ll from, ll to, bool one) {
        if (one) {
            adj[from].pb({to, 1});
        } else {
            adj[from].pb({to, 0});
        }
    }

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

	ll shortest_distance(ll starting_node, ll ending_node) {
        DEBUG(starting_node, ending_node);
		deque<int> dq;
		dq.push_back(starting_node);
		visited[starting_node] = true;

        vector<ll> dist = vector<ll>(n, 0);

		bool valid = true;
		while(!dq.empty() && valid) {
			ll current = dq.front();
			dq.pop_front();
            DEBUG(current, adj[current]);

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i].f;
				if(visited[neighbor] == false) {
					visited[neighbor] = true;
                    // 1 BFS
                    if (adj[current][i].s == 1) {
                        dq.push_back(neighbor);
                    } else {
                        // 0 BFS
                        dq.push_front(neighbor);
                    }

                    dist[neighbor] = dist[current] + adj[current][i].s;
				} 
			}
            DEBUG(dist);
		}

        return dist[ending_node];
    }
};


ll q, Q, T, k, l, r, x, y, z, g;
int n, m;

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=671 
int main() {
    usaco("lasers");
	// usacio("lasers");
    // io;

    cin >> n;
    pll start, end;
    cin >> x >> y;
    start = {x, y};
    cin >> x >> y;
    end = {x, y}; 

    vector<pll> inp(n + 2);
    f0r(i, n) {
        cin >> x >> y;
        inp[i] = {x, y};
    }
    inp[n] = start;
    inp[n + 1] = end;
    sort(inp.begin(), inp.end());

    // Fill in coord_to_node
    int node_counter = 0;
    f0r(i, n + 2) {
        coord_to_node[inp[i]] = node_counter;
        node_counter++;
    }

    // Fill in x_to_node map
    f0r(i, n + 2) {
        if (x_to_node.count(inp[i].f) == 0) {
            // not exist
            x_to_node[inp[i].f] = node_counter;
            node_counter++;
        }
    }

    // Fill in y_to_node map
    f0r(i, n + 2) {
        if (y_to_node.count(inp[i].s) == 0) {
            // not exist
            y_to_node[inp[i].s] = node_counter;
            node_counter++;
        }
    }

    UnweightedGraph g(node_counter, 0, false);
    // Add edges in the graph
    f0r(i, n + 2) {
        x = inp[i].f;
        y = inp[i].s;
        
        // X
        g.insert_edge(coord_to_node[inp[i]], x_to_node[x], true);
        g.insert_edge(x_to_node[x], coord_to_node[inp[i]], false);

        // Y
        g.insert_edge(coord_to_node[inp[i]], y_to_node[y], true);
        g.insert_edge(y_to_node[y], coord_to_node[inp[i]], false);
    }

    // DEBUG(coord_to_node);
    // DEBUG(x_to_node);
    // DEBUG(y_to_node);
    // g.display();

    ll ret = g.shortest_distance(coord_to_node[start], coord_to_node[end]);
    cout << ret - 1 << endl;
}
