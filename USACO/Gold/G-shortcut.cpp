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

ll q, Q, k, l, r, x, y, z, g;
int n, m, T;

// Scuffed PQ so I can iterate through a pq
// Right after declare the PQ right the line below with this pasted in template above WeightedGraph
// vector<pair<ll, int>> &tasks = Container(pq);
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
    vector<vector<int>> next;

    // numCows[1] is the num of cows that traverse through
    vector<ll> numCows;

    WeightedGraph(int _nodes, int _edges, bool _undirected) {
        nodes = _nodes;
        edges = _edges;
        undirected = _undirected;
        adj = vector<vector<pair<int, int>>>(_nodes);
        dist = vector<ll>(_nodes, LLONG_MAX);
        prev = vector<int>(_nodes, -1);
        next = vector<vector<int>>(_nodes);

        numCows = vector<ll>(_nodes, 0);
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

    void add_numCows(vector<ll> &numCows) {
        this->numCows = numCows;
    }

    /* 
    Recursion afterwards to count numCows that go through this path
    Have in Dijkstra the raw shortest distance from this node to end
    */

    void dijkstra(int src) {
        fill(dist.begin(), dist.end(), LLONG_MAX);

        auto comp = [](pair<ll, int>&a, pair<ll, int>&b) {
            if (a.f == b.f) {
                return a.s > b.s;
            } else {
                return a.f > b.f;
            }
        };
        // Priority queue where first is distance and second is the node you reach there with that distance
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(comp)> pq(comp);
        vector<pair<ll, int>> &tasks = Container(pq);
        dist[src] = 0;
        pq.push({0, src});

        while(pq.size()) { // not 0
            ll curr_dist; int node;
            tie(curr_dist, node) = pq.top();
            pq.pop();

            if (curr_dist > dist[node]) continue;
            for(pair<int, int> i : adj[node]) {
                // If we can reach neighboring node in shorter distance
                if (curr_dist + i.s <= dist[i.f]) {
                    // Dealing with lexographically smallest

                    /* DO NEXT DYNAMICALLY POST DIJKSTRA WITH INFO FROM PREV */

                    if (curr_dist + i.s == dist[i.f]) {
                        if (node < prev[i.f]) {
                            prev[i.f] = node;
                        }
                    } else {
                        // Normally what you'd do in Dijkstra if not <= dist
                        prev[i.f] = node;
                    }

                    // Update new distance to reach this node
                    dist[i.f] = curr_dist + i.s;

                    pq.push({dist[i.f], i.f});
                }

            }
            // DEBUG(tasks);
            // DEBUG(next);
        }
    }

    void setNext() {
        f1r(i, 1, n) {
            next[prev[i]].pb(i);
        }
    }

    // Recursive function to calculate the numCows that go through each node
    // Still TLE when this is commented out
    ll sumCows(int src) {
        ll counter = numCows[src];
        for(int i : next[src]) {
            counter += sumCows(i);
        }

        numCows[src] = counter;
        return counter;
    }
};


//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=899 
int main() {
    usaco("shortcut");
	// usacio("shortcut");
    // io;

    cin >> n >> m >> T;

    vector<ll> cows(n);
    f0r(i, n) {
        cin >> cows[i];
    }

    WeightedGraph g(n, m, true);
    g.add_numCows(cows);
    g.init_adj();

    g.dijkstra(0);
    g.setNext();
    g.sumCows(0);
    // DEBUG(g.dist);
    // DEBUG(g.prev);
    // DEBUG(g.next);

    // DEBUG(g.numCows);

    ll ret = 0;
    f1r(i, 1, n) {
        ll time_saved = g.numCows[i] * (g.dist[i] - T);
        ret = max(ret, time_saved);
    }

    cout << ret << endl;
}
