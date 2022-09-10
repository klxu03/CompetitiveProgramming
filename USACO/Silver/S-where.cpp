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
vector<array<pll, 2>> PCL; // PCL[0][0].f is the top left's rows and PCL[0][1].s is first bottom right col

bool isValid(int r, int c, pll start, pll end) {
    return r >= start.f && r <= end.f && c >= start.s && c <= end.s;
}

// Check if something is a PCL and assume the starting cell is 
// part of the spot family
bool spot_floodfill(pll start, pll end) {
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

    char spot = inp[start.f][start.s];
    char contig = '-';
    pll initial_contig;
    int total_contig_counter = 0;
    int total_spot_counter = 0;

    // Make sure all cells are either spots or contig in this PCL
    for (int i = start.f; i <= end.f; i++) {
      for (int j = start.s; j <= end.s; j++) {
        if (inp[i][j] != contig && inp[i][j] != spot) {
          if (contig == '-') {
            total_contig_counter++;
            initial_contig = mp(i, j);
            contig = inp[i][j];
          } else {
            // A third color has appeared
            // DEBUG("third color found");
            return false;
          }
        } else if (inp[i][j] == contig) {
          total_contig_counter++;
        } else if (inp[i][j] == spot) {
          total_spot_counter++;
        }
      }
    }

    if (contig == '-') {
      // Never found another color or contig color 
      // DEBUG("never found another contig/2nd color");
      return false;
    }

    // Counter to floodfill first contig element and make sure its floodfill
    // size is equal to total # of contig (this single floodfill)
    int multiple_contig_counter = 1;
    deque<pll> contig_dq; // [row #, col #] for contiguous
    vector<vector<bool>> contig_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    contig_dq.pb(initial_contig);
    contig_visited[initial_contig.f][initial_contig.s] = true;

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
                multiple_contig_counter++;
              } 
            }
        }
    }

    if (multiple_contig_counter < total_contig_counter) {
      // Contig is not fully contiguous
      // DEBUG("contig not fully contiguous");
      return false;
    }

    // Counter to floodfill first spot element and make sure its floodfill
    // size is not equal to total # of spot (there are multiple other spots)
    int multiple_spot_counter = 1;
    deque<pll> spot_dq; // [row #, col #] for contiguous
    vector<vector<bool>> spot_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    spot_dq.pb(start);
    spot_visited[start.f][start.s] = true;

    while(!spot_dq.empty()) {
        pll current = spot_dq.front();
        spot_dq.pop_front();

        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !spot_visited[newR][newC]) {
              spot_visited[newR][newC] = true;
              if (inp[newR][newC] == spot) {
                spot_dq.pb(mp(newR, newC));
                multiple_spot_counter++;
              } 
            }
        }
    }

    if (multiple_spot_counter >= total_spot_counter) {
      // There aren't multiple spots out there, this equals the total amount
      // DEBUG("only one spot");
      return false;
    }

    // DEBUG("true is spot");
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

