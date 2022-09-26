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
    freopen((filename + ".txt").c_str(), "r", stdin);
    freopen((filename + "_output.txt").c_str(), "w", stdout);
}

ll q, Q, T, k, l, r, x, y, z, g;
ll n, m;

const ll MOD = (ll) 1e9 + 7;

class WeightedGraph {
    public:
    int nodes; // # of nodes
    int edges; // # of edges
    bool undirected;
    vector<vector<pair<int, int>>> adj; // adjacency neighbor vector
    // pair<first, second> = adj[5][0] where first is node 5's 1st neighbors pointed to node, and second is the cost
    vector<ll> dist; // distance to get to this node
    vector<int> prev;
    vector<bool> visited;

    vector<ll> res;

    WeightedGraph(int _nodes, int _edges, bool _undirected) {
        nodes = _nodes;
        edges = _edges;
        undirected = _undirected;
        adj = vector<vector<pair<int, int>>>(_nodes);
        dist = vector<ll>(_nodes, LLONG_MAX);
        prev = vector<int>(_nodes, -1);

        visited = vector<bool>(_nodes, false);
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

    void add_adj(int n1, int n2, ll c) {
        adj[n1].pb({n2, c});
    }

    // Priority queues are sus and can't pass objects or lambda functions as comparator
    // This is how you get around it
    // auto comp = [](pair<ll, int>&a, pair<ll, int>&b) {
    //     return a.f > b.f;
    // };
    // // Priority queue where first is distance and second is the node you reach there with that distance
    // priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(comp)> pq(comp);

    // LOL acc a BFS
    void dijkstra(int src) {
        if (visited[src] == true) {
            return;
        }

        fill(dist.begin(), dist.end(), 0);
        // fill(prev.begin(), prev.end(), -1);

        // Priority queue where first is distance and second is the node you reach there with that distance
		deque<int> dq;
		dq.push_back(src);

		while(!dq.empty()) {
			ll current = dq.front();
			dq.pop_front();

			f0r(i, adj[current].size()) {
				pll neighbor = adj[current][i];
				// if(prev[neighbor.f] == -1) {
					prev[neighbor.f] = current;
                    visited[neighbor.f] = true;
                    ll new_weight = dist[current] + neighbor.s;
                    DEBUG(new_weight, dist[current], neighbor.s);
                    new_weight %= MOD;  
                    dist[neighbor.f] = new_weight;
					dq.push_back(neighbor.f);

                    res.pb(new_weight);
				// } 
			}
		}

        // Process the result
    }

    void sort_res() {
        sort(res.begin(), res.end());
    }
};


void solve(); 

int main() {
	io;
    // usaco("");
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

vector<array<ll, 3>> buyers;
vector<array<ll, 3>> sellers;

// Buyer is searching for min index of lower price
// Return -1 if no compatible match
ll binary_search(int index) {
    array<ll, 3> buyer = buyers[index];
    ll lo = 0;
    ll hi = n + 1;
	while (lo < hi) {
		ll mid = (lo + hi)/2;
        // DEBUG(mid, sellers[mid]);
        if (sellers[mid][0] < buyer[0]) {
            lo = mid + 1;
            // DEBUG("higher 1");
        } else if (sellers[mid][0] == buyer[0]) {
            if (sellers[mid][1] < buyer[1]) {
                hi = mid;
                // DEBUG("lower 1");
            } else {
                lo = mid + 1;
                // DEBUG("higher 2");
            }
        } else {
            hi = mid;
            // DEBUG("lower 2");
        }
	}   

    // DEBUG(lo, sellers[lo]);
    if (sellers[lo][0] > buyer[0]) {
        return -1;
    }

	// have to check again bottom lo, if no work go up
    if (sellers[lo][0] < buyer[0]) {
        lo++;
    } else if (sellers[lo][0] == buyer[0] && sellers[lo][1] >= buyer[1]) {
        lo++;
    }

    if (sellers[lo][0] != buyer[0]) {
        return -1;
    }

	return lo;
}


void solve() {
    cin >> n >> k;

    buyers = vector<array<ll, 3>>(n); // {Date, Amt, Index}
    sellers = vector<array<ll, 3>>(n);

    f0r(i, n) {
        ll buy_date, sell_date, buy_amt, sell_amt;
        cin >> buy_date >> sell_date >> buy_amt >> sell_amt;
        buy_date--; sell_date--;

        buyers[i] = {buy_date, buy_amt, i};   
        sellers[i] = {sell_date, sell_amt, i};   
    }

    sort(buyers.begin(), buyers.end(), [](const array<ll, 3>& x, const array<ll, 3>& y) {
        if (x[0] == y[0]) {
            return x[1] < y[1];
        }

        return x[0] < y[0];
    });

    sort(sellers.begin(), sellers.end(), []
    (const array<ll, 3>& x, const array<ll, 3>& y) {
        if (x[0] == y[0]) {
            return x[1] > y[1];
        }

        return x[0] < y[0];
    });

    // DEBUG(buyers);
    // DEBUG(sellers);

    // DEBUG(binary_search(7));

    WeightedGraph g(n, 0, false);
    // Add edges
    f0r(i, n) {
        int res = binary_search(i);
        if (res != -1) {
            while(res <= n - 1 && sellers[res][1] < buyers[i][1] && sellers[res][0] == buyers[i][0]) {
                // DEBUG(i, res, buyers[i], sellers[res]);
                g.add_adj(sellers[res][2], i, buyers[i][1] - sellers[res][1]);
                res++;
            }
        }
    }

    f0r(i, n) {
        DEBUG(i, g.adj[i]);
    }

    f0r(i, n) {
        g.dijkstra(i);
    }
    g.sort_res();
    
    ll counter = 0;
    for(int i = g.res.size() - 1; i >= 0; i--) {
        if (k > 0) {
            counter += g.res[i];
        }
        k--;
    }

    DEBUG(g.res);
    cout << counter << endl;
}