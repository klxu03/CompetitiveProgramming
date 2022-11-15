// https://leetcode.com/contest/weekly-contest-318/problems/apply-operations-to-an-array/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> applyOperations(vector<int>& nums) {
        vector<int> ret;
        for(int i = 0; i < nums.size() - 1; i++) {
            if (nums[i] == nums[i + 1] && nums[i] != 0) {
                ret.push_back(nums[i] * 2);
                nums[i + 1] = 0;
            } else {
                if (nums[i] != 0) {
                    ret.push_back(nums[i]);
                }
            }
        }
        
        if (nums[nums.size() - 1] != 0) {
            ret.push_back(nums[nums.size() - 1]);
        }
        
        while (ret.size() < nums.size()) {
            ret.push_back(0);
        }
        
        return ret;
    }
};