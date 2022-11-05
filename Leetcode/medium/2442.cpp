// https://leetcode.com/contest/weekly-contest-315/problems/count-number-of-distinct-integers-after-reverse-operations/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countDistinctIntegers(vector<int>& nums) {
        set<int> s;
        for (int i = 0; i < nums.size(); i++) {
            s.insert(nums[i]);
            
            // reverse number
            int n = nums[i];
            int reversed_num = 0;
            int rem = 0;
            while (n != 0) {
                rem = n % 10;
                reversed_num = reversed_num * 10 + rem;
                n /= 10;
            }
            s.insert(reversed_num);
        }
        
        return s.size();
    }
};