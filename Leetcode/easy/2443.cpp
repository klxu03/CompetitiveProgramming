// https://leetcode.com/contest/weekly-contest-315/problems/sum-of-number-and-its-reverse/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool sumOfNumberAndReverse(int num) {
        if (num == 0) {
            return true;
        }
        
        for (int i = 0; i < num; i++) {
            // reverse number
            int n = i;
            int reversed_num = 0;
            int rem = 0;
            while (n != 0) {
                rem = n % 10;
                reversed_num = reversed_num * 10 + rem;
                n /= 10;
            }
            
            if (i + reversed_num == num) {
                return true;
            }
        }
        
        return false;
    }
};