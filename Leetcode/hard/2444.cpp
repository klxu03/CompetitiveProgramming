// https://leetcode.com/contest/weekly-contest-315/problems/count-subarrays-with-fixed-bounds/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long numFixedBoundArray(vector<int>& nums, int start_index, int minK, int maxK) {
        if (nums[0] == -1 || start_index >= nums.size()) {
            return 0;
        }
        
        long long sub = -1;
        int start = -1;
        int end = -1;
        pair<bool, bool> p = {false, false}; // p.f if minK found yet, p.s if maxK
        for (int i = start_index; i < nums.size(); i++) {
            if (nums[i] == minK && !p.first) {
                if (start == -1) {
                    start = i;
                } else {
                    end = i;
                }
                
                p.first = true;
            }
            
            if (nums[i] == maxK && !p.second) {
                if (start == -1) {
                    start = i;
                } else {
                    end = i;
                }
                
                p.second = true;
            }
            
            // found both
            if (p.first && p.second) {
                sub = end - start;
                break;
            }
        }
        
        if (p.first && p.second) {            
            long long ret = nums.size() - sub - start_index + numFixedBoundArray(nums, start_index + 1, minK, maxK);
            ret -= (start - start_index);
            return ret;
        }
        
        return 0;
    }
    
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {      
        vector<vector<int>> cut_nums;
        cut_nums.push_back({});
        int counter = 0;
        
        pair<bool, bool> p = {false, false}; // p.first is if minK is in yet, p.second is if maxK is in yet
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] == minK) {
                p.first = true;
            }    
            
            if (nums[i] == maxK) {
                p.second = true;
            }
                        
            if (nums[i] < minK || nums[i] > maxK) {
                if (!p.first || !p.second) {
                    cut_nums[counter].push_back(-1); // in case no ele
                    cut_nums[counter][0] = -1;
                }
                
                counter++;
                cut_nums.push_back({});
                
                p = {false, false};
                continue; 
            }
            
            cut_nums[counter].push_back(nums[i]);
        }
        
        long long res = 0;
        // cout << "cut_nums.size(): " << cut_nums.size() << endl;
        for (int i = 0; i < cut_nums.size(); i++) {            
            // cout << "i: " << i << endl;
            if (cut_nums[i].size() <= 0) {
                continue;
            }
            // for (int j = 0; j < cut_nums[i].size(); j++) {
            //     cout << cut_nums[i][j] << " ";
            // }
            cout << endl;
            long long ret = numFixedBoundArray(cut_nums[i], 0, minK, maxK);
            res += ret;
            
        }
        // cout << cut_nums[4][0];
        
        return res;
    }
};