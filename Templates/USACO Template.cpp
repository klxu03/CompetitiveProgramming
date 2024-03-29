#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>
#define pii pair<int, int>

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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

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

ll q, Q, T, k, l, r, x, y, z;
int n, m;

//Problem URL: 
int main() {
    // usaco("testCases");
	usacio("testCase");
    // io;

}

// Instead of a pair, use array<int, 2>

// Sorting a vector descendingly
// sort(vec.begin(), vec.end(), greater<ll>());

// Sorting a vector of pairs ascendingly based on second
// sort(inp.begin(), inp.end(), [](pll& x, pll& y) {
//     return x.s < y.s;
// });

class UnweightedGraph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<ll> visited; // visited nodes

	UnweightedGraph(ll nodes, ll edges, bool undirected) {
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

// Scuffed PQ so I can iterate through a pq
// Right after declare the PQ right the line below with this pasted in template above WeightedGraph
// vector<pair<ll, int>> &scuffed_pq = Container(pq);
template <class T, class S, class C>
S& Container(priority_queue<T, S, C>& q) {
    struct HackedQueue : private priority_queue<T, S, C> {
        static S& Container(priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
    return HackedQueue::Container(q);
}

class WeightedGraph {
    public:
    int nodes; // # of nodes
    int edges; // # of edges
    bool undirected;
    vector<vector<pair<int, int>>> adj; // adjacency neighbor vector
    // pair<first, second> = adj[5][0] where first is node 5's 1st neighbors pointed to node, and second is the cost
    vector<ll> dist; // distance to get to this node
    vector<int> prev;

    WeightedGraph(int _nodes, int _edges, bool _undirected) {
        nodes = _nodes;
        edges = _edges;
        undirected = _undirected;
        adj = vector<vector<pair<int, int>>>(_nodes);
        dist = vector<ll>(_nodes, LLONG_MAX);
        prev = vector<int>(_nodes, -1);
    }

    void init_adj() {
        f0r(i, edges) {
            int n1, n2; ll c; // node1, node2, cost
            cin >> n1 >> n2 >> c;
            n1--; n2--;
            adj[n1].pb(mp(n2, c));

            if (undirected) {
                adj[n2].pb(mp(n1, c));
            }
        }
    }

    // Priority queues are sus and can't pass objects or lambda functions as comparator
    // This is how you get around it
    // auto comp = [](pair<ll, int>&a, pair<ll, int>&b) {
    //     return a.f > b.f;
    // };
    // // Priority queue where first is distance and second is the node you reach there with that distance
    // priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(comp)> pq(comp);
    void dijkstra(int src) {
        fill(dist.begin(), dist.end(), LLONG_MAX);

        // Priority queue where first is distance and second is the node you reach there with that distance
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while(pq.size()) { // not 0
            ll curr_dist; int node;
            tie(curr_dist, node) = pq.top();
            pq.pop();

            if (curr_dist > dist[node]) continue;
            for(pair<int, int> i : adj[node]) {
                // If we can reach neighboring node in shorter distance
                if (curr_dist + i.s < dist[i.f]) {
                    // Update new distance to reach this node
                    dist[i.f] = curr_dist + i.s;
                    prev[i.f] = node;

                    pq.push({dist[i.f], i.f});
                }
            }
        }
    }
};

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

ll old_binary_search(ll lo, ll hi, bool works) {
	while(lo < hi) {
		ll mid = (lo + hi + 1)/2;

		// Binary search part
		if(works) {
			if(hi == mid) {
				hi--;
			} else {
				hi = mid;
			}
		} else {
			lo = mid + 1;
		}
	}
	
	// check to see if it works on lo
	if (works == false) {
		lo++;
	}
	return lo;
}

ll wikipedia_binary_search(ll lo, ll hi, bool works) {
	while (lo < hi) {
		ll mid = lo + (hi - lo)/2;
		if (!works) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}

	// have to check again bottom lo, if no work go up

	return lo;
}

// Do something similar to upper_bound except greatest number smaller
set<ll>::iterator greatest_number_smaller(set<ll>& s, ll num) {
    DEBUG(num, *(--s.end()), *s.begin());
 
    if(num <= *(--s.end()) && num >= *s.begin()) {
        return --s.upper_bound(num);
    } else {
        set<ll>::iterator ending = s.end();
        ending--;
        return ending;
    }
}

void floodfill(pll start) {
	/* Create these two global variables */
	vector<vector<bool> > visited;
	vector<string> grid;

	deque<pll > dq; // [row #, col #]
	dq.push_back(start);
    visited[start.f][start.s] = true;

    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

	while(!dq.empty()) {
		pll current = dq.front();
        dq.pop_front();

        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];

            bool isValid = true;
            if (isValid && !visited[newR][newC] && grid[newR][newC] == 't') {
                visited[newR][newC] = true;
                dq.pb(mp(newR, newC));
            }
        }
	}
}
class Tree {
    public:
    vector<vector<ll> > edges; // children is just all edges - the parent
    vector<ll> parentArr; // parentArr[1] gives the parent for Node 1
    vector<ll> depth; // depth[1] gives the depth of the current node of Node 1
    vector<ll> size_arr; // Size of subtree including this node as root

    vector<ll> fun;
    vector<ll> special_nodes; // Nodes that have multiple children
    
    Tree(ll nodes) {
        edges = vector<vector<ll> >(nodes);
        parentArr = vector<ll>(nodes);
        depth = vector<ll>(nodes, 0); // Root has depth 0
        size_arr = vector<ll>(nodes);

        fun = vector<ll>(nodes, 0);
    }

    // Basically does a DFS, pre-processing
    ll traverse(ll vertex, ll parentNode = -1) {
        ll size = 1;

        parentArr[vertex] = parentNode;
        DEBUG(vertex, parentNode);
        for (ll child: edges[vertex]) {
            // We only want to go to childrens and not back up to parent
            if (child != parentNode) { 
                depth[child] = depth[vertex] + 1;
                // This vertex is now the parent, recursively go down
                size += traverse(child, vertex);
            }
        }

        size_arr[vertex] = size;
        return size;
    }

    // Preprocessing similar to BFS
    void preprocess(ll root) {
		deque<ll> dq;
        dq.pb(root);

        while(!dq.empty()) {
            ll current = dq.front();
            dq.pop_front();

            f0r(i, edges[current].size()) {
				ll child = edges[current][i];
                dq.pb(child);
                DEBUG(current, child);
            }
        }
    }

    void sort_by_depth(vector<ll>& arr) {
        // [this] is C++ capturing so it captures the scope of the variable inside [] so this making it use the instance variables inside this (or this current tree)
        sort(arr.begin(), arr.end(), [this](ll n1, ll n2) {
            return depth_less_than(n1, n2);
        });
    }

    bool depth_less_than(ll n1, ll n2) {
        return depth[n1] < depth[n2];
    }
};

vector<int> compute_lps(vector<ll> pat) {
    int n = pat.size();
    vector<int> lps(n);
    lps[0] = 0;
    for (int i = 1; i < n; i++) {
        lps[i] = 0;
        int j = lps[i - 1]; /* trying length j + 1 */
        while (j > 0 && pat[j] != pat[i]) {
            j = lps[j - 1];
        }
        if (pat[j] == pat[i]) {
            lps[i] = j + 1;
        }
    }
    return lps;
}

vector<int> find_matches(vector<ll> text, vector<ll> pat) {
    int n = pat.size(), m = text.size();
    vector<ll> v = pat;
    v.push_back(-1);
    v.insert(v.end(), text.begin(), text.end());
    vector<int> lps = compute_lps(v), ans;
    for (int i = n + 1; i <= n + m; i++) { /* n + 1 is where the text starts */
        if (lps[i] == n) {
            ans.push_back(i - 2 * n); /* i - (n - 1) - (n + 1) */
        }
    }
    return ans;
}
