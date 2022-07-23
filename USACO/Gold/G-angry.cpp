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

// Checking if mid has enough initial detonation to detonate all the crates
bool works(vector<ll>& bales, ll mid, bool addHalf) {
    ll bales_exploded = 0;
    bool incrementing = true; // is counter going up or down as we go right
    ll counter = 0; // going up by how much right now

    while (bales_exploded + 1 < bales.size()) {
        // DEBUG(bales_exploded, counter, incrementing);
        // If we are still incrementing counter or not
        if (incrementing) {

            if (bales_exploded + 1 >= bales.size()) {
                throw invalid_argument("0");
            }
            // Need to explode one or more bales in this one explosion
            if (bales.at(bales_exploded + 1) - bales.at(bales_exploded) <= counter) {
                ll og = bales.at(bales_exploded);
                if (bales_exploded + 1 >= bales.size()) {
                    throw invalid_argument("1");
                }
                counter++;
                while (bales_exploded + 1 < bales.size() && bales.at(bales_exploded + 1) - og <= counter) {
                    bales_exploded++;
                }
            } else {
                if (bales_exploded + 1 >= bales.size()) {
                    throw invalid_argument("2");
                }
                // we need to increase the counter, right now it's not sufficient to reach the next bale
                counter = bales.at(bales_exploded + 1) - bales.at(bales_exploded);
                bales_exploded++;
            }

            // Case when current counter exceeds mid
            if (counter >= mid) {
                DEBUG(bales_exploded, counter, incrementing);
                DEBUG(mid, bales[bales_exploded - 1], bales[bales_exploded], bales[bales_exploded + 1]);
                // no longer incrementing, going down
                incrementing = false;

                // and make sure counter isn't double mid, if it's double mid then cannot cover incrementing X and decrementing X 
                // as well as starting the explosion in the middle of the two bales case, so false not possible mid is too low
                if (addHalf == false) {
                    if (mid * 2 < counter) {
                        return false;
                    }
                } else {
                    // in bottom case where we add 0.5, then when going up then down, double 0.5 so + 1 
                    if (mid * 2 + 1 < counter) {
                        return false;
                    }
                }

                ll og = bales[bales_exploded - 1];

                // If not addHalf, and counter just equals mid continue descending with current counter
                if (!addHalf && counter == mid) {
                    continue;
                } else {
                    if (addHalf) {
                        DEBUG(bales[bales_exploded + 1] - og, mid, mid * 2 + 1);
                        DEBUG(bales_exploded);
                        while(bales[bales_exploded + 1] - og <= mid * 2 + 1) {
                            bales_exploded++;
                        }
                        DEBUG(bales[bales_exploded - 1], bales[bales_exploded]);
                        DEBUG(bales_exploded);
                        counter--;
                        counter--;
                    } else {
                        counter--;
                    }
                }
            }

        } else {
            ll og = bales.at(bales_exploded);

            if (bales_exploded + 1 >= bales.size()) {
                throw invalid_argument("3");
            }
            // Cannot reach the next bale with current explosion size, and since decrementing it's false
            if (bales.at(bales_exploded + 1) - og > counter) {
                DEBUG(bales.at(bales_exploded + 1), og, counter);
                DEBUG("false 1");
                return false;
            }

            if (bales_exploded + 1 >= bales.size()) {
                throw invalid_argument("4");
            }
            while (bales_exploded + 1 < bales.size() && bales.at(bales_exploded + 1) - og <= counter) {
                bales_exploded++;
            }
            counter--;

            // We cannot reach the end as counter just hit negative, not enough explosion to make it
            if (counter < -1) {
                DEBUG("false 2");
                return false;
            }
        }
    }

    return true;
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=597 
int main() {
    usaco("angry");
    // io;

    cin >> n;
    vector<ll> bales(n);

    f0r(i, n) {
        cin >> bales.at(i);
    }

    sort(bales.begin(), bales.end());
    DEBUG(bales);

    // Binary Search minimum "working" solution
    ll lo = 1, hi = 1e9;
    while (lo < hi) {
        ll mid = (lo + hi)/2;

        DEBUG(mid, works(bales, mid, false), lo, hi);

        if (!works(bales, mid, false)) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    if (!works(bales, lo, false)) {
        lo++;
    }  

    DEBUG(false, works(bales, 21559, true));
    DEBUG(false, works(bales, 21560, false));

    if (works(bales, (lo - 1), true)) {
        cout << (lo - 1) << ".5" << endl;
    } else {
        cout << lo << ".0" << endl;
    }
}