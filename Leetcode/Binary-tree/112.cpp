/*路径总和*/
#include "../leetcode.h"

bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    if (!root->left && !root->right) {
        return root->val == targetSum;
    }
    return hasPathSum(root->left, targetSum - root->left->val) || hasPathSum(root->right, targetSum - root->right->val);
}