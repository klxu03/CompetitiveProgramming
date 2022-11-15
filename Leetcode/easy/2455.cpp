// https://leetcode.com/contest/weekly-contest-317/problems/average-value-of-even-numbers-that-are-divisible-by-three/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int averageValue(vector<int>& nums) {
        int counter = 0;
        int sum = 0;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] % 6 == 0) {
                sum += nums[i];
                counter++;
            }
        }
        
        if (counter == 0) {
            return 0;
        } else {
            
        
            return sum/counter;
        }
    }
};