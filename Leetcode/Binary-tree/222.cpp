/*完全二叉树的节点个数*/
#include "../leetcode.h"

class Solution {
public:
    int countNodes(TreeNode* root) {
        return dfs(root);
    }

    int dfs(TreeNode* root) {
        if (!root) return 0;

        int left = dfs(root->left);
        int right = dfs(root->right);

        return left + right + 1;
    }
};