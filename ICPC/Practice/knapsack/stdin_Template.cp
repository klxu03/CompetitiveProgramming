#include <vector>
#include <set>
#include <map>
#include <queue>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <utility>
#include <deque>

using namespace std;
typedef long long ll;
typedef long double ld;
#define INF 2001001001
#define MOD 1000000007


int main() {
	stringstream ss;
	
	cout << ss.str();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////

//template for compare functor
struct cmp {
	bool operator()(const Class& x, const Class& y) const { return x.a < y.a; }
};

// size of components are stored as negative values
// any node with a negative value is the representative node
struct DSU{
	vector<int> sets;
	void init(int n){ sets = vector<int>(n+1 ,-1);}
	int find(int x){
		
		return sets[x] < 0 ? x : sets[x] = find(sets[x]);
	}
	bool unite(int x, int y){
		
		x = find(x);
		y = find(y);
		if(x == y) return 0;
		if(sets[x] > sets[y]) swap(x, y);
		sets[x] += sets[y];
		sets[y] = x;
		return 1;
	}
	
};

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

// for mod exponentiation simply pass in a thrid parameter, m (mod), and then mod after every time you multiply
ll binpow(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a; // for mod exponentiation add a mod m here
        a = a * a; // for mod exponentiation add a mod m here
        b >>= 1;
    }
    return res;
}
// find mod inverse of a number. Uses fermat's little theorem so only works when mod is prime
ll mod_inv(ll a, ll mod){
	if(gcd(a, mod) == 1){
		return binpow(a , mod-2);
	}
	else{
		return -1; // a doesn't have a mod inverse in this mod space
	}
}