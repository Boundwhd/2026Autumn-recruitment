/*求根节点到叶节点数字之和*/
#include "../leetcode.h"

class Solution {
    int ans = 0;
public:
    int sumNumbers(TreeNode* root) {
        dfs(root, 0);
        return ans;
    }

    void dfs(TreeNode* node, int num) {
        num = num * 10 + node->val;
        if (!node->left && !node->right) ans += num;
        if (node->left) dfs(node->left, num);
        if (node->right) dfs(node->right, num);
    }
};
