/*对称二叉树*/
#include "../leetcode.h"

bool check(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
}


bool isSymmetric(TreeNode* root) {
    return check(root->left, root->right);
}

/*创建check函数，来检查两个对称节点是否满足要求*/