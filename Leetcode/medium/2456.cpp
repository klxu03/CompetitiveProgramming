// https://leetcode.com/contest/weekly-contest-317/problems/most-popular-video-creator/

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        map<string, long long> sum_popularity;
        map<string, pair<long long, string> > best; // pair.f is the # views, pair.s is the ID
        
        for(int i = 0; i < views.size(); i++) {
            if (best.find(creators[i]) == best.end()) {
                // not in maps yet
                sum_popularity.insert({creators[i], views[i]});
                best.insert({creators[i], {views[i], ids[i]}});
            } else {
                sum_popularity[creators[i]] += views[i];
                if (views[i] > best[creators[i]].first) {
                    best[creators[i]] = {views[i], ids[i]};
                } else if (views[i] == best[creators[i]].first && ids[i] < best[creators[i]].second) {
                    best[creators[i]] = {views[i], ids[i]};
                }
            }
        }
        
        // for (auto it = sum_popularity.begin(); it != sum_popularity.end(); ++it) {
        //     cout << it->first << " " << it->second << endl;
        // }
        
        long long curr_max = -1;
        vector<vector<string>> res;
        
        for (const auto &it : sum_popularity) {
            // cout << it.first << " " << it.second << endl;
            if (it.second > curr_max) {
                curr_max = it.second;
            }
        }
        
        for (const auto &it : sum_popularity) {
            if (it.second == curr_max) {
                vector<string> curr = {it.first, best[it.first].second};
                // cout << curr[0] << " " << curr[1] << endl;
                res.push_back(curr);
            }
        }
        
        return res;
    }
};