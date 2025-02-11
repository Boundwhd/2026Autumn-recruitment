/*二叉树中的最大路径和*/
#include "../leetcode.h"

class Solution {
    int ans = INT_MIN;
public:
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return ans;
    }

    int dfs(TreeNode* cur) {
        if (!cur) return 0;
        int left = max(0, dfs(cur->left));
        int right = max(0, dfs(cur->right));

        ans = max(ans, cur->val + left + right);
        return cur->val + max(left, right);
    }
};