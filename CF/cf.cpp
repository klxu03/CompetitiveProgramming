using namespace std;
#include <bits/stdc++.h>

// https://codeforces.com/contest/1901/problem/D

// 5 5 5 5 5
// 2 4 5 3 1

// i fix index i, and I'm finding cost if chain left first, then right
// bottle_neck_right + i (num of elements to the left)
// bottle_neck_right = hp + dist from i

// 1 1 1 1 1 1 1000 1 1 1 100
// neg counter = 0

int main() {
    int n;
    cin >> n;

    vector<long long> inp(n);
    for (int i = 0; i < n; i++) {
        cin >> inp[i];
    }

    // handles edge case n == 1
    if (n == 1) {
        cout << inp[0] << endl;
        return 0;
    }

    vector<long long> preprocess_right(n); // preprocess_right[j] gives me the index to the right of j that is going to be the bottleneck index
    preprocess_right[n - 1] = -1;
    long long threshold_val = inp[n - 1];
    int ind = n - 1;
    int neg_counter = -1;

    for (int i = n - 2; i >= 0; i--) {
        preprocess_right[i] = ind;

        if (inp[i] + neg_counter >= threshold_val) {
            threshold_val = inp[i] + neg_counter;
            ind = i;
        }
        neg_counter--;
    }

    vector<long long> preprocess_left(n);
    preprocess_left[0] = -1;
    threshold_val = inp[0];
    ind = 0;
    neg_counter = -1;

    for (int i = 1; i < n; i++) {
        preprocess_left[i] = ind;

        if (inp[i] + neg_counter >= threshold_val) {
            threshold_val = inp[i] + neg_counter;
            ind = i;
        }
        neg_counter--;
    }

    long long ret = INT_MAX;

    // distance + hp
    long long score_right = max(preprocess_right[0] + inp[preprocess_right[0]], inp[0]);
    long long score_left = max((n - 1 - preprocess_left[n - 1]) + inp[preprocess_left[n - 1]], inp[n - 1]);
    ret = min(score_right, score_left);

    // power = 5, + 2 away so he effectively needs 7
    // 5 5 5 5 5
    // 5 6 9 8 7 <- wiz power

    for (int i = 1; i < n - 1; i++) {
        // assume index i is where we are starting

        // min(ret, max(score going left, going right))
        long long required_power_left = -1; // i first chain right, then go left
        long long required_power_right = -1;

        // 2 + 5 + 2
        required_power_left = (n - i - 1) + inp[preprocess_left[i]] + (i - preprocess_left[i]);

        // i els to the left
        required_power_right = i + inp[preprocess_right[i]] + (preprocess_right[i] - i);

        ret = min(ret, max(max(required_power_left, required_power_right), inp[i]));
    }

    cout << ret << endl;
}