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
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back 
#define f first
#define s second
#define mp make_pair
#define pll pair<ll, ll>
#define pii pair<int, int>
int sum;
int dir1[] = {0, 1, 0 ,-1};
int dir2[] = {1, 0, -1, 0};
vector<string> grid;
int n, m;
void bfs(int, int);
int main() {
	stringstream ss;
	
    cin >> n >> m;
    for(int i =0; i < n; i++){
        string temp;
        cin >> temp;
        grid.push_back(temp);
    }
    sum =0;
    
    for(int i =0; i < n; i++){
        for(int j =0; j < m; j++){
            char a = grid[i][j];
            if(a =='/'){
                if(i+1 < n && j+1 < m){
                    if((grid[i+1][j] == '\\' && grid[i][j+1] == '\\') && grid[i+1][j+1] == '/'){
                        sum++;
                    }
                }
            }
        }
    }
    
    for(int i =0; i < n; i++){
        for(int j =0; j < m; j++){
            if(grid[i][j] == '.'){
                bfs(i, j);
                
            }
            
        }
    }
    ss << sum << endl;
	cout << ss.str();
	return 0;
}
void bfs(int i, int j){
    queue<pii> q;
    q.push(mp(i, j));
    grid[i][j] = 'v';
    sum++;
    while(!q.empty()){
        i = q.front().f;
        j = q.front().s;
        q.pop();
        for(int k =0; k < 4; k++){
            int a = i + dir1[k];
            int b = j + dir2[k];
            if((a >= 0 && a < n) && (b >=0 && b < m)){
                if(grid[a][b] == '.'){
                    grid[a][b] = 'v';
                    q.push(mp(a, b));
                }
                
            }
            else{
                sum--;
                return;
            }
        }
        int a = i-1;
        int b = j+1;
        if(grid[i-1][j] == '/' && grid[i][j+1] == '/'){
            if((a >= 0 && a < n) && (b >=0 && b < m)){
                if(grid[a][b] == '.'){
                grid[a][b] = 'v';
                q.push(mp(a, b));
                }
                
            }
            else{
                sum--;
                return;
            }
        }
        a = i -1;
        b = j - 1;
        if(grid[i-1][j] == '\\' && grid[i][j-1] == '\\'){
            if((a >= 0 && a < n) && (b >=0 && b < m)){
                if(grid[a][b] == '.'){
                grid[a][b] = 'v';
                q.push(mp(a, b));
                }
                
            }
            else{
                sum--;
                return;
            }
        }
        a = i +1;
        b = j + 1;
        if(grid[i+1][j] == '\\' && grid[i][j+1] == '\\'){
            if((a >= 0 && a < n) && (b >=0 && b < m)){
                if(grid[a][b] == '.'){
                grid[a][b] = 'v';
                q.push(mp(a, b));
                }
                
            }
            else{
                sum--;
                return;
            }
        }
        a = i +1;
        b = j - 1;
        if(grid[i+1][j] == '/' && grid[i][j-1] == '/'){
            if((a >= 0 && a < n) && (b >=0 && b < m)){
                if(grid[a][b] == '.'){
                grid[a][b] = 'v';
                q.push(mp(a, b));
                }
                
            }
            else{
                sum--;
                return;
            }
        }
    }
}

