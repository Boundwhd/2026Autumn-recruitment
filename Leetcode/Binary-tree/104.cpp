/*二叉树的最大深度*/
#include "../leetcode.h"

int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

/*递归法，求解两个子树的高度，再递归*/