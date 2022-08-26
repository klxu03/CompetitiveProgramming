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

ll q, Q, T, k, l, r, x, y, z, g;
int n, m;

vector<string> inp;
vector<array<pll, 2>> PCL; // PCL[0][0].f is the top left's rows

bool isValid(int r, int c, pll start, pll end) {
    return r >= start.f && r <= end.f && c >= start.s && c <= end.s;
}

// Check if something is a PCL and default is spotted
bool spots_floodfill(pll start, pll end) {
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};
    deque<pll> contig_dq; // [row #, col #] for contiguous
    deque<pll> spots_dq; // [row #, col #] for spots
    vector<vector<bool>> contig_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    vector<vector<bool>> spots_visited = vector<vector<bool>>(n, vector<bool>(n, false));

    spots_dq.pb(start);
    spots_visited[start.f][start.s] = true;

    int spots_counter = 1; // number of total spots in this PCL

    // By default, assuming first one is contig 
    char spots = inp[start.f][start.s];
    char contig = '-';

    // Find which value is contig
    while(!spots_dq.empty() && contig == '-') {
        pll current = spots_dq.front();
        spots_dq.pop_front();
        
        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !spots_visited[newR][newC]) {
              spots_visited[newR][newC] = true;
              if (inp[newR][newC] == spots) {
                spots_dq.pb(mp(newR, newC));
                spots_counter++;
              } else if (contig == '-') {
                contig = inp[newR][newC];
                contig_dq.pb(mp(newR, newC));
                contig_visited[newR][newC] = true;
              }
            } 
        }
    }

    if (contig == '-') {
      return false;
    }

    // Now that you know where contig is
    while(!contig_dq.empty()) {
        pll current = contig_dq.front();
        contig_dq.pop_front();
        
        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !contig_visited[newR][newC]) {
              contig_visited[newR][newC] = true;
              if (inp[newR][newC] == contig) {
                contig_dq.pb(mp(newR, newC));
              } else {
                if (spots == inp[newR][newC] && !spots_visited[newR][newC]) {
                  spots_visited[newR][newC] = true;
                  spots_dq.pb(mp(newR, newC));
                  spots_counter++;
                } else {
                  // Some phantom 3rd spot color has appeared
                  return false;
                }
              }
            }
        }
    }

    // Redo spots again
    while(!spots_dq.empty()) {
        pll current = spots_dq.front();
        spots_dq.pop_front();
        
        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !spots_visited[newR][newC]) {
              spots_visited[newR][newC] = true;
              if (inp[newR][newC] == spots) {
                spots_dq.pb(mp(newR, newC));
                spots_counter++;
              } else if (inp[newR][newC] != contig) {
                // Some phantom 3rd color appeared
                return false;
              }
            } 
        }
    }

    // Make sure all cells are either spots or contig in this PCL
    for (int i = start.f; i <= end.f; i++) {
      for (int j = start.s; j <= end.s; j++) {
        if (inp[i][j] != spots && inp[i][j] != contig) {
          return false;
        }
      }
    }

    // Do a BFS floodfill from a single spot and count the number of cells visited
    // If it equals total spots_counter, then this PCL only has one spot
    // Otherwise there'll be other cells unvisited somewhere else in another spot
    deque<pll> multiple_dq;
    int multiple_counter = 1;
    vector<vector<bool>> multiple_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    if (spots != '-') {
      multiple_visited[start.f][start.s] = true;
      multiple_dq.pb(mp(start.f, start.s));
    } else {
      return false;
    }

    while(!multiple_dq.empty()) {
      pll current = multiple_dq.front();
      multiple_dq.pop_front();

      f0r(i, 4) {
        int newR = current.f + dr[i];
        int newC = current.s + dc[i];
        if(isValid(newR, newC, start, end) && !multiple_visited[newR][newC]) {
          multiple_visited[newR][newC] = true;
          if (inp[newR][newC] == spots) {
            multiple_dq.pb(mp(newR, newC));
            multiple_counter++;
          }
        }
      }
    }

    // There is only one "spot" in this PCL as no other cells have a spot
    if (multiple_counter == spots_counter) {
      return false;
    }

    return true;
}

