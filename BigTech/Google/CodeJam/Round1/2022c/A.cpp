#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>
#include <deque>
#include <climits>
#include <numeric>
#include <cmath>
#include <iomanip>

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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

void solve() {
	cin >> n;
    bool possible = true;

    vector<string> inp(n);

    f0r(i, n) {
        cin >> inp[i];
    }

    vector<bool> all_same(n, true);
    // First make sure each letter in each word is contiguous
    f0r(i, n) {
        vector<char> letters(26, '!');
        char first_char = inp[i][0];
        f0r(j, inp[i].size()) {
            char curr = inp[i][j];
            if (letters[curr - 'A'] != '!' && j - letters[curr - 'A'] > 1) {
                possible = false;
            }
            letters[curr - 'A'] = j;
            if (curr != first_char) {
                all_same[i] = false;
            }
        }
        DEBUG(i, possible);
    }
    DEBUG(all_same);

    char beginning_letter = '!';

    // Check if beginnings and endings make sense
    set<ll> possible_used;
    // set<char> letters_used;
    if (possible) {
        bool stop = true;
        ll counter = 0;
        while(!stop || counter == 0) {
            stop = true;
            f0r(i, n) {
                if (all_same[i]) continue;

                char beginning = inp[i][0];
                char ending = inp[i][inp[i].size() - 1];

                if (beginning_letter == '!') {
                    beginning_letter = beginning;
                    // possible_used.insert(i);
                    // f1r(j, 0, inp[i].size()) {
                    //     letters_used.insert(inp[i][j]);
                    // }
                    stop = false;
                }
                // DEBUG(letters_used); 
                
                if (beginning_letter == ending && possible_used.count(i) == 0) {
                    beginning_letter = beginning;
                    stop = false;
                    possible_used.insert(i);

                    // if (inp[i].size() > 1) {
                    //     ll j = 1;
                    //     DEBUG(true, inp[i][j], letters_used.count(inp[i][j]), inp[i][j] != inp[i][j - 1] );
                    //     if (letters_used.count(inp[i][j]) > 0 && inp[i][j] != inp[i][j - 1]) {
                    //         possible = false;
                    //     }
                    //     DEBUG(possible);
                    //     letters_used.insert(inp[i][j]);
                    // }

                    // f1r(j, 1, inp[i].size()) {
                    //     DEBUG(true, inp[i][j], letters_used.count(inp[i][j]), inp[i][j] != inp[i][j - 1] );
                    //     if (letters_used.count(inp[i][j]) > 0 && inp[i][j] != inp[i][j - 1]) {
                    //         possible = false;
                    //     }
                    //     letters_used.insert(inp[i][j]);
                    // }
                }

                f0r(j, n) {
                    if (i == j || all_same[j]) continue;
                    if (inp[j][0] == beginning) {
                        possible = false;
                    }

                    if (inp[j][inp[j].size() - 1] == ending) {
                        possible = false;
                    }
                }
                DEBUG(i, possible, beginning_letter);
            }

            counter++;
        }
    }

    if (possible) {
        // let's build out the string
        string ret;
        set<ll> used;

        char curr = beginning_letter;
        string word = "?";
        string prev_word = "!";
        ll counter = 0;
        while(word != prev_word) {
            prev_word = word;
            // Add repeats
            f0r(i, n) {
                if (all_same[i] && inp[i][0] == curr && used.count(i) == 0) {
                    used.insert(i);
                    ret += inp[i];
                }
            }
            DEBUG(ret, prev_word, word, curr);

            // Add the normal one
            f0r(i, n) {
                if (!all_same[i] && inp[i][0] == curr && used.count(i) == 0) {
                    used.insert(i);
                    ret += inp[i];
                    curr = inp[i][inp[i].size() - 1];

                    word = inp[i];
                }
            }
            DEBUG(ret, word);
            counter++;
        }

        // Add in all the full same ones at the end
        f0r(i, n) {
            if (all_same[i] && used.count(i) == 0) {
                ret += inp[i];
            }
        }

        set<char> final_letters_used;
        f0r(i, ret.size()) {
            if (final_letters_used.count(ret[i]) > 0 && ret[i] != ret[i - 1]) {
                possible = false;
            }
            final_letters_used.insert(ret[i]);
        }

        if (possible) {
            cout << ret << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }

    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}