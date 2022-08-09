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

int n, m, q, Q, T, k, l, r, x, y, z, g;

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

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=789
int main() {
    usaco("mootube");
    // io;

    cin >> n >> q;
    DSU d(n);

    // edges[2] is r connecting edges[0] and edges[1]
    vector<vector<int>> edges(n - 1, vector<int>(3));
    f0r(i, n - 1) {
        int x, y, z;
        cin >> x >> y >> z;
        edges[i] = {x, y, z};
    }

    // queries[0] is r, queries[1] is node, queries[2] is index, queries[3] is ret
    vector<vector<int>> queries(q, vector<int>(4));
    for(int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        queries[i] = {x, y, i, -1};
    }

    sort(edges.begin(), edges.end(), [](vector<int>& x, vector<int>& y) {
        return x[2] > y[2];
    });

    sort(queries.begin(), queries.end(), [](vector<int>& x, vector<int>& y) {
        return x[0] > y[0];
    });

    DEBUG(edges);
    DEBUG(queries);

    int edge_counter = 0; 
    for(int queries_counter = 0; queries_counter < q; queries_counter++) {
        while(edge_counter < n - 1 && edges[edge_counter][2] >= queries[queries_counter][0]) {
            // DSU join them
            d.unite(edges[edge_counter][0], edges[edge_counter][1]);
            edge_counter++;
        }
        queries[queries_counter][3] = d.size(queries[queries_counter][1]) - 1;
    }

    sort(queries.begin(), queries.end(), [](vector<int>& x, vector<int>& y) {
        return x[2] < y[2];
    });

    f0r(i, q) {
        cout << queries[i][3] << endl;
    }
}