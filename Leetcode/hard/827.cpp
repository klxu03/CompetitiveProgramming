// Problem URL: https://leetcode.com/problems/making-a-large-island/

#include <bits/stdc++.h>

using namespace std;

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

class Solution {
public:
    int n;
    vector<vector<int>> groups; // Copy of grid except groups[x][y] tells you which group it's in
    // then use group_map to figure out the size of that component
    vector<int> group_map; // Group 1 value would be how many elements are in that component

    bool isValid(int x, int y) {
        if (x < 0 || x >= n) {
            return false;
        }

        if (y < 0 || y >= n) {
            return false;
        }

        return true;
    }

    // non-recursive DFS flood fill
    int floodFill(vector<vector<int>>& grid, int startX, int startY, int group) {
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};


        deque<pair<int, int> > dq;
        dq.push_back(make_pair(startX, startY));
        int counter = 0; // the amount of tiles in this group

        while(!dq.empty()) {
            pair<int, int> current = dq.front();
            if (groups[current.first][current.second] == -1) {
                groups[current.first][current.second] = group;
                counter++;
            }

            bool pop_front = true;
            for(int i = 0; i < 4; i++) {
                int newX = current.first + dx[i];
                int newY = current.second + dy[i];
                if (isValid(newX, newY) && grid[newX][newY] == 1 && groups[newX][newY] == -1) {
                    dq.push_front(make_pair(newX, newY));
                    break;
                }

                if (i == 3) {
                    dq.pop_front();
                }
            }
        }

        group_map[group] = counter;
        return counter;
    }

    int largestIsland(vector<vector<int>>& grid) {
        n = grid.size();
        groups = vector<vector<int>>(n, vector<int>(n, -1));
        group_map = vector<int>(n * n + 1, 0);

        long long currGroup = 1;
        int maxGroupSize = 0; // case when the entire board is filled with 1, do not return -1
        // Label each island component with flood fill
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (groups[i][j] == -1 && grid[i][j] == 1) {
                    int currGroupSize = floodFill(grid, i, j, currGroup++);
                    maxGroupSize = max(maxGroupSize, currGroupSize);
                }
            }
        } 

        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < n; j++) {
        //         cout << groups[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};

        int ret = maxGroupSize;
        // For each tile in the n * n grid, if it is 0 try making it 1 and calculating new biggest island group size
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    int island_size = 1;
                    vector<int> visited_groups(4, -1);
                    for(int k = 0; k < 4; k++) {
                        int newX = i + dx[k];
                        int newY = j + dy[k];
                        if (isValid(newX, newY) && groups[newX][newY] >= 1) {
                            // Make sure that you are not repeating adding of one big island surrounding this tile
                            bool newGroup = true;
                            for(int k2 = 0; k2 < 4; k2++) {
                                if (visited_groups[k2] == groups[newX][newY]) newGroup = false;
                            }

                            if (newGroup) {
                                island_size += group_map[groups[newX][newY]];
                                visited_groups[k] = groups[newX][newY];
                            }
                        }
                    }

                    // Keep a running max 
                    ret = max(ret, island_size);
                }
            }
        }

        // If the entire board is filled with 0, then u can turn one of them into 1 
        if (ret == 0) {
            return 1;
        }
        return ret;
    }
};