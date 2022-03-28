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

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for(long long a = b; a < c; a++)
//#define max3(a, b, c) max(a, max(b, c))
#define pb push_back 
#define f first
#define s second
#define mp make_pair
#define pll pair<ll, ll>

int main() {
	stringstream ss;
	int n;
    cin >> n;
    vector<pll> vec;
    for(int i =0; i < n; i++){
        ll a, b;
        cin >> a >> b;
        vec.pb(mp(a, b));
    }
    ll sum =0;
    ll time =0;
    int ind =0;
    unordered_set<ll> uset;
    for(int i =1; i <= n; i++){
        if(uset.find(i) != uset.end()){
            time++;
            
        }
        else{
            while(ind < n && vec[ind].s != i){
                ind++;
                uset.insert(vec[ind].s);
            }
            sum += fmax(0, vec[ind].f - time -1);
            if(vec[ind].f == time){
                time++;
            }
            else{
                time = vec[ind].f;
            }
            ind++;
        }
        cout << i << " " << sum << endl;
    }
    cout << sum << endl;
	return 0;
}