#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define pb push_back
#define f first
#define s second
#define pii pair<int, int>
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int stooi(string num) {
    int ret = 0;
    if (num[0] == '-') {
        f1r(i, 1, num.size()) {
            ret *= 10;
            ret += num[i] - '0';
        }

        ret *= -1;
    } else {
        f0r(i, num.size()) {
            ret *= 10;
            ret += num[i] - '0';
        }
    }

    return ret;
}

// im assuming (2,2) isn't an interval, these are actual ones with values in them
vector<pii> split(string interval) {
    if (interval == "null") return {};

    vector<pii> ret;
    vector<string> v;
    int i = 0;
    while (i < interval.size()) {
        string curr = "";
        while (i < interval.size()) {
            if (i == interval.size() - 1) {
                curr += interval[i];
                v.pb(curr);
                i++;
                break;
            } else if (interval[i] == ' ') {
                v.pb(curr);
                i++;
                break;
            }
            curr += interval[i];

            i++;
        }
    }

    f0r(i, v.size()) {
        string left = "";
        string right = "";

        int j;
        // handle left
        for (j = 1; j < v[i].size(); j++) {
            if (v[i][j] == ',') {
                j++;
                break;
            }
            left.pb(v[i][j]);
        }

        for (j = j; j < v[i].size(); j++) {
            if (v[i][j] == ')' || v[i][j] == ']') {
                break;
            }
            right.pb(v[i][j]);
        }

        int left_n = stooi(left);
        int right_n = stooi(right);

        if (v[i][0] == '(') left_n++;
        if (v[i][v[i].size() - 1] == ')') right_n--;
        ret.pb({left_n, right_n});
    }
    sort(ret.begin(), ret.end());
    return ret;
}

bool in_interval(int num, vector<pii> &interval) {
    f0r(i, interval.size()) {
        if (num >= interval[i].f && num <= interval[i].s) {
            return true;
        }
    }

    return false;
}

void sumsNotCommon(string intervals1, string intervals2, string intervals3) {
    vector<pii> int1 = split(intervals1);
    vector<pii> int2 = split(intervals2);
    vector<pii> int3 = split(intervals3);

    int in_one = 0;
    int in_two = 0;

    f1r(i, -99, 100) {
        int cnt = 0; // # of intervals this num is in

        if (in_interval(i, int1)) cnt++;
        if (in_interval(i, int2)) cnt++;
        if (in_interval(i, int3)) cnt++;

        if (cnt == 1) {
            in_one += i;
        } else if (cnt == 2) {
            in_two += i;
        }
    }

    if (intervals3 == "null") {
        cout << in_one << endl;
    } else {
        cout << in_one << " " << in_two << endl;
    }
}

int main() {
    io;
    string interval1, interval2, interval3;
    getline(cin, interval1);
    getline(cin, interval2);
    getline(cin, interval3);
    sumsNotCommon(interval1, interval2, interval3);
}