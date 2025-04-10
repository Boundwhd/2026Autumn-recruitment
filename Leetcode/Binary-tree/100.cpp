/*相同的树*/
#include "../leetcode.h"

bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr && q == nullptr) {
        return true;
    } else if (p == nullptr || q == nullptr) {
        return false;
    } else if (p->val != q->val) {
        return false;
    }

    return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right));
}
