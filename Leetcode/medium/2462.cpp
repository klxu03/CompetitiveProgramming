// https://leetcode.com/contest/weekly-contest-318/problems/total-cost-to-hire-k-workers/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        cout << costs.size() << endl;
        multiset<int> l;
        multiset<int> r;
        
        long long ret = 0;
        
        for(int i = 0; i < candidates; i++) {
            l.insert(costs[i]);
        }
        int l_c = candidates;
        
        int r_c;
        if (costs.size() - candidates >= candidates) {
            for (int i = 0; i < candidates; i++) {
                r.insert(costs[costs.size() - 1 - i]);
            }
            r_c = candidates;
        } else {
            for (int i = candidates; i < costs.size(); i++) {
                r.insert(costs[i]);
            }
            r_c = costs.size() - candidates;
        }
        
        for (int i = 0; i < k; i++) {
            if (l.size() > 0 && r.size() > 0) {
                if (*l.begin() <= *r.begin()) {
                    ret += *l.begin();
                    l.erase(l.begin());

                    if (l_c + r_c < costs.size()) {
                        l.insert(costs[l_c]);
                        l_c++;
                    }

                } else {
                    ret += *r.begin();
                    r.erase(r.begin());

                    if (l_c + r_c < costs.size()) {   
                        r.insert(costs[costs.size() - 1 - r_c]);
                        r_c++;
                    }
                } 
            } else if (l.size() == 0 && r.size() > 0) {
                ret += *r.begin();
                r.erase(r.begin());

                if (l_c + r_c < costs.size()) {   
                    r.insert(costs[costs.size() - 1 - r_c]);
                    r_c++;
                }
            } else if (r.size() == 0 && l.size() > 0) {
                ret += *l.begin();
                l.erase(l.begin());
                
                if (l_c + r_c < costs.size()) {
                    l.insert(costs[l_c]);
                    l_c++;
                }
            }

            
            // cout << l_c << " " << r_c << endl;
            // cout << ret << endl;
        }

        return ret;
        
    }
};