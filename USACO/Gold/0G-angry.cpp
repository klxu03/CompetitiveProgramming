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

// Have to do mid + 0.5
bool halfUnderWorks(vector<ll>& bales, ll mid) {
    bool goingUp = true;
    // How much the next bale explosion increments going forward
    ll nextIncrement = 1;
    ll currIndex = 0;

    ll maxIndex = bales.size();
    // DEBUG(maxIndex, mid);
    while(currIndex < maxIndex - 1) {
        DEBUG(goingUp, nextIncrement, currIndex);

        // Case where we need to switch directions
        if (goingUp && bales[currIndex + 1] - bales[currIndex] >= mid) {
            // Perfectly switch
            if (bales[currIndex + 1] - bales[currIndex] <= mid + 1) {
                currIndex++;
                goingUp = false;
                nextIncrement = mid;
            } else {
                // make sure bales[currIndex + 1] isn't more than mid * 2 away
                if (bales[currIndex + 1] - bales[currIndex] > mid * 2) {
                    return false;
                } else {
                    currIndex++;
                    goingUp = false;
                    nextIncrement = mid - 1;
                }

                DEBUG("imperfect switch", currIndex);
            }

        } else if (goingUp) {
        // Still going up left to right increasing explosion size

            // Need to boost nextIncrement by more than 1 
            if (bales[currIndex + 1] - bales[currIndex] > nextIncrement) {
                nextIncrement = bales[currIndex + 1] - bales[currIndex];
                nextIncrement++;
                currIndex++;
                DEBUG("boosted going up");
            } else {
                // Case where you might explode multiple bales in one explosion
                // Or just "perfectly" far enough for one bale

                ll ogIndex = currIndex;
                while (currIndex + 1 < maxIndex) {
                    if (bales[currIndex + 1] - bales[ogIndex] <= nextIncrement) {
                        currIndex++;
                    } else {
                        break;
                    }
                }
                nextIncrement++;
            }

            if (nextIncrement > mid) {
                goingUp = false;
                nextIncrement = mid;
            }
        } else {
            // Decreasing explosion size

            // Next bale is too far away
            if (bales[currIndex + 1] - bales[currIndex] > nextIncrement) {
                return false;
            }

            // Might explode multiple bales or just "perfectly" enough for one
            ll ogIndex = currIndex;
            while (currIndex + 1 < maxIndex) {
                if (bales[currIndex + 1] - bales[ogIndex] <= nextIncrement) {
                    currIndex++;
                } else {
                    break;
                }
            }
            nextIncrement--;
            if (nextIncrement < 0) {
                return false;
            } else if (nextIncrement == 0) {
                // if (currIndex != bales.size() - 1) {
                //     return false;
                // }
            } 
        }
    }

    return true;
}

// Checks if a specific explosion size of mid can work on these bales
bool works(vector<ll>& bales, ll mid) {
    bool goingUp = true;
    // How much the next bale explosion increments going forward
    ll nextIncrement = 1;
    ll currIndex = 0;

    ll maxIndex = bales.size();
    // DEBUG(maxIndex, mid);
    while(currIndex < maxIndex - 1) {
        DEBUG(goingUp, nextIncrement, currIndex);

        // Case where we need to switch directions
        if (goingUp && bales[currIndex + 1] - bales[currIndex] >= mid) {
            // Perfectly switch
            if (bales[currIndex + 1] - bales[currIndex] <= mid) {
                currIndex++;
                goingUp = false;
                nextIncrement = mid;
            } else {
                // make sure bales[currIndex + 1] isn't more than mid * 2 away
                if (bales[currIndex + 1] - bales[currIndex] > mid * 2) {
                    return false;
                } else {
                    currIndex++;
                    goingUp = false;
                    nextIncrement = mid - 1;
                }

                DEBUG("imperfect switch", currIndex);
            }

        } else if (goingUp) {
        // Still going up left to right increasing explosion size

            // Need to boost nextIncrement by more than 1 
            if (bales[currIndex + 1] - bales[currIndex] > nextIncrement) {
                nextIncrement = bales[currIndex + 1] - bales[currIndex];
                nextIncrement++;
                currIndex++;
                DEBUG("boosted going up");
            } else {
                // Case where you might explode multiple bales in one explosion
                // Or just "perfectly" far enough for one bale

                ll ogIndex = currIndex;
                while (currIndex + 1 < maxIndex) {
                    if (bales[currIndex + 1] - bales[ogIndex] <= nextIncrement) {
                        currIndex++;
                    } else {
                        break;
                    }
                }
                nextIncrement++;
            }

            if (nextIncrement > mid) {
                goingUp = false;
                nextIncrement = mid;
            }
        } else {
            // Decreasing explosion size

            // Next bale is too far away
            if (bales[currIndex + 1] - bales[currIndex] > nextIncrement) {
                return false;
            }

            // Might explode multiple bales or just "perfectly" enough for one
            ll ogIndex = currIndex;
            while (currIndex + 1 < maxIndex) {
                if (bales[currIndex + 1] - bales[ogIndex] <= nextIncrement) {
                    currIndex++;
                } else {
                    break;
                }
            }
            nextIncrement--;
            if (nextIncrement < 0) {
                return false;
            } else if (nextIncrement == 0) {
                // if (currIndex != bales.size() - 1) {
                //     return false;
                // }
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
        cin >> bales[i];
    }
    sort(bales.begin(), bales.end());

    DEBUG(bales);

    ll lo = 0, hi = 1e9;

    // DEBUG(works(bales, 2));
    // DEBUG(works(bales, 3));
    // DEBUG(works(bales, 4));
    // DEBUG(works(bales, 100));

    while(lo < hi) {
		ll mid = (lo + hi + 1)/2;
        DEBUG(mid);

		// Binary search part
		if(works(bales, mid)) {
			if(hi == mid) {
				hi--;
			} else {
				hi = mid;
			}
		} else {
			lo = mid + 1;
		}
    }

	if (works(bales, lo) == false) {
		lo++;
	}

    // Then try lo - 0.5 case and see if it still works
    if (halfUnderWorks(bales, lo - 1)) {
        cout << lo << ".5" << endl;
    } else {
        cout << lo << ".0" << endl;
    }

    DEBUG(works(bales, 20000));
}