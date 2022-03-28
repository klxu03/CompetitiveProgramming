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
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back 
#define f first
#define s second
#define mp make_pair
#define pll pair<ll, ll>

int main() {
	stringstream ss;
    int n, p, k;
    cin >> n >> p >> k;
    vector<int> vec;
    for(int i =0; i < n; i++){
        int a;
        cin >> a;
        vec.pb(a);
    }
    vector<int> starts(n+1, -1);
    vector<int> cyc(n+1, 0);
    ll curr =0;
    int ind =0;
    int cycles = 0;
    int days =0;
    starts[1] = 0;
    int kevin_days;
    int kevin_cycles;
    while(true){
         ll a = vec[ind];
         if(curr+a > p){
             days++;
             if(starts[a] != -1){
                 int left = k-days;
                 int div = days - starts[a];
                 int cycd = cycles - cyc[a];
                 cycles += (left/div)*cycd;
                 kevin_days = div;
                 kevin_cycles = cycd;
                 break;
             }
             else{
                 if(ind < n-1){
                     ind++;
                 }
                 else{
                     ind = 0;
                     cycles++;
                 }
                 curr = a;
                 starts[a] = days;
                 cyc[a] = cycles;
             }

         }
         else{
             curr += a;
             if(ind < n-1){
                 ind++;
             }
             else{
                 ind = 0;
                 cycles++;
             }
         }
    }

    cout << kevin_days << " " << kevin_cycles << endl;
    
	cout << cycles << endl;
	return 0;
}

