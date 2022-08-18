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

ll q, Q, T, k, l, r, x, y, z, g;
int n, m;

class WeightedGraph {
    public:
    int nodes; // # of nodes
    int edges; // # of edges
    bool undirected;
    vector<vector<pair<int, int>>> adj; // adjacency neighbor vector
    // pair<first, second> = adj[5][0] where first is node 5's 1st neighbors pointed to node, and second is the cost
    vector<ll> dist; // distance to get to this node
    vector<vector<int>> prev;

    vector<ll> dp;

    WeightedGraph(int _nodes, int _edges, bool _undirected) {
        nodes = _nodes;
        edges = _edges;
        undirected = _undirected;
        adj = vector<vector<pair<int, int>>>(_nodes);
        dist = vector<ll>(_nodes, LLONG_MAX);
        prev = vector<vector<int>>(_nodes);

        dp = vector<ll>(_nodes, -1);
        dp[0] = 1;
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
                    prev[i.f] = {node};

                    pq.push({dist[i.f], i.f});
                } else if (curr_dist + i.s == dist[i.f]) {
                    prev[i.f].pb(node);
                }
            }
        }
    }

    int get_num_paths(int node) {
        if (dp[node] != -1) {
            return dp[node];
        }

        int ret = 0;
        for(int i : prev[node]) {
            ret += get_num_paths(i);
            while(ret > ((ll) 1e9) + 7) {
                // ret -= ((ll) 1e9) + 7;
                ret = 0;
            }
        }
        dp[node] = ret;
        return ret;
    }

    // Doing a shortest distance BFS where prev is the adjacency matrix from end to beginning
    int shortest_path() {
        vector<bool> visited(nodes, false);
		deque<int> dq;
        dq.pb(n - 1);
        visited[n - 1] = true;

        vector<int> local_dist = vector<int>(n);
        local_dist[n - 1] = 0;

        while(!dq.empty()) {
            int current = dq.front();
            dq.pop_front();

            for(int neighbor : prev[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    dq.pb(neighbor);

                    local_dist[neighbor] = local_dist[current] + 1;
                }
            }
        }

        return local_dist[0];
    }

    // Doing a longest distance BFS where prev is the adjacency matrix from end to beginning
    // Just don't keep a visited array and keep going in this "inefficient" but efficient enough BFS
    int longest_path() {
        deque<int> dq;
        dq.pb(n - 1);

        vector<int> local_dist = vector<int>(n);
        local_dist[n - 1] = 0;

        while(!dq.empty()) {
            int current = dq.front();
            dq.pop_front();

            for(int neighbor : prev[current]) {
                dq.pb(neighbor);
                local_dist[neighbor] = local_dist[current] + 1;
            }
        }

        return local_dist[0];
    }
};


void solve(); 
void usacio(string filename) {
    io;
    freopen((filename + ".txt").c_str(), "r", stdin);
}


// Problem: https://cses.fi/problemset/task/1202 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
    tin

	cin >> n >> m;
    WeightedGraph g(n, m, false);
    g.init_adj();

    g.dijkstra(0);

    // DEBUG(g.dist);
    // f0r(i, n) {
    //     DEBUG(g.prev[i]);
    // }

    ll min_distance = g.dist[n - 1];
    DEBUG(g.dist[0], g.dist[n - 1]);
    int num_paths = g.get_num_paths(n - 1);
    int shortest_path = g.shortest_path();
    int longest_path = g.longest_path();

    cout << min_distance << " " << num_paths << " " << shortest_path << " " << longest_path << endl;
    
    tpr
}