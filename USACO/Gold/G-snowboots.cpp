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

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=813
int main() {
    usaco("snowboots");
    // io;

    ll b;
    cin >> n >> b;

    // [key, value]: key = step size, value = a boot of this depth and above will be able
    // to pass through the barn for the key's specific step size
    unordered_map<ll, ll> max_step_size_to_min_depth;
    max_step_size_to_min_depth[1] = -1;

    // tiles: snow depth, index
    vector<pll> tiles(n);
    // scuffedDSU: start of the group index, end of the group index, 1 if blacked out -1 if not blacked out
    vector<array<ll, 3>> scuffedDSU(n);
    f0r(i, n) {
        ll tileDepth;
        cin >> tileDepth;
        tiles[i] = mp(tileDepth, i);
        scuffedDSU[i] = {i, i, -1};

        max_step_size_to_min_depth[1] = max(tileDepth, max_step_size_to_min_depth[1]);
    }

    DEBUG(tiles);
    sort(tiles.begin(), tiles.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        // If both tiles being compared have a snow depth of 0
        // bring start and end to the bottom of the "priority queue vector"
        if (x.f == 0 && y.f == 0) {
            // If it's index 0 or n - 1 (the last tile), make it last 
            return x.s != 0 && x.s != n - 1;
        }

        return x.f > y.f;
    });

    vector<pll> boots(b);
    f0r(i, b) {
        ll depth, stepSize;
        cin >> depth >> stepSize;
        boots[i] = mp(depth, stepSize);
    }
    DEBUG(tiles, boots, max_step_size_to_min_depth[1]);

    ll numTilesBlackedOut = 0;
    // Calculate the max_step_size_to_min_depth for depths from 2 to 10^5
    f1r(i, 2, 1e5) {
        // Keep blacking out largest tile unless we reach the ending two tiles 
        while(numTilesBlackedOut <= n - 2) {
            pll tile = tiles[numTilesBlackedOut];
            DEBUG(tile);
            ll newGroupSize = 1;

            // If we can black out this new index, the left and right index
            // of the newly formed scuffedDSU group
            ll leftIndex = tile.s, rightIndex = tile.s;

            // There is a group to the left
            if (scuffedDSU[tile.s - 1][2] == 1) {
                leftIndex = scuffedDSU[tile.s - 1][0];
                newGroupSize += 1 + scuffedDSU[tile.s - 1][1] - scuffedDSU[tile.s - 1][0]; 
            }
            // There is a group to the right
            if (scuffedDSU[tile.s + 1][2] == 1) {
                rightIndex = scuffedDSU[tile.s + 1][1];
                newGroupSize += 1 + scuffedDSU[tile.s + 1][1] - scuffedDSU[tile.s + 1][0]; 
            }

            // If the new group size blacks out too much
            if (newGroupSize >= i) {
                max_step_size_to_min_depth[i] = tile.f;
                break;
            } else {
                // Can keep blacking out next tile, actually black it out
                numTilesBlackedOut++;
                // Adjust the DSU groups
                scuffedDSU[leftIndex] = {leftIndex, rightIndex, 1};
                scuffedDSU[rightIndex] = {leftIndex, rightIndex, 1};
                DEBUG("keep going", i, newGroupSize);
            }
        }
    }

    // DEBUG(1e5 == 100000);
    DEBUG(max_step_size_to_min_depth);

    f0r(i, b) {
        pll boot = boots[i];
        if (boot.f >= max_step_size_to_min_depth[boot.s]) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
}