/* 
Thought of a much simpler implementation.
Do the initial contiguous, go through and get the first spot and count
contig_counter. Then go through n^2 sweep and count total_contig and total_spot

    // Make sure all cells are either spots or contig in this PCL
    for (int i = start.f; i <= end.f; i++) {
      for (int j = start.s; j <= end.s; j++) {
        if (inp[i][j] != spots && inp[i][j] != contig) {
          return false;
        }
      }
    }

Then take initial spot and do the same multiple_spot check. 
Now you catch case where there are multiple contiguous and this just works
without shenanigans of adding spots you see during contig floodfill into spots_dq
*/

// Check if something is a PCL and default is contiguous
// Returning true if this region is a PCL
bool contig_floodfill(pll start, pll end) {
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};
    deque<pll> contig_dq; // [row #, col #] for contiguous
    deque<pll> spots_dq; // [row #, col #] for spots
    vector<vector<bool>> contig_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    vector<vector<bool>> spots_visited = vector<vector<bool>>(n, vector<bool>(n, false));

    contig_dq.pb(start);
    contig_visited[start.f][start.s] = true;

    int spots_counter = 0; // number of total spots in this PCL

    // By default, assuming first one is contig 
    char contig = inp[start.f][start.s];
    char spots = '-';
    pll initial_spot = {-1, -1};

    while(!contig_dq.empty()) {
        pll current = contig_dq.front();
        contig_dq.pop_front();
        
        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !contig_visited[newR][newC]) {
              contig_visited[newR][newC] = true;
              if (inp[newR][newC] == contig) {
                contig_dq.pb(mp(newR, newC));
              } else {
                if (spots == inp[newR][newC] && !spots_visited[newR][newC]) {
                  spots_visited[newR][newC] = true;
                  spots_dq.pb(mp(newR, newC));
                  spots_counter++;
                } else if (spots == '-') {
                  spots = inp[newR][newC];
                  spots_visited[newR][newC] = true;
                  spots_dq.pb(mp(newR, newC));
                  spots_counter++;
                  initial_spot = mp(newR, newC);
                } 
                else {
                  // Some phantom 3rd spot color has appeared
                  return false;
                }
              }
            }
        }
    }

    while(!spots_dq.empty()) {
        pll current = spots_dq.front();
        spots_dq.pop_front();
        
        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !spots_visited[newR][newC]) {
              spots_visited[newR][newC] = true;
              if (inp[newR][newC] == spots) {
                spots_dq.pb(mp(newR, newC));
                spots_counter++;
              } else if (inp[newR][newC] != contig) {
                // Some phantom 3rd color appeared
                return false;
              }
            } 
        }
    }

    // Make sure all cells are either spots or contig in this PCL
    for (int i = start.f; i <= end.f; i++) {
      for (int j = start.s; j <= end.s; j++) {
        if (inp[i][j] != spots && inp[i][j] != contig) {
          return false;
        }
      }
    }

    // Do a BFS floodfill from a single spot and count the number of cells visited
    // If it equals total spots_counter, then this PCL only has one spot
    // Otherwise there'll be other cells unvisited somewhere else in another spot
    deque<pll> multiple_dq;
    int multiple_counter = 1;
    vector<vector<bool>> multiple_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    if (spots != '-') {
      multiple_visited[initial_spot.f][initial_spot.s] = true;
      multiple_dq.pb(mp(initial_spot.f, initial_spot.s));
    } else {
      return false;
    }

    while(!multiple_dq.empty()) {
      pll current = multiple_dq.front();
      multiple_dq.pop_front();

      f0r(i, 4) {
        int newR = current.f + dr[i];
        int newC = current.s + dc[i];
        if(isValid(newR, newC, start, end) && !multiple_visited[newR][newC]) {
          multiple_visited[newR][newC] = true;
          if (inp[newR][newC] == spots) {
            multiple_dq.pb(mp(newR, newC));
            multiple_counter++;
          }
        }
      }
    }

    // There is only one "spot" in this PCL as no other cells have a spot
    if (multiple_counter == spots_counter) {
      return false;
    }

    return true;
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=740 
int main() {
    // usaco("testCases");
	// usacio("testCase");
    io;

    cin >> n;
    inp = vector<string>(n);
    f0r(i, n) {
        cin >> inp[i];
    }

    f0r(r1, n) {
      f0r(c1, n) {
        f1r(r2, r1, n) {
          f1r(c2, c1, n) {
            if (r1 == r2 && c1 == c2) continue;
            // Top left r1 c1
            // Bottom right r2 c2
          }
        }
      }
    }
}
