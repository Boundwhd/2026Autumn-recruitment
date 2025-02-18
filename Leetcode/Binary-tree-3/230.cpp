/*二叉搜索树中第K小的元素*/
#include "../leetcode.h"

class Solution {
    vector<int> nums;
public:
int kthSmallest(TreeNode* root, int k) {
        dfs(root);
        return nums[k - 1];
    }

    void dfs(TreeNode* root) {
        if (!root) return;
        dfs(root->left);
        nums.push_back(root->val);
        dfs(root->right);
    }
};