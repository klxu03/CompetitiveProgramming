// https://leetcode.com/contest/weekly-contest-317/problems/minimum-addition-to-make-integer-beautiful/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target) {
        long long orig_n = n;
        long long n_sum = 0;
        while (n > 0) {
            n_sum += (n % 10);
            n /= 10;
        }
        cout << "initial: " << n_sum << endl;
        
        long long ret = 0;
        n = orig_n;
        
        long long ten_mod = 1;
        
        while (n_sum > target) {
            // need to make the ones a 0
            n = orig_n + ret;
            
            n_sum = 0;
            
            ten_mod *= 10;
            // cout << "1: " << n << " " << ten_mod << endl;
            
            long long last_digit = n % ten_mod;
            // cout << last_digit << endl;
            ret += ten_mod - last_digit;
            n = orig_n + ret;
            
            // cout << "n: " << n << endl;
            
            while (n > 0) {
                n_sum += (n % 10);
                n /= 10;
            }
            
            // cout << last_digit << endl;
            // cout << n_sum << endl;
            // cout << ret << endl;
        }
        
        return ret;
    }
};