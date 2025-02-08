/*翻转二叉树*/
#include "../leetcode.h"

TreeNode* invertTree(TreeNode* root) {
    if (root == nullptr) return nullptr;

    TreeNode* left = invertTree(root->left);
    TreeNode* right = invertTree(root->right);
    
    root->left = right;
    root->right = left;

    return root;
}

/*从叶子节点开始，翻转每一个节点，返回每一个翻转后的根节点*/