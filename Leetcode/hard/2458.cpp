// https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/description/

#include <bits/stdc++.h>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:    
    vector<int> left_height; // left_height[5] gives the left height of node 5
    vector<int> right_height; 
    vector<int> depth; // depth of each node
    
    vector<bool> matters; // matters[5] if this node is "important"
    vector<int> alt_height; // alt_height[i] gives alt height assuming matters[i] == true
    
    int alt_height_counter; // running max keeping track of alternate heights
    
    // Calculating the alt heights of nodes that matter (what best height of tree is without this node and not already down this path)
    void getAltHeights(TreeNode* node) {
        matters[node->val] = true;
        alt_height[node->val] = alt_height_counter; // Set the alt height of this node that matters
        
        // Figure out which node matters
        if (left_height[node->val] > right_height[node->val]) {
            alt_height_counter = max(alt_height_counter, depth[node->val] + right_height[node->val]); // Recalculate the running "max" alt_height
            getAltHeights(node->left);
        } else if (right_height[node->val] > left_height[node->val]) {
            alt_height_counter = max(alt_height_counter, depth[node->val] + left_height[node->val]); // Recalculate the running "max" alt_height
            getAltHeights(node->right);
        }
    }
    
    // Calculating the heights and storing the depth of each node
    int getHeightsAndDepth(TreeNode* node, int currDepth) {
        // Base case, if null node height of 0
        if (node == nullptr) {
            return 0;
        }
        
        // Setting the depth of the current node
        depth[node->val] = currDepth;
        
        // Recurse left and right node
        left_height[node->val] = getHeightsAndDepth(node->left, currDepth + 1);
        right_height[node->val] = getHeightsAndDepth(node->right, currDepth + 1);
        
        return 1 + max(left_height[node->val], right_height[node->val]);
    }
    
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        left_height = vector<int>(1e5 + 1, 0);
        right_height = vector<int>(1e5 + 1, 0);
        depth = vector<int>(1e5 + 1, 0);
        
        matters = vector<bool>(1e5 + 1, false);
        matters[root->val] = true;
        alt_height = vector<int>(1e5 + 1, 0);
        
        alt_height_counter = 0;
        
        getHeightsAndDepth(root, 0);
        
        getAltHeights(root);
                
        int height = max(left_height[root->val], right_height[root->val]);
        
        // Filling in the return array of answers
        vector<int> ret(queries.size());
        for(int i = 0; i < queries.size(); i++) {
            if (matters[queries[i]]) {
                ret[i] = max(depth[queries[i]] - 1, alt_height[queries[i]]); // choose between alt_height or depth of parent
            } else {
                ret[i] = height; // not a node that matters, so it's just the tree height
            }
        }
        
        return ret;
    }
};