// https://leetcode.com/contest/weekly-contest-315/problems/largest-positive-integer-that-exists-with-its-negative/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int findMaxK(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<int> s;
        
        int ret = -1;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0) {
                s.insert(nums[i]);
            } else {
                if (s.find(-1 * nums[i]) != s.end()) {
                    ret = nums[i];
                }
            }
        }
        
        return ret;
    }
};