// Check if something is a PCL and assume the starting cell is 
// part of the contiguous family
bool contig_floodfill(pll start, pll end) {
    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

    char contig = inp[start.f][start.s];
    char spot = '-';
    pll initial_spot;
    int total_contig_counter = 0;
    int total_spot_counter = 0;

    // Make sure all cells are either spots or contig in this PCL
    for (int i = start.f; i <= end.f; i++) {
      for (int j = start.s; j <= end.s; j++) {
        if (inp[i][j] != contig && inp[i][j] != spot) {
          if (spot == '-') {
            total_spot_counter++;
            initial_spot = mp(i, j);
            spot = inp[i][j];
          } else {
            // A third color has appeared
            // DEBUG("third color found");
            return false;
          }
        } else if (inp[i][j] == contig) {
          total_contig_counter++;
        } else if (inp[i][j] == spot) {
          total_spot_counter++;
        }
      }
    }

    if (spot == '-') {
      // Never found another color or spot color 
      // DEBUG("never found another spot/2nd color");
      return false;
    }

    // Counter to floodfill first contig element and make sure its floodfill
    // size is equal to total # of contig (this single floodfill)
    int multiple_contig_counter = 1;
    deque<pll> contig_dq; // [row #, col #] for contiguous
    vector<vector<bool>> contig_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    contig_dq.pb(start);
    contig_visited[start.f][start.s] = true;

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
                multiple_contig_counter++;
              } 
            }
        }
    }

    if (multiple_contig_counter < total_contig_counter) {
      // Contig is not fully contiguous
      // DEBUG("contig not fully contiguous");
      return false;
    }

    // Counter to floodfill first spot element and make sure its floodfill
    // size is not equal to total # of spot (there are multiple other spots)
    int multiple_spot_counter = 1;
    deque<pll> spot_dq; // [row #, col #] for contiguous
    vector<vector<bool>> spot_visited = vector<vector<bool>>(n, vector<bool>(n, false));
    spot_dq.pb(initial_spot);
    spot_visited[initial_spot.f][initial_spot.s] = true;

    while(!spot_dq.empty()) {
        pll current = spot_dq.front();
        spot_dq.pop_front();

        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if(isValid(newR, newC, start, end) && !spot_visited[newR][newC]) {
              spot_visited[newR][newC] = true;
              if (inp[newR][newC] == spot) {
                spot_dq.pb(mp(newR, newC));
                multiple_spot_counter++;
              } 
            }
        }
    }

    if (multiple_spot_counter >= total_spot_counter) {
      // There aren't multiple spots out there, this equals the total amount
      // DEBUG("only one spot");
      return false;
    }

    // DEBUG("true is contig");
    return true;
}

void floodfill(pll start, pll end) {
  bool isValidPCL = false;
  isValidPCL = isValidPCL || contig_floodfill(start, end);
  isValidPCL = isValidPCL || spot_floodfill(start, end);

  // if (isValidPCL) {
  //   // go through check all other PCLs and see if it's a subset or superset of others
  //   f0r(i, PCL.size()) {
  //     if (PCL[i][0].f >= start.f && PCL[i][0].f >= start.s && PCL[i][1].f <= end.f && PCL[i][1].s <= end.s) {
  //       // current is a superset of another PCL
  //       PCL.erase(PCL.begin() + i);
  //       break;
  //     } else if (PCL[i][0].f <= start.f && PCL[i][0].s <= start.s && PCL[i][1].f >= end.f && PCL[i][1].s >= end.s) {
  //       // current is a subset of another PCL
  //       // goto end;
  //       return;
  //     } 
  //   }  
    
  //   PCL.pb({start, end});
  // }

  if (isValidPCL) {
    PCL.pb({start, end});
  }

  // end:;
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=740 
int main() {
    usaco("where");
	// usacio("testCase");
    // io;

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
            floodfill(mp(r1, c1), mp(r2, c2));
          }
        }
      }
    }

    // PCL.pb({mp(0, 2), mp(0, 5)});
    // PCL.pb({mp(0, 2), mp(0, 7)});
    // PCL.pb({mp(0, 4), mp(4, 6)});
    // PCL.pb({mp(0, 4), mp(5, 6)});

    // Prune my PCL for subsets
    vector<int> removed_indices;
    f0r(i, PCL.size()) {
      f0r(j, PCL.size()) {
        if (i == j) continue;

        if (PCL[i][0].f >= PCL[j][0].f && PCL[i][0].s >= PCL[j][0].s 
        && PCL[i][1].f <= PCL[j][1].f && PCL[i][1].s <= PCL[j][1].s) {
          // PCL.erase(PCL.begin() + i);
          removed_indices.pb(i);
          break;
        }
      }
    }
    sort(removed_indices.begin(), removed_indices.end());
    DEBUG(removed_indices);
    DEBUG(removed_indices.size(), PCL.size());

    DEBUG(PCL);
    cout << PCL.size() - removed_indices.size() << endl;

    // DEBUG("DOING CONTIG FLOODFILL");
    // contig_floodfill(mp(0, 0), mp(n - 1, n - 1));

    // DEBUG("DOING SPOT FLOODFILL");
    // spot_floodfill(mp(0, 0), mp(n - 1, n - 1));

}
