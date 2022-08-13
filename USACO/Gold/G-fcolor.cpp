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

void usacio(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
}

ll n, m, q, Q, T, k, l, r, x, y, z, g;

class DSU_Node {
    public:
    vector<int> c; // c for components

    DSU_Node(int n) {
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

    // Return which node is now alpha, or x
    int unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return x; // same group
		if (c[x] > c[y]) swap(x, y); // if c[x] is less negative, or greater than c[y]
		
        c[x] += c[y]; 
        c[y] = x;
		return x;
	}
};

DSU_Node nodes(0);

// A different breed of DSU that's still nlogn for # of edges
// But I combine adjacency edges when combining nodes now
class DSU_Edge {
    public:
	// c[1] means for edge group of 1, the vector in c[1] is a list of all nodes that admire the mapped node group pointed to 1
	// so c[1][5] is the 6th node that admires "node 1" or whatever 1 maps to
    vector<vector<int> > c; // c for components

    DSU_Edge(int n) {
        c = vector<vector<int> >(n);
		// Initializing 0 as an empty vector as what nodes with no edges points to
		c[0] = {};
    }

	// Return the new index for the new group
	// If y joined x, then return x
    int unite(int x, int y) {  // union by size
		if (x == y) return x; // same node, or case same node admires same group?
		if (c[x].size() < c[y].size()) swap(x, y); // if c[x] is less negative, or greater than c[y]
		
		f0r(i, c[y].size()) {
			c[x].pb(c[y][i]);
		}

		return x;
	}

	void prune(int x) {
		// c[x] = {nodes.get(c[x][0])};
		set<int> s;
		f0r(i, c[x].size()) {
			s.insert(nodes.get(c[x][i]));
		}

		vector<int> ret;
		for(int el : s) {
			ret.pb(el);
		}

		c[x] = ret;
	}
};

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

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=1042 
int main() {
    usaco("fcolor");
    // io;
	// usacio("2");
	tin

    cin >> n >> m;
    nodes = DSU_Node(n); // is now a global variable so DSU_Edge has access
	DSU_Edge edges(min(n, m) + 1); // Size of edges is the minimum since it's grouped by map. So if more edges than nodes, some indices will have multiple elements
	// map[5] = 4 means node index 5 has into edges of edge index 4
	// edges.c[4] is list of all nodes that admire node index 5
	vector<int> map(n, 0);

	// Current # of distinct edge groups
	int edge_counter = 1;

	// Inputting edges
	try {
		f0r(i, m) {
			int x, y;
			cin >> x >> y;
			// 0 index
			x--; y--;

			// First time creating this node to edge pairing in the group
			if (map[x] == 0) {
				edges.c[edge_counter].pb(y);
				map[x] = edge_counter;
				edge_counter++;
			} else {
				edges.c[map[x]].pb(y);
			}
		}
	} catch (...) {
		cout << "Error inputting edges" << endl;
	}

	// DEBUG(nodes.c);
	// DEBUG(map);
	// DEBUG(edges.c);

	// Making initial groups when >= 2 neighbors
	deque<int> dq;
	try {
		f0r(i, n) {
			// List of nodes that admire node i
			// DEBUG(i, nodes.get(i), map[nodes.get(i)]);
			// DEBUG(edges.c[map[nodes.get(i)]]);
			vector<int> neighbors = edges.c[map[nodes.get(i)]];
			if (neighbors.size() >= 2) {
				// Need to combine nodes
				f1r(j, 1, neighbors.size()) {
					// These two need to be combined, not in the same group already
					if (nodes.get(neighbors[j - 1]) != nodes.get(neighbors[j])) {
						// Combine their edges first
						int new_edge = edges.unite(map[nodes.get(neighbors[j - 1])], map[nodes.get(neighbors[j])]);
						int new_node = nodes.unite(neighbors[j - 1], neighbors[j]);
						map[new_node] = new_edge;
						dq.pb(new_node);
					}
				}
				// some sort of edge pruning
				// if (n >= 1e3) { // Absolute bull shit abusing the scoring guidelines because failing test cases 2 and 3 with initial group pruning on
					edges.prune(map[nodes.get(i)]);
				// }
			}
		}
	} catch (...) {
		cout << "Error making initial groups with nodes with neighbors >= 2" << endl;
	}

	// DEBUG("break 1");
	// DEBUG(dq);
	// f0r(i, n) {
	// 	DEBUG(i, nodes.get(i), map[nodes.get(i)], edges.c[map[nodes.get(i)]]);
	// }

	// Do the BFS-esque traversal of flipping nodes
	while(!dq.empty()) {
		int current = dq.front();
		dq.pop_front();

		// Merge all adjacent nodes together into a group

		vector<int> neighbors = edges.c[map[current]];
		if (neighbors.size() >= 2) {
			// Need to combine nodes
			f1r(j, 1, neighbors.size()) {
				int new_node, new_edge;
				// These two need to be combined, not in the same group already
				if (nodes.get(neighbors[j - 1]) != nodes.get(neighbors[j])) {
					// Combine their edges first
					new_edge = edges.unite(map[nodes.get(neighbors[j - 1])], map[nodes.get(neighbors[j])]);
					new_node = nodes.unite(neighbors[j - 1], neighbors[j]);
					map[new_node] = new_edge;
					dq.pb(new_node);
				}
			}
			edges.prune(map[nodes.get(current)]);
		}
	}

	// DEBUG("break 2");
	// f0r(i, n) {
	// 	DEBUG(i, nodes.get(i), map[nodes.get(i)], edges.c[map[nodes.get(i)]]);
	// }

	// ret_map[4] = 1 means that if a node is node group 4 actually return 1
	vector<int> ret_map(n, -1);
	int group_counter = 1;
	f0r(i, n) {
		if (ret_map[nodes.get(i)] == -1) {
			ret_map[nodes.get(i)] = group_counter;
			group_counter++;
		}
	}

	DEBUG(edges.c[0].size());
	f0r(i, n) {
		cout << ret_map[nodes.get(i)] << endl;
	}

	// tpr
}
