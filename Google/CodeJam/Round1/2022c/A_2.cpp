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
        char first_char = inp[i][0];
        f0r(j, inp[i].size()) {
            char curr = inp[i][j];
            // if (letters[curr - 'A'] != '!' && j - letters[curr - 'A'] > 1) {
            //     possible = false;
            // }
            // letters[curr - 'A'] = j;
            if (curr != first_char) {
                all_same[i] = false;
            }
        }
    }
    DEBUG(all_same);

    char beginning_letter = '!';
    set<ll> possible_used; // index of words already checked

    // This is to find the beginning letter
    if (possible) {
        bool stop = true;
        ll counter = 0;
        while (!stop || counter == 0) {
            stop = true;
            counter++;

            f0r(i, n) {
                if(all_same[i]) {
                    possible_used.insert(i);
                    continue;
                } 

                char beginning = inp[i][0];
                char ending = inp[i][inp[i].size() - 1];

                if (beginning_letter == '!') {
                    beginning_letter = beginning;
                    // possible_used.insert(i);
                    stop = false;
                }

                if (beginning_letter == ending && possible_used.count(i) == 0) {
                    beginning_letter = beginning;
                    stop = false;
                    possible_used.insert(i);
                }
            }
        }

        ll num_looked = 0;
        f0r(i, n) {
            DEBUG(i, possible_used.count(i));
            // Didn't look through each possible word
            if (possible_used.count(i) == 0) {
                num_looked++;
            }
        }
        // if (num_looked > 1) {
        //     possible = false;
        // }
    }
    DEBUG(possible, beginning_letter);

    if (possible) {
        string ret;
        set<ll> used;

        char curr = beginning_letter;
        string word = "?";
        string prev_word = "!";

        ll words_counter = 0;
        /*
3
9
A AA BB A BB AZ ZZY BA WB
4
OY AAA BB YO
7
HAS CODE CCCC SSSSSSSYYYYZ LLLL EEEE LKKKJJJJ
        */

       /*
        REDO where you first add HAS, then SSSYZ, then CCC CODE, then EEEE, then LLL, LKKJJJJ
        Add each component one at a time
       */
        while (prev_word != word) {
            prev_word = word;

            // Add repeats
            f0r(i, n) {
                if (all_same[i] && inp[i][0] == curr && used.count(i) == 0) {
                    used.insert(i);
                    ret += inp[i];
                    words_counter++;
                }
            }

            // Add the normal one
            f0r(i, n) {
                if (!all_same[i] && inp[i][0] == curr && used.count(i) == 0) {
                    used.insert(i);
                    ret += inp[i];
                    
                    // Set curr, or new_beginning check to be current ending
                    curr = inp[i][inp[i].size() - 1];

                    word = inp[i];
                    words_counter++;
                    break;
                }
            }
            DEBUG(ret);
        }
        DEBUG(used);

        // HAS CODE CCCCCCC
        f0r(i, n) {
            if (all_same[i]) continue;
            if (used.count(i) > 0) continue;

            DEBUG("HASCODECC", i);

            char this_beginning = inp[i][0];
            f0r(j, n) {
                DEBUG(this_beginning, inp[j][0]);
                if (all_same[j] && inp[j][0] == this_beginning && used.count(j) == 0) {
                    ret += inp[j];
                    used.insert(j);
                    words_counter++;
                }
            }
            ret += inp[i];
            used.insert(i);
            words_counter++;
        }

        // look at last letter add in all_used
        char last_letter = ret[ret.size() - 1];
        f0r(i, n) {
            if(all_same[i] && inp[i][0] == last_letter && used.count(i) == 0) {
                ret += inp[i];
                used.insert(i);
            }
        }
        DEBUG("last letter", ret);

        // Add in all the unused ones at the end
        f0r(i, n) {
            DEBUG("Last", used.count(i));
            if (used.count(i) == 0) {
                ret += inp[i];
                words_counter++;
            }
        }

        set<char> final_letters_used;
        f0r(i, ret.size()) {
            if (final_letters_used.count(ret[i]) > 0 && ret[i] != ret[i - 1]) {
                possible = false;
            }
            final_letters_used.insert(ret[i]);
        }
        DEBUG(final_letters_used, words_counter);

        if (possible) {
            cout << ret << endl;
        } else {
            DEBUG(ret);
            cout << "IMPOSSIBLE" << endl;
        }

    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}