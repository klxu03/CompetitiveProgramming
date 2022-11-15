// https://leetcode.com/contest/weekly-contest-318/problems/maximum-sum-of-distinct-subarrays-with-length-k/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    // Print the queue
void showq(queue<int> gq)
{
    queue<int> g = gq;
    cout << "Q: ";
    while (!g.empty()) {
        cout << g.front() << " ";
        g.pop();
    }
    cout << '\n';
}
    
    void shows(set<int> st) {
        cout << "S: ";
        for (auto it: st) {
            cout << it << " ";
        }
        cout << endl;
    }
    
    long long maximumSubarraySum(vector<int>& nums, int k) {
        long long ret = 0;
        
        long long running_sum = 0;
        set<int> s;
        queue<int> q;
        
        for(int i = 0; i < nums.size(); i++) {
            if (s.find(nums[i]) == s.end()) {
                // not currently in the set
                
                if (s.size() < k) {
                    // Set too small
                    s.insert(nums[i]);
                    q.push(nums[i]);
                    running_sum += nums[i];
                    
                    if (s.size() == k) {
                        ret = max(running_sum, ret);
                    }
                    
                } else {
                    // Gotta delete front element
                    int front = q.front();
                    q.pop();
                    s.erase(front);
                    running_sum -= front;
                    q.push(nums[i]);
                    running_sum += nums[i];
                    s.insert(nums[i]);
                    
                    ret = max(running_sum, ret);
                }
            } else {
                // found a repeat
                // int front = q.front();
                // q.pop();
                
                // clear all non-nums[i] elements
//                 while (front != nums[i]) {
//                     running_sum -= front;
//                     s.erase(front);
                    
//                     if (q.size() == 0) {
//                         break;
//                     }
//                     front = q.front();
//                     q.pop();
//                 }
                
                while (q.size() != 0) {
                    int front = q.front();
                    q.pop();
                    running_sum -= front;
                    s.erase(front);
                    
                    if (front == nums[i]) {
                        break;
                    }
                    
                }
                
                running_sum += nums[i];
                s.insert(nums[i]);
                q.push(nums[i]);
                
                if (s.size() == k) {
                    ret = max(running_sum, ret);
                }
            }
            
            if (s.size() == k) {
                ret = max(running_sum, ret);
            }
            
            // showq(q);
            // shows(s);
            // cout << "running: " << running_sum << " ret: " << ret << endl;
            
        }
        
        return ret;
    }
};