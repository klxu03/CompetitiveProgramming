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
#include <numeric>
#include <cmath>
#include <iomanip>

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

// Problem: 
int main() {
	io;
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

ll factorial(ll num) {
    ll ret = 1;
    f1r(i, 1, num + 1) {
        ret *= i;
    }
    return ret;
}

 // Computes base^exp
ll mpow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
    if (exp % 2 == 1){
        res = (res * base);
    }
    exp >>= 1;
    base = (base * base);
    }
    return res;
}

class Graph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<ll> visited; // visited nodes
    vector<ll> dist; // distance

	Graph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		visited = vector<ll>(n, false);
        dist = vector<ll>(n, 0);
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

        dist = vector<ll>(n, 0);

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

// Should I add the weight 1 to vertex "11122", answer is no
bool should_add(ll vertex, ll weight) {
    ll weight_count = 0;
    while(vertex > 0 && weight_count < 3) {
        if (vertex % 10 == weight) {
            weight_count++;
        }

        vertex /= 10;
    }

    return weight_count < 3;
}

void solve() {
    ll e, w; // # of exercises, # of weight types
    cin >> e >> w;

    // ll size = factorial(w * 3)/mpow((factorial(3)), w);
    // size += 1;
    ll size = 5248;
    
    vector<vector<ll> > dp(e, vector<ll> (m, -1));
    
    // Map for index 4 -> node 12
    map<ll, ll> node_map;
    
    // Map for node 12 -> index 4
    map<ll, ll> index_map;

    Graph g(size, 0, true);

    ll counter = 1;
    vector<ll> prev;
    f1r(i, 1, w + 1) {
        prev.pb(i); // builds {1, 2, 3} in prev

        g.insert_edge(0, counter);
        node_map.insert(mp(counter, i));
        index_map.insert(mp(i, counter++));
    }

    // Build out the next 8 digits after already having one
    f0r(i, 3*w - 1) {
        vector<ll> next_prev;
        // Add a 1, 2, or 3 to the end and make it a new node and check if should add 1, 2, or 3

        f0r(j, prev.size()) {
            ll prev_node = prev[j]; // Takes "11122"
            f1r(k, 1, w + 1) {
                // checks if should add (and if so, add) 1, 2, or 3
                DEBUG(prev_node, k, should_add(prev_node, k));
                if (should_add(prev_node, k)) {
                    ll new_node = prev_node * 10 + k;
                    next_prev.pb(new_node);

                    g.insert_edge(index_map[prev_node], counter);
                    index_map.insert(mp(new_node, counter));
                    node_map.insert(mp(counter++, new_node));
                }
            }

        }

        prev = next_prev;
    }

    f0r(i, size) {
        DEBUG(i, node_map[i]);
    }

    g.display();
    DEBUG(node_map[3567], node_map[5247]);